// //////////////////////////////////////////////////////////
// file name: filept2.cpp
// author:		Aaron Licata
// creation date:	28/02/01
// last modified:	28/02/01
// version number	1
//
// description: file i/o module implementation for pt2 format
//
// //////////////////////////////////////////////////////////

#include "config.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include "geom.h"
#include "rabdata.h"
#include "filept2.h"



// ///////////////////////////////////////////////////////////
// function: PT2ReadFirstToken()
//
// creation date:	27/02/01
// last modified:	27/02/01
// purpose: read the first token from a file pointer. It is 
// assumed to be an integer
//
// arguments: fp file pointer
//            destination buffer for token 
//
// return value: none
// ///////////////////////////////////////////////////////////

void PT2ReadFirstToken(FILE *fp, char *token)
{
	int i = 0;

	while ((token[i] = fgetc(fp)) != '\n')
	{
		i++;
	}
	token[i] = '\0';
}



// ///////////////////////////////////////////////////////////
// function: PT2ReadNextLine()
//
// creation date:	27/02/01
// last modified:	27/02/01
// purpose: read in a line from a file pointer an save result 
// in three token buffers. It is assumed that a line is made 
// of three tokens for x,y,z coordinates. 
//
// arguments: file pointer 
//            three destination token buffers 
//
// return value: none
// ///////////////////////////////////////////////////////////

void PT2ReadNextLine(FILE *fp, char *token1, char *token2, char *token3)
{

	int i = 0;
  
	while ((token1[0] = fgetc(fp)) == ' ' || token1[0] == '\t');
	i = 1;
	while ((token1[i] = fgetc(fp)) != ' ')
	{
		i++;
	}
	token1[i] = '\0';

	while ((token2[0] = fgetc(fp)) == ' ' || token2[0] == '\t');
	i = 1;
	while ((token2[i] = fgetc(fp)) != ' ')
	{
		i++;
	}
	token2[i] = '\0';

	while ((token3[0] = fgetc(fp)) == ' ' || token3[0] == '\t');
	i = 1;
	while ((token3[i] = fgetc(fp)) != '\n')
	{
		i++;
	}
	token3[i] = '\0';

}



// ///////////////////////////////////////////////////////////
// function: PT2ReadFile()
//
// creation date:	27/02/01
// last modified:	27/02/01
// purpose: open and read a file of format pt2. Stores result in
// a vertex array
//
// arguments: filename to open and read in
//            object holding the vertex array 
//
// return value: 1 success, 0 failure
// ///////////////////////////////////////////////////////////

int PT2ReadFile(const char *filename, Skeleton *o)
{

	char token[20];
	
	memset(&token[0], 20, sizeof(char));

	if (!o) return 0;
	
	AppOutN("reading file ");

        FILE *fp = fopen(filename, "r");
	if (!fp) return 0;

	PT2ReadFirstToken(fp, token);
	o->vertCount = atoi(token);
	AppOut("number of points : ");
	AppOutN(o->vertCount);

	o->vert = new Vertex3 [o->vertCount+4];

	AppOutN("reading point coordinates");
	char token1[220];
	char token2[220];
	char token3[220];
	double mx = 0;
	double my = 0;
	double mz = 0;

	int count = 0;
	while (count < o->vertCount)
	{
		PT2ReadNextLine(fp, token1, token2, token3);
		o->vert[count].x = atof(token1);
		o->vert[count].y = atof(token2);
		o->vert[count].z = atof(token3);
		if (o->vert[count].x > mx) mx = o->vert[count].x;
		if (o->vert[count].y > my) my = o->vert[count].y;
		if (o->vert[count].z > mz) mz = o->vert[count].z;

		AppOut(count); AppOut(" ");
		AppOut(o->vert[count].x); AppOut(" "); 
		AppOut(o->vert[count].y); AppOut(" "); 
		AppOut(o->vert[count].z); AppOut(" "); 
		AppEndl();

		count++;	
	}
	AppOutN("finished reading file");
	
	AppOutN("normalizing coordinates");
	double max;
	if (mx > my)
		max = mx;
	else
		max = my;

	if (max < mz) max = mz;
	
	for (int j=0; j < o->vertCount; j++)
	{
		o->vert[j].x /= max;
		o->vert[j].y /= max;
		o->vert[j].z /= max;

	}

	return 1;
}


