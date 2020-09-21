#include "AVLTree.hpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    AVLTree<int> avl;
    while (getline(cin, s))
    {
        if (s == "q")
            break;
        stringstream ss(s);
        int val;
        while (ss >> val)
        {
            // cout << val << endl;
            avl.insert(val);
        }
        // cout << "222";
        avl.draw();
    }
}