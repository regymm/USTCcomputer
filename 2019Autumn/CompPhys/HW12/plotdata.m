A = importdata('data.txt', ' ');
datanum = length(A(1,:));
Rs = A(:,1);
plot(A(:,1), A(:, 2:datanum), 'k.', 'MarkerSize', 0.01)
