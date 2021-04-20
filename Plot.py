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
r,time,energy = [[],[],[]]
for n in np.arange(i):
    r.append([])

energy_i = float(L[0].split('\t')[5])
for line in L:
    l = line.split('\t')
    index = names.index(l[0])
    r[index].append(float(l[2]))
    if index==0:
        time.append(float(l[-1]))
        if l[5]=='0':
            energy.append(np.nan)
        else:
            energy.append(float(l[5]))


f,ax=plt.subplots(2,1)
ax[0].set_ylim([0,np.amax(r)+1])
ax[0].set_xlim([0,max(time)])
ax[1].set_ylim([0,2])
ax[1].set_xlim([0,max(time)])
for n in np.arange(i):
    ax[0].plot(time,r[n],label=names[n])
ax[0].legend(loc='upper right')
ax[1].plot(time,np.array(energy)/energy_i,c='k')
plt.show()
