#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชัน BFS รับกราฟแบบ Adjacency List (Pass by Reference เพื่อความรวดเร็ว)
void BFS(const vector<vector<int>>& graph, int startVertex){
    //* สร้าง array เก็บสถานะการเยือน กำหนดเป็น false ทั้งหมด
    vector<bool> visited(graph.size(), false);
    visited[startVertex] = true; //* ทำเครื่องหมายว่าเยือนจุดเริ่มต้นแล้ว
    queue<int> q; //* คิวสำหรับจัดลำดับการค้นหาแบบแนวกว้าง
    q.push(startVertex); //* นำจุดเริ่มต้นเข้าคิว
    //@ ทำงานไปเรื่อยๆ จนกว่าคิวจะว่าง (ไม่มีจุดให้เดินต่อแล้ว)
    while(!q.empty()){
        int currentVertex = q.front(); //* ดึงตัวหน้าสุดของคิวมาประมวลผล
        q.pop(); //* เอาตัวสแรกออกจากคิว (Dequeue)
        cout<<currentVertex<<" "; // พิมพ์จุดที่กำลังยืนอยู่
        //* ลูปเช็กเฉพาะ "เพื่อนบ้านที่มีเส้นเชื่อมจริงๆ" เท่านั้น
        //* graph[currentVertex].size() คือจำนวนเพื่อนบ้านทั้งหมดของจุดนี้
        // for(int neighbor : graph[currentVertex]) ก็ได้เหมือนกัน
        for(int i = 0; i < graph[currentVertex].size(); i++){
            // graph[currentVertex][i] คือ "หมายเลขของจุดยอดที่เป็นเพื่อนบ้าน"
            // เช็กว่าเพื่อนบ้านคนนี้ เราเคยไปเยือนหรือยัง?
            if(!visited[graph[currentVertex][i]]){
                // ถ้ายังไม่เคยไป ให้จับเพื่อนบ้านคนนี้เข้าคิวรอไว้เลย
                q.push(graph[currentVertex][i]);
                //! สำคัญมาก: ต้อง Mark ว่าไปแล้วทันทีที่เอาเข้าคิว
                // เพื่อป้องกันไม่ให้จุดอื่นเอาเพื่อนบ้านคนนี้เข้าคิวซ้ำอีกรอบ
                visited[graph[currentVertex][i]] = true; 
            }
        }
    }
}

int main(){
    int nVertex, nEdge;
    cin>>nVertex>>nEdge;
    //* สร้าง Adjacency List รอรับข้อมูล
    vector<vector<int>> graph(nVertex);
    for(int i = 0; i < nEdge; i++){
        int start, end;
        cin>>start>>end;
        //* เก็บข้อมูลเส้นเชื่อมแบบกราฟไม่มีทิศทาง (ไป-กลับ)
        graph[start].push_back(end);
        graph[end].push_back(start);
    }
    //* แสดงผลหน้าตาของ Adjacency List
    for(int i = 0; i < nVertex; i++){
        cout<<i<<" ";
        for(int j = 0; j < graph[i].size(); j++){
            cout<<graph[i][j]<<" ";
        }
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