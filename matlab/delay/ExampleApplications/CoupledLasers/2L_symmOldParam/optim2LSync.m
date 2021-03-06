
%% prepare matlab
close all
clear 
clc

%% define system to begin with
param=[0.54;0.5];
%xGue=[0.3333;0.0004;-0.01;0.3333;0.0004;-0.01];
xGue=[0.1910;0.2732;-0.01;0.1910;0.2732;-0.01];
% xGue=[0.2356;0.2356;-0.01;0.2356;0.2356;-0.01];
p=VariableVector(-0.02,8,{'omega'});

% param = [0.45;0.45];
% xGue = [0.0407031314951728;0.668830467436600;0.000696388699168746;0.0407031314951731;0.668830467436600;0.000696388699168743];
% p=VariableVector(-0.003595083936435,8,{'omega'});


%% name states and parameters
xNom=VariableVector(xGue,0,[{'E1r'};{'E1i'};{'n1'};{'E2r'};{'E2i'};{'n2'}]);
alphaNom=VariableVector(param,6,[{'pump1'};{'pump2'}]);

%% define system dynamics
tau=@(x,alpha,p)100/1000;
% lasermod=@(x,xtau,alpha,p)[p(1) * x(2) + 0.5e0 * x(3) * x(1) - 0.20e1 * x(3) * x(2) + 0.25e-2 * cos(0.100e3 * p(1) + 0.2e1) * xtau(1) + 0.25e-2 * sin(0.100e3 * p(1) + 0.2e1) * xtau(2) + 0.25e-2 * cos(0.100e3 * p(1) + 0.2e1) * xtau(4) + 0.25e-2 * sin(0.100e3 * p(1) + 0.2e1) * xtau(5);
%                             -p(1) * x(1) + 0.20e1 * x(3) * x(1) + 0.5e0 * x(3) * x(2) - 0.25e-2 * sin(0.100e3 * p(1) + 0.2e1) * xtau(1) + 0.25e-2 * cos(0.100e3 * p(1) + 0.2e1) * xtau(2) - 0.25e-2 * sin(0.100e3 * p(1) + 0.2e1) * xtau(4) + 0.25e-2 * cos(0.100e3 * p(1) + 0.2e1) * xtau(5);
%                             0.5e-2 * alpha(1) - 0.5e-2 * x(3) - 0.5e-2 * (x(3) + 0.1e1) * (x(1)^2 + x(2)^2);
%                             p(1) * x(5) + 0.5e0 * x(6) * x(4) - 0.20e1 * x(6) * x(5) + 0.25e-2 * cos(0.100e3 * p(1) + 0.2e1) * xtau(4) + 0.25e-2 * sin(0.100e3 * p(1) + 0.2e1) * xtau(5) + 0.25e-2 * cos(0.100e3 * p(1) + 0.2e1) * xtau(1) + 0.25e-2 * sin(0.100e3 * p(1) + 0.2e1) * xtau(2);
%                             -p(1) * x(4) + 0.20e1 * x(6) * x(4) + 0.5e0 * x(6) * x(5) - 0.25e-2 * sin(0.100e3 * p(1) + 0.2e1) * xtau(4) + 0.25e-2 * cos(0.100e3 * p(1) + 0.2e1) * xtau(5) - 0.25e-2 * sin(0.100e3 * p(1) + 0.2e1) * xtau(1) + 0.25e-2 * cos(0.100e3 * p(1) + 0.2e1) * xtau(2);
%                             0.5e-2 * alpha(2) - 0.5e-2 * x(6) - 0.5e-2 * (x(6) + 0.1e1) * (x(4)^2 + x(5)^2)  
%                           ];

lasermod=@Laser_DDE_2L;

%% collect them in an object 
aDDE_2L=DDE(@(x,xtau,alpha,p)lasermod(x,xtau,alpha,p),tau,xNom,alphaNom,p);

