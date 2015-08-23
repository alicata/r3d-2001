// /////////////////////////////////////////////////
// apperr.h
//
// author:			Aaron Licata
// creation date:	01/09/00
// last modified:	01/09/00
//
// Header file for application error handling

#ifndef APPERROR_H
#define APPERROR_H

// Application errors
#define APPERR_TETRA_ALLOC				"error #1000: application cannot allocatate memory for a new tetrahedron"
#define APPERR_FACE_ALLOC				"error #1010: application cannot allocatate memory for a new face"
#define APPERR_EDGE_ALLOC				"error #1020: application cannot allocatate memory for a new edge"

#define APPERR_INSUFFICIENT_SAMPLE_DENSITY	"error #1100: data cannot be processed because its sample density is insufficient"
#define APPERR_2D_OR_1D_SAMPLES				"error #1110: data cannot be processed because is 2-dimensional or 1-dimensional"



// System Errors
#define SYSERR_NO_ALLOC  "error #2000: system has exhuasted memory resources"

// Application Exit Number
#define APPERR_EXIT_ERROR_NO	1


void AppError(char *);

#endif


