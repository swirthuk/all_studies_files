clear; clc;
V=[-1, 0, -18, 0, 6];
p=poly(V,'x','c')
x=roots(p)
mprintf('%2.2f   ',x)
V=[-2, -0.08, 0.94, 1.3];
p=poly(V,'x','c')
x=roots(p)
mprintf('\n')
mprintf('%2.2f   ',x)
