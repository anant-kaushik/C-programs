from subprocess import run
from os import listdir, mkdir
import sys

logger = False


def log(str):
    if logger == True:
        print(str)


def setup_bin():
    if 'bin' in listdir():
        log('dir opr: bin exists')
    else:
        mkdir('bin')
        log('dir opr: bin created')


def compile_C_prog(file):
    setup_bin()

    if len(file.split('.')) != 2:
        raise Exception('Invalid file name')

    file_name = file.split('.')[0]
    script = 'clang ' + file + ' -o ' + './bin/' + file_name
    run(script, shell=True)


def run_C_prog(file):
    file_name = file.split('.')[0]
    script = './bin/' + file_name
    run(script, shell=True)


def compile_run_C(file):
    run('clear', shell=True)
    compile_C_prog(file)
    run_C_prog(file)


if __name__ == "__main__":
    args = sys.argv

    if '--log' in args:
        logger = True

    compile_run_C(args[1])

# python3 runner.py FILE_NAME.c
