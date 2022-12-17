//int main(int argc, char* argv[])
//{
//	omp_set_num_threads(4);
//#pragma omp parallel for num_threads(4) collapse(2) schedule(static, 3)
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			printf("i = %d, j= %d, threadId = %d \n", i, j, omp_get_thread_num());
//		}
//	}
//
//
//}

//#define SEED time(NULL)
//int main() {
//	//cout << "SEED"<< SEED<<endl;
//	//srand(SEED);
//	//cout << "SEED" << SEED << endl;
//	int i, count, n;
//	double x, y, z, pi;
//
//	//printf("n = ");
//	cout << "n = ";
//	//scanf("%d", &n);
//	cin >> n;
//
//	count = 0;
//	omp_set_num_threads(4);
//#pragma omp parallel for private(x, y, z) reduction(+:count) 
//	for (i = 0; i < n; ++i) {
//
//		//cout << "rand(): " << rand() << " ;		RAND_MAX: " << RAND_MAX << endl;
//		x = (double)rand() / RAND_MAX;
//
//		y = (double)rand() / RAND_MAX;
//
//		z = x * x + y * y;
//
//		if (z <= 1) count++;
//	}
//
//
//#pragma omp single
//	pi = (double)count / n * 4;
//
//	//printf("Approximate PI = %g", pi);
//	cout << "Approximate PI = " << pi;
//
//	return(0);
//}


////Parallel PI number approximation
//static long num_steps = 100000; double step;
//#define NUM_THREADS 2
//int main()
//{
//	int i; double x, pi, sum = 0.0;
//	step = 1.0 / (double)num_steps;
//	omp_set_num_threads(NUM_THREADS);
//#pragma omp parallel for private(x) reduction(+:sum)
//	for (i = 0; i < num_steps; i++) {
//		x = (i + 0.5) * step;
//		sum = sum + 4.0 / (1.0 + x * x);
//	}
//	pi = step * sum;
//	cout << pi;
//}


////Serial PI number approximation
//int main()
//{
//	static long num_steps = 100000;
//	double step;
//	int i; double x, pi, sum = 0.0;
//	step = 1.0 / (double)num_steps;
//	for (i = 0; i < num_steps; i++) {
//		x = (i + 0.5) * step;
//		sum = sum + 4.0 / (1.0 + x * x);
//	}
//	pi = step * sum;
//	cout << pi;
//}


//int main()
//{
//	int matrixSample[4][4];
//	fill(*matrixSample, *matrixSample + 4 * 4, 0);
//	cout << "matrixSample: " << matrixSample << endl;
//	cout << "*matrixSample: " << *matrixSample << endl;
//	cout << "*matrixSample + 4 * 4: " << *matrixSample + 4 * 4 << endl;
//
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			if (i == 0||j==0)
//				matrixSample[i][j] = 4;
//			cout << "Item[" << i << ", " << j << "]: " << matrixSample[i][j] << endl;
//		}
//	}
//
//
//	cout << "parallel approach:" << endl;
//
//	string result = "";
//	omp_set_num_threads(4);
//
////#pragma omp parallel for
//	for (int i = 1; i < 4; i++)
//	{
//		for (int j = 1; j < 4; j++)
//		{
//			matrixSample[i][j] += matrixSample[i-1][j-1]+ matrixSample[i - 1][j]+ matrixSample[i][j - 1];
//			cout << "Item[" << i << ", " << j << "]: " << matrixSample[i][j] << endl;
//		}
//	}
//
//
//}


//int main()
//{
//	static long num_steps = 100000;
//	double step; 
//	int i; double x, pi, sum = 0.0;
//	step = 1.0 / (double)num_steps;
//	omp_set_num_threads(4);
//	//double threads[4];
//
//#pragma omp parallel for private(x) reduction( + : sum )
//	for (i = 0; i < num_steps; i++) {
//		//int id = omp_get_thread_num();
//		x = (i + 0.5) * step;
//		sum+= 4.0 / (1.0 + x * x);
//	}
//
//	//#pragma omp single
////	for (int j = 0; j < 4; j++)
////		sum += threads[j];
//	pi = step * sum;
//	cout << pi;
//}




//int main() {
//
//#pragma omp parallel num_threads(5)
//    {
//        int id = omp_get_thread_num();
//        std::cout << "Hello Hello Hello Hello Hello " << " from" << id << std::endl;
//    }
//
//    return 0;
//}

//int fib(int n)
//{
//    int i, j;
//    if (n < 2)
//    {
//        return n;
//    }
//    else
//    {
//#pragma omp task shared(i) firstprivate(n)
//        i = fib(n - 1);
//#pragma omp task shared(j) firstprivate(n)
//        j = fib(n - 2);
//    }
//#pragma omp taskwait
//    return i + j;
//}
//
//int main()
//{
//    int n = 10;
//    cout << "Number of threads: " << omp_get_num_threads() << endl;
//    omp_set_dynamic(0);
//    omp_set_num_threads(4);
//#pragma omp parallel shared(n)
//    {
//        cout << "Number of threads(in parallel region): " << omp_get_num_threads << endl;
//#pragma omp single
//        printf("fib(%d) = %d\n", n, fib(n));
//    }
//}

// int main()
// {
//     omp_set_num_threads(4);
// #pragma omp parallel
//     {
// #pragma omp single
//         {

// #pragma omp task
//             {
//                 cout << "task 1!\n";
//             }

// #pragma omp task
//             {
//                 cout << "task 2!\n";
//             }
// #pragma omp taskwait
// #pragma omp task
//             {
//                 cout << "task 3!\n";
//             }

// #pragma omp parallel sections
//             {
// #pragma omp section
//                 {
//                     cout << "Hello World!\n";
//                 }

// #pragma omp section
//                 {
//                     cout << "Hello World 2!\n";
//                 }
//             }
//         }
//     }
// }
