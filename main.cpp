#include "header.h"

using namespace std;

// These are the questions in the striver sheet https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/
int maxSubArray(vector<int> &nums)
{
    int cur = nums[0];
    int maxx = nums[0];

    for (int i = 1; i < nums.size(); ++i)
    {
        if (cur < 0)
            cur = 0;
        cur += nums[i];
        maxx = max(maxx, cur);
    }

    return maxx;
}

int maxProfit(vector<int> &prices)
{
    int cur = INT_MAX;
    int profit = 0;
    int maxi = 0;
    int n = prices.size();
    for (int i = 0; i < n; ++i)
    {
        cur = min(cur, prices[i]);
        profit = prices[i] - cur;
        maxi = max(maxi, profit);
    }
    return maxi;
}

void merge(vector<int> &nums1, int n, vector<int> &nums2, int m)
{
    vector<int> nums;
    int i = 0, j = 0;

    while (i < n and j < m)
    {
        if (nums1[i] < nums2[j])
        {
            nums.push_back(nums1[i]);
            i++;
        }
        else
        {
            nums.push_back(nums2[j++]);
        }
    }

    while (i < n)
        nums.push_back(nums1[i++]);
    while (j < m)
        nums.push_back(nums2[j++]);
    i = 0;
    for (auto &it : nums1)
        it = nums[i++];
}

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {}

int longestConsecutive(vector<int> &nums)
{
    unordered_map<int, int> m;
    for (auto it : nums)
        m[it]++;
    int count = 0;
    int longest = 0;
    for (auto it : m)
    {
        if (m.find(it.first - 1) == m.end())
        {
            int ele = it.first;
            count = 0;
            while (m.find(ele) != m.end())
            {
                count++;
                ele++;
            }
            longest = max(longest, count);
        }
    }

    return longest;
}

int lengthOfLongestSubstring(string s)
{
}

int main()
{
    std::cout << "Hello practice questions\n";
    return 0;
}