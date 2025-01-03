CC:= gcc
CFLAGS:= -Wall
LDFLAGS:= -lm
INCLUDES:= -I./include/
SRCS:= main.c src/queue.c
OBJS:= $(SRCS:.c=.o)
TARGET:= main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
