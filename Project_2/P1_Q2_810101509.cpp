#include <iostream>
#include <vector>
using namespace std;

bool operator_finder(const vector<int> &numbers, int target, vector<char> &operators, int Index, const int fixed_target)
{
    if (Index >= numbers.size())
    {
        return target == 0;
    }
    operators.push_back('+');
    if (operator_finder(numbers, target - numbers[Index], operators, Index + 1, fixed_target))
    {
        return true;
    }
    operators.pop_back();
    if (Index > 0)
    {
        operators.push_back('-');
        if (operator_finder(numbers, target + numbers[Index], operators, Index + 1, fixed_target))
        {
            return true;
        }
        operators.pop_back();

        operators.push_back('*');
        int new_target = fixed_target - (numbers[Index] * (fixed_target - target));
        if (operator_finder(numbers, new_target, operators, Index + 1, fixed_target))
        {
            return true;
        }
        operators.pop_back();
    }
    return false;
}
int main()
{
    int n;
    cin >> n;

    int num;
    vector<int> numbers;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> num;
        numbers.push_back(num);
    }
    int target;
    cin >> target;

    vector<char> operators;

    bool result = operator_finder(numbers, target, operators, 0, target);
    if (result)
    {
        int i = 0, j = 1;
        while (i < numbers.size() || j < operators.size())
        {
            if (i < numbers.size())
            {
                cout << numbers[i];
                i++;
            }
            if (j < operators.size())
            {
                cout << operators[j];
                j++;
            }
        }
        cout << '=' << target;
    }
    else
    {
        cout << "No Solution!" << endl;
    }

    return 0;
}