import numpy as np
import matplotlib.pylab as plt

with open('output.txt') as f:
    L = f.readlines()
del L[0]
names,mass,loop,i = [[],[],True,0]
while loop:
    if not L[i].split('\t')[0] in names:
        names.append(L[i].split('\t')[0])
        mass.append(float(L[i].split('\t')[1]))
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

if i == 1:
    colors = ['k']
else:
    cm = plt.get_cmap('viridis')
    colors = [cm(1.4*float(n)/float(i)) for n in np.arange(i)]
    

f,ax=plt.subplots(2,1,gridspec_kw={'height_ratios':[3,1]},figsize=(8,6))
plt.subplots_adjust(hspace=0)
ax[0].tick_params(axis='x',length=0,labelsize=0)
ax[0].set_ylim([0,np.amax(r)+1])
ax[0].set_xlim([0,max(time)])
ax[1].set_ylim([0,2])
ax[1].set_xlim([0,max(time)])
ax[1].set_xlabel('Time [yrs]',fontsize=15)
ax[0].set_ylabel('Radius [AU]',fontsize=15)
ax[1].set_ylabel(r'E/E$_{0}$ [N]',fontsize=15)
for n in np.arange(i):
    ax[0].plot(time,r[n],color=colors[n],label=names[n])
ax[0].legend(loc='upper right',prop={'size':12})
ax[1].plot(time,np.array(energy)/energy_i,c='k')
plt.show()
