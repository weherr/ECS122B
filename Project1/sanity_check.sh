#!/bin/bash


if [ "$1" != "" ] && [ "$2" != "" ]; then
    # if the first & second cmd line arg exist, print
g++  quicksort_verbose.cpp -o quicksort_verbose.out

g++  mergesort_verbose.cpp -o mergesort_verbose.out


start=1
files=1
fails=0
zero=0

for (( d=$files; d<=$1; d++ ))
do

	for (( c=$start; c<=$2; c++ ))
	do
		echo $RANDOM >> data.txt; 
	done


	./quicksort_verbose.out data.txt > quicksortAnswers.txt
	./mergesort_verbose.out data.txt > mergesortAnswers.txt 


	if diff quicksortAnswers.txt mergesortAnswers.txt; then
		filler=1
	else
	    cp quicksortAnswers.txt quicksort_failed_test_$d.txt
	    cp mergesortAnswers.txt mergesort_failed_test_$d.txt
	    ((fails=fails+1))
	fi


	rm data.txt
	rm quicksortAnswers.txt
	rm mergesortAnswers.txt

done

rm quicksort_verbose.out
rm mergesort_verbose.out


if [[ "$fails" -eq 0 ]]; then
	echo "All tests passed."
else
	echo "$fails tests failed."
fi



else
    echo "Please give number of tests and number of integers"
    exit
fi

