# Generate a convergence graph for multi thread execution

This test generate a convergence graph for multi thread execution with vfsa. This multi thread execution is controled by the repeat parameter.
The value of the repeat parameter is the number of threads used in vfsa optimization

Run this test with scons (pass the number of threads to be used with the ngraphs parameter):

```
scons view ngraphs=5
```
