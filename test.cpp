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
#define N 4
#define M 100
using namespace std;

double fun(double * population){
	return population[0] - population[1] + pow(population[2], 2) + population[3];
}
void puzirek(double * fitness){
	int i, kol = 1;
	double temp;
	while(kol > 0){
		kol = 0;
		for(i = 0; i < M - 1; i++){
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
	float roulette[M][2];

	double **population = new double*[M];
	for(int i = 0; i < M; i++)
		population[i] = new double[N];

	double *fitness = new double[M];
	srand(time(0));

	for(int i = 0; i < M; i++)//Начальная популяция
		for(int j = 0; j < N; j++)
			population[i][j] = -200.15 / 15 + rand() % 401;

	for(int j = 0; j < 10; j++){//10 поколений
		double sum = 0;
		printf("Поколение %d\n", j + 1);

		for(int i = 0; i < M; i++){
			fitness[i] = fun(population[i]);//Значения функции
			sum += fitness[i];
		}

		puzirek(fitness); //Сортировка

		//Рулетка
		for(int i = 0; i < M; i++){
			roulette[i][0] = fitness[i];
			roulette[i][1] = fitness[i + 1];
//			printf("%5lf %5lf\n", roulette[i][0], roulette[i][1]);
		}
		//Новая популяция
		//Кроссовер
//		for(int i = 0; i < M; i++){
//			int i_dad = rand() % M, i_mom = rand() % M;
//			const int m = 2 * M;
//
//
//		}
		for(int k = 0; k < M; k++){
			int x = rand() % int(sum);
			for(int i = 0; i < M; i++){
				if((x >= roulette[i][0]) && (x < roulette[i][1])){
					for(int b = 0; b < N; b++){
						int p_mutation = rand() % 100; //Вероятность мутации
						if((p_mutation > 0) && (p_mutation <= 20)){
							cout << "\nмутация " << population[i][b] << " ДО ";
							double a = (population[i][b] - population[i][b] * 5 / 100.0);
							double c = (int)(population[i][b] + population[i][b] * 5 / 100.0);
							if(a < c)
								population[i][b] = a + rand() % ((int)c + 1);
							else
								population[i][b] = c + rand() % ((int)a + 1);
							cout << population[i][b];
							cout << "\nМутация " << a << " " << c << endl;;
						}
						population[k][b] = population[i][b];
					}
				}
			}
		}
		for(int i = 0; i < M; i++){
			for(int k = 0; k < N; k++)
				printf("%5lf ", population[i][k]);
			printf("\n");
		}
	}
	for(int i = 0; i < M; i++)
		delete []population[i];
	delete []population;
	delete []fitness;
	return EXIT_SUCCESS;
}
