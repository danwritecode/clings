CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c files.c utils.c runna.c exercise.c
OBJS = $(SRCS:.c=.o)

TARGET = clings

all: $(TARGET)

debug: CFLAGS += -DDEBUG
debug: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean debug

