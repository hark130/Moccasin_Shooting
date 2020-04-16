BUILD = ./build/
CC = gcc
CFLAGS = -Wall
C_CODE = ./src/c/
DIST = ./dist/
PYTHON_CODE = ./src/python/

library:
	$(MAKE) egg_layer
	$(MAKE) command_cat

egg_layer:
	# NOTE: I was unable to get the "egg layer" script (inside a Makefile recipe) to work any other way than this!
	$(eval CUR_DIR=$(shell sh -c "pwd"))
	python3 $(PYTHON_CODE)setup_python_script06.py bdist_egg --dist-dir=$(CUR_DIR)/dist --bdist-dir=$(CUR_DIR)/build

command_cat:
	$(CC) $(CFLAGS) -o $(DIST)MOSH_Command_Cat.o -c $(C_CODE)MOSH_Command_Cat.c

# This recipe's input/notes/code take from:
#	https://www.linuxjournal.com/article/8497
# To link your application to the Python interpreter at compile time, you should run the python-config program to get
# a list of the linking options that should be passed to the compiler. On my system, those are:
# -lpython2.3 -lm -L/usr/lib/python2.3/config
linux_journal:
	# Original Python2.2 modified for Python2.7
	$(CC) $(CFLAGS) -o $(DIST)linux_journal.o -c $(C_CODE)linux_journal_code.c
	$(CC) $(CFLAGS) -o $(DIST)linux_journal.bin $(DIST)linux_journal.o -lpython2.7
	# Original Python2.2 modified for Python3.6
	$(CC) $(CFLAGS) -o $(DIST)linux_journal3.o -c $(C_CODE)linux_journal_code_python3.c
	$(CC) $(CFLAGS) -o $(DIST)linux_journal3.bin $(DIST)linux_journal3.o -lpython3.6m

system:
	$(MAKE) clean_files
	$(MAKE) library
	$(CC) $(CFLAGS) -o $(DIST)main_system.o -c $(C_CODE)main_system.c
	$(CC) $(CFLAGS) -o $(DIST)system.bin $(DIST)MOSH_Command_Cat.o $(DIST)main_system.o

popen:
	$(MAKE) clean_files
	$(MAKE) library
	$(CC) $(CFLAGS) -o $(DIST)main_popen.o -c $(C_CODE)main_popen.c
	$(CC) $(CFLAGS) -o $(DIST)popen.bin $(DIST)MOSH_Command_Cat.o $(DIST)main_popen.o

clean_files:
	@rm -f *_out.txt > /dev/null 2>&1

clean:
	@$(MAKE) clean_files > /dev/null 2>&1
	@rm -f $(DIST)*.o $(DIST)*.exe $(DIST)*.bin $(DIST)*.lib $(DIST)*.so $(DIST)*.egg

all:
	$(MAKE) clean
	$(MAKE) system
