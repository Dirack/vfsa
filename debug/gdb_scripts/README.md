# GDB scripts for debug

This is a repository of several GNU Debugger (GDB) Scripts for debug sessions using GDB.
You can load those scripts in GDB console or use it as a template to load parameters in GDB.
Use the command inside gdb shell to load args for 'Mvfsacrsnh.c':

```
source gdb_script
```

Or you could load the GDB script when calling gdb to starting a new debug session:

```
gdb --command=gdb_script vfsa.x
```
