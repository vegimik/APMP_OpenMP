//#include <iostream>
//using namespace std;
//#include <omp.h>
//#include <string.h>
//#include <stdlib.h>
//#include <random>
//#include <math.h>
//#include <time.h>
//
//struct Node {
//	int data;
//	Node* next;
//};
//
//int main() {
//
//	struct Node* head = new Node;
//	struct Node* currNode = head;
//
//	head->data = 0;
//	for (int i = 1; i < 10; ++i) {
//		currNode->next = new Node;
//		currNode = currNode->next;
//		currNode->data = i;
//	}
//
//	// traverse the linked list:
//	// examine data
//#pragma omp parallel
//	{
//		currNode = head;
//#pragma omp single
//		{
//			while (currNode) {
//#pragma omp task firstprivate(currNode)
//				{
//#pragma omp critical (cout)
//					std::cout << "Node data: " << currNode->data << " " << omp_get_thread_num() << "\n";
//				}
//				currNode = currNode->next;
//			}
//		}
//	}
//}