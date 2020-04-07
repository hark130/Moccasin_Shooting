# Moccasin_Shooting
Test various ways of executing Python from C code.

## Execution

From the Moccasin_Shooting directory:

* `python src/python/python_script01.py`
* `python src/python/python_script02.py`
* `python src/python/python_script03.py`
* `python src/python/python_script04.py`
* `python src/python/setup_python_script05.py bdist_egg --dist-dir dist`; `python dist/python_script05-0.1-py3.6.egg`

## Functional Tests

| Test Number     | Description         | system()        | popen()         | Embedded Python3 | Calling Python from C |
| :-------------: | :------------------ | :-------------: | :-------------: | :-------------: | :-------------: |
| python_script01 | Basic functionality | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script02 | Basic function      | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script03 | Module function     | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script04 | Package function    | :grey_question: | :grey_question: | :grey_question: | :grey_question: |
| python_script05 | Egg distribution    | :grey_question: | :grey_question: | :grey_question: | :grey_question: |

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