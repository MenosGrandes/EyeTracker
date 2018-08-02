CC = g++
CFLAGS = -g -p -Wall -std=c++11 -ltbb
SRCS = main.cpp
PROG = eyeDetection
BIN = bin
MKDIR_P = mkdir -p $(BIN)
OPENCV = `pkg-config --libs --cflags opencv` 
LIBS = $(OPENCV)
RM = rm -rf



all : buildAll
debug :
	$(MKDIR_P)
	$(CC) $(CFLAGS) -DDEBUG -o $(BIN)/$(PROG) $(SRCS) $(LIBS)

buildAll:$(SRCS)
	$(MKDIR_P)
	$(CC) $(CFLAGS) -o $(BIN)/$(PROG) $(SRCS) $(LIBS)
clean:
	$(RM) $(BIN)

