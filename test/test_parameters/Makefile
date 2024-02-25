# Makefile
#
# Purpose: Run default parameters tests.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 25/02/2024
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

TESTS=rnip_beta_plane_interface

# Default is to run the test
all:	$(addsuffix .test,$(TESTS))

%.test:	%
	make -C $<

help:
	@echo "Run 'make' to run default parameres tests"
