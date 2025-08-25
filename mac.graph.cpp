#include "header.h"
#include "main.h"

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    vector<int> ans;
    int N = graph.size();
    vector<vector<int>> adj(N);
    vector<int> indegree(N, 0);
    for (int i = 0; i < N; ++i) {
        for (auto it : graph[i]) {
            // reverse the graph
            adj[it].push_back(i);
        }
    }
    queue<int> q;
    for (int i = 0; i < N; ++i) {
        for (auto it : adj[i]) indegree[it]++;
    }

    vector<bool> safe(N, false);

    for (int i = 0; i < indegree.size(); ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        safe[node] = true;

        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0) q.push(it);
        }
    }

    for (int i = 0; i < N; ++i)
        if (safe[i]) ans.push_back(i);
    // sort(ans.begin(), ans.end());
    return ans;
}
