A = importdata('datasqr.txt', ' ');
hold on
plot(log(A(:,1)),log(A(:,2)), 'LineWidth', 1)
len = length(A(:,1));
rangestart = length(A(:,1)) / 4;
% plot(log(A(rangestart:len,1)),log(A(rangestart:len,2)), 'black')
x = log(A(rangestart:len,1));
y = log(A(rangestart:len,2));
P = polyfit(x, y, 1);
yfit = P(1) * x + P(2);
plot(x, yfit, 'r', 'LineWidth', 2)
disp(P(1))