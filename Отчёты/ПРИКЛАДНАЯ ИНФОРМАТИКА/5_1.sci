clear
clc
x = -10:10;
for i = 1:length(x)
    if x(i) > 5
        y(i) = 8 * x(i);
    elseif x(i) >= -5 & x(i) <= 5
        y(i) = x(i)^2;
    else
        y(i) = sin(x(i));
    end
end
plot(x, y)
