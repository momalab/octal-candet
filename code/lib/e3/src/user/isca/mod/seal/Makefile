CC=g++
FLAGS=-O2 -std=c++17
ROOT=../../../../..
INCS=-I${ROOT}/3p/seal_unx/include
LIBS=-L${ROOT}/3p/seal_unx/lib -lseal -pthread

%: %.cpp
	${CC} ${INCS} ${FLAGS} -c $<
	${CC} -o $@.exe $@.o ${LIBS}
