CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c files.c utils.c runna.c exercise.c
OBJS = $(SRCS:.c=.o)
DEBUG_OBJS = $(SRCS:.c=_debug.o)

TARGET = clings
DEBUG_TARGET = clings_debug

all: $(TARGET)

debug: $(DEBUG_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(DEBUG_TARGET): $(DEBUG_OBJS)
	$(CC) $(CFLAGS) -DDEBUG -o $(DEBUG_TARGET) $(DEBUG_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_debug.o: %.c
	$(CC) $(CFLAGS) -DDEBUG -c $< -o $@

clean:
	rm -f $(OBJS) $(DEBUG_OBJS) $(TARGET) $(DEBUG_TARGET)

.PHONY: all clean debug

