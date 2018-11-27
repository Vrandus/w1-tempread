#!/bin/bash
first=$(./tempread)
if [ $first -eq 1 ]
then
	echo "unreadable"
exit

fi
echo "Init temp: $first"

while :
do
	current=$(./tempread)
	let diff=$current-$first
	if [ $diff -gt 1000 -a $diff -lt 2000 ]
	then
		echo " +-1 C"
		gpio write 0 1
		gpio write 1 0
		gpio write 2 0
	fi
	if [ $diff -gt 2000 -a $diff -lt 3000 ]
	then
		echo " +-2 C"
		gpio write 0 1
		gpio write 1 1
		gpio write 2 0
	fi
	if [ $diff -gt 3000 ]
	then
		echo "+-3 C"
		gpio write 0 1
		gpio write 1 1
		gpio write 2 1
	fi
done
