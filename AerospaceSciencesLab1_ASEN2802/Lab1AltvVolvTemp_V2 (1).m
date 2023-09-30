%%Altitude, Temp, and Volume plots

Alt = 0:30000;

[T,a,P,rho] = atmoscoesa(Alt);

%plot(Alt,T)


title('Temperature V. Altitude')
xlabel('Altitude (m)')
ylabel('Temperature (K)')
m_He = 0.00125; %kg
m_b = 0.010655; %kg

V_disp = (m_He + m_b) ./ rho;



%plot(Alt,V_disp)

title('Volume V. Altitude')
ylabel('Volume (m^3)')
xlabel('Altitude(m)')

%% Hot Air Balloon

V_disp_hot = 0.13; %m^3
m_hot = 0.02661; %kg

mV = m_hot / V_disp_hot;
i = 1;
while T_in < 522
    
    T_in(i) = P(i) / (287 * (rho(i) -mV));
    i = i+1;
end

plot(Alt(1:11249),T_in)
title('Temperature V. Altitude')
xlabel('Altitude (m)')
ylabel('Temperature (K)')
yline(T_in(end),"--","Max Temp")
xline(11259,"--","Max Altitude")
ylim([340 590])
xlim([0 14000])

yline
