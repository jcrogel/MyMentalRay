#!/usr/bin/env python

import getopt
import os
import sys




class MayaRender:
    def __init__(self):
        self.mayafile = ""
        self.MAYA_PATH = "/Applications/Autodesk/maya2008/Maya.app/Contents/"    
        self.RENDER_MEL = "~/Documents/workspace/Render/Render.mel"
        self.MAYA_APPS = MAYA_PATH + "bin/"
        self.outputPath = ""
        self.outputPrefix = ""
        self.outputFormat = ""
        
    
    def setMayaFile(self,file):
        self.mayafile = file

    def setoutputPath(self,path):
        self.outputPath = path
        
    def setFilePrefix(self,name):
        self.outputPath = ""
        
    
    def render(self):
        cmd = self.MAYA_APPS+"maya "
        print cmd 
        for line in  os.popen(cmd):
            print line


def printhelp():
    print """
        Usage: Render 
    """;
    sys.exit()

def getoptions():
    try:
        opts,args = getopt.getopt(sys.argv[1:],"ho:v",["help",""])
    except:
        print str(err)
        printhelp()


if __name__ == "__main__":
    getoptions()
    

    fcheck_cmd  = "fcheck " 