import os
import re

#вариант 3

print ('file extension:')
extension = input()
if len(extension) == 0:
    extension = '.*.cpp'
if extension[0] != '.':
    extension = '.'+extension
    
print ('result file:')
res_file = input()
if len(res_file) == 0:
    res_file = 'D:\\file.txt'

found_files = []
for dir_, subdirs, files in os.walk('D:'):
    for f in files:
        if re.search(extension, f):
            found_files.append(f)
            
print(found_files)
    
with open(res_file, 'a') as f:
    f.write('search files {}\n'.format(extension))
    for i in found_files:
        f.write(i + '\n')
    
