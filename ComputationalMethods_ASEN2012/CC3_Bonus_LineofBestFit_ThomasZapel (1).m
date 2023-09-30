%% ASEN 2012: Coding Challenge #3 - Polynomial Least Squares Regression
% by: Thomas Zapel
% SID: 109344832
% last modified: 10/7/2022
%
% OUTLINE: 
% The goal of this problem is to write a LeastSquares function that
% will take in vectors for t, y, and p, returning: 
%     x_hat : the coefficients for any polynomial of order p
%       f   : an anonymous function representing the polynomial
% 
% for this section of the challenge, you will be asked to plot the given
% stream of data with the MOST APPROPRIATE ORDER POLYNOMIAL, using your
% function for a LeastSquares regression.
%
% NOTE: use of polyfit or polyval will not be accepted for this challenge
% problem

% read in and extract data
data = readmatrix('BonusData.xlsx');
t = data(:,1);
y = data(:,2);

% plot the data and compare to the LS solution
figure(2);hold on
    
    % plot data
    plot(t,y,"x")
    pause(100/1000)

    % using a FOR loop, plot multiple polynomial lines of best fit
    order = 10;
    for i = 1:order
        [x_hat,f] = leastSquares(t,y,i);
        plot(t,f(t));
        
    end
    
    
hold off
%% Function Defintion
function [x_hat,f] = leastSquares(t,y,p)

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
    
end

