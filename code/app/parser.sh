#!/bin/bash

# info files
CNFILE=$1
VARFILE=$2
CNFTFILE=$3
VARFTFILE=$4

#output files
OCNFILE=$5
OVARFILE=$6

awk 'NR==FNR{a[$1];next} ($1 in a)' ${CNFTFILE} ${CNFILE} | \
sed -e 's/	2/	4/g' -e 's/	1/	3/g' -e 's/	0/	2/g' -e 's/	-1/	1/g' -e 's/	-2/	0/g'  > ${OCNFILE}

awk 'NR==FNR{a[$1];next} ($2 in a)' ${VARFTFILE} ${VARFILE} | \
awk '!seen[$1$2]++ {print $1"\t"$2"\t"$8}' | \
sed 's/LOW/0.1/g' | sed 's/MODERATE/0.5/g' | sed 's/MODIFIER/0.75/g' | \
sed 's/HIGH/1/g' > ${OVARFILE}
