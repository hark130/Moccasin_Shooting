# Moccasin_Shooting
Test various methods of executing Python3 from C code in Linux.

## METHODS

1. [system()](http://man7.org/linux/man-pages/man3/system.3.html)
2. [popen()](http://man7.org/linux/man-pages/man3/popen.3.html)
3. [Embedding Python in Your C Programs](https://www.linuxjournal.com/article/8497)
4. [Calling Python from C](https://www.geeksforgeeks.org/calling-python-from-c-set-1/)
5. [Extending and Embedding the Python Interpreter](https://docs.python.org/3/extending/)

## EXECUTION

From the Moccasin_Shooting directory:

`./devops/scripts/basic_run.sh`

**-OR-**

* `python3 src/python/python_script01.py -c src/python/test_files/python_script01_in.txt`
* `python3 src/python/python_script02.py -c src/python/test_files/python_script02_in.txt`
* `python3 src/python/python_script03.py -c src/python/test_files/python_script03_in.txt`
* `python3 src/python/python_script04.py -c src/python/test_files/python_script04_in.txt`
* `python3 src/python/python_package/ -c src/python/test_files/python_script05_in.txt`
* Build the egg, then "eggsecute" it
	* `python3 src/python/setup_python_script06.py bdist_egg --dist-dir=dist --bdist-dir=build`
	* `python3 dist/python_script06.egg -c src/python/test_files/python_script06_in.txt`

## RUN TESTS

From the `Moccasin_Shooting` directory:

`devops/scripts/run_tests.sh`

## TEST RESULTS

| Test Number     | Description         | 1. system()        | 2. popen()         | 3. Python/C API    | 4. Calling Python from C | 5. Embedding the Python Interpreter |
| :-------------: | :------------------ | :----------------: | :----------------: | :----------------: | :-------------: | :-------------: |
| python_script01 | Basic functionality | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :grey_question: | :grey_question: |
| python_script02 | Basic function      | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :grey_question: | :grey_question: |
| python_script03 | Module function     | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :grey_question: | :grey_question: |
| python_script04 | Package function    | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :grey_question: | :grey_question: |
| python_script05 | Package execution   | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :grey_question: | :grey_question: |
| python_script06 | Egg execution       | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :grey_question: | :grey_question: |

**LEGEND**

| Emoji              | Meaning                                    |
| :----------------: | :----------------------------------------- |
| :anger:            | False positive, misleading/missing results |
| :boom:             | Seg fault or core dump                     |
| :grey_question:    | Test not yet executed                      |
| :heavy_check_mark: | Test passed                                |
| :x:                | Test failed                                |

NOTE:

	- [Calling Python from C](https://www.geeksforgeeks.org/calling-python-from-c-set-1/)
	- Egg execution (see: python_script06) is the end requirement.  Everything prior is just a stepping stone.

## CODE REVIEW

### Python Code

From the Moccasin_Shooting directory:

* `pycodestyle --max-line-length=100 .`

### C Code

* valgrind --leak-check=full --track-origins=yes --tool=memcheck --child-silent-after-fork=yes --error-exitcode=1 --trace-children=yes dist/system.bin echo test
* valgrind --leak-check=full --track-origins=yes --tool=memcheck --child-silent-after-fork=yes --error-exitcode=1 --trace-children=yes dist/popen.bin echo test
