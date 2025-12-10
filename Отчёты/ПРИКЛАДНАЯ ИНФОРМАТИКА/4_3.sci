clear
clc
a=[2.74,-1.18,1.23;-1.18,1.71,-0.52;1.23,-0.52,0.62];
b=[0.16;1.81;-1.12];
mprintf('Функция fsolve:\n')
function [y]=fn(x)
    y(1) = 2.74*x(1) - 1.18*x(2) + 1.23*x(3) - 0.16;
    y(2) = -1.18*x(1) + 1.71*x(2) - 0.52*x(3) - 1.81;
    y(3) = 1.23*x(1) - 0.52*x(2) + 0.62*x(3) + 1.25;
endfunction
disp(fsolve([0;0;0],fn));
mprintf('\n')
x=inv(a)*b
mprintf(' Обратная Матрица:\n')
disp(x)

mprintf('\n Метод Крамера\n')

a1=a;a1(:,1)=b;
a2=a;a2(:,2)=b;
a3=a;a3(:,3)=b;
D=det(a);
d(1)=det(a1);d(2)=det(a2);d(3)=det(a3);
x=d/D
disp(x)
