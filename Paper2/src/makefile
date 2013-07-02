CC = g++
CCFLAG = -c -g
objects = main.o

main: $(objects)
	$(CC) $(objects) -o main

main.o:main.cpp SLT.h Rect.h test.h

.PHONY: clean
clean:
	rm $(objects) main
