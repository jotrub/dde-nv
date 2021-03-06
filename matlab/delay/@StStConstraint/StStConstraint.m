%> @file StStConstraint.m
%> @brief class that inherits its properities from EqualityConstraints. It
%> represents steady state constraints.
%> @author Jonas Otten
%> @date 18 Jul 2017
% ======================================================================
%> @brief     This class describes equality constraints representing the steady
%> state condition for the nominal parameters. It also contains a
%> procedure to initialize the constraint
% ======================================================================




classdef StStConstraint < EqualityConstraint
    
    properties(SetAccess=protected)

    end
    
    methods
    % ======================================================================
    %> @brief Class constructor
    %>
    %> This function constructs instances of the class StStConstraint
    %>
    %> @param aDDE instance of class DDE
    %> @param vars collection of instances of VariableVector (at least
    %> state, uncertain parameters and certain parameters)
    % 
    %> @return instance of the StStConstraint class.
    % ======================================================================
        
        function aStStCon=StStConstraint(aDDE,vars)
            % constructs the instances of the class StStConstraint
            conEq=@(y)aDDE.rhs(y(vars.x.index),...
                repmat(y(vars.x.index),1,aDDE.ntau),...
                y(vars.alpha.index),...
                y(vars.p.index));
            aStStCon=aStStCon@EqualityConstraint(conEq,vars.x.nVar,vars,0);
        end
        
    % ======================================================================
    %> @brief look for a steady state as initialization of this
    %> StStConstraint instance
    %>
    %> @param aStStCon instance of StStConstraint which will be initialized
    %> @param options options for numerical solver fsolve 
    %>
    %> @return initialized instance of the StStConstraint class.
    % ====================================================================== 
        
        
        function aStStCon=initStStConstraint(aStStCon,options)
            %create function handle to search for initial state while
            %holding the parameters alpha fixed
            
            indexX=aStStCon.vars.x.index;
            alpha=aStStCon.vars.alpha.values;
            p=aStStCon.vars.p.values;
            conEqFixedAlpha=@(y)aStStCon.conFun([y(indexX);alpha;p]);
            
            x0=aStStCon.vars.x.values;
            % try to initialize steady state constraint
            [x,~,exitflag]=fsolve(conEqFixedAlpha,x0,options);
            aStStCon.vars.x.values=x;
            if exitflag>0
                aStStCon.status=1;
                fprintf('steady state constraint for nominal point successfully initialized!\n')
            else
                warning(['initialization of steady state contsraint with default options for fsolve not successful, exitflag = ',num2str(exitflag)]);
            end
        end
        
        
    % ======================================================================
    %> @brief look for a steady state as initialization of this
    %> StStConstraint instance while allowing rotating coordinates
    %>
    %> @param aStStCon instance of StStConstraint which will be initialized
    %> @param options options for numerical solver fsolve 
    %>
    %> @return initialized instance of the StStConstraint class.
    % ====================================================================== 
           function aStStCon=initStStConstraintRot(aStStCon,options)
            %create function handle to search for initial state and rotation frequency while
            %holding the parameters alpha fixed
            
            indexX=aStStCon.vars.x.index;
            alpha=aStStCon.vars.alpha.values;
            p=aStStCon.vars.p.values;
            conEqFixedAlpha=@(y)aStStCon.conFun([y(indexX);alpha;y(aStStCon.vars.x.nVar+1:aStStCon.vars.x.nVar+aStStCon.vars.p.nVar)]);
            
            x0=[aStStCon.vars.x.values;aStStCon.vars.p.values];
            % try to initialize steady state constraint
            [x,~,exitflag]=fsolve(conEqFixedAlpha,x0,options);
            aStStCon.vars.x.values=x(indexX);
            aStStCon.vars.p.values=x(indexX(end)+1:indexX(end)+aStStCon.vars.p.nVar);
            if exitflag>0
                aStStCon.status=1;
                fprintf('steady state constraint for nominal point successfully initialized!\n')
            else
                warning(['initialization of steady state contsraint with default options for fsolve not successful, exitflag = ',num2str(exitflag)]);
            end
        end
    end
    
end

