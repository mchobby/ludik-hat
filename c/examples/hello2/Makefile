# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = hello2 # target executable
objects = func.o hello.o

all: $(target)

hello2: $(objects)
	g++ -o $(target) $(objects)

hello.o: hello.cpp
	g++ -c hello.cpp

func.o: func.cpp
	g++ -c func.cpp

clean:
		rm *.o $(target)
