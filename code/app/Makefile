# parameters

N_FEATURES=32768
N_THREADS=8
IBIT=6
WBIT=14

# directories
LOCALDIR=$(abspath .)
CODEDIR=${LOCALDIR}/..
DATADIR_CLIENT=${LOCALDIR}/../../data/client
DATADIR_SERVER=${LOCALDIR}/../../data/server
LIBDIR=${CODEDIR}/lib
E3DIR=${LIBDIR}/e3
SRCDIR=${E3DIR}/src
SEALDIR=${E3DIR}/3p/seal_unx
COMMONDIR=${CODEDIR}/common

FEATUREDIR_CLIENT=${DATADIR_CLIENT}/${N_FEATURES}
FEATUREDIR_SERVER=${DATADIR_SERVER}/${N_FEATURES}

# e3 config
CGT_FILE=${COMMONDIR}/cgt.cfg
E3NOABORT=1
SEAL=1

# compiler info
CC=g++
FLAGS=-O2 -std=c++17
INCS=-I${SRCDIR} -I${SEALDIR}/include -I${COMMONDIR} -I${LIBDIR}
E3_CPP=${SRCDIR}/cgtshared.cpp ${SRCDIR}/secint.cpp ${SRCDIR}/cgtkey.cpp
LIBS=${LIBDIR}/plaintext.cpp ${LIBDIR}/dataformat.cpp ${LIBDIR}/io.cpp ${E3_CPP} -L${SEALDIR}/lib -lseal -pthread
DEFINES=-DE3NOABORT=${E3NOABORT} -DE3KEY=1

# files
IDFILE=${DATADIR_CLIENT}/Test_samples.txt# patient ids file
CNFILE=${DATADIR_CLIENT}/Test_CNs.txt# cn file
VARFILE=${DATADIR_CLIENT}/Test_variants.txt# variants file
CNFTFILE=${FEATUREDIR_CLIENT}/cn_features_V2.txt# CN features file
VARFTFILE=${FEATUREDIR_CLIENT}/var_features_V2.txt# variants features file
WFILE=${FEATUREDIR_SERVER}/Weights.txt# weights file
BFILE=${FEATUREDIR_SERVER}/Bias.txt# biases file
OCNFILE=parsed_cn.tmp
OVARFILE=parsed_var.tmp
DOFILE=output.tmp# decrypted output file

all: parse run

%: %.cpp
	${CC} ${FLAGS} ${INCS} -o $@.exe $< ${LIBS} ${DEFINES}

cgt:
	rm -f *.const *.key
	cd ${SRCDIR} && \
	$(MAKE) c && \
	$(MAKE) cgt.exe SEAL=${SEAL} && \
	./cgt.exe gen -c ${CGT_FILE} -d ${LOCALDIR} && \
	bash amalgam.sh && bash amalkey.sh && \
	cp *.key ${LOCALDIR} && \
	cp *.const ${LOCALDIR}

c: clean
	rm -f *.const *.key

clean:
	rm -f *.o *.exe *.tmp

compile: main

parse:
	sh parser.sh ${CNFILE} ${VARFILE} ${CNFTFILE} ${VARFTFILE} ${OCNFILE} ${OVARFILE}

run:
	./main.exe ${IDFILE} ${OCNFILE} ${OVARFILE} ${CNFTFILE} ${VARFTFILE} ${WFILE} ${BFILE} ${DOFILE} ${IBIT} ${WBIT} ${N_THREADS}
