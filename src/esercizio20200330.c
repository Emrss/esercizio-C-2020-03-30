/*
 ============================================================================
 Name        : Fibonacci.c
 Author      : Emiliano Rossi
 Version     :
 Copyright   : 
 Description : Es fibonacci Rossi Emiliano
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 39
#define PHI 1.6180339887

unsigned long fibonacci(unsigned int n){
	unsigned long result[3] ={0};
	result[1]=1;

	if(n==0){
		return result[0];
	} else if (n==1){
		return result[1];
	}else {
		for (int i =1; i <n; i++){
			result[2] = result[0]+result[1];
			result[0]=result[1];
			result[1]=result[2];
			}
	}
	return result[2];
}

long double pot(long double x, unsigned int n){
	long double y =x;
	for (int i =0; i<n;i++){
		x=x * y;
	}
	return x;

}

long double aprox(unsigned int n){
	//nonostante abbia messo <math.h> non mi riconosce la funzione pow(), di conseguenza l'ho fatta manualmente io
	long double res = ((pot(PHI,n-1)- pot(1-PHI, n-1))/ sqrt(5));
	return res;
}




unsigned long * fibonacci_array(unsigned int n){
	unsigned long * fib;
	fib = calloc(n+1, sizeof(unsigned long));

	if (fib== NULL){
		perror("calloc");
		exit(-1);
	}
	*(fib)=0;
	if (n>0){
		*(fib+1)=1;
		for (int i=2; i<=n;i++)
			*(fib+i)=*(fib+i-1)+*(fib+i-2);

	}
	return fib;

}

void stampa(unsigned long * array){
	printf("\n");
	for(int i =0;i<SIZE+1;i++){
		printf("%lu |", *(array+i));
	}
	printf("\n\n");
}


void swap(unsigned long * x,unsigned long *y){
	int temp =*(x);
	*(x)=*(y);
	*(y)=temp;

}

void swap_array_c(unsigned long * array, unsigned int size){
	unsigned int centro = (size - (size % 2))/2;
	for(unsigned int  i=0;i<centro;i++){
		swap(array+i,array+size-i-1);
	}
}

void bubbleSort(unsigned long * a, unsigned int size_a){
	int sw =-1; //variabile volta a contare quanti swap per ciclo;
	while (sw!=0){
		sw=0;
		for (int i =0; i < (size_a-1); i++){ //scorro i valori dal primo al penultimo
			if (*(a+i)> *(a+i+1)) { // effettuo uno swap
				sw++;
				swap(a+i,a+i+1);
			}
		}
	}
}
int main(int argc, char ** argv) {
	unsigned int i =2;
	double rapp;
	unsigned long res_e;
	long double res_a;

	printf("Esercizio 1\n");

	printf("Ora valuto qual'è l'n-esimo valore che correttamente riesco a calcolare\n");
	while(1){
		rapp = fibonacci(i)/aprox(i);
		if (rapp<=0.999){
			i--;

			printf("Ho ottenuto che max n value: %d\n", i);
			break;
		}
		i++;
	}
	res_e =fibonacci(i);
	res_a= aprox(i);
	printf("In particolare i risultati che ottengo con n=%d sono \n\n",i);
	printf("\tEsatto:\t\t %lu\n",res_e);
	printf("\tAprossimato:\t %.0Lf\n", res_a);
	printf("\n");
	res_a= aprox(i+1);
	res_e=fibonacci(i+1);
	printf("Mentre con n=%d ottengo\n\n",i+1);
	printf("\tEsatto:\t\t %lu\n",res_e);
	printf("\tAprossimato:\t %.0Lf\n", res_a);

	printf("\n");

	printf("Esericzio 2 con SIZE=%d\n",SIZE);

	unsigned long * fibonacci_result = fibonacci_array(SIZE);
	printf("Ho generato il seguente array\n");
	stampa(fibonacci_result);

	unsigned long fibonacci_result_copy[SIZE+1];
	printf("Ne sto facendo una copia\n");
	memcpy(fibonacci_result_copy, fibonacci_result, (SIZE+1)*sizeof(long));

	printf("Ho fatto la copia, adesso la inverto\n");
	swap_array_c(fibonacci_result_copy,SIZE+1);
	stampa(fibonacci_result_copy);

	printf("Eseguo Bubble Sort\n");
	bubbleSort(fibonacci_result_copy,SIZE+1);
	printf("Ho ottenuto\n");
	stampa(fibonacci_result_copy);

	if (memcmp(fibonacci_result_copy,fibonacci_result,(SIZE+1)*sizeof(long))!=0){
		printf("C'è stato qualche errore\n");
		free(fibonacci_result);
		return 1;
	} else{
		printf("I due array sono uguali!\n");
	}
	free(fibonacci_result);

	return EXIT_SUCCESS;
}
