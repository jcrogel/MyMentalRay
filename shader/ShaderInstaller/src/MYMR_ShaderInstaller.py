#!/usr/bin/env python

import os
import sys
from maya import cmds
import xml.dom.minidom
import getopt

#def findFile(so_file):
#    grp = so_file.split("|")[0]
#    cmds.textFieldButtonGrp(grp,label="here")
#    file = cmds.fileDialog(m=0)
#    print file
#
#window= cmds.window(title="MyMR ShaderInstaller",widthHeight=(500, 500),backgroundColor=(.33,.33,.33))
#cmds.columnLayout( adjustableColumn=True )
#sofile = cmds.textFieldButtonGrp( label='Compiled File (.so or .dll)' ,buttonLabel="...",buttonCommand="findFile(sofile)")
#cmds.textFieldButtonGrp( label='Mi File' )
#cmds.textFieldButtonGrp( label='XPM Icon' )
#
#
#cmds.checkBox( label='Link Files instead of Copying them (useful for shader writers)' )
#cmds.button( label='Install Shader' )
#cmds.setParent( '..' )
#cmds.showWindow( window )



class ShaderInstall:
    def __init__(self):
        self.melScript = []
        self.soFile = []
        self.xpmFile = []
        self.miFile = []
        self.link = False
    
    def Install(self):
        pass
    
    def checkFiles(self):
        pass

                
    

def usage():
    print """Shader Installer:
        By Juan Carlos Moreno jcarlos@mymentalray.com
        Usage: shaderinstall [options] 
        
        Options:
            -h, -help        Displays this message
            -m, -mifile  <file>  Mental Ray Interface file
            -x, -xpmicon <file>
            -l, -library <file>  
            -s, -melscript <file>
            -d, --sourcedir
            
    """
    
    
if __name__ == "__main__":
    si = ShaderInstall()
    try:
        opts,args = getopt.getopt(sys.argv[1:], "hm:x:l:s:L", ["help","mifile=","xpmicon=","library=","melscript=","softLink"])
    except getopt.GetoptError, err:
        print str(err)
        usage()
        sys.exit()
    
    for o,a in opts:
        if o in ["-h","--help"]:
            usage()
            sys.exit()
            
        if o in ["-m","--mifile"]:
            si.miFile.append(a)
            
        if o in ["-x","--xpmicon"]:
            si.xpmFile.append(a)

        if o in ["-l","--library"]:
            si.soFile.append(a)        
        
        if o in ["-s","--melscript"]:
            si.melScript.append(a)                  

        if o in ["-L","--softLink"]:
            si.link = True            
        