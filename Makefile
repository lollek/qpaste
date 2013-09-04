CC = g++
SRC = src/mylist_t.o src/loader.o src/main.o
TARGET = qpaste

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(SRC)
	$(RM) $(TARGET)