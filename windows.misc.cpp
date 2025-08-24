#include "header.h"

using namespace std;

int longestSubarray(vector<int> &nums)
{
    int start = 0;
    int zero = 1;
    int longest = 0;
    for (int ind = 0; ind < nums.size(); ind++)
    {
        zero -= (nums[ind] == 0);

        while (zero < 0)
        {
            zero += (nums[start] == 0);
            start++;
        }

        longest = max(longest, ind - start);
    }

    return longest;
}

int main()
{
    return 0;
}