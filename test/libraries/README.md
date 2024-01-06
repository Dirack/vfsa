#### TESTS DIRECTORY OF VFSA PROGRAMS - Tests for libraries and functions

Those tests run in the program make. There are several
types of tests that can be done:

- Unit tests: Just run the command 'make' to run all unit tests
in the file 'Test\_vfsacrsnh.c'.

- Optimization tests: Run 'make time' to run the optimization
tests and to show execution time of the program with scons.

- GDB debug: Run 'make vfsa.x' to generate the executable vfsa.x
to be used in debugging with GNU Debugger (GDB). The 'gdb\_scripts/gdb\_script'
file can be used to load all arguments needed to run the program in GDB. Use
'source gdb\_scripts/gdb\_script' in GDB shell.

- GDB test: Run 'make gdbtest' to run tests in GDB shell.
