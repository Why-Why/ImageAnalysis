CC=g++
CINCLUDE=-I/usr/local/include -I./Base/include
CFLAGS=-Wall -g
LFLAGS=-L/usr/local/lib -ljpeg -lm
OUTNAME=main

OBJECT = ./Base/source/config.o ./Base/source/function.o \
		 ./Test/source/getImage.o \
		 main.o

test : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) $(CINCLUDE) $(LFLAGS) -o $(OUTNAME)

$(OBJECT)  : ./Base/include/config.h	./Base/source/config.cpp \
			 ./Base/include/function.h	./Base/source/function.cpp
getImage.o : ./Test/include/getImage.h	./Test/source/getImage.cpp

.PHONY : clean
clean :
	-rm $(OUTNAME) $(OBJECT)
