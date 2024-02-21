# Makefile
#
# Purpose: Prepare a debug version of the program.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 06/11/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Uncomment the line below to run on a CENTOS system. Or call make as 'make CENTOS=1'
#CENTOS=1 

DEP = ../vfsacrsnh_lib.c
GDBDEP = ../Mvfsacrsnh.c $(DEP)
UNITY = Unity/unity.c

# Default is to run the test
all:	vfsa.x generate_data_cube

%.x:	%.c
ifdef CENTOS
	@gcc -I$$RSFSRC/include -I/usr/include/openblas -L$$RSFSRC/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf -lopenblas -g
else
	@gcc -I$$RSFSRC/include -L$$RSFSRC/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf
endif

# Generate a version of the program for debugging with GDB
vfsa.x:	generate_data_cube $(GDBDEP)
	@echo "\033[95mGenerate a version of the program for debugging with GDB...\033[m"
ifdef CENTOS
	gcc -I$$RSFSRC/include -I/usr/include/openblas -L$$RSFSRC/lib $(GDBDEP) -o $@ -lm -lrsf -lopenblas -g -fopenmp
else
	gcc -g -I$$RSFSRC/include -L$$RSFSRC/lib $(GDBDEP) -o $@ -lrsf -lm -fopenmp
endif
	@echo "...done"

# Generate input data for debug session
generate_data_cube:	test_data_cube/SConstruct
	@echo "\033[95mGenerate a data cube for tests\033[m"
	cd test_data_cube && scons -s -Q
	@echo "...done"

gdbtest:	vfsa.x
	@echo "\033[95mRunning tests in a GDB shell\033[m"
	gdb -q --command=gdb_scripts/gdb_test $<

clean:
	scons -C test_data_cube -c; rm *.x

help:
	@echo "Run 'make' or 'make vfsa.x' to prepare a program version for GDB"
	@echo "Run 'make gdbtest' run test in GDB shell"

.PHONY:	clean help all
