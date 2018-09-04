#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

class Rule: 
	def __init__(self, p, x, w):
		self.p = p
		self.x = x 
		self.w = w 

f = open('weight.txt', 'r')

text = [] 
c = 0
for line in f: 
	spl = line.split('\t')
	if (len(spl)==3):
		text.append(line) 
		c += 1

	else:
		text[c-1] += line 
f.close()

rules = [] 
for i in range(len(text)):
	string = text[i] 
	spl = string.split()
	p = int(spl[0]) 
	x = [] 
	w = [] 
	for j in range(1, len(spl), 2):
		if (spl[j][0].isdigit()):
			x.append(float(spl[j]))
			w.append(float(spl[j+1]))
		else:
			val = float(spl[j][1:])
			x.append(val)
			x.append(-val)
			val = float(spl[j+1])
			w.append(val)
			w.append(val) 

	rules.append(Rule(p, x, w))

f = open('rules.txt', 'w')
for i in range(len(rules)):
	f.write('case ' + str(rules[i].p) + ': {\n')
	f.write('\t_x = {\n\t\t')
	for j in range(len(rules[i].x)):
		f.write(str(rules[i].x[j]) + ', ')
	f.write('\n\t};\n')
	f.write('\t_w = {\n\t\t')
	for j in range(len(rules[i].w)):
		f.write(str(rules[i].w[j]) + ', ')
	f.write('\n\t};')
	f.write('\n\tbreak; \n}\n')


f.close()