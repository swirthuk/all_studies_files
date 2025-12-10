clear; clc;
deff('[y]=f(x)', 'y = (6/(x^2 - 1)) - (2/(x - 1)) - (2 - (x + 4)/(x - 1))');
x0 = 0; //начинаем поиск с нуля
result = fsolve(x0, f);
mprintf('Ответ = %2.3f\n', result);
