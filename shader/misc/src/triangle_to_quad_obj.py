#!/usr/bin/env python

import sys
import os
import re

file = sys.argv[1]
vertex_array = []
face_array = []


class vertex:
    def __init__(self,x=0,y=0,z=0):
        self.x = x
        self.y = y
        self.z = z
        self.faces = []
        self.edge = False

class face:
    def __init__(self):
        self.vertex = []
        self.edge_count = 0
        self.removed =False


def still_have_triangles(vert):
    cnt = 0 
    for face in vert.faces:
        if len(face.vertex)==3:
            cnt +=1
    #/print cnt
    return cnt

def merge_faces(face1,face2):
    upper_array = None
    lower_array = None
    
    new_face_vertex = set()
    sorted_face_points = []
    x_sorted_vertex = []
    y_sorted_vertex = []
    new_face_vertex.update(face1.vertex)
    new_face_vertex.update(face2.vertex)
    new_face_vertex = list(set(new_face_vertex))
    
    
    new_face_vertex.sort(lambda x,y: cmp(x.z,y.z))    
    #print len(y_sorted_vertex)
    
    if new_face_vertex[0].x < new_face_vertex[1].x:
         sorted_face_points.append(new_face_vertex[0])
         sorted_face_points.append(new_face_vertex[1])
    else:
        sorted_face_points.append(new_face_vertex[1])
        sorted_face_points.append(new_face_vertex[0])
    
    if new_face_vertex[2].x < new_face_vertex[3].x:
         sorted_face_points.append(new_face_vertex[2])
         sorted_face_points.append(new_face_vertex[3])
    else:
        sorted_face_points.append(new_face_vertex[3])
        sorted_face_points.append(new_face_vertex[2])
    face1.vertex = sorted_face_points
    

    face2.removed = True
    if face2 in face_array:
        face_array.remove(face2)
    for vert in face1.vertex:
        if face2 in vert.faces:
            vert.faces.remove(face2)
            
def reduce_faces(vert):
    vert_faces = vert.faces
    for face1 in vert_faces:
        #print face1.vertex[0].y
        if len(vert.faces)>1:
            for face2 in vert_faces:
                if face1 != face2:
                    common_vertex_count = 0
                    diff_vertex = [] 
                    for vertex in face2.vertex:
                        if vertex in face1.vertex:
                            common_vertex_count += 1
                        else:
                            diff_vertex.append(vertex)
                    if common_vertex_count > 1:
                        if len(face1.vertex)==3 and len(face2.vertex)==3:
                            if len(diff_vertex)==1:
                                
                                merge_faces(face1,face2)
                                

for line in open(file):
    line = line.rstrip()
    match = re.search("v\s+", line)
    if match:
        v_val = line[match.end():].split()
        vertex_array.append(vertex(float(v_val[0]),float(v_val[1]),float(v_val[2])))
    match = re.search("f\s+", line)
    if match:
        lsplit = line[match.end():].split()
        f = face()
        for v in lsplit:
            vertex_num = int(v.split("/")[0])-1
            vrtx = vertex_array[vertex_num]
            
            f.vertex.append(vrtx)
            vrtx.faces.append(f)
            if f not in face_array:
                face_array.append(f)


for vert in vertex_array:
    #print "%f %f %f %d" %(vert.x,vert.y,vert.z,len(vert.faces))
    if len(vert.faces) == 1 or len(vert.faces) == 2 or len(vert.faces) == 3:
        vert.edge = True
        for f in vert.faces:
            f.edge_count += 1
            
    if len(vert.faces) % 3==0:
        cnt = 1
        reduce_faces(vert)
        
                
        cnt += 1


for v in vertex_array:
    print "v %f %f %f" % (v.x,v.y,v.z) 
    
for face in face_array:
    face_str = "f"
    for v in face.vertex:
        for i in range(len(vertex_array)):
            if vertex_array[i] == v:
                face_str += " %d" % (i+1)
                break
    print face_str
