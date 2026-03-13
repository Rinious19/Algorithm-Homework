#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชัน DFS รับ graph แบบ Reference
// รับค่า 1. กราฟ 2. อาเรย์เก็บสถานะการเยือน (visited) 3. จุดที่กำลังยืนอยู่ (currentVertex)
// const data_type& var คือ Pass by Reference(เร็ว) โดยไม่อนุญาตให้แก้ไขข้อมูลภายในตัวแปรนั้นๆ
void DFS(const vector<vector<int>>& graph, vector<bool>& visited, int currentVertex){
    cout<<currentVertex<<" "; //* 1. พิมพ์ vertex ปัจจุบันที่กำลังยืนอยู่
    //* 2. ทำเครื่องหมายว่า "จุดนี้เคยมาเยือนแล้วนะ" เพื่อจะได้ไม่เดินวนกลับมาที่เดิมซ้ำ (ป้องกัน Infinite Loop)
    visited[currentVertex] = true;
    //* 3. วนลูปเช็กเพื่อนบ้าน "เฉพาะ vertex ที่มีเส้นเชื่อมถึงกัน" (ตรงนี้แหละที่เร็วกว่า Matrix)
    // ใช้ for(int neighbor : graph[currentVertex]) ก็ได้เหมือนกัน
    for(int i = 0; i < graph[currentVertex].size(); i++){ 
        // graph[currentVertex] คือ "ลิสต์ของเพื่อนบ้าน" ที่เชื่อมต่อกับ currentVertex
        // graph[currentVertex][i] คือ "หมายเลข vertex ปลายทาง" ตัวที่ i ที่เชื่อมอยู่
        // ถ้าจุดปลายทางนั้นยังไม่เคยไป (!visited)
        if(!visited[graph[currentVertex][i]])
            //* ให้มุดลึกเดินต่อไปยังจุดปลายทางนั้นทันที
            DFS(graph, visited, graph[currentVertex][i]);
    }
}

int main(){
    int nVertex, nEdge;
    cin>>nVertex>>nEdge;
    //* สร้าง Adjacency List
    vector<vector<int>> graph(nVertex);
    for(int i = 0; i < nEdge; i++){
        int start, end;
        cin>>start>>end;
        //* Undirected Graph: กรณีที่กราฟไม่มีทิศทาง (เส้นเชื่อมไปได้ทั้งสองทาง)
        // สังเกตจากการที่เราอัปเดตตารางให้เป็น 1 ทั้งไปและกลับ!
        graph[start].push_back(end);
        graph[end].push_back(start);
    }
    for(int i = 0; i < nVertex; i++){ // พิมพ์หน้าตาของ Adjacency List ออกมาดู
        cout<<i<<" ";
        for(int j = 0; j < graph[i].size(); j++){
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