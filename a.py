#!/usr/bin/python
#-*- coding:utf-8 -*-
import sys
import os
r = lambda: sys.stdin.readline()

def replaceFourSpaceToTab(s):
    ret = ""
    lst = s.split('    ')
    ok = True

    for w in lst:
        if w == '':
            if ok:
                ret = ret + '\\t'
        else:
            ok = False
            ret = ret + w
    return ret

print 'input filename'
filename = str(r()).replace("\n",'')

if not os.path.exists('code/'+filename):
    print 'the file is not exist'
    exit(-1)

codes = []
with open('code/'+filename,'r') as fp:
    codes = fp.readlines()

res = []
for code in codes:
    now = replaceFourSpaceToTab(code)
    now = now[:-1]+'\\n'
    now = "\""+now+"\""
    res.append(now)

print 'converting success!'

print "Input keyword"
key = str(r()).replace('\n','')
key = "\'"+key+"\'"

print "Input output filename"
output_filename = str(r()).replace('\n','')

with open('result/'+output_filename,'w') as fp:
    isFirst = True
    for line in res:
        if isFirst:
            print '\\\t\t'+key+': '+line
            fp.write('\\\t\t'+key+': '+line)
            fp.write('\n')
            isFirst = False
        else:
            if line == res[-1]:
                print '\\\t\t\t.'+line+','
                fp.write('\\\t\t\t.'+line+',')
                fp.write('\n')
            else:
                print '\\\t\t\t.'+line
                fp.write('\\\t\t\t.'+line)
                fp.write('\n')
