//#include <iostream>
//using namespace std;
//#include <omp.h>
//#include <string.h>
//#include <stdlib.h>
//#include <random>
//#include <math.h>
//#include <time.h>
//
//
//
//int main(int argc, char* argv[])
//{
//	int i, j;
//	const int sizeMatrix = 200;
//	int matrix[sizeMatrix][sizeMatrix];
//
//
//	//#pragma omp parallel for private(i, j) collapse(2)
//	for (i = 0; i < sizeMatrix; i++)
//	{
//		for (j = 0; j < sizeMatrix; j++)
//		{
//			if (i == 0 && j != 0) { matrix[i][j] = 150; }
//			if (i != 0 && j == 0) { matrix[i][j] = 250; }
//			//cout << "[" << i << "][" << j << "]" << matrix[i][j] << endl;
//		}
//	}
//
//
//
//	cout << endl << "Sequential: " << endl;
//	double start = omp_get_wtime();
//	for (int iteration = 1; iteration <= sizeMatrix; iteration++)
//	{
//		for (int innerItteration = iteration; innerItteration >= 1; innerItteration--)
//		{
//			int row = innerItteration;
//			int col = iteration - innerItteration + 1;
//			if (row >= sizeMatrix || col >= sizeMatrix)
//				continue;
//			matrix[row][col] = (
//				abs(sin(matrix[row - 1][col - 1]))
//				+ abs(sin(matrix[row][col - 1]))
//				+ abs(sin(matrix[row - 1][col]))
//				) * 100;
//		}
//	}
//	double end = omp_get_wtime();
//	cout << endl << "Sequential Time: " << end - start << "seconds" << endl;
//
//
//	//#pragma omp single
//	//	for (i = 0; i < sizeMatrix; i++)
//	//	{
//	//		for (j = 0; j < sizeMatrix; j++)
//	//		{
//	//			cout << "Modified: [" << i << "][" << j << "]" << matrix[i][j] << endl;
//	//		}
//	//	}
//
//
//	omp_set_num_threads(4);
//	cout << endl << "Iteration:" << endl;
//	int iteration, innerItteration;
//	start = omp_get_wtime();
//	//#pragma omp parallel  for shared(sizeMatrix)
//	for (iteration = 1; iteration <= sizeMatrix; iteration++)
//	{
//#pragma omp parallel for shared(iteration) private(innerItteration) schedule(static, 3)
//		for (innerItteration = iteration; innerItteration >= 1; innerItteration--)
//		{
//			int row = innerItteration;
//			int col = iteration - innerItteration + 1;
//			if (row >= sizeMatrix || col >= sizeMatrix)
//				continue;
//			//cout << "Here we are:  [" << row << "][" << col << "]" << endl;
//			matrix[row][col] = (
//				abs(sin(matrix[row - 1][col - 1]))
//				+ abs(sin(matrix[row][col - 1]))
//				+ abs(sin(matrix[row - 1][col]))
//				) * 100;
//
//		}
//
//
//	}
//	end = omp_get_wtime();
//
//	cout << endl << "Time: " << end - start << "seconds" << endl;
//
//
//	//#pragma omp single
//	//	for (i = 0; i < sizeMatrix; i++)
//	//	{
//	//		for (j = 0; j < sizeMatrix; j++)
//	//		{
//	//			cout << "Modified: [" << i << "][" << j << "]" << matrix[i][j] << endl;
//	//		}
//	//	}
//
//
//		//omp_set_num_threads(4);
//	//#pragma omp parallel for num_threads(4) collapse(2) schedule(static, 3)
//	//	for (int i = 0; i < 3; i++) {
//	//		for (int j = 0; j < 3; j++) {
//	//			printf("i = %d, j= %d, threadId = %d \n", i, j, omp_get_thread_num());
//	//		}
//	//	}
//
//}