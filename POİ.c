#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define e  2.71828
#define N 50

double fY(double x){
	
	return(pow(e,( - (pow(x, 5) / 5) + (pow(x, 3) / 3 ) - (pow(x,2) / 2 ))));
}

double fYdx(double x, double y){
	
	return(y * ( - pow(x,4) + pow(x,2) - x));
}


double *euler(double (*fYdx1)(double, double), double xFirst, double yFirst, double xlast, double h){
	
	 int i;
	 double *yEuler;
	 yEuler=malloc(N*sizeof(double));
	 yEuler[0]=1.24;
   
		 for(i=1,xFirst; xFirst<=xlast; xFirst=xFirst+h,i++){
		
		yFirst=yFirst + h * fYdx(xFirst ,yFirst);
		yEuler[i]=yFirst;
	}
	
	return yEuler;
}


double *midpoint(double (*fYdx2)(double, double), double xFirst, double yFirst, double xlast, double h){
	
	
	int i;
	double ta,tb;
	double *yMidpoint;
	yMidpoint=malloc(N*sizeof(double));
	yMidpoint[0]=1.24;
	
	
	
	for(i=1,xFirst; xFirst<=xlast; xFirst=xFirst+h, i++){
	
	
	ta= h* fYdx(xFirst, yFirst);
	tb= h*fYdx(xFirst+h/2, yFirst+(h*ta/2));
	yFirst=yFirst+tb;
	yMidpoint[i]=yFirst;
	}
	
	return yMidpoint;
}





double *RK4(double (*fYdx3)(double, double), double xFirst, double yFirst, double xlast, double h){
	
	double *yRK4;
	yRK4=malloc(N*sizeof(double));
	double ta, tb, tc, td;
	int i;
	yRK4[0]=1.24;
	
	
	
	for(i=1, xFirst; xFirst<=xlast; xFirst=xFirst+h,i++){
	
		ta=h*fYdx(xFirst, yFirst);
		tb=h*fYdx(xFirst+h/2.0, yFirst+ta/2.0);
		tc=h*fYdx(xFirst+h/2.0, yFirst+tb/2.0);
		td=h*fYdx(xFirst+h, yFirst+tc);
		yFirst=yFirst+(ta+2.0*tb+2*tc+td)/6.0;
		yRK4[i]=yFirst;
	}
	
	return yRK4;
}
int main(){
	
	int i;
	double xFirst, yFirst, xlast, h;
	double *eresult;
	double *miresult;
	double *ruresult;
	
	
	
	
	printf("please enter the x0:\n");
	scanf("%lf",&xFirst);
	printf("please enter the y0:\n");
	scanf("%lf",&yFirst);
	printf("please enter the xlast:\n");
	scanf("%lf",&xlast);
	printf("please enter the h:\n");
	scanf("%lf",&h);
	
	
	eresult=malloc(N*sizeof(double)); 
	miresult=malloc(N*sizeof(double));
	ruresult=malloc(N*sizeof(double)); 
	
	

	
	printf("                       Euler      Midpoint      RK4       Exact\n  ");
	
	
	for( i=0 ; xFirst < xlast + h ; xFirst=xFirst + h, i++){
				
		printf("Step %d-y(%f)", i, xFirst);
		eresult = euler(fYdx, xFirst, yFirst, xlast, h);
		printf("--- %lf", eresult[i]);
		miresult = midpoint(fYdx, xFirst, yFirst, xlast, h);
		printf("---%lf", miresult[i]);
		ruresult = RK4(fYdx, xFirst, yFirst, xlast, h);
		printf("---%lf", ruresult[i]);
		printf("---%lf\n",fY(xFirst));
		
	}	
	

	
	
	
	
	
}


