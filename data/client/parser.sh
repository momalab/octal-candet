#!/bin/bash

# info files
IDFILE=$1
CNFILE=$2
VARFILE=$3
CNFTFILE=$4
VARFTFILE=$5

#output files
OCNFILE=$6
OVARFILE=$7

awk 'NR==FNR{a[$1];next} ($1 in a)' ${CNFTFILE} ${CNFILE} | awk 'FNR>1{for (i=2; i<=NF; i++) $i=($i+2)} {print $0}' > ${OCNFILE}

awk 'NR==FNR{a[$1];next} ($2 in a)' ${VARFTFILE} ${VARFILE} | awk -F['\t''('')'] '!seen[$1$2]++ {print $1"\t"$2"\t"$7"\t"$8"\t"$9"\t"$10}' | awk '{if (NF==4) print $1"\t"$2"\t0\t0\t"$4; else print $0}' | awk '{if ($3=="deleterious") $3=0.5; print $0}' | awk '{if ($3=="deleterious_low_confidence") $3=0.25; print $0}' | awk '{if ($3=="tolerated_low_confidence") $3=-0.25; print $0}' | awk '{if ($3=="tolerated") $3=-0.5; print $0}' | sed 's/LOW/0.1/g' | sed 's/MODERATE/0.5/g' | sed 's/MODIFIER/0.75/g' | sed 's/HIGH/1/g' | awk '{print $1"\t"$2"\t"$3*$4"\t"$5}' > ${OVARFILE}
