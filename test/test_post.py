#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
    <+ MODULE_NAME +>

    <+ DESCRIPTION +>

    Licensed under the <+ LICENSE +> license, see <+ X +> for more details etc.
    Copyright by yueyang
"""

import httplib
import urllib
import time

def post(url, params):
    conn = None
    conn = httplib.HTTPConnection(url)
    path = '/post'
    method = 'POST'
    try:
        conn.request(method, path, params)
    except:
        print "post: socket error"
        return
    try:
        rc = conn.getresponse()
    except:
        print "error"
        return

    buf = rc.read()
    print rc.status, rc.reason, buf

if __name__ == '__main__':
    print "POST: /post"
    import os
    os.system('cp test_sp1.py /tmp')
    os.system('cp test_sp2.py /tmp')
    if (not (os.path.exists('/tmp/test'))):
        os.system("mkdir /tmp/test")

    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp2.py')
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp.py')
    time.sleep(1)
    post('192.168.142.1:8888', '/usr/bin/python,python,/tmp/test_sp1.py')
