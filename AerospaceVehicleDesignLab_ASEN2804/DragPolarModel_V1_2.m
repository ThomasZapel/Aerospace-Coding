%% Aircraft Geometry
% Sref_Glove = 0.06064;
% Swet_Glove = 0.017943;
c = 0.075;
WingSweep = 35;
b_prime = ((0.4 - c) * sind(30)) / sind(60 - WingSweep);
b_half = b_prime * cosd(WingSweep);
b = b_half * 2;
%b_prime = b / cosd(WingSweep);
Sref_Wing = b_prime * c * 2;
Swet_Wing = Sref_Wing - (0.11*c);
Swet = Swet_Wing;
Sref = Sref_Wing;
length = 0.315;
maxh = 0.11;
d = 0.11;
AR = (b^2) / Sref_Wing
Amax = maxh * d;
Abase = pi * ((0.03/2)^2);
e = 1 / (1.05 + (0.007*pi*AR));
Mach = 0.3; 
leakage = 0.15; 
Re = 5*(10^5); 

% GloveSweep = 75;
XCmax_Wing = 0.1;
TCmax_Wing = 0.1;
% XCmax_Glove = 0.4;
% TCmax_Glove = 0.08/0.4;
XCmax_Stab = 0.1;
TCmax_Stab = 0.1;
Swet_Stab = 0.0012;
StabSweep = 0;
Re_Wing = 5 * (10^5);
Cflam = 1.328 / sqrt(Re_Wing);
Cfturb = 0.074 / (Re_Wing^0.2);

Swet_Vert = Swet_Stab / 2;
XCmax_Vert = XCmax_Stab;
TCmax_Vert = 0.1;
VertSweep = 0;

%% Conceptual config
% Mach = 2
% mach cone angle = 30
% length from cone to end of body = 387 mm
% max wing span = 446 mm


%% CD0 summation
SumBody = body(Re,length,d,Amax,Mach); % Re,length,Amax,Mach
SumWing = wing(Swet_Wing,XCmax_Wing,TCmax_Wing,WingSweep,Mach,Cfturb); % Swet_W,XCmax_Wing,TCmax_Wing,WingSweep,Mach
%SumGlove = glove(Swet_Glove,XCmax_Glove,TCmax_Glove,GloveSweep,Mach,Cfturb); % Swet_Glove,XCmax_Glove,TCmax_Glove,GloveSweep,Mach
SumStab = horizonatal(Swet_Stab,XCmax_Stab,TCmax_Stab,Mach,StabSweep,Cfturb); % Swet_Stab,XCmax_Stab,TCmax_Stab,Mach,StabSweep
SumVert = vertical(Swet_Vert,XCmax_Vert,TCmax_Vert,Mach,VertSweep,Cfturb); % Swet_Vert,XCmax_Vert,TCmax_Vert,Mach,VertSweep,Cf
CDmisc = Cdmisc(Mach,Abase,Sref); % Mach,Abase,Sref

CD0 = (1+leakage) * (((SumBody+SumVert+SumWing+(2*SumStab))/Sref) + CDmisc);
% CD_lp = leakage*CD0;
% 
% 
% CD0 = CD0 + CD_lp;

%% For Best L/D
CL = sqrt(CD0 * pi * e * AR);
CD = 2*CD0;

LDmax = (1/2) * sqrt(pi*e*AR / CD0)

Drag = @(x) CD0 + (x.^2 / (pi * e * AR));
plot(0:0.1:1,Drag(0:0.1:1))
hold on

%% Raymer Component Build up

% Body
function SumBody = body(Re,length,d,Amax,Mach)
    Cfbody = 0.455 / ((log10(Re)^2.58) * ((1 + (0.144 * (Mach^2)))^0.65));
    f = length / (sqrt((4/pi)*(Amax)));
    FFBody = 0.9 + (5/(f^1.5)) + (f/400);
    SumBody = Cfbody*FFBody*(length*d); % Qbody = 1
end

% Wing
function SumWing = wing(Swet_W,XCmax_Wing,TCmax_Wing,WingSweep,Mach,Cf)
    FFWing = (1 + ((0.6/XCmax_Wing) * TCmax_Wing) + (100 * (TCmax_Wing^4))) * ((1.35*(Mach^0.18)*cosd(WingSweep)^0.28));
    QWing = 1.4;
    SumWing = Cf*FFWing*QWing*Swet_W;
end

% Glove
function SumGlove = glove(Swet_Glove,XCmax_Glove,TCmax_Glove,GloveSweep,Mach,Cf)
    FFWing = (1 + ((0.6/XCmax_Glove) * TCmax_Glove) + (100 * (TCmax_Glove^4))) * ((1.35*(Mach^0.18)*cosd(GloveSweep)^0.28));
    QWing = 1.4;
    SumGlove = Cf*FFWing*QWing*Swet_Glove;
end

% Horizaontal Stabilizers
function SumStab = horizonatal(Swet_Stab,XCmax_Stab,TCmax_Stab,Mach,StabSweep,Cf)
    FFWing = (1 + ((0.6/XCmax_Stab) * TCmax_Stab) + (100 * (TCmax_Stab^4))) * ((1.35*(Mach^0.18)*cosd(StabSweep)^0.28));
    QWing = 1.4;
    SumStab = Cf*FFWing*QWing*Swet_Stab;
end

% Vertical Stabilizers
function SumVert = vertical(Swet_Vert,XCmax_Vert,TCmax_Vert,Mach,VertSweep,Cf)
    FFWing = (1 + ((0.6/XCmax_Vert) * TCmax_Vert) + (100 * (TCmax_Vert^4))) * ((1.35*(Mach^0.18)*cosd(VertSweep)^0.28));
    QWing = 1.4;
    SumVert = Cf*FFWing*QWing*Swet_Vert;
end

% Cdmisc
function CDmisc = Cdmisc(Mach,Abase,Sref)
    DQbase = (0.139 + (0.419 * (Mach - 0.161)^2)) * (Abase);
    CDmisc = DQbase / Sref;
end