# Makefile
#
# Purpose: Run parameters test.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 06/11/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Default is to run the test
all:	test

# run parameters test with scons to measure execution time
test:	parameters_test/SConstruct
	@echo "\033[95mRunning parameters test\033[m"
	scons
	@echo ...done

clean:
	scons -c

help:
	@echo "Run 'make' to run parameters test"

.PHONY:	clean help all