% clear tau
% clear alphaNom
% clear xGue
% clear param
% clear omega
% clear phi

%% construct object ''aDDENLP''

minDist=0.00000000001;

J=@(x)-1e2*abs((x(1)+1i*x(2))+(x(4)+1i*x(5)))^2; %Maximale Intensität (mit p1=p2=0.1)

aDDENLP=DDENLP(J,aDDE_2L,xNom,[-Inf;-Inf;-Inf;-Inf;-Inf;-Inf],[Inf;Inf;Inf;Inf;Inf;Inf],[0;0],[0.8;0.5],-Inf,Inf);
% clear aDDE_1L
% clear J
% clear xNom

aDDENLP.optionsInitEqCons=optimoptions('fsolve','Algorithm','levenberg-marquardt','MaxIter',10000,'MaxFunEvals',200000,'display','off','TolFun',1e-7,'TolX',1e-7);
aDDENLP.optionsInitOptim=optimoptions('fmincon','Algorithm','interior-point','MaxIter',10000,'MaxFunEvals',200000,'display','off');
aDDENLP.optionsMainOptim=optimoptions('fmincon','Algorithm','interior-point','MaxIter',10000,'MaxFunEvals',200000,'display','iter','TolFun',1e-14,'TolX',1e-10,'TolCon',1e-10);

%active-set
%% initialize steady state constraints
aDDENLP.initializeStStRot();


aDDENLP.vars.nominal.x.values
aDDENLP.vars.nominal.p.values
[~]=aDDENLP.checkStabilityPoint('nominal');

aDDENLP.vars.nominal.eigs

%% add NV Cons

%Mod-Fold Punkt Branch 1 (100)
xCrit1=VariableVector([0.197742718207656;0.254333015283471;-0.0100548294108757;0.0766499369976581;0.341727571036470;-0.00900159364531876],0,[{'E1rcrit1'};{'E1icrit1'};{'n1crit1'};{'E2rcrit1'};{'E2icrit1'};{'n2crit1'}]);
alphaCrit1=VariableVector([0.106099537864213;0.0870803879148029],0,[{'pump1crit1'};{'pump2crit1'}]);
pCrit1=VariableVector(-0.0193,0,{'omegacrit1'});

 aDDENLP.addNVCon('modfold',@Mod_Fold_2L,@NV_Mod_Fold_2L,xCrit1,alphaCrit1,pCrit1);
 %aDDENLP.NVCon(end).vars.w1.values=[-2.04600372668366e-06;0.735133515320831;2.69991153805835e-08;0.268291038541200;0.622574199020755;6.34770142102037e-09];
 %aus der fsolve-berechnung nur_w_2l
 aDDENLP.NVCon(end).vars.w1.values=[-0.202958484289877;0.150220521107475;-0.00334100169657379;-0.505941218404173;0.824774581827560;0.000925615564299419];

 
% aDDENLP.addNVCon('modfold',@Mod_Fold_2L,@NV_Mod_Fold_2L,xCrit1,alphaCrit1,p);
clear alphaCrit1
clear xCrit1
clear pCrit1


%Mod-Fold Punkt Branch 1 (100)
xCrit1=VariableVector([0.0766499369976581;0.341727571036470;-0.00900159364531876;0.197742718207656;0.254333015283471;-0.0100548294108757],0,[{'E1rcrit1'};{'E1icrit1'};{'n1crit1'};{'E2rcrit1'};{'E2icrit1'};{'n2crit1'}]);
alphaCrit1=VariableVector([0.0870803879148029;0.106099537864213],0,[{'pump1crit1'};{'pump2crit1'}]);
pCrit1=VariableVector(-0.0193,0,{'omegacrit1'});


 aDDENLP.addNVCon('modfold',@Mod_Fold_2L,@NV_Mod_Fold_2L,xCrit1,alphaCrit1,pCrit1);
 %aDDENLP.NVCon(end).vars.w1.values=[-2.04600372668366e-06;0.735133515320831;2.69991153805835e-08;0.268291038541200;0.622574199020755;6.34770142102037e-09];
 %aus der fsolve-berechnung nur_w_2l
 aDDENLP.NVCon(end).vars.w1.values=[-0.505941218404173;0.824774581827560;0.000925615564299419;-0.202958484289877;0.150220521107475;-0.00334100169657379];

 
