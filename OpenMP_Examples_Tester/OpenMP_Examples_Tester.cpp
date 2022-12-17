#include <iostream>
using namespace std;
#include <omp.h>
#include <string.h>
#include <stdlib.h>
#include <random>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <cstdio>
#include <iomanip> 


void print_title();
void initialize_matrices(float** a, float** b, float** c, int size);
void matrix_fill(float** matrix1, float** matrix2, float** matrix3, int size);
void get_matrix_size(int& size);
bool compareMatrices(float** s_matrix, float** p_matrix, int size, int checkRandomly);
double getCurrentClock();

void print_matrix_2D(float** matrix, int size);
void print_matrix_header(int size);
void print_matrix_footer(int size);


//do Assignemnt2 business logic decomposition
//a is the matrix 
//array size for all is size x size
void assignment2_sequential(float** a, int size)
{
	for (int iteration = 1; iteration <= size; iteration++)
	{
		for (int innerItteration = iteration; innerItteration >= 1; innerItteration--)
		{
			int row = innerItteration;
			int col = iteration - innerItteration + 1;
			if (!(row >= size || col >= size))
				a[row][col] = (
					abs(sin(a[row - 1][col - 1]))
					+ abs(sin(a[row][col - 1]))
					+ abs(sin(a[row - 1][col]))
					) * 100;
		}
	}

}

//do parallelization of Assignemnt2 business logic decomposition
//a is the matrix 
//array size for all is size x size
void assignment2_parallel(float** a, int size)
{
	omp_set_num_threads(4);
	int iteration, innerItteration;
	for (iteration = 1; iteration <= size; iteration++)
	{
#pragma omp parallel for shared(iteration) private(innerItteration) schedule(static, 16)
		for (innerItteration = iteration; innerItteration >= 1; innerItteration--)
		{
			int row = innerItteration;
			int col = iteration - innerItteration + 1;
			if (row >= size || col >= size)
				continue;
			a[row][col] = (
				abs(sin(a[row - 1][col - 1]))
				+ abs(sin(a[row][col - 1]))
				+ abs(sin(a[row - 1][col]))
				) * 100;

		}


	}

}

//Paralellization: Method 2
//do parallelization of Assignemnt2 business logic decomposition
//a is the matrix 
//array size for all is size x size
void assignment2_parallel2(float** a, int size)
{
	omp_set_num_threads(64);
	int iteration, innerItteration;
	for (iteration = 1; iteration <= size; iteration++)
	{
#pragma omp parallel for shared(iteration) private(innerItteration) schedule(static, 8)
		for (innerItteration = iteration; innerItteration >= 1; innerItteration--)
		{
			int row = innerItteration;
			int col = iteration - innerItteration + 1;
			int priority = row + col + abs(row - col);
			//int shouldBeCreatedTask = !(row >= size || col >= size) ? 1 : 0;
			/*if(shouldBeCreatedTask)*/
#pragma omp task firstprivate(row, col, priority) priority(priority)
			{
				//cout << "Mehtod 3, task Matrix[" << row << "][" << col << "], with priority = " << priority << "" << endl;
				if (!(row >= size || col >= size))
					a[row][col] = (
						abs(sin(a[row - 1][col - 1]))
						+ abs(sin(a[row][col - 1]))
						+ abs(sin(a[row - 1][col]))
						) * 100;

			}
		}
		//#pragma omp taskyield


	}

}

int main(int argc, char** argv)
{
	//size of matrix
	int size;

	double runtime;

	//seed rng
	srand(1);

	//size of matrix
	print_title();

	get_matrix_size(size);

	cout << "Your input matrix size is ";
	cout << size << " x " << size << endl;
	fflush(stdout);

	//initalize matrices
	float** matrixSequential = new float* [size];
	float** matrixParallelizationMathod1 = new float* [size];
	float** matrixParallelizationMathod2 = new float* [size];
	initialize_matrices(matrixSequential, matrixParallelizationMathod1, matrixParallelizationMathod2, size);

	//fill a with random values
	matrix_fill(matrixSequential, matrixParallelizationMathod1, matrixParallelizationMathod2, size);

	//cout << "Matrix: " << endl;
	//print_matrix_2D(a, size);

#pragma region Sequential
	//do Computation
	runtime = omp_get_wtime();
	assignment2_sequential(matrixSequential, size);
	runtime = omp_get_wtime() - runtime;

	//cout << "A Matrix: " << endl;
	//print_matrix_2D(a, size);

	cout << "Assignment 2 in sequential mode Computation Time: ";
	cout << runtime;
	cout << " seconds" << endl;;

#pragma endregion

#pragma region Parallelization METHOD 1
	//do Computation
	double runtimeInParallelMode1 = omp_get_wtime();
	assignment2_parallel(matrixParallelizationMathod1, size);
	runtimeInParallelMode1 = omp_get_wtime() - runtimeInParallelMode1;

	//cout << "Matrix from method 1: " << endl;
	//print_matrix_2D(matrixParallelizationMathod1, size);

	cout << "Assignment 2 in parallelization mode (METHOD 1) Computation Time: " << runtimeInParallelMode1 << " seconds" << endl;;
#pragma endregion
#pragma region Parallelization METHOD 2
	//do Computation
	double runtimeInParallelMode2 = omp_get_wtime();
	assignment2_parallel2(matrixParallelizationMathod2, size);
	runtimeInParallelMode2 = omp_get_wtime() - runtimeInParallelMode2;

	//cout << "Matrix from method 2: " << endl;
	//print_matrix_2D(matrixParallelizationMathod2, size);

	cout << "Assignment 2 in parallelization mode (METHOD 2) Computation Time: " << runtimeInParallelMode2 << " seconds" << endl;;
#pragma endregion


#pragma region Results and Conclusions
	double differnce = runtime - runtimeInParallelMode1;
	double differnce2 = runtime - runtimeInParallelMode2;
	cout << "Diferences betweeen modes (Sequential vs Paralelization[Method 1] are: " << abs(differnce) << " seconds in favor of " << (differnce > 0 ? "parallel " : "sequential ") << "mode." << endl;
	cout << "Diferences betweeen modes (Sequential vs Paralelization[Method 2] are: " << abs(differnce2) << " seconds in favor of " << (differnce2 > 0 ? "parallel " : "sequential ") << "mode." << endl;
	
	cout << "Result of computed matrices (Sequential vs Paralelization_Method_1 seems " << (compareMatrices(matrixSequential, matrixParallelizationMathod1, size, 10) == 1 ? "valid " : "NOT valid ") << endl;
	cout << "Result of computed matrices (Sequential vs Paralelization_Method_2 seems " << (compareMatrices(matrixSequential, matrixParallelizationMathod2, size, 10) == 1 ? "valid " : "NOT valid ") << endl;
#pragma endregion

	return 0;
}


