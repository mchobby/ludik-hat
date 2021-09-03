# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = read_ds18b20 # target executable
objects = ds18b20.o read_ds18b20.o

all: $(target)

read_ds18b20: $(objects)
	g++ -Wall -o $(target) -lpigpio -lrt -lpthread $(objects)

read_ds18b20.o: read_ds18b20.cpp
	g++ -c read_ds18b20.cpp

ds18b20.o: ds18b20.cpp
	g++ -c ds18b20.cpp

clean:
	rm *.o $(target)