% aDDENLP.addNVCon('modfold',@Mod_Fold_2L,@NV_Mod_Fold_2L,xCrit1,alphaCrit1,p);
clear alphaCrit1
clear xCrit1
clear pCrit1



%% initatialize constraints and prepare optimization


aDDENLP.initNVCons();
aDDENLP.concatConstraints();
aDDENLP.concatInitPoints();



% openfig('Pump_fsolve.fig')
% 
% figure(1)
% hold on
% plot3(aDDENLP.vars.nominal.alpha.values(1),aDDENLP.vars.nominal.alpha.values(2),aDDENLP.vars.nominal.p.values(1),'ks')
% 
% figure(1)
% hold on
% plot3(aDDENLP.vars.critical(1,1).alpha.values(1),aDDENLP.vars.critical(1,1).alpha.values(2),aDDENLP.vars.critical(1,1).p.values(1),'rs')
% 
% figure(1)
% hold on
% plot3(aDDENLP.vars.critical(2,1).alpha.values(1),aDDENLP.vars.critical(2,1).alpha.values(2),aDDENLP.vars.critical(2,1).p.values(1),'rs')
% 
% figure(1)
% hold on
% quiver3(aDDENLP.vars.critical(1,1).alpha.values(1),aDDENLP.vars.critical(1,1).alpha.values(2),aDDENLP.vars.critical(1,1).p.values(1),0.012*aDDENLP.vars.critical(1,1).r.values(1),0.012*aDDENLP.vars.critical(1,1).r.values(2),0)
% 
% figure(1)
% hold on
% quiver3(aDDENLP.vars.critical(2,1).alpha.values(1),aDDENLP.vars.critical(2,1).alpha.values(2),aDDENLP.vars.critical(2,1).p.values(1),0.012*aDDENLP.vars.critical(2,1).r.values(1),0.012*aDDENLP.vars.critical(2,1).r.values(2),0)

openfig('modfold_simple.fig');
xlim([0,1])
ylim([0,1])

figure(1)
hold on
plot(aDDENLP.vars.nominal.alpha.values(1),aDDENLP.vars.nominal.alpha.values(2),'ks')

% figure(1)
% hold on
% plot(aDDENLP.vars.critical(1,1).alpha.values(1),aDDENLP.vars.critical(1,1).alpha.values(2),'rs')
% 
% figure(1)
% hold on
% plot(aDDENLP.vars.critical(2,1).alpha.values(1),aDDENLP.vars.critical(2,1).alpha.values(2),'rs')
% 
% figure(1)
% hold on
% quiver(aDDENLP.vars.critical(1,1).alpha.values(1),aDDENLP.vars.critical(1,1).alpha.values(2),0.012*aDDENLP.vars.critical(1,1).r.values(1),0.012*aDDENLP.vars.critical(1,1).r.values(2))
% 
% figure(1)
% hold on
% quiver(aDDENLP.vars.critical(2,1).alpha.values(1),aDDENLP.vars.critical(2,1).alpha.values(2),0.012*aDDENLP.vars.critical(2,1).r.values(1),0.012*aDDENLP.vars.critical(2,1).r.values(2))


%% run optimization
aDDENLP.maxAllowedRealPart=-1;
aDDENLP.minDist=minDist;
%minDist muss verändert werden, da diese am Anfang deutlich
%unter 1 liegt

aDDENLP.runOptim;


