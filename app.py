from pathlib import Path
import shutil
import files
import os

# filesystem stuff
#   checks if selected files already have a corresponding .cpp file
#   copies selected files and renames copies to filename_old
#   create empty cpp file
# cpp file:
#   iterate header file lines, save current scopes
# header file:
#   remove function bodies

# how to find scopes and function bodies: look for {} and see if this or prev line contain namespace, class or struct
# enhancements: remove comments and preprocessor definitions

#1. copy files (for testing only)

do_testing = True

if do_testing:
    copyPath = Path("D:/Programming/Python_Projects/cpp_from_h/files/testfiles")
    assert(copyPath.exists())
    
    dir = copyPath.parent / "test"
    if not dir.exists():
        os.mkdir(dir)
    for path in dir.glob("*.*"):
        os.remove(path)

    for path in copyPath.glob("*.h"):
        shutil.copy(path, dir / path.name, follow_symlinks=True)

#change these to commandline args
save_old_header = True
srcPath = Path("D:/Programming/Python_Projects/cpp_from_h/files/test") 

assert(srcPath.exists())

for path in srcPath.glob("*.h"):

    if files.get_cpp_path(path).exists():
        continue

    files.create_files_for_header(h = path)
    files.process_header(path)


# creates corresponding files
