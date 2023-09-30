
offset = 0;
% Main Wing Geometry
c = 0.065;
WingSweep = 35;

    %originally 0.162
wing_offset = 0.17;
ct = 0.11;
b_prime_half = ((wing_offset) * sind(30)) / sind(60 - WingSweep);


b_prime = b_prime_half * 2;
b = b_prime * cosd(WingSweep);
Sref_Wing = b_prime * c;
y_bar = ((2*c) + (2 * b_prime_half * cosd(90-WingSweep))) / 4;
Xmac = ((b * tand(WingSweep)) + c) / 4;
a0 = 0.11;
AR = (b^2) / Sref_Wing;
AR_corr = AR * (1 + (1.9 * 0.06 / b));
e = 1 / (1.05 + (0.007*pi*AR_corr));
a = a0 / (1 + ((57.3 * a0) / (pi * e * AR_corr)));




% Canard Geometry
%ct = 0.12; % canard chord length [m] %offset goes here
CanardSweep = 60;
Xtmac = (ct * (2*tand(30)*tand(60) + 1)) / 6; % canard mean aero chord [m]

St = (ct.^2) * tand(30); % [m^2]
S_cone = ((ct)^2) * tand(18.6); % [m^2]
St_wet = St - S_cone; % [m^2]


AR_t = ((2 * ct * tand(30)).^2) / St;
e_t = 1 / (1.05 + (0.007*pi*AR_t));
a_t = a0 / (1 + ((57.3 * a0) / (pi * e_t * AR_t)));

% Tail Geometry
bn = 0.06;
TailSweep_rad = (pi/2) - atan(bn / c); % not used
TailSweep = TailSweep_rad .* 180 ./ pi; % not used
Sn_total = bn * c * 2;
% Xnmac = ((bn .* tand(TailSweep)) + c) / 6;

% CG calculations
% Plastic config = 0.162655 Hat config = 0.1955
arm_rocket = 0.1955 + offset; %offset
arm_wing = (y_bar) + 0.162 + offset; %offset
arm_canard = ((2/3) * ct) + offset; %offset
m_wing = Sref_Wing * 377.167; % [g]

% Plastic config = 165g Hat config = 97g
m_rocket = 97; % [g]
m_canard = St * 377.167; % wet area of canard * density [g]
m_tail = Sn_total * 377.167;
m_struct = ((0.5 * (ct^2) * tand(18.6)) + (0.5 * (ct^2) * tand(20))) * 377.167;
Moment_rocket = arm_rocket * m_rocket;
Moment_wing = arm_wing * m_wing;
Moment_canard = arm_canard .* m_canard;
Moment_tail = ((b_prime_half * sind(WingSweep)) + ((1/2) * c) + 0.162 + offset) * m_tail;
Moment_struct = (ct / 3) * m_struct;

CG_total = (Moment_rocket + Moment_wing + Moment_canard + Moment_tail + Moment_struct) ./ (m_rocket + m_wing + m_canard + m_tail + m_struct);

% Stability calcuations
h_cg = (CG_total - wing_offset - offset) / c;
h_acw = Xmac / c;
lt = CG_total - Xtmac;
Vh = (lt .* St) ./ (c * Sref_Wing); % St_ref or St_wet???

h_np = h_acw - (Vh * (a_t / a));
CG = CG_total(end) - wing_offset - offset
NP = h_np(end) * c


SM = h_np - h_cg;

slope = -a * SM;
% Questions
% Vh - St_ref or St_wet???
% for neutral stability do we want h_cg - h_acw = Vh?

slope
SM
Vh


figure(1)
fun = @(x) (slope*x);
hold on; grid on;
fplot(fun,[-0.5 0.5],"LineWidth",1.5);
title("Trim diagram");
xlabel("AOA_e"); ylabel("Cm_cg")

%Stability of Delta wing
a = a0 / (1 + ((57.3 * a0) / (pi * e * AR_corr)));
SM = 0.13865;
slope = -a * SM;
fun = @(x) (slope*x);grid on;
fplot(fun,[-0.5 0.5],"LineWidth",1.5);
title("Trim diagram");
xlabel("AOA_e"); ylabel("Cm_cg")
legend("Swept Wing", "Delta Wing")

%Required Tail Incidence:
% Swept Wing:
a = a0 / (1 + ((57.3 * a0) / (pi * e * AR_corr)));

a_t = a0 / (1 + ((57.3 * a0) / (pi * e_t * AR_t)));


it = a - a_t


