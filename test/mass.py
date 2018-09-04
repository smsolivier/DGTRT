#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

from scipy.integrate import fixed_quad 

import GenBasis as gb 

B, dB = gb.genBasis(3) 

A = np.zeros((3,3))
A[0,0] = 1
A[1,1] = 5
A[2,2] = 3
A[0,1] = -1 
A[2,1] = .2 

print(A) 

b = np.ones(3) 

print(np.linalg.solve(A, b))