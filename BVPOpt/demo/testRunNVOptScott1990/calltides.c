/****************************************************************************
	Driver file of the dp_tides program
	This file has been created by MathTIDES (1.20) June 8, 2011, 15:42

	Copyright (C) 2010 A. Abad, R. Barrio, F. Blesa, M. Rodriguez
	Grupo de Mecanica Espacial
	University of Zaragoza
	SPAIN

	http://gme.unizar.es/software/tides
	Contact: <tides@unizar.es>

	This file is part of TIDES.

	TIDES is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	TIDES is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with TIDES.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "scott.h"

void calltides_(int *nvar1, int *npar1, double *p1, double *v1, double *xend, double *outvals) {

	int nvar;
	int npar;
        int nfun = 0;
	int nipt = 2;
	nvar=*nvar1;
	npar=*npar1;


	double v[nvar], p[npar], lt[nipt];
	double tolrel, tolabs;
	double** scott_DataMatrix;
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

	fd = fopen("scottResult.txt", "w");
	Array2DB_init(&scott_DataMatrix, nipt, scott_columns());


/***********************************************************/
/***********************************************************/
/*       CALL THE INTEGRATOR                               */
/***********************************************************/
/***********************************************************/

	dp_tides(scott, nvar, npar, nfun, v, p, 
			lt, nipt, tolrel, tolabs, scott_DataMatrix, fd);


	int sizematr;
//	sizematr=1+nvar+(nvar+npar)*nvar+((nvar+npar)*(nvar+npar+1)*nvar)/2;
	int ngen;
	ngen=nvar+npar;
	sizematr=1+nvar+ngen*nvar+(ngen*(ngen+1)*nvar)/2+(ngen*(ngen+1)*(ngen+2)*nvar)/6;

	for( counter = 0; counter < sizematr; counter++)
	{
		// commented code checks if one derivative is not a number, which could
		// occur, but couldn't be proved otherwise
//		printf("%f\t",scott_DataMatrix[1][counter]);
//		if(!isnan(scott_DataMatrix[1][counter]) && !isnan(-scott_DataMatrix[1][counter]))
			outvals[counter]= scott_DataMatrix[1][counter];
//		else
//			outvals[counter]= 0;
//		printf("%f\n",outvals[counter]);
	}

	fclose(fd); 

	return;
}

