#include "header.h"

using namespace std;

// These are the questions in the striver sheet https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/

/**
 * Array portion
 */

int maxSubArray(vector<int> &nums) {
    int cur = nums[0];
    int maxx = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        if (cur < 0)
            cur = 0;
        cur += nums[i];
        maxx = max(maxx, cur);
    }

    return maxx;
}

int maxProfit(vector<int> &prices) {
    int cur = INT_MAX;
    int profit = 0;
    int maxi = 0;
    int n = prices.size();
    for (int i = 0; i < n; ++i) {
        cur = min(cur, prices[i]);
        profit = prices[i] - cur;
        maxi = max(maxi, profit);
    }
    return maxi;
}

void merge(vector<int> &nums1, int n, vector<int> &nums2, int m) {
    vector<int> nums;
    int i = 0, j = 0;

    while (i < n and j < m) {
        if (nums1[i] < nums2[j]) {
            nums.push_back(nums1[i]);
            i++;
        } else {
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

int longestConsecutive(vector<int> &nums) {
    unordered_map<int, int> m;
    for (auto it : nums)
        m[it]++;
    int count = 0;
    int longest = 0;
    for (auto it : m) {
        if (m.find(it.first - 1) == m.end()) {
            int ele = it.first;
            count = 0;
            while (m.find(ele) != m.end()) {
                count++;
                ele++;
            }
            longest = max(longest, count);
        }
    }

    return longest;
}

int lengthOfLongestSubstring(string s) {
    int n = s.length();
    set<char> st;
    int left = 0, right = 0;
    int len = 0;
    while (right < n) {
        if (st.find(s[right]) == st.end()) {
            len = max(len, right - left + 1);
            st.insert(s[right]);
            right++;
        } else
            st.erase(s[left++]);
    }

    return len;
}

int uniqueHelp(int i, int j, vector<vector<int>> &dp, int m, int n) {
    if (i < 0 or i >= m or j < 0 or j >= n)
        return 0;
    if (i == 0 and j == 0)
        return 1;
    if (dp[i][j] != -1)
        return dp[i][j];
    int up = uniqueHelp(i - 1, j, dp, m, n);
    int left = uniqueHelp(i, j - 1, dp, m, n);
    return dp[i][j] = left + up;
}
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, -1));

    return uniqueHelp(m - 1, n - 1, dp, m, n);
}

vector<vector<int>> merge(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    // ans.push_back(intervals[0]);
    for (auto it : intervals) {
        if (!ans.empty() and ans.back()[1] >= it[0]) {
            ans.back()[1] = max(ans.back()[1], it[1]);
        } else
            ans.push_back(it);
    }
    return ans;
}

/**
 * Linked list portion
 */

ListNode *reverseList(ListNode *head) {
    ListNode *prev = NULL, *cur = head, *nextNode = NULL;

    while (cur) {
        nextNode = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nextNode;
    }

    return prev;
}

ListNode *middleNode(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast and fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    ListNode *temp = new ListNode(-1);
    ListNode *dummy = temp;
    while (list1 and list2) {
        if (list1->val < list2->val) {
            temp->next = list1;
            list1 = list1->next;
        } else {
            temp->next = list2;
            list2 = list2->next;
        }
        temp = temp->next;
    }

    if (list1) {
        temp->next = list1;
    }

    if (list2) {
        temp->next = list2;
    }
    return dummy->next;
}

ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *start = new ListNode(0);
    start->next = head;

    ListNode *slow = start, *fast = start;

    for (int i = 0; i < n; ++i)
        fast = fast->next;

    while (fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;  // to cut the link
    return start->next;
}

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    int sum = 0, carry = 0;
    ListNode *temp = new ListNode(0);
    ListNode *dummy = temp;
    while (l1 or l2 or carry) {
        sum = 0;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        if (carry)
            sum += carry;

        carry = sum / 10;
        sum %= 10;
        ListNode *node = new ListNode(sum);
        temp->next = node;
        temp = temp->next;
    }

    return dummy->next;
}

bool hasCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;

    while (fast and fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}

ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    bool cycle = false;
    while (fast and fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            cycle = true;
            break;
        }
    }

    if (!cycle)
        return NULL;

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *cur = head;
    int count = 0;
    while (cur) {
        count++;
        cur = cur->next;
    }

    if (count < k) {
        return head;
    }
    cur = head;
    ListNode *prev = NULL, *nextNode = cur->next;

    for (int i = 0; i < k; ++i) {
        nextNode = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nextNode;
    }

    head->next = reverseKGroup(cur, k);
    return prev;
}

// sort the linked list

ListNode *middle(ListNode *head) {
    ListNode *slow = head, *fast = head->next;
    while (fast and fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

ListNode *merge(ListNode *left, ListNode *right) {
    ListNode *dummy = new ListNode(-1);
    ListNode *temp = dummy;
    while (left and right) {
        if (left->val < right->val) {
            dummy->next = left;
            left = left->next;
        } else {
            dummy->next = right;
            right = right->next;
        }

        dummy = dummy->next;
    }

    if (left)
        dummy->next = left;
    if (right)
        dummy->next = right;
    return temp->next;
}

ListNode *sortList(ListNode *head) {
    if (!head or !head->next)
        return head;
    ListNode *left = head;
    ListNode *mid = middle(head);
    ListNode *right = mid->next;
    mid->next = nullptr;

    left = sortList(left);
    right = sortList(right);
    return merge(left, right);
}

Node *copyRandomList(Node *head) {
    map<Node *, Node *> m;
    Node *cur = head;
    while (cur) {
        m[cur] = new Node(cur->val);
        cur = cur->next;
    }

    cur = head;

    while (cur) {
        m[cur]->next = m[cur->next];
        m[cur]->random = m[cur->random];
        cur = cur->next;
    }

    return m[head];
}

Node *copyRandomList(Node *head) {
    map<Node *, Node *> m;
    Node *cur = head;
    while (cur) {
        m[cur] = new Node(cur->val);
        cur = cur->next;
    }

    cur = head;

    while (cur) {
        m[cur]->next = m[cur->next];
        m[cur]->random = m[cur->random];
        cur = cur->next;
    }

    return m[head];
}

Node *copyRandomList(Node *head) {
    map<Node *, Node *> m;
    Node *cur = head;
    while (cur) {
        m[cur] = new Node(cur->val);
        cur = cur->next;
    }

    cur = head;

    while (cur) {
        m[cur]->next = m[cur->next];
        m[cur]->random = m[cur->random];
        cur = cur->next;
    }

    return m[head];
}

// linked list and array

vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 and nums[i] == nums[i - 1]) continue;
        int j = i + 1, k = n - 1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum == 0) {
                ans.push_back({nums[i], nums[j], nums[k]});
                while (j < k and nums[j] == nums[j + 1]) j++;
                while (j < k and nums[k] == nums[k - 1]) k--;
                k--;
                j++;
            } else if (sum > 0)
                k--;
            else
                j++;
        }
    }

    return ans;
}

int trap(vector<int> &height) {
    int n = height.size();
    vector<int> left(n), right(n);
    left[0] = height[0];
    right[n - 1] = height[n - 1];

    for (int i = 1; i < n; ++i) left[i] = max(left[i - 1], height[i]);
    for (int i = n - 2; i >= 0; i--) right[i] = max(right[i + 1], height[i]);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (min(left[i], right[i]) - height[i]);
    }

    return ans;
}

int main() {
    std::cout << "Listed List questions\n";
    return 0;
}