DESTDIR ?=
PREFIX ?= /usr/local
LIB ?= $(PREFIX)/lib
BIN ?= $(PREFIX)/bin

wasm3_src=../source/*.c
wasm3_src_obj=*.o

# To compile: run 'make objects', then 'make'

all: faustwasm3 faustbench-wasm3

objects: $(wasm3_src)
	$(CC) -march=native -Dd_m3LogOutput=0 -Ofast -c $(wasm3_src)
	
faustwasm3: faustwasm3.cpp wasm3_dsp.h wasm3_dsp.cpp $(wasm3_src_obj) 
	$(CXX) -Ofast -march=native -std=c++11 faustwasm3.cpp wasm3_dsp.cpp $(wasm3_src_obj) -Dd_m3LogOutput=0 `pkg-config --cflags --libs jack sndfile samplerate gtk+-2.0` $(LIB)/libHTTPDFaust.a -lmicrohttpd -dead_strip -o faustwasm3

faustbench-wasm3: faustbench-wasm3.cpp wasm3_dsp.h wasm3_dsp.cpp $(wasm3_src_obj)
	$(CXX) -Ofast -march=native -std=c++11 faustbench-wasm3.cpp wasm3_dsp.cpp $(wasm3_src_obj) -Dd_m3LogOutput=0 -o faustbench-wasm3

install:

	([ -e faustwasm3 ]) && cp faustwasm3 $(BIN) || echo faustwasm3 not found
	([ -e faustbench-wasm3 ]) && cp faustbench-wasm3 $(BIN) || echo faustbench-wasm3 not found

clean:

	rm *.o
	([ -e faustwasm3 ]) && rm faustwasm3 || echo faustwasm3 not found
	([ -e faustbench-wasm3 ]) && rm faustbench-wasm3 || echo faustbench-wasm3 not found
