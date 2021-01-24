# Makefile
#
# Purpose: Run unit tests, optimization tests and prepare a
# debug version of the program.
# 
# Site: https://dirack.github.io
# 
# Programer: Rodolfo A C Neves (Dirack) 06/11/2020
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
all:	generate_data_cube Test_vfsacrsnh_lib.x

%.x:	%.c
ifdef CENTOS
	@gcc -I$$RSFSRC/include -I/usr/include/openblas -L$$RSFSRC/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf -lopenblas -g
	@./$@
	@rm $@
else
	@gcc -I$$RSFSRC/include -L$$RSFSRC/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf 
	@./$@
	@rm $@
endif

# Generate a version of the program for debugging with GDB
vfsa.x:	generate_data_cube $(GDBDEP)
ifdef CENTOS
	gcc -I$$RSFSRC/include -I/usr/include/openblas -L$$RSFSRC/lib $(GDBDEP) -o $@ -lm -lrsf -lopenblas -g
else
	gcc -g -I$$RSFSRC/include -L$$RSFSRC/lib $(GDBDEP) -o $@ -lrsf -lm
endif

# run optimization test with scons to measure execution time
time:	optimization_test/SConstruct
	cd optimization_test && scons --clean && scons dataCube.rsf && scons --debug=time

# Generate a data cube for semblance and nonHyperbolicCRSApp functions tests
generate_data_cube:	test_data_cube/SConstruct
	@cd test_data_cube && scons -s -Q

clean:
	rm *.x

help:
	@echo "Compilation of the tests\nRun 'make' to unit test"
	@echo "Run 'make vfsa.x' to prepare a program version for GDB"
	@echo "Run 'make time' to run optimization tests"

.PHONY:	clean help
