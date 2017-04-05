#!/bin/bash

# NEEDS TO BE RUN IN DIR WITH Enumeration.cpp	
	for ((x=0;x<50;x++))
	do
		# for the number of items
		for (( d=3; d<=5; d++))
		do
			Allowed copies
			for (( c=1; c<=4; c++ ))
			do
				
				echo SubSetEnumerationTimed >:
				echo -n Number items $d - Max Number of copies $c 
				time ./SubSetEnumerationTimed.out $d $c
				echo
				echo NTupleEnumeration: 
				echo -n Number items $d - Max Number of copies $c 
				time ./NTupleEnumerationTimed.out $d $c
				echo 

			done

		done
	done

