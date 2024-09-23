objects = courseExplorer.o course.o

courseExplorer: $(objects)
	g++ $(objects) -o courseExplorer

courseExplorer.o: courseExplorer.cpp course.h
	g++ -c courseExplorer.cpp

course.o: course.cpp course.h
	g++ -c course.cpp

clean:
	del -f $(objects) courseExplorer.exe
