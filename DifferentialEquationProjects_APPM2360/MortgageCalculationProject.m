%% 3.2.1 Fixed rate mortgage

%% Plotting with step size h = 0.5
h = 0.5;
A = [750000];
t = [0];
r = 0.05;

%loop Finding slope at each point

i = 1;
while A > 0
%Loop Body
Am(i) = (r * A(i)) - (12 * 4000); %find A' (slope of A at each step)
A(i+1) = (Am(i) * h) + A(i);
t(i+1) = t(i) + h;
i = i + 1;
end
fprintf("Mortgage will be paid off in %d Years!\n",t(end))

figure(1)
plot(t,A,"-or")
hold on
% Plotting A(t) - True Solution
fplot(@(t) 960000 - (210000 / exp(-0.05 * t)),[0,31],"-c");
title("Dollars Remaining vs. Time");
xlabel("Time (Years)");
ylabel("Dollars Remaining in Hundred Thousands($)");
legend("Numerical Solution (h = 0.01)","True Solution");
ylim([0,800000]);
grid on

%% Plotting with step size h = 0.01

%Declare step size and inital conditions
h = 0.01;
A = [750000];
t = [0];
r = 0.05;

%loop Finding slope at each point

i = 1;
while A > 0
%Loop Body
Am(i) = (r * A(i)) - (12 * 4000); %find A' (slope of A at each step)
A(i+1) = (Am(i) * h) + A(i);
t(i+1) = t(i) + h;
i = i + 1;
end
fprintf("Mortgage will be paid off in %d Years!\n",t(end))

figure(2)
plot(t,A,"-r");
% Plotting A(t) - True Solution
hold on
fplot(@(t) 960000 - (210000 / exp(-0.05 * t)),[0,31],"-c");
title("Dollars Remaining vs. Time");
xlabel("Time (Years)");
ylabel("Dollars Remaining in Hundred Thousands($)");
legend("Numerical Solution (h = 0.01)","True Solution");
ylim([0,800000]);
grid on;

%% 3.2.2 Variable rate mortgage

% Eulers Method with h = 0.01
% inital values
h = 0.01;
A = 750000;
t = 0;
r = 0.03;

%loop Finding slope at each point

i = 1;
while A > 0
%Loop Body
if t(i) > 5
    r(i) = 0.05 + (0.015 * sqrt(t(i) - 5));
else
    r(i) = 0.05;
end

Am(i) = (r(i) * A(i)) - (12 * 4000); %find A' (slope of A at each step)
A(i+1) = (Am(i) * h) + A(i);
t(i+1) = t(i) + h;
i = i + 1;
end
fprintf("Mortgage will be paid off in %d Years!\n",t(end))

plot(t,A)
hold on
%fplot(@(t,r) (48000 / r) + (( 750000 - (48000 / r)) / exp(-r * t)),[0,31],"-c");
title("Dollars Remaining vs. Time");
xlabel("Time (Years)");
ylabel("Dollars Remaining in Hundred Thousands($)");
legend("Numerical Solution (P = $4000)","True Solution");
ylim([0,800000]);
grid on