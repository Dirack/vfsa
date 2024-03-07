# Makefile
#
# Purpose: Run tests for bug related on issue 32.
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

DEP = ../../../vfsacrsnh_lib.c

# Default is to run the test
all:	call_generateRandomNumber.x call_generateRandomNumberPrecise.x
	./Test_bug_issue_32.sh

%.x:	%.c
ifdef CENTOS
	@gcc -I$$RSFSRC/include -I.. -I/usr/include/openblas -L$$RSFSRC/lib $< $(DEP) -o $@ -lm -lrsf -lopenblas -g
else
	@gcc -I$$RSFSRC/include -I.. -L$$RSFSRC/lib $< $(DEP) -o $@ -lm -lrsf
endif

clean:
	rm *.x
help:
	@echo "Compilation of the tests\nRun 'make' to unit test"

.PHONY:	clean help all
