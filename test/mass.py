#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

from scipy.integrate import fixed_quad 

import GenBasis as gb 

p = 1
a = 0
b = 2
B, dB = gb.genBasis(p, a, b) 

NB = len(B) 
A = np.zeros((NB, NB))

for i in range(NB):
	for j in range(NB):
		func = lambda xi: dB[i](xi) * B[j](xi)
		A[i,j] = fixed_quad(func, a, b)[0] 

print(A) 