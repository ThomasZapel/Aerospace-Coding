%% ASEN 2012: Project 2: Water Bottle Rocket Flight, Fall 2022
% by: Thomas Zapel
% SID: 10344832
% Date created : 11/20/2022
% last modified: 11/20/2022
%Purpose: To evaluate the trajectory, thrust, air volume, and velocity
% of a water bottle rocket for a set of given constants and initial
% conditons

%Assumptions made:
    % 2D system 
    % No Wind 
    % No forces from stand
    % Isentropic expansion

%Inputs: 
    % X & Z position
    % X & Z velocity 
    % Air volume
    % Air mass
    % Water mass

%Outputs:
    % X & Z velocity
    % X & Z acceleration
    % Rate of change of air volume
    % Rate of change of air mass
    % Rate of change of water mass
    % Thrust (in component form)

clc; clear; close all;
%% ODE Call
const = getConst();
IC = [const.x0;const.z0;const.vx0;const.vz0;const.vol_air0;const.mass_water0;const.mass_air0];
stopCond = odeset("Events", @stopCond_func);
[t,X] = ode45(@(t,X) rocketmotion(t,X),const.tspan,IC,stopCond);

%% Ploting, Verification vs. Calculated
load project2verification.mat;


for i = 1:length(t)
    [~,thrust_xz] = rocketmotion(t(i),X(i,:));
    thrust(i) = norm(thrust_xz);
    i = i + 1;
end


% Height vs. Distance
figure(1)
plot(X(:,1),X(:,2)); hold on; grid on
plot(verification.distance,verification.height,":r")
ylim([0 30]); xlim([0 80])
title("Height vs. Distance"); ylabel("Height (m)"); xlabel("Distance (m)")
legend("Calculated","Verification")
xticks(0:10:80)

% Thrust vs. Time

figure(2)
plot(t,thrust); hold on; grid on
plot(verification.time,verification.thrust,":r")
xlim([0 0.45])
title("Thrust vs. Time"); ylabel("Thrust (N)"); xlabel("Time (s)")
legend("Calculated","Verification")
xticks(0:0.05:0.45)

% Air Volume vs. Time
figure(3)
plot(t,X(:,5)); hold on; grid on
plot(verification.time,verification.airVolume,":r")
xlim([0 0.2])
title("Air Volume vs. Time"); ylabel("Air Volume (m^3)"); xlabel("Time (s)")
legend("Calculated","Verification","Location","northwest")
xticks(0:0.05:0.25)

% Velocity vs. Time
figure(4)
plot(t,X(:,3),"b"); hold on; grid on
plot(t,X(:,4),"g")
plot(verification.time,verification.xVelocity,":r")
plot(verification.time,verification.zVelocity,":p")
ylim([-20 30]); xlim([0 4])
title("Velocity vs. Time"); ylabel("Velocity (m/s)"); xlabel("Time (s)")
legend("Calculated X","Calculated Z","Verification X","Verification Z")
yticks(-20:5:30); xticks(0:0.5:4)
snapnow


