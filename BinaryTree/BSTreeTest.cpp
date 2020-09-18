#include "BSTree.hpp"
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
    assert(bstree.getRoot() == nullptr);
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
// test generic and expandability
void test3()
{
    class Node
    {
    private:
        int key, val;

    public:
        Node() {}
        Node(int k, int v) : key(k), val(v) {}
        // These operators are necessary.
        bool operator<(const Node &n) const { return key < n.key; }
        bool operator>(const Node &n) const { return key > n.key; }
        bool operator==(const Node &n) const { return key == n.key; }
        bool operator!=(const Node &n) const { return key != n.key; }
        Node &operator=(const Node &n)
        {
            key = n.key, val = n.val;
            return *this;
        }
    };
    BSTree<Node> tree;
    srand(time(nullptr));
    vector<int> pool;
    int n = 10000;
    while (n--)
        pool.push_back(rand());
    for (int x : pool)
        tree.insert(Node(x, x));
    tree.selfCheck();
    for (int x : pool)
    {
        tree.remove(Node(x, x));
        tree.selfCheck();
    }
    cout << "Pass Test Case 3: Generic Expandability." << endl;
}
int main()
{
    vector<function<void()>> tests = {test1, test2, test3};
    for (auto f : tests)
        f();
}