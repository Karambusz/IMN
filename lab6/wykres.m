
function c = redblue(m)
%REDBLUE    Shades of red and blue color map
%   REDBLUE(M), is an M-by-3 matrix that defines a colormap.
%   The colors begin with bright blue, range through shades of
%   blue to white, and then through shades of red to bright red.
%   REDBLUE, by itself, is the same length as the current figure's
%   colormap. If no figure exists, MATLAB creates one.
%
%   For example, to reset the colormap of the current figure:
%
%             colormap(redblue)
%
%   See also HSV, GRAY, HOT, BONE, COPPER, PINK, FLAG, 
%   COLORMAP, RGBPLOT.
%   Adam Auton, 9th October 2009
if nargin < 1, m = size(get(gcf,'colormap'),1); end
if (mod(m,2) == 0)
    % From [0 0 1] to [1 1 1], then [1 1 1] to [1 0 0];
    m1 = m*0.5;
    r = (0:m1-1)'/max(m1-1,1);
    g = r;
    r = [r; ones(m1,1)];
    g = [g; flipud(g)];
    b = flipud(r);
else
    % From [0 0 1] to [1 1 1] to [1 0 0];
    m1 = floor(m*0.5);
    r = (0:m1-1)'/max(m1,1);
    g = r;
    r = [r; ones(m1+1,1)];
    g = [g; 1; flipud(g)];
    b = flipud(r);
end

c = [r g b]; 


set(0,'DefaultAxesFontSize',15,'DefaultAxesFontName','Arial Cyr');



subplot(2,3,1);
dataMap = readmatrix('mapa_50.dat');
h = pcolor(dataMap);
set(h, 'EdgeColor', 'none');
colormap(c);
colorbar
title('$Mapa \; dla \; nx=ny=50 \; \bf\rho_{1} = \bf\rho_{2} = 0$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


subplot(2,3,2);
dataMap = readmatrix('mapa_100.dat');
h = pcolor(dataMap);
set(h, 'EdgeColor', 'none');
colormap(c);
colorbar
title('$Mapa \; dla \; nx=ny=100 \; \bf\rho_{1} = \bf\rho_{2} = 0$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


subplot(2,3,3);
dataMap = readmatrix('mapa_200.dat');
h = pcolor(dataMap);
set(h, 'EdgeColor', 'none');
colormap(c);
colorbar
title('$Mapa \; dla \; nx=ny=200 \; \bf\rho_{1} = \bf\rho_{2} = 0$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');




subplot(2,3,4);
dataMap = readmatrix('mapa_1_1.dat');
h = pcolor(dataMap);
set(h, 'EdgeColor', 'none');
colormap(c);
colorbar
caxis([-0.6 0.6]);
title('$Mapa \; dla \; nx=ny=100 \; \bf\epsilon_{1} = 1 \; \bf\epsilon_{2} = 1$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');


subplot(2,3,5);
dataMap = readmatrix('mapa_1_2.dat');
h = pcolor(dataMap);
set(h, 'EdgeColor', 'none');
colormap(c);
colorbar
caxis([-0.6 0.6]);
title('$Mapa \; dla \; nx=ny=100 \; \bf\epsilon_{1} = 1 \; \bf\epsilon_{2} = 2$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');



subplot(2,3,6);
dataMap = readmatrix('mapa_1_10.dat');
h = pcolor(dataMap);
set(h, 'EdgeColor', 'none');
colormap(c);
colorbar
caxis([-0.6 0.6]);
title('$Mapa \; dla \; nx=ny=100 \; \bf\epsilon_{1} = 1 \; \bf\epsilon_{2} = 10$','Interpreter','latex');
xlabel('x','Interpreter','latex'); 
ylabel('y','Interpreter','latex');

