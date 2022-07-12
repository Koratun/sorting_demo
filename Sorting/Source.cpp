//Kody Mitchell
//Sorting program - a program to demonstrate the efficiency of different sorting algorithms.
//11/26/2021

#include<iostream>
#include<random>
#include<chrono>

using namespace std;

//Swaps the elements at the given addresses.
void swap(int* a, int* b);

//Takes a pointer to an array and the indices where to begin and end sorting.
//Sorts the array by comparing each element to its neighbor and swapping them if the left neighbor is not less than the right neighbor.
void bubbleSort(int arr[], int begin, int end);

//Takes a pointer to an array and the indices where to begin and end sorting.
//From left to right insert elements into a sublist that is sorted as elements are inserted.
void insertionSort(int arr[], int begin, int end);

//Takes a pointer to an array and the indices where to begin and end sorting.
//Split the array into two sublists, sort them, and then combine them into one sorted list recursively.
//Must also be supplied with a temp array with the same size as the given array.
void mergeSort(int arr[], int tempArr[], int begin, int end);

//Helper function to merge two lists that are within one array.
void merge(int arr[], int tempArr[], int begin, int center, int end);

//Simply prints the given array from the given indices.
void printArray(int arr[], int begin, int end);

//Function to fill the array with random values, also prints the array if it is small enough.
void prepArray(int arr[], int size);


int main() {
	const int n = 10000;
	int myArray[n];

	//Seed the random number generator
	srand(time(0));



	//Begin Bubble section
	cout << "Bubble:\n";
	prepArray(myArray, n);

	//Start timer
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	bubbleSort(myArray, 0, n);
	//End timer
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	//Get time passed
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	if (n < 100) {
		cout << "\nSorted: \n";
		printArray(myArray, 0, n);
	}

	cout << "\nTime: " << time_span.count() << " seconds.\n";



	//Begin Insertion section
	cout << "\nInsertion:\n";
	prepArray(myArray, n);

	//Start timer
	t1 = chrono::high_resolution_clock::now();
	insertionSort(myArray, 0, n);
	//End timer
	t2 = chrono::high_resolution_clock::now();
	//Get time passed
	time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	if (n < 100) {
		cout << "\nSorted: \n";
		printArray(myArray, 0, n);
	}

	cout << "\nTime: " << time_span.count() << " seconds.\n";


	//Begin Merge section
	cout << "\nMerge:\n";
	prepArray(myArray, n);
	//Merge requires additional temp array
	{
		int temp[n];

		//Start timer
		t1 = chrono::high_resolution_clock::now();
		mergeSort(myArray, temp, 0, n);
		//End timer
		t2 = chrono::high_resolution_clock::now();
		//Get time passed
		time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	//the temp array moves out of scope, and out of memory
	}

	if (n < 100) {
		cout << "\nSorted: \n";
		printArray(myArray, 0, n);
	}

	cout << "\nTime: " << time_span.count() << " seconds.\n";



	return 0;
}

void prepArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 1000;
	}

	if (size < 100) {
		cout << "Unsorted: \n";
		printArray(arr, 0, size);
	}
}


void printArray(int arr[], int begin, int end) {
	for (int i = begin; i < end; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


void bubbleSort(int arr[], int begin, int end){
	//(begin, end]

	//Iterate through the list 'size - 1' times
	for (int passes = end - begin - 1; passes > 0; passes--) {
		//Go through the list and compare elements. 
		for (int i = 0; i < passes; i++) {
			//If left is greater than right, then swap
			if (arr[i] > arr[i + 1]) {
				swap(arr + i, arr + i + 1);
			}
		}
	}

}

void insertionSort(int arr[], int begin, int end)
{
	//(begin, end]

	//Iterate through the list 'size - 1' times
	for (int pass = 1; pass < end - begin; pass++) {
		//Go through the sublist to see where the element should be inserted.
		int newValue = arr[pass];
		int i;
		for (i = pass; i > 0; i--) {
			//If the previous element is greater than the new element, shift it to the right.
			if (arr[i - 1] > newValue) {
				//Shift to the right.
				arr[i] = arr[i - 1];
			}
			//If the previous element is less than or equal to the new element, then this is the position we want to insert the new element.
			else {
				//Break out of the loop and use the 'i' value to insert the new element.
				break;
			}
		}
		//Even if the new value is the new smallest value, i will be 0, so this will function correctly.
		arr[i] = newValue;

	}

}

void mergeSort(int arr[], int tempArr[], int begin, int end){
	

	//If we aren't sorting one element
	if (begin < end - 1) {
		//Find the center of the given array
		int center = (end - begin) / 2 + begin;
		//Sort the left list
		mergeSort(arr, tempArr, begin, center);
		//Sort the right list
		mergeSort(arr, tempArr, center, end);
		//merge the lists
		merge(arr, tempArr, begin, center, end);

	}

}

void merge(int arr[], int tempArr[], int begin, int center, int end){
	//Keep track of where we are within each subarray
	int leftPos = begin, rightPos = center;
	//Keep track of where we are within the temp array
	int tempInd = begin;

	//As long as there are elements to be sorted in either list...
	while (leftPos < center || rightPos < end) {

		//If there are elements to be sorted in both lists
		if (leftPos < center && rightPos < end) {

			//See which element is smaller
			if (arr[leftPos] < arr[rightPos]) {

				//Add the element from the LEFT sublist to the temp array, and increment the respective indices
				tempArr[tempInd++] = arr[leftPos++];
			}
			else {
				//Add the element from the RIGHT sublist to the temp array, and increment the respective indices
				tempArr[tempInd++] = arr[rightPos++];
			}
		}
		//If there are elements to be sorted in only one list
		else if (leftPos < center) {

			//Add the element from the LEFT sublist to the temp array, and increment the respective indices
			tempArr[tempInd++] = arr[leftPos++];
		}
		else {
			//Add the element from the RIGHT sublist to the temp array, and increment the respective indices
			tempArr[tempInd++] = arr[rightPos++];
		}
	}

	//Elements have been sorted into the temp array
	//Move them back to the original array in order
	for (tempInd = begin; tempInd < end; tempInd++) {
		arr[tempInd] = tempArr[tempInd];
	}

}
