Ne = 10
Nangles = 32
fe_order = 5
xb = 8 

niter = 100

function Sigma_t(x) 
	return 1 
end 

function Sigma_s(x)
	return 0.8 
end 

function Source(x, mu) 
	if (x < 4) then 
		return 1/2
	else 
		return 0
	end
end 

function Inflow(x, mu) 
	return 0 
end