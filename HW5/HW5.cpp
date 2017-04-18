/*
	Homework 5
	Zak Fahey, Evan Vujcec
*/
using namespace std;
#include <stdlib.h>
#include <functional>
#include <chrono>
#include <string>
typedef chrono::high_resolution_clock Clock;

int * randomArray(int size)
{
	int *arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % (2 * size);
	}
	return arr;
}

void testSortingMethod(string name, function<int* (int[], int)> sortingFunction, const int** arrays)
{
	int arraySizes[5] = { 10, 100, 500, 5000, 25000 };

	for (int i = 0; i < 5; i++)
	{
		auto start = Clock::now();

		//Duplicate array
		

		auto end = Clock::now();
		int time = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	}
}

//Sorting methods
int * bubbleSort(int input[], int size)
{

}
int * insertionSort(int input[], int size)
{

}
int * mergeSort(int input[], int size)
{

}
int * quickSort(int input[], int size)
{

}
int * heapSort(int input[], int size)
{

}
int * countingSort(int input[], int size)
{

}
int * radixSort(int input[], int size)
{

}
//

int main()
{
	srand(NULL);
	int *arrays[5];
	arrays[0] = randomArray(10);
	arrays[1] = randomArray(100);
	arrays[2] = randomArray(500);
	arrays[3] = randomArray(5000);
	arrays[4] = randomArray(25000);

	testSortingMethod("Bubble sort", bubbleSort, arrays);
	testSortingMethod("Insertion sort", insertionSort, arrays);
	testSortingMethod("Merge sort", mergeSort, arrays);
	testSortingMethod("Quicksort", quickSort, arrays);
	testSortingMethod("Heapsort", heapSort, arrays);
	testSortingMethod("Counting sort", countingSort, arrays);
	testSortingMethod("Radix sort", radixSort, arrays);

	return 0;
}