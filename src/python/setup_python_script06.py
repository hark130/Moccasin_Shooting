from setuptools import setup, find_packages
import os


def test_running_relative():
    """
        PURPOSE - This function determins if __file__ is being executed from the cwd
        RETURN
            True if Absolute path of __file__ == current working directory
            False otherwise
    """
    # LOCAL VARIABLES
    we_are_here = False  # Prove this wrong

    # DO IT
    # print('File working directory    {}'.format(os.path.dirname(os.path.abspath(__file__))))  # DEBUGGING
    # print('Current working directory {}'.format(os.getcwd()))  # DEBUGGING
    we_are_here = os.path.dirname(os.path.abspath(__file__)) == os.getcwd()

    # DONE
    return we_are_here


def change_cwd_to_this_dir(this_dir):
    """
        PURPOSE - Change the current workiing directory to match this_dir
    """
    # LOCAL VARIABLES
    path = os.getcwd()
    path_to_this_dir = ''

    # VALIDATION
    if not isinstance(this_dir, str):
        raise TypeError('this_dir must be a string')
    elif not this_dir:
        raise ValueError('this_dir can not be empty')
    elif this_dir not in path:
        raise RuntimeError('I will not go hunting for {} in {}'.format(this_dir, path))

    # DO IT
    while True:
        if not path:
            raise RuntimeError('Ran out of directories')
        elif os.path.split(path)[1] == this_dir:
            path_to_this_dir = os.path.join(os.path.split(path)[0], this_dir)
            break
        path = os.path.split(path)[0]

    # DONE
    os.chdir(path_to_this_dir)


def main():
    # LOCAL VARIABLES
    project_name = 'Moccasin_Shooting'
    cwd = os.getcwd()

    # VALIDATION
    if project_name not in cwd:
        raise RuntimeError('The current working directory must be inside {}'.format(project_name))
    else:
        print(os.getcwd())  # DEBUGGING
        change_cwd_to_this_dir(project_name)
        print(os.getcwd())  # DEBUGGING
        os.chdir(os.path.join(os.getcwd(), 'src', 'python'))

    # SETUP
    setup(name='python_script06',
          version='0.1',
          packages=find_packages(),
          author='Joseph Harkleroad',
          author_email='hark130@gmail.com',
          # Module to call on $ python my.egg
          py_modules=['__main__'],
          )


if __name__ == '__main__':
    main()
