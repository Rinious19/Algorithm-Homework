#include <bits/stdc++.h>
using namespace std;

//* นิยามค่า INF (Infinity) เป็น 1,000,000,000 (1e9) 
//* เหตุผลที่ใช้ 1e9 แทน INT_MAX เพื่อป้องกันปัญหา Integer Overflow เวลาเอาค่าไปบวกกัน
const int INF = 1e9;

//? floydWarshall: ฟังก์ชันหลักที่ใช้ในการคำนวณระยะทางสั้นที่สุดระหว่างทุกคู่ของโหนดในกราฟ
void floydWarshall(const vector<vector<int>>& graph){
   	int numVertices = graph.size();
	//* สร้างตาราง distMatrix คัดลอกข้อมูลเริ่มต้นมาจาก graph
    vector<vector<int>> distMatrix = graph;
    //! k คือ "โหนดทางผ่าน" (Intermediate vertex) **ต้องอยู่ลูปนอกสุดเสมอ**
    for(int k = 0; k < numVertices; k++){
        //* i คือ "โหนดต้นทาง" (Source vertex)
        for(int i = 0; i < numVertices; i++){
            //* j คือ "โหนดปลายทาง" (Destination vertex)
            for(int j = 0; j < numVertices; j++){
                //* ตรวจสอบก่อนว่ามีทางจาก i ไป k และจาก k ไป j จริงๆ (ไม่ใช่ INF)
                if(distMatrix[i][k] < INF && distMatrix[k][j] < INF)
                    //* อัปเดตระยะทางจาก i ไป j ให้เป็นค่าที่น้อยที่สุดระหว่าง:
                    // 1. ระยะทางเดิม (ไปตรงๆ หรือเส้นทางเก่าที่เคยเจอ)
                    // 2. ระยะทางใหม่ (เดินจาก i แวะ k แล้วค่อยไป j)
                    distMatrix[i][j] = min(distMatrix[i][j], distMatrix[i][k] + distMatrix[k][j]);
            }
        }
    }
    // ส่วนแสดงผลลัพธ์ตาราง (Matrix Output)
    cout<<"Shortest Path Matrix (APSP):"<<endl;
    for(int i = 0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            if(distMatrix[i][j] == INF) 
                cout<<"INF\t"; // ถ้าไปไม่ถึงให้พิมพ์ INF
            else 
                cout<<distMatrix[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int main(){
    int numVertices, numEdges;
	cin>>numVertices>>numEdges;
    //* สร้างกราฟขนาด V x V โดยตั้งค่าเริ่มต้นทุกช่องให้เป็น INF (ตีว่ายังไม่มีถนนเชื่อมกัน)
    vector<vector<int>> graph(numVertices, vector<int>(numVertices, INF));
    //* ระยะทางจากโหนดใดๆ ไปหาตัวมันเอง (เส้นทแยงมุมของ Matrix) ต้องมีค่าเป็น 0 เสมอ
    for(int i = 0; i < numVertices; i++)
        graph[i][i] = 0;
    //* รับค่าเส้นเชื่อม
    for(int i = 0; i < numEdges; i++){
        int start, dest, weight;
        cin>>start>>dest>>weight;
        graph[start - 1][dest - 1] = weight; // Directed Graph
    }
    floydWarshall(graph);
    return 0;
}

/*
* Test Case1
    Input: 4 6
		   1 2 3
		   1 4 5
		   2 1 2
		   2 4 4
		   3 2 6
		   4 3 2
    Output: Shortest Path Matrix (APSP):
	         1       2       3       4  //* ระยะทางจาก i ไป j (i คือแถว, j คือคอลัมน์)
	     ┌──────────────────────────────                        
		1|   0       3       7       5
		2|   2       0       6       4
		3|   8       6       0       10
		4|   10      8       2       0
@ Concept (แนวคิด)
- Floyd-Warshall ใช้แนวคิดที่เรียกว่า Dynamic Programming (การเขียนโปรแกรมแบบพลวัต)
- หลักการคือ "การแบ่งปัญหาใหญ่เป็นปัญหาย่อย แล้วนำคำตอบย่อยมาต่อยอดกัน" ลองจินตนาการถึงการจองตั๋ว
  เครื่องบิน:
	● คุณต้องการบินจาก กรุงเทพ (i) ไป นิวยอร์ก (j) * ตอนแรกคุณดูแค่ เที่ยวบินตรง (Direct Flight) 
	  ซึ่งอาจจะแพงมาก หรือไม่มีบินตรง (เป็น Infinity)
	● จากนั้นคุณเริ่มหาตัวเลือกใหม่ โดยลองเอา โตเกียว (k) มาเป็นจุดแวะพัก (Transit)
	● คุณก็ไปดูตารางราคาว่า "ตั๋วกรุงเทพไปโตเกียว" + "ตั๋วโตเกียวไปนิวยอร์ก" มันถูกกว่าการบินตรงไหม? 
	  ถ้าถูกกว่า คุณก็จดเส้นทางแวะพักนี้ทับเส้นทางบินตรงเดิมไปเลยครับ
@ หลักการทำงาน (Principles)
- กลไกหลักของ Floyd-Warshall คือการใช้ Loop ซ้อนกัน 3 ชั้น (k, i, j) เพื่ออัปเดตตารางเมทริกซ์ 2 มิติ
  (สมมติชื่อว่าตาราง D)	
1. จุดเริ่มต้น (Initial State): สร้างตาราง D ขนาด V x V โดยให้ D[i][j] มีค่าเท่ากับน้ำหนัก
   เส้นทางตรงจาก i ไป j (ถ้าไม่มีทางไปให้เป็น infty, ถ้า i = j ให้เป็น 0 ระยะทางจากโหนดไปหาตัวมันเอง)
2. ตัวแปร k (จุดแวะพัก): ลูปนอกสุดจะเป็นตัวกำหนดว่า "ในรอบนี้ เราจะอนุญาตให้ใช้โหนดหมายเลข 0 ถึง k 
   เป็นจุดแวะพักได้"
3. สมการอัปเดต (Relaxation): ในแต่ละรอบของ k, สำหรับทุกๆ คู่โหนดต้นทาง i และปลายทาง j เราจะเปรียบ
   เทียบระยะทางว่า:
   		● D[i][j] = min(D[i][j], D[i][k] + D[k][j])
		● D[i][j] : ระยะทางเดิมที่ดีที่สุดที่เคยหาได้
		● D[i][k] + D[k][j] : ระยะทางใหม่ที่เกิดจากการเดินจาก i ไปแวะ k แล้วค่อยเดินจาก k ไป j
4. ทำซ้ำจนครบ: เมื่อลูป k ขยับไปเรื่อยๆ จนครบทุกโหนด แปลว่าเราได้ลองใช้โหนดทุกโหนดบนกราฟเป็นจุดแวะ
   พักครบหมดแล้ว ตารางที่ได้ในรอบสุดท้ายคือระยะทางที่สั้นที่สุดของทุกคู่จุด (APSP)
@ Time Complexity: O(V^3) 
- เนื่องจากมีการใช้ Loop ซ้อนกัน 3 ชั้น (k, i, j) ที่แต่ละชั้นวิ่งจาก 0 ถึง V-1
*/
