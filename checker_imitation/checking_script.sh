#!/bin/bash

#this script shall be placed in vm_champs older where and will use vm_champs/asm and ../asm 
#to complie champs from vm_champs/champs directory
#the resut will be displayed in diference.txt file


# $BOT_DIR="."

# BLUE        =   \033[0;94m
# YELLOW      =   \033[0;33m
# LIGHT       =   \033[0;5m
# COLOR_OFF   =   \033[0m
# GREEN       =   \033[0;32m
# PURPLE      =   \033[0;35m
# CYAN        =   \033[0;36m


$(mkdir  ./my ./or);
$(touch difference.txt)
$(chmod +x ./my);
$(chmod +x ./or);
# ="/my"  #my
# OR="/or" #original
bots=$(find vm_champs/champs -name "*.s") #list bots
cp $bots ./my
cp $bots ./or

# ./vm_champs/asm 

# echo $bots; 
my_bots=$(find my -name "*.s")
or_bots=$(find or -name "*.s")

i=0;
for i in $or_bots
do
vm_champs/asm $i

done

i=0;
for i in $my_bots
do
../asm $i

done





# comp_m=( $(find or -name '*.cor') )
# comp_o=( $(find my -name '*.cor') )

# for element in $(seq 0 $((${#comp_m[@]} - 1)))
# do
# 	if 
# 	echo =========\> "${comp_o[$element]}"  "${comp_m[$element]}"   \<=========
#   	diff "${comp_o[$element]}"  "${comp_m[$element]}" >> difference.txt
# done
echo "********* Folders differ: *********" 

diff --brief -r my/ or/ >> difference.txt

echo "=================>Files that differ: <===================" >> difference.txt


DIR1=$(ls or)
DIR2=$(ls my)

for i in $DIR1; do
    for j in $DIR2; do
        if [[ $i == $j ]]; then
            # echo "=====> $i" 
            # echo $DIR2/$j
            # echo "====> $i"
            # echo "====> $j"
            diff "my/$i" "or/$j" >> difference.txt
        fi
    done
done

cat difference.txt
rm -rf difference.txt
# rm -rf my or


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





# name1=${file1##*/}
# name2=${file2##*/}
# if [[ $name1 == $name2 ]]; then
#     echo "$name1 exists in both directories"
# fi