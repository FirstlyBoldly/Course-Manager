objects = courseExplorer.o course.o

courseExplorer: $(objects)
	g++ $(objects) -o courseExplorer

courseExplorer.o: courseExplorer.cpp course.h
course.o: course.cpp course.h

.PHONY: clean
clean:
	del -f $(objects) courseExplorer.exe
