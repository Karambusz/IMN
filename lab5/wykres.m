clc;clear;
set(0,'DefaultAxesFontSize',15,'DefaultAxesFontName','Arial Cyr');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data = readtable('relaksacja_k.dat');

figure

plot(data.Var1(1:81), data.Var2(1:81), 'r',  'LineWidth', 4);
hold on;
plot(data.Var1(82:214), data.Var2(82:214), 'g',  'LineWidth', 4);
hold on;
plot(data.Var1(215:372), data.Var2(215:372), 'b',  'LineWidth', 4);
hold on;
plot(data.Var1(373:511), data.Var2(373:511), 'm',  'LineWidth', 4);
hold on;
plot(data.Var1(512:517), data.Var2(512:517), 'k',  'LineWidth', 4);

legend({'$k = 16$', '$k = 8$','$k = 4$','$k = 2$','$k = 1$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
 title('S(it)');
 xlabel('it');
 ylabel('S');
 
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure
dataMap = readmatrix('mapa_relaksacja_k_16.dat');
dataM = dataMap.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
title('$k=16$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

figure
dataMap = readmatrix('mapa_relaksacja_k_8.dat');
dataM = dataMap.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
title('$k=8$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


figure
dataMap = readmatrix('mapa_relaksacja_k_4.dat');
dataM = dataMap.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
title('$k=4$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

figure
dataMap = readmatrix('mapa_relaksacja_k_2.dat');
dataM = dataMap.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
title('$k=2$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

figure
dataMap = readmatrix('mapa_relaksacja_k_1.dat');
dataM = dataMap.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
title('$k=1$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

