CC=gcc

INC_DIR=../inc

DOX_DIR=../doxy

CFLAGS =-g -Wall -Wextra -pedantic -O0

SRCS = $(wildcard *.c)

BINS = $(SRCS:%.c=%)

TARGET = hashcount

all: clean $(TARGET)

$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) -o $@ $^ -lm

$(DOX_DIR)/index.html: 
	doxygen ../doxy/Doxyfile

run:
	@./$(TARGET) file_streams/input.txt

debug: $(SRCS)
	@$(CC) $(CFLAGS) -o $(TARGET) $^ -lm
	@gdb $(TARGET) 

segfault: $(SRCS)
	ulimit -c unlimited
	$(CC) $(CFLAGS) -o $(TARGET) $^ -lm
	gdb $(TARGET) core 

memleak:
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

help:
	cat Makefile
	
clean:
	rm -rf .*swp .*swo *.o $(BINS) censored_buckets.txt censored_all_except_buckets.txt 


