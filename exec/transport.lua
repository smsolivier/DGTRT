Ne = 100
Nangles = 32
xb = 10
fe_order = 2

niter = 50 

function Sigma_t(x) 
	return math.cos(math.pi*x*2/xb) + 1
end 

function Sigma_s(x)
	return .7*Sigma_t(x)
end 

function Source(x, mu) 
	if (x > 4 and x < 6) then 
		return 1 
	else 
		return 0
	end
end 

function Inflow(x, mu) 
	if (mu > 0) then 
		return 1
	else 
		return 0
	end
end