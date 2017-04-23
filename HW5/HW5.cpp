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

bool isSorted(vector<int> arr)
{
	for (int i = 0; i < arr.size() - 1; i++)
	{
		if (arr[i] > arr[i + 1]) return false;
	}
	return true;
}

bool hasSameItems(vector<int> original, vector<int> sorted)
{
	int *rates = new int[original.size() * 2];

	//Initialize the array
	for (int i = 0; i < original.size() * 2; i++)
	{
		rates[i] = 0;
	}
	//Add up the difference in frequencies between the two lists
	for (int i = 0; i < original.size(); i++)
	{
		rates[original[i]]++;
		rates[sorted[i]]--;
	}
	//Verify that the number of each number is the same with each list
	for (int i = 0; i < original.size() * 2; i++)
	{
		if (rates[i] != 0) return false;
	}
	return true;
}

void testSortingMethod(string name, function<vector<int> (vector<int>)> sortingFunction, vector<int> arrays[5])
{
	int arraySizes[5] = { 10, 100, 500, 5000, 25000 };

	cout << name << ":" << endl;

	for (int i = 0; i < 5; i++)
	{
		vector<int> result;
		auto start = Clock::now();
		//Running fewer iterations for the last few arrays
		for (int j = 0; j < (i > 3 ? 1 : 10); j++)
		{
			result = sortingFunction(arrays[i]);
		}
		auto end = Clock::now();
		int time = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * (i > 3 ? 10 : 1);

		cout << "Array size: " << arraySizes[i] << ", Is sorted: " << isSorted(result) << ", Has same items: " << hasSameItems(arrays[i], result) << ", Time: " << time << "ns" << endl;
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
	for (int i = 1; i < input.size(); i++)
	{
		int j = i;
		//Find right spot
		while (j > 0 && input[i] < input[j - 1])
		{
			j--;
		}
		int temp = input[i];
		//Push other items forward
		for (int k = j; k < i; k++)
		{
			input[k + 1] = input[k];
		}
		//Put item in right spot
		input[j] = temp;
	}
	return input;
}

vector<int> mergeSort(vector<int> input)
{
	if(input.size() == 1) return input;

	if (input.size() == 2)
	{
		if (input[1] < input[0])
		{
			int temp = input[1];
			input[1] = input[0];
			input[0] = temp;
		}
		return input;
	}

	vector<int> newVec1, newVec2;
	//Split vector into 2
	for (int i = 0; i < input.size(); i++)
	{
		if (i < input.size() / 2)
		{
			newVec1.push_back(input[i]);
		}
		else
		{
			newVec2.push_back(input[i]);
		}
	}

	//Sort the 2 subvectors
	newVec1 = mergeSort(newVec1);
	newVec2 = mergeSort(newVec2);

	//Merge the two subvectors together
	int index1 = 0, index2 = 0, resultIndex = 0;
	while (resultIndex < input.size())
	{
		//Insert either the smaller item or the one that isn't empty
		if (index2 >= newVec2.size() || (index1 < newVec1.size() && newVec1[index1] < newVec2[index2]))
		{
			input[resultIndex] = newVec1[index1];
			index1++;
		}
		else
		{
			input[resultIndex] = newVec2[index2];
			index2++;
		}
		resultIndex++;
	}

	return input;
}

void quickSortInner(vector<int>& input, int left, int right)
{
	// Assigning the left and right pointers
	int i = left;
	int j = right;

	// Assigning random pivot value
	int pivot = input[left + (rand() % (left - right))];
	int temp;

	// Partioning of the data
	while (i <= j)
	{
		// Find values to swap
		while (input[i] < pivot) { i++; }
		while (input[j] > pivot) { j--; }

		// Swap values
		if (i <= j)
		{
			temp = input[i];
			input[i] = input[j];
			input[j] = temp;
			i++;
			j--;
		}
	}

	if (left < j)
		quickSortInner(input, left, j);
	if (i < right)
		quickSortInner(input, i, right);
}

vector<int> quickSort(vector<int> input)
{
	quickSortInner(input, 0, input.size()-1);
	return input;
}

vector<int> heapSort(vector<int> input)
{
	return input;
}

vector<int> countingSortInner(vector<int> input, int range, function<int(int)> comparison)
{
	int *rates = new int[range];

	//Initialize the array
	for (int i = 0; i < range; i++)
	{
		rates[i] = 0;
	}
	//Add up the frequencies
	for (int i = 0; i < input.size(); i++)
	{
		rates[comparison(input[i])]++;
	}
	//Make the frequencies cumulative
	for (int i = 1; i < range; i++)
	{
		rates[i] += rates[i - 1];
	}
	//Build the sorted list
	vector<int> clone(input);
	for (int i = input.size() - 1; i >= 0; i--)
	{
		int ind = comparison(clone[i]);
		input[rates[ind] - 1] = clone[i];
		rates[ind]--;
	}

	return input;
}

vector<int> countingSort(vector<int> input)
{
	return countingSortInner(input, input.size() * 2, [](int n) { return n; });
}

int nthDigit(int number, int index)
{
	//Index goes from right to left
	return number / (int)pow(10, index) % 10;
}

vector<int> radixSort(vector<int> input)
{
	for (int i = 0; i < (int)log10(input.size()) + 1; i++)
	{
		input = countingSortInner(input, 10, [i](int n) { return nthDigit(n, i); });
	}
	return input;
}
//

int main()
{
	srand(time(NULL));
	vector<int> arrays[5];
	arrays[0] = randomArray(10);
	arrays[1] = randomArray(100);
	arrays[2] = randomArray(500);
	arrays[3] = randomArray(5000);
	arrays[4] = randomArray(25000);

	//testSortingMethod("Bubble sort", bubbleSort, arrays);
	//testSortingMethod("Insertion sort", insertionSort, arrays);
	//testSortingMethod("Merge sort", mergeSort, arrays);
	testSortingMethod("Quicksort", quickSort, arrays);
	//testSortingMethod("Heapsort", heapSort, arrays);
	//testSortingMethod("Counting sort", countingSort, arrays);
	//testSortingMethod("Radix sort", radixSort, arrays);

	return 0;
}