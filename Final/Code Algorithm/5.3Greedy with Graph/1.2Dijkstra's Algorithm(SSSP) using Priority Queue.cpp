#include <bits/stdc++.h>
using namespace std;

//* สร้างนามแฝง (Alias) ให้ pair<int, int> เพื่อให้พิมพ์ง่ายขึ้นและอ่านง่าย
//* เราจะใช้โครงสร้างนี้เก็บข้อมูลแบบ {ระยะทางจาก u ไป v, โหนด v} ใน Priority Queue
typedef pair<int, int> pii; // {ระยะทาง, โหนดปลายทาง}

void dijkstra_pq(const vector<vector<pii>>& graph, int startNode){
    int numVertices = graph.size();
    vector<int> distances(numVertices, INT_MAX);
    vector<int> previousNode(numVertices, -1);
    //@ สร้าง Priority Queue แบบ Min-Heap (ค่าน้อยสุดจะอยู่บนสุดเสมอ)
    //* รูปแบบคือ: priority_queue<ชนิดข้อมูล, คอนเทนเนอร์, ตัวเปรียบเทียบ>
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    //* เริ่มต้นที่จุด startNode ระยะทางเป็น 0
    distances[startNode] = 0;
    //* โยนจุดเริ่มต้นเข้าไปในคิวในรูปแบบ {ระยะทาง, โหนด} -> {0, startNode}
    //! สาเหตุที่เอาระยะทางขึ้นก่อน เพราะ Priority Queue จะเรียงลำดับจากค่าตัวแรกเสมอ
    pq.push({0, startNode});
    while(!pq.empty()){ //@ วนลูปจนกว่าคิวจะว่าง
        //* 1. ดึงโหนดที่ระยะทางสั้นที่สุดในคิวออกมา (Root ของ Min-Heap)
        int currentDist = pq.top().first; // .first คือระยะทางที่เก็บไว้ในคิว
        int u = pq.top().second; // .second คือโหนดปลายทางที่เก็บไว้ในคิว
        pq.pop(); // เอาออกจากคิว
        //! จุดสำคัญ (Optimization):
        // เนื่องจากกราฟอาจมีหลายเส้นทางที่ไปถึง u ได้ ค่า u อาจถูกโยนเข้าคิวหลายรอบ
        // ถ้าค่าระยะทางที่ดึงออกมา มันมากกว่าระยะทางที่สั้นที่สุดที่เคยหาได้แล้ว ให้ข้ามไปเลย
        if (currentDist > distances[u]) continue;
        //* 2. สำรวจเพื่อนบ้านทั้งหมดของโหนด u
        // กราฟเราเป็น Adjacency List: graph[u] จะมีเฉพาะโหนดที่เชื่อมกันจริงๆ
        for(auto neighbor : graph[u]){ 
            // auto ใช้แทน pii เพราะ graph[u] เป็น vector ของ pii
            int v = neighbor.second;       // โหนดเพื่อนบ้าน
            int weight = neighbor.first;   // น้ำหนักเส้นทางจาก u ไป v
            //* 3. Relaxation (ผ่อนคลายขอบ)
            // ถ้าระยะทางใหม่ (ผ่าน u) สั้นกว่าระยะทางเดิมที่เคยจดไว้
            if (distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight; // อัปเดตระยะทางใหม่
                previousNode[v] = u;                  // จดจำทางผ่าน
                // โยนระยะทางใหม่ที่สั้นกว่า และโหนดเป้าหมายเข้าไปในคิว
                pq.push({distances[v], v});
            }
        }
    }
    //@ ส่วนแสดงผลลัพธ์ (สไตล์เดิม)
    for(int i = 0; i < numVertices; i++){
        if(i != startNode && distances[i] != INT_MAX){
            cout<<"Path from "<<startNode + 1<<" to "<<i + 1<<" : ";
            vector<int> path;
            for(int curr = i; curr != -1 ; curr = previousNode[curr]) path.push_back(curr);
            for(int j = path.size() - 1; j > 0; j--) cout<<path[j] + 1<<" -> ";
            cout<<path[0] + 1<<" | Total dist = "<<distances[i]<<endl;
        }
    }
}

int main(){
    int numVertices, numEdges;
    if (!(cin>>numVertices>>numEdges)) return 0;
    //* สร้าง Adjacency List: เป็น Array ของ Vector
    //* graph[u] = จะเก็บ List ของ {น้ำหนัก, โหนดปลายทาง v}
    vector<vector<pii>> graph(numVertices);
    for(int i = 0; i < numEdges; i++){
        int start, dest, weight;
        cin>>start>>dest>>weight;
        //* กราฟ 2 ทิศทาง (Undirected Graph)
        //* สังเกตว่าเรา push ข้อมูลแบบ {weight, node} เข้าไป
        graph[start].push_back({weight, dest});
        graph[dest].push_back({weight, start});
    }
    dijkstra_pq(graph, 0);
    return 0;
}

