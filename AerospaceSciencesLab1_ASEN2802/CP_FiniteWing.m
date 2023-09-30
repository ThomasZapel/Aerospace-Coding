%% Cp and Angle of Attack
% Author: Thomas Zapel and Mercedes Murray

i=1; 
while i < length(-15:16)+1
    % Declare Angle of Attack
    AOA = -15:16;
    Cp_temp = func("ASEN2802_InfiniteWing_FullRange.csv",AOA(i)); % FILENAME, AOA
    
    %% Best fit lines and averaging for Cp at trailing edge
    %Read in port locations
    Port_Locations = readmatrix("ClarkY14_PortLocations.xlsx");
    %Create vector without any NaN for locations
    Port_Locations_Clean = Port_Locations;
    Port_Locations_Clean(10,:) = [];
    % Create polynomials and evaluate each resultat line to find estimated
    % Cp for the trailing edge
    P1 = polyfit(Port_Locations_Clean(8:9,3),Cp_temp(8:9),1);
    P2 = polyfit(Port_Locations_Clean(10:11,3),Cp_temp(10:11),1);
    y1 = polyval(P1,Port_Locations(:,3));
    y2 = polyval(P2,Port_Locations(:,3));
    
    % Take the average of each of the estimated Cp's found above
    Cp_trail = mean([y1(10),y2(10)]); % adding final Cp to end of Cp vector
    Cp_temp = [Cp_temp(1:9),Cp_trail,Cp_temp(10:end),Cp_temp(1)];
    for j = 1:length(Cp_temp);
        Cp(i,j) = Cp_temp(j);
    end
    i = i + 1;
end

%% Ploting
plot([Port_Locations(:,3);0],Cp(6,:),"-oc"); hold on; grid on
plot([Port_Locations(:,3);0],Cp(1,:),"-or");
plot([Port_Locations(:,3);0],Cp(21,:),"-og");
plot([Port_Locations(:,3);0],Cp(26,:),"-om");
plot([Port_Locations(:,3);0],Cp(end-1,:),"-o","color",[1 (130/255) 0]);
legend("AOA: -10","AOA: 0","AOA: 5","AOA: 10","AOA: 15")


ax = gca; ax.YDir = "reverse";%invert axis
title("Coefficient of Pressure vs. Chord Length")
ylabel("Coefficient of Pressure"); xlabel("Chord Length [in]")



%% Function to find Cp
function Cp = func(filename,AoA)
    % Post-Processing
    Data_T = readtable(filename); % Read in given filename
    Data = table2array(Data_T); % Convert Data to Matrix
    Data_V = mean(Data(AoA == Data(:,8),:)); % Take Average of all Data for same AoA

    q_inf = Data_V(5); % Dynamic pressure from Pitot-Static

    Cp = Data_V(end-15:end) / q_inf; % Calculate Cp for each port pressure
end