#!/bin/bash
#
# Test_issue_32.sh (Shell Script)
# 
# Purpose: Test bug related on issue 32.
# 
# Site: https://www.geofisicando.com
# 
# Programmer: Rodolfo A C Neves (Dirack) 05/02/2024
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

TESTSTR="Test_issue_32.sh: Random number generation"
v1=$(./call_generateRandomNumber.x)
v2=$(./call_generateRandomNumber.x)

if [ "$v1" == "$v2" ]; then
	echo -e "${TESTSTR}:\033[32mPASS\033[m"
else
	echo -e "${TESTSTR}:\033[31mFAIL\033[m: Function generateRandomNumber generates different values each system call!"
	echo "v1=$v1 and v2=$v2"
	exit 1
fi

TESTSTR="Test_issue_32.sh: Random number generation"
v1=$(./call_generateRandomNumberPrecise.x)
v2=$(./call_generateRandomNumberPrecise.x)

if [ "$v1" == "$v2" ]; then
	echo -e "${TESTSTR}:\033[31mFAIL\033[m: Function generateRandomNumber generates the same value each system call!"
	echo "v1=$v1 and v2=$v2"
	exit 1
fi

echo -e "${TESTSTR}:\033[32mPASS\033[m"
