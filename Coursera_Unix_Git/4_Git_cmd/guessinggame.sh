#!/bin/bash
function count(){
	filenumber=$1
	guess=$2
	#echo $filenumber
	if [[	$filenumber -eq $guess ]];then
		return 0
	elif [[ $filenumber -gt $guess ]];then
		return 1
	elif [[ $filenumber -lt $guess ]];then
		return 2
	fi
}
filenumber=`find ./ -type f | wc -l`
echo "(all files rigth answer is $filenumber)"
echo ""
while true; do
	echo -n "please input: "
	read response
	count $filenumber $response
	ans=$?
	#echo $ans
	if [[ $ans -eq 0 ]];then
		echo "you are right!"
		break
	elif [[ $ans -eq 1 ]];then
		echo "your guess is lower"
	elif [[ $ans -eq 2 ]];then
		echo "your guess is upper"
	fi
done
echo "bye bye"