#pragma region Helper Functions

void print_title() {
	cout << "===============================================================" << endl;
	cout << "                       Assignment 2                            " << endl;
	cout << "===============================================================" << endl;
}


void get_matrix_size(int& size)
{
	int N, temp;
	bool error = true;
	cout << "Please enter the size of your square matrix: " << endl;
	fflush(stdout);

	//N = scanf_s("%d", &size);
	cin >> size;
	N = 1;
	cout << "N=" << N << ", size =" << size << endl;
	while ((N != 1 && error == true) || size < 2) {
		while ((temp = getchar()) != EOF && temp != '\n');
		cout << "Invalid input... Please enter a number larger or equal to 2: " << endl;
		fflush(stdout);
		//N = scanf_s("%d", &size);
		cin >> size;
		N = 1;
		cout << "N=" << N << ", size =" << size << endl;
		if (size > 0) {
			error = false;
		}
	}

	//while ((N != 1 && error == true) || size < 2 || size % 2 != 0) {
	//	while ((temp = getchar()) != EOF && temp != '\n');
	//	SetColor(4);
	//	cout << "Invalid input... Please enter a number larger or equal to 2 and is multiplication of 2: " << endl;
	//	SetColor(7);
	//	fflush(stdout);
	//	N = scanf_s("%d", &size);
	//	if (size > 0) {
	//		error = false;
	//	}
	//}
}




//initialize the matrices
void initialize_matrices(float** a, float** b, float** c, int size)
{
	//for each row in the 2d array, initialize the values
	for (int i = 0; i < size; ++i)
	{
		a[i] = new float[size];
		b[i] = new float[size];
		c[i] = new float[size];
	}
}

//fill the array with random values (done for a)
void matrix_fill(float** matrix1, float** matrix2, float** matrix3, int size)
{
	//fill a with random values
	cout << "Producing matrix values " << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix1[i][j] = 0;
			matrix2[i][j] = 0;
			matrix3[i][j] = 0;
			if (i == 0 && j != 0) { matrix1[i][j] = 150; matrix2[i][j] = 150; matrix3[i][j] = 150; }
			if (i != 0 && j == 0) { matrix1[i][j] = 250; matrix2[i][j] = 250; matrix3[i][j] = 250; }
		}
	}
}


double getCurrentClock() {
	return  clock() / (double)CLOCKS_PER_SEC;
}


bool compareMatrices(float** s_matrix, float** p_matrix, int size, int checkRandomly) {
	int row, col;
	for (int indx = 0; indx < checkRandomly; indx++)
	{
		row = 0 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (size - 0)));
		col = 0 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (size - 0)));
		if (s_matrix[row][col] != p_matrix[row][col])
			return false;
	}
	return true;
}

#pragma endregion


#pragma region Matrix Formatter
void print_matrix_header(int size)
{
	cout << left << setw(9) << setprecision(3) << " __" << left << setw(9);
	for (int i = 1; i < size; i++)
	{
		cout << left << setw(9) << setprecision(3) << "" << left << setw(9);
	}
	cout << left << setw(9) << setprecision(3) << "       __" << left << setw(9) << endl;
	cout << left << setw(9) << setprecision(3) << "|" << left << setw(9);
	for (int i = 0; i < size; i++)
	{
		cout << left << setw(9) << setprecision(3) << "" << left << setw(9);
	}
	cout << left << setw(9) << setprecision(3) << "|" << left << setw(9) << endl;
}

void print_matrix_2D(float** matrix, int size)
{
	// print the header for the matrix
	//for each row...
	print_matrix_header(size);
	for (int i = 0; i < size; i++)
	{
		cout << left << setw(9) << setprecision(3) << "|" << left << setw(9);
		//for each column
		for (int j = 0; j < size; j++)
		{
			//print out the cell
			cout << left << setw(9) << setprecision(3) << matrix[i][j] << left << setw(9);
		}
		//new line when ever row is done
		cout << left << setw(9) << setprecision(3) << "|" << left << setw(9);
		cout << endl;
	}
	// print the footer the matrix
	print_matrix_footer(size);
}

void print_matrix_footer(int size)
{
	cout << left << setw(9) << setprecision(3) << "|__" << left << setw(9);
	for (int i = 1; i < size; i++)
	{
		cout << left << setw(9) << setprecision(3) << "" << left << setw(9);
	}
	cout << left << setw(9) << setprecision(3) << "       __|" << left << setw(9) << endl;
}


#pragma endregion




