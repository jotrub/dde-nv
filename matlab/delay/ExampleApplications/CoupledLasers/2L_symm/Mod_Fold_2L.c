#include "mex.h"
#include <math.h>

void ManifoldEquation (
  double *x,
  double *alpha,
  double *p,
  double *w,
  double residuum[13])
{
  residuum[0] = 0.1000e4 * p[0] * x[1] + 0.1000e4 * x[2] * x[0] - 0.5000e4 * x[2] * x[1] + 0.5000e0 * cos(0.1000e4 * p[0] + 0.1e1) * x[0] + 0.5000e0 * sin(0.1000e4 * p[0] + 0.1e1) * x[1] + 0.5000e0 * cos(0.1000e4 * p[0] + 0.1e1) * x[3] + 0.5000e0 * sin(0.1000e4 * p[0] + 0.1e1) * x[4];
  residuum[1] = -0.1000e4 * p[0] * x[0] + 0.5000e4 * x[2] * x[0] + 0.1000e4 * x[2] * x[1] - 0.5000e0 * sin(0.1000e4 * p[0] + 0.1e1) * x[0] + 0.5000e0 * cos(0.1000e4 * p[0] + 0.1e1) * x[1] - 0.5000e0 * sin(0.1000e4 * p[0] + 0.1e1) * x[3] + 0.5000e0 * cos(0.1000e4 * p[0] + 0.1e1) * x[4];
  residuum[2] = 0.1000e1 * alpha[0] - 0.1000e1 * x[2] - 0.1000e1 * (0.2e1 * x[2] + 0.1e1) * (pow(x[0], 0.2e1) + pow(x[1], 0.2e1));
  residuum[3] = 0.1000e4 * p[0] * x[4] + 0.1000e4 * x[5] * x[3] - 0.5000e4 * x[5] * x[4] + 0.5000e0 * cos(0.1000e4 * p[0] + 0.1e1) * x[3] + 0.5000e0 * sin(0.1000e4 * p[0] + 0.1e1) * x[4] + 0.5000e0 * cos(0.1000e4 * p[0] + 0.1e1) * x[0] + 0.5000e0 * sin(0.1000e4 * p[0] + 0.1e1) * x[1];
  residuum[4] = -0.1000e4 * p[0] * x[3] + 0.5000e4 * x[5] * x[3] + 0.1000e4 * x[5] * x[4] - 0.5000e0 * sin(0.1000e4 * p[0] + 0.1e1) * x[3] + 0.5000e0 * cos(0.1000e4 * p[0] + 0.1e1) * x[4] - 0.5000e0 * sin(0.1000e4 * p[0] + 0.1e1) * x[0] + 0.5000e0 * cos(0.1000e4 * p[0] + 0.1e1) * x[1];
  residuum[5] = 0.1000e1 * alpha[1] - 0.1000e1 * x[5] - 0.1000e1 * (0.2e1 * x[5] + 0.1e1) * (pow(x[3], 0.2e1) + pow(x[4], 0.2e1));
  residuum[6] = -0.1359140914e1 * cos(0.1000e4 * p[0] + 0.1e1) * w[0] - 0.1359140914e1 * sin(0.1000e4 * p[0] + 0.1e1) * w[1] - 0.1359140914e1 * cos(0.1000e4 * p[0] + 0.1e1) * w[3] - 0.1359140914e1 * sin(0.1000e4 * p[0] + 0.1e1) * w[4] - 0.1000e4 * x[2] * w[0] - (0.1000e4 * p[0] - 0.5000e4 * x[2]) * w[1] - (0.1000e4 * x[0] - 0.5000e4 * x[1]) * w[2] - 0.10e1 * w[0];
  residuum[7] = 0.1359140914e1 * sin(0.1000e4 * p[0] + 0.1e1) * w[0] - 0.1359140914e1 * cos(0.1000e4 * p[0] + 0.1e1) * w[1] + 0.1359140914e1 * sin(0.1000e4 * p[0] + 0.1e1) * w[3] - 0.1359140914e1 * cos(0.1000e4 * p[0] + 0.1e1) * w[4] - (-0.1000e4 * p[0] + 0.5000e4 * x[2]) * w[0] - 0.1000e4 * x[2] * w[1] - (0.5000e4 * x[0] + 0.1000e4 * x[1]) * w[2] - 0.10e1 * w[1];
  residuum[8] = 0.2000e1 * (0.2e1 * x[2] + 0.1e1) * x[0] * w[0] + 0.2000e1 * (0.2e1 * x[2] + 0.1e1) * x[1] * w[1] - (-0.1000e1 - 0.2000e1 * pow(x[0], 0.2e1) - 0.2000e1 * pow(x[1], 0.2e1)) * w[2] - 0.10e1 * w[2];
  residuum[9] = -0.1359140914e1 * cos(0.1000e4 * p[0] + 0.1e1) * w[0] - 0.1359140914e1 * sin(0.1000e4 * p[0] + 0.1e1) * w[1] - 0.1359140914e1 * cos(0.1000e4 * p[0] + 0.1e1) * w[3] - 0.1359140914e1 * sin(0.1000e4 * p[0] + 0.1e1) * w[4] - 0.1000e4 * x[5] * w[3] - (0.1000e4 * p[0] - 0.5000e4 * x[5]) * w[4] - (0.1000e4 * x[3] - 0.5000e4 * x[4]) * w[5] - 0.10e1 * w[3];
  residuum[10] = 0.1359140914e1 * sin(0.1000e4 * p[0] + 0.1e1) * w[0] - 0.1359140914e1 * cos(0.1000e4 * p[0] + 0.1e1) * w[1] + 0.1359140914e1 * sin(0.1000e4 * p[0] + 0.1e1) * w[3] - 0.1359140914e1 * cos(0.1000e4 * p[0] + 0.1e1) * w[4] - (-0.1000e4 * p[0] + 0.5000e4 * x[5]) * w[3] - 0.1000e4 * x[5] * w[4] - (0.5000e4 * x[3] + 0.1000e4 * x[4]) * w[5] - 0.10e1 * w[4];
  residuum[11] = 0.2000e1 * (0.2e1 * x[5] + 0.1e1) * x[3] * w[3] + 0.2000e1 * (0.2e1 * x[5] + 0.1e1) * x[4] * w[4] - (-0.1000e1 - 0.2000e1 * pow(x[3], 0.2e1) - 0.2000e1 * pow(x[4], 0.2e1)) * w[5] - 0.10e1 * w[5];
  residuum[12] = pow(w[0], 0.2e1) + pow(w[1], 0.2e1) + pow(w[2], 0.2e1) + pow(w[3], 0.2e1) + pow(w[4], 0.2e1) + pow(w[5], 0.2e1) - 0.1e1;
}



