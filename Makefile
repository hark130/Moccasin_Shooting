BUILD = ./build/
CC = gcc
CFLAGS = -Wall
C_CODE = ./src/c/
DIST = ./dist/
PYTHON_CODE = ./src/python/

library:
	$(MAKE) egg_layer

egg_layer:
	# NOTE: I was unable to get the "egg layer" script (inside a Makefile recipe) to work any other way than this!
	$(eval CUR_DIR=$(shell sh -c "pwd"))
	python3 $(PYTHON_CODE)setup_python_script06.py bdist_egg --dist-dir=$(CUR_DIR)/dist --bdist-dir=$(CUR_DIR)/build

system:
	$(MAKE) clean_files
	$(MAKE) library
	$(CC) $(CFLAGS) -o $(DIST)main_system.o -c $(C_CODE)main_system.c
	$(CC) $(CFLAGS) -o $(DIST)system.bin $(DIST)main_system.o

popen:
	$(MAKE) clean_files
	$(MAKE) library
	$(CC) $(CFLAGS) -o $(DIST)main_popen.o -c $(C_CODE)main_popen.c
	$(CC) $(CFLAGS) -o $(DIST)popen.bin $(DIST)main_popen.o

clean_files:
	@rm -f *_out.txt > /dev/null 2>&1

clean:
	@$(MAKE) clean_files > /dev/null 2>&1
	@rm -f $(DIST)*.o $(DIST)*.exe $(DIST)*.bin $(DIST)*.lib $(DIST)*.so $(DIST)*.egg

all:
	$(MAKE) clean
	$(MAKE) system