/*
* Test Case1
    Input: 5 6
           0 1 5
		   0 3 9
		   0 4 1
           1 2 2
		   2 3 6
		   3 4 2
    Output: Path from 0 to 1 : 0 -> 1      | Total distance = 5
            Path from 0 to 2 : 0 -> 1 -> 2 | Total distance = 7
            Path from 0 to 3 : 0 -> 4 -> 3 | Total distance = 3
            Path from 0 to 4 : 0 -> 4      | Total distance = 1
@ Concept ของ Dijkstra's Algorithm Using Priority Queue:
- Dijkstra อาศัยแนวคิดที่เรียกว่า Greedy Algorithm (อัลกอริทึมแบบละโมบ) คือการตัดสินใจเลือกทางเลือกที่
  "ดูดีที่สุดในขณะนั้น" เสมอ โดยในที่นี้คือการเลือก "โหนดที่อยู่ใกล้ที่สุดที่เพิ่งค้นพบ" ก่อน เพื่อขยายเส้นทางต่อไป
  เรื่อยๆ เหมือนกับการหยดน้ำลงบนกระดาษทิชชู่ น้ำจะซึมแผ่ออกไปยังจุดที่ใกล้ที่สุดรอบๆ ตัวมันก่อนเสมอ
- ข้อจำกัดสำคัญ: Dijkstra ไม่สามารถใช้กับกราฟที่มีเส้นทางน้ำหนักติดลบ (Negative Weight Edge) ได้ 
  เพราะหลักการแบบละโมบจะถือว่า ถ้ายืนยันระยะทางสั้นสุดของโหนดใดไปแล้ว จะไม่มีทางมีเส้นทางอื่นที่สั้นกว่านี้อีก 
  (ถ้าน้ำหนักติดลบได้ การเดินอ้อมอาจจะทำให้ระยะทางรวมลดลง ซึ่งขัดกับหลักการนี้)
! Dijkstra's algorithm การันตีคำตอบว่าเป็นเส้นทางที่สั้นที่สุด (Shortest Path) เสมอ
@ หลักการทำงาน (Principles) ใช้ Priority Queue:
- อัลกอริทึมจะรักษาข้อมูล 3 ส่วนหลักๆ ไว้เสมอ คือ:
    ● ระยะทางสั้นที่สุดที่ค้นพบในปัจจุบัน (Distance): เริ่มต้นจุดเริ่มต้นเป็น 0 จุดอื่นๆ เป็น Infinity (INT_MAX)
    ● โหนดก่อนหน้า (Previous Node): เพื่อเก็บข้อมูลว่าเราเดินทางมาถึงโหนดนี้ผ่านทางโหนดไหน 
    ● Priority Queue: เพื่อให้เราสามารถดึงโหนดที่มีระยะทางสั้นที่สุดที่ยังไม่ถูกล็อคออกมาได้อย่างรวดเร็ว
- ขั้นตอนการทำงาน:
    1. เริ่มต้นที่จุดเริ่มต้น (startNode) ระยะทางเป็น 0 และโยนเข้าไปใน Priority Queue
    2. ดึงโหนดที่มีระยะทางสั้นที่สุดออกจาก Priority Queue (สมมติว่าเป็นโหนด u)
    3. ถ้าโหนด u นี้มีระยะทางมากกว่าระยะทางที่เราบันทึกไว้แล้ว แสดงว่าเราเคยเจอโหนดนี้มาก่อนและได้ระยะทาง
      ที่ดีกว่าแล้ว ให้ข้ามไปเลย
    4. สำรวจเพื่อนบ้านของ u (โหนด v ที่เชื่อมกับ u) และทำการ Relaxation:
        * ถ้าระยะทางใหม่ (จาก u ไป v) สั้นกว่าระยะทางเดิมที่เคยบันทึกไว้สำหรับ v
            ● อัปเดตระยะทางใหม่สำหรับ v และบันทึกว่าเราเดินทางมาถึง v ผ่าน u
            ● ระบุโหนดก่อนหน้าของ v เป็น u เพื่อให้เราสามารถย้อนรอยเส้นทางได้ในภายหลัง
            ● โยนระยะทางใหม่และโหนด v เข้าไปใน Priority Queue เพื่อให้มันถูกพิจารณาในรอบถัดไป
    5. ทำซ้ำข้อ 2-4 จนกว่าจะเยี่ยมชมครบทุกโหนด (หรือจนกว่าโหนดที่เหลือจะไปไม่ถึงแล้ว)
@ Time Complexity: O(E log V) 
- สำหรับกราฟที่ใช้ Adjacency List และ Priority Queue เพราะในแต่ละรอบเราจะดึงโหนดที่มีระยะทางน้อยที่
  สุดออกมาได้ใน O(log V) และเราจะทำการ Relaxation กับทุกขอบ (Edge) ในกราฟ ซึ่งมีจำนวน E ขอบ
@ ตัวอย่างการทำงาน:
    Nodes:         0  1  2  3  4 
    previousNode: -1  0  1  4  0
    distance:      0  5  7  3  1 
    startNode = 0
- SSSP ในข้อนี้คือ
    ● จากโหนด 0 ไปยังโหนด 1: เส้นทางที่สั้นที่สุดคือ 0 -> 1       ระยะทาง = 5
    ● จากโหนด 0 ไปยังโหนด 2: เส้นทางที่สั้นที่สุดคือ 0 -> 1 -> 2  ระยะทาง = 7
    ● จากโหนด 0 ไปยังโหนด 3: เส้นทางที่สั้นที่สุดคือ 0 -> 4 -> 3  ระยะทาง = 3
    ● จากโหนด 0 ไปยังโหนด 4: เส้นทางที่สั้นที่สุดคือ 0 -> 4       ระยะทาง = 1
@ เขียนลูปแบบปกติ ตรงส่วนหาเพื่อนบ้านของโหนด u เพื่อความเข้าใจง่ายขึ้น
    for(int i = 0; i < graph[u].size(); i++){
        int weight = graph[u][i].first; // น้ำหนักของขอบจาก u ไป v
        int v = graph[u][i].second;      // โหนดปลายทาง v
        // ทำการ Relaxation ต่อไป...
        if(distances[u] + weight < distances[v]){
            distances[v] = distances[u] + weight;
            previousNode[v] = u;
            pq.push({distances[v], v});
        }
    }
*/