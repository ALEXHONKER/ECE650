function res=test()
h=0.97;
m=2;
rate=50;
length=60;
a=1.06;
k=0.12;
BU=1;
time=0:0.005:300;
save=0;
st=0;
en=0;
ff=zeros(size(time));
l=0;
i=0;
while i<64 
st=0;
en=0;
final=zeros(size(time));
l=0;
BU=1;
while l<=300
	x=rand;
	tl=k*(x**(-1/a)-1);
	l=l+tl;
	if BU==1
	   final=final.+(50).*(time>=en& time<(en+tl));
	   save=tl*50+save;
	else
	   final=final.+(0.*(time>=en & time<(en+tl)));
	end 
	st=en;
	en=en+tl; 
	BU=~BU;
end
i=i+1;
ff=ff+final;
end
figure
plot(time,ff)
xlabel('time');
ylabel('packets');

function res=aggre()
h=0.97;
m=2;
rate=50;
length=60;
a=1.06;
k=0.12;
BU=1;
pa=0;
time=0:0.001:60;
save=0;
st=0;
en=0;
final=zeros(size(time));
l=0;
while l<=60
	x=rand;
	tl=k*(x**(-1/a)-1);
	l=l+tl;
	if BU==1
	   final=final.+(50).*(time>=en& time<(en+tl));
	   save=tl*50+save;
	else
	   final=final.+(0.*(time>=en & time<(en+tl)));
	end 
	st=en;
	en=en+tl; 
	BU=~BU;
end
figure
plot(time,final)
xlabel('time');
ylabel('packets');
