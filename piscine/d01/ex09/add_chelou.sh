#!/bin/sh

# Dirtiest script I have ever made!
# It's as dirty as the exercise!

ibase1=\''\"?!'
ibase2=mrdoc
obase='gtaio luSnemf'

nbr1=$(echo "${FT_NBR1}" | sed  "s/'/0/g" | sed "s/\\\/1/g" | tr '"?!' '234')
dec_nbr1=$(echo "ibase=5;${nbr1}" | bc)

nbr2=$(echo "${FT_NBR2}" | tr "${ibase2}" '01234')
dec_nbr2=$(echo "ibase=5;${nbr2}" | bc)

#echo ${dec_nbr1}
#echo ${dec_nbr2}

#sum=$(echo "obase=13; ${dec_nbr1} + ${dec_nbr2}" | bc)
sum=$(echo "obase=13;ibase=5; ${nbr1} + ${nbr2}" | bc)

for (( i=0 ; i<${#sum} ; i++ )) ; do
	char=${sum:$i:1}
	dec_char=$(echo "obase=10;ibase=13;$char" | bc)
	printf "${obase:$dec_char:1}"
done

echo
