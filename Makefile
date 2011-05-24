CFLAGS = -Wall -Wextra
SOURCE = src/exercicio1.c
TARGET = exercicio

build:
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	echo "todo"

all: build
