#!/usr/bin/python3
import glob
import os

files = glob.glob("./**/*.cpp", recursive=True)
heard_files = glob.glob("./**/*.h", recursive=True)

files.extend(heard_files)

# 如果路径中包含 deps/3rd 则不进行格式化
files = [i for i in files if "deps/3rd" not in i]

# 如果路径中包含 sql/parser 则不进行格式化
files = [i for i in files if "sql/parser" not in i]

for i in files:
    os.system(f"clang-format --style=file -i \"%s\"" % i)

print(f"format %d files" % len(files))
