import subprocess

oc0=0.
dc0=0.033
nc0=31

otemp0=0.
dtemp0=0.1
ntemp0=31

om0=5
dm0=0.1
nm0=1
ot0=1.1
dt0=0.1
nt0=1
v0=1.5

lc0=[]
ltemp0=[]
lrn=[]
lrnip=[]
lbeta=[]
lsemb=[]

for temp0i in range(ntemp0):


    temp0 = otemp0+dtemp0*temp0i
    for c0i in range(nc0):

        c0 = oc0+dc0*c0i

        fileinput = 'crsParameters_c0_%d_temp0_%d.rsf' % (c0i,temp0i)
        result = subprocess.check_output(['sfdisfil <'+fileinput+' number=n format="%f "'], shell=True)
        lista = result.split()
        lc0.append(float(lista[0]))
        ltemp0.append(float(lista[1]))
        lsemb.append(float(lista[3]))
        print(float(lista[3]))

print("n1=%d d1=%g o1=%g label1=c0 n2=%d d2=%g o2=%g label2=temp0 data_format=ascii_float in=surface.asc" % (nc0,dc0,oc0,ntemp0,dtemp0,otemp0))
