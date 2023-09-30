%% Question 10
n = 5;
for i = 1:n
    for j = 1:n
        S(i,j) = sqrt(2 / n) * sin ((pi * (i - 0.5) * (j - 0.5)) / n);
    end
end

%% Question 11
% S_identity = S * S;
% validate = round(S_identity) ~= eye(5);
% if sum(validate) == 0
%     disp("S * S = I(5), no values are different in the matricies")
% end

%% Question 12
% Y = S*X*S; % DST
% X = S*Y*S; % Inverse DST

%% Question 13
% Read in the image and store as a matrix of doubles
X_int = imread("square.jpg");
X_double = double(X_int);

% Find S for DST
n = length(X_double);
for i = 1:n
    for j = 1:n
        S(i,j) = sqrt(2 / n) * sin ((pi * (i - 0.5) * (j - 0.5)) / n);
    end
end

% Perform DST for each color channel
Y_red = S*X_double(:,:,1)*S;
Y_green = S*X_double(:,:,2)*S;
Y_blue = S*X_double(:,:,3)*S;

% Removing unnecessary data
p = 1;
% when p=0, no data are saved
% when p=1, all data are saved
for i = 1:n
    for j = 1:n
        if (i+j > p*2*n)
            Y_red(i,j) = 0;
            Y_green(i,j) = 0;
            Y_blue(i,j) = 0;
        end
    end
end

% Perform Inverse DST to recreate color channels
X_red = S*Y_red*S;
X_green = S*Y_green*S;
X_blue = S*Y_blue*S;

% Concatenate color channels into image
X = cat(3,X_red,X_green,X_blue);
figure(4)

% Display compressed image
imagesc(uint8(X))

% Write to image
imwrite(uint8(X),"compressedP1.jpg")

%% Question 14
% Find non-zero entries in Y matrix
Y = cat(3,Y_red,Y_green,Y_blue);
A = Y~=0;
Y_nonzero_count = sum(A(:));

%% Question 15
a = dir("square.jpg");         
Uncompressed_size = a.bytes;

b = dir("compressed.jpg");
Compressed_size = b.bytes;

CR = Uncompressed_size / Compressed_size;

% p = 0.5, CR = 1.5142, great quality
% p = 0.3, CR = 1.7744, good quality
% p = 0.1, CR = 2.9786, poor quality (blurred and wobbled image)

