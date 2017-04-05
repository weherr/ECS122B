#!/bin/bash

if [ "$1" != "" ] && [ "$2" != "" ] && [ "$3" != "" ]; then
	if [ "$1" == "quicksort" ] || [ "$1" == "quicksort_verbose.out" ] || [ "$1" == "quicksort_timed.out" ] || [ "$1" == "quicksort_stats.out" ]; then
		make
		echo "Sample Number   Language        Time       # of Partitioning Stages   # of Exchanges   # of Comapres" > quicksort.csv

		start=1
		files=1


		# for each test we want to run
		for (( d=$files; d<=$2; d++ ))
		do
			#print number of randoms to data.txt
			for (( c=$start; c<=$3; c++ ))
			do
				echo $RANDOM >> data.txt; 
			done


			(time ./quicksort_timed.out data.txt) 2> timed.txt

			real=$(cat timed.txt | head -2 | tail -1)
			user=$(cat timed.txt | head -3 | tail -1)
			sys=$( cat timed.txt | head -4 | tail -1)

			rm timed.txt


			./quicksort_stats.out data.txt > quicksort_data.txt


			partition=$(cat quicksort_data.txt | head -1 | tail -1 | tr -dc '0-9')
			exchanges=$(cat quicksort_data.txt | head -2 | tail -1 | tr -dc '0-9')
			compares=$(cat quicksort_data.txt | head -3 | tail -1| tr -dc '0-9')


			echo "$d               C++        $real             $partition                    $exchanges               $compares" >> quicksort.csv 
			echo "                           $user  " >> quicksort.csv
			echo "                           $sys   " >> quicksort.csv

			echo "" >> quicksort.csv

			rm data.txt


		done



		rm quicksort_data.txt



	elif [ "$1" == "mergesort" ] || [ "$1" == "merge_verbose.out" ] || [ "$1" == "merge_timed.out" ] || [ "$1" == "merge_stats.out" ]; then
		make

		echo "Sample Number   Language        Time       # of Recursive Calls  # of Exchanges   # of Comapres" > mergesort.csv
		start=1
		files=1


		# for each test we want to run
		for (( d=$files; d<=$2; d++ ))
		do
			#print number of randoms to data.txt
			for (( c=$start; c<=$3; c++ ))
			do
				echo $RANDOM >> data.txt; 
			done


			(time ./merge_timed.out data.txt) 2> timed.txt

			real=$(cat timed.txt | head -3 | tail -1)
			user=$(cat timed.txt | head -4 | tail -1)
			sys=$( cat timed.txt | head -5 | tail -1)


			rm timed.txt

			
			./mergesort_stats.out data.txt > mergesort_data.txt


			recursive=$(cat mergesort_data.txt | head -1 | tail -1 | tr -dc '0-9')
			exchanges=$(cat mergesort_data.txt | head -2 | tail -1 | tr -dc '0-9')
			compares=$(cat mergesort_data.txt | head -3 | tail -1| tr -dc '0-9')


			echo "$d               C++        $real                    $recursive                  $exchanges               $compares" >> mergesort.csv 
			echo "                           $user  " >> mergesort.csv
			echo "                           $sys   " >> mergesort.csv

			echo "" >> mergesort.csv

			rm data.txt


		done

		rm mergesort_data.txt

	else
		echo "Could not open executable"
	fi



make clean
else
    echo "Please give an executable, number of tests, and number of integers"
    exit
fi

