CC = g++
CCFLAGS = -c -g
objects = GraphPacking.o Layout.o PackingCommand.o Rect.o SPPackingCommand.o SPPackingStrategy.o main.o

.cpp.o:
	$(CC) $< $(CCFLAGS) -o $@ 

main: $(objects)
	$(CC) $(objects) -o main

GraphPacking.o: GraphPacking.cpp GraphPacking.h SPPackingCommand.h Layout.h
Layout.o: Layout.cpp Layout.h Rect.h PackingStrategy.h
PackingCommand.o: PackingCommand.cpp PackingCommand.h
Rect.o: Rect.cpp Rect.h Point.h
SPPackingCommand.o: SPPackingCommand.cpp SPPackingCommand.h GraphPacking.h Layout.h Rect.h
SPPackingStrategy.o: SPPackingStrategy.cpp SPPackingStrategy.h SPPackingCommand.h Layout.h
main.o: main.cpp SPPackingStrategy.h SPPackingCommand.h Layout.h test.h

.PHONY: clean
clean:
	rm $(objects) main
