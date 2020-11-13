OBJECTS = profile.o network.o
HFILES = profile.h network.h post.h
CXXFLAGS = --std=c++11

main: main.o ${OBJECTS}
	g++ -o main main.o ${OBJECTS}

tests: tests.o ${OBJECTS}
	g++ -o tests tests.o ${OBJECTS}

main.o: main.cpp ${HFILES}

tests.o: tests.cpp doctest.h ${HFILES}

profile.o: profile.cpp profile.h

network.o: network.cpp ${HFILES}

clean:
	rm -f main.o tests.o ${OBJECTS}
	
help:
	@echo  make main : make executable named main
	@echo make tests : make test suite named tests
