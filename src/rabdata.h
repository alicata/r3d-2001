/* Copyright 1996, Viewpoint Datalabs Int'l, www.viewpoint.com, 1-800-DATASET */
/* 
#     Usage Rights:  You (the user) may use this model to help build cool personal
#     vrml worlds, but please give us credit when you do ("3D model provided by
#     Viewpoint Datalabs, www,viewpoint.com").  Please don't sell it or use it to
#     make money indirectly.  Don't redistribute it or put it on a web site except
#     as a part of your personal, non-commerical vrml world.  If you want to do a
#     commercial project, give us a call at 1-800-DATASET or visit www.viewpoint.com
#     and we'll help you obtain the rights to do so.
*/

/*
 *  Note that this data was put directly into the program
 *  to provide a demo program on the net that people could
 *  just run without having to fetch datafiles.  
 *  i.e. more convienent for the user this way
 */


#ifndef RABBIT_DATA_H
#define RABBIT_DATA_H

#define RABBIT_VERTEX_NUM (453) // 12

#define realType double

#include "geom.h"

extern realType rabbit_x[RABBIT_VERTEX_NUM];
extern realType rabbit_y[RABBIT_VERTEX_NUM];
extern realType rabbit_z[RABBIT_VERTEX_NUM];

realType * get_rabbit_xyz();
realType * get_rabbit_x();
realType * get_rabbit_y();
realType * get_rabbit_z();
int get_rabbit_size();
void convertToNativeDataFormat(Skeleton *o); 


#endif
