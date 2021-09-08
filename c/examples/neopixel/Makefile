# target: pre-req1 pre-req2
# Created with the help of https://earthly.dev/blog/g++-makefile/
target = neotest # target executable
objects = neopixel.o

all: $(target)

# -lws2811 -I /usr/local/include/ws2811/  -L /usr/local/lib/
neotest: $(objects)
	g++ -Wall -o $(target) -lpigpio -lrt -lpthread $(objects) -lws2811

neopixel.o: neopixel.cpp
	g++ -I /usr/local/include/ws2811/ -c neopixel.cpp

clean:
	rm *.o $(target)
