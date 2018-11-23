#!/bin/bash
# $BOT_DIR="."
$(mkdir  ./my ./or);
$(touch difference.txt)
$(chmod +x ./my);
$(chmod +x ./or);
# ="/my"  #my
# OR="/or" #original
bots=$(find vm_champs/champs -name '*.s') #list bots
cp $bots ./my
cp $bots ./or

# ./vm_champs/asm 

# echo $bots; 
my_bots=$(find my -name '*.s')
or_bots=$(find or -name '*.s')

i=0;
for i in $or_bots
do
$(vm_champs/asm $i)

done

i=0;
for i in $my_bots
do
$(../asm $i)
# echo "$i"
done


comp_m=$(find my -name '*.cor')
comp_o=$(find or -name '*.cor')


arrayname=( $(find or -name '*.cor') )
arrayname2=( $(find my -name '*.cor') )

for element in $(seq 0 $((${#arrayname[@]} - 1)))
do
     echo =========\> "${arrayname2[$element]}"  "${arrayname[$element]}"   \<=========
    diff "${arrayname2[$element]}"  "${arrayname[$element]}" >> difference.txt
done




# for i in $comp_m
# do
# echo ============\> "$i" comp_m \<====================
# done

# ${!AR[*]}


# diff my/Varimathras.cor my/Wall.cor >> difference.txt
# $(diff "${comp_o[idx]}" "${comp_m[idxx]}" >> difference.txt);

# for ((idx=0; idx<${!comp_m[@]}; ++idx)) do
# 	echo  ======\>  $idx "${comp_m[*]}"  \<==========  >> difference.txt 
# 	# diff "${comp_o[idx]}" "${comp_m[idx]}" >> "difference.txt"
# done

# echo $idx

# echo "${comp_o[idx]}"

# AR=('foo' 'bar' 'baz' 'bat')
# for i in "${!AR[@]};" do
#   printf '${AR[%s]}=%s\n' "$i" "${AR[i]}"
# done
# $(cp $bots /my);
# $(cp $(ls -l  vm_champs/champs | grep -E "(/|.*\.s$)") /or);
	# $(cp $bot ./or);
# done

#copy bots to my




# for ((idx=0; idx<${#array[@]}; ++idx)); do
#     echo "$idx" "${array[idx]}"
# done

# echo "${comp_o[idx]}" "${comp_m[idx]}"
# echo "${comp_m[idx]}"


# AR=('foo' 'bar' 'baz' 'bat')
# for i in ${!AR[*]}; do
#   echo $i  ${AR[i]}
# done