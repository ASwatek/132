#!/bin/bash

# Print the number of lines that contain 'but' (either upper or lowercase) in
# sample.txt (When run, this script should print 2)
#
# To run this command, type ./unix2.sh on the command line
#
# TODO: Write your command beneath this line.

grep 'but' sample.txt -c -i
