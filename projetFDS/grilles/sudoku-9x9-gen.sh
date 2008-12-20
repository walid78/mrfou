#!/bin/sh

#
# Uses command-line version of sudoku board game (sudoku-cli)
#

sudoku-cli -g -f compact | grep -v '^%' | \
sed -e 's/\./_/g' -e 's/\(.\)/\1 /g' -e 's/^ *//' -e 's/ *$//' -e 's/9/0/'
