CC=g++
HEADER_DIR=-I/usr/local/include
LIB_DIR=-L/usr/local/lib
CFLAGS=-g -Wall -std=c++11 -o3
ARCH=-arch x86_64
LIBS=-lprotobuf


all: article_collection

article_collection: main article_collection.pb
	$(CC) $(LIB_DIR) $(LIBS) main.o article_collection.pb.o -o article_collection

main: main.cc
	$(CC) $(ARCH) $(HEADER_DIR) $(CFLAGS) -c main.cc -o main.o

article_collection.pb: article_collection.pb.cc
	$(CC) $(ARCH) $(HEADER_DIR) $(CFLAGS) -c article_collection.pb.cc -o article_collection.pb.o

clean:
	rm *o article_collection
