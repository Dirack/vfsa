# Makefile
#
# Purpose: Run unit tests that reproduce bugs.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 06/11/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

TESTS=test_issue_32 test_issue_46

all: $(TESTS)

test_issue_%: issue_%
	make -C $<
