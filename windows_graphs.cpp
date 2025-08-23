#include "header.h"

using namespace std;

class BipartiteDFS
{
private:
    bool canBeColored(int node, vector<vector<int>> &graph, vector<int> &color, int col)
    {
        color[node] = col;

        for (auto it : graph[node])
        {
            if (color[it] == -1)
            {
                if (!canBeColored(it, graph, color, !col))
                    return false;
            }
            else if (color[it] == color[node])
                return false;
        }

        return true;
    }
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> color(n, -1); // uncolored

        for (int i = 0; i < n; ++i)
        {
            if (color[i] == -1)
            {
                if (!canBeColored(i, graph, color, 1))
                    return false;
            }
        }

        return true;
    }
};

class BipartiteBFS
{
private:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> colors(n, -1);

        for (int i = 0; i < n; i++)
        {
            if (colors[i] == -1)
            {
                queue<int> q;
                q.push(i);

                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();

                    for (auto it : graph[node])
                    {
                        if (colors[it] == -1)
                        {
                            colors[it] = !colors[node];
                            q.push(it);
                        }
                        else if (colors[it] == colors[node])
                            return false;
                    }
                }
            }
        }

        return true;
    }
};

// rotten oranges
class RottingOranges
{
private:
    int orangesRotting(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        queue<vector<int>> q; // row col time
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 2)
                {
                    q.push({i, j, 0});
                    grid[i][j] = 3;
                }
            }
        }
        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};
        int maxTime = 0;
        while (!q.empty())
        {
            int len = q.size();
            for (int i = 0; i < len; ++i)
            {
                auto it = q.front();
                int row = it[0];
                int col = it[1];
                int curTime = it[2];
                maxTime = max(maxTime, curTime);
                q.pop();

                for (int k = 0; k < 4; ++k)
                {
                    int nR = row + dr[k];
                    int nC = col + dc[k];

                    if (nR >= 0 && nC >= 0 && nR < n && nC < m && grid[nR][nC] == 1)
                    {
                        q.push({nR, nC, curTime + 1});
                        grid[nR][nC] = 3;
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 1)
                {
                    return -1;
                }
            }
        }

        return maxTime;
    }
};

class DetectCycleUndirectedGraph
{
private:
    bool cycleCheckDFS(int node, vector<vector<int>> &adj, vector<int> &visited, int parent)
    {
        visited[node] = 1;
        for (auto it : adj[node])
        {
            if (!visited[it])
            {
                if (cycleCheckDFS(it, adj, visited, node))
                    return true;
            }
            else if (visited[it] && it != parent)
                return true;
        }

        return false;
    }

    bool cycleCheckBFS(int node, vector<vector<int>> &adj, vector<int> &visited)
    {
        visited[node] = 1;
        queue<pair<int, int>> q; // node parent
        q.push({node, -1});

        while (!q.empty())
        {
            auto it = q.front();
            q.pop();

            int node = it.first;
            int parent = it.second;

            for (auto it : adj[node])
            {
                if (!visited[it])
                {
                    visited[it] = 1;
                    q.push({it, node});
                }
                else if (visited[it] && it != parent)
                    return true;
            }
        }

        return false;
    }

    bool isCycle(int V, vector<vector<int>> &edges)
    {
        vector<vector<int>> adj(V);
        for (auto it : edges)
        {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        vector<int> visited(V, 0);
        for (int i = 0; i < V; ++i)
        {
            if (!visited[i])
            {
                if (cycleCheckBFS(i, adj, visited))
                    return true;
            }
        }

        return false;
    }
};

class Graph01Matrix
{
private:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));
        vector<vector<int>> dis(n, vector<int>(m, INT_MAX));
        // queue<vector<int>> q; // row col dist
        queue<pair<pair<int, int>, int>> q;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (mat[i][j] == 0)
                {
                    visited[i][j] = 1;
                    dis[i][j] = 0;
                    q.push({{i, j}, 0});
                }
            }
        }
        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};
        while (!q.empty())
        {
            int len = q.size();
            for (int i = 0; i < len; ++i)
            {
                auto it = q.front();
                q.pop();
                int row = it.first.first;
                int col = it.first.second;
                int dist = it.second;
                dis[row][col] = dist;
                for (int k = 0; k < 4; ++k)
                {
                    int nRow = row + dr[k];
                    int nCol = col + dc[k];

                    if (nRow >= 0 && nCol >= 0 && nRow < n && nCol < m && !visited[nRow][nCol])
                    {
                        visited[nRow][nCol] = 1;
                        q.push({{nRow, nCol}, dist + 1});
                    }
                }
            }
        }

        return dis;
    }
};

int main()
{
    return 0;
}