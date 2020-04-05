#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "LinearHashing.hpp"
#include "CuckooHashing.hpp"
using namespace std;

string replaceAll(const string &src, string oldChars, string newChars)
{
    string s(src);
    int pos = s.find(oldChars);
    while (pos != string::npos)
    {
        s.replace(pos, oldChars.length(), newChars);
        pos = s.find(oldChars);
    }
    return s;
}

vector<string> split(const string &s)
{
    vector<string> result;
    stringstream ss(s);
    string buf;
    while (ss >> buf)
        result.push_back(buf);
    return result;
}

void runTest(string filename, Hashing<uint32_t, uint32_t> *hashing)
{
    ifstream file(filename);
    ofstream output(replaceAll(filename, ".in", ".out"));
    string buf = "";
    int i = 0;
    while (getline(file, buf))
    {
        // std::printf("[%d] ", ++i);
        vector<string> v = split(buf);
        if (v[0] == "Set")
        {
            uint32_t key = stol(v[1]);
            uint32_t val = stol(v[2]);
            hashing->set(key, val);
        }
        else if (v[0] == "Get")
        {
            uint32_t key = stol(v[1]);
            auto val = hashing->get(key);
            if (val == nullptr)
                output << "null"
                       << "\n";
            else
                output << val->getVal() << "\n";
        }
        else if (v[0] == "Del")
        {
            uint32_t key = stol(v[1]);
            hashing->remove(key);
        }
        else
        {
            throw "Unknown operation " + v[0];
        }
    }
    file.close();
    output.close();
}
int main()
{
    // LinearHashing<uint32_t, uint32_t> hashing;
    CuckooHashing<uint32_t, uint32_t> hashing;
    runTest("large.in", &hashing);
}