# Usage examples of sfvfsacrsnh for a set of (t0,m0) pairs

In this usage example we use the same gaussian reflector model as input and kirchhoff modeling. We use _sfvfsacrsnh_ to obtain the CRS parameters for a set of (t0,m0) pairs.

## How to run it?

* Run 'scons' in this directory (it may take some time):

```sh
~$ scons
```

## Expected outcomes

Scons will generate a parameters cube in 'crsParameters.rsf' file. The optimized parameters
are organized in the current order: RN, RNIP, BETA, Semblance.
The RN, RNIP and BETA are the zero offset CRS parameters. Semblance is the semblance measure
between the non-hyperbolic CRS traveltime approximation and the seismic data cube in a CMP x
offset window around Central CMP m0.

The parameters cube in 'crsParameters.rsf' file is organized as follows:

```sh
~$ sfin crsParameters.rsf
crsParameters.rsf:
    in="/home/rodolfo/rsfdata/vfsa/examples/fullParametersOptimization/crsParameters.rsf@"
    esize=4 type=float form=native 
    n1=2           d1=0.1         o1=1.1        label1="t0" unit1="s" 
    n2=3           d2=1           o2=3          label2="m0" unit2="km" 
    n3=4           d3=1           o3=0          label3="parameters" unit3="RN, RNIP, BETA, Semblance"
```

For each (t0,m0) pair (n1 coordinate, n2 coordinate) we get 4 parameters (n3 coordinate) as described above.

Use the following commands to dump parameters values from parameters cube (values should change from one iteration to another).

- Get RN values:

```
<crsParameters.rsf sfwindow n3=1 f3=0 | sfdisfil col=1
```

- Get RNIP values:

```
<crsParameters.rsf sfwindow n3=1 f3=1 | sfdisfil col=1
```
- Get BETA values:

```
<crsParameters.rsf sfwindow n3=1 f3=2 | sfdisfil col=1
```
- Get Semblance values:

```
<crsParameters.rsf sfwindow n3=1 f3=3 | sfdisfil col=1
```

