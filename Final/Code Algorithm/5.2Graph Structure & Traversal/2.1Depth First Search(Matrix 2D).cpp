#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชัน DFS แบบ Recursive (เรียกใช้ตัวเองซ้ำเพื่อขุดลึกลงไปเรื่อยๆ)
// รับค่า 1. กราฟ 2. อาเรย์เก็บสถานะการเยือน (visited) 3. จุดที่กำลังยืนอยู่ (currentVertex)
// const data_type& var คือ Pass by Reference(เร็ว) โดยไม่อนุญาตให้แก้ไขข้อมูลภายในตัวแปรนั้นๆ
void DFS(const vector<vector<int>>& graph, vector<bool>& visited, int currentVertex){
    cout<<currentVertex<<" "; //* 1. พิมพ์จุดยอดปัจจุบันที่เดินทางมาถึง
    //* 2. ทำเครื่องหมายว่า "จุดนี้เคยมาเยือนแล้วนะ" เพื่อจะได้ไม่เดินวนกลับมาที่เดิมซ้ำ (ป้องกัน Infinite Loop)
    visited[currentVertex] = true;
    //* 3. ลองมองหา vertex อื่นๆ ทั้งหมดว่ามีทางเดินจาก currentVertex ไป vertex อื่นๆไหม 
    for(int i = 0; i < graph.size(); i++){
        // เงื่อนไข: ถ้า "มีเส้นเชื่อมจาก currentVertex ไป vertex i" (graph[currentVertex][i] == 1) 
        // และ "vertex i นั้นเรายังไม่เคยไป" (!visited[i])
        if(graph[currentVertex][i] && !visited[i])
            DFS(graph, visited, i); //* 4. ให้เดินลึกลงไปยัง vertex i ต่อไปเลย (recursive call)
    }
}

int main(){
    int nVertex, nEdge;
    cin>>nVertex>>nEdge;
    //* สร้าง Adjacency Matrix
    vector<vector<int>> graph(nVertex, vector<int>(nVertex,0));
    for(int i = 0; i < nEdge; i++){
        int start, end;
        cin>>start>>end;
        //* Undirected Graph: กรณีที่กราฟไม่มีทิศทาง (เส้นเชื่อมไปได้ทั้งสองทาง)
        // สังเกตจากการที่เราอัปเดตตารางให้เป็น 1 ทั้งไปและกลับ!
        graph[start][end] = 1;
        graph[end][start] = 1;
    }
    for(int i = 0; i < nVertex; i++){ // พิมพ์หน้าตาของ Adjacency Matrix ออกมาดู
        for(int j = 0; j < nVertex; j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
    //* สร้าง Vector เพื่อคอยจดจำว่าจุดไหนเคยไปมาแล้วบ้าง (เริ่มต้นด้วย false คือยังไม่เคยไปเลยสักจุด)
    vector<bool> visited(nVertex, false);
    cout<<endl;
    //* สั่งให้เริ่มเดินค้นหาแบบ DFS โดยเริ่มจาก Vertex หมายเลข 0
    DFS(graph, visited, 0);
    return 0;
}

/*
* Test Case1
    Input: 6 6
           0 1
           0 2
           1 3
           2 3
           3 4
           4 5
    Output: 0 1 3 2 4 5
*/