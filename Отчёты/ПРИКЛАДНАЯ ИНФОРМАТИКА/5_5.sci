clear; clc;

function y = f(a, b, x)
    if x < 1.5
        y = ((tan(x)^2)/5) + ((a*x)/3);
    elseif x == 1.5
        y = sqrt(abs(1 + 0.3*x^3)) + a^x;
    else
        y = (a/2.5) + atan(x)^2;
    end
endfunction

dx = 0.25; 
x = 1:dx:3; 
a_values = [7.376; 8.33; 5.14];
b = 1;

for k = 1:length(a_values)
    a = a_values(k);
    mprintf("\nПри a=%.3f:\n", a);
    
    for i = 1:length(x)
        mprintf("x=%.1f  y=%f\n", x(i), f(a, b, x(i)));
    end
end
