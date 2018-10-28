from os import listdir
from os.path import isfile, join, dirname

listname = 'dx7patches_list.txt'
dir = dirname(__file__)
path = join(dir, 'dx7patches')
file_list = [f for f in listdir(path) if isfile(join(path, f))]

old_file_list = []
if isfile(join(path, listname)):


with open(listname, 'w') as outfile:
    for item in file_list:
        outfile.write("%s\n" % item)
