CC=g++
CINCLUDE=-I/usr/local/include -I./Base/include
CFLAGS=-Wall -g
LFLAGS=-L/usr/local/lib -ljpeg -lm
OUTNAME=main

OBJECT = ./Base/source/config.o ./Base/source/function.o \
		 main.o

test : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) $(CINCLUDE) $(LFLAGS) -o $(OUTNAME)

$(OBJECT) : ./Base/include/config.h		./Base/source/config.cpp \
			./Base/include/function.h	./Base/source/function.cpp

.PHONY : clean
clean :
	-rm $(OUTNAME) $(OBJECT)