/* The gateway function */                                                                                             
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])                                           
{                                                                                                                      
                                                                                                                       
 /* check for proper number of arguments */                                                                            
 if(nrhs!=4) {                                                                                                         
     mexErrMsgIdAndTxt("MyToolbox:populationModelModFoldManiPop:nrhs","4 inputs required (some of them are vectors).");
 }                                                                                                                     
 if(nlhs==0) {                                                                                                         
     mexErrMsgIdAndTxt("MyToolbox:populationModelModFoldManiPop:nlhs","Please define an output!");                     
 }                                                                                                                     
 if(nlhs!=1) {                                                                                                         
     mexErrMsgIdAndTxt("MyToolbox:populationModelModFoldManiPop:nlhs","One output required.");                         
 }                                                                                                                     
                                                                                                                       
 /* get the values of the inputs                                                                                       
  * scalars are fetched using mxGetScalar and assigned to a type double,                                               
  * vectors are fetched using mxGetPr and assigned to type double pointer                                              
  */                                                                                                                   
                                                                                                                       
 double *xPointer = mxGetPr(prhs[0]);                                                                                  
 double *alphaPointer = mxGetPr(prhs[1]);                                                                             
 double *pPointer = mxGetPr(prhs[2]);                                                                              
 double *wPointer = mxGetPr(prhs[3]);                                                                                  
                                                                                                                       
                                                                                                                       
 /* create the output matrix */                                                                                        
 plhs[0] = mxCreateDoubleMatrix(1,(mwSize)                                                                             
13                                                                                                                      
,mxREAL);                                                                                                              
                                                                                                                       
 /* get a pointer to the real data in the output matrix */                                                             
 double *residuumPointer = mxGetPr(plhs[0]);                                                                           
                                                                                                                       
 /* call the computational routine */                                                                                  
 ManifoldEquation(xPointer, alphaPointer, pPointer, wPointer, residuumPointer);                                                  
}                                                                                                                      
