all: generate_data generate_plot view

generate_data: SConstruct
	scons

generate_plot: plot_test.py
	python plot_test.py

view: SConscript
	scons -f $< view