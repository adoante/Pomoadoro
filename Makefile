CC = g++	# use g++ for compiling c++ code
CFLAGS = -g -Wall -std=c++11		# compilation flags: -g for debugging.

all: main
SRCS = main.cpp
DEPS = $(SRCS:.cpp=.d)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

main: main.o
	$(CC) main.o -o pomoadoro

clean:
	rm *.o pomoadoro
