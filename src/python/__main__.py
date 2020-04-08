"""
    PURPOSE - The most basic of package-based
    DETAILS - A package-defined function from within an .egg
"""

from python_package.python_package import main


def eggsecute():
    print(f'Executing eggsecute()')
    main('python_script05.py')


if __name__ == '__main__':
    print(f'Executing __main__.py\n{__file__}')
    eggsecute()
