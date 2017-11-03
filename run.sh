#!/bin/bash

rm *.jpg

./$1 > dots.txt
gnuplot historical.gnu
gnuplot phase_portrait.gnu 
