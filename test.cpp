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
#define N 3
#define M 100
using namespace std;

double fun(float * population){
	return population[0] - population[1] + pow(population[2], 2);
}
void puzirek(float * fitness){
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
	float roulette[M][2];

	float **population = new float*[M];
	for(int i = 0; i < M; i++)
		population[i] = new float[N];

	float *fitness = new float[M];
	srand(time(0));

	for(int i = 0; i < M; i++)//Начальная популяция
		for(int j = 0; j < N; j++)
			population[i][j] = -200.15 / 15 + rand() % 401;

	for(int j = 0; j < 10; j++){//10 поколений
		float sum = 0;
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
		for(int k = 0; k < M; k++){
			int x = rand() % int(sum);
			for(int i = 0; i < M; i++){
				if((x >= roulette[i][0]) && (x < roulette[i][1])){
					for(int b = 0; b < N; b++){
						int percent = rand() % 100; //Вероятность мутации
						if((percent > 0) && (percent <= 20)){
							cout << "mutatiya" << endl;
							float mutation = rand() % 5; //Мутация
							if((rand() % 2) == 1){
								cout << "\n" << population[i][b] << "\n";
								population[i][b] += (population[i][b] * (mutation / 100));
								cout << "+ " << mutation << " " << population[i][b] << endl;
							}
							else{
								population[i][b] -= (population[i][b] * (mutation / 100));
								cout << "- " << mutation << endl;
							}
						}
						population[k][b] = population[i][b];
					}
				}
			}
		}
		for(int i = 0; i < M; i++){
			for(int k = 0; k < N; k++)
				printf("%5lf ", population[i][k]);
			cout << endl;
		}
	}
	for(int i = 0; i < M; i++)
		delete []population[i];
	delete []population;
	delete []fitness;
	return EXIT_SUCCESS;
}
