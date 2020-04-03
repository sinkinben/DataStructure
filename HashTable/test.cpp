#include <iostream>
#include <utility>
#include <vector>
#include <string>
int main()
{
    using namespace std;
    int *p = nullptr;
    int *&r = p;
    cout << (r == nullptr) << endl;
}