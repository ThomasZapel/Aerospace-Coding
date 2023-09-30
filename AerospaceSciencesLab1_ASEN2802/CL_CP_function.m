%% Cl and CD for Finite Wing
% Author: Thomas Zapel and Mercedes Murray

i=1; 
while i < length(-15:16)+1
   AOA = -15:16; 
   
    Cp = func("ASEN2802_InfiniteWing_FullRange.csv",AOA(i)); % FILENAME, AOA%% Best fit lines and averaging for Cp at trailing edge
    
    %Read in port locations
    Port_Locations=readmatrix("ClarkY14_PortLocations.xlsx");
    
    %Create vector without any NaN for locations
    Port_Locations_Clean = Port_Locations;
    Port_Locations_Clean(10,:) = [];
    
    % Create polynomials and evaluate each resultat line to find estimated
    % Cp for the trailing edge
    P1 = polyfit(Port_Locations_Clean(8:9,3),Cp(8:9),1);
    P2 = polyfit(Port_Locations_Clean(10:11,3),Cp(10:11),1);
    y1 = polyval(P1,Port_Locations(:,3));
    y2 = polyval(P2,Port_Locations(:,3));
    
    %Take the average of each of the estimated Cp's found above
    Cp_trail = mean([y1(10),y2(10)]); % adding final Cp to end of Cp vector%% Ploting
    Cp = [Cp(1:9),Cp_trail,Cp(10:end)];
    %plot(Port_Locations(:,3),Cp,"-o"); 
    %hold on
    %ax = gca; ax.YDir = "reverse";%invert axis
    %grid on
    
    %%coefficients 
    chord = 3.5031; %%inches
    dz = Port_Locations(:,4);
    dy = Port_Locations(:,3);
    cn = trapz(dy,Cp)*(-1/chord);%%coeff of normal force
    ca = trapz(dz,Cp)*(1/chord); %%coeff of axial force
    
    %coefficient of lift = area under cp curve 
    cl(i) = (cn * cosd(AOA(i))) - (ca * sind(AOA(i)));
    %coefficient of drag 
    cd(i) = (cn * sind(AOA(i))) + (ca * cosd(AOA(i)));
    
    i=i+1;

end 

ClarkY14 = readmatrix("ClarkY14_NACA_TR628.xlsx");

%% Plotting
angle = -15:16;
figure (1)
plot(angle,cl,"-o","color",[0 (150/255) 1]); hold on
plot(ClarkY14(:,1),ClarkY14(:,2),"-or")
title("Coefficient of Lift vs. Angle of Attack"); grid on
ylabel("Coefficient of Lift"); xlabel("Angle of Attack [^{\circ}]");
legend("Calculated CL","NACA Clark Y14 CL")

figure(2)
plot(angle,cd,"-o","color",[0 (150/255) 1]); hold on
plot(ClarkY14(:,1),ClarkY14(:,3),"-or")
title("Coefficient of Drag vs. Angle of Attack");grid on
ylabel("Coefficient of Drag"); xlabel("Angle of Attack [^{\circ}]");
legend("Calculated CD","NACA Clark Y14 CD")

[~,ind] = max(cl)

%% Function to find Cp
function Cp = func(filename,AoA)
    % Post-Processing
    Data_T = readtable(filename); % Read in given filename
    Data = table2array(Data_T); % Convert Data to Matrix
    Data_V = mean(Data(AoA == Data(:,8),:)); % Take Average of all Data for same AoA
    q_inf = Data_V(5); % Dynamic pressure from Pitot-Static
    Cp = Data_V(end-15:end) / q_inf; % Calculate Cp for each port pressure

end