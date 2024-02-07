# Makefile
#
# Purpose: Run tests for libraries and functions.
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

DEP = ../../vfsacrsnh_lib.c
GDBDEP = ../../Mvfsacrsnh.c $(DEP)
UNITY = ../Unity/unity.c

# Default is to run the test
all:	generate_data_cube generate_simple_cube Test_vfsacrsnh_lib.x
	@./Test_vfsacrsnh_lib.x dummyheader=test_data_cube/dummyheader.rsf \
		rnmax=test_data_cube/rnmax.rsf \
		rnmin=test_data_cube/rnmin.rsf \
		rnipmax=test_data_cube/rnipmax.rsf \
		rnipmin=test_data_cube/rnipmin.rsf \
		betamax=test_data_cube/betamax.rsf \
		betamin=test_data_cube/betamin.rsf \
		; rm Test_vfsacrsnh_lib.x

%.x:	%.c
ifdef CENTOS
	@gcc -I$$RSFSRC/include -I.. -I/usr/include/openblas -L$$RSFSRC/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf -lopenblas -g
else
	@gcc -I$$RSFSRC/include -I.. -L$$RSFSRC/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf
endif

# Generate a version of the program for debugging with GDB
vfsa.x:	generate_data_cube $(GDBDEP)
ifdef CENTOS
	gcc -I$$RSFSRC/include -I/usr/include/openblas -L$$RSFSRC/lib $(GDBDEP) -o $@ -lm -lrsf -lopenblas -g -fopenmp
else
	gcc -g -I$$RSFSRC/include -L$$RSFSRC/lib $(GDBDEP) -o $@ -lrsf -lm -fopenmp
endif

# Generate a data cube for semblance and nonHyperbolicCRSApp functions tests
generate_data_cube:	test_data_cube/SConstruct test_data_cube/generate_dummy_header.sh
	@echo "\033[95mGenerate a data cube for semblance and nonHyperbolicCRSApp functions tests\033[m"
	@cd test_data_cube && scons -s -Q && ./generate_dummy_header.sh
	@echo ...done

# Generate a data cube for semblance and nonHyperbolicCRSApp functions tests
generate_simple_cube:	test_data_cube/SConstruct
	@echo "\033[95mGenerate a data cube for semblance and nonHyperbolicCRSApp functions tests\033[m"
	@cd test_data_cube && scons -s -Q simpleDataCube.rsf
	@echo ...done

clean:
	scons -C test_data_cube -c

help:
	@echo "Compilation of the tests\nRun 'make' to unit test"

.PHONY:	clean help all
