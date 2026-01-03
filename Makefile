CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS = -pthread
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
TARGET = tfs

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
