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

bots=$(find vm_champs/champs -name "*.s") #list bots
cp $bots ./my
cp $bots ./or

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


echo "\033[1;36m"
echo "********* Folders differ: *********"  >> difference.txt

diff --brief -r my/ or/ >> difference.txt


cat difference.txt
rm -rf difference.txt
rm -rf my or





$(mkdir  ./my ./or);
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
vm_champs/asm -a $i > "$i.txt"
rm -rf $i
done

i=0;
for i in $my_bots
do
 # echo ">>>$i<<<"
../asm -a $i > "$i.txt"
rm -rf $i
done

echo "=================>Flag A differs: <===================" >> result.txt

diff --brief -r my/ or/ >> result.txt
echo " \033[1;35m"
cat result.txt
rm -rf my or 
rm -rf result.txt



$(mkdir  ./my ./or);
$(chmod +x ./my);
$(chmod +x ./or);
# ="/my"  #my
# OR="/or" #original
bots=$(find vm_champs/champs -name "*.s") #list bots
cp $bots ./my
cp $bots ./or

# ./vm_champs/asm 
echo "=================>StdScr difference: <===================" >> result.txt

# echo $bots; 
my_bots=$(find my -name "*.s")
or_bots=$(find or -name "*.s")

i=0;
for i in $or_bots
do
vm_champs/asm  $i > "$i.txt"
../asm  $i > "$i2.txt"
if [[ $(diff "$i2.txt" "$i.txt") ]]; then
    echo "$i ===>" >> result.txt && diff "$i2.txt" "$i.txt" >> result.txt
fi
rm -rf $i
done

echo " \033[1;32m"
cat -e result.txt
rm -rf my or 
rm -rf result.txt
