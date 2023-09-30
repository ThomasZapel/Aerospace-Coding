%% Calculating Airspeed

% Declare Constants
Patm = 83700;
T_K = 21.8+273.15;
R = 287;

% Read in and post process Data
load("config1.mat");
Data_m = table2array(data);
P = Data_m(:,3);
P_max = max(P);
time = Data_m(:,1);

% Calculating Airspeed
v = sqrt((2 * P * R * T_K) / Patm);
v_max = max(v)

%% Uncertianty in airspeed

% Partial Derivatives
partial_P = (sqrt(R) * sqrt(T_K)) / (sqrt(2) * sqrt(P_max) *sqrt(Patm));
partial_T_atm = - (sqrt(P_max) * sqrt(R) * sqrt(T_K)) / (sqrt(2) * (Patm^(3/2)));
partial_P_atm = (sqrt(P_max) * sqrt(R)) / (sqrt(2) * sqrt(T_K) * sqrt(Patm));

% Uncertianties in measurements
err_P = 49.76;
err_P_atm = 50;
err_T_K = 0.05;

% General Method for uncertianty
term1 = (partial_P * err_P)^2;
term2 = (partial_T_atm * err_T_K)^2;
term3 = (partial_P_atm * err_P_atm)^2;

% Uncertianty in airpseed
delta_v = sqrt(term1 + term2 + term3)
