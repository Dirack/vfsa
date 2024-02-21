# Debug directory for vfsa debug sessions with GDB

- GDB debug session: Run 'make' or 'make vfsa.x' to generate the executable vfsa.x
to be used in debugging with GNU Debugger (GDB). The 'gdb\_scripts/gdb\_script'
file can be used to load all arguments needed to run the program in GDB. Use
'source gdb\_scripts/gdb\_script' in GDB shell.

- GDB test: Run 'make gdbtest' to run tests in GDB shell.
