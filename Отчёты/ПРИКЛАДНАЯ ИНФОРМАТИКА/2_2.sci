A = [2, 1, 3; 5, 10, 2; 1, 4, 3];
A(2,2) = 3;

zeros_matrix = zeros(4, 4);
ones_matrix = ones(4, 4);
random_matrix = rand(4, 4);
eye_matrix = eye(4, 4);
magic_matrix = magic(4);

v = [1,2,3,4];
k = 2;
X = diag(v, k);

B = [5,2,0;7,3,0;4,1,2];
M = cat(1, A, B); 
N = cat(2, A, B); 
L = blockdiag(A, B);
B(1:3) = [];
L(2:1) = [];
A = [2, 1, 3; 5, 10, 2; 1, 4, 3];
B = [5,2,0;7,3,0;4,1,2];
det_A = det(A);
det_B = det(B);
rank_A = rank(A);
rank_B = rank(B);
inv_A = inv(A);
inv_B = inv(B);
sum_A = sum(A);
sum_B = sum(B);
prod_A= prod(A);
prod_B = prod(B);
max_A = max(A);
max_B = max(B);
min_A = min(A);
min_B = min(B);
