#!/usr/bin/env python
# adhesive.py

import subprocess
import re


class a:

    def __init__(self):
        self.bindlist = {}

    def call(self, func, lang, target):
        res = subprocess.check_output(['./adhesive', 'call', func, lang, target])
        return_val = re.search('_ADHESIVERETURN:\({\[(.+)\]}\)', res).group(1)
        return return_val

    def handle(self, argc, args):
        if '___adhescall' in args:
            print 'Hello'

            # an adhesive function must be called

            if not self.bindlist[args[2]]:
                print 'ADHESERROR:(Function not bound)'
            else:
                print '_ADHESIVERETURN:({[' + self.bindlist[args[2]]() + ']})'
                exit()

    def bind(self, bindword, func):
        self.bindlist[bindword] = func
