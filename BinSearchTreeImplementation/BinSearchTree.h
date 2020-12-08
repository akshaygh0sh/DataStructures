#include <iostream>
#include <vector>

using namespace std;

namespace BinSearchTree
{
    int Left(int index)
    {
        return (index + 1)* 2 - 1;
    }

    int Right(int index)
    {
        return (index + 1) * 2;
    }

    int Parent(int index)
    {
        if (index % 2 == 0)
        {
            return (index / 2) - 1;
        }
        else
        {
            return (index / 2);
        }
    }

    template <class treeType>
    struct BinSearchTree
    {
        treeType nodeData;
        BinSearchTree* leftChild = nullptr;
        BinSearchTree* rightChild = nullptr;
        BinSearchTree* rootPtr = nullptr;
    };

    // Initializes the root node of the binary tree and returns the pointer to the root of the tree
    template <class treeType>
    BinSearchTree<treeType>* InitBinSearchTree(treeType rootVal)
    {
        BinSearchTree<treeType>* rootPtr = new BinSearchTree<treeType>;
        rootPtr->nodeData = rootVal;
        return rootPtr;
    }

    // Inserts a value at the proper index in the binary search tree, increases the size of the tree by one each time the function is called with a new value
    template <class treeType>
    void BinSearchTreeInsert(BinSearchTree<treeType>* rootPtr, treeType insertVal)
    {
        BinSearchTree<treeType>* tempPtr = nullptr;
        BinSearchTree<treeType>* insertionPoint = rootPtr;

        while (insertionPoint != nullptr)
        {
            tempPtr = insertionPoint;
            // If the value to be inserted is less than the "current node" AKA the insertion point, go to the left child of the current node
            if (insertVal < insertionPoint->nodeData)
            {
                insertionPoint = insertionPoint->leftChild;
            }
            else
            {
                insertionPoint = insertionPoint->rightChild;
            }
        }

        insertionPoint = new BinSearchTree<treeType>;
        insertionPoint->nodeData = insertVal;
        insertionPoint->rootPtr = rootPtr;

        if (tempPtr == nullptr)
        {
            rootPtr->nodeData = insertVal;
            rootPtr->rootPtr = rootPtr;
        }
        else
        {
            if (insertVal < tempPtr->nodeData)
            {
                tempPtr->leftChild = insertionPoint;
            }
            else
            {
                tempPtr->rightChild = insertionPoint;
            }
        }
    }

    template <class treeType>
    BinSearchTree<treeType>* Parent(BinSearchTree<treeType>* curNode)
    {
        auto parentPtr = curNode->rootPtr;

        if (parentPtr == curNode)
        {
            return nullptr;
        }

        while (parentPtr != nullptr)
        {
            if (curNode->nodeData <= parentPtr->nodeData)
            {
                if (parentPtr->leftChild == curNode)
                {
                    return parentPtr;
                }
                else
                {
                    parentPtr = parentPtr->leftChild;
                }
            }
            if (curNode->nodeData > parentPtr->nodeData)
            {
                if (parentPtr->rightChild == curNode)
                {
                    return parentPtr;
                }
                else
                {
                    parentPtr = parentPtr->rightChild;
                }
            }
        }
    }

    template <class treeType>
    BinSearchTree<treeType>* SearchTree(BinSearchTree<treeType>* rootPtr, treeType searchVal)
    {
        while (rootPtr != nullptr)
        {
            if (searchVal < rootPtr->nodeData)
            {
                if (rootPtr->leftChild != nullptr)
                {
                    if (searchVal == rootPtr->leftChild->nodeData)
                    {
                        return rootPtr->leftChild;
                    }
                    else
                    {
                        rootPtr = rootPtr->leftChild;
                    }
                }
                else
                {
                    rootPtr = nullptr;  
                }
            }
            else if (searchVal > rootPtr->nodeData)
            {
                if (rootPtr->rightChild != nullptr)
                {
                    if (searchVal == rootPtr->rightChild->nodeData)
                    {
                        return rootPtr->rightChild;
                    }
                    else
                    {
                        rootPtr = rootPtr->rightChild;
                    }
                }
                else
                {
                    rootPtr = nullptr;
                }
            }
        }
        return rootPtr;
    }

    template <class treeType>
    BinSearchTree<treeType>* Successor(BinSearchTree<treeType>* curNode)
    {
        if (curNode->rightChild != nullptr)
        {
            return curNode->rightChild;
        }
        
        auto parentPtr = Parent(curNode);

        while (parentPtr != nullptr && curNode == parentPtr->rightChild)
        {
            curNode = parentPtr;
            parentPtr = Parent(curNode);
        }

        return parentPtr;
    }

    template <class treeType>
    void BinSearchTreeInsert(BinSearchTree<treeType>* rootPtr, vector<treeType> insertValsVec)
    {
        for (auto ix : insertValsVec)
        {
            BinSearchTreeInsert(rootPtr, ix);
        }
    }

    template <class treeType>
    void DeleteFromTree(BinSearchTree<treeType>* nodeToDelete)
    {
        if (nodeToDelete->rightChild == nullptr && nodeToDelete->leftChild == nullptr)
        {
            BinSearchTree<treeType>* parentNode = Parent(nodeToDelete);
            if (parentNode->leftChild == nodeToDelete)
            {
                parentNode->leftChild = nullptr;
                delete nodeToDelete;
                return;
            }
            if (parentNode->rightChild == nodeToDelete)
            {
                parentNode->rightChild = nullptr;
                delete nodeToDelete;
                return;
            }
        }

        if (nodeToDelete->rightChild == nullptr && nodeToDelete->leftChild != nullptr)
        {
            BinSearchTree<treeType>* parentNode = Parent(nodeToDelete);
            parentNode->leftChild = nodeToDelete->leftChild;
            delete nodeToDelete;
            return;
        }
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            BinSearchTree<treeType>* parentNode = Parent(nodeToDelete);
            parentNode->rightChild = nodeToDelete->rightChild;
            delete nodeToDelete;
            return;
        }

        if (nodeToDelete->rightChild != nullptr && nodeToDelete->leftChild != nullptr)
        {
            BinSearchTree<treeType>* successorNode = Successor(nodeToDelete);
            nodeToDelete->nodeData = successorNode->nodeData;
            DeleteFromTree(successorNode);
            return;
        }

    }

    /*template <class treeType>
    BinSearchTree<treeType>* BinSearchTreeInsertRecursive(BinSearchTree<treeType>* rootPtr, treeType insertVal)
    {
        if (rootPtr == nullptr)
        {
            rootPtr = new BinSearchTree<treeType>;
            rootPtr->nodeData = insertVal;
            return rootPtr;
        }
        else
        {
            if (insertVal <= rootPtr->nodeData)
            {
                BinSearchTree<treeType>* leftChild = nullptr;
                leftChild = BinSearchTreeInsertRecursive(rootPtr->leftChild, insertVal);
                rootPtr->leftChild = leftChild;
            }
            if (insertVal > rootPtr->nodeData)
            {
                BinSearchTree<treeType>* rightChild = nullptr;
                rightChild = BinSearchTreeInsertRecursive(rootPtr->rightChild, insertVal);
                rootPtr->rightChild = rightChild;
            }
            return rootPtr;
        }   
    }*/
}