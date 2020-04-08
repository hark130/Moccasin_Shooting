"""
    PURPOSE - The most basic of package-based
    DETAILS - A package-defined function from within an .egg
"""

from python_package import main

print("test")

def eggsecute():
    main('python_script05.py')


if __name__ == '__main__':
    eggsecute()
