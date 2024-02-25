# Makefile
#
# Purpose: Parameters test. Obtain RNIP and BETA correct values.
#
# Site: https://www.geofisicando.com
# 
# Programer: Rodolfo A. C. Neves (Dirack) 25/02/2024
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

all: generate_data view test clean

generate_data: SConstruct
	@scons; \
		<crsParameters1.rsf sfwindow n3=1 f3=1 | sfdisfil col=1 number=n format="%f |" > test_rnip_interface1.txt; \
		<crsParameters2.rsf sfwindow n3=1 f3=1 | sfdisfil col=1 number=n format="%f" > test_rnip_interface2.txt; \
		<crsParameters1.rsf sfwindow n3=1 f3=2 | sfdisfil col=1 number=n format="%f |" > test_beta_interface1.txt; \
		<crsParameters2.rsf sfwindow n3=1 f3=2 | sfdisfil col=1 number=n format="%f" > test_beta_interface2.txt;

view:	header_result view_rnip view_beta

header_result:
	@echo
	@echo "Result of this test - Start report"
	@echo

view_rnip: test_rnip_interface1.txt test_rnip_interface2.txt
	@echo "--- RNIPs for each interface ---"
	@echo "  First  | Second"
	@paste $^ -d" | "
	@echo "--- Correct value ---"
	@echo "1.000000 | 1.950000"
	@echo

view_beta: test_beta_interface1.txt test_beta_interface2.txt
	@echo "--- BETAs for each interface ---"
	@echo "  First  | Second"
	@paste $^ -d" | "
	@echo "--- Correct value ---"
	@echo "0.000000 | 0.000000"
	@echo

test:	./Test_parameter_values.sh
	./$<
	@echo

clean:
	scons -c; rm test_rnip_interface*.txt test_beta_interface*.txt
