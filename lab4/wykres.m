clc;clear;

set(0,'DefaultAxesFontSize',15,'DefaultAxesFontName','Arial Cyr');
%%%%%%%%%%%%Relaksacja globalna%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data = readtable('relaksacja_globalna_0.6.dat');
data1 = readtable('relaksacja_globalna_1.0.dat');
figure;
plot(data.Var1(2:end), data.Var2(2:end), 'r',  'LineWidth', 4);
hold on;
plot(data1.Var1(2:end), data1.Var2(2:end), 'b',  'LineWidth', 4);
set(gca, 'XScale', 'log');
ylim([0, 5000]);
legend({sprintf('$\\;\\omega = 0.6\\;\\;(%i\\;iteracji)\\;$', max(data.Var1) + 1),...
    sprintf('$\\;\\omega = 1.0\\;\\;(%i\\;iteracji)\\;$', max(data1.Var1) + 1)},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Relaksacja globalna');
xlabel('it');
ylabel('S(it)');

%%%%%%%%%%%%Relaksacja globalna (mapa)%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure;
dataMap = readmatrix('mapa_relaksacja_globalna_0.6.dat');
dataM = dataMap.';
% surf(dataM)
% colormap jet
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
title('$Relaksacja \;\; globalna \;:\; \omega = 0.6$','Interpreter','latex');
xlabel('i','Interpreter','latex') 
ylabel('j','Interpreter','latex')


figure;
dataMap = readmatrix('mapa_relaksacja_globalna_1.0.dat');
dataM = dataMap.';
% surf(dataM)
% colormap jet
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
title('$Relaksacja \;\; globalna \;:\; \omega = 1.0$','Interpreter','latex');
xlabel('i','Interpreter','latex') 
ylabel('j','Interpreter','latex')
% h = pcolor(dataM);
% set(h, 'EdgeColor', 'none');
% [m, n] = size(dataM);
% % xticks(0:15:n);
% % yticks(0:15:m);
% % xt = get(gca, 'XTick');
% % set(gca, 'XTick',xt, 'XTickLabel',xt/10)
% % yt = get(gca, 'YTick');
% % set(gca, 'YTick',yt, 'YTickLabel',yt/10)
% colormap(gca,'jet')
% colorbar
% title('$Relaksacja \;\; globalna \;:\; \omega = 0.6$','FontSize', 20, 'Color',...
%     'k', 'FontWeight', 'bold','Interpreter','latex');
% xlabel('i','FontSize', 20, 'Color', 'k', 'FontWeight', 'bold','Interpreter','latex') 
% ylabel('j','FontSize', 20, 'Color', 'k', 'FontWeight', 'bold','Interpreter','latex')

%%%%%%%%%%%%Relaksacja lokalna%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data = readtable('relaksacja_lokalna_1.0.dat');
data1 = readtable('relaksacja_lokalna_1.4.dat');
data2 = readtable('relaksacja_lokalna_1.8.dat');
data3 = readtable('relaksacja_lokalna_1.9.dat');
figure;
plot(data.Var1(2:end), data.Var2(2:end), 'r',  'LineWidth', 4);
hold on;
plot(data1.Var1(2:end), data1.Var2(2:end), 'm',  'LineWidth', 4);
hold on;
plot(data2.Var1(2:end), data2.Var2(2:end), 'b',  'LineWidth', 4);
hold on;
plot(data3.Var1(2:end), data3.Var2(2:end), 'g',  'LineWidth', 4);

set(gca, 'XScale', 'log');
ylim([0, 3000]);
legend({sprintf('$\\;\\omega = 1.0\\;\\;(%i\\;iteracji)\\;$', max(data.Var1) + 1),...
    sprintf('$\\;\\omega = 1.4\\;\\;(%i\\;iteracji)\\;$', max(data1.Var1) + 1),...
    sprintf('$\\;\\omega = 1.8\\;\\;(%i\\;iteracji)\\;$', max(data2.Var1) + 1),...
    sprintf('$\\;\\omega = 1.9\\;\\;(%i\\;iteracji)\\;$', max(data3.Var1) + 1)},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Relaksacja lokalna');
xlabel('it');
ylabel('S(it)');

%%%%%%%%%%%%Relaksacja lokalna (mapa)%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% figure;
% dataMap = readmatrix('mapa_relaksacja_lokalna_1.0.dat');
% dataM = dataMap.';
% h = pcolor(dataM);
% set(h, 'EdgeColor', 'none');
% colormap(gca,'jet');
% % surf(dataM)
% % colormap jet
% colorbar
% title('$Relaksacja \;\; lokalna \;:\; \omega = 1.0$','Interpreter','latex');
% xlabel('i','Interpreter','latex') 
% ylabel('j','Interpreter','latex')
% 
% 
% figure;
% dataMap = readmatrix('mapa_relaksacja_lokalna_1.4.dat');
% dataM = dataMap.';
% h = pcolor(dataM);
% set(h, 'EdgeColor', 'none');
% colormap(gca,'jet');
% % surf(dataM)
% % colormap jet
% colorbar
% title('$Relaksacja \;\; lokalna \;:\; \omega = 1.4$','Interpreter','latex');
% xlabel('i','Interpreter','latex') 
% ylabel('j','Interpreter','latex')
% 
% figure;
% dataMap = readmatrix('mapa_relaksacja_lokalna_1.8.dat');
% dataM = dataMap.';
% h = pcolor(dataM);
% set(h, 'EdgeColor', 'none');
% colormap(gca,'jet');
% % surf(dataM)
% % colormap jet
% colorbar
% title('$Relaksacja \;\; lokalna \;:\; \omega = 1.8$','Interpreter','latex');
% xlabel('i','Interpreter','latex') 
% ylabel('j','Interpreter','latex')
% 
% figure;
% dataMap = readmatrix('mapa_relaksacja_lokalna_1.9.dat');
% dataM = dataMap.';
% h = pcolor(dataM);
% set(h, 'EdgeColor', 'none');
% colormap(gca,'jet');
% % surf(dataM)
% % colormap jet
% colorbar
% title('$Relaksacja \;\; lokalna \;:\; \omega = 1.9$','Interpreter','latex');
% xlabel('i','Interpreter','latex') 
% ylabel('j','Interpreter','latex')

