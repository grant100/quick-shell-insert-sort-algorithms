// Project6.cpp : Defines the entry point for the console application.

// Author:	   Grant Sowards
// Assignment:	   project 6
// File:	   project6.cpp
// Instructor:	   Reza Sonati
// Class:	   CS 2420  Section: 001 
// Date Written:   06/015/2015 
// Description:  Sorting

// I declare that the source code contained in this assignment was written solely by me.
// I understand that copying any source code, in whole or in part,
// constitutes cheating, and that I will receive a zero on this project
// if I am found in violation of this policy.

#include "stdafx.h"
#include <time.h> 
#include <stdio.h>
#include <dos.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
const int ONE = 1;
const int TWO = 2;

//Node definition
struct Node
{	
	Node(string);
	clock_t e_clock;
	clock_t e_time;
	int size;
	string name;
};

//Node constructor
Node::Node(string setName)
{
	 e_clock = NULL;
	 e_time = NULL;
	 size = 0;
	 name = setName;
}

// Function Name: writeFile
// Purpose: write sorted vector to file 
// Parameters: (vector<int> dataVector, Node insertNode)
// Returns:	  void
// Pre-conditions: none
// Post-conditions: file created
void writeFile(vector<int> dataVector, Node insertNode)
{
	string name = insertNode.name + ".txt";
	ofstream oFile;
	oFile.open(name);
	for (int i = 0; i < dataVector.size(); i++)
	{
		oFile <<"\n"<< dataVector[i];
		//cout << "\n" << dataVector[i];
	}
		oFile.close();
}


// Function Name: pivot
// Purpose:generate pivot index 
// Parameters: (vector<int> dataVector, int left, int right)
// Returns:	  int
// Pre-conditions: none
// Post-conditions: none
int pivot(vector<int> dataVector, int left, int right)
{
	return (left + right) / 2;//use middle value for pivot
}

// Function Name: splitFunc
// Purpose:	  sort items based on pivot value
// Parameters: (vector<int> &dataVector, int left, int right)
// Returns:	  int
// Pre-conditions: unsorted vector/sub vector	
// Post-conditions: sorted vector based on pivot value
int splitFunc(vector<int> &dataVector, int left, int right)
{
	int pivot_index = pivot(dataVector, left, right);//select pivot
	int pivot = dataVector[pivot_index];//get pivot value
	int left_index = left;//begin index at position 0
	
	int temp = pivot;
	dataVector[pivot_index] = dataVector[right];//move right most value in vector to pivot place
	dataVector[right] = pivot;//move pivot to right most position in vector
	for (int i = left; i <= right - 1; i++)//begin check from leftmost position in vector
	{
		if (dataVector[i] < pivot)//if value is less than the index then swap it with the left most value and increment the index at leftmost position by 1
		{
			int temp2 = dataVector[i];
			dataVector[i] = dataVector[left_index];
			dataVector[left_index] = temp2;
			left_index += 1;
		}
	}
	//when we reach here the value in left_index is not less than the pivot
	//replace left_index with the pivot value (move it back), and move value at index to the right most position
	int temp3 = dataVector[left_index];
	dataVector[left_index] = dataVector[right];
	dataVector[right] = temp3;
	
	return left_index;//this now contains the pivot value and is the split point for the vector
}

// Function Name: quickSort
// Purpose:	  Sort data using quick method
// Parameters: (vector<int> dataVector, int left, int right, Node &quickNode)
// Returns:	  void
// Pre-conditions: unsorted vector	
// Post-conditions: sorted vector written to file
void quickSort(vector<int> &dataVector, int left, int right, Node &quickNode)//have to pass by reference in order for the vector to be modified
{
	clock_t start;
	clock_t end;
	start = clock();
	if (left < right)
	{
		int split = splitFunc(dataVector, left, right);
		quickSort(dataVector, left, split - 1, quickNode);//recursive call for left sub vector
		quickSort(dataVector, split + 1, right, quickNode);//recursive call for right sub vector
	}
	end = clock();
	//store statistical information in object
	quickNode.e_clock = end - start;
	quickNode.e_time = ((end - start) / CLK_TCK);
	quickNode.size = dataVector.size();
	return;
}

// Function Name: shellSort
// Purpose:	  Sort data using Shell (gap) method
// Parameters: (vector<int> dataVector, clock_t start, clock_t &end, Node &insertNode)
// Returns:	  void
// Pre-conditions: unsorted vector	
// Post-conditions: sorted vector written to file
void shellSort(vector<int> dataVector, clock_t start, clock_t end, Node &insertNode)
{
	start = clock();
	int size = dataVector.size() - 1;
	int j;
	for (int space = size / 2; space > 0; space =  space/ 2)//the gap is half the size of vector, then for each iteration reduce size by 1/2
	{
		for (int i = space; i < size; ++i)//loop for iterating though values separated by gap value
		{
			int temp = dataVector[i];//temp value to store i (value on right side of vector) if it is smaller then j-space and swap is needed
			for (j = i; j >= space && temp < dataVector[j - space]; j = j- space)//if the value at j-space is greater than value at i then move j-space value to i
			{
				dataVector[j] = dataVector[j - space];
			}
			dataVector[j] = temp; //move smaller 'i' value to where j -space was
		}
	}
	end = clock();
	//store stastical information in object
	insertNode.e_clock = end - start;
	insertNode.e_time = ((end - start) / CLK_TCK);
	insertNode.size = dataVector.size(); 
	//write file
	writeFile(dataVector, insertNode);

}

// Function Name: insertionSortcontinueInput()
// Purpose:	  Sort data using insertion method
// Parameters: (vector<int> dataVector, clock_t start, clock_t &end, Node &insertNode)
// Returns:	  void
// Pre-conditions: unsorted vector	
// Post-conditions: sorted vector written to file
void insertionSort(vector<int> dataVector, clock_t start, clock_t &end, Node &insertNode)
{
	start = clock();
	int i, j, tmp;
	for (i = 1; i < dataVector.size(); i++) 
	{
		j = i;
		while (j > 0 && dataVector[j - 1] > dataVector[j]) //begin comparing prior position to next sequential position, if prior value is greater than
		{												   //next value then swap, continue in this loop until the condition is no longer met (pushes smallest number to front)	
			tmp = dataVector[j];
			dataVector[j] = dataVector[j - 1];
			dataVector[j - 1] = tmp;
			j--;
		}
	}
	end = clock();   
	//store stastical information in object
	insertNode.e_clock = end-start; 
	insertNode.e_time = ((end - start) / CLK_TCK);
	insertNode.size = dataVector.size();
	//write file
	writeFile(dataVector, insertNode);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream iFile;
	//create sorting objects
	Node insert_1("insert_sort_1");
	Node insert_2("insert_sort_2");
	Node insert_3("insert_sort_3");
	Node shell_1("shell_sort_1");
	Node shell_2("shell_sort_2");
	Node shell_3("shell_sort_3");
	Node quick_1("quick_sort_1");
	Node quick_2("quick_sort_2");
	Node quick_3("quick_sort_3");
	//declare vector
	vector<int> dataVector;
	int data;
	bool isOpen = false;
	bool isContinue = true;
	clock_t start = NULL; 
	clock_t end = NULL;

	std::cout << "Grant Sowards" << "\nCS 2420" << "\nProject 6 Sorting" << endl;
	int counter = 0;
	while (isContinue)
	{
		
		std::cout << "\nEnter file name (include extension), e.g. numbers.txt: " << endl;
		while (!isOpen)
		{
			string cinName;
			cin >> cinName;
			string fileName = cinName;
			iFile.open(fileName);
			if (iFile.is_open())
			{
				isOpen = true;
				std::cout << "\nOpening File..." << endl;
			}
			else
			{
				cin.clear();
				std::cout << "Could not open file!" << "\n\nTry Again: ";
			}

		}
		cout << "\n------------------Sorting Updates-------------";
		
		while (!iFile.eof()) //read in file
		{
			iFile >> data;
			dataVector.push_back(data);
		}
		iFile.close();
		int size = dataVector.size();
		int zero = 0;

		//this series calls each sort and passes in the vector and the sort object
		if (counter == 0)
		{
			shellSort(dataVector, start, end, shell_1);
			cout << "\nShell Sort Complete...";
			insertionSort(dataVector, start, end, insert_1);
			cout << "Insertion Sort Complete...";
			quickSort(dataVector, zero, size - 1, quick_1);
			cout << "Quick Sort Complete...";
			writeFile(dataVector, quick_1);
			dataVector.clear();
			cout << "\nLoad next file: ";
			isContinue = true;
			isOpen = false;
		}
		if (counter == 1)
		{
			shellSort(dataVector, start, end, shell_2);
			cout << "\nShell Sort Complete...";
			insertionSort(dataVector, start, end, insert_2);
			cout << "Insertion Sort Complete...";
			quickSort(dataVector, zero, size - 1, quick_2);
			cout << "Quick Sort Complete...";
			writeFile(dataVector, quick_2);
			dataVector.clear();

			cout << "\nLoad next file: ";
			isContinue = true;
			isOpen = false;
		}
		if (counter == 2)
		{

			shellSort(dataVector, start, end, shell_3);
			cout << "\nShell Sort Complete...";
			insertionSort(dataVector, start, end, insert_3);
			cout << "Insertion Sort Complete...";
			quickSort(dataVector, zero, size - 1, quick_3);
			cout << "Quick Sort Complete...";
			writeFile(dataVector, quick_3);
			dataVector.clear();
			isContinue = false;
		}
		counter++;

	}
	//insertion sort on 100,000 values takes a VERY long time FYI
	cout << "\n--------------------------Statistical Information-----------------------" << endl;
	cout << "\nName: " << shell_1.name << " Clock: " << shell_1.e_clock << " Elapsed Time: " << shell_1.e_time << " Size: " << shell_1.size;
	cout << "\nName: " << insert_1.name << " Clock: " << insert_1.e_clock << " Elapsed Time: " << insert_1.e_time << " Size: " << insert_1.size;
	cout << "\nName: " << quick_1.name << " Clock:  " << quick_1.e_clock << " Elapsed Time: " << quick_1.e_time << " Size: " << quick_1.size;
	cout << "\n";
	cout << "\nName: " << shell_2.name << " Clock:  " << shell_2.e_clock << " Elapsed Time: " << shell_2.e_time << " Size: " << shell_2.size;
	cout << "\nName: " << insert_2.name << " Clock: " << insert_2.e_clock << " Elapsed Time: " << insert_2.e_time << " Size: " << insert_2.size;
	cout << "\nName: " << quick_2.name << " Clock:  " << quick_2.e_clock << " Elapsed Time: " << quick_2.e_time << " Size: " << quick_2.size;
	cout << "\n";
	cout << "\nName: " << shell_3.name << " Clock:  " << shell_3.e_clock << " Elapsed Time: " << shell_3.e_time << " Size: " << shell_3.size;
	cout << "\nName: " << insert_3.name << " Clock:  " << insert_3.e_clock << " Elapsed Time: " << insert_3.e_time << " Size: " << insert_3.size;
	cout << "\nName: " << quick_3.name << " Clock:  " << quick_3.e_clock << " Elapsed Time: " << quick_3.e_time << " Size: " << quick_3.size;
	cout << "\n\nExiting...";

	std::cin.clear();
	std::cin.ignore();
	std::cin.get();
	return 0;
}

