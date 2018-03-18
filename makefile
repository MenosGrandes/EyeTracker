CC = g++
CFLAGS = -g -Wall -std=c++11
SRCS = main.cpp
PROG = eyeDetection

OPENCV = `pkg-config --libs --cflags opencv` 
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
