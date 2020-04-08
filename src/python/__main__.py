"""
    PURPOSE - The most basic of package-based
    DETAILS - A package-defined function from within an .egg
"""

from python_package.python_package import main


def eggsecute():
    main('python_script06.py')


if __name__ == '__main__':
    print(f'Executing __main__.py\n{__file__}')
    eggsecute()
