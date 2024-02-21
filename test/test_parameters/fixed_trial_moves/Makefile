# Makefile
#
# Purpose: Parameters test. Fixed number of iterations value.
#
# Site: https://www.geofisicando.com
# 
# Programer: Rodolfo A. C. Neves (Dirack) 10/11/2020
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

all: generate_data generate_plot view

generate_data: SConstruct
	scons

generate_plot: plot_test.py
	python plot_test.py > surface.asc

view: SConscript
	scons -f $< view
