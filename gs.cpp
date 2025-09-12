#include "header.h"

using namespace std;

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

int firstMissingPositive(vector<int>& nums) {
    unordered_map<int, int> m;
    for (auto it : nums) m[it]++;
    int n = nums.size();
    int num = 1;
    while (m.find(num) != m.end()) num++;
    return num;
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