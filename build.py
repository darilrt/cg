# version: 1.0

import subprocess
import sys
import os

# CC CONFIGURATION ------------------------
CC = "g++"

OPTIONS = [
    "-I./include/",
    "-L./lib/",
    "-DGLEW_STATIC",
    "-std=c++17",
    # "-O3",
    # "-mwindows"
]

LIBS = [
    "glew32s",
    "glu32",
    "opengl32",
    "mingw32",
    "SDL2main",
    "SDL2",
    "ws2_32",
]

NAME = "main.exe"
# CC CONFIGURATION ------------------------

def compile(file_path):
    print("compiling {file}".format(file=file_path))
    
    obj_path = "./obj" + file_path[5:-4] + ".o"
    
    ret = os.system("{CC} {libs} -c {in_file} {options} -o {out_file}".format(
        CC=CC,
        options=" ".join(OPTIONS),
        libs=" ".join(["-l" + l for l in LIBS]),
        out_file=obj_path,
        in_file=file_path,
    ))
    
    return ret

def get_file_recursive_and_timestamp(PATH):
    return {l: str(os.path.getmtime(l)) for l in [os.path.join(dp, f).replace("\\", "/") for dp, dn, filenames in os.walk(PATH) for f in filenames if os.path.splitext(f)[1] == '.cpp']}

def get_tmp():
    if not os.path.exists(".tmp"):
        open(".tmp", "w+").close();
    
    with open(".tmp") as f:
        data = f.readlines()
        
        return {line.split()[0]: line.split()[1] for line in data}

file_data = get_file_recursive_and_timestamp("./src/")
tmp_data = get_tmp()

if not os.path.exists("obj"):
    os.mkdir("obj")

if not os.path.exists("bin"):
    os.mkdir("bin")

if os.path.exists("bin/" + NAME):
    os.remove("bin/" + NAME)
tmp_lines = []
build_list = []

for file, sm in file_data.items():
    if not os.path.exists(os.path.dirname("./obj" + file[5:])):
        os.makedirs(os.path.dirname("./obj" + file[5:]))
    
    if "rebuild" in sys.argv:
        if compile(file) == 0:
            tmp_lines.append("{} {}\n".format(file, sm))
        
        else:
            exit()
    
    elif not file in tmp_data or (file in tmp_data and tmp_data[file] != sm):
        if compile(file) == 0:
            tmp_lines.append("{} {}\n".format(file, sm))
            
        else:
            exit()
        
    else:
        if not os.path.exists("./obj" + file[5:-4] + ".o"):
            if compile(file) == 0:
                tmp_lines.append("{} {}\n".format(file, sm))
            
            else:
                exit()
            
        else:
            tmp_lines.append("{} {}\n".format(file, sm))
    
    build_list.append("./obj" + file[5:-4] + ".o")

os.system("{CC} -o bin/{name} {objects} {options} {lib}".format(
    CC=CC,
    lib=" ".join(["-l" + l for l in LIBS]),
    name=NAME,
    objects=" ".join(build_list),
    options=" ".join(OPTIONS)
))

tmp_file = open(".tmp", "w+")
tmp_file.write("".join(tmp_lines))
tmp_file.close()

if "run" in sys.argv:
    if os.path.exists("bin/" + NAME):
        subprocess.call(['./bin/{}'.format(NAME)])
