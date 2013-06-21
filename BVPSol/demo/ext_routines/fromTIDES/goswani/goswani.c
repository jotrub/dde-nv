/****************************************************************************
	This file has been created by MathTIDES (1.20) June 13, 2013, 11:46

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

#include "goswani.h"


long  goswani(realNUM t, realNUM v[], realNUM p[], int ORDER, realNUM cvfd[][ORDER+1])
{
	static int   VARIABLES        = 4;
	static int   PARAMETERS       = 2;
	static int   FUNCTIONS        = 0;
	static int   LINKS            = 97;
	static int   PARTIALS_VARS    = 6;
	static long  NUM_DERIVATIVES  = 84;
	static long  NUM_COLUMNS      = 336;

	static int   POS__PARTIALS[6] = {1,2,3,4,5,6};
	static int   POS_FUNCTIONS[1] = {0};

	static long  POS_ACCUM[85] = {0,1,3,5,7,9,11,13,16,20,24,28,32,36,39,43,47,51,55,58,62,66,70,73,77,81,84,88,91,95,101,107,113,119,125,131,139,147,155,163,169,177,185,193,199,207,215,221,229,235,239,245,251,257,263,269,277,285,293,299,307,315,321,329,335,339,345,351,357,363,371,379,385,393,399,403,409,415,421,429,435,439,445,451,455};
	static long  POS_COEFS[455] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,3,3,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,3,3,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,3,3,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,3,3,1,1,1,2,2,1,1,1,1,2,2,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,3,3,1,1,1,2,2,1,1,1,2,1,1,2,1,1,3,3,1};
	static long  POS_PREVI[455] = {0,0,1,0,2,0,3,0,4,0,5,0,6,0,1,7,0,2,1,8,0,3,1,9,0,4,1,10,0,5,1,11,0,6,1,12,0,2,13,0,3,2,14,0,4,2,15,0,5,2,16,0,6,2,17,0,3,18,0,4,3,19,0,5,3,20,0,6,3,21,0,4,22,0,5,4,23,0,6,4,24,0,5,25,0,6,5,26,0,6,27,0,1,7,28,0,2,1,8,7,29,0,3,1,9,7,30,0,4,1,10,7,31,0,5,1,11,7,32,0,6,1,12,7,33,0,2,13,1,8,34,0,3,2,14,1,9,8,35,0,4,2,15,1,10,8,36,0,5,2,16,1,11,8,37,0,6,2,17,1,12,8,38,0,3,18,1,9,39,0,4,3,19,1,10,9,40,0,5,3,20,1,11,9,41,0,6,3,21,1,12,9,42,0,4,22,1,10,43,0,5,4,23,1,11,10,44,0,6,4,24,1,12,10,45,0,5,25,1,11,46,0,6,5,26,1,12,11,47,0,6,27,1,12,48,0,2,13,49,0,3,2,14,13,50,0,4,2,15,13,51,0,5,2,16,13,52,0,6,2,17,13,53,0,3,18,2,14,54,0,4,3,19,2,15,14,55,0,5,3,20,2,16,14,56,0,6,3,21,2,17,14,57,0,4,22,2,15,58,0,5,4,23,2,16,15,59,0,6,4,24,2,17,15,60,0,5,25,2,16,61,0,6,5,26,2,17,16,62,0,6,27,2,17,63,0,3,18,64,0,4,3,19,18,65,0,5,3,20,18,66,0,6,3,21,18,67,0,4,22,3,19,68,0,5,4,23,3,20,19,69,0,6,4,24,3,21,19,70,0,5,25,3,20,71,0,6,5,26,3,21,20,72,0,6,27,3,21,73,0,4,22,74,0,5,4,23,22,75,0,6,4,24,22,76,0,5,25,4,23,77,0,6,5,26,4,24,23,78,0,6,27,4,24,79,0,5,25,80,0,6,5,26,25,81,0,6,27,5,26,82,0,6,27,83};
	static long  POS_PREIV[455] = {0,1,0,2,0,3,0,4,0,5,0,6,0,7,1,0,8,1,2,0,9,1,3,0,10,1,4,0,11,1,5,0,12,1,6,0,13,2,0,14,2,3,0,15,2,4,0,16,2,5,0,17,2,6,0,18,3,0,19,3,4,0,20,3,5,0,21,3,6,0,22,4,0,23,4,5,0,24,4,6,0,25,5,0,26,5,6,0,27,6,0,28,7,1,0,29,7,8,1,2,0,30,7,9,1,3,0,31,7,10,1,4,0,32,7,11,1,5,0,33,7,12,1,6,0,34,8,1,13,2,0,35,8,9,1,14,2,3,0,36,8,10,1,15,2,4,0,37,8,11,1,16,2,5,0,38,8,12,1,17,2,6,0,39,9,1,18,3,0,40,9,10,1,19,3,4,0,41,9,11,1,20,3,5,0,42,9,12,1,21,3,6,0,43,10,1,22,4,0,44,10,11,1,23,4,5,0,45,10,12,1,24,4,6,0,46,11,1,25,5,0,47,11,12,1,26,5,6,0,48,12,1,27,6,0,49,13,2,0,50,13,14,2,3,0,51,13,15,2,4,0,52,13,16,2,5,0,53,13,17,2,6,0,54,14,2,18,3,0,55,14,15,2,19,3,4,0,56,14,16,2,20,3,5,0,57,14,17,2,21,3,6,0,58,15,2,22,4,0,59,15,16,2,23,4,5,0,60,15,17,2,24,4,6,0,61,16,2,25,5,0,62,16,17,2,26,5,6,0,63,17,2,27,6,0,64,18,3,0,65,18,19,3,4,0,66,18,20,3,5,0,67,18,21,3,6,0,68,19,3,22,4,0,69,19,20,3,23,4,5,0,70,19,21,3,24,4,6,0,71,20,3,25,5,0,72,20,21,3,26,5,6,0,73,21,3,27,6,0,74,22,4,0,75,22,23,4,5,0,76,22,24,4,6,0,77,23,4,25,5,0,78,23,24,4,26,5,6,0,79,24,4,27,6,0,80,25,5,0,81,25,26,5,6,0,82,26,5,27,6,0,83,27,6,0};

	static long  POS_ACCUM_S[85] = {0,1,2,3,4,5,6,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,52,55,58,61,64,67,70,74,78,82,86,89,93,97,101,104,108,112,115,119,122,125,128,131,134,137,140,144,148,152,155,159,163,166,170,173,176,179,182,185,188,192,196,199,203,206,209,212,215,218,222,225,228,231,234,237};
	static long  POS_COEFS_S[237] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1};
	static long  POS_PREVI_S[237] = {0,0,0,0,0,0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,2,0,3,0,4,0,5,0,6,0,3,0,4,0,5,0,6,0,4,0,5,0,6,0,5,0,6,0,6,0,1,7,0,1,7,0,1,7,0,1,7,0,1,7,0,1,7,0,2,13,0,3,2,14,0,4,2,15,0,5,2,16,0,6,2,17,0,3,18,0,4,3,19,0,5,3,20,0,6,3,21,0,4,22,0,5,4,23,0,6,4,24,0,5,25,0,6,5,26,0,6,27,0,2,13,0,2,13,0,2,13,0,2,13,0,2,13,0,3,18,0,4,3,19,0,5,3,20,0,6,3,21,0,4,22,0,5,4,23,0,6,4,24,0,5,25,0,6,5,26,0,6,27,0,3,18,0,3,18,0,3,18,0,3,18,0,4,22,0,5,4,23,0,6,4,24,0,5,25,0,6,5,26,0,6,27,0,4,22,0,4,22,0,4,22,0,5,25,0,6,5,26,0,6,27,0,5,25,0,5,25,0,6,27,0,6,27};
	static long  POS_PREIV_S[237] = {0,1,2,3,4,5,6,7,1,8,1,9,1,10,1,11,1,12,1,13,2,14,2,15,2,16,2,17,2,18,3,19,3,20,3,21,3,22,4,23,4,24,4,25,5,26,5,27,6,28,7,1,29,8,2,30,9,3,31,10,4,32,11,5,33,12,6,34,8,1,35,8,9,1,36,8,10,1,37,8,11,1,38,8,12,1,39,9,1,40,9,10,1,41,9,11,1,42,9,12,1,43,10,1,44,10,11,1,45,10,12,1,46,11,1,47,11,12,1,48,12,1,49,13,2,50,14,3,51,15,4,52,16,5,53,17,6,54,14,2,55,14,15,2,56,14,16,2,57,14,17,2,58,15,2,59,15,16,2,60,15,17,2,61,16,2,62,16,17,2,63,17,2,64,18,3,65,19,4,66,20,5,67,21,6,68,19,3,69,19,20,3,70,19,21,3,71,20,3,72,20,21,3,73,21,3,74,22,4,75,23,5,76,24,6,77,23,4,78,23,24,4,79,24,4,80,25,5,81,26,6,82,26,5,83,27,6};


	if(ORDER < 0) return NUM_COLUMNS;

	static int  NOT_INITIALIZED = 1;
	if(NOT_INITIALIZED)
	{
		set_iterations();
		NOT_INITIALIZED = 0; 
	}
	set_max_order(ORDER);

	realNUM var[VARIABLES+1][NUM_DERIVATIVES][ORDER+1];
	realNUM par[PARAMETERS][NUM_DERIVATIVES][ORDER+1];
	realNUM link[LINKS][NUM_DERIVATIVES][ORDER+1];
	variables_init(var,v,t);
	parameters_init(par,p);
	links_init(link);
	derivatives_init(var,par,v);

	int i;
	for(i=0;  i<=ORDER; i++) {
		var_t(var[3],var[1], i);
		var_t(var[4],var[2], i);
		var_t(link[92],var[3], i);
		var_t(link[96],var[4], i);
		inv_t(par[0],link[0],i);
		sub_t(var[1],var[2],link[1],i);
		add_t_c("1.",par[0],link[2],i);
		add_t_c("1.",par[1],link[3],i);
		add_t_c("1.",par[0],link[4],i);
		add_t_c("2.",par[1],link[5],i);
		add_t_c("2.",par[0],link[6],i);
		sincos_t(var[1],link[7],link[8],i);
		sincos_t(var[2],link[9],link[10],i);
		mul_t_c("-29.400000000000002",par[0],link[11],i);
		mul_t_c("-19.6",par[0],link[12],i);
		mul_t_c("-9.8",par[1],link[13],i);
		mul_t_c("-2.",par[1],link[14],i);
		mul_t_c("-1.",par[0],link[15],i);
		mul_t_c("-1.",par[1],link[16],i);
		mul_t_c("2.",par[0],link[17],i);
		mul_t(par[0],par[0],link[18],i);
		mul_t(par[0],par[1],link[19],i);
		mul_t(var[3],var[3],link[20],i);
		mul_t(var[4],var[4],link[21],i);
		sincos_t(link[1],link[27],link[22],i);
		add_t_c("-2.",link[14],link[23],i);
		add_t_c("-2.",link[16],link[24],i);
		add_t_c("-1.",link[16],link[25],i);
		add_t(link[6],par[1],link[26],i);
		mul_t_c("-19.6",link[9],link[28],i);
		mul_t_c("-9.8",link[9],link[29],i);
		mul_t_c("-1.",link[0],link[30],i);
		mul_t_c("2.",link[1],link[31],i);
		mul_t_c("9.8",link[7],link[32],i);
		mul_t(link[2],link[2],link[33],i);
		mul_t(link[2],par[0],link[34],i);
		mul_t(link[3],link[17],link[35],i);
		mul_t(link[3],link[18],link[36],i);
		mul_t(link[4],link[4],link[37],i);
		mul_t(link[9],link[11],link[38],i);
		mul_t(link[9],link[13],link[39],i);
		mul_t(link[12],par[1],link[40],i);
		add_t(link[5],link[35],link[41],i);
		add_t(link[19],link[26],link[42],i);
		add_t(link[28],link[38],link[43],i);
		sincos_t(link[31],link[44],link[45],i);
		mul_t_c("-1.",link[27],link[46],i);
		mul_t_c("9.8",link[22],link[47],i);
		mul_t(link[2],link[22],link[48],i);
		mul_t(link[9],link[40],link[49],i);
		mul_t(link[18],link[25],link[50],i);
		mul_t(link[18],link[29],link[51],i);
		mul_t(link[18],link[39],link[52],i);
		mul_t(link[22],link[22],link[53],i);
		mul_t(link[23],par[0],link[54],i);
		mul_t(link[27],link[34],link[55],i);
		mul_t(link[27],par[0],link[56],i);
		add_t(link[24],link[54],link[57],i);
		add_t(link[36],link[41],link[58],i);
		add_t(link[39],link[43],link[59],i);
		mul_t_c("-9.8",link[42],link[60],i);
		mul_t_c("-1.",link[53],link[61],i);
		mul_t_c("-0.5",link[44],link[62],i);
		mul_t_c("1.",link[53],link[63],i);
		mul_t(link[7],link[47],link[64],i);
		mul_t(link[15],link[44],link[65],i);
		mul_t(link[20],link[55],link[66],i);
		mul_t(link[20],link[56],link[67],i);
		mul_t(link[21],link[46],link[68],i);
		add_t(link[32],link[68],link[69],i);
		add_t(link[49],link[59],link[70],i);
		add_t(link[50],link[57],link[71],i);
		mul_t(link[9],link[60],link[72],i);
		mul_t(link[18],link[62],link[73],i);
		mul_t(link[21],link[62],link[74],i);
		mul_t(link[21],link[65],link[75],i);
		mul_t(link[33],link[61],link[76],i);
		mul_t(link[37],link[63],link[77],i);
		mul_t(link[37],link[64],link[78],i);
		add_t(link[51],link[70],link[79],i);
		add_t(link[58],link[76],link[80],i);
		add_t(link[67],link[72],link[81],i);
		add_t(link[71],link[77],link[82],i);
		mul_t(link[21],link[73],link[83],i);
		mul_t(link[58],link[69],link[84],i);
		divide_t(link[30],link[80],link[85],i);
		add_t(link[74],link[79],link[86],i);
		mul_t(link[48],link[81],link[87],i);
		add_t(link[52],link[86],link[88],i);
		add_t(link[84],link[87],link[89],i);
		mul_t(link[2],link[85],link[90],i);
		add_t(link[66],link[88],link[91],i);
		mul_t(link[89],link[90],link[92],i);
		add_t(link[75],link[91],link[93],i);
		add_t(link[83],link[93],link[94],i);
		add_t(link[78],link[94],link[95],i);
		divide_t(link[95],link[82],link[96],i);
	}

	write_solution(cvfd,var,link);

	return NUM_COLUMNS;
}

long  goswani_columns()
{
	 return 337;
}

long  goswani_pos_der(char *der)
{
	static char* STR_DER[84] = {"000000","100000","010000","001000","000100","000010","000001","200000","110000","101000","100100","100010","100001","020000","011000","010100","010010","010001","002000","001100","001010","001001","000200","000110","000101","000020","000011","000002","300000","210000","201000","200100","200010","200001","120000","111000","110100","110010","110001","102000","101100","101010","101001","100200","100110","100101","100020","100011","100002","030000","021000","020100","020010","020001","012000","011100","011010","011001","010200","010110","010101","010020","010011","010002","003000","002100","002010","002001","001200","001110","001101","001020","001011","001002","000300","000210","000201","000120","000111","000102","000030","000021","000012","000003"};
	long i;
	for(i=0; i < 84; i++)
		if(strcmp(der,STR_DER[i]) == 0) return i;
	return -1;
}

long  goswani_variable_column(int v, char *der)
{
	 return position_variable(v, goswani_pos_der, der);
}

long  goswani_function_column(int f, char *der)
{
	 return position_function(f, goswani_pos_der, der);
}


