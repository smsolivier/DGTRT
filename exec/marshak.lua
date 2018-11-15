Ne = 100
Nangles = 4
xb = 1
fe_order = 1

Tend = 10
dt = 1e-2
Tinit = (1e-2)^(1/4) 
n_outer = 50
n_inner = 10
t_outer = 1e-6 
t_inner = 1e-10
freq = 5
a = 1

function Sigma_t(x, T) 
	return 1/T^3
end 

function Sigma_s(x, T)
	return 0
end 

function Source(x, mu) 
	return 1
end 

function Inflow(x, mu) 
	if (mu > 0) then 
		return 0
	else 
		return 0
	end
end