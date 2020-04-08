# Moccasin_Shooting
Test various ways of executing Python from C code.

## Execution

From the Moccasin_Shooting directory:

`./devops/scripts/basic_run.sh`

**-OR-**

* `python src/python/python_script01.py -c src/python/test_files/python_script01_in.txt`
* `python src/python/python_script02.py -c src/python/test_files/python_script02_in.txt`
* `python src/python/python_script03.py -c src/python/test_files/python_script03_in.txt`
* `python src/python/python_script04.py -c src/python/test_files/python_script04_in.txt`
* `python src/python/python_package/ -c src/python/test_files/python_script05_in.txt`
* Build the egg, then "eggsecute" it
	* `python src/python/setup_python_script06.py bdist_egg --dist-dir=dist --bdist-dir=build`
	* `python dist/python_script06-0.1-py3.6.egg -c src/python/test_files/python_script06_in.txt`

## Functional Tests

| Test Number     | Description         | system()        | popen()         | Embedded Python3 | Calling Python from C |
| :-------------: | :------------------ | :-------------: | :-------------: | :-------------: | :-------------: |
| python_script01 | Basic functionality | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script02 | Basic function      | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script03 | Module function     | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script04 | Package function    | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script05 | Package execution   | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script06 | Egg execution       | :grey_question: | :grey_question: | :grey_question: | :grey_question: |

**LEGEND**

| Emoji              | Meaning                                    |
| :----------------: | :----------------------------------------- |
| :anger:            | False positive, misleading/missing results |
| :boom:             | Seg fault or core dump                     |
| :grey_question:    | Test not yet executed                      |
| :heavy_check_mark: | Succeeded in finding the error             |
| :x:                | Failed to find the error                   |

NOTE:
	- [Calling Python from C](https://www.geeksforgeeks.org/calling-python-from-c-set-1/)
	- Egg execution (see: python_script06) is the end requirement.  Everything prior is just a stepping stone.
