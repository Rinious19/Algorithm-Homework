#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
typedef pair<int, int> pii; //* ใช้คู่ {น้ำหนักเส้นเชื่อม, หมายเลขโหนด}

void primMST(const vector<vector<pii>>& graph, int startNode){
    int graphSize = graph.size();
    //* distance: เก็บ "น้ำหนักเส้นเชื่อมที่ถูกที่สุด" ที่สามารถพาโหนดนี้มาเชื่อมกับ MST ได้ (ไม่ใช่ระยะทางสะสมแบบ Dijkstra)
    vector<int> distance(graphSize, INF);
    //* parent: เก็บว่าโหนดนี้เชื่อมต่อกับ MST ผ่านโหนดไหน (ไว้ใช้ปริ้นท์เส้นทางตอนจบ)
    vector<int> parent(graphSize, -1);
    //* inMST: เช็คว่าโหนดนี้ถูกรวมเข้าไปในต้นไม้แผ่ทั่ว (MST) หรือยัง
    vector<bool> inMST(graphSize, false);
    //* Min-Heap เก็บข้อมูลแบบ {น้ำหนัก, โหนด}
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, startNode});
    distance[startNode] = 0;
    while(!pq.empty()){ //@ ขั้นตอนหลักของ Prim's Algorithm
        //* 1. ดึงโหนดที่ใช้ "ราคา (น้ำหนักเส้นเชื่อม)" น้อยที่สุดในการต่อเข้ากับต้นไม้
        int u = pq.top().second;
        pq.pop();
        //! ถ้าโหนดนี้อยู่ในต้นไม้แล้ว ให้ข้ามไป (ป้องกันการเกิดวงวน หรือ Cycle)
        if(inMST[u]) continue;
        //* 2. นำโหนด u เข้าเป็นส่วนหนึ่งของต้นไม้ (MST)
        inMST[u] = true;
        //* 3. สำรวจเพื่อนบ้านทั้งหมดของ u เพื่อหากิ่งก้านใหม่ๆ
        for(auto neighbor : graph[u]){
            int weight = neighbor.first;
            int v = neighbor.second;
            //* เงื่อนไขในการอัปเดต (จุดที่ต่างจาก Dijkstra!):
            // - โหนด v ต้องยังไม่อยู่ในต้นไม้ (!inMST[v])
            // - น้ำหนักเส้นเชื่อมจาก u ไป v ต้อง "น้อยกว่า" ราคาเดิมที่เคยเสนอไว้ (weight < distance[v])
            if(!inMST[v] && weight < distance[v]){
                distance[v] = weight; // อัปเดตราคาใหม่ที่ถูกกว่า
                pq.push({distance[v], v}); // โยนเข้าคิวรอพิจารณา
                parent[v] = u; // จดจำไว้ว่าถ้าจะเชื่อม v ให้ประหยัดสุด ต้องต่อสายมาจาก u
            }
        }
    }
    //@ ส่วนแสดงผลลัพธ์ 
    int totalCost = 0;
    cout<<"Edges in the Minimum Spanning Tree (MST):"<<endl;
    cout<<"Edge \tWeight"<<endl; 
    for(int i = 0; i < graphSize; i++){
        if(parent[i] != -1){ //* เช็คเผื่อกรณีกราฟขาดจากกัน / เป็น startNode ที่ไม่มี parent
            cout<<parent[i]<<" - "<<i<<" \t  "<<distance[i]<<endl;
            totalCost += distance[i];
        }
    }
    cout<<"-------------------------------------"<<endl;
    cout<<"Total Cost of MST = "<<totalCost<<endl;
}

int main(){
    int numVertices, numEdges;
    //* รับค่าจำนวนโหนดและเส้นเชื่อม
    cin>>numVertices>>numEdges;
    vector<vector<pii>> graph(numVertices + 1);
    for(int i = 0; i < numEdges; i++){
        int u, v, weight;
        cin>>u>>v>>weight;
        //* MST มักใช้กับกราฟไร้ทิศทาง (Undirected Graph)
        graph[u].push_back({weight, v});
        graph[v].push_back({weight, u});
    }
    primMST(graph, 1);
    return 0;
}

