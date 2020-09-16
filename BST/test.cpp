#include "BST.hpp"
#include <ctime>
#include <functional>
using namespace std;
auto vprint = [](vector<int> &v) {for(int x:v)cout<<x<<' '; cout<<endl; };
// test insert and remove
void test1()
{

    BSTree<int> bstree;
    int n = 10000;
    srand(time(nullptr));
    vector<int> pool;
    for (int i = 0; i < n; i++)
        pool.push_back(rand());
    for (auto t : pool)
    {
        bstree.insert(t);
        bstree.selfCheck();
        // cout << "Insert " << t << " ." << endl;
        // bstree.draw();
        // getchar();
    }
    // cout << "Insertion done." << endl;
    for (auto t : pool)
    {
        bstree.remove(t);
        bstree.selfCheck();
    }
    cout << "Pass Test Case 1: Insertion and removal." << endl;
}
// test precedessor and successor
void test2()
{
    BSTree<int> tree;
    srand(time(nullptr));
    int n = 20000;
    vector<int> v;
    while (n--)
        v.push_back(rand());

    for (int x : v)
        tree.insert(x);
    tree.selfCheck();
    // tree.draw();
    for (int x : v)
    {
        auto p1 = tree.predecessor(x), p2 = tree.successor(x);
        if (p1 != nullptr)
            assert(p1->val <= x);
        if (p2 != nullptr)
            assert(x <= p2->val);
    }
    cout << "Pass Test Case 2: Precedessor and successor." << endl;
}
int main()
{
    vector<function<void()>> tests = {test1, test2};
    for (auto f : tests)
        f();
}