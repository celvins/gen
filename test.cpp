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
	double ** roulette = new double*[M];
	double **population = new double*[M];
	for(int i = 0; i < M; i++){
		population[i] = new double[N];
		roulette[i] = new double[2];
	}
	double *fitness = new double[M];
	srand(time(0));

	//Начальная популяция
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
			population[i][j] = -200.15 / 15 + rand() % 401;

	//10 поколений
	for(int j = 0; j < 10; j++){
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
		}
		//Новая популяция
		//Кроссовер
		for(int g = 0; g < M; g++){
			int x_dad = rand() % int(sum), x_mom = rand() % int(sum), dad = roulete(roulette, x_dad), mom = roulete(roulette, x_mom);
			double parents[2][N];
			for(int j = 0; j < N; j++){
				parents[0][j] = population[dad][j];
				parents[1][j] = population[mom][j];
			}
			for(int b = N - 1; b > N / 2; b--){
				population[dad][b] = parents[1][b];
				population[mom][b] = parents[0][b];
			}
			int child1, child2;
			if(dad < mom){
				child1 = dad;
				child2 = mom;
			}
			else{
				child1 = mom;
				child2 = dad;
			}

			for(int i = child1; i <= child2; i++){
				int all_p_mutation = rand() % 100; //Вероятность мутации особи
				if((all_p_mutation > 0) && (all_p_mutation <= 25)){
					for(int b = 0; b < N; b++){
						int p_mutation = rand() % 100; //Вероятность мутации гена
						if((p_mutation > 0) && (p_mutation <= 20)){
							//cout << "\nмутация " << population[i][b] << " ДО ";
							double a = (population[i][b] - population[i][b] * 5 / 100.0);
							double c = (population[i][b] + population[i][b] * 5 / 100.0);
							if(a < c)
								population[i][b] = a + rand() * (c - a) / (double)RAND_MAX;
							else
								population[i][b] = c + rand() * (a - c) / (double)RAND_MAX;
							//cout << population[i][b] << endl;
						}
					}
				}
			}
		}


//		for(int k = 0; k < M; k++){
//			int x = rand() % int(sum);
//			int i = roulete(roulette,x);
//			for(int b = 0; b < N; b++){
//				int p_mutation = rand() % 100; //Вероятность мутации
//				if((p_mutation > 0) && (p_mutation <= 20)){
//					cout << "\nмутация " << population[i][b] << " ДО ";
//					double a = (population[i][b] - population[i][b] * 5 / 100.0);
//					double c = (population[i][b] + population[i][b] * 5 / 100.0);
//					if(a < c)
//						population[i][b] = a + rand() * (c - a) / (double)RAND_MAX;
//					else
//						population[i][b] = c + rand() * (a - c) / (double)RAND_MAX;
//					cout << population[i][b];
//					cout << "\nМутация " << a << " " << c << endl;;
//				}
//				population[k][b] = population[i][b];
//			}
//		}

		for(int i = 0; i < M; i++){
			for(int k = 0; k < N; k++)
				printf("%5lf ", population[i][k]);
			printf("\n");
		}
	}

	for(int i = 0; i < M; i++){
		delete []population[i];
		delete []roulette[i];
	}
	delete []roulette;
	delete []population;
	delete []fitness;
	return EXIT_SUCCESS;
}
int roulete(double ** roulette, double x){
	for(int i = 0; i < M; i++)
		if((x >= roulette[i][0]) && (x < roulette[i][1]))
			return i;
	return false;
}
