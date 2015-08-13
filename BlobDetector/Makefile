UNAME_S := $(shell uname -s)

INCLUDE = -I. -I/usr/local/include -I$(HOME)/torch/install/include
LDFLAGS =
LIBOPTS = -shared -L/usr/local/lib/lua/5.1 -L/usr/local/lib `pkg-config --libs opencv`
CFLAGS = -O3 -c -fpic -Wall `pkg-config --cflags opencv`
CC = g++

ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -lTH -lluajit -lluaT
endif


.PHONY: all
all : libblob_finder.so


.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) $<


libblob_finder.so : blob_finder.cpp
	$(CC) $< $(LIBOPTS) -o $@ $(LDFLAGS)


clean :
	    rm -f libblob_finder.so
