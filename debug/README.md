# Debug directory for vfsa debug sessions with GDB

This directory is a framework for debugging sessions with GNU debugger (GDB) and
VFSA programs. The programs versions are compiled for gdb and arguments are loaded 
using gdb scripts. In the directory 'test\_data\_cube', dummy data is build to be
offered as input in debugging sessions.

Bellow, the debugging options:

- GDB debug session: Run 'make' or 'make vfsa.x' or 'make nhcrssurf.x'
to generate the executable vfsa.x or 'nhcrssurf.x'
to be used in debugging with GNU Debugger (GDB). The 'gdb\_scripts/gdb\_script'
file can be used to load all arguments needed to run the program in GDB. Use
'source gdb\_scripts/gdb\_script' in GDB shell.

- GDB test: Run 'make gdbtest' to run 'vfsa.x' tests in GDB shell.

## Usage examples

To run 'vfsa.x' with a gdb script called 'gdb\_script' in 'gdb\_scripts' directory use:

```
gdb --command=gdb_scripts/gdb_script ./vfsa.x
```

To run 'nhcrssurf.x' with a gdb script called 'gdb\_script\_nhcrssurf' in 'gdb\_scripts' directory use:

```
gdb --command=gdb_scripts/gdb_script_nhcrssurf ./nhcrssurf.x
```
