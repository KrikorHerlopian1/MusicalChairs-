#!/bin/sh
###########################################################
### Script to run Program5 repeatedly with 2,000 children
###########################################################

echo;echo "Test p5 repeatedly until CTRL-c"; echo

#ulimit -n 2600

i=1
while [ $i -le 100 ]
do
   #strace -f ./p5 4			# trace system calls
   ./p5 5 | grep Congra
   i=`expr $i + 1`
done

