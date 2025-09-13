#include "header.h"

using namespace std;

template <typename T>
class BinaryTreeNode {
   public:
    T data;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;

    BinaryTreeNode(T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

int trap(vector<int>& height) {
    int n = height.size();
    vector<int> leftMax(n);
    vector<int> rightMax(n);

    leftMax[0] = height[0];
    rightMax[n - 1] = height[n - 1];

    for (int i = 1; i < n; ++i) {
        leftMax[i] = max(leftMax[i - 1], height[i]);
    }

    for (int i = n - 2; i >= 0; i--) {
        rightMax[i] = max(rightMax[i + 1], height[i]);
    }

    int water = 0;
    for (int i = 0; i < n; ++i) {
        if (leftMax[i] > height[i] && rightMax[i] > height[i])
            water += (min(leftMax[i], rightMax[i]) - height[i]);
    }

    return water;
}

int firstMissingPositiveUsingHash(vector<int>& nums) {
    unordered_map<int, int> m;
    for (auto it : nums) m[it]++;
    int n = nums.size();
    int num = 1;
    while (m.find(num) != m.end()) num++;
    return num;
}

// some error was there
int firstMissingPositive(vector<int>& nums) {
    for (auto& it : nums)
        if (it < 0) it = 0;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int ind = abs(nums[i]) - 1;
        if (ind < 0 or ind >= n) continue;
        if (nums[ind] == 0) nums[ind] = -(n + 1);
        nums[ind] = nums[ind] < 0 ? nums[ind] : -nums[ind];
    }

    for (int i = 1; i < n; ++i) {
        if (nums[i] - 1 > 0) return i;
    }
    return n + 1;
}

int longestValidParentheses(string s) {
    /**
     *
     *  stack<int> st;
        int n = s.size();
        // st.push(s[0]);
        int maxlen = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
                st.push(i);
            else
            {
                if (!st.empty() and s[st.top()] == '(')
                {
                    st.pop();
                    int lastPos = -1;
                    if (!st.empty())
                    {
                        lastPos = st.top();
                    }
                    int curlen = i - lastPos;
                    maxlen = max(maxlen, curlen);
                }
                else
                    st.push(i);
            }
        }
        return maxlen;
     */
    int left = 0;
    int right = 0;

    int maxx = 0;
    int n = s.length();
    // left to right
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(')
            left++;
        else
            right++;
        if (right > left) {
            left = 0;
            right = 0;

        } else if (left == right) {
            maxx = max(maxx, left * 2);
        }
    }

    // right to left
    left = 0, right = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '(')
            left++;
        else
            right++;

        if (left > right) {
            left = 0, right = 0;
        }

        else if (left == right) {
            maxx = max(maxx, left * 2);
        }
    }

    return maxx;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    queue<pair<int, pair<int, int>>> q;  // dist row col
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    vector<vector<int>> visited(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 0) {
                q.push({0, {i, j}});
                dist[i][j] = 0;
                visited[i][j] = 1;
            }
        }
    }

    int drow[4] = {1, -1, 0, 0};
    int dcol[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto values = q.front();
        q.pop();
        int dis = values.first;
        int row = values.second.first;
        int col = values.second.second;
        for (int k = 0; k < 4; ++k) {
            int nRow = row + drow[k];
            int nCol = col + dcol[k];
            dist[row][col] = dis;
            if (nRow >= 0 && nCol >= 0 && nRow <= m - 1 && nCol <= n - 1 && !visited[nRow][nCol]) {
                visited[nRow][nCol] = 1;
                q.push({dis + 1, {nRow, nCol}});
            }
        }
    }
    return dist;
}

/*

   vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    queue<pair<int, pair<int, int>>> q;  // dist row col
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 0) {
                q.push({0, {i, j}});
                dist[i][j] = 0;
            }
        }
    }

    int drow[4] = {1, -1, 0, 0};
    int dcol[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto values = q.front();
        q.pop();
        int dis = values.first;
        int row = values.second.first;
        int col = values.second.second;
        dist[row][col]=dis;
        for (int k = 0; k < 4; ++k) {
            int nRow = row + drow[k];
            int nCol = col + dcol[k];
            if (nRow >= 0 && nCol >= 0 && nRow < m && nCol < n  && mat[nRow][nCol] == 1 && dist[nRow][nCol]==INT_MAX) {
                dist[nRow][nCol] = dis+1;
                q.push({dis + 1, {nRow, nCol}});
            }
        }
    }
    return dist;
}
*/

int maxArea(vector<int>& height) {
    int n = height.size();
    int area = 0;
    int left = 0, right = n - 1;

    while (right > left) {
        area = max(area, min(height[left], height[right]) * (right - left));
        if (height[left] > height[right])
            right--;
        else
            left++;
    }

    return area;
}

long countWays(int ind, int* denominations, int value, vector<vector<long>>& dp) {
    if (ind == 0) {
        if (value % denominations[ind] == 0) return 1;
        return 0;
    }

    if (dp[ind][value] != -1) return dp[ind][value];
    // 2 options
    long take = 0;
    if (denominations[ind] <= value) take = countWays(ind, denominations, value - denominations[ind], dp);
    long notTake = countWays(ind - 1, denominations, value, dp);
    return dp[ind][value] = take + notTake;
}

long countWaysToMakeChange(int* denominations, int n, int value) {
    vector<vector<long>> dp(n, vector<long>(value + 1, -1));
    return countWays(n - 1, denominations, value, dp);
}

bool knows(int a, int b) {
    return true;
}

int findCelebrity(int n) {
    // TLE
    //  vector<int> ind(n, 0);
    //  vector<int> out(n, 0);
    //  for (int i = 0; i < n; ++i) {
    //      for (int j = 0; j < n; ++j) {
    //          if (i != j and knows(i, j)) {
    //              ind[j]++;
    //              out[i]++;
    //          }
    //      }
    //  }

    // for (int i = 0; i < n; ++i) {
    //     if (ind[i] == n - 1 and out[i] == 0) return i;
    // }
    // return -1;

    // using 2 pointer approach
    int left = 0, right = n - 1;

    while (left < right) {
        if (knows(left, right))  // if left knows right then left cannot be celeb
            left++;
        else
            right--;
    }

    for (int i = 0; i < n; ++i) {
        if (i != left && !knows(i, left)) return -1;
    }

    for (int i = 0; i < n; ++i) {
        if (i != left && knows(left, i)) return -1;
    }
    return left;
}

char firstNonRepeatingCharacter(string str) {
    unordered_map<char, int> m;
    for (auto it : str) m[it]++;

    for (int i = 0; i < str.length(); ++i) {
        if (m[str[i]] == 1) return str[i];
    }
    return str[0];
}

/* this is also TLE O(n2)*/
// int jumpsUtil(int ind, int jumps, vector<int>& arr, int n, vector<vector<int>>& dp) {
//     if (ind >= n - 1) return jumps;
//     if (dp[ind][jumps] != -1) return dp[ind][jumps];
//     int mini = INT_MAX;
//     for (int i = 1; i <= arr[ind]; i++) {
//         mini = min(mini, jumpsUtil(ind + i, jumps + 1, arr, n, dp));
//     }
//     return dp[ind][jumps] = mini;
// }
// int minJumps(vector<int>& arr, int n) {
//     vector<vector<int>> dp(n, vector<int>(n, -1));
//     int jumps = jumpsUtil(0, 0, arr, n, dp);
//     return jumps == INT_MAX ? -1 : jumps;
// }

int minJumps(vector<int>& arr, int n) {
    // we will by range .. left and right pointer , left will point to the starting point and
    // right will point to farthest point

    int left = 0, right = 0;
    int jumps = 0;
    while (right < n - 1) {
        int farthest = 0;
        for (int i = left; i <= right; i++) {
            farthest = max(farthest, arr[i] + i);
        }

        left = right + 1;
        right = farthest;
        jumps++;
    }

    return jumps;
}

int openLock(vector<string>& deadends, string target) {
    unordered_set<string> dead;
    for (auto it : deadends) dead.insert(it);
    string start = "0000";
    if (dead.find(start) != dead.end()) return -1;
    queue<string> q;
    q.push(start);
    dead.insert(start);
    int steps = 0;
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            string cur = q.front();
            q.pop();
            if (cur == target) return steps;

            // try out all the states that we can go from the cur
            for (int j = 0; j < 4; ++j) {
                char ch = cur[j];
                // we can either increase the wheel or decrease the wheel
                char inc = ch == '9' ? '0' : ch + 1;
                cur[j] = inc;
                if (dead.find(cur) == dead.end()) {
                    q.push(cur);
                    dead.insert(cur);
                }

                cur[j] = ch;

                char dec = ch == '0' ? '9' : ch - 1;
                cur[j] = dec;
                if (dead.find(cur) == dead.end()) {
                    q.push(cur);
                    dead.insert(cur);
                }

                cur[j] = ch;
            }
        }
        steps++;
    }

    return -1;
}
vector<BinaryTreeNode<int>*> printNodesAtDistanceK(BinaryTreeNode<int>* root, BinaryTreeNode<int>* target, int K) {
    // Write your code here.
}

string FirstNonRepeating(string& s) {
    unordered_map<char, int> m;
    queue<char> q;
    string ans = "";
    for (int i = 0; i < s.length(); ++i) {
        m[s[i]]++;
        q.push(s[i]);
        while (!q.empty() && m[q.front()] > 1) q.pop();

        if (!q.empty())
            ans += q.front();
        else
            ans += "#";
    }

    return ans;
}

vector<int> minSubarray(vector<int> arr, int n, int x) {
    int sum = 0;
    int minLength = INT_MAX;

    int start = 0, end = 0;
    int vecStart = -1, vecEnd = -1;
    while (end < n) {
        sum += arr[end];
        while (sum > x) {
            if ((end - start + 1) < minLength) {
                minLength = end - start + 1;
                vecStart = start;
                vecEnd = end;
            }
            // minLength = min(minLength, end - start + 1);
            sum -= arr[start];
            start++;
        }
        end++;
    }
    // cout<<sum<<" ";cout<<endl;
    // cout<<start<<" "<<end<<"\n";
    vector<int> ans;
    if (vecStart != -1 and vecEnd != -1) {
        for (int i = vecStart; i <= vecEnd; i++) {
            ans.push_back(arr[i]);
        }
    }

    return ans;
}