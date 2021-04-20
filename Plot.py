import numpy as np
import matplotlib.pylab as plt

with open('output.txt') as f:
    L = f.readlines()
del L[0]
names,loop,i = [[],True,0]
while loop:
    if not L[i].split('\t')[0] in names:
        names.append(L[i].split('\t')[0])
        i+=1 
    else:
        loop=False
r,time,t = [[],[],0]
for n in np.arange(i):
    r.append([])

for line in L:
    l = line.split('\t')
    index = names.index(l[0])
    r[index].append(float(l[2]))
    if index==0:
        time.append(t)
        t+=1


f,ax=plt.subplots(1,1)
ax.set_ylim([0,np.amax(r)+1])
ax.set_xlim([0,max(time)])
for n in np.arange(i):
    ax.plot(time,r[n],label=names[n])
ax.legend(loc='upper right')
plt.show()
