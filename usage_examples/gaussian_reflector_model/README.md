# Usage examples of sfvfsacrsnh and sfnhcrssurf

In this usage example we use a gaussian reflector model as input and kirchhoff modeling to obtain the
seismic data cube (Seismic data organized in CMP x Offset x Time coordinates) from it.

After that we use _sfvfsacrsnh_ to fit the non-hyperbolic CRS traveltime approximation in the reflection traveltime surface
exatracted from the data cube. Finally, we plot these surfaces and approximation error side by side.

### How to run it?

* Run 'scons view' in this directory (it may take some time):

```sh
~$ scons view
```

#### Expected outcomes

 After the program _scons_ do all the steps in the SConstruct file, you will see the generated surfaces as follow:
 
 ![surfaces](https://github.com/Dirack/vfsa/blob/master/images/surfaces.png)
 
 And the CRS parameters will appear on your terminal screen. They are saved in the _crsParameters.rsf_ file.
 You can obtain them running:
 
 ```sh
 ~$ sfdisfil <crsParameters.rsf
0:          3.23       0.9706    -0.003872       0.7791          0.5
5:            10          1.1            5
```

The first 3 numbers are RN, RNIP and BETA. The fourth one is the semblance (it may change from one running to another).
The fifth and sixth are C0 and Temp0, arbitrary parameters used in vfsa that may change from problem to problem. Finally
t0 (Normal ray traveltime) and m0 (Central CMP of the approximation) are the last ones.
