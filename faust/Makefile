

DESTDIR ?=
PREFIX ?= /usr/local
LIB ?= $(PREFIX)/lib
BIN ?= $(PREFIX)/bin

wasm3_src=../source/*.c

all: faustwasm3 

libwasm3: $(wasm3_src)
	$(CXX) -Ofast -march=native $(wasm3_src) -Dd_m3LogOutput=0 -c 
	
faustwasm3: faustwasm3.cpp wasm3_dsp.h wasm3_dsp.cpp libwasm3
	$(CXX) -Ofast -march=native -std=c++11 faustwasm3.cpp wasm3_dsp.cpp m3_*.o `pkg-config --cflags --libs jack sndfile samplerate gtk+-2.0` $(LIB)/libHTTPDFaust.a -lmicrohttpd -dead_strip -o faustwasm3

install:

	([ -e faustwasm3 ]) && cp faustwasm3 $(BIN) || echo faustwasm3 not found

clean:

	([ -e faustwasm3 ]) && rm faustwasm3 || echo faustwasm3 not found
