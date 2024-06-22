#include "LL.cpp"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	bool swap = 1;
	int num;
	int size = 0;
	string file;
	ifstream inFile;
	LL<int> list;
	LL<int>::iterator list1;
	LL<int>::iterator list2;

	cout << "Enter file with list: ";
	cin >> file;
	inFile.open(file);						// open input file

	while (inFile.is_open() == false) {		// loop to check if valid file
		cout << "Invalid file, please re-enter: ";
		cin >> file;
		inFile.open(file);
	}
 
	while (inFile.eof() == false) {			// take input until the end of the file
		size++;
		inFile >> num;
		list.tailInsert(num);
	}

	cout << "Original List" << endl;

	list1 = list.begin();					// print usorted linked list

	while (list1 != nullptr) {
		cout << *list1 << " ";
		list1++;
	}	

	cout << endl << endl;

	do {									// sort the linked list
		swap = 0;
		list1 = list.begin();				// move to the start of the list
		list2 = list.begin();				// move to the second item in the list
		list2++;
											// loop until the end of the list
		while (list1 != nullptr && list2 != nullptr) {
			if (*list1 > * list2) {			// swap if item n > n+1
				list.swapNodes(list1, list2);
				swap = true;
			}
			list1++;
			list2++;
		}
	} while (swap);							// loop while items are still being swapped

	cout << "Sorted List" << endl;

	list1 = list.begin();					// print sorted list


	while (list1 != nullptr) {
		cout << *list1 << " ";
		list1++;
	}

	cout << endl;
}