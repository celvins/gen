//============================================================================
// Name        : test2.cpp
// Author      : Vardanyan Andranik
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "fosfitkinetika.h"
#include <math.h>
#define N 5
#define M 10
#define ALL_P_MUTATION_DOWN 0
#define ALL_P_MUTATION_UP 25
#define P_MUTATION_DOWN 0
#define P_MUTATION_UP 20
using namespace std;
int cmpfunc (const void *, const void *);
int choice_parent(double **, double);
void mutation(double *);
double create_roulette(double **, double **, double *);
void krossover(double **, double **, double **, double);
int main(){
	FILE *file;
	if(((file = fopen("gran.txt", "r"))) == 0){
		printf("Error file");
	}
	double ** roulette = new double*[M];
	double ** population = new double*[M];
	double ** new_population = new double*[M];
	double * fitness = new double[M];
	double gran[N][4];
	//gran.txt
	/*
	 * границы мин макс для генов каждой популяции
	 */
	for(int i = 0; i < N; i++){
		for(int j = 0; j < 4; j++){
			fscanf(file, "%lf", &gran[i][j]);
		}
	}
	fclose(file);
	for(int i = 0; i < M; i++){
		population[i] = new double[N];
		new_population[i] = new double[N];
		roulette[i] = new double[2];
	}
	srand(time(0));
	//Начальная популяция
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++)
			population[i][j] = gran[j][0] * pow(10,gran[j][1]) + rand() * (gran[j][2] * pow(10,gran[j][3]) - gran[j][0] * pow(10,gran[j][1])) /(double)RAND_MAX;
	}
	/*
	 *	соединить файл fosfit_kinetika
	 *	посчитать фитнесс через файл
	 */

	for(int j = 0; j < 2; j++){
		printf("Поколение %d\n", j + 1);
		for(int i = 0; i < M; i++){
			for(int k = 0; k < N; k++)
				printf("%5.25lf ", population[i][k]);
			printf("\n");
		}
		double roulette_sum = 0;
		roulette_sum = create_roulette(roulette, population, fitness);
		krossover(population, new_population, roulette, roulette_sum);
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
double fun(double * population){
	return population[0] - population[1] + pow(population[2], 2) + population[3];
}
int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
double create_roulette(double ** roulette, double ** population, double * fitness){
	double roulette_sum = 0;
	//Расчет фитнесса, рулетка
	for(int i = 0; i < M; i++){
		fitness[i] = F_SUM(population[i]);//Значения функции
		roulette_sum += fitness[i];
	}
	qsort(fitness, M , sizeof(double), cmpfunc);
	//Рулетка
	for(int i = 0; i < M; i++){
		roulette[i][0] = fitness[i];
		roulette[i][1] = fitness[i + 1];
	}
	return roulette_sum;
}
int choice_parent(double ** roulette, double x){
	//Рулетка
	for(int i = 0; i < M; i++)
		if((x >= roulette[i][0]) && (x < roulette[i][1]))
			return i;
	return 0;
}
void mutation(double * population){
	int all_p_mutation = rand() % 100; //Вероятность мутации особи
	if((all_p_mutation > ALL_P_MUTATION_DOWN) && (all_p_mutation <= ALL_P_MUTATION_UP)){
		for(int b = 0; b < N; b++){
			int p_mutation = rand() % 100; //Вероятность мутации гена
			if((p_mutation > P_MUTATION_DOWN) && (p_mutation <= P_MUTATION_UP)){
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
void krossover(double ** population, double ** new_population, double ** roulette, double roulette_sum){
	for(int g = 0; g < M; g += 2){
		int x_dad = rand() % int(roulette_sum), x_mom = rand() % int(roulette_sum), dad = choice_parent(roulette, x_dad), mom = choice_parent(roulette, x_mom), krossover_variant;
		double parents[2][N], child[2][N];
		krossover_variant = rand() % 3;
		for(int b = 0; b < N; b++){
			parents[0][b] = population[dad][b];
			parents[1][b] = population[mom][b];
		}
		switch (krossover_variant){
		case 0:
			//Гены распределяются потомству пополам
			for(int b = 0; b < N / 2; b++){
				child[0][b] = parents[1][b];
				child[1][b] = parents[0][b];
			}
			for(int b = N / 2; b < N; b++){
				child[0][b] = parents[0][b];
				child[1][b] = parents[1][b];
			}
			break;
		case 1:
			//Гены чередуются
			for(int b = 0; b < N; b++){
				if(b % 2 == 0){
					child[0][b] = parents[0][b];
					child[1][b] = parents[1][b];
				}
				else {
					child[1][b] = parents[0][b];
					child[0][b] = parents[1][b];
				}
			}
			break;
		case 2:
			//Точка раздела геннов задается случайным образом
			int point_division = rand() % N;
			for(int b = 0; b < point_division; b++){
				child[0][b] = parents[0][b];
				child[1][b] = parents[1][b];
			}
			for(int b = point_division; b < N; b++){
				child[0][b] = parents[1][b];
				child[1][b] = parents[0][b];
			}
			break;
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
