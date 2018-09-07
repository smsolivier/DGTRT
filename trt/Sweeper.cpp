#include "Sweeper.hpp"
#include "BilinearIntegrator.hpp"
#include "LinearIntegrator.hpp"

namespace trt 
{

void Sweeper::Solve(Coefficient* sig_s, Coefficient* sig_t, Coefficient* q, 
	const Vector& phi, TVector& psi) const {

	for (int n=0; n<_quad.NumPoints(); n++) {
		double mu = _quad.Point(n); 
		Vector psi_n; 
		psi.GetAngle(n, psi_n); 
		if (mu > 0) SweepLR(mu, sig_s, sig_t, q, phi, psi_n); 
		else SweepRL(mu, sig_s, sig_t, q, phi, psi_n); 
		psi.SetAngle(n, psi_n); 
	}
}

void Sweeper::SweepLR(double mu, Coefficient* sig_s, Coefficient* sig_t, 
	Coefficient* q, const Vector& phi, Vector& psi_n) const {

	CHECK(mu > 0, "mu must be positive for left to right sweeps");

	ConstantCoefficient c_mu(mu); 
	MassIntegrator col_int(sig_t); 
	MassIntegrator scat_int(sig_s); 
	WeakConvectionIntegrator stream_int(&c_mu); 
	q->SetState(mu); 
	DomainIntegrator di(q); 
	_inflow->SetState(mu); 
	for (int e=0; e<_space->GetNumElements(); e++) {
		Matrix stream, coll, scatt; 
		Element& el = _space->GetElement(e); 
		Vector rhs(el.NumNodes()); 
		stream_int.Assemble(el, stream); 
		col_int.Assemble(el, coll); 
		scat_int.Assemble(el, scatt); 

		// add into one matrix 
		Matrix A(el.NumNodes()); 
		coll.Add(stream, A); 

		// add scattering to rhs 
		Array<int> vdofs; 
		el.GetVDofs(vdofs);
		Vector phi_local; 
		phi.GetSubVector(vdofs, phi_local); 
		phi_local /= 2.; 
		scatt.Mult(phi_local, rhs); 

		// assemble source integrator 
		Vector source; 
		di.Assemble(el, source); 
		rhs += source; 

		// apply upwinding 
		if (e > 0) {
			Element& pel = _space->GetElement(e-1); 
			rhs[0] += mu * psi_n[pel.GetNode(pel.NumNodes()-1).GlobalID()]; 
		} else {
			rhs[0] += mu * _inflow->Eval(el.GetTrans(), 0);  
		}
		A(el.NumNodes()-1, el.NumNodes()-1) += mu; 

		// solve local system 
		Vector psi_local(el.NumNodes()); 
		A.Solve(rhs, psi_local); 

		// put in solution 
		for (int i=0; i<psi_local.Size(); i++) {
			psi_n[el.GetNode(i).GlobalID()] = psi_local[i]; 
		}
	} 
}

void Sweeper::SweepRL(double mu, Coefficient* sig_s, Coefficient* sig_t, 
	Coefficient* q, const Vector& phi, Vector& psi_n) const {

	CHECK(mu < 0, "mu must be negative for right to left sweep"); 

	ConstantCoefficient c_mu(mu); 
	MassIntegrator col_int(sig_t); 
	MassIntegrator scat_int(sig_s); 
	WeakConvectionIntegrator stream_int(&c_mu); 
	q->SetState(mu); 
	DomainIntegrator di(q); 
	_inflow->SetState(mu); 
	for (int e=_space->GetNumElements()-1; e>=0; e--) {
		Element& el = _space->GetElement(e); 
		Matrix stream, coll, scatt; 
		Vector rhs(el.NumNodes()); 

		stream_int.Assemble(el, stream); 
		col_int.Assemble(el, coll); 
		scat_int.Assemble(el, scatt); 

		// add into one matrix 
		Matrix A(el.NumNodes()); 
		coll.Add(stream, A); 

		// add scattering to rhs 
		Array<int> vdofs; 
		el.GetVDofs(vdofs);
		Vector phi_local; 
		phi.GetSubVector(vdofs, phi_local); 
		phi_local /= 2.; 
		scatt.Mult(phi_local, rhs);

		// assemble source integrator 
		Vector source; 
		di.Assemble(el, source); 
		rhs += source; 

		// apply upwinding 
		if (e < _space->GetNumElements()-1) {
			Element& pel = _space->GetElement(e+1); 
			rhs[rhs.Size()-1] += fabs(mu) * psi_n[pel.GetNode(0).GlobalID()]; 
		} else {
			rhs[rhs.Size()-1] += fabs(mu) * _inflow->Eval(el.GetTrans(), 1); 
		}
		A(0,0) += fabs(mu); 

		Vector psi_local(el.NumNodes()); 
		A.Solve(rhs, psi_local); 

		// put into solution 
		for (int i=0; i<psi_local.Size(); i++) {
			psi_n[el.GetNode(i).GlobalID()] = psi_local[i]; 
		}
	}
}

} // end namespace trt 