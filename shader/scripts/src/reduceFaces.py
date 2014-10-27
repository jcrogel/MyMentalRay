#!/usr/bin/env python


import os
import sys

face_list=[]

    
if __name__ == "__main__":
    for line in open(sys.argv[1]):
        if line.startswith("f "):
            line_split = line.split()
            face = []
            for item in line_split:
                if item.find("/")>-1:
                    vertex = item.split("/")[0]            
                    face.append(vertex)
            face_list.append(face) 
            

    for vertex in face_list:
        for vert in face_list:
            diff = set(vert)-set(vertex)
            if len(diff) == 1:                
                if len(vertex)==3:                              
                    for diff_item in diff:
                        vertex.append(diff_item)                
                    face_list.remove(vert)
                elif len(vert)==3:
#                    for diff_item in diff:
#                        vert.append(diff_item)                                    
#                    face_list.remove(vertex)
                    pass
                
    for line in open(sys.argv[1]):
        if line.startswith("f "):
            for face in face_list:
                face_str = ""
                for item in face:
                     face_str += " " + str(item)
                print "f " + face_str
        else:
            print line.strip().rstrip()


class vertex:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0
    

class face:
    def __init__(self):
        self.vertices = []
        
    
    
        
