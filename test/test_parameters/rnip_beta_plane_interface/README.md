# Test obtain correct RNIP and BETA parameters for a plane interface velocity model

This test is used to assure that vfsa is obtaining correct values for RNIP and BETA parameters.
The parameters values are calculated for a simple plane interfaces model using Hubral's transmission law.
The paramters values should be as follows:

- For the first interface RNIP should be close to 1
- For the second interface RNIP should be close to 1.95
- For both interfaces BETA should be close to 0

Run this test with make:

```
make
```
