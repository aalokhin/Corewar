#!/bin/bash

# Specify path with your champions.
CHAMPS=$(find champs -type f -name "*.cor" | grep -v champs/championships/2014/gudepard/Kappa.cor | grep -v champs/42.cor)
echo $CHAMPS

# Specify executable of your corewar.
MY=../corewar
# Specify executable of original corewar.
OR=./corewar

make_diff() {
	./$MY -d 15000 $@ > file1
	./$OR -d 15000 $@ > file2
	diff file1 file2 || printf "$@ - different\n\n" >> dump
	# ./$MY -v 31 $@ > file_v1
	# ./$OR -v 31 $@ > file_v2
	# diff file1 file2 || printf "$@ - different\n\n" >> vvv
}

for i in $CHAMPS; do
	make_diff $i
	# for j in $CHAMPS; do
		# make_diff $i $j
		# for k in $CHAMPS; do
			# make_diff $i $j $k
			# for h in $CHAMPS; do
				# make_diff $i $j $k $h
			# done
		# done
	# done
done

# rm -f file_v1 file_v2
rm -f file_1 file_2