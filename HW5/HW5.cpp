/*
	Homework 5
	Zak Fahey, Evan Vujcec
*/
using namespace std;
#include <stdlib.h>
#include <functional>
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>
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

string printArray(int *arr, int size)
{
	string ret = "[ ";

	for (int i = 0; i < size; i++)
	{
		if (i != 0)
		{
			ret += ", ";
		}
		ret += to_string(arr[i]);
	}

	ret += " ]";

	return ret;
}

void testSortingMethod(string name, function<int* (int[], int)> sortingFunction, const int** arrays)
{
	int arraySizes[5] = { 10, 100, 500, 5000, 25000 };

	cout << name << ":" << endl;

	for (int i = 0; i < 5; i++)
	{
		auto start = Clock::now();
		int *result;

		for (int j = 0; j < 10; j++)
		{
			int *clonedArray;
			copy(arrays[i], arrays[i] + arraySizes[i], clonedArray);
			//TODO: will the array returned by this function be an altered clonedArray pointer or will it be a new array? The former may cause issues.
			result = sortingFunction(clonedArray, arraySizes[i]);
			delete clonedArray;
		}

		auto end = Clock::now();
		int time = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		cout << "Array size: " << arraySizes[i] << ", Sorted result: " << printArray(result, arraySizes[i]) << ", Time: " << time << "ns" << endl;
		delete result;
	}
	cout << endl;
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