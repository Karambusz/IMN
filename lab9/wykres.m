clc;clear;

data = readmatrix('T.dat');
data100 = zeros(39, 39);
data200 = zeros(39, 39);
data500 = zeros(39, 39);
data1000 = zeros(39, 39);
data2000 = zeros(39, 39);
for i = 1:39
    for j = 1:39
        data100(i,j) = data(i,j);
        data200(i,j) = data(i+39,j);
        data500(i,j) = data(i+78,j);
        data1000(i,j) = data(i+117,j);
        data2000(i,j) = data(i + 156,j);        
    end
end
dataM1 = data100.';
dataM2 = data200.';
dataM3 = data500.';
dataM4 = data1000.';
dataM5 = data2000.';
figure;
subplot(3,2,1);
h = pcolor(dataM1);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
caxis([0, 40])
title('$T(x,y)\; it = 100$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

subplot(3,2,2);
h = pcolor(dataM2);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
caxis([0, 40])
title('$T(x,y)\; it = 200$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

subplot(3,2,3);
h = pcolor(dataM3);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
caxis([0, 40])
title('$T(x,y)\; it = 500$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

subplot(3,2,4);
h = pcolor(dataM4);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
caxis([0, 40])
title('$T(x,y)\; it = 1000$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

subplot(3,2,5);
h = pcolor(dataM5);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
caxis([0, 40])
title('$T(x,y)\; it = 2000$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


data = readmatrix('nablaT.dat');
data100 = zeros(39, 39);
data200 = zeros(39, 39);
data500 = zeros(39, 39);
data1000 = zeros(39, 39);
data2000 = zeros(39, 39);
for i = 1:39
    for j = 1:39
        data100(i,j) = data(i,j);
        data200(i,j) = data(i+39,j);
        data500(i,j) = data(i+78,j);
        data1000(i,j) = data(i+117,j);
        data2000(i,j) = data(i + 156,j);        
    end
end
dataM1 = data100.';
dataM2 = data200.';
dataM3 = data500.';
dataM4 = data1000.';
dataM5 = data2000.';

figure;
subplot(3,2,1);
h = pcolor(dataM1);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
caxis([0, 0.12])
title('$\nabla^{2}T(x,y)\;it = 100$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

subplot(3,2,2);
h = pcolor(dataM2);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
caxis([0, 0.045])
title('$\nabla^{2}T(x,y)\;it = 200$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

subplot(3,2,3);
h = pcolor(dataM3);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
caxis([0, 0.0025])
title('$\nabla^{2}T(x,y)\;it = 500$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

subplot(3,2,4);
h = pcolor(dataM4);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
title('$\nabla^{2}T(x,y)\;it = 1000$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

subplot(3,2,5);
h = pcolor(dataM5);
set(h, 'EdgeColor', 'none');
colormap(gca,'hot');
colorbar
title('$\nabla^{2}T(x,y)\;it = 2000$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');