CC = gcc
CFLAGS=-Wall
DIST = ./dist/
CODE = ./src/c/

library:
	@echo TD: DDN... library

system:
	$(MAKE) library
	$(CC) $(CFLAGS) -o $(DIST)main_system.o -c $(CODE)main_system.c
	$(CC) $(CFLAGS) -o $(DIST)system.bin $(DIST)main_system.o

clean_files:
	@rm -f *_out.txt > /dev/null 2>&1

clean:
	@$(MAKE) clean_files > /dev/null 2>&1
	@rm -f $(DIST)*.o $(DIST)*.exe $(DIST)*.bin $(DIST)*.lib $(DIST)*.so

all:
	$(MAKE) clean
	$(MAKE) system
