#!/bin/bash 
# change these per each homework 
#	link to tests:
#	number of tests: 
numtests=93
#	command to execute test: 
command="./hw3 < ./tests/t\$i.in >& ./tests/t\$i.res"

i="0"

while [ $i -lt $numtests ] 
	do 
	eval ${command}  # Fails to $i into it
	diff ./tests/t${i}.res ./tests/t${i}.out &> /dev/null
	if [[ $? != 0 ]] 
		then
		echo "Failed test #"${i}"!"
		exit 
	fi 
	i=$[$i+1] 
done 

echo "Finished tests - GREAT SUCCESS" 
exit
