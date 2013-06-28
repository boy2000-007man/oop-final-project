CC = g++
CCFLAGS = -c -g
objects = GraphPacking.o Layout.o PackingCommand.o Rect.o SPPackingCommand.o SPPackingStrategy.o main.o

.cpp.o:
	$(CC) $< $(CCFLAGS) -o $@ 

main: $(objects)
	$(CC) $(objects) -o main

GraphPacking.o: GraphPacking.cpp GraphPacking.h
Layout.o: Layout.cpp Layout.h
PackingCommand.o: PackingCommand.cpp PackingCommand.h
Rect.o: Rect.cpp Rect.h
SPPackingCommand.o: SPPackingCommand.cpp SPPackingCommand.h
SPPackingStrategy.o: SPPackingStrategy.cpp SPPackingStrategy.h
main.o: main.cpp SPPackingStrategy.h SPPackingCommand.h Layout.h sdk.h

.PHONY: clean
clean:
	rm $(objects) main
