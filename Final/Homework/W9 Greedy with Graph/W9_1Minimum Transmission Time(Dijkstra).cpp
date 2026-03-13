#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; //* INF (Infinity) แทนระยะทางที่ไปไม่ถึง
typedef pair<int, int> pii; //* ใช้ pair เก็บข้อมูล {เวลาที่ใช้สะสม, หมายเลขเครื่องคอมพิวเตอร์}

//? ฟังก์ชันสำหรับแก้ปัญหา 1 ชุดข้อมูล (1 Test Case)
void solve(){
    int numComputers, numCables, sourceNode, destNode; // numComputers = numNode
    cin>>numComputers>>numCables>>sourceNode>>destNode;
    //@ สร้างกราฟแบบ Adjacency List
    //* graph[u] จะเก็บลิสต์ของ {เวลาที่ใช้, เครื่องปลายทาง v}
    vector<vector<pii>> graph(numComputers);
    for(int i = 0; i < numCables; ++i){ // numCables = numEdge
        int nodeA, nodeB, transmissionTime;
        cin>>nodeA>>nodeB>>transmissionTime;    
        //* Undirected Graph เป็นกราฟสองทิศทาง จึงต้องเชื่อมทั้งไปและกลับ
        graph[nodeA].push_back({transmissionTime, nodeB});
        graph[nodeB].push_back({transmissionTime, nodeA});
    }
    vector<int> minTimes(numComputers, INF); //* เก็บเวลาที่น้อยที่สุดจากต้นทางไปยังโหนดต่างๆ
    //* Priority Queue แบบ Min-Heap (ดึงค่าเวลาที่น้อยที่สุดออกมาก่อน)
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    minTimes[sourceNode] = 0; //* เริ่มต้นที่ sourceNode ใช้เวลา 0
    pq.push({0, sourceNode});
    while(!pq.empty()){
        int currentTime = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();
        //* ทริคเพิ่มเติม: ถ้าเราหาทางมาถึงเครื่องปลายทางที่ต้องการได้แล้ว (และดึงออกจากคิวได้)
        //* แสดงว่าเป็นเวลาที่น้อยที่สุดแน่นอน หยุดการทำงานได้เลย ประหยัดเวลาขึ้นไปอีก!
        if(currentNode == destNode) break;
        //* ถ้าข้อมูลในคิวเป็นข้อมูลเก่าที่ช้ากว่าที่เราเคยอัปเดตไปแล้ว ให้ข้ามทิ้ง
        if(currentTime > minTimes[currentNode]) continue;
        //* สำรวจคอมพิวเตอร์เพื่อนบ้านที่เชื่อมต่ออยู่
        for(auto cable : graph[currentNode]){
            int timeToNext = cable.first;
            int nextNode = cable.second;
            // ถ้าเวลาที่เดินทางผ่าน currentNode รวมกับเวลาของสายสัญญาณนี้น้อยกว่าเวลาเดิมที่เคยบันทึกไว้
            //! minTimes[currentNode] = currentTime เพราะเรามีการตรวจสอบแล้วว่า currentTime เป็นเวลาที่น้อยที่สุดที่เคยเจอสำหรับ currentNode
            if(minTimes[currentNode] + timeToNext < minTimes[nextNode]){
                minTimes[nextNode] = minTimes[currentNode] + timeToNext;
                pq.push({minTimes[nextNode], nextNode});
            }
        }
    }
    //@ สรุปผลลัพธ์: ถ้าเครื่องเป้าหมายยังมีค่าเป็น INF แสดงว่าไม่มีเส้นทางเชื่อมไปถึง (หรือเน็ตหลุด)
    if(minTimes[destNode] == INF)
        cout<<-1<<"\n";
    else
        cout<<minTimes[destNode]<<"\n";
}

int main(){
    int numTestCases;
    if(cin>>numTestCases){
        //* วนลูปแก้ปัญหาตามจำนวน Test Case ที่โจทย์ให้มา
        while(numTestCases--)
            solve();
    }
    return 0;
}

/*
* Test Case1
    Input: 2
           2 1 0 1
           0 1 100
           3 3 2 0
           0 1 100
           0 2 200
           1 2 50
    Output: 100
            150
@ วิเคราะห์และอธิบายโจทย์
- โจทย์กำหนดให้มีคอมพิวเตอร์เชื่อมต่อกันด้วยสายสัญญาณที่มีคุณภาพต่างกัน (ทำให้เวลาส่งข้อมูลไม่เท่ากัน) 
  และต้องการหา "เวลาที่น้อยที่สุด" ในการส่งจากเครื่องต้นทางไปยังเครื่องปลายทาง
- การแปลงโจทย์เป็นกราฟ:
    ● คอมพิวเตอร์ (Computers): เปรียบเสมือน โหนด (Nodes/Vertices)
    ● สายสัญญาณ (Cables): เปรียบเสมือน เส้นเชื่อม (Edges) * เวลาในการส่งข้อมูล: เปรียบเสมือน 
      น้ำหนักของเส้นเชื่อม (Weights)
    ● ลักษณะกราฟ: เป็น Undirected Graph) เพราะสายสัญญาณส่งข้อมูลไป-กลับได้ (แบบสองทิศทาง)
@ ทำไมถึงต้องใช้ Dijkstra + Priority Queue?
- ดูจากข้อจำกัด (Constraints) ของโจทย์:
    ● จำนวนโหนดสูงสุด (n) = 20,000
    ● จำนวนเส้นเชื่อมสูงสุด (m) = 50,000
- ถ้าใช้ Dijkstra แบบธรรมดา (Loop หามิน) ที่มีความซับซ้อน O(V^2) โค้ดจะทำงานช้าเกินไปและอาจติด 
  Time Limit Exceeded (TLE)
- ดังนั้นการใช้ Dijkstra กับ Priority Queue ที่มีความซับซ้อน O(E log V) จึงเป็นทางเลือกที่ถูกต้องที่สุด
@ ทริคพิเศษในโค้ด (Early Exit Optimization)
- สังเกตบรรทัดนี้ในโค้ดครับ:
    if (currentNode == targetNode) break;
- ปกติ Dijkstra จะหาเส้นทางที่สั้นที่สุดไปยัง ทุกจุด ในกราฟ แต่โจทย์ข้อนี้ถามหาเป้าหมายปลายทางแค่จุดเดียว 
- ดังนั้น ทันทีที่เราดึง targetNode ออกมาจากคิวได้สำเร็จ (แปลว่าเรารับรองแล้วว่านี่คือเวลาที่เร็วที่สุด) เราสามารถสั่ง
  break เพื่อหยุดอัลกอริทึมได้เลย ไม่ต้องไปนั่งคำนวณโหนดที่เหลือต่อ
*/