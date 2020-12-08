#include "BinSearchTree.h"

template <class treeType>
void DisplayVector(vector<treeType> treeVec)
{
    for (auto ix : treeVec)
    {
        cout << ix << " ";
    }
    cout << endl;
}

int main()
{
    auto rootPtr = BinSearchTree::InitBinSearchTree(12);
    cout << "Root Ptr: " << rootPtr << endl;
    vector<int> insertVals{ 5, 9, 2, 13, 13, 15, 17, 18, 19 };
    BinSearchTree::BinSearchTreeInsert(rootPtr, insertVals);
    cout << "Node 19's Ptr: " << BinSearchTree::SearchTree(rootPtr, 19) << endl;
    cout << "Deleting 5 from BinSearchTree." << endl;
    BinSearchTree::DeleteFromTree(BinSearchTree::SearchTree(rootPtr, 5));
    cout << "5's pointer after Deletion: " << BinSearchTree::SearchTree(rootPtr, 5) << endl;
}