#!/usr/bin/env python


import os
import sys
import getopt

class mkscript:
    def __init__(self,name):
        self.name = name
    
    def create(self):
        template = "mkscript_template"
        

def print_help():
    print """
    mkscript -h
    
    """  
    
if __name__ == "__main__":
    try:
        opts, args = getopt.gnu_getopt( sys.argv[1:], "hn", ["help","name="] )
    except getopt.GetoptError:
        print "I didn't understand some options you gave..."
        print_help()
        sys.exit( 2 )

    for o, a in opts:
        if o in ( "-h", "--help" ):
            print_help()  
            sys.exit(0)  
    
    cobj = mkscript()
    mkscript.create()