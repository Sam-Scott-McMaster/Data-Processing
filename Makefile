CC = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = main.o data_io.o data_cleaning.o
TARGET = data_cleaner

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c data_io.h data_cleaning.h
	$(CC) $(CFLAGS) -c main.c

data_io.o: data_io.c data_io.h
	$(CC) $(CFLAGS) -c data_io.c

data_cleaning.o: data_cleaning.c data_cleaning.h data_io.h
	$(CC) $(CFLAGS) -c data_cleaning.c

clean:
	rm -f $(OBJS) $(TARGET)
