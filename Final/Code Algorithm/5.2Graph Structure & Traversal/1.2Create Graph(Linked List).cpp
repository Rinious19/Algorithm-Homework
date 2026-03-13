#include <bits/stdc++.h>
using namespace std;

int main(){
    int nVertex, nEdge; //* ตัวแปร จำนวนจุดยอด (Vertex/Node), จำนวนเส้นเชื่อม (Edge)
    cin>>nVertex>>nEdge;
    //* สร้าง Adjacency List คืออาร์เรย์ของ Vector โดยมีขนาดเท่ากับจำนวนจุดยอด (nVertex)
    // เปรียบเสมือนการสร้างกล่องเปล่าๆ nVertex ใบ รอใส่รายชื่อจุดหมายปลายทาง
    vector<vector<int>> graph(nVertex); 
    //! graph[i] จะเป็น Vector ที่เก็บรายชื่อของ Vertex ที่เชื่อมต่อกับ Vertex i
    for(int i = 0; i < nEdge; i++){
        int start, end;
        cin>>start>>end;
        // เมื่อมีเส้นเชื่อมจาก start ไป end (กราฟมีทิศทาง)
        // เราจะเอาค่า end ไปต่อท้าย (push_back) ในลิสต์ของ start
        // เช่น ถ้า 0 ชี้ไป 1 ก็แค่เอาเลข 1 ไปหย่อนใส่กล่องหมายเลข 0
        graph[start].push_back(end);
    }
    //* วนลูปเพื่อแสดงผล Adjacency List ที่สร้างเสร็จแล้วออกมาทางหน้าจอ
    for(int i = 0;i < nVertex; i++){
        cout<<i<<" "; // พิมพ์เลข vertex i
        for(int j = 0; j < graph[i].size(); j++)
            cout<<graph[i][j]<<" "; // พิมพ์เลขจุดหมายปลายทางที่เชื่อมต่อกับ vertex i 
        cout<<endl;
    }
    return 0;
}

/*
* Test Case1
    Input:  5 10
            0 0
            1 3
            2 0
            3 2
            4 1
            0 1
            2 1
            3 4
            0 2
            2 4
    Output: 0 0 1 2 
            1 3 
            2 0 1 4 
            3 2 4 
            4 1
*/