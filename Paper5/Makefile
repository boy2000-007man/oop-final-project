CC = g++
CCFLAGS = -c -g
objects = dc.o edge.o error.o i_o.o memory.o sort.o main.o \
	  sdk.o delaunay_triangulation.o bng.o rmst.o polygonal_contraction.o 

.cpp.o:
	$(CC) $< $(CCFLAGS) -o $@ 

main: $(objects)
	$(CC) $(objects) -o main

dc.o: dc.cpp defs.h decl.h dc.h edge.h
edge.o: edge.cpp defs.h decl.h edge.h extern.h
error.o: error.cpp
i_o.o: i_o.cpp defs.h decl.h extern.h edge.h
memory.o: memory.cpp defs.h decl.h
sort.o: sort.cpp defs.h decl.h
main.o: main.cpp sdk.h
sdk.o: sdk.cpp sdk.h
delaunay_triangulation.o: delaunay_triangulation.cpp delaunay_triangulation.h sdk.h
bng.o: bng.cpp bng.h sdk.h
rmst.o: rmst.cpp rmst.h sdk.h
polygonal_contraction.o: polygonal_contraction.cpp polygonal_contraction.h sdk.h

.PHONY: clean
clean:
	rm $(objects) main
