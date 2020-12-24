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

data = readtable('E.dat');

figure;

plot(data.Var1(1:1000), data.Var2(1:1000), 'r',  'LineWidth', 4);
hold on;
plot(data.Var1(1001:2000), data.Var2(1001:2000), 'b',  'LineWidth', 4);
hold on;
plot(data.Var1(2001:3000), data.Var2(2001:3000), 'g',  'LineWidth', 4);
legend({'$\beta = 0.0 \;,\alpha =0.0$', '$\beta = 0.1 \;,\alpha =0.0$', '$\beta = 1.0 \;,\alpha =0.0$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('$E(t)$','Interpreter','latex');
xlabel('t','Interpreter','latex'); 
ylabel('E','Interpreter','latex');

figure;
data = readmatrix('mapa1.dat');
data1 = data.';
h = pcolor(data1);
set(h, 'EdgeColor', 'none');
colormap(c);
[m, n] = size(data1)
xticks(0:100:n);
yticks(0:10:m);
xt = get(gca, 'XTick');
set(gca, 'XTick',xt, 'XTickLabel',xt/20)
yt = get(gca, 'YTick');
set(gca, 'YTick',yt, 'YTickLabel',yt/10)
colorbar;
title('$\beta = 0.0 \;,\alpha =0.0$','Interpreter','latex');
xlabel('t','Interpreter','latex'); 
ylabel('x','Interpreter','latex');


figure;
data = readmatrix('mapa2.dat');
data1 = data.';
h = pcolor(data1);
set(h, 'EdgeColor', 'none');
colormap(c);
[m, n] = size(data1)
xticks(0:100:n);
yticks(0:10:m);
xt = get(gca, 'XTick');
set(gca, 'XTick',xt, 'XTickLabel',xt/20)
yt = get(gca, 'YTick');
set(gca, 'YTick',yt, 'YTickLabel',yt/10)
colorbar;
title('$\beta = 0.1 \;,\alpha =0.0$','Interpreter','latex');
xlabel('t','Interpreter','latex'); 
ylabel('x','Interpreter','latex');


figure;
data = readmatrix('mapa3.dat');
data1 = data.';
h = pcolor(data1);
set(h, 'EdgeColor', 'none');
colormap(c);
[m, n] = size(data1)
xticks(0:100:n);
yticks(0:10:m);
xt = get(gca, 'XTick');
set(gca, 'XTick',xt, 'XTickLabel',xt/20)
yt = get(gca, 'YTick');
set(gca, 'YTick',yt, 'YTickLabel',yt/10)
colorbar;
title('$\beta = 1.0 \;,\alpha =0.0$','Interpreter','latex');
xlabel('t','Interpreter','latex'); 
ylabel('x','Interpreter','latex');


data = readtable('E_1.dat');
figure;
plot(data.Var1, data.Var2, 'g',  'LineWidth', 4);
legend({'$\beta = 1.0 \;,\alpha =1.0$'},...
    'Location','best','Orientation','vertical','FontSize', 20, 'FontWeight', 'bold','Interpreter','latex');
title('$E(t)$','Interpreter','latex');
xlabel('t','Interpreter','latex'); 
ylabel('E','Interpreter','latex');

figure;
data = readmatrix('mapa4.dat');
data1 = data.';
h = pcolor(data1);
set(h, 'EdgeColor', 'none');
colormap(c);
[m, n] = size(data1)
xticks(0:100:n);
yticks(0:10:m);
xt = get(gca, 'XTick');
set(gca, 'XTick',xt, 'XTickLabel',xt/20)
yt = get(gca, 'YTick');
set(gca, 'YTick',yt, 'YTickLabel',yt/10)
colorbar;
caxis([-0.05 0.04]);
title('$\beta = 1.0 \;,\alpha =1.0$','Interpreter','latex');
xlabel('t','Interpreter','latex'); 
ylabel('x','Interpreter','latex');