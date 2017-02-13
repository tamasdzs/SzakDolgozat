x=linspace(-6,6,300);
plot(x,phi(2,1,x),'LineWidth',1)
axis([-6 6 -1 1]);
set(gca,'XTick',-6:4:6)
set(gca,'YTick',-1:0.4:1)
hold on
box on
grid on

figure
x=linspace(-6,6,300);
plot(x,phi(3,1,x),'LineWidth',1)
axis([-6 6 -1 1]);
set(gca,'XTick',-6:4:6)
set(gca,'YTick',-1:0.4:1)
hold on
box on
grid on
