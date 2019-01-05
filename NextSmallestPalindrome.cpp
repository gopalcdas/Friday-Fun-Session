#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

const int NINE = 9;

void PrintVector(vector<int> const output)
{
    for (int i = 0; i < output.size(); i++)
        cout << output[i] << " ";

    cout << endl;
}

vector<int> CopyVector(vector<int> const input)
{
    vector<int> output;
    for (int i = 0; i < input.size(); i++)
        output.push_back(input[i]);
	
    return output;
}

bool All9s(vector<int> const output)
{
    for (int i = 0; i < output.size(); i++)
        if (output[i] != NINE)
            return false;

    return true;
}

void DealWithAll9Input(vector<int> const output)
{
    cout << "1 ";
    for (int i = 0; i < output.size()-1; i++)
        cout << "0 ";
    cout << "1 " << endl;
}

bool ExistingPalindrome(vector<int> const output)
{
    for (int i = 0; i < output.size() / 2; i++)
    if (output[i] != output[output.size() - 1 - i])
        return false;

    return true;
}

void GetNextPalindrome(vector<int> &output)
{
    int mid = output.size()/2;
    if (output.size() % 2)
    {
        if (output[output.size() / 2] < NINE)
        {
            output[output.size() / 2]++;
            return;
        }
    else
        output[output.size() / 2] = 0;

    mid--;
    }

    for (int i = mid; i < output.size(); i++)
    {
        if (output[i] < NINE)
        {
            output[i] = output[output.size() -1 - i] = output[i] + 1;
            break;
        }
        else
            output[i] = output[output.size() - 1 - i] = 0;
    }
}

bool RightSideSmaller(vector<int> const output)
{
    int mid = output.size() / 2;
    mid--;

    for (int i = mid; i >= 0; i--)
    {
        if (output[i] > output[output.size() - 1 - i])
            return true;

        if (output[i] < output[output.size() - 1 - i])
            return false;
    }
		
    return false;
}

void GetNextPalindromeRightSideSmaller(vector<int> &output)
{
    int mid = output.size() / 2;
    if (output.size() % 2)
        mid--;

    for (int i = mid; i < output.size(); i++)
        if(output[output.size() - 1 - i] != output[i])
            output[i] = output[output.size() - 1 - i];
}

void GetNextPalindromeRightSideBigger(vector<int> &output)
{
    int mid = output.size() / 2;
    if (output.size() % 2)
    {
        if (output[output.size() / 2] < NINE)
            output[output.size() / 2]++;
        else
            output[output.size() / 2] = 0;

        mid--;
    }

    int i;
    for (i = mid; i >= 0; i--)
    {
        if (output[i] < output[output.size() - 1 - i])
        {
            output[i] = output[output.size() - 1 - i];
            break;
        }

        if (output[i] == output[output.size() - 1 - i])
        {
            if(output[i] == NINE)
                output[output.size() - 1 - i] = output[i] = 0;
            else
            {
                output[output.size() - 1 - i] = output[i] = output[i] + 1;
                break;
            }
        }
    }

    for (int j = i-1; j >=0; j--)
        output[output.size() - 1 - j] = output[j];
}

void NextPalindrome(vector<int> input)
{
    if (All9s(input))
    {
        DealWithAll9Input(input);
        return;
    }

    vector<int> output = CopyVector(input);
    if (ExistingPalindrome(output))
        GetNextPalindrome(output);
    else if(RightSideSmaller(output))
        GetNextPalindromeRightSideSmaller(output);
    else
        GetNextPalindromeRightSideBigger(output);

    PrintVector(output);
}

int main()
{
    static const int arr1[] = { 9, 9 };
    vector<int> input1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
    PrintVector(input1);
    NextPalindrome(input1);

    static const int arr2[] = { 1 };
    vector<int> input2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    PrintVector(input2);
    NextPalindrome(input2);

    static const int arr3[] = { 1, 4, 5, 8, 7, 6, 7, 8, 3, 2, 2 };
    vector<int> input3(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
    PrintVector(input3);
    NextPalindrome(input3);

    static const int arr4[] = { 1, 2, 5, 3, 2, 2 };
    vector<int> input4(arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]));
    PrintVector(input4);
    NextPalindrome(input4);

    static const int arr5[] = { 1, 2, 5, 3, 2, 2 };
    vector<int> input5(arr5, arr5 + sizeof(arr5) / sizeof(arr5[0]));
    PrintVector(input5);
    NextPalindrome(input5);

    static const int arr6[] = { 9, 4, 1, 8, 7, 9, 7, 8, 3, 2, 2 };
    vector<int> input6(arr6, arr6 + sizeof(arr6) / sizeof(arr6[0]));
    PrintVector(input6);
    NextPalindrome(input6);

    static const int arr7[] = { 7, 8, 3, 3, 2, 2 };
    vector<int> input7(arr7, arr7 + sizeof(arr7) / sizeof(arr7[0]));
    PrintVector(input7);
    NextPalindrome(input7);

    static const int arr9[] = { 1, 2, 5, 3, 4 };
    vector<int> input9(arr9, arr9 + sizeof(arr9) / sizeof(arr9[0]));
    PrintVector(input9);
    NextPalindrome(input9);

    getchar();
}
