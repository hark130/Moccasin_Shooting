from setuptools import setup, find_packages
import os


def main():
    script05_path = os.path.join("..", "..", "src", "python", "python_hw_package")
    setup(name="python_script05",
          version="0.1",
          packages=find_packages(where=script05_path),
          author = "Joseph Harkleroad",
          author_email = "hark130@gmail.com"
          )


if __name__ == "__main__":
    main()
