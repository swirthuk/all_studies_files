clear
clc
clf

x = [-3:0.5:3];

y1 = (1 + abs(x)) ./ ((1 + x + x.^2).^(1./8));
y2 = (1 + cos(x).^4) ./ (3 + x);

plot(x,y1,'LineStyle','--','Color','r','Thickness',5,...
'Marker','s','MarkerEdgeColor','b','markerFaceColor','y',...
'MarkerSize',10)

plot(x,y2,'LineStyle','-','Color','g','Thickness',3,...
'Marker','o','MarkerEdgeColor','r','markerFaceColor','k',...
'MarkerSize',10)

xtitle('Графики функций y1(x), y2(x)', 'X', 'Y');
legend('y1(x)', 'y2(x)', 1);
xgrid;
