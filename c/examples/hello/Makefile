# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = hello # target executable
objects = hello.o

all: $(target)

hello: $(objects)
	g++ -o $(target) $(objects)

hello.o: hello.cpp
	g++ -c hello.cpp

clean:
		rm *.o $(target)
