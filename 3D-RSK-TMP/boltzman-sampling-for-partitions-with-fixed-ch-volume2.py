# Import the libraries
import matplotlib.pyplot as plt
import seaborn as sns
import io
import pandas as pd
import numpy as np
import math

def mean_(vals, freq):
  sum = 0.0
  k = 0.0
  for x, y in zip(vals, freq):
    sum += x * y
    k += y
  return sum / k

def mode_(vals, freq):
  res = vals[0]
  k = freq[0]
  for x, y in zip(vals, freq):
    if y > k:
      k = y
      res = x
  return res

def range_(vals, freq):
  l = -1
  r = -1
  for x, y in zip(vals, freq):
    if y > 0:
      if l == -1:
        l = x
      r = x
  return (l, r)

def mid_range(vals, freq):
  l = -1
  r = -1
  for x, y in zip(vals, freq):
    if y > 0:
      if l == -1:
        l = x
      r = x
  return (l + r) / 2



def matrix_sample(q, sz): 
  A = []
  for i in range(sz):
    A.append([])
    for j in range(sz):
      A[i].append([])
      for k in range(sz):
        A[i][j].append(0)
        A[i][j][k] = int(np.random.geometric(1 - math.pow(q, i+j+k+1))) - 1
  return A

def transfer_map(A):
  sz = len(A)
  for i in range(sz - 1, -1, -1):
    for j in range(sz - 1, -1, -1):
      for k in range(sz - 1, -1, -1):
        mx = 0
        if i < sz - 1:
          mx = max(mx, A[i + 1][j][k])
        if j < sz - 1:
          mx = max(mx, A[i][j + 1][k])
        if k < sz - 1:
          mx = max(mx, A[i][j][k + 1])
        A[i][j][k] += mx
  return A

def ch_volume(A):
  sz = len(A)
  vol = 0
  for i in range(sz):
    for j in range(sz):
      for k in range(sz):
        mx = 0
        if i < sz - 1:
          mx = max(mx, A[i + 1][j][k])
        if j < sz - 1:
          mx = max(mx, A[i][j + 1][k])
        if k < sz - 1:
          mx = max(mx, A[i][j][k + 1])
        vol += (i + j + k + 1) * (A[i][j][k] - mx)
  return vol

def volume(A):
  sz = len(A)
  vol = 0
  for i in range(sz):
    for j in range(sz):
      for k in range(sz):
        vol += A[i][j][k]
  return vol

def boltzman_sample(ch_v, q, sz):
  steps = 0
  while True:
    steps += 1
    A = transfer_map(matrix_sample(q, sz))
    if ch_volume(A) == ch_v:
      print('Found in ' + str(steps) + ' steps!')
      return A

import os
import csv 

def collect_data(q, sz, T):
	# creating a folder
	dir_name = f'sampling/Collect_Data-for-q={q}-sz={sz}'
	os.mkdir(dir_name)

	cnt = [[0] * (10001) for x in range(0, sz + 1)]
	small_percentage = 0
	percentage = 0
	for i in range(T):
		A = transfer_map(matrix_sample(q, sz))
		ch_v = ch_volume(A)
		v = volume(A)
		if ch_v <= sz:
			cnt[ch_v][v] += 1

		if i % 100 == 0:
			print(f'sz = {sz}, {100.0 * i / T}% done!')
		if (i + 1) * 10 > (percentage + 1) * T:
			percentage += 1 
			print(f'{percentage * 10}% done!')
			with open(f'{dir_name}/{percentage * 10}%data.csv', 'w') as f:
				writer = csv.writer(f)	
				writer.writerows(cnt)			
	with open(f'{dir_name}/full-data.csv', 'w') as f:
		writer = csv.writer(f)
		writer.writerows(cnt)
#collect_data(0.5, 40, 100000)
#collect_data(0.6, 70, 100000)
collect_data(0.7, 100, 100000)