aDDENLP.aCostFunction=@(x)-abs((x(1)+1i*x(2))+(x(4)+1i*x(5)))^2;
aDDENLP.optionsMainOptim=optimoptions('fmincon','Algorithm','active-set','MaxIter',10000,'MaxFunEvals',200000,'display','iter','TolFun',1e-12,'TolX',1e-12);
aDDENLP.deconstructOptimum();
aDDENLP.concatInitPoints();
aDDENLP.runOptim;


hier = aDDENLP.deconstructOptimum();

figure(1)
hold on
plot(aDDENLP.vars.nominal.alpha.values(1),aDDENLP.vars.nominal.alpha.values(2),'ks')

plot(...
    minDist*sqrt(aDDENLP.nAlpha)*sin(0:0.01:2*pi)+aDDENLP.vars.nominal.alpha.values(1),...    
    minDist*sqrt(aDDENLP.nAlpha)*cos(0:0.01:2*pi)+aDDENLP.vars.nominal.alpha.values(2),...
    'k')


figure(1)
hold on
plot(aDDENLP.vars.critical(1,1).alpha.values(1),aDDENLP.vars.critical(1,1).alpha.values(2),'rs')

figure(1)
hold on
plot(aDDENLP.vars.critical(2,1).alpha.values(1),aDDENLP.vars.critical(2,1).alpha.values(2),'rs')
% 
figure(1)
hold on
quiver(aDDENLP.vars.critical(1,1).alpha.values(1),aDDENLP.vars.critical(1,1).alpha.values(2),0.015*aDDENLP.vars.critical(1,1).r.values(1),0.015*aDDENLP.vars.critical(1,1).r.values(2))

figure(1)
hold on
quiver(aDDENLP.vars.critical(2,1).alpha.values(1),aDDENLP.vars.critical(2,1).alpha.values(2),0.1*aDDENLP.vars.critical(2,1).r.values(1),0.1*aDDENLP.vars.critical(2,1).r.values(2))

xlabel('A');ylabel('B');
grid on;



 
 
 
%% check stability

[~]=aDDENLP.checkStabilityPoint('nominal');
% [~]=aDDENLP.checkStabilityPoint('critical');
% 
% [~]=aDDENLP.checkStabilityAtVertices();
% 
% [~]=aDDENLP.checkStabilityAtRandom();

return

%% run simulation

point=aDDENLP.vars.nominal(end);

point.alpha.values = point.alpha.values +[0.01;-0.01];
omega=point.p.values(1);

E1=point.x.values(1)+1i*point.x.values(2);
n1=point.x.values(3);
E2=point.x.values(4)+1i*point.x.values(5);
n2=point.x.values(6);

history=@(t)[...
    real(E1*1.2*exp(+1i*0.5*omega*t));
    imag(E1*1.2*exp(+1i*0.5*omega*t));
    n1+0*t;
    real(E2*1*exp(-1i*0.5*omega*t));
    imag(E2*1*exp(-1i*0.5*omega*t));
    n2+0*t];



options=ddeset('RelTol',1e-6,'AbsTol',1e-9);
sol=ddesd(aDDENLP,point,history,[0 10],options);

figure(2);clf;
plot(sol.x,sol.y(1:3:end,:))
%  matlab2tikz('2LaserReRot.tex')

% figure(21);clf;
% 
% tHist=-100:0;
% 
% hist=history(tHist).*exp(1i*omega*tHist);
% Eh1 = (hist(1,:)+1i*hist(2,:)).*exp(-1i*omega*tHist);
% Eh2 = (hist(4,:)+1i*hist(5,:)).*exp(-1i*omega*tHist);
% plot(tHist,real(Eh1),tHist,real(Eh2))
% 


 figure(3);clf;
 A=sol.y(1:3:end,:)+1i*sol.y(2:3:end,:);
 E=A.*repmat(exp(-1i*point.p.values(1)*sol.x*1000),2,1);
 plot(sol.x,real(E*exp(0.2*1i*pi)))
%  matlab2tikz('2LaserReFix.tex')

