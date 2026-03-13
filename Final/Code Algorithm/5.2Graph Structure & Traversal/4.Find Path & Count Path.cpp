#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชัน findAllPath ด้วย DFS เพื่อหาเส้นทางทั้งหมดจาก currentVertex ไปยัง targetVertex
//* รับตัวแปร path เข้ามาเพื่อจดจำเส้นทางที่เดินผ่านมาด้วย
//* targetVertex คือจุดหมายปลายทางที่เราต้องการไปให้ถึง
void findAllPath(const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& path, int currentVertex, int targetVertex){
    //@ 1. นำจุดที่กำลังยืนอยู่ เข้าไปเก็บใน "ประวัติการเดินทาง (path)"
    visited[currentVertex] = true; //* ทำเครื่องหมายว่าในเส้นทางนี้ เราเหยียบจุดนี้แล้วนะ
    path.push_back(currentVertex); // จดลงสมุดบันทึกเส้นทาง
    //@ 2. เช็กว่า "ถึงเป้าหมายหรือยัง?"
    if(currentVertex == targetVertex){
        //* ถ้าถึงเป้าหมายแล้ว ให้พิมพ์เส้นทางที่บันทึกไว้ออกมาให้หมด
        for(int i = 0; i < path.size(); i++) 
            cout<<path[i]<<" ";
        cout<<"- "<<path.size() - 1<<" "<<endl; // พิมพ์จำนวนเส้นเชื่อม (ความยาวเส้นทาง = จำนวนจุดในเส้นทาง - 1)
    }
    else{
        //@ 3. ถ้ายังไม่ถึงเป้าหมาย ให้มองหาทางไปต่อ
        for(int i = 0; i < graph.size(); i++){
            //* ถ้ามีเส้นทางเชื่อมไปจุด i และจุด i นั้นเรายังไม่ได้เดินผ่านในเส้นทางนี้
            if(graph[currentVertex][i] && !visited[i])
                //* มุดลึกไปจุด i ต่อไป
                findAllPath(graph, visited, path, i, targetVertex);
        }
    }
    //@ 4. Backtracking เมื่อสำรวจจากจุดนี้จนสุดทางแล้ว (ไม่ว่าจะเจอเป้าหมายหรือไม่เจอ)
    //* ก่อนจะ "ถอยหลัง" กลับไปหาทางแยกก่อนหน้า เราต้อง "ลบรอยเท้า" ของตัวเองออก
    visited[currentVertex] = false; //* ปลดล็อกจุดนี้ เผื่อว่าเส้นทางอื่นในอนาคตจะเดินมาใช้จุดนี้ได้
    path.pop_back(); //* ลบจุดนี้ออกจากประวัติการเดินทางของรอบนี้
}

int main(){
    int nVertex, nEdge;
    cin>>nVertex>>nEdge;
    //* สร้างกราฟแบบ Adjacency Matrix
    vector<vector<int>> graph(nVertex, vector<int>(nVertex, 0));
    for(int i = 0; i < nEdge; i++){
        int start, end;
        cin>>start>>end;
        //* กราฟไม่มีทิศทาง (Undirected)
        graph[start][end] = 1;
        graph[end][start] = 1; 
    }
    //* พิมพ์ Matrix ออกมาดู
    for(int i=0;i<nVertex;i++){
        cout<<i<<" ";
        for(int j=0;j<nVertex;j++)
            cout<<graph[i][j]<<" ";
        cout<<endl;
    }
    vector<bool> visited(nVertex, false); // สถานะการเยี่ยมชมสำหรับแต่ละเส้นทาง
    cout<<endl;
    vector<int> path; // ตัวแปรเก็บประวัติการเดินทาง
    int targetVertex = 2;   // กำหนดจุดหมายปลายทางคือโหนด 2
    int startVertex = 0;    // กำหนดจุดเริ่มต้นคือโหนด 0
    //* เริ่มค้นหาเส้นทางทั้งหมดจาก 0 ไป 2
    findAllPath(graph, visited, path, startVertex, targetVertex);
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
    Output: 0 1 3 2 - 3 
            0 2 - 1
@ ทำไมถึงต้องมี Backtracking (visited[startVertex] = false;) ?
- ใน Test Case ผลลัพธ์ออกมา 2 เส้นทาง:
    ● 0 1 3 2 - 3 (ระยะทาง 3 ก้าว)
    ● 0 2 - 1 (ระยะทาง 1 ก้าว)
- ถ้าคอมพิวเตอร์เลือกเดินเส้นทางแรกก่อนคือมุดไปทาง 0 -> 1 -> 3 -> 2 เมื่อเจอโหนด 2 (เป้าหมาย) แล้ว 
  ถ้าเรา ไม่ปลดล็อก visited สถานะของโหนด 0, 1, 2, 3 จะเป็น true ค้างไว้ตลอดกาล
- เมื่อคอมพิวเตอร์จะลองสำรวจเส้นทางที่สองจากโหนด 0 ไป 2 โดยตรง มันจะเห็นว่า visited[2] เป็น true 
  ไปแล้ว มันเลยคิดว่า "อ้าว จุดนี้เดินผ่านไปแล้วนี่ งั้นไม่ไปดีกว่า" ทำให้เราอดได้เส้นทางที่สอง!
- การทำ Backtracking จึงเป็นการบอกว่า "โอเค จบการสำรวจเส้นทางฝั่งนี้แล้ว ขอเคลียร์สถานะตัวเองทิ้งนะ 
  เพื่อให้การค้นหาในเส้นทางอื่นๆ สามารถเริ่มใหม่ได้อย่างอิสระ"
*/