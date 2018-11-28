Ne = 100
Nangles = 8
xb = 1
fe_order = 1

Tend = 1
dt = 1e-5
Tinit = 2*(1e-5)^(1/4) 
n_outer = 100
n_inner = 10
t_outer = 1e-12
t_inner = 1e-12
freq = 1
a = 2

function Sigma_t(x, T) 
	return 1/T^3 
end 

function Sigma_s(x, T)
	return 0
end 

alpha = 1 
beta = 1
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

function cv(x, T)
	return 1
end 