function [maxEig,steadyState,eigs] = checkStability(funcs,parameter,x0,numMinEig,freeParams)
% function to evalutate the stability of a DDE steady state. It uses
% DDE-BIFTOOL
%
% Arguments:
%
% - funcs: structure in DDE-BIFTOOL-syntax containing all relevant
% information of the DDE
%
% - parameter: parametervector, syntax: [p1,p2,...,pn]
%
% - x0: intial guess for steady state
%
% - numMinEig: lower boundary for numerical eigenvalue approximation
% 
% - freeParams: freeParameters indication algebraic variables within
% 'parameter'


if (nargin < 4) || (isempty(numMinEig))
    numMinEig = -5;
end

if nargin < 5
    freeParams=[];
end

enableOutput = 1;

% define steady state for DDE-BIFTOOL
stst.kind = 'stst';
stst.parameter = parameter;
stst.x = x0;

% prepare all options
flag_newhheur = 1;
method = df_mthod(funcs,'stst',flag_newhheur);
method.stability.minimal_real_part = numMinEig; % only for numerics (no stability boundary)

method.point.newton_max_iterations = 50;
method.point.print_residual_info = 1;
method.point.newton_nmon_iterations = 10;


if ~isempty(freeParams)
    warning('off','p_correc:nonsquare');
end


% correct steady state
[stst,success] = p_correc(funcs,stst,freeParams,[],method.point);

if ~isempty(freeParams)
    warning('on','p_correc:nonsquare');
end

if (~success)&&enableOutput
    warning('correction failed');
    maxEig = NaN;
    steadyState = stst.x;
    eigs=NaN(100,1);
else
    if (norm(stst.x,2) < 0.01)&&enableOutput
        warning('possibly converged to trivial steady state');
    end
    
    % evalutate the stability
    
    stst.stability = p_stabil(funcs,stst,method.stability);
    
    % extract biggest real part
    eigs = stst.stability.l1;
    [~,index] = max(real(stst.stability.l1));
    maxEig = stst.stability.l1(index);
    steadyState = stst.x;
    
end
end