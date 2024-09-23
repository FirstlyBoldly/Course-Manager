courseExplorer: courseExplorer.o course.o
	g++ courseExplorer.o course.o -o courseExplorer

courseExplorer.o: courseExplorer.cpp
	g++ -c courseExplorer.cpp

course.o: course.cpp course.h
	g++ -c course.cpp

clean:
	rm *.o courseExplorer
