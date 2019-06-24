#!/bin/bash
#
# Installs gef and sets up GDB with a basic config for CSSE132.
#
# For more info on gef:
# https://gef.readthedocs.io/en/latest/
# https://github.com/hugsy/gef/
#
# Created Spring 2018
# Sid Stamm <stammsl@rose-hulman.edu>
#

echo "---------------------------------------"
echo "RHIT CSSE132 Raspberry Pi 3 GDB setup"
echo "---------------------------------------"
echo ""

echo "Downloading and installing gef... "
echo ""

wget -q -O- https://github.com/hugsy/gef/raw/master/scripts/gef.sh | sh
wget -O ~/.gef.rc https://www.rose-hulman.edu/class/csse/csse132/install.gef.rc

echo ""
echo "You are ready to run gdb!"
echo "For help once you're in gdb, just type \"help\""
echo "For help with gef-specific things, type \"gef help\"."
echo ""
echo "To debug a program, type: "
echo "        gdb ./<program>"
echo "on the command line."
echo "(be sure to replace <program> with the name of your program.)"
echo ""

