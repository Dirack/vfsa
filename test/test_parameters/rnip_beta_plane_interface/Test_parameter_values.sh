#!/bin/bash
#
# Test_parameter_values.sh (Shell Script)
#
# Purpose: Calculate the average of parameters values and test if it is close to the correct values
#
# Site: https://www.geofisicando.com
#
# Programmer: Rodolfo A C Neves (Dirack) 25/02/2024
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.


TESTSTR="Test_paramter_values.sh: Get correct RNIP and BETA values"

check_value(){

	file="$1"
	expected="$2"
	delta="$3"
	average="0"
	nvalues="0"

	while read v
	do
		fv=$(echo "$v" | cut -d" " -f1) 
		average=$(echo "$fv+$average" | bc -l)
		nvalues=$(echo "$nvalues+1" | bc -l)
	done < "$file"

	average=$(echo "$average/$nvalues" | bc -l)

	min=$(echo "$expected-$delta" | bc -l)
	max=$(echo "$expected+$delta" | bc -l)
	res=$(echo "$average < $min || $average > $max" | bc -l)

	if [ "$res" -eq "1" ]
	then
		echo -e "${TESTSTR}:\033[31mFAIL\033[m: Average of values for parameter is far from expected: Average=$average Expected=$min<$expected<$max\033[m"
		echo -e "${TESTSTR}:\033[31mFAILED while checking parameters from file $file\033[m"
		exit 1
	fi
}

check_value test_rnip_interface1.txt "1.0" "0.1"
check_value test_rnip_interface2.txt "1.95" "0.1"
check_value test_beta_interface1.txt "0.00" "0.1"
check_value test_beta_interface2.txt "0.00" "0.1"

echo -e "${TESTSTR}:\033[32mPASS\033[m"
