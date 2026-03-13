#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii; //* {weight, node}
int INF = 10e7;

void dijkstra(vector<vector<pii>>& graph, int nodeStart, int nodeDest){
    int graphSize = graph.size();
    vector<int> distance(graphSize, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, nodeStart});
    distance[nodeStart] = 0;
    while(!pq.empty()){
        int currentNode = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();
        if(currentDist > distance[currentNode]){
            continue;
        }
        for(auto el : graph[currentNode]){
            int nextNode = el.second; 
            int nextDist = el.first;
            if(nextDist + distance[currentNode] < distance[nextNode]){
                distance[nextNode] = nextDist + distance[currentNode];
                pq.push({distance[nextNode], nextNode});
            }
        }
    }
    cout<<distance[nodeDest];
}

int main(){
    int nPlace, nRoad, nodeStart, nodeDest;
    cin>>nPlace>>nRoad>>nodeStart>>nodeDest;
    vector<vector<pii>> graph(nPlace + 1); //* 1 Index Based
    for(int i=0;i<nRoad;i++){
        int start, end, weight;
        cin>>start>>end>>weight;
        graph[start].push_back({weight, end});
        graph[end].push_back({weight, start});
    }
    dijkstra(graph, nodeStart, nodeDest);
    return 0;
}

/*
* Test Case1
    Input: 4 4 1 4 
           1 2 2
           1 3 5
           2 4 6
           3 4 1
    Output: 6
* Test Case2
    Input: 3 3 1 3
           1 2 3
           2 3 4
           1 3 10
    Output: 7
*/