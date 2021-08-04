#include <bits/stdc++.h>
using namespace std;

/*
    Find shortest path from source node to all node. 
    Time Complexity: O(N + MlogM) // goes through all nodes, adds for each edge at most
one distance to the priority queue.
    Requirement: No negative weight edge.
    Speciality: Uses each edge exactly once to update the distances. 

    Steps in short:
        At each iteration, 
            Selects the node which has not been processed yet and closest to the source. 
            Update distances of nodes using edges going out from this Node.
            This node has been processed :D 

            **Maintains a priority_queue of updated nodes to find the closest unprocessed node.
*/

vector<long long int> dijkstra(int source, vector<vector<pair<int, long long int>>> &adj){
    int n = adj.size() - 1;
    
    vector<long long> distance(n + 1, LLONG_MAX);
    distance[source] = 0;
    
    priority_queue<pair<long long int, int>> q;
    vector<bool> processed(n + 1, false);

    q.push({0, source});
    while (!q.empty()) {
        int a = q.top().second; q.pop();
        if (processed[a]) continue;

        processed[a] = true;
        
        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            
            if (distance[a]+w < distance[b]){
                distance[b] = distance[a] + w;
                q.push({-distance[b],b}); // We are pushing negative distance as priority queue by default stores max at top. 
            }
        }
    }

    return distance;
}

//Implementation source: Competitive Programmer's Handbook - Antti Laaksonen