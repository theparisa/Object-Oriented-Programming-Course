#include <vector>
#include <string>
#include <iostream>
using namespace std;

bool rec_fun(vector<char> vec, int start_index, int end_index)
{
    int size_vec = vec.size();

    for (int i = end_index; i >= 0; i--)
    {
        if (('a' <= vec[i] && vec[i] <= 'z') || ('A' <= vec[i] && vec[i] <= 'Z'))
        {
            end_index = i;
            // cout<<"end = "<<end_index<<endl;
            break;
        }
    }
    for (int i = start_index; i < size_vec; i++)
    {
        if (('a' <= vec[i] && vec[i] <= 'z') || ('A' <= vec[i] && vec[i] <= 'Z'))
        {
            start_index = i;
            // cout<<"start = "<<start_index<<endl;
            break;
        }
    }
    // if(end_index == start_index){return true;}
    char start_char = vec[start_index];
    char end_char = vec[end_index];

    if (start_char == end_char || toupper(start_char) == end_char || start_char == toupper(end_char))
    {
        if (end_index - start_index == 1)
        {
            return true;
        }
        if (start_index >= end_index)
        {
            return true;
        }
        return rec_fun(vec, start_index + 1, end_index - 1);
    }
    return false;
}
int main()
{
    string str;

    while (getline(cin, str))
    {
        vector<char> vec(str.begin(), str.end());
        int size_vec = vec.size();
        int start_index = 0;
        int end_index = size_vec - 1;
        bool result = rec_fun(vec, start_index, end_index);
        if (result)
        {
            cout << "true" << endl;
        }
        else
        {
            cout << "false" << endl;
        }
    }

    return 0;
}