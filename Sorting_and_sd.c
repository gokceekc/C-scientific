#include<stdio.h>
#include<math.h>


int N;

double mean(int a[], int N);
double std_deviation(int a[], int N );

//-----------------------------------------------------------------------------------------------------------
int main(){
	int m;
	int sum2=0;
	double c,b;
	int N; 
	int temp;
	
	printf("enter the value of number:"); 
	scanf("%d",&N);
	
	int a[N];
	for(int i=0; i<N; i++){
		
		printf("enter number %d:",i+1); scanf("%d",&a[i]);
	}
	
	printf("Data items in original order\n");
	for(int j=0; j<N; j++){
		
		printf("%d\t",a[j]);
	}
	
// bubble sort ---------------------------------------------------------------------------
	
	for(int j=0; j<N-2; j++){
	
	for(int i=1; i<N; i++){
		
		if(a[i-1]>a[i]){  
		//swap
		temp=a[i];
		a[i]=a[i-1];
		a[i-1]=temp;
		
		}
		}
	}
	printf(" \nData items in ascending order:\n");
	
	for (int k=0; k<N; k++){
		printf("%d\t",a[k]);
	}
	
	//----------------------------------------------------------------------------------------------
	
	for(int i=0; i<N; i++){
		sum2=sum2+a[i];
	}
	printf("\nTotal of numbers:%d",sum2);
	
	
	c=mean(a,N);
	printf("\nAverage of numbers:%lf",c);
	

	b=std_deviation(a,N);
	printf("\nStandart Deviation:%lf",b);
	
	
	
}


double mean(int a[N], int N){
	
	double x;
	double sum=0.0;
	
	for(int i=0; i<N; i++){
		
		sum=sum+a[i];
	}
	
	x=sum/N;
	
	return x;
}

double std_deviation(int a[N], int N ){
	double t;
	double y;
	mean(a,N);
	t=mean(a,N);
	
	double sum1=0.0;
	for(int i=0; i<N; i++){
		
		sum1+=pow((a[i]-t),2);
	}
	
	y=sqrt(sum1/N);
	
	return y;
}




