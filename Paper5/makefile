main:main.o sdk.o sdk.h delaunay_triangulation.o delaunay_triangulation.h bng.o bng.h rmst.o rmst.h polygonal_contraction.o polygonal_contraction.h
	g++ main.o sdk.o delaunay_triangulation.o bng.o rmst.o polygonal_contraction.o -o main
main.o:main.cpp sdk.h
	g++ -c main.cpp -o main.o
sdk.o:sdk.cpp sdk.h
	g++ -c sdk.cpp -o sdk.o
delaunay_triangulation.o:delaunay_triangulation.cpp delaunay_triangulation.h
	g++ -c delaunay_triangulation.cpp -o delaunay_triangulation.o
bng.o:bng.cpp bng.h
	g++ -c bng.cpp -o bng.o
rmst.o:rmst.cpp rmst.h
	g++ -c rmst.cpp -o rmst.o
polygonal_contraction.o:polygonal_contraction.cpp polygonal_contraction.h
	g++ -c polygonal_contraction.cpp -o polygonal_contraction.o
clean:
	rm *.o
