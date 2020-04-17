from setuptools import setup, find_packages
from shutil import copyfile
import os
import sys


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
    project_abs_dir = ''
    cwd = os.getcwd()
    pkg_name = 'python_script06'  # Pass this to setup
    pkg_version = '1.0'  # Pass this to setup
    egg_filename = pkg_name + '-' + pkg_version + '-py' + str(sys.version_info[0]) \
        + '.' + str(sys.version_info[1]) + '.egg'
    generic_egg_filename = pkg_name + '.egg'
    egg_abs_filename = ''  # Define this after determining the project dir
    generic_egg_abs_filename = ''  # Define this after determining the project dir

    # VALIDATION
    if project_name not in cwd:
        raise RuntimeError('The current working directory must be inside {}'.format(project_name))
    else:
        change_cwd_to_this_dir(project_name)
        project_abs_dir = os.getcwd()
        egg_abs_filename = os.path.join(project_abs_dir, 'dist', egg_filename)
        generic_egg_abs_filename = os.path.join(project_abs_dir, 'dist', generic_egg_filename)
        os.chdir(os.path.join(os.getcwd(), 'src', 'python'))

        # SETUP
        setup(name=pkg_name,
              version=pkg_version,
              packages=find_packages(),
              author='Joseph Harkleroad',
              author_email='hark130@gmail.com',
              # Module to call on $ python my.egg
              py_modules=['__main__'],
              )

        # COPY
        copyfile(egg_abs_filename, generic_egg_abs_filename)


if __name__ == '__main__':
    main()
