#!/bin/bash

for folder in `ls ../results`;
do
	echo "EMPTY" > ../results/$folder/a.csv
	echo "EMPTY" > ../results/$folder/s.csv
	echo "EMPTY" > ../results/$folder/*.txt
done

rm ../results/prd/*.csv ../results/qs/*.csv ../results/cr/*.csv
rm ../results/combined/\*.txt ../results/in_action/\*.txt ../results/p/\*.txt ../results/t/\*.txt ../results/qrs/\*.txt
