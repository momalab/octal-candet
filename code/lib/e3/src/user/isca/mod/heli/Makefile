ROOT=../../../../..
HELIB=${ROOT}/3p/heli_unx

CC=g++
FLAGS=-O2 -std=c++17
INCS=-I${HELIB}/src
LIBS=${HELIB}/native/fhe.a -lntl -lgmp -lm -pthread

%: %.cpp
	${CC} ${INCS} ${FLAGS} -c $<
	${CC} -o $@.exe $@.o ${LIBS}
