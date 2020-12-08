#include <iostream>	
#include <string>
#include <list>

using namespace std;


struct SinglyLinkedList
{
	int number;
	SinglyLinkedList* nextPtr;
};



struct StackNode
{
	int number;
	StackNode* prevPtr;
};

typedef SinglyLinkedList* SinglyLinkedListPtr;
typedef StackNode* StackNodePtr;

StackNode* headStackPtr = nullptr;
auto repeatedValsGlobal = list<int>();

void ResetStack();
void DisplayStack(StackNodePtr curPtr);

// Initializes a linked list and returns the value of the first pointer of that singly linked list (only next ptrs)
SinglyLinkedListPtr InitLinkedList(int numberOfNodes)
{
	int counter = 0;

	SinglyLinkedListPtr prevTempNode = nullptr;
	SinglyLinkedListPtr headPtr = nullptr;

	while (counter < numberOfNodes)
	{
		SinglyLinkedListPtr currentNode = new SinglyLinkedList;

		cout << "What is the number associated with this node? ";
		cin >> currentNode->number;

		currentNode->nextPtr = nullptr;
		if (prevTempNode != nullptr)
		{
			prevTempNode->nextPtr = currentNode;
		}
		if (counter == 0)
		{
			headPtr = currentNode;
			prevTempNode = currentNode;
		}
		if (counter == numberOfNodes - 1)
		{
			return headPtr;
		}
		prevTempNode = currentNode;
		counter++;
	}
}

// Displays a linked list beginning from the pointer in the parameter
void DisplayLinkedList(SinglyLinkedListPtr curPtr)
{
	cout << endl;
	while (curPtr != nullptr)
	{
		cout << "Node's associated number: ";
		cout << curPtr->number << endl;
		cout << "Node's Pointer: ";
		cout << curPtr << endl;
		cout << "Node's Next Pointer: ";
		cout << curPtr->nextPtr << endl;
		curPtr = curPtr->nextPtr;
		cout << endl;
	}
}

// Pushes an element onto the stack and updates the headpointer of the stack
void push (int number)
{
	StackNodePtr newStackNode = new StackNode;
	newStackNode->number = number;

	// If the stack is empty, the headStackPtr global variable will be null, so if the stack is empty then make the node being pushed the head node (set its prev ptr to null)
	newStackNode->prevPtr = headStackPtr;	
	headStackPtr = newStackNode;
}

// Appends to the global string of repeatedValues if there are consecutive values preceding the complement value that add up to the complement value
void isComplement(StackNodePtr headPtr, int complementNumber)
{
	int sum = 0;
	// This string will keep track of the values on the stack that add up to the complement number, if the values on the stack do not add up to the complement number, then the string is not added to the repeatedValsGlobal variable which is a string that keeps track of all of the repeated values
	string repeatedValsTemp;
	auto retList = list<int>();
	auto curPtr = headPtr;
	
	while ((curPtr != nullptr) && (sum != complementNumber * -1))
	{
		sum = sum + curPtr->number;
		retList.push_back(curPtr->number);
		curPtr = curPtr->prevPtr;
	}


	if (sum == complementNumber * -1)
	{
		// If the numbers on the stack equal the complement number, then add the string of those values to the global string that keeps track of all the repeated values. complementNumber is included too since that is the number that the numbers on the stack cancel out.
	
		for (auto it = retList.cbegin(); it != retList.cend(); ++it)
		{
			repeatedValsGlobal.push_back(*it);
		}
		repeatedValsGlobal.push_back(complementNumber);
		ResetStack();
		return;
	}
	else
	{
		// If no consecutive numbers in the stack equal the number, then return false.
		ResetStack();
		return;
	}
}

// Function completely resets the stack. This function is necessary after we determine whether or not the stack numbers complement the complementNumber. The stack must be reset after the boolean value is evaluated, so we can keep testing on the other "complementNumbers" in the linked list 
void ResetStack()
{
	StackNodePtr curPtr = nullptr;

	while (curPtr != nullptr)
	{
		curPtr = headStackPtr->prevPtr;
		delete headStackPtr;
		headStackPtr = curPtr;
	}
}

// Function retrieves (returns) the value at the top of the stack and then deletes that value and makes the value that was under that value on the stack the new top of the stack.
int pop()
{
	int returnValue = headStackPtr->number;
	auto headTemp = headStackPtr;
	if (headStackPtr->prevPtr != nullptr)
	{
		headStackPtr = headStackPtr->prevPtr;
	}
	else
	{
		headStackPtr = nullptr;
	}
	return returnValue;
}

// This function pops numbers of the same sign (negative/positive) until a number of the opposite sign is found. Returns the pointer of the number with the opposite sign.
SinglyLinkedListPtr FindComplement(SinglyLinkedListPtr curPtr)
{
	// Checks to see if the current number is positive
	if (curPtr->number >= 0)
	{
		// If it is positive then it traverses the linked list until it hits the end of the list or a negative number
		while ((curPtr->number >= 0) && (curPtr->nextPtr != nullptr))
		{
			// It pushes any non negative numbers onto the stack
			push(curPtr->number);
			curPtr = curPtr->nextPtr;
		}
		return curPtr;
	}
	else
	{
		// Traverses linked list until it finds a negative number or the end of the linked list
		while ((curPtr->number < 0) && (curPtr->nextPtr != nullptr))
		{
			// Pushes any negative numbers onto the stack
			push(curPtr->number);
			curPtr = curPtr->nextPtr;
		}
		return curPtr;
	}
}


// Rewrite so it works with every data type -> use push() and pop() for this
void DisplayStack(StackNodePtr curPtr)
{
	if (curPtr == nullptr)
	{
		cout << "Nothing currently in the stack." << endl;
		return;
	}
	cout << endl;
	while (curPtr != nullptr)
	{
		cout << "Stack Node's number: ";
		cout << curPtr->number << endl;
		cout << "Stack Node's pointer: ";
		cout << curPtr << endl;
		cout << "Stack Node's previous pointer: ";
		cout << curPtr->prevPtr << endl;
		curPtr = curPtr->prevPtr;
		cout << endl;
	}
}

int main()
{
	//Initializes a linked list with 5 elements in it
	auto linkedListPtr = InitLinkedList(6);
	// This loop finds all the "complement numbers"/numbers with a sign that breaks up the current streak of signs and then checks to see if the numbers preceding the complement number (which are added onto the stack in FindComplement) can add up to the number. If they do add up to the number, then the repeatedValsGlobal string will concatenate the values that add up to the complement number. Eventually, if there are any cancelling/complementing values then the repeatedValsGlobal string will contain all of the repeated consecutive values.
	while (linkedListPtr != nullptr)
	{
		// Finds the first "complement" after the specified pointer
		int complementNumber = FindComplement(linkedListPtr)->number;
		//DisplayStack(headStackPtr);

		// Checks to see if any consecutive values preceding the complementNumber add up to the complementNumber, if there are then the global string appends those values to itself
		isComplement(headStackPtr, complementNumber);
		// Moves the pointer that the FindComplement function is using to the pointer after the previous complement value. If no more complements exist in the list the FindComplement function will traverse to the end of the list and then the linkedListPtr will be set to a nullptr and the loop will terminate
		linkedListPtr = FindComplement(linkedListPtr)->nextPtr;
		ResetStack();
	}

	cout << "Redundant values/Consecutive Values that cancel each other out: " << endl;
	for (auto it = repeatedValsGlobal.cbegin(); it != repeatedValsGlobal.cend(); ++it)
	{
		cout << *it;
		cout << " ";
	}
}