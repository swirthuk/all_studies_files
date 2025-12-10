n = 10;
x = linspace(0.1, 0.1, 1);
S = zeros(1, length(x));
for k = 1:n
    term = (k^2 + 1) / factorial(k) * (x / 2).^k;
    S = S + term;
end
x = 30;
y = (x.^2 / 4) + (x / 2) + 1;
mprintf("Значения суммы S:"); disp(S);
mprintf("Значения функции y:"); disp(y);
