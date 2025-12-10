A = [21, 4, 2, -13, 10, 5, -2, 0, -1, 7];
mprintf("Исходный вектор A\n"); disp(A)
elem = 0;
equal = 0;

for i = 1:length(A)
    if A(i) < 0
        elem = A(i);
        equal = i;
        break;
    end
end
mprintf("Первый отрицательный элемент вектора A(%d) = %.1f\n", equal, elem);
A = [1,3,-4,5,-8;0,-10,9,9,7;-4,21,3,5,0;12,0,4,2,13];
mprintf("Исходная матрица:\n"); disp(A);
x = 100; mprintf("Число x = %d\n", x);
for i = 1:4
    maxi = max(A(i, :));
    for j = 1:5
        if A(i, j) == maxi
            A(i, j) = x;
        end
    end
end

mprintf("Полученная матрица:\n");
disp(A);
