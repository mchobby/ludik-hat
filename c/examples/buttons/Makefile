# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = buttons # target executable
objects = buttons.o

all: $(target)

buttons: $(objects)
	g++ -Wall -o $(target) -lpigpio -lrt -lpthread $(objects)

buttons.o: buttons.cpp
	g++ -c buttons.cpp

clean:
	rm *.o $(target)
