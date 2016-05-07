%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  2-body problem
%%	FCK-SAT
%%	INTERFEROMETER_X-RAY_IMAGING_GAMMA-RAY
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
clc;

G=3;
m1=1;
x1=-15;
y1=0;
vx1=0;
vy1=-2;
m2=300;
x2=0;
y2=0;
vx2=0;
vy2=0;
t=0;
endtime=100;
i=1000000;

dt=(endtime)/i;
X1=zeros(1,i);
Y1=zeros(1,i);
X2=zeros(1,i);
Y2=zeros(1,i);
VX1=zeros(1,i);
VY1=zeros(1,i);
VX2=zeros(1,i);
VY2=zeros(1,i);


X1(1)=x1;
Y1(1)=y1;
X2(1)=x2;
Y2(1)=y2;
VX1(1)=vx1;
VY1(1)=vy1;
VX2(1)=vx2;
VY2(1)=vy2;

c=1;

while c<i

    dx=X2(c)-X1(c);
    dy=Y2(c)-Y1(c);
    r=(dx^2+dy^2)^(1/2);
    
    a1=G*m2/r^2;
    a2=G*m1/r^2;
    
    ax1=a1*(dx/r);
    ay1=a1*(dy/r);
    ax2=a2*(-dx/r);
    ay2=a2*(-dy/r);

    X1(c+1)=X1(c)+VX1(c)*dt+(1/2)*ax1*dt^2;
    Y1(c+1)=Y1(c)+VY1(c)*dt+(1/2)*ay1*dt^2;
    X2(c+1)=X2(c)+VX2(c)*dt+(1/2)*ax2*dt^2;
    Y2(c+1)=Y2(c)+VY2(c)*dt+(1/2)*ay2*dt^2;
    
    VX1(c+1)=VX1(c)+ax1*dt;
    VY1(c+1)=VY1(c)+ay1*dt;
    VX2(c+1)=VX2(c)+ax2*dt;
    VY2(c+1)=VY2(c)+ay2*dt;
    c=c+1;
end

figure(1)
posit=plot(X1,Y1,X2,Y2,x1,y1,'*',x2,y2,'o');
title('Position(t) SAT');
xlabel('x');
ylabel('y');
daspect([1 1 1]);
set(gca,'PlotBoxAspectRatio',[1 1 1]);
grid on;

for rd=1:i/300:i
    
    
    rd=floor(rd);
    
    set(posit(1),'XData',X1(1:rd));
    set(posit(1),'YData',Y1(1:rd));
    set(posit(2),'XData',X2(1:rd));
    set(posit(2),'YData',Y2(1:rd));
    set(posit(3),'XData',X1(rd));
    set(posit(3),'YData',Y1(rd));
    set(posit(4),'XData',X2(rd));
    set(posit(4),'YData',Y2(rd));
    
    drawnow
end

figure(2)
im = imread('d.jpg');

X = [-1.5 3.2; 1.8 3.3; -3.7 1.5; -1.5 1.3; ...
      0.8 1.2; 3.3 1.5; -4.0 -1.0;-2.3 -0.7; ...
      0 -0.5; 2.0 -1.5; 3.7 -0.8; -3.5 -2.9; ...
     -0.9 -3.9; 2.0 -3.5; 3.5 -2.25];
 
voronoi(X(:,1),X(:,2))

