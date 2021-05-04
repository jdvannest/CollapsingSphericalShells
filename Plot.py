import argparse,sys,os
import numpy as np
import matplotlib.pylab as plt

parser = argparse.ArgumentParser(description="Generates plots from output .txt files", 
                                usage="Plot.py -f output_filename")
parser.add_argument("-f", "--file", help="Path to output .txt file. Including '.txt'"+
                                        "is optional",required=True)
parser.add_argument("-g", "--gif", help="Create a .gif of the collapsing shells "+
                                        "(optional)",action="store_true")                      
args = parser.parse_args()

fname = args.file if args.file[-4:]=='.txt' else args.file+'.txt'

try:
    with open(fname) as f:
        L = f.readlines()
except:
    print("Data file not found...")
    sys.exit()
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
    
imagename = fname.split('/')[-1].split('.')[0] if '/' in fname else fname.split('.')[0]
if(i<6):
    for n in np.arange(i):
        try:
            print(f'Shell {names[n]} Collapsed in {time[np.where(np.array(r[n])<1e-5)[0][0]]} years')
        except:
            print(f'Shell {names[n]} Failed to Collapse...')
else:
    try:
        coll_times=[]
        for n in np.arange(i):
            coll_times.append(time[np.where(np.array(r[n])<1e-5)[0][0]])
        print(f'Full Collapse in {np.max(coll_times)} years')
    except:
        print('System Failed to Collapse...')

#Create plot of Radii vs time and Energy
f,ax=plt.subplots(2,1,gridspec_kw={'height_ratios':[3,1]},figsize=(10,8))
plt.subplots_adjust(hspace=0)
ax[0].tick_params(axis='x',length=0,labelsize=0)
ax[0].set_ylim([0,1.1*np.amax(r)])
ax[0].set_xlim([0,max(time)])
#ax[1].set_ylim([0,2])
ax[1].set_xlim([0,max(time)])
ax[1].set_xlabel('Time [yrs]',fontsize=15)
ax[0].set_ylabel('Radius [AU]',fontsize=15)
ax[1].set_ylabel(r'E/E$_{0}$ [N]',fontsize=15)
for n in np.arange(i):
    ax[0].plot(time,r[n],color=colors[n],label=names[n])
if i<6: ax[0].legend(loc='upper right',prop={'size':12})
ax[1].plot(time,np.array(energy)/energy_i,c='k')
f.savefig(f'Plots/{imagename}.png',bbox_inches='tight',pad_inches=.1)
print(f"Images saved to Plots/{imagename}.png")

if args.gif:
    maxline=5 if i<6 else 2
    def myprint(string,clear=False):
        if clear:
            sys.stdout.write("\033[F")
            sys.stdout.write("\033[K") 
        print(string)
    print("Compiling gif...")
    #Create .gif of the shells
    os.system('mkdir tmp')
    t = 0
    if len(time)<200:
        jump=1
    else:
        jump=int(len(time)/200)
    while(t<len(time)):
        f,ax=plt.subplots(1,1,figsize=(5,5))
        ax.set_xlim([-1.1*np.amax(r),1.1*np.amax(r)])
        ax.set_ylim([-1.1*np.amax(r),1.1*np.amax(r)])
        for n in np.arange(i):
            ax.add_patch(plt.Circle((0,0),r[n][t],facecolor='None',edgecolor=colors[n],
                        linewidth=(mass[n]/max(mass)*maxline),label=names[n]))
        if i<6: ax.legend(loc='upper right',prop={'size':12})
        f.savefig(f'tmp/{imagename}.{"%010d"%(t,)}.png',bbox_inches='tight',pad_inches=.1)
        plt.close()
        t+=jump

    #Compile images into a gif
    import imageio
    imagenames = os.listdir('tmp/')
    imagenames = np.sort(np.array(imagenames))
    images = []
    for name in imagenames:
        images.append(imageio.imread('tmp/'+str(name)))
    imageio.mimsave(f'Plots/{imagename}.gif', images, duration=.03)
    os.system('rm -f tmp/*')
    os.system('rmdir tmp/')
    myprint(f"Gif saved to Plots/{imagename}.gif",clear=True)