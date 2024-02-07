#!/bin/bash

HEADER="3.0	sfmath	test/libraries/test_data_cube:	rodolfo@rodolfo-Nitro-AN515-54	Sun Feb  4 17:00:05 2024

	label1="Offset"
	data_format="native_float"
	esize=4
	in="${DATAPATH}test/libraries/test_data_cube/gaussianReflector.rsf@"
	unit1="km"
	x1=0"

echo "$HEADER" > $(dirname $0)/dummyheader.rsf