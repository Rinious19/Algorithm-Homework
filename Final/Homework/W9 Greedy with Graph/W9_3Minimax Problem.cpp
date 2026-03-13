#include <bits/stdc++.h>
using namespace std;

const int INF = 1e8; //* กำหนดค่า Infinity ให้พอดี (ไม่เกินขอบเขต int เมื่อบวกกัน)

//? ฟังก์ชันหลักสำหรับหาเขตที่ควรตั้งโรงพยาบาลใหม่
int findBestHospitalLocation(vector<vector<int>> dist, const vector<int> &existingHosp){
    int distSize = dist.size(); //* ขนาดของตารางระยะทาง (รวม index 0 ที่ไม่ได้ใช้)
    //@ 1. รัน Floyd-Warshall: เขตเริ่มที่ 1 ถึง N 
    for(int k = 1; k < distSize; ++k)
        for(int i = 1; i < distSize; ++i)
            for(int j = 1; j < distSize; ++j)
                if(dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    //@ 2. เซ็ตสถานะ รพ. เดิม และหาระยะทางไป รพ. เดิมที่ใกล้ที่สุด
    vector<bool> hasHospital(distSize, false);
    //* เก็บ “ระยะทางสั้นที่สุดจากเขตนั้น ไปยังโรงพยาบาลเดิมที่ใกล้ที่สุด (มีได้หลายที่)”
    vector<int> minDistToExisting(distSize, INF); 
    for(int h : existingHosp){
        hasHospital[h] = true;
        for(int i = 1; i < distSize; ++i) //* i = (เขตทั้งหมด) 
            //* หาระยะทางที่ใกล้ที่สุดจากเขต i ไปยัง รพ. h (รพ. เดิมที่มีอยู่แล้ว) 
            // แล้วเก็บไว้ใน minDistToExisting[i] (ถ้าเจอระยะทางที่สั้นกว่าเดิมก็อัปเดต)
            minDistToExisting[i] = min(minDistToExisting[i], dist[i][h]);
    }
    //@ 3. จำลองตั้ง รพ. ใหม่ทีละเขตเพื่อหาจุดที่ดีที่สุด (Minimax)
    //* bestLocation เก็บเขตที่ควรตั้ง รพ. ใหม่, minOfMaxDist เก็บค่าระยะทางสูงสุดที่ต่ำที่สุดที่ได้จากการตั้ง รพ. ใหม่
    int bestLocation = -1, minOfMaxDist = INF; 
    for(int u = 1; u < distSize; ++u){ //* สร้างรพ. ใหม่ที่เขต u
        if(hasHospital[u]) //* ถ้าเขตนี้มี รพ. เดิมอยู่แล้ว ก็ไม่ต้องพิจารณาเป็นเขตตั้ง รพ. ใหม่ (ข้ามไปเลย)
            continue;
        int currentMaxDist = 0;
        //! เราสร้างรพ. ที่เขต u หาระยะทางที่มากที่สุดในการเดินทางจากเขต v ไป u 
        // เปรียบเทียบระยะทางในการไปรพ. ระหว่าง รพ. เดิม (v) กับ รพ. ใหม่ (u) แล้วหาระยะใกล้สุด 
        for(int v = 1; v < distSize; ++v)
            currentMaxDist = max(currentMaxDist, min(minDistToExisting[v], dist[u][v]));
        if(currentMaxDist < minOfMaxDist){
            minOfMaxDist = currentMaxDist;
            bestLocation = u;
        }
    }
    return bestLocation;
}

int main(){
    int numExistingHospitals, numRoads; 
    cin>>numExistingHospitals>>numRoads; //* รับจำนวนโรงพยาบาลเดิมและจำนวนถนน
    vector<int> existingHospitals(numExistingHospitals);
    for(int i = 0; i < numExistingHospitals; ++i)
        cin>>existingHospitals[i]; //* รับเขตที่มีโรงพยาบาลเดิมอยู่
    int totalDistricts = 0; //* เก็บจำนวนเขตทั้งหมด (จะอัปเดตจากข้อมูลถนนที่ค่ามากที่สุด)
    //@ เก็บข้อมูลถนนในรูปแบบ {เขตเริ่ม, เขตปลาย, ระยะทาง}
    //! เราสร้าง dist ตั้งแต่แรกไม่ได้เพราะเราต้องรู้จำนวนเขตทั้งหมดก่อน (ไม่รู้ล่วงหน้าว่ามีกี่เขต)
    vector<vector<int>> roads(numRoads, vector<int>(3)); 
    for(int i = 0; i < numRoads; ++i){
        cin>>roads[i][0]>>roads[i][1]>>roads[i][2];
        totalDistricts = max({totalDistricts, roads[i][0], roads[i][1]}); //* หาจำนวนเขตทั้งหมดไปในตัว
    }
    //@ เตรียมตาราง APSP และใส่ข้อมูลถนนเริ่มต้น 
    // ใช้ 1-based index ตามโจทย์ ต้องบวก 1 เพื่อให้ใช้ index 1 ถึง N 
    vector<vector<int>> dist(totalDistricts + 1, vector<int>(totalDistricts + 1, INF));
    for(int i = 1; i <= totalDistricts; ++i) //* ระยะทางไปหาเขตตัวเองคือ 0
        dist[i][i] = 0;
    //* นำข้อมูลถนนใส่ในตาราง Matrix (ใช้ min เผื่อกรณีโจทย์หลอกมีถนนเชื่อมคู่เดิม 2 เส้น)
    for(const auto &road : roads){
        int u = road[0], v = road[1], w = road[2];
        //! ใช้ min เผื่อกรณีโจทย์หลอกมีถนนเชื่อมคู่เดิม 2 เส้น (ระยะทางอาจไม่เท่ากัน)
        dist[u][v] = min(dist[u][v], w); // Unirected Graph
        dist[v][u] = min(dist[v][u], w);
    }
    int result = findBestHospitalLocation(dist, existingHospitals);
    if(result != -1)
        cout << result << "\n";
    return 0;
}

/*
* Test Case1
    Input: 1 6
           2
           1 2 10
           2 3 10
           3 4 10
           4 5 10
           5 6 10 
           6 1 10
    Output: 5
@ วิเคราะห์และอธิบายโจทย์
- ปัญหาในโจทย์ข้อนี้คือ "การหาจุดตั้งโรงพยาบาลสนามแห่งใหม่" เพื่อรองรับผู้ป่วยโควิด-19 โดยมีเงื่อนไขหลักๆ:
1. ลดความเหลื่อมล้ำในการเดินทาง (Minimax Objective): เป้าหมายหลักของโจทย์นี้ ไม่ใช่การหาผลรวมระยะ
   ทางที่สั้นที่สุด แต่เป็นการ ทำให้ "คนที่ดวงซวยที่สุด (ต้องเดินทางไกลที่สุด)" เดินทางได้ใกล้ขึ้น หรือพูดง่ายๆ 
   คือ หาจุดที่ทำให้ระยะทางสูงสุดที่ประชาชนคนใดคนหนึ่งต้องเดินทาง มีค่าน้อยที่สุดนั่นเองครับ นี่คือที่มาของคำว่า 
   Minimax (Minimize the Maximum value)
2. อ้างอิงจากโรงพยาบาลเดิม: เรามีโรงพยาบาลตั้งอยู่แล้วบางเขต แปลว่าประชาชนสามารถเลือกได้ว่าจะไปโรงพยาบาล
   เก่าที่ใกล้บ้าน หรือไปโรงพยาบาลใหม่ที่เรากำลังจะสร้าง (ใครใกล้กว่าไปอันนั้น)
3. สร้างโรงพยาบาลใหม่ 1 แห่งในเขตที่ยังไม่มี: ต้องเลือกเขตที่ยังไม่มีโรงพยาบาลมา 1 เขต เพื่อตั้งโรงพยาบาลใหม่
4. เงื่อนไขตัวเลขเขต: ถ้ามีหลายเขตที่สร้างแล้วทำให้คนไกลสุดได้ผลดีเท่ากัน ให้เลือก "เขตที่มีหมายเลขน้อยที่สุด"
@ แนวคิดของอัลกอริทึม (Floyd-Warshall + Brute Force)
1. คำนวณระยะทางทุกคู่ (All-Pairs Shortest Path):
    ● เริ่มแรก เราไม่รู้ว่าใครจะเดินทางไปไหนบ้าง เลยใช้ Floyd-Warshall Algorithm เพื่อหาระยะทางที่สั้นที่
      สุดจาก "ทุกเขตไปทุกเขต" เตรียมไว้ก่อนเลย ข้อดีคือเขียนง่าย (ลูป 3 ชั้นสั้นๆ) และพอดีจำนวนเขต 
      (N <= 500) คอมพิวเตอร์คำนวณไหวสบายๆ
2. สถานการณ์ปัจจุบัน (ก่อนสร้าง รพ. ใหม่):เราต้องรู้ก่อนว่า ณ ตอนนี้ ที่ยังมีแค่โรงพยาบาลเก่า ประชาชนแต่ละเขต
  เขาไปโรงพยาบาลไหนที่ใกล้ที่สุด แล้วมันไกลแค่ไหนเราก็สร้างตาราง minDistToExisting มาเก็บระยะทางสั้นสุด
  จาก "แต่ละเขต ไป โรงพยาบาลเดิมที่ใกล้ที่สุด"
3. จำลองการสร้าง รพ. ใหม่ (Brute Force Simulation):
    ● เราจะใช้วิธีลองผิดลองถูก (Brute Force) โดยลองสมมติว่าสร้างโรงพยาบาลใหม่ที่เขต u (ที่ยังไม่มี รพ.)
    ● สำหรับทุกๆ เขต v เราจะประเมินว่า "ถ้าสร้าง รพ. ที่ u เขต v จะเดินทางใกล้ลงไหม?" โดยเทียบระหว่าง 
      ไป รพ. เดิม (minDistToExisting[v]) กับ ไป รพ. ใหม่ที่ u (dist[u][v])
    ● จากนั้นเราจะหาสถิติว่า ในสถานการณ์ที่ รพ. อยู่เขต u นี้ คนที่เดินทางไกลที่สุด (currentMaxDist) 
      ต้องเดินทางไกลแค่ไหน?
4. คัดเลือกจุดที่ดีที่สุด (Minimax Selection):
    ● เราจะเลือกเขต u ที่ทำให้ currentMaxDist มีค่าน้อยที่สุดเป็นคำตอบสุดท้าย
    ● ถ้ามีเขตที่ให้ผลลัพธ์เท่ากัน การที่เราลูปไล่เขตจาก 1 ไป N จะทำให้เราเจอเขตหมายเลขน้อยที่สุดก่อน 
      และมันจะไม่อัปเดตค่า (เพราะเราใช้ < ไม่ใช่ <=) ทำให้ตรงกับเงื่อนไขโจทย์พอดี
*/