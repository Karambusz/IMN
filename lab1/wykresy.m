clc;clear;

set(0,'DefaultAxesFontSize',15,'DefaultAxesFontName','Arial Cyr');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% EULER %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
data = readtable('mje.dat');
figure;
plot(data.Var1(1:500), data.Var3(1:500), 'k',  'LineWidth', 4);
hold on;
plot(data.Var1(1:500), data.Var2(1:500), 'r:', 'LineWidth', 4);
hold on;
plot(data.Var1(501:550), data.Var2(501:550), 'g:', 'LineWidth', 4);
hold on;
plot(data.Var1(551:555), data.Var2(551:555), 'b:', 'LineWidth', 4);
legend({'$analityczne$', '$\Delta t = 0.01$', '$\Delta t = 0.1$', '$\Delta t = 1.0$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
 title('Metoda jawna Eulera');
 xlabel('t');
 ylabel('y');
% % 
figure;
plot(data.Var1(1:500), data.Var4(1:500), 'r', 'LineWidth', 5);
hold on;
plot(data.Var1(501:550), data.Var4(501:550), 'g', 'LineWidth', 5);
hold on;
plot(data.Var1(551:555), data.Var4(551:555), 'b', 'LineWidth', 5);
set(gca, 'YScale', 'log');
legend({'$\Delta t = 0.01$', '$\Delta t = 0.1$', '$\Delta t = 1.0$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Błąd obliczeniowy - metoda jawna Eulera');
xlabel('t') 
ylabel('|yn-ya|')



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% RK2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

data = readtable('rk2.dat');

figure;
plot(data.Var1(1:500), data.Var3(1:500), 'k', 'LineWidth', 4);
hold on;
plot(data.Var1(1:500), data.Var2(1:500), 'r:', 'LineWidth', 4);
hold on;
plot(data.Var1(501:550), data.Var2(501:550), 'g:', 'LineWidth', 4);
hold on;
plot(data.Var1(551:555), data.Var2(551:555), 'b:', 'LineWidth', 4);
legend({'$analityczne$', '$\Delta t = 0.01$', '$\Delta t = 0.1$', '$\Delta t = 1.0$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('RK2');
xlabel('t'); 
ylabel('y');
% 
figure;
plot(data.Var1(1:500), data.Var4(1:500), 'r', 'LineWidth', 5);
ylim([0.0000001, 1]);
hold on;
plot(data.Var1(501:550), data.Var4(501:550), 'g', 'LineWidth', 5);
hold on;
plot(data.Var1(551:555), data.Var4(551:555), 'b', 'LineWidth', 5);
set(gca, 'YScale', 'log');
legend({'$\Delta t = 0.01$', '$\Delta t = 0.1$', '$\Delta t = 1.0$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Błąd obliczeniowy - RK2');
xlabel('t') 
ylabel('|yn-ya|')




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% RK4 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

data = readtable('rk4.dat');

figure;
plot(data.Var1(1:500), data.Var3(1:500), 'k', 'LineWidth', 4);
hold on;
plot(data.Var1(1:500), data.Var2(1:500), 'r:', 'LineWidth', 4);
hold on;
plot(data.Var1(501:550), data.Var2(501:550), 'g:', 'LineWidth', 4);
hold on;
plot(data.Var1(551:555), data.Var2(551:555), 'b:', 'LineWidth', 4);
legend({'$analityczne$', '$\Delta t = 0.01$', '$\Delta t = 0.1$', '$\Delta t = 1.0$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('RK4');
xlabel('t'); 
ylabel('y');
% % 
figure;
plot(data.Var1(1:500), data.Var4(1:500), 'r', 'LineWidth', 5);
hold on;
plot(data.Var1(501:550), data.Var4(501:550), 'g', 'LineWidth', 5);
hold on;
plot(data.Var1(551:555), data.Var4(551:555), 'b', 'LineWidth', 5);
set(gca, 'YScale', 'log');
legend({'$\Delta t = 0.01$', '$\Delta t = 0.1$', '$\Delta t = 1.0$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Błąd obliczeniowy - RK4');
xlabel('t') 
ylabel('|yn-ya|')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% RLC %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data = readtable('rlc.dat');
% 
figure;
plot(data.Var1(1:2513), data.Var2(1:2513), 'k:', 'LineWidth', 4);
hold on;
plot(data.Var1(2514:5026), data.Var2(2514:5026), 'r:', 'LineWidth', 4);
hold on;
plot(data.Var1(5027:7539), data.Var2(5027:7539), 'g--', 'LineWidth', 4);
hold on;
xlim([0, 0.25]);
plot(data.Var1(7540:10052), data.Var2(7540:10052), 'b-.', 'LineWidth', 4);
hold on;
xlim([0, 0.3]);
legend({'$\omega_{V} = 0.5\omega_{0}$', '$\omega_{V} = 0.8\omega_{0}$', '$\omega_{V} = \omega_{0}$', '$\omega_{V} = 1.2\omega_{0}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Obwód RLC - I(t)');
xlabel('t'); 
ylabel('I(t)');
%
figure;
plot(data.Var1(1:2513), data.Var3(1:2513), 'k:', 'LineWidth', 4);
hold on;
plot(data.Var1(2514:5026), data.Var3(2514:5026), 'r:', 'LineWidth', 4);
hold on;
plot(data.Var1(5027:7539), data.Var3(5027:7539), 'g--', 'LineWidth', 4);
hold on;
xlim([0, 0.25]);
plot(data.Var1(7540:10052), data.Var3(7540:10052), 'b-.', 'LineWidth', 4);
hold on;
xlim([0, 0.3]);
legend({'$\omega_{V} = 0.5\omega_{0}$', '$\omega_{V} = 0.8\omega_{0}$', '$\omega_{V} = \omega_{0}$', '$\omega_{V} = 1.2\omega_{0}$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('Obwód RLC - q(t)');
xlabel('q'); 
ylabel('q(t)');





































