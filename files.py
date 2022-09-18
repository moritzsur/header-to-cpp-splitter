from io import TextIOWrapper
from pathlib import Path
import shutil
import processing

def save_old_header(path):
    pass

def get_cpp_path(h):
    cppName = h.stem + ".cpp"
    return h.parent / cppName

def create_files_for_header(h):
    with open(get_cpp_path(h), "w") as cppFile:
        cppFile.write("//this cpp file was auto generated")

    targetName = h.stem + "_old.h"
    shutil.copy(h, h.parent / targetName, follow_symlinks=True)

def process_header(path):
    hLines = []
    cppLines = []
    with open(path, "r") as file:
        hLines = file.readlines()
        
    out = processing.process_raw_lines(hLines, cppLines)
    hLines = out[0]
    cppLines = out[1]

    with open(path, "w") as file:
        file.truncate(0)
        file.writelines(hLines)

    with open(get_cpp_path(path), "w") as file:
        file.writelines(cppLines)

        