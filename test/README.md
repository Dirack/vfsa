# Tests directory

This is the tests directory of the vfsa package. New tests should be added here.
To run default tests listed in the TESTS variable of the Makefile presented in this directory, use the following command:

```
make
```

You can also run a specific directory test using:

```
make <directory>.test
```

The Makefile is configured to run another Makefile in the specific directory that is responsible for running the tests
available in the directory. Please follow this pattern when adding new tests.