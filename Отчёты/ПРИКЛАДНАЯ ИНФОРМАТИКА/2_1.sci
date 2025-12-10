function rez=y1(b)
    rez=(1./(b.^2))-cos(b)-3;
endfunction

db = 1.5;
b = -5:db:8;
mprintf("Значение функции y:\n");
y=y1(b);
disp(y);
