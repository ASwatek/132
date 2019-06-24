#!/bin/bash

total=0
t=`./unix1.sh`
if [ "$t" == "this." ]; then
	echo Unix1 pass 2/2
	total=$(($total + 2))
else
	echo Unix1 fail 0/2
fi

t=`./unix2.sh`
if [ "${t}" == "2" ]; then
	echo Unix2 pass 2/2
	total=$(($total + 3))
else
	echo Unix2 fail 0/3
fi

echo Total $total / 5
