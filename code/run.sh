#!/bin/sh

LOGFILE=run.log
rm -f ${LOGFILE}
cd app
STARTTIME=$(date +%s)
make IDFILE=../$1 CNFILE=../$2 VARFILE=../$3 N_FEATURES=$4 | tee ../${LOGFILE}
ENDTIME=$(date +%s)
cd ..
echo "Time (total): $(( $ENDTIME - $STARTTIME )) s" | tee -a ${LOGFILE}

TIMEFILE=time.log
grep "Time (total)"       ${LOGFILE} | awk '{printf "(%f, ", $3}' >  ${TIMEFILE}
grep "Time (encryption)"  ${LOGFILE} | awk '{printf "%f, " , $3}' >> ${TIMEFILE}
grep "Time (computation)" ${LOGFILE} | awk '{printf "%f, " , $3}' >> ${TIMEFILE}
grep "Time (decryption)"  ${LOGFILE} | awk '{printf "%f)\n", $3}' >> ${TIMEFILE}
