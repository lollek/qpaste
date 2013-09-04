CC = g++
SRC = src/mylist_t.o src/parser.o
TARGET = qpaste

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)