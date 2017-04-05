#!/bin/bash


make

fails=0
testNumber=0
for (( d=0; d<100; d++ ))
do
	./Enumeration.out 6 sanity_check > failure.txt 
	if diff SubSetResults.txt NTupleResults.txt; then
		((testNumber=testNumber+1))
		echo Test $testNumber passed
	else
		echo Test $testNumber FAILED
		echo Data Used:
		cat failure.txt
		echo
		echo MY OUTPUT: 
		cat SubSetResults.txt
		cat NTupleResults.txt
		((fails=fails+1))
		break
	fi
done


if [[ "$fails" -eq 0 ]]; then
	rm failure.txt
	rm SubSetResults.txt
	rm NTupleResults.txt
fi


make clean