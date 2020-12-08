#pragma once
#include "BinTreeImplementation.h"
#include <stack>
#include <assert.h>
namespace Heap
{
    template <class treeType>
    // The function for swapping the heap vector values
    void swap(treeType& a, treeType& b)
    {
        treeType tempA = a;
        a = b;
        b = tempA;
    }

    int Parent(int i)
    {
        assert(i > 1);
        return i / 2;
    }

    int Left(int i)
    {
        assert(i >= 1);
        return i * 2;
    }

    int Right(int i)
    {
        assert(i >= 1);
        return i * 2 + 1;
    }

    template <class treeType>
    void Heapify(vector<treeType> &A, int index)
    {
        unsigned int largest = index;
        unsigned int leftIndex = 2 * index;
        unsigned int rightIndex = 2 * index + 1;

        // If the leftChild of the current "node" is greater, then set the index of the largest to the index of the leftChild
        if (leftIndex <= A.size() - 1 && A[leftIndex] > A[index])
        {
            largest = leftIndex;
        }
        // If the rightChild of the current "node" is greater than the current "node", then set the index of the largest to the index of the rightChild. If the leftChild was greater than the current "node" and the rightChild is greater than the leftChild then set the largest index to the rightChild
        if (rightIndex <= A.size() - 1 && A[rightIndex] > A[largest])
        {
            largest = rightIndex;
        }
        // If the largest of the subtree (the current, left, and right nodes) is not equal to the current node, then swap the current node's value with the value of the largest node in the heapArray
        if (largest != index)
        {
            swap(A[index], A[largest]);
            // Repeat the process at the subtree to "heapify" the subtree if needed
            Heapify(A, largest);
        }
    }

    template <class treeType>
    void BuildHeap(vector <treeType> &heapVec)
    {
        // Starts at the index of the last parent node (the parent of the last/rightmost leaf node) and heapifies working up the tree (until the root node @ index 1 is reached). The ending result should be a completely heapified tree
        for (int ix = ((heapVec.size() - 1) / 2) + 1; ix != 0; ix--)
        {
            Heapify(heapVec, ix);
        }
    }

    template <class treeType>
    treeType HeapExtractMax(vector<treeType> &heapVec)
    {
        auto heapMax = heapVec[1];
        // After saving the max heap value in heapMax, switch the max value and the last value in the heap and then remove the last value in the heap
        swap(heapVec[1], heapVec[heapVec.size() - 1]);
        heapVec.pop_back();
        // After you have swapped the values and removed the last value, heapify so the elements satisfy the properties of a heap
        Heapify(heapVec, 1);
        return heapMax;
    }

    template <class treeType>
    // Takes an heap array as parameter and returns the sorted elements in a vector
    vector <treeType> HeapSort(const vector<treeType> heapVec)
    {
        vector<treeType> subHeap = heapVec;
        // Extract the max of the heap (the ExtraMax function then removes the max from the heap and reheapifies the sub heap)

        
        vector<treeType> sortedVec (heapVec.size());
        int size = heapVec.size() - 1;
        for (auto ix = size; ix >=1 ; ix--)
        {
            sortedVec[ix] = HeapExtractMax(subHeap);
        }
        // Return the sorted vector
        return sortedVec;
    }


    template <class treeType>
    void HeapInsert(vector <treeType> &heapVec, treeType insertVal)
    {
        heapVec.push_back(insertVal);
        auto i = heapVec.size() - 1;
        while (i > 1 && heapVec[Parent(i)] < insertVal)
        {
            swap(heapVec[Parent(i)], heapVec[i]);
            i = Parent(i);
        }
    }
}

