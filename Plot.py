import matplotlib.pylab as plt

with open('output.txt') as f:
    L = f.readlines()
del L[0]
r,time,t = [[],[],0]
for line in L:
    r.append(float(line.split('\t')[2]))
    time.append(t)
    t+=1

f,ax=plt.subplots(1,1)
ax.plot(time,r,c='k')
plt.show()
