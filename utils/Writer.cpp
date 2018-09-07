#include "Writer.hpp"

using namespace std; 

namespace trt 
{

Writer::Writer(string name) {
	_base_name = name; 
	_count = 0; 
	_writes = 0; 
	_f = 1; 
}

void Writer::Add(GridFunction& gf, string name) {
	_gf.Append(&gf); 
	_names.Append(name); 
}

void Writer::Write(bool force) {
	if (_count++%_f != 0 && !force) {
		return; 
	}

	ofstream out(_base_name+ to_string(_writes++) + ".curve"); 
	for (int v=0; v<_gf.Size(); v++) {
		out << "# " << _names[v] << endl; 
		FESpace* space = _gf[v]->GetSpace(); 
		for (int e=0; e<space->GetNumElements(); e++) {
			Element& el = space->GetElement(e); 
			int p = el.GetOrder(); 
			double h = 1./p; 
			for (int i=0; i<p; i++) {
				double xref = h*i + h/2; 
				double u = el.Interpolate(xref, *_gf[v]); 
				double xphys = el.GetTrans().Transform(xref); 
				out << xphys << " " << u << endl; 
			}
		}
	}
	out.close(); 
}

} // end namespace trt 