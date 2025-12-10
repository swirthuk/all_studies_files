clear
clc
x1 = 8; x2 = 8; x3 = -4; x4 = 8;
A = [x1, x2, x3, x4];
digit = 0;
z = "";
mprintf('\nx1=%.0f x2=%.0f x3=%.0f x4=%.0f\n', x1, x2, x3, x4);

for i = 1:4
    if sum(A == A(i)) == 1 then
        digit = A(i);
        if digit == x1
            z = "x1";
        elseif digit == x2
            z = "x2";
        elseif digit == x3
            z = "x3";
        elseif digit == x4
            z = "x4";
        end
        break;
    end
end
mprintf("Переменная, отличная от других: %s = %.0f\n", z, digit);
x = 0.78;
mprintf("x=%.2f\n", x);
n = 1; H = x; S = H;
mprintf('%5s%15s%15s\n', 'n:', 'H:', 'S:');
mprintf('%5d%15.10f%15.10f\n', n, H, S);

while abs(H) > 10^-5
    n = n + 1;
    H = -H * ((2*n - 1) / (2*n^2 + n)) * x^2;
    S = S + H;
    mprintf('%5d%15.10f%15.10f\n', n, H, S);
end
mprintf('Сумма ряда S(x) = %.10f\n', S);
