clear
clc
function z=u(x,y,b,c)
    if x>=6
        z=sqrt(c)*(x+b*c)
    else
        z=((sqrt(c))/x)*(x-b*c)
    end
endfunction
y = 0.2; b = 0.78; c = [0.01;0.02;0.4;0.9]; x = 9*c+b*sqrt(y)
mprintf('\nЗначение функции U= %.3f',u(x,y,b,c))
