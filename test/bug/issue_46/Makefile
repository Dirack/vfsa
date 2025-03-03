# Makefile
#
# Purpose: Run tests related with issue 46.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 21/02/2024
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Uncomment the line below to run on a CENTOS system. Or call make as 'make CENTOS=1'
#CENTOS=1 

DEP = ../../../nhcrssurf_lib.c
GDBDEP = ../../../Mnhcrssurf.c $(DEP)
UNITY = ../../Unity/unity.c

# Default is to run the test
all:	Test_nhcrssurf_lib.x
	@./Test_nhcrssurf_lib.x par=dummyheader.rsf; rm Test_nhcrssurf_lib.x

%.x:	%.c
ifdef CENTOS
	@gcc -I$$RSFROOT/include -I../.. -I/usr/include/openblas -L$$RSFROOT/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf -lopenblas -g
else
	@gcc -I$$RSFROOT/include -I../.. -L$$RSFROOT/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf
endif

clean:
	rm *.x

help:
	@echo "Compilation of the tests\nRun 'make' to unit test"

.PHONY:	clean help all
