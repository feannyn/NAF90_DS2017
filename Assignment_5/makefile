CXXFLAG=g++ -std=c++11

all: proj5.x

#dependencies are what are required before running the code
# the two object files are then used to link and then create a single executable
proj5.x: passserver.o proj5.o 
	$(CXXFLAG) -lcrypt -o proj5.x passserver.o proj5.o
	

proj5.o: passserver.h hashtable.h proj5.cpp
	$(CXXFLAG) -lcrypt -c proj5.cpp

passserver.o: passserver.h passserver.cpp
	$(CXXFLAG) -c passserver.cpp

clean:
	rm -f *.o
