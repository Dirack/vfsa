import subprocess
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np

oc0=0.
dc0=0.033
nc0=31

ont=0.
dnt=3
nnt=31

om0=5
dm0=0.1
nm0=1
ot0=1.1
dt0=0.1
nt0=1
v0=1.5

lc0=[]
lnt=[]
lrn=[]
lrnip=[]
lbeta=[]
lsemb=[]

for nti in range(nnt):


    nt = ont+dnt*nti
    for c0i in range(nc0):

        c0 = oc0+dc0*c0i

        fileinput = 'crsParameters_c0_%d_nt_%d.rsf' % (c0i,nti)
        result = subprocess.check_output(['sfdisfil <'+fileinput+' number=n format="%f "'], shell=True)
        lista = result.split()
        lc0.append(float(lista[0]))
        lnt.append(float(lista[1]))
        lsemb.append(float(lista[3]))
        #print(str(c0)+' '+str(temp0)+' '+result)
        
#fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
# Creating figure
fig = plt.figure(figsize =(14, 9))
ax = plt.axes(projection ='3d')
# Plot the surface.
print(lsemb)
x=np.arange(oc0,1.023,dc0)
y=np.arange(ont,nnt*dnt+ont,dnt)
z=np.array(lsemb).reshape(nc0,nnt)
surf = plt.contour(x,y,z, cmap=cm.coolwarm,linewidth=0, antialiased=False)
# Plot the surface.
#surf = ax.plot_surface(x, y, z)
# Creating plot
#surf = ax.plot_surface(x, y, z,
#                      edgecolor ='none')

fig.colorbar(surf, ax = ax,
             shrink = 0.5, aspect = 5)

ax.set_title('Surface plot')
plt.show()
