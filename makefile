CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I./include

SRCS = src/main.c src/files.c src/utils.c src/runna.c src/exercise.c src/display.c
OBJS = $(SRCS:src/%.c=obj/%.o)

TARGET = clings

all: $(TARGET)

debug: CFLAGS += -DDEBUG
debug: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clear: clean
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf obj

.PHONY: all clean clear debug

