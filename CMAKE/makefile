CC = g++
CFLAGS = -g -p -Wall -std=c++11 
SRCS = main.cpp
PROG = eyeDetection
BIN = bin
MKDIR_P = mkdir -p $(BIN)
OPENCV = `pkg-config --libs --cflags opencv4` 
LIBS = $(OPENCV) -ltbb
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

