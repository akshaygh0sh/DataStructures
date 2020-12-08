#include "TreeImplementation.h"

template <class treeType>
void DisplayVector(vector<treeType> displayVec)
{
    for (auto ix : displayVec)
    {
        cout << ix << " ";
    }
    cout << endl;
}

int main()
{
    auto levelNum = 1;
    auto childIndex = 1;
    auto rootParentData = -1;

    //auto rootPtr = InitTree<char>(levelNum , childIndex, rootParentData);
    //DumpTree(rootPtr, levelNum, childIndex, rootParentData);

    auto binRootPtr = InitBinTree<char>(levelNum, childIndex, rootParentData);

    cout << "Storing In Order Sequence: " << endl;
    vector<char> vecParamIn;
    DisplayInOrder<char>(binRootPtr, vecParamIn);
    DisplayVector(vecParamIn);

    cout << "Storing Pre Order Sequence: " << endl;
    vector<char> vecParamPre;
    DisplayPreOrder<char>(binRootPtr, vecParamPre);
    DisplayVector(vecParamPre);

    vector <char> testPre{ 'A', 'B', 'C' };
    vector <char> testIn{ 'A', 'B', 'C' };
    auto treePtr = ConstructTree(testPre, testIn);

    
}