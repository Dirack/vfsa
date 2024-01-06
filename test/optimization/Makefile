# Makefile
#
# Purpose: Run optimization tests.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 06/11/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Default is to run the test
all:	time

# run optimization test with scons to measure execution time
time:	optimization_test/SConstruct
	@echo "\033[95mRunning optimization tests\033[m"
	cd optimization_test && scons --clean && scons dataCube.rsf && scons --debug=time
	@echo ...done

clean:
	scons -C optimization_test -c

help:
	@echo "Run 'make' to run optimization tests"

.PHONY:	clean help all
