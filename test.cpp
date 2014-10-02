//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <time.h>
#define N 2
#define M 100
using namespace std;

double fun(double **population, int i){
	return population[i][0] - population[i][1] + pow(population[i][2], 2);
}
void puzirek(double * fitness){
	int i, kol = 1;
	double temp;
	while(kol > 0){
		kol = 0;
		for(i = 0; i < M; i++){
			if(fitness[i] > fitness[i + 1]){
				temp = fitness[i];
				fitness[i] = fitness[i + 1];
				fitness[i + 1] = temp;
				kol++;
			}
		}
	}
}
int main() {
	double **population = new double*[N];
	double *fitness = new double[M];
	for(int i = 0; i < M; i++)
		population[i] = new double[M];
	double sum = 0, roulette[M][2];
	srand(time(0));
	//Начальная популяция
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++)
			population[i][j] = -200.15 / 15 + rand() % 401;
	}

	//10 поколений
	for(int j = 0; j < 10; j++){
		printf("Поколение %d\n", j + 1);
		for(int i = 0; i < M; i++)
			printf("%lf %lf %lf\n", population[i][0], population[i][1], population[i][2]);

		//Значения функции
		for(int i = 0; i < M; i++){
			fitness[i] = fun(population, i);
			sum += fitness[i];
		}
		/*
		 * Сортировка fitness
		 */
		puzirek(fitness);

		//Рулетка
		for(int i = 0; i < M; i++){
			roulette[i][0] = fitness[i];
			roulette[i][1] = fitness[i + 1];
//			printf("%5lf %5lf\n", roulette[i][0], roulette[i][1]);
		}
		//Новая популяция
		for(int k = 0; k < M; k++){
			int x = rand() % int(sum);
			for(int i = 0; i < M; i++){
				if((x >= roulette[i][0]) && (x < roulette[i][1]))
					for(int b = 0; b < N; b++)
						population[k][b] = population[i][b];
			}
		}
	}
	for(int i = 0; i < M; i++)
		delete []population[i];
	delete []population;
	return EXIT_SUCCESS;
}