%% Rocket Motion Function
function [dX,fThrust] = rocketmotion(t,X)
    const = getConst();
    
    x = X(1);
    z = X(2);
    vx = X(3);
    vz = X(4);
    vol_air = X(5);
    m_water = X(6);
    m_air = X(7);
   
    v = sqrt((vx^2)+ (vz^2));

    % Finding heading for any given velocity
    if z < const.test_height
        head = [cosd(const.theta0);sind(const.theta0)];
    else
        head_x = vx / sqrt((vx^2) + (vz^2));
        head_z = vz / sqrt((vx^2) + (vz^2));
        head = [head_x;head_z];
    end
    
    % Finding pressure
    if vol_air < const.vol_bot && z >= 0
        pres = const.pres0 * ((const.vol_air0 / vol_air)^const.gamma);
    else
        pres_end = const.pres0 * ((const.vol_air0 / const.vol_bot)^const.gamma);
        pres = pres_end * ((m_air / const.mass_air0)^const.gamma);
    end
    disp("Problems Here:")
    disp("Pressure in bottle: "); disp(pres);
    disp("Atmo Presure: "); disp(const.pres0);

    % Phase 1
    if vol_air < const.vol_bot && z >= 0 && pres > const.pres_a
        % volume rate of change Calculations
        a = (const.vol_air0 / vol_air)^const.gamma;
        b = (const.pres0 * a) - const.pres_a;
        c = (2 / const.rho_water) * b;
        vol_dot = const.Cdis * const.At * sqrt(c);

        % Mass Calculations
        m_dot_water = - const.Cdis * const.At * sqrt(2 * const.rho_water * (pres - const.pres_a));
        m_dot_air = 0;
        m = const.mass_bot + m_air + m_water;
        
        % Force due to Gravity
        fGrav = [0; - m * const.g0];

        % Force due to Drag
        fDrag_x = - head(1) * ((1/2) * const.Cdrag * const.Ac * const.rho_air * (v^2));
        fDrag_z = - head(2) * ((1/2) * const.Cdrag * const.Ac * const.rho_air * (v^2));
        fDrag = [fDrag_x;fDrag_z];

        % Force due to Thrust
        fThrust_x = head(1) * (2 * const.Cdis * const.At * (pres - const.pres_a));
        fThrust_z = head(2) * (2 * const.Cdis * const.At * (pres - const.pres_a));
        fThrust = [fThrust_x;fThrust_z];
    % Phase 2
    elseif pres > const.pres_a% This conditional might cause issues b/c vol_air cannot be greater than vol_bot
        vol_dot = 0;
        m_water = 0;
        rho = m_air / const.vol_bot;
        temp = pres / (rho * const.R_air);

        % Critical pressure calculations
        a = 2 / (const.gamma + 1);
        b = const.gamma / (const.gamma - 1);
        pres_crit = pres * (a^b);

        % Exit Velocity Calculations
        if pres_crit > const.pres_a
            pres_exit = pres_crit;
            mach_exit = 1;
            a = 2 / (const.gamma + 1);
            temp_exit = a * temp;
            rho_exit = pres_exit / (const.R_air * temp_exit);
            
        else
            pres_exit = const.pres_a;

            a = pres / const.pres_a;
            b = (const.gamma - 1) / const.gamma;
            c = (const.gamma - 1) / 2;
            mach_exit = sqrt(((a^b) - 1) / c);

            d = (const.gamma - 1) / 2;
            temp_exit = temp / (1 + (d * (mach_exit^2)));
            rho_exit = const.pres_a / (const.R_air * temp_exit);
        end
        
        v_exit = mach_exit * (sqrt(const.gamma * const.R_air * temp_exit));

        % Mass Calculations
        m_dot_water = 0;
        m_dot_air = - const.Cdis * rho_exit * const.At * v_exit;
        m = const.mass_bot + m_air;
        
        % Force due to Gravity
        fGrav = [0; - m * const.g0];

        % Thrust Calculations
        fThrust_x = head(1) * ((-m_dot_air * v_exit) + ((pres_exit - const.pres_a) * const.At));
        fThrust_z = head(2) * ((-m_dot_air * v_exit) + ((pres_exit - const.pres_a) * const.At));
        fThrust = [fThrust_x;fThrust_z];

        % Force due to Drag
        fDrag_x = - head(1) * ((1/2) * const.Cdrag * const.Ac * const.rho_air * (v^2));
        fDrag_z = - head(2) * ((1/2) * const.Cdrag * const.Ac * const.rho_air * (v^2));
        fDrag = [fDrag_x;fDrag_z];
    % Phase 4
    elseif z <= 0
        % Null changes
        fGrav = [0;0];
        fDrag = [0;0];
        fThrust = [0;0];
        m_dot_water = 0;
        m_dot_air = 0;
        m = const.mass_bot + m_air;
        vol_dot = 0;
        xv = 0;
        zv = 0;


    % Phase 3
    else
        % Null changes
        vol_dot = 0;
        m_dot_water = 0;
        m_dot_air = 0;

        % Force due to gravity
        m = const.mass_bot + m_air;
        fGrav = [0; - m * const.g0];

        % Force due to Thrust
        fThrust = [0;0];

        %Force due to Drag
        fDrag_x = - head(1) * ((1/2) * const.Cdrag * const.Ac * const.rho_air * (v^2));
        fDrag_z = - head(2) * ((1/2) * const.Cdrag * const.Ac * const.rho_air * (v^2));
        fDrag = [fDrag_x;fDrag_z];

    end
    fnet = fGrav + fDrag + fThrust;
    ax = fnet(1) / m;
    az = fnet(2) / m;

    dX = [vx;vz;ax;az;vol_dot;m_dot_water;m_dot_air];

end


%% Constants Function
function const = getConst()

    % Givens
    const.g0 = 9.81; %m/s Acceleration due to gravity
    const.Cdis = 0.8; % discharge constant
    const.rho_air = 0.961; % kg/m^3 ambient air density
    const.vol_bot = 0.002; % m^2 volume of empty bottle
    const.pres_a = 12.1 * 6894.76; % psi atmospheric pressure
    const.gamma = 1.4; % ratio of specific heats for air
    const.rho_water = 1000; %kg/m^3 water density
    const.dia_t = 0.021; % cm -> m throat diameter
    const.dia_b = 0.105; % cm -> m bottle diameter
    const.R_air = 287; % J / (kg*K) Gas constant
    const.mass_bot = 0.15; % empty mass [kg]
    const.Cdrag = 0.5; % drag coefficient
    const.pres0 = (81.5 * 6894.76) + const.pres_a; % psi inital air pressure
    const.vol_water0 = 0.001; % m^3 inital water volume
    const.t0 = 300; % K inital air temp
    const.vx0 = 0; % m/s inital velocity
    const.vz0 = 0;
    const.theta0 = 45;% degree inital angle
    const.x0 = 0; % m inital horizontal
    const.z0 = 0.25; % m inital vertical
    const.ls = 0.5; % m test stand length

    % Time span
    const.tspan = [0 8]; % integration time span
    
    % Calculated constants
    const.vol_air0 = const.vol_bot - const.vol_water0;
    const.mass_air0 = ((const.pres0 * const.vol_air0) / (const.R_air * const.t0));

    const.mass_water0 = const.vol_water0 * const.rho_water;

    const.Ac = pi * ((const.dia_b / 2)^2);
    const.At = pi * ((const.dia_t / 2)^2);

    % Test Stand Z height
    const.test_height = (0.5 * sind(45)) + const.z0;
end

%% Stop Condition Function
function [value, isterminal, direction] = stopCond_func(t,X)
    value = (X(2) <= 0); % Stop when z is equal to 0
    isterminal = 1; % Stops integration
    direction = 0;
end
