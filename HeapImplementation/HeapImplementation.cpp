#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "HeapImplementation.h"
using namespace std;


// Returns a vector of random ints with range of 0-numberOfElements with the 0th element being 0/ there being a garbage value at index 0, so heap operation math is easier
vector<int> RandVec(int numberOfElements)
{
    vector<int> randomVec(numberOfElements + 1);
    randomVec[0] = 0;
    for (int ix = 1; ix <= numberOfElements; ix++)
    {
        randomVec[ix] = rand() % numberOfElements;
    }
    return randomVec;
}

template <class treeType>
void DisplayVector(vector<treeType> displayVec)
{
    for (auto ix : displayVec)
    {
        cout << ix << " ";
    }
    cout << endl;
}

bool comparator(int v1, int v2)
{
    return v1 > v2;
}

int main()
{
    //auto treePtr = BinTree::InitBinTree<int>(1, 1, -1);
    //cout << endl;
    //int nodeCount = 1;
    //vector<int> treeArray(BinTree::GetSizeBinTree(treePtr, nodeCount) + 1);
    //BinTree::TreeToVector(treePtr, 1, treeArray);

    /*vector <int> treeArray{ 0, 4, 1, 3, 2, 16, 9, 10, 14, 8 , 7 };
    Heap::BuildHeap(treeArray);

    cout << "Displaying Heap: ";
    DisplayVector(treeArray);

    auto insertValue = 25;
    cout << "Inserting value \"" << insertValue <<"\" into heap: ";
    Heap::HeapInsert(treeArray, insertValue);
    DisplayVector(treeArray);*/

    vector <int> randomIntVec = RandVec(1000000);
    auto copyVec = randomIntVec;
    Heap::BuildHeap(randomIntVec);
    clock_t start, end;
    start = clock();
    cout << "Beginning sort." << endl;
    vector <int> sortedVec = Heap::HeapSort(randomIntVec);
    cout << "Sorting complete." << endl; 
    end = clock();
    cout << "Vector " << " of size " << randomIntVec.size() -1 << " sorted in " << (end - start) / (double) CLOCKS_PER_SEC << " seconds." << endl;
    // cout << "Displaying sorted elements: ";
    // DisplayVector(sortedVec);

    make_heap(copyVec.begin(), copyVec.end(), comparator);
    start = clock();
    cout << "Beginning sort." << endl;
    sort_heap(copyVec.begin(), copyVec.end(), comparator);
    end = clock();
    cout << "Sorting complete." << endl;
    cout << "Vector " << " of size " << randomIntVec.size() - 1 << " sorted in " << (end - start) / (double)CLOCKS_PER_SEC << " seconds." << endl;
    
    //DisplayVector(copyVec);

}