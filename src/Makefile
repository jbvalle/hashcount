CC=gcc

CFLAGS =-g -Wall -Wextra -pedantic -O0

SRCS = $(wildcard *.c)

BINS = $(SRCS:%.c=%)

TARGET = hashcount

all: clean $(TARGET) run

$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) -o $@ $^ -lm

run:
	@./$(TARGET)

debug: $(SRCS)
	@$(CC) $(CFLAGS) -o $(TARGET) $^ -lm
	@gdb $(TARGET)

segfault: $(SRCS)
	ulimit -c unlimited
	$(CC) $(CFLAGS) -o $(TARGET) $^ -lm
	gdb $(TARGET) core

memleak:
	valgrind --leak-check=full ./$(TARGET)

help:
	cat Makefile
	
clean:
	rm -rf .*swp .*swo *.o $(BINS)


