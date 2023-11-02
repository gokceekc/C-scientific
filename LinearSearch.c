#include<stdio.h>
#include<stdlib.h>

int linearsearch(int arr[], int n, int wanted){
	int i;
	for(int i=0; i<n; i++){
		
		if(wanted==arr[i]){
			return i;
		}
	}
	return -1;
}



int main(){
	int n,wanted, result;
	printf("enter the length of array:");
	scanf("%d",&n);
	int arr[n];
	for(int i=0; i<n; i++){
	printf("number: "); scanf("%d", &arr[i]);
	
	}
	
	printf("enter the wanted number:");
	scanf("%d",&wanted);
	result=linearsearch(arr,n,wanted);
	if(result==-1){
		printf("\nwnated number is not exist in the array");
	}
	
	else{
		printf("wanted number is inside the array");
	}
}
