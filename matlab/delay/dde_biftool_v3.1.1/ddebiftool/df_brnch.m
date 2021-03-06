function branch=df_brnch(funcs,free_par,kind,flag_newhheur)
%% set up empty branch with default values
% function branch=df_brnch(funcs,free_par,kind,flag_newhheur)
% INPUT:
%       funcs problem functions
%       free_par free parameter list
%       kind type of solution point
%       flag_newhheur (optional, default: 1) boolean: use new steplength heuristic
%                     Only used if kind==stst, cf. df_mthod
% OUTPUT:
%	branch empty branch with default values

% (c) DDE-BIFTOOL v. 3.1.1(19), 11/04/2014
% Update on 05/03/2007 ("flag_newhheur" <=> (imag(method.stability.lms_parameter_rho)~=0) )
%
% 
%
%%
sys_tau=funcs.sys_tau;


if ~exist('flag_newhheur','var'),
  flag_newhheur=1;
end;  

branch.method=df_mthod(funcs,kind,flag_newhheur);

branch.parameter.free=free_par;
branch.parameter.min_bound=[];
branch.parameter.max_bound=[];
branch.parameter.max_step=[];

tp_del=funcs.tp_del;
if tp_del==0
  tau=sys_tau();
  for j=1:length(tau)
    branch.parameter.min_bound(j,:)=[tau(j) 0];
  end;
end;

branch.point=[];

return;
