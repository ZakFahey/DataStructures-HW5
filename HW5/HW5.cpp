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
#include <vector>
typedef chrono::high_resolution_clock Clock;

vector<int> randomArray(int size)
{
	vector<int> arr;
	arr.reserve(size);
	for (int i = 0; i < size; i++)
	{
		arr.push_back(rand() % (2 * size));
	}
	return arr;
}

string printArray(vector<int> arr)
{
	string ret = "[ ";

	for (int i = 0; i < arr.size(); i++)
	{
		if (i != 0)
		{
			ret += ", ";
		}
		if (i > 50)
		{
			ret += "...";
			break;
		}
		ret += to_string(arr[i]);
	}

	ret += " ]";

	return ret;
}

void testSortingMethod(string name, function<vector<int> (vector<int>)> sortingFunction, vector<int> arrays[5])
{
	int arraySizes[5] = { 10, 100, 500, 5000, 25000 };

	cout << name << ":" << endl;

	for (int i = 0; i < 5; i++)
	{
		vector<int> result;
		auto start = Clock::now();
		for (int j = 0; j < 1; j++)
		{
			result = sortingFunction(arrays[i]);
		}
		auto end = Clock::now();
		int time = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

		cout << "Array size: " << arraySizes[i] << ", Sorted result: " << printArray(result) << ", Time: " << time << "ns" << endl;
	}
	cout << endl;
}

//Sorting methods
vector<int> bubbleSort(vector<int> input)
{
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (int i = 0; i < input.size() - 1; i++)
		{
			//Swap the values if they're not in the right order
			if (input[i] > input[i + 1])
			{
				int temp = input[i];
				input[i] = input[i + 1];
				input[i + 1] = temp;
				swapped = true;
			}
		}
	}
	return input;
}
vector<int> insertionSort(vector<int> input)
{
	return input;
}
vector<int> mergeSort(vector<int> input)
{
	return input;
}
vector<int> quickSort(vector<int> input)
{
	return input;
}
vector<int> heapSort(vector<int> input)
{
	return input;
}
vector<int> countingSort(vector<int> input)
{
	return input;
}
vector<int> radixSort(vector<int> input)
{
	return input;
}
//

int main()
{
	srand(NULL);
	vector<int> arrays[5];
	arrays[0] = randomArray(10);
	arrays[1] = randomArray(100);
	arrays[2] = randomArray(500);
	arrays[3] = randomArray(5000);
	arrays[4] = randomArray(25000);

	testSortingMethod("Bubble sort", bubbleSort, arrays);
	//testSortingMethod("Insertion sort", insertionSort, arrays);
	//testSortingMethod("Merge sort", mergeSort, arrays);
	//testSortingMethod("Quicksort", quickSort, arrays);
	//testSortingMethod("Heapsort", heapSort, arrays);
	//testSortingMethod("Counting sort", countingSort, arrays);
	//testSortingMethod("Radix sort", radixSort, arrays);

	int a;
	cin >> a;
	return 0;
}