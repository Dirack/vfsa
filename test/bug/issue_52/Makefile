# Makefile
#
# Purpose: Tests for bug related in issue 52.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 27/02/2024
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Uncomment the line below to run on a CENTOS system. Or call make as 'make CENTOS=1'
#CENTOS=1 

DEP = ../../../vfsacrsnh_lib.c
GDBDEP = ../../../Mvfsacrsnh.c $(DEP)
UNITY = ../../Unity/unity.c

# Default is to run the test
all:	Test_bug_issue_52.x
	@./Test_bug_issue_52.x \
		; rm Test_bug_issue_52.x

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
