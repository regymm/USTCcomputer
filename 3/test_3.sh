#/bin/sh

for i in -5.0 -3.0 1.0 2.0 2.5 3.0 5.0
do
	echo -ne "$i\n"
	echo $i | ./3
	echo -ne "-----------\n"
done
