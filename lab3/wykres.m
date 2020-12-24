clc;clear;

set(0,'DefaultAxesFontSize',15,'DefaultAxesFontName','Arial Cyr');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%trapezy%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data = readtable('trapezy_tol_2.dat');
data1 = readtable('trapezy_tol_5.dat');
figure;
plot(data.Var1(1:end), data.Var3(1:end), 'g',  'LineWidth', 4);
hold on;
plot(data1.Var1(1:end), data1.Var3(1:end), 'm',  'LineWidth', 4);
hold on;
ylim([-2.5, 2.5]);
legend({'$TOL = 10^{-2}$', '$TOL = 10^{-5}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
 title('Metoda Trapezów');
 xlabel('t');
 ylabel('x(t)');
 
figure;
plot(data.Var1(1:end), data.Var4(1:end), 'g',  'LineWidth', 4);
hold on;
plot(data1.Var1(1:end), data1.Var4(1:end), 'm',  'LineWidth', 4);
hold on;
ylim([-8, 8]);
legend({'$c(D=0)$', '$x_{sr}(D=0)$', '$c(D=0.1)$', '$x_{sr}(D=0.1)$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Metoda Trapezów');
 xlabel('t');
 ylabel('v(t)');
 
figure;
plot(data.Var1(1:end), data.Var2(1:end), 'g',  'LineWidth', 4);
hold on;
plot(data1.Var1(1:end), data1.Var2(1:end), 'm',  'LineWidth', 4);
hold on;
ylim([0, 1]);
xlim([0, 41]);
legend({'$TOL = 10^{-2}$', '$TOL = 10^{-5}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Metoda Trapezów');
 xlabel('t');
 ylabel('dt(t)');
 
 
figure;
plot(data.Var3(1:end), data.Var4(1:end), 'g',  'LineWidth', 4);
hold on;
plot(data1.Var3(1:end), data1.Var4(1:end), 'm',  'LineWidth', 4);
hold on;
ylim([-8, 8]);
xlim([-2.5, 2.51]);
legend({'$TOL = 10^{-2}$', '$TOL = 10^{-5}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Metoda Trapezów');
 xlabel('x');
 ylabel('v(x)');
 
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%RK2%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 data = readtable('rk2_tol_2.dat');
data1 = readtable('rk2_tol_5.dat');
figure;
plot(data.Var1(1:end), data.Var3(1:end), 'g',  'LineWidth', 4);
hold on;
plot(data1.Var1(1:end), data1.Var3(1:end), 'm',  'LineWidth', 4);
hold on;
ylim([-2.5, 2.5]);
legend({'$TOL = 10^{-2}$', '$TOL = 10^{-5}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Metoda RK2');
 xlabel('t');
 ylabel('x(t)');
 
figure;
plot(data.Var1(1:end), data.Var4(1:end), 'g',  'LineWidth', 4);
hold on;
plot(data1.Var1(1:end), data1.Var4(1:end), 'm',  'LineWidth', 4);
hold on;
ylim([-8, 8]);
legend({'$TOL = 10^{-2}$', '$TOL = 10^{-5}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Metoda RK2');
 xlabel('t');
 ylabel('v(t)');
 
figure;
plot(data.Var1(1:end), data.Var2(1:end), 'g',  'LineWidth', 4);
hold on;
plot(data1.Var1(1:end), data1.Var2(1:end), 'm',  'LineWidth', 4);
hold on;
ylim([0, 0.7]);
xlim([0, 41]);
legend({'$TOL = 10^{-2}$', '$TOL = 10^{-5}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Metoda RK2');
 xlabel('t');
 ylabel('dt(t)');
 
 
figure;
plot(data.Var3(1:end), data.Var4(1:end), 'g',  'LineWidth', 4);
hold on;
plot(data1.Var3(1:end), data1.Var4(1:end), 'm',  'LineWidth', 4);
hold on;
ylim([-8, 8]);
xlim([-2.5, 2.51]);
legend({'$TOL = 10^{-2}$', '$TOL = 10^{-5}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Metoda RK2');
 xlabel('x');
 ylabel('v(x)');