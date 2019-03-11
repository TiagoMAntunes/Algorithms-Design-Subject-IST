import os, sys, re
from pprint import pprint
 
def header_parse(filepath):
    functionmatcher = re.compile('\w+ \w+\((\s*[a-zA-Z_\(\)\*]+\s+[a-zA-Z_\(\)\*]+\s*(,\s*[a-zA-Z_\(\)\*]+\s+[a-zA-Z_\(\)\*]+\s*)*)\);')  #if it works, it ain't stupid
    structbeginmatcher = re.compile('\s*(typedef){0,1}\s*struct\s*\w+\s*{')
    structendmatcher = re.compile('\s*}\s*[\*]*\s*\w+;')
    definematcher = re.compile('#define\s+\w+\s+\w+')
    headers = []
    structs = []
    defines = []
    with open(filepath) as f:
        lines = f.readlines()
        i = 0
        while i < len(lines):
            line = lines[i]
            if functionmatcher.match(line):
                headers.append(line)
            elif definematcher.match(line):
                defines.append(line)
            elif structbeginmatcher.match(line):
                data = line
                i+=1
                line = lines[i]
                while not structendmatcher.match(line):
                    data += line
                    i += 1
                    line = lines[i]
                data+=line
                structs.append(data)
            i+=1
            
    return (headers,structs,defines)
 
def bubbleSort(alist, cmpfn):
    for passnum in range(len(alist)-1,0,-1):
        for i in range(passnum):
            if cmpfn(alist[i],alist[i+1]):
                temp = alist[i]
                alist[i] = alist[i+1]
                alist[i+1] = temp

def content_parse(filepath):
    definematcher = re.compile('#define\s+\w+\s+\w+')
    includematcher = re.compile('#include\s+<.*>')
    includes = []
    defines = []
    functionbodies = []
    with open(filepath) as f:
        lines = f.readlines()
        for line in lines:
            if includematcher.match(line):
                includes.append(line)
            elif definematcher.match(line):
                includes.append(line)
            elif '#include' not in line:
                functionbodies.append(line)
    return includes, defines, functionbodies

if __name__ == '__main__':
    headers = []
    contents = []

    headerpat= re.compile('.*\.h')
    contentpat = re.compile('.*\.c')
    
    files_directories = sys.argv[1:]
    for dir in files_directories:
        #enter folders
        files = os.listdir(dir)
        #check if each file is relevant
        for file in files:
            if headerpat.match(file):
                headers.append(os.path.join(dir, file))
            elif contentpat.match(file):
                contents.append(os.path.join(dir,file))
   
    f = open('production.c', 'w+')
    files_headers = []
    structs = []
    defines = []
    files_contents = []

    
    for file in headers:
        h, s, d = header_parse(file)
        files_headers += h
        structs += s
        defines += d
    includes = []
    functionbodies = []
    for file in contents:
        i, d, fb = content_parse(file)
        includes += i
        defines += d
        functionbodies += fb

    structs_adts = []
    for struct in structs:
        structs_adts.append((struct.split(' ')[-1][:-2],struct))

    bubbleSort(structs_adts, lambda x,y: True if x[0] not in y[1] else False)
    structs = [x[1] for x in structs_adts]

    f.write(''.join(set(includes)))
    f.write(''.join(set(defines)))
    f.write(''.join(structs))
    f.write(''.join(files_headers))
    f.write(''.join(functionbodies))

    print('New file generated. Name: ' + 'production.c')