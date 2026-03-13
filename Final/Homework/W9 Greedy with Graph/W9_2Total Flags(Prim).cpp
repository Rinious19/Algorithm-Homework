#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii; //* สร้างนามแฝง (Alias) ให้ pair<ระยะทาง, หมายเลขสถานที่>

//? ฟังก์ชันหาจำนวนธงทั้งหมดที่ต้องใช้ด้วย Prim's Algorithm
long long calculateTotalFlags(const vector<vector<pii>>& graph) {
    int numPlaces = graph.size() - 1; // จำนวนสถานที่ (รวม index 0 ที่ไม่ได้ใช้)
    //* priority queue แบบ Min-Heap เพื่อหาเส้นทางที่สั้นที่สุดเสมอ
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    //* อาเรย์เช็คว่าสถานที่นี้ถูกเชื่อมเข้าขบวน (MST) หรือยัง (สร้างเผื่อ index 0 ไปด้วย)
    vector<bool> visited(numPlaces + 1, false);
    //* อาเรย์เก็บระยะทางที่สั้นที่สุดที่ค้นพบสำหรับแต่ละสถานที่ (เริ่มต้นเป็น INT_MAX)
    vector<int> distance(numPlaces + 1, INT_MAX);
    long long totalFlags = 0; //* ตัวแปรเก็บจำนวนธงทั้งหมดที่ต้องใช้
    int edgesUsed = 0; //* ตัวนับว่าเราเชื่อมเส้นทางไปกี่เส้นแล้ว
    //* เริ่มต้นที่สถานที่หมายเลข 1 (ระยะทาง 0 เมตร)
    pq.push({0, 1});
    distance[1] = 0; // ระยะทางจากสถานที่เริ่มต้นถึงตัวเองเป็น 0
    while(!pq.empty()) { //@ เริ่ม Prim Algorithm
        //* 1. ดึงเส้นทางที่สั้นที่สุดออกมา
        int currentDistance = pq.top().first;
        int currentPlace = pq.top().second;
        pq.pop();
        //* 2. ถ้าสถานที่นี้อยู่ใน MST แล้ว ให้ข้ามไป (ป้องกันวงวน)
        if(visited[currentPlace]) continue;
        //* 3. ยืนยันการเชื่อมสถานที่นี้เข้า MST
        visited[currentPlace] = true;
        //* 4. คำนวณจำนวนธง (ยกเว้นโหนดเริ่มต้นที่ระยะทางเป็น 0 เราจะไม่นำมาคิด)
        if(currentDistance > 0) {
            totalFlags += (currentDistance - 1);
            edgesUsed++;
        }
        //! Optimization: ถ้าเชื่อมครบทุกสถานที่แล้ว (จำนวนเส้นทาง = จำนวนสถานที่ - 1) ให้หยุดลูปได้เลย ไม่ต้องเสียเวลาทำต่อ
        if(edgesUsed == numPlaces - 1) break;
        //* 5. สำรวจเส้นทางอื่นๆ ที่เชื่อมกับสถานที่นี้
        for (auto nextRoute : graph[currentPlace]) {
            int nextDistance = nextRoute.first;
            int nextPlace = nextRoute.second;
            //* โยนเส้นทางใหม่ๆ ที่ไปยังสถานที่ที่ "ยังไม่เคยไป" ลงคิว
            if(!visited[nextPlace] && nextDistance < distance[nextPlace]) {
                distance[nextPlace] = nextDistance; //* อัปเดตระยะทางที่สั้นที่สุดสำหรับสถานที่นี้
                pq.push({nextDistance, nextPlace});
            }
        }
    }
    return totalFlags;
}

int main() {
    int numPlaces, numPaths;
    cin>>numPlaces>>numPaths;
    //* สร้างกราฟ (บวก 1 เพื่อให้ใช้ index 1 ถึง N ได้ตรงตามโจทย์)
    vector<vector<pii>> graph(numPlaces + 1);
    for (int i = 0; i < numPaths; i++) {
        int startPlace, destPlace, distance;
        cin>>startPlace>>destPlace>>distance;
        //* เป็นเส้นทางที่เดินไป-กลับได้ (Undirected Graph)
        graph[startPlace].push_back({distance, destPlace});
        graph[destPlace].push_back({distance, startPlace});
    }
    //* เรียกใช้ฟังก์ชันและแสดงผลลัพธ์
    long long answer = calculateTotalFlags(graph);
    cout<<answer<<"\n";
    return 0;
}

/*
* Test Case1
    Input: 6 9
           1 2 8
           1 6 6
           2 3 6
           2 4 9
           2 5 7
           2 6 6
           3 4 5
           4 5 5
           5 6 8
    Output: 23
@ วิเคราะห์และอธิบายโจทย์
โจทย์มีเงื่อนไขหลัก 3 ข้อที่ชี้เป้ามาที่ MST ชัดเจนมาก:
1. "เดินทางได้ครบทุกสถาน... จำนวนเส้นทางน้อยที่สุด": นี่คือนิยามของ Spanning Tree (ต้นไม้แผ่ทั่ว) 
    คือเชื่อมทุกจุดโดยไม่เกิดวงวน (Cycle)
2. "ระยะทางรวม... ต้องมีระยะทางน้อยที่สุด": นี่คือนิยามของ Minimum (เล็กที่สุด) พอรวมกับข้อ 1 จึงกลายเป็น
   ปัญหา Minimum Spanning Tree (MST) ทันที
3. จุดหลอก (The Catch) "การปักธง": โจทย์ไม่ได้ถามหาระยะทางรวมตรงๆ แต่ถามหา "จำนวนธง" โดยโจทย์
   บอกว่า เส้นทางยาว l เมตร จะใช้ธง l - 1 ผืน
* สมการง่ายๆ ในการหาคำตอบ: 
- เมื่อเราเลือกเส้นทางที่ดีที่สุดมาเข้าแก๊ง MST ได้แล้ว แทนที่เราจะเอาระยะทางมาบวกกันตรงๆ เราก็แค่เอา 
  (ระยะทางของเส้นนั้น - 1) มาบวกสะสมเข้าไปเรื่อยๆ ก็จะได้คำตอบแล้ว
@ อธิบายจุดสำคัญในโค้ดใช้ 
1. long long สำหรับ totalFlags: อันนี้สำคัญมากครับ! เพราะระยะทาง l มากสุดคือ 100,000 และ
   จำนวนสถานที่ N มากสุดคือ 20,000 ถ้ารวมกันทั้งหมดอาจจะเกินลิมิตของตัวแปร int ธรรมดาได้ 
   (พังตอนส่งเทสเคสท้ายๆ) การใช้ long long จึงปลอดภัยที่สุด
2. edgesUsed เอาไว้ทำ Early Exit: เรารู้ว่า MST ที่สมบูรณ์จะมีเส้นเชื่อมแค่ N - 1 เส้นเสมอ พอเราบวกธงครบ
   N - 1 เส้นปุ๊บ เราสั่ง break ออกจาก while ลูปได้เลยครับ ไม่ต้องไปนั่งเคลียร์คิวที่เหลือให้เสียเวลา
3. 1-based Indexing: โจทย์กำหนดสถานที่เริ่มต้นตั้งแต่ 1 ถึง n โค้ดนี้เลยตั้งขนาด Array ให้เป็น 
   numPlaces + 1 เพื่อที่จะได้ใส่ค่าเข้า Array ตามหมายเลขตรงๆ โดยไม่ต้องเอามาลบ 1 ก่อนให้งง
*/