%% ASEN 2012: Project 1 - Calorimeter best fits
% Created by: Thomas Zapel
% Student number: 109344832
% Last edited: 10/17/2022
% Enhanced Least Squares polynomial caluator function at bottom
% Now includes ability to find sigma_y of the given data set

%% Reading and Setting Variables
SampleD = readtable("SampleD");
data = SampleD(:,2:end);
time = data{:,1};
cal1 = data{:,2};
cal2 = data{:,5};
cal_avg = (cal1+cal2)/2; % Average of both cal readings


%% Fitting t0 inital temeprature of the calorimeter

[~,min_ind] = min(cal_avg); %find minimum temperature, used for length of best fit line

[x_hat_t0,f_t0,sigma_y_t0] = leastSquares(time(1:min_ind),cal_avg(1:min_ind),1);

% t0 found, with error
t0_err = sigma_y_t0; % Other way to find error?

% Find times when the temperature is measured above 2 times the
% error
time_above = time((diff(cal_avg) > (t0_err*2)));
% Find where the time where the difference between the time that
% the points are above 2 times the error and the time of the
% minimum temeperature value
[~,min_diff_ind] = min(abs(time_above - time(min_ind)));

% Time of the index where the minimum difference of time is
% where t0 occurs
t0 = f_t0(time_above(min_diff_ind));

%% Fitting t1 - inital temeprature of the sample
% Boiling water data
water = data{:,3};

[x_hat_water,f_t1,sigma_y_t1] = leastSquares(time,water,4); %Line of best fit function

% t1 found, with error
t1 = f_t1(end);
t1_err = sigma_y_t1;

%% Fitting t2 - final temperature of the sample
[max_temp,max_ind] = max(cal_avg);

[x_hat_t2,f_t2,sigma_y_t2] = leastSquares(time(max_ind:end),cal_avg(max_ind:end),1);

%Find time when t2 occurs
[~,time_t2] = min(abs(cal_avg - (f_t2(time_above(min_diff_ind)) + t0) / 2));

% t2 found with error
t2 = f_t2(time(time_t2));
t2_err = sigma_y_t2;

%% Function for Least squares
function [x_hat,f,sigma_y] = leastSquares(t,y,p)

    % create H matrix
    for i = 0:p %iterate this loop from 0 to the order
        my_field = strcat('Col',num2str(i)); %create temp variables names
        H_struct.(my_field) = t.^i; % name structure values and name them
    end
    H = table2array(struct2table(H_struct)); % Convert struture to matrix
    H = fliplr(H); %flip H about "vertical axis"
    
    % compute coefficient vector, x_hat
    x_hat = inv(H'*H)*H'*y;
    
    % do not change the following lines of code: this will generate the
    % anonymous function handle "f" for you
    f = '@(x)';
    for i = 0:p
        f = strcat(f,'+',strcat(string(x_hat(i+1)),'.*x.^',string(p-i)));
    end
    eval(strcat('f = ',f,';'))

    %Error and Residual sum of squares
    N = length(t);
    sigma_y = sqrt((1 / (N - 2)) * sum((f(t) - y).^2));

end
