clc;clear;

set(0,'DefaultAxesFontSize',15,'DefaultAxesFontName','Arial Cyr');


%%%%%%%%%%%%%%%%%%%%%%%Picarda%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data = readtable('picard.dat');
figure;

plot(data.Var1(1:end), data.Var2(1:end), 'r',  'LineWidth', 4);
hold on;
plot(data.Var1(1:end), data.Var3(1:end), 'b',  'LineWidth', 4);
ylim([0, 600]);
legend({'$u(t) Zakazeni$', '$z(t) Zdrowi$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
 title('Metoda Picarda');
 xlabel('t');
 ylabel('u(t), z(t)');
%%%%%%%%%%%%%%%%%%%%%%%Newtona%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data = readtable('newton.dat');
figure;

plot(data.Var1(1:end), data.Var2(1:end), 'r',  'LineWidth', 4);
hold on;
plot(data.Var1(1:end), data.Var3(1:end), 'b',  'LineWidth', 4);
ylim([0, 600]);
legend({'$u(t) Zakazeni$', '$z(t) Zdrowi$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
 title('Metoda Newtona');
 xlabel('t');
 ylabel('u(t), z(t)');
 
 %%%%%%%%%%%%%%%%%%%%%%%%%%rk2%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 data = readtable('rk2.dat');
figure;

plot(data.Var1(1:end), data.Var2(1:end), 'r',  'LineWidth', 4);
hold on;
plot(data.Var1(1:end), data.Var3(1:end), 'b',  'LineWidth', 4);
ylim([0, 600]);
legend({'$u(t) Zakazeni$', '$z(t) Zdrowi$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
 title('RK2');
 xlabel('t');
 ylabel('u(t), z(t)');