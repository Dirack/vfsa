# Makefile
#
# Purpose: Run tests.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 06/11/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

TESTS=libraries optimization

# Default is to run all tests
all:	$(addsuffix .test, $(TESTS))

%.test:	%
	@echo "\033[95mRunning tests in $< directory...\033[m"
	make -C $<

clean:
	scons -C test_data_cube -c

help:
	@echo "Run 'make' to run all the tests available in this directory"
	@echo "Run 'make <directory>.test' to run a test of a specific directory"

.PHONY:	clean help all
