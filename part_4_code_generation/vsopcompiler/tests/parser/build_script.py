"""
Simple python script to build a script to run all the tests inside the folder.
"""

import os
import os.path

if __name__ == '__main__':
    script = open("run.sh", "w")

    files = os.listdir(".")
    print(files)
    for file in files:
        if file.endswith(".vsop"):
            script.write("echo\n")
            script.write("echo \* Testing " + file + " \*\n")
            script.write("./vsopc -p tests/parser/"+file+"\n")

    script.close()
