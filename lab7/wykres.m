clc;clear;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Q = -1000%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure;
data = readmatrix('psi_-1000.dat');
dataM = data.';
contour(dataM, 400)
colorbar
caxis([-55 -50]);
title('$Q \; = \; -1000, \; \bf\Psi(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

figure;
data = readmatrix('dzeta_-1000.dat');
dataM = data.';
contour(dataM, 100)
colorbar
caxis([-200 300]);
title('$Q \; = \; -1000, \; \bf\zeta(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


figure;
data = readmatrix('u_-1000.dat');
dataM = data.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
caxis([-2 16]);
title('$Q \; = \; -1000, \; u(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


figure;
data = readmatrix('v_-1000.dat');
dataM = data.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
caxis([-6 1]);
title('$Q \; = \; -1000, \; v(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Q = -4000%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure;
data = readmatrix('psi_-4000.dat');
dataM = data.';
contour(dataM, 600)
colorbar
caxis([-218 -202]);
title('$Q \; = \; -4000, \; \bf\Psi(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

figure;
data = readmatrix('dzeta_-4000.dat');
dataM = data.';
contour(dataM, 100)
colorbar
caxis([-500 1000]);
title('$Q \; = \; -4000, \; \bf\zeta(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


figure;
data = readmatrix('u_-4000.dat');
dataM = data.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
caxis([-10 70]);
title('$Q \; = \; -4000, \; u(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


figure;
data = readmatrix('v_-4000.dat');
dataM = data.';
h = pcolor(dataM);
set(h, 'EdgeColor', 'none');
colormap(gca,'jet');
colorbar
caxis([-14 4]);
title('$Q \; = \; -4000, \; v(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Q = 4000%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure;
data = readmatrix('psi_4000.dat');
dataM = data.';
contour(dataM, 400)
colorbar
caxis([202 218]);
title('$Q \; = \; 4000, \; \bf\Psi(x,y)$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');
