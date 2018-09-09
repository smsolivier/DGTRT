Ne = 50
Nangles = 8
xb = 1 
fe_order = 2

Tend = 1
dt = 1e-3
Tinit = (1e-2)^(1/4) 
n_outer = 50
n_inner = 10
t_outer = 1e-6 
t_inner = 1e-10

function Sigma_t(x, T) 
	return 1/T^3
end 

function Sigma_s(x, T)
	return 0
end 

function Source(x, mu) 
	return 0
end 

function Inflow(x, mu) 
	if (mu > 0) then 
		return 1
	else 
		return 0
	end
end