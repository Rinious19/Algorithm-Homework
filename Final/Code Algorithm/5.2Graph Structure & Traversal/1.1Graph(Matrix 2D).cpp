#include <bits/stdc++.h>
using namespace std;

int main(){
    int nVertex, nEdge; //* ตัวแปร จำนวนจุดยอด (Vertex/Node), จำนวนเส้นเชื่อม (Edge)
    cin>>nVertex>>nEdge;
    //* สร้าง Vector 2 มิติ (อาร์เรย์ 2 มิติ) ขนาด nVertex x nVertex เพื่อทำเป็น Adjacency Matrix
    // โดยกำหนดให้ทุกช่องมีค่าเริ่มต้นเป็น 0 (หมายถึงยังไม่มีการเชื่อมต่อกัน)
    vector<vector<int>> graph(nVertex, vector<int>(nVertex, 0));
    for(int i = 0; i < nEdge; i++){ // วนลูปตามจำนวนเส้นเชื่อม (nEdge) เพื่อรับข้อมูลว่ามีเส้นไหนเชื่อมกันบ้าง
        int start, end; 
        cin>>start>>end; // รับค่าจุดเริ่มต้นและจุดสิ้นสุด
        //* Directed Graph: กรณีที่กราฟมีทิศทาง (เส้นเชื่อมมีทิศทางจาก start ไป end เท่านั้น)
        graph[start][end] = 1; //@ กำหนดค่าใน Adjacency Matrix ว่ามีการเชื่อมต่อกัน (1 หมายถึงมีเส้นเชื่อม) 
    }
    //* วนลูปซ้อนกัน 2 ชั้น เพื่อแสดงผล Adjacency Matrix ที่สร้างเสร็จแล้วออกมาทางหน้าจอ
    for(int i = 0; i < nVertex;i++){
        for(int j = 0; j < nVertex; j++)
            cout<<graph[i][j]<<" "; // พิมพ์ค่า 0 หรือ 1 พร้อมเว้นวรรค
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
    Output: 1 1 1 0 0 
            0 0 0 1 0 
            1 1 0 0 1 
            0 0 1 0 1 
            0 1 0 0 0
*/