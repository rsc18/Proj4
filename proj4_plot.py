import matplotlib.pyplot as plt
import math
import numpy as np
from sklearn.cluster import MeanShift, estimate_bandwidth

ack=[]

data=[]
act_data=[]

with open('/home/tangent/Downloads/proj4_MAC_testdata1','r') as handle:
    for line in handle:
        currentdata=line[:-1]
        data.append(currentdata)
xx=[]
yy=[]
zz=[]
ww=[]
for d in data:
    a=[]
    a=d.split(" ")
    m=float(a[0])
    n=float(a[1])
    act_data.append(math.sqrt(m*m+n*n));
    yy.append(0.35)
    xx.append(0.15)
    zz.append(0.005)
    ww.append(0.02)
    
#for d in data:



plt.plot(act_data)
#plt.plot(ack)
plt.plot(yy)
plt.plot(xx)
plt.plot(ww)
plt.plot(zz)