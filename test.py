#!/usr/bin/env python
# test.py

import sys
import time
import adhesive as adhes


def other_thing():
    return 'hello?'


adhesiv = adhes.a()
adhesiv.bind('other_thing', other_thing)
adhesiv.handle(len(sys.argv), sys.argv)
start = time.time()

for i in range(0, 100):
    print adhesiv.call('thing', 'cpp', 'test')
    
end = time.time()
tm = end - start
print 'Took ' + str(tm)
start = time.time()

for i in range(0, 100):
    print 'Hello'

end = time.time()

print 'Took ' + str(end - start)
print 'it takes ' + str(tm - (end - start)) \
    + ' seconds longer through Adhesive API'
