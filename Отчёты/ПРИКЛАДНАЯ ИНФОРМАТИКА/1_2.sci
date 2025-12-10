a=2.50;
b=4.20;
C=125.00*%pi/180;

c=sqrt(a^2+b^2-2*a*b*cos(C));

A=acos((b^2+c^2-a^2)/(2*b*c));
B=%pi-A-C;

S=0.5*a*c*sin(B);

mprintf("\n");
mprintf("   СТОРОНЫ ТРЕУГОЛЬНИКА:\n");
mprintf("\nЗначение а = %g см\n", a);
mprintf("Значение b = %g см\n", b);
mprintf("Значение c = %g см\n", c);

mprintf("\n   УГЛЫ ТРЕУГОЛЬНИКА:\n");
mprintf("A = %.2f град.\n", A*180/%pi);
mprintf("B = %.2f град.\n", B*180/%pi);
mprintf("C = %.2f град.\n", C*180/%pi);

mprintf("\n   ПЛОЩАДЬ ТРЕУГОЛЬНИКА:\nS = %.2f кв.см", S)
