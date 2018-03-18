CC = g++
CFLAGS = -g -Wall -std=c++11
SRCS = main.cpp
PROG = eyeDetection
BIN = bin
MKDIR_P = mkdir -p $(BIN)
OPENCV = `pkg-config --libs --cflags opencv` 
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(MKDIR_P)
	$(CC) $(CFLAGS) -o $(BIN)/$(PROG) $(SRCS) $(LIBS)
