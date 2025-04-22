CC = gcc
CFLAGS = -Wall -Wextra -I./src
SRC = src/main.c src/frames.c
TARGET = parrot_live

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)