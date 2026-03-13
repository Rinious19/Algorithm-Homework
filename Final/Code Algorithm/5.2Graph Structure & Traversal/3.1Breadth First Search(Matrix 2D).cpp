#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชัน BFS รับกราฟและจุดเริ่มต้น
void BFS(const vector<vector<int>> graph, int startVertex){
    //* สร้าง array เก็บสถานะการเยือน กำหนดค่าเริ่มต้นเป็น false ให้หมด
    vector<bool> visited(graph.size(), false);
    //* เริ่มต้นด้วยการนำจุดแรกเข้าคิว และทำเครื่องหมายว่าไปเยือนแล้ว
    visited[startVertex] = true; //* นำจุดเริ่มต้นเข้าคิว
    //* สร้าง Queue (คิว - เข้าก่อนออกก่อน FIFO)
    queue<int> queue; 
    queue.push(startVertex);
    //@ ทำงานไปเรื่อยๆ จนกว่าคิวจะว่าง (ไม่มีจุดให้เดินต่อแล้ว)
    while(!queue.empty()){
        int currentVertex = queue.front(); //* ดึงตัวที่อยู่หน้าสุดของคิวออกมา
        queue.pop(); //* เอาตัวสแรกออกจากคิว (Dequeue)
        cout<<currentVertex<<" "; // พิมพ์จุดที่กำลังยืนอยู่ออกมา
        for(int i = 0; i < graph.size(); i++){ //* กวาดสายตาดูเพื่อนบ้าน "ทุกตัว" ของจุดปัจจุบัน
            //* ถ้ามีเส้นเชื่อมถึงกัน และจุดนั้นยังไม่เคยไป
            if(graph[currentVertex][i] && !visited[i]){
                queue.push(i); // ให้จับเพื่อนบ้านตัวนั้น "ต่อแถวเข้าคิว" รอไว้เลย
                //! ต้องทำเครื่องหมายว่าไปแล้ว (visited = true) ตั้งแต่ตอนเอาเข้าคิวเลย 
                // เพื่อป้องกันไม่ให้จุดอื่นเอาจุดนี้เข้าคิวซ้ำซ้อน
                visited[i] = true; 
            }
        }
    }
}

int main(){
    int nVertex, nEdge;
    cin>>nVertex>>nEdge;
    //* สร้าง Adjacency Matrix
    vector<vector<int>>graph(nVertex, vector<int>(nVertex, 0));
    for(int i = 0; i < nEdge; i++){
        int start, end;
        cin>>start>>end;
        //* กราฟไม่มีทิศทาง (Undirected)
        graph[start][end] = 1;
        graph[end][start] = 1;
    }
    //* พิมพ์หน้าตา Matrix
    for(int i = 0; i < nVertex; i++){
        for(int j = 0; j < nVertex; j++)
            cout<<graph[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    //* เรียกใช้ BFS โดยเริ่มจากจุดที่ 0
    BFS(graph, 0); 
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
    Output: 0 1 2 3 4 5
*/