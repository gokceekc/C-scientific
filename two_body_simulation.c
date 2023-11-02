#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 4


struct TwoBodyModel{


double m1;
double m2;
double m12;
double u[N];
double position[N];

};

struct TwoBodyModel *tbm;


struct TwoBodyControl{
	
double T ;
double q ;
double e ;
double deltat;
int method;	

};
struct TwoBodyControl *con;



void initialize(struct TwoBodyModel *tbm, struct TwoBodyControl *con){
	
	con->T=0;
	con->q=0;
	con->e=0;
	con->deltat=0;
  
	
	tbm->m1=1;
	tbm->m2=0;
	tbm->m12=1;
	tbm->position[0]=0, tbm->position[1]=0, tbm->position[2]=0, tbm->position[3]=0;
	tbm->u[0]=1, tbm->u[1]=0,  tbm->u[2]=0,  tbm->u[3]=0;    
	
	

}



double *derivative(struct TwoBodyModel *tbm, struct TwoBodyControl *con){
	double *du;
	double *r, distanceR;
	int i=0;
	du=(double*) malloc(4*sizeof(double));
	r=(double*) malloc(2*sizeof(double));
	r[0]=tbm->u[0];
	r[1]=tbm->u[1];
	distanceR = sqrt(pow(r[0], 2) + pow(r[1], 2));	

	
	for(i=0; i<2; i++){
		du[i] = tbm->u[i + 2];
        du[i + 2] = -((1 + con->q) * r[i] ) / pow(distanceR, 3);
	} 

	return du;
	
}
void RungeKutta(struct TwoBodyModel *tbm, struct TwoBodyControl *con){
	double *du;
	du=(double*) malloc(4*sizeof(double));
	int len=sizeof(tbm->u) / sizeof(tbm->u[0]);
	double a[4] = {con->deltat/2, con->deltat/2, con->deltat, 0};
    double b[4] = {con->deltat/6, con->deltat/3, con->deltat/3, con->deltat/6};
    double u0[4]= {0,0,0,0};
    double ut[4] = {0,0,0,0};
    
    for(int i=0; i<len; i++){
        u0[i]=tbm->u[i];
        ut[i]=0;
      }  
     for(int j=0; j<4; j++){
            du = derivative(tbm,con);
            for(int i=0; i<len; i++){
                tbm->u[i] = u0[i] + a[j]*du[i];
                ut[i] = ut[i] + b[j]*du[i];
                
}  
}
        for (int i=0; i<len; i++){

            tbm->u[i] = u0[i] + ut[i];
            
	}
}

void euler(struct TwoBodyModel *tbm, struct TwoBodyControl *con){
    double *du;
    du = derivative(tbm,con);
        for(int i=0; i<4; i++){
		
            tbm->u[i] = tbm->u[i] + con->deltat * du[i];
}
}

double initialVelocity(double q, double eccentricity){

    return (sqrt((1 + q) * (1 + eccentricity)));

}


void calculateNewposition(struct TwoBodyModel *tbm){
	double r=1;
	double a1= (tbm->m2/ tbm->m12)*r;   
	double a2= (tbm->m1/ tbm->m12)*r;
	tbm->position[0] = - a2 * tbm->u[0];
    tbm->position[1] = - a2 * tbm->u[1];
    tbm->position[2] = a1 * tbm->u[0];
    tbm->position[3] = a1 * tbm->u[1];
	
	

}


void Apply(struct TwoBodyModel *tbm, struct TwoBodyControl *con){
	FILE *fptr;
	fptr=fopen("LocationVector.txt", "w");
	int flag;
    initialize(tbm,con);
    printf("Enter mass ratio: ");
    scanf("%lf",&con->q);
    printf("Enter eccentricity: ");
    scanf("%lf", &con->e);
    printf("Enter T: ");
    scanf("%lf", &con->T);
    printf("Enter deltaT: ");
    scanf("%lf", &con->deltat);
    tbm->m2=1*con->q;
    tbm->m12=tbm->m1+tbm->m2;
    tbm->u[3]=initialVelocity(con->q, con->e);
    printf("Choose method\n1:RungeKutta\n2:Euler\n");
    scanf("%d", &con->method);
    
    
    for(int i=0; i<(con->T)/(con->deltat); i++)	{
    if(con->method==1){
    RungeKutta(tbm,con);
	}	

	
	else{
		
	euler(tbm,con);
	
	}	
		
	calculateNewposition(tbm);
	fprintf(fptr, "%lf",tbm->position[0]);
	fprintf(fptr, ", %lf",tbm->position[1]);
	fprintf(fptr, ", %lf",tbm->position[2]);
	fprintf(fptr, ", %lf\n",tbm->position[3]);
	}
}

int main(){

    struct TwoBodyModel model;
    struct TwoBodyControl control;
    Apply(&model,&control);
   

	
	return 0;
	
}

