#!/usr/bin/env bash

make gen
make minkowski
make slow

chmod 777 gen
chmod 777 minkowski
chmod 777 slow

for i in {1..1000000}
do
	echo $i

	./gen $i > input.txt
	./minkowski > output1.txt
	./slow > output2.txt

	d=$(diff output1.txt output2.txt)

	if [[ $d != "" ]]
	then
		echo --- has test ---
		cat input.txt
		echo --- solution answer ---
		cat output1.txt
		echo --- slow ---
		cat output2.txt
		break
	fi
done
