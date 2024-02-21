#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Python
#
# Purpose: Generate plot data for parameters test.
#
# Site: https://www.geofisicando.com
# 
# Programer: Rodolfo A. C. Neves (Dirack) 10/11/2020
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

import subprocess

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
        print(float(lista[3]))

print("n1=%d d1=%g o1=%g label1=c0 n2=%d d2=%g o2=%g label2=Iterations data_format=ascii_float in=surface.asc" % (nc0,dc0,oc0,nnt,dnt,ont))