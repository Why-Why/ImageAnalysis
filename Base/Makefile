CC=g++
CINCLUDE=-I/usr/local/include
CFLAGS=-Wall -g
LFLAGS=-L/usr/local/lib -ljpeg -lm

OBJECT = ./source/config.o ./source/function.o \
		 main.o

test : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) $(CINCLUDE) $(LFLAGS) -o tool

$(OBJECT) : ./include/config.h		./source/config.cpp \
			./include/function.h	./source/function.cpp

.PHONY : clean
clean :
	-rm tool $(OBJECT)
