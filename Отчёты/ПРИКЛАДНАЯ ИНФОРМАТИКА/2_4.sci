function rez=g(a,b)
    rez = ((sqrt(a+b)-a^2)/(a*b+a-b))+sqrt((abs(a-b)/3));
endfunction

s = 10;
t = 8;

result = g(-1.2, s) + g(t, s) - g(2, s*t)
disp(result);