/* ตัวอย่างข้อมูลนำเข้า (Input)
* Test Case1
    Input: 6 8
           1 2 3
           1 5 5
           2 5 6
           2 3 5
           3 4 9
           3 6 3
           4 6 7
           5 6 2
    Output: Edges in the Minimum Spanning Tree (MST):
            Edge    Weight
            1 - 2     3
            2 - 3     5
            6 - 4     7
            6 - 5     2
            3 - 6     3
            -------------------------------------
            Total Cost of MST = 20
@ Concept (แนวคิด)
- คือ การเริ่มต้นจากโหนดใดโหนดหนึ่ง (สามารถเลือกได้) แล้วค่อยๆ ขยายเส้นทางไปยังโหนดที่อยู่ใกล้ที่สุด 
  ที่ยังไม่เคยไป โดยใช้ข้อมูลของเส้นเชื่อมที่มีน้ำหนักน้อยที่สุดในขณะนั้น
- ต่างจาก Dijkstra's Algorithm ที่เน้นการหาเส้นทางที่สั้นที่สุดจากจุดเริ่มต้นไปยังโหนดอื่นๆ (ระยะทางสะสม)
  Prim's Algorithm เน้นการสร้างต้นไม้แผ่ทั่วที่มีน้ำหนักรวมต่ำที่สุด โดยไม่สนใจเส้นทางที่สั้นที่สุดระหว่างโหนด
- คล้ายกับการโยนหินลงน้ำแล้วให้วงคลื่นค่อยๆ แผ่ขยายออกไป จากจุดที่โยนหินลงไป
* ความแตกต่างเดียวที่สำคัญมากคือ:
    ● Dijkstra: สนใจ "ระยะทางรวมทั้งหมดจากจุดเริ่มต้น" (distances[u] + weight)
        - if(currentDistance > distance[u]) continue; 
        - if(cuurrentDistance + weight < distance[v]) { ... }
    ● Prim: สนใจแค่ "ความยาวของเส้นเชื่อม (Edge) ที่สั้นที่สุด" ที่ใช้ต่อกิ่งก้านใหม่เข้ากับต้นไม้ (weight) 
      เท่านั้น ไม่สนใจระยะทางสะสม
        - if(inMST[u]) continue;
        - if(weight < distance[v]) { ... }
@ ขั้นตอนการทำงาน (Step-by-Step)
1. จุดเริ่มต้น (Initialization):
    ● สุ่มเลือกโหนดเริ่มต้นขึ้นมา 1 โหนด (มักเริ่มที่โหนด 0)
    ● กำหนดค่า distance (ราคาสายเชื่อม) ของโหนดเริ่มต้นเป็น 0 และโหนดอื่นๆ ทั้งหมดเป็น INT_MAX
    ● เตรียม inMST (สมุดบันทึก) เพื่อเก็บว่าโหนดไหนถูกรวมเข้าต้นไม้แล้วบ้าง
2. เลือกโหนดที่ "ถูกที่สุด" (Pick the best edge):
    ● หาโหนด u ที่ยังไม่อยู่ในต้นไม้ (inMST เป็นเท็จ ถ้าอยู่ในต้นไม้แล้วเลือกจะเกิดวงวน (Cycle))
      และมีค่า distance ต่ำที่สุดในขณะนั้น (Root Node)
    ● ในโค้ดเวอร์ชันอัปเกรด เราจะใช้ Priority Queue (Min-Heap) เพื่อดึงโหนดนี้ออกมาได้ทันทีโดยไม่ต้อง
      วนลูปหาเอง
3. ผนวกเข้าเป็นส่วนหนึ่งของต้นไม้:
    ● เปลี่ยนสถานะโหนด u ให้เป็น inMST = true เพื่อยืนยันว่าโหนดนี้เข้าสู่ระบบต้นไม้แผ่ทั่วแล้ว
4. สำรวจเพื่อนบ้าน (Relaxation):
    ● มองไปที่โหนดเพื่อนบ้าน v ทุกตัวที่เชื่อมอยู่กับ u
    ● เงื่อนไขการอัปเดต: ถ้าโหนด v ยังไม่อยู่ในต้นไม้ และ น้ำหนักเส้นเชื่อมจาก u ไปยัง v มีราคา "ถูกกว่า" 
      ค่า distance เดิมที่เราเคยจดไว้
    ● ให้ทำการอัปเดต distance[v] เป็นค่าน้ำหนักใหม่นั้น และบันทึก parent[v] = u เพื่อจำว่าโหนด v 
      นี้ควรเชื่อมต่อผ่านโหนด u ถึงจะประหยัดที่สุด
    ● โยนโหนด v ที่อัปเดตแล้วเข้าไปใน Priority Queue เพื่อรอการพิจารณาในรอบถัดไป
5. ทำซ้ำ:
    ● วนกลับไปทำข้อ 2 จนกว่าโหนดทุกโหนดจะถูกดึงเข้าไปอยู่ในต้นไม้ครบทั้งหมด
@ ตัวอย่างการทำงาน:
- สมมติมีหมู่บ้าน A, B, C, D
1. เริ่มต้น: สุ่มเลือกยืนที่หมู่บ้าน A
2. แผ่ขยายรอบ 1: มองไปรอบๆ A พบว่ามีทางไป B (ราคา 10), ไป C (ราคา 5)
    ● เราเลือก A → C (ราคา 5) เพราะถูกสุด ตอนนี้ต้นไม้เรามี A กับ C แล้ว
3. แผ่ขยายรอบ 2: มองออกจากต้นไม้ของเรา (A และ C) ไปหาจุดที่ยังไม่เชื่อม (B และ D)
    ● ทางออกมี: A → B (10), C → B (2), C → D (8)
    ● เราเลือก C → B (ราคา 2) ตอนนี้ต้นไม้เรามี A, C, B
4. แผ่ขยายรอบ 3: มองหาทางเชื่อมไป D (จุดเดียวที่เหลืออยู่)
    ● สมมติมีทาง B → D (ราคา 4), C → D (8)
    ● เราเลือก B → D (ราคา 4)
*/