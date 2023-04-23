import sys
import subprocess


if __name__ == '__main__':
    subprocess.check_call([sys.executable] + sys.argv[1:])
