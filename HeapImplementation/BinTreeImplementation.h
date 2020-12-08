#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>


using namespace std;

namespace BinTree
{
    template <class treeType>
    struct BinTree
    {
        BinTree* lChild = nullptr;
        BinTree* rChild = nullptr;
        treeType nodeData;
    };

    template <class treeType>
    BinTree<treeType>* InitBinTree(int levelNumber, int childIndex, treeType parentData)
    {
        BinTree<treeType>* node = new BinTree<treeType>;
        BinTree<treeType>* leftChild = nullptr;
        BinTree<treeType>* rightChild = nullptr;
        cout << "Enter the data for node at level: " << levelNumber << " child index: " << childIndex << ": " << " with parent " << parentData << ": ";
        cin >> node->nodeData;
        string newNodes;

        cout << "Will there be a left child at node " << node->nodeData << " level: " << levelNumber << " child index: " << childIndex << "? ";
        cin >> newNodes;

        if (newNodes != "n" && newNodes != "N")
        {
            leftChild = InitBinTree<treeType>(levelNumber + 1, childIndex, node->nodeData);
        }

        cout << "Will there be a right child at node " << node->nodeData << " level: " << levelNumber << " child index: " << childIndex << "? ";
        cin >> newNodes;
        if (newNodes != "n" && newNodes != "N")
        {
            rightChild = InitBinTree<treeType>(levelNumber + 1, childIndex, node->nodeData);

        }
        node->lChild = leftChild;
        node->rChild = rightChild;
        return node;
    }


    template <class treeType>
    vector<treeType> DisplayPreOrder(BinTree<treeType>* node, vector<treeType>& preOrderVec)
    {
        if (node != nullptr)
        {
            preOrderVec.push_back(node->nodeData);
            DisplayPreOrder(node->lChild, preOrderVec);
            DisplayPreOrder(node->rChild, preOrderVec);
        }
        return preOrderVec;
    }

    template <class treeType>
    vector<treeType> DisplayInOrder(BinTree<treeType>* node, vector<treeType>& inOrderVec)
    {
        if (node != nullptr)
        {
            DisplayInOrder<treeType>(node->lChild, inOrderVec);
            inOrderVec.push_back(node->nodeData);
            DisplayInOrder<treeType>(node->rChild, inOrderVec);
        }
        return inOrderVec;
    }

    template <class treeType>
    vector <treeType> DisplayPostOrder(BinTree<treeType>* node, vector<treeType>& postOrderVec)
    {
        if (node != nullptr)
        {
            DisplayPostOrder<treeType>(node->lChild, postOrderVec);
            DisplayPostOrder<treeType>(node->rChild, postOrderVec);
            postOrderVec.push_back(node->nodeData);
        }
        return postOrderVec;
    }

    template <class treeType>
    int NumberOfLeafNodes(BinTree<treeType>* node)
    {
        int sum = 0;
        if (node->lChild == nullptr && node->rChild == nullptr)
        {
            sum += 1;
        }
        else
        {
            if (node->lChild != nullptr)
            {
                sum += NumberOfLeafNodes(node->lChild);
            }
            if (node->rChild != nullptr)
            {
                sum += NumberOfLeafNodes(node->rChild);
            }
        }
        return sum;
    }

    // Splits a vector into a left and right subvector given a sentinel value (which will not be included in either of the sub vectors)
    template <class treeType>
    pair<vector<treeType>, vector<treeType>> SubVector(const vector<treeType>& InitialVec, treeType senValue)
    {
        // The first element of the pair will be the left side of what was split by the sentinel value passed as a parameter and the second element of the pair will be the right side.
        pair <vector<treeType>, vector<treeType>> returnPair;
        auto iter = find(InitialVec.begin(), InitialVec.end(), senValue);
        // if iter == InitialVec.end(), then the value senValue was NOT found in InitialVec
        auto subVectorLeft = vector<treeType>(InitialVec.begin(), iter);
        if (iter != InitialVec.end())
        {
            iter++;
            auto subVectorRight = vector<treeType>(iter, InitialVec.end());
            returnPair.first = subVectorLeft;
            returnPair.second = subVectorRight;
        }
        return returnPair;
    }

    template <class treeType>
    bool isBalancedLeaf(BinTree<treeType>* rootPtr, vector<int>& levelVec, int levelCount)
    {
        if (rootPtr->lChild == nullptr && rootPtr->rChild == nullptr)
        {
            levelVec.push_back(levelCount);
            int minLevel = *min_element(levelVec.begin(), levelVec.end());

            for (int ix = 0; ix < levelVec.size(); ix++)
            {
                if (levelVec[ix] - minLevel > 1)
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            bool returnBool;
            if (rootPtr->lChild != nullptr)
            {
                returnBool = isBalancedLeaf(rootPtr->lChild, levelVec, levelCount + 1);
            }
            if (rootPtr->rChild != nullptr)
            {
                returnBool = isBalancedLeaf(rootPtr->rChild, levelVec, levelCount + 1);
            }
            return returnBool;
        }
    }

    template <class treeType>
    bool isBalancedDepth(BinTree<treeType>* rootPtr)
    {
        if (rootPtr->rChild == nullptr && rootPtr->lChild == nullptr)
        {

        }
        else
        {
            int leftDepth = 0;
            int rightDepth = 0;
            vector<int> depthVec;

            if (rootPtr->lChild != nullptr)
            {
                depthVec.clear();
                leftDepth = FindTreeDepth(rootPtr->lChild, 1, depthVec);

            }
            if (rootPtr->rChild != nullptr)
            {
                depthVec.clear();
                rightDepth = FindTreeDepth(rootPtr->rChild, 1, depthVec);
            }

            if (abs(leftDepth - rightDepth) > 1)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

    }

    template <class treeType>
    int FindTreeDepth(BinTree<treeType>* rootPtr, int levelCount, vector<int>& depthVec)
    {
        if (rootPtr->lChild == nullptr && rootPtr->rChild == nullptr)
        {
            depthVec.push_back(levelCount);
        }
        else
        {
            if (rootPtr->lChild != nullptr)
            {
                FindTreeDepth(rootPtr->lChild, levelCount + 1, depthVec);
            }
            if (rootPtr->rChild != nullptr)
            {
                FindTreeDepth(rootPtr->rChild, levelCount + 1, depthVec);
            }
        }
        return *max_element(depthVec.begin(), depthVec.end());
    }

    template <class treeType>
    int GetSizeBinTree(BinTree<treeType>* rootPtr, int& nodeCount)
    {
        if (rootPtr->lChild == nullptr && rootPtr->rChild == nullptr)
        {
        }
        else
        {
            if (rootPtr->lChild != nullptr)
            {
                nodeCount = nodeCount + 1;
                GetSizeBinTree(rootPtr->lChild, nodeCount);
            }
            if (rootPtr->rChild != nullptr)
            {
                nodeCount = nodeCount + 1;
                GetSizeBinTree(rootPtr->rChild, nodeCount);
            }
        }
        return nodeCount;
    }

    template <class treeType>
    void TreeToVector(BinTree<treeType>* rootPtr, int elementNum, vector<treeType>& TreeVector)
    {
        TreeVector[elementNum] = rootPtr->nodeData;
        if (rootPtr->lChild == nullptr && rootPtr->rChild == nullptr)
        {
        }
        else
        {
            if (rootPtr->lChild != nullptr)
            {
                TreeToVector<treeType>(rootPtr->lChild, elementNum * 2, TreeVector);
            }
            if (rootPtr->rChild != nullptr)
            {
                TreeToVector<treeType>(rootPtr->rChild, elementNum * 2 + 1, TreeVector);
            }
        }
    }

    template <class treeType>
    BinTree<treeType>* ConstructTree(vector<treeType> preOrderVec, vector<treeType> inOrderVec)
    {
        // Keep resizing until the size of the inOrderVector is 1
        if (inOrderVec.size() > 1)
        {
            // Splits the inOrder vector using the value at preOrderVec[0] (which should always be the "parent/root") and stores the left subtree in inOrderPair.first and the right subtree in inOrderPair.second
            pair <vector<treeType>, vector<treeType>> inOrderPair = SubVector(inOrderVec, preOrderVec[0]);

            // Creates a copy of the preOrderVector without the first element (since it has already been used to split the inOrderVec) -> preparing for the next recursive loop
            vector<treeType> tempPreOrderVec = preOrderVec;
            tempPreOrderVec.erase(tempPreOrderVec.begin());

            BinTree<treeType>* leftChild = nullptr;
            BinTree<treeType>* rightChild = nullptr;

            // If the inOrderPair.first (left subtree) is empty then proceed with the right subtree
            if (inOrderPair.first.empty() != true)
            {
                // If left is not empty then proceed with processing the left subtree
                leftChild = ConstructTree<treeType>(tempPreOrderVec, inOrderPair.first);
            }
            // Proceed with processing the right subtree if the left subtree (inOrderPair.first) is empty
            if (inOrderPair.second.empty() != true)
            {
                // Resizes the tempPreOrderVec so that only the relevant preOrder pattern for the right subtree is passed to the function when processing the rightChild
                for (int ix = 0; ix < inOrderPair.first.size(); ix++)
                {
                    tempPreOrderVec.erase(tempPreOrderVec.begin());
                }
                rightChild = ConstructTree<treeType>(tempPreOrderVec, inOrderPair.second);
            }
            BinTree<treeType>* rootPtr = new BinTree<treeType>;
            // The root will always be at the beginning of the preOrderVector
            rootPtr->nodeData = preOrderVec[0];
            // Sets the root's leftChild if there is no leftChild, the value of leftChild will be null
            rootPtr->lChild = leftChild;
            // Sets the root's rightChild if there is no rightChild, the value of rightChild will be null
            rootPtr->rChild = rightChild;
            return rootPtr;
        }
        else
        {
            // Once the inOrderVec size is 1, the child is set to the value of the element in the inOrderVec

            // This if statement is for safety, since for any preOrder and inOrder representations of legal binary trees passed to this function, the preOrderVec and inOrderVec's first elements will equal each other once the program has reached this point

            // A node with the single elements data value is then created and returned, this node will act as the "child node"
            if (preOrderVec[0] == inOrderVec[0])
            {
                BinTree<treeType>* childPtr = new BinTree<treeType>;
                childPtr->nodeData = inOrderVec[0];
                return childPtr;
            }
            else
            {
                cout << "Error. Exiting Program";
                exit(-1);
            }
        }
    }
}




