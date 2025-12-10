fi = 0.01:0.01:2*%pi-0.01;
p = (2./sin(fi)) + 3;
polarplot(fi, p);
legend('r = (2/sin(fi)) + 3');
