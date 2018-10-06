#/bin/sh

for i in -90 100 90 85 70 60 45 101
do
	echo -ne "$i\n"
	echo $i | ./4
	echo -ne "-----------\n"
done
