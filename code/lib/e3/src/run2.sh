#!/bin/sh

#cd cpp_crcl && make && cd ..

TFHE=0
FHEW=0
HELI=0
CUDD=0
SEAL=0

MPIR=0

lib=tfhe
#lib=heli
#lib=fhew
lib=bddn
#lib=bdda
#lib=bddf
#lib=gate
#lib=gat
#lib=bench/aes_circ
#lib=nand
#lib=pilc
#lib=pila
lib=fibo
#lib=sanja
#lib=extern
#lib=ext_gate
#lib=pail
#lib=pailg
#lib=../../tests/user/seal_arith
#lib=kalm/cha
#lib=isca/comb/gate
#lib=isca/comb/gate/std
#lib=ops_circ
lib=ops_ring
#lib=bsort
#lib=ops
#lib=bug17

#lib=isca/bench/bridge/fact
#lib=isca/bench/bridge/fib
#lib=isca/bench/bridge/isort
#lib=isca/bench/bridge/jen
#lib=isca/bench/bridge/matrix
#lib=isca/bench/bridge/sieve
#lib=isca/bench/bridge/speck
#lib=isca/bench/bridge/bsort

#lib=ops_circ

#lib=../../tests/user/seal/int/arith
#lib=../../tutorials/steps/3
#lib=../../tests/user/neural_network/cipher

usr=user/$lib
cfg=$usr/cgt.cfg
#cfg=$usr/../cgt.cfg

# clean keys
rm -f *.key secint.* *.const *.tmp
rm -f bob.exe alice.exe

ncpu=`grep -c ^processor /proc/cpuinfo`

ncpu = $(( $ncpu - 1 ))
if (( $ncpu < 1 )); then
ncpu = 1
fi

echo "run2: Building cgt"
make -j $ncpu TFHE=$TFHE FHEW=$FHEW HELI=$HELI CUDD=$CUDD MPIR=$MPIR SEAL=$SEAL cgt.exe || exit

echo ./cgt.exe gen -c $cfg -d $usr
./cgt.exe gen -c $cfg -d $usr || exit

## make -j $ncpu -f mak_bob.mak USER=$usr BITSIZE=8 TFHE=$TFHE FHEW=$FHEW HELI=$HELI MPIR=$MPIR SEAL=$SEAL CGT=$cfg bob.exe || exit
##./bob.exe 1000000 || exit
##make -j $ncpu -f mak_alice.mak USER=$usr BITSIZE=8 CUDD=$CUDD TFHE=$TFHE FHEW=$FHEW HELI=$HELI MPIR=$MPIR SEAL=$SEAL CGT=$cfg alice.exe || exit
##./alice.exe

#./bob.exe || exit
#./bob.exe | ./cgt.exe dec -c $cfg -s 8 || exit

echo -ne '\007'
