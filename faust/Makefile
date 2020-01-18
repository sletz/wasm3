LIB ?= /usr/local/lib

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

wasm3_src=../source/*.c

all: faustwasm3 


libwasm3: $(wasm3_src)
	$(CC) -O3 $(wasm3_src) -c 
	
faustwasm3: faustwasm3.cpp wasm3_dsp.h wasm3_dsp.cpp libwasm3
	$(CXX) -Ofast -std=c++11 faustwasm3.cpp wasm3_dsp.cpp m3_*.o `pkg-config --cflags --libs jack sndfile samplerate gtk+-2.0` $(LIB)/libHTTPDFaust.a -lmicrohttpd -o faustwasm3

install:

	([ -e faustwasm3 ]) && cp faustwasm3 $(prefix)/bin || echo faustwasm3 not found

clean:

	([ -e faustwasm3 ]) && rm faustwasm3 || echo faustwasm3 not found
