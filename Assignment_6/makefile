CXXFLAG=g++ -std=c++11

all: proj6.x

proj6.x: proj6.o
	$(CXXFLAG) -o proj6.x proj6.cpp

proj6.o: proj6.cpp
	$(CXXFLAG) -c proj6.cpp

clean:
	rm -rf *.o
