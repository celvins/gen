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
int roulete(double **, double);
void mutation(double *);
double set_roulette(double **, double **, double *, double);
void krossover(double **, double **, double **, double);
double fun(double *);
void puzirek(double * fitness);
int main() {
	double ** roulette = new double*[M];
	double ** population = new double*[M];
	double ** new_population = new double*[M];
	double * fitness = new double[M];
	for(int i = 0; i < M; i++){
		population[i] = new double[N];
		new_population[i] = new double[N];
		roulette[i] = new double[2];
	}
	srand(time(0));
	//Начальная популяция
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
			population[i][j] = -200.15 / 15 + rand() % 401;
	//10 поколений
	for(int j = 0; j < 10; j++){
		double sum = 0;
		printf("Поколение %d\n", j + 1);
		sum = set_roulette(roulette, population, fitness, sum);
		//Новая популяция
		//Кроссовер & мутация особей
		krossover(population, new_population, roulette, sum);
		for(int i = 0; i < M; i++){
			for(int k = 0; k < N; k++)
				printf("%5lf ", population[i][k]);
			printf("\n");
		}
	}
	for(int i = 0; i < M; i++){
		delete []population[i];
		delete []roulette[i];
		delete []new_population[i];
	}
	delete []new_population;
	delete []roulette;
	delete []population;
	delete []fitness;
	return EXIT_SUCCESS;
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
double fun(double * population){
	return population[0] - population[1] + pow(population[2], 2) + population[3];
}
double set_roulette(double ** roulette, double ** population, double * fitness, double sum){
	//Расчет фитнесса, рулетка
	for(int i = 0; i < M; i++){
		fitness[i] = fun(population[i]);//Значения функции
		sum += fitness[i];
	}
	puzirek(fitness); //Сортировка
	//Рулетка
	for(int i = 0; i < M; i++){
		roulette[i][0] = fitness[i];
		roulette[i][1] = fitness[i + 1];
	}
	return sum;
}
int roulete(double ** roulette, double x){
	//Рулетка
	for(int i = 0; i < M; i++)
		if((x >= roulette[i][0]) && (x < roulette[i][1]))
			return i;
	return false;
}
void mutation(double * population){
	int all_p_mutation = rand() % 100; //Вероятность мутации особи
	if((all_p_mutation > 0) && (all_p_mutation <= 25)){
		for(int b = 0; b < N; b++){
			int p_mutation = rand() % 100; //Вероятность мутации гена
			if((p_mutation > 0) && (p_mutation <= 20)){
				double a = (population[b] - population[b] * 5 / 100.0);
				double c = (population[b] + population[b] * 5 / 100.0);
				if(a < c)
					population[b] = a + rand() * (c - a) / (double)RAND_MAX;
				else
					population[b] = c + rand() * (a - c) / (double)RAND_MAX;
			}
		}
	}
}
void krossover(double ** population, double ** new_population, double ** roulette, double sum){
	for(int g = 0; g < M; g += 2){
		int x_dad = rand() % int(sum), x_mom = rand() % int(sum), dad = roulete(roulette, x_dad), mom = roulete(roulette, x_mom);
		double parents[2][N], child[2][N];
		for(int b = 0; b < N; b++){
			parents[0][b] = population[dad][b];
			parents[1][b] = population[mom][b];
		}
		for(int b = 0; b < N / 2; b++){
			child[0][b] = parents[1][b];
			child[1][b] = parents[0][b];
		}
		for(int b = N / 2; b < N; b++){
			child[0][b] = parents[0][b];
			child[1][b] = parents[1][b];
		}
		for(int i = 0; i < 2; i++)
			mutation(child[i]);

		for(int i = 0; i < N; i++){
			new_population[g][i] = child[0][i];
			new_population[g + 1][i] = child[1][i];
		}
	}
	for(int i = 0; i < M; i++)
		for(int k = 0; k < N; k++)
			population[i][k] = new_population[i][k];
}
