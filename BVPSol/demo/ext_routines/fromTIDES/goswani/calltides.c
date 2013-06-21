#include <stdio.h>
#include <stdlib.h>
#include "goswani.h"

void calltides_(int *nvar1, int *npar1, double *p1, double *v1, double *xend, double *outvals) {

	int nvar = 4;
	int npar = 2;
	int nfun = 0;
	int nipt = 2;
	nvar=*nvar1;
	npar=*npar1;
	
	double v[nvar], p[npar], lt[nipt];
	double tolrel, tolabs; 
	double** goswani_DataMatrix;
	FILE   *fd;


/************************************************************/
/************************************************************/
/*     INITIAL CONDITIONS, INTEGRATION TIMES, TOLERANCES    */
/************************************************************/
/************************************************************/

/* --- PARAMETERS VALUE --- */
	int counter;
	for( counter = 0; counter < npar; counter++)
	{
	  p[counter]= p1[counter];
	}

/* --- INITIAL VALUES --- */
	for( counter = 0; counter < nvar; counter++)
	{
	  v[counter]= v1[counter];
	}

/* ---     INTEGRATION POINTS    --- */
	lt[0] = 0 ;
	lt[1]=*xend;

/* --- REQUIRED TOLERANCES --- */
	tolrel = 1.e-16 ;
	tolabs = 1.e-16 ;

/***********************************************************/
/***********************************************************/
/*        OUTPUT: file   &data matrix                     */
/***********************************************************/
/***********************************************************/

	fd = fopen("goswaniResult.txt", "w");
	Array2DB_init(&goswani_DataMatrix, nipt, goswani_columns());


/***********************************************************/
/***********************************************************/
/*       CALL THE INTEGRATOR                               */
/***********************************************************/
/***********************************************************/

	dp_tides(goswani, nvar, npar, nfun, v, p, 
			lt, nipt, tolrel, tolabs, goswani_DataMatrix, fd);
	
	///// TRANSLATE OUTPUT INTO FORTRAN

	int sizematr;
        int ngen;
	ngen=nvar+npar;
	sizematr=1+nvar+ngen*nvar+(ngen*(ngen+1)*nvar)/2+(ngen*(ngen+1)*(ngen+2)*nvar)/6;

	for( counter = 0; counter < sizematr; counter++)
	{
		outvals[counter]= goswani_DataMatrix[1][counter];
	}


	fclose(fd); 

	return;
}


