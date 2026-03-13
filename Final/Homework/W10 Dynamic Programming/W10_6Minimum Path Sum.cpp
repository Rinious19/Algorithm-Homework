#include <bits/stdc++.h>

using namespace std;

//* กำหนดค่าตัวเลขมากๆ แทนค่า "อนันต์" (Infinity) เพื่อใช้ในการเปรียบเทียบหาค่าต่ำสุด
const long long INF = 1e15; 

//? ฟังก์ชันหา cost รวมที่น้อยที่สุดแบบ Top-Down DP
long long getMinPathCost(int currentRow, int currentCol, int startRow, int startCol, 
                         const vector<vector<int>>& costGrid, vector<vector<long long>>& memo) {
    //@ 1. ถ้าทะลุออกนอกขอบเขต (น้อยกว่าจุดเริ่มต้น) ให้คืนค่าอนันต์ เพื่อไม่ให้เส้นทางนี้ถูกเลือก
    if (currentRow < startRow || currentCol < startCol)
        return INF;
    //@ 2. Base Case: ถ้าเดินย้อนกลับมาถึงจุดเริ่มต้นพอดี ให้คืนค่า cost ของจุดเริ่มต้น
    if (currentRow == startRow && currentCol == startCol)
        return costGrid[startRow][startCol];
    //@ 3. ถ้าเคยคำนวณ cost ที่น้อยที่สุดของพิกัดนี้ไว้แล้ว ให้ดึงจากตาราง Memo ไปตอบได้เลย
    if (memo[currentRow][currentCol] != -1)
        return memo[currentRow][currentCol];
    //@ 4. คำนวณหา cost ของเส้นทางที่มาจาก "ด้านบน" และ "ด้านซ้าย"
    long long costFromTop = getMinPathCost(currentRow - 1, currentCol, startRow, startCol, costGrid, memo);
    long long costFromLeft = getMinPathCost(currentRow, currentCol - 1, startRow, startCol, costGrid, memo);
    //@ 5. เลือกเส้นทางที่ cost น้อยกว่า แล้วบวกกับ cost ของช่องปัจจุบัน จากนั้นบันทึกลง Memo
    memo[currentRow][currentCol] = costGrid[currentRow][currentCol] + min(costFromTop, costFromLeft);
    return memo[currentRow][currentCol];
}

int main() {
    int numRows, numCols; //* รับค่าขนาดของตาราง แถว และ คอลัมน์
    cin>>numRows>>numCols;
    //* สร้างตาราง 2 มิติสำหรับเก็บค่า cost
    vector<vector<int>> costGrid(numRows, vector<int>(numCols));
    //* รับค่า cost แต่ละช่องเข้าตาราง
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++)
            cin>>costGrid[i][j];
    }
    //* รับค่าพิกัดเริ่มต้น และพิกัดเป้าหมาย
    int startX, startY, targetX, targetY;
    cin>>startX>>startY>>targetX>>targetY;
    //* สร้างตาราง Memo ขนาด numRows x numCols แล้วใส่ค่าเริ่มต้นเป็น -1 ทุกช่อง
    vector<vector<long long>> memo(numRows, vector<long long>(numCols, -1));
    //! เรียกใช้ฟังก์ชัน โดยให้ currentRow และ currentCol เริ่มจากพิกัดเป้าหมาย (ทำย้อนกลับ Top-Down)
    long long minTotalCost = getMinPathCost(targetX, targetY, startX, startY, costGrid, memo);
    cout << minTotalCost << "\n"; // แสดงผลลัพธ์
    return 0;
}

/*
* Test Case1
    Input: 3 3
           10 15 20
           25 30 35
           40 45 50
           0 0 2 2
    Output: 130
@ Minimum Path Sum
- เป็นปัญหาการหา เส้นทางที่มีต้นทุนต่ำที่สุด (Minimum Path Sum) บนตาราง 2 มิติ (Grid) โดยมีเงื่อนไข
  บังคับว่าสามารถเดินได้แค่ "ขวา" (Right) หรือ "ลง" (Down) เท่านั้น โจทยระบุชัดเจนให้ใช้วิธี Top-Down 
  Dynamic Programming
@ หลักการ (Dynamic Programming Approach)
- การทำ Top-Down DP คือการเขียนฟังก์ชันแบบเรียกตัวเอง (Recursion) โดยเราจะเริ่มคิดจาก "จุดหมายปลายทาง"
  ย้อนกลับไปหา "จุดเริ่มต้น" และใช้ตาราง (Memo) เพื่อจดจำค่าที่เคยคำนวณไปแล้ว
    ● กำหนด State: ให้ฟังก์ชัน getMinPathCost(r, c) เป็นตัวแทนของ "ต้นทุน (Cost) ที่น้อยที่สุดในการ
      เดินทางจากจุดเริ่มต้นมายังพิกัดแถวที่ r และคอลัมน์ที่ c"
    ● กรณีพื้นฐาน (Base Cases):
        - ถ้าพิกัด (r, c) คือจุดเริ่มต้นพอดี ต้นทุนก็คือค่า cost ของช่องนั้นเพียงช่องเดียว
        - ถ้าพิกัด (r, c) ทะลุออกนอกขอบเขตตาราง (เช่น ถอยร่นไปจนแถวหรือคอลัมน์น้อยกว่าพิกัดเริ่มต้น) เรา
          จะให้ฟังก์ชันคืนค่า "อนันต์" (Infinity หรือตัวเลขที่เยอะมากๆ) เพื่อให้ตอนเอาไปเปรียบเทียบหาค่าต่ำ
          สุด (min) เส้นทางที่ทะลุกรอบนี้จะไม่ถูกเลือก
    ● สมการเปลี่ยนผ่าน (Transition): เนื่องจากเราเดินได้แค่ขวาและลง แปลว่าการที่เราจะมาอยู่ที่ช่อง (r, c) 
      ได้ เราต้องมาจากช่อง ด้านบน (r-1, c) หรือช่อง ด้านซ้าย (r, c-1) ทางใดทางหนึ่งเท่านั้น
        - สมการคือ: ต้นทุนรวมช่องปัจจุบัน = costGrid[r][c] + ค่าน้อยที่สุดระหว่าง getMinPathCost(บน) 
          และ getMinPathCost(ซ้าย)    
@ Time Complexity: 
- Time Complexity: O(N * M) เมื่อ N คือจำนวนแถวและ M คือจำนวนคอลัมน์ของตาราง เนื่องจากแต่ละพิกัดใน
  กริดระหว่างจุดเริ่มต้นถึงเป้าหมาย จะถูกคำนวณเพียงแค่ครั้งเดียวเท่านั้น และถูกเก็บไว้ในตัวแปร memo
@ ตัวอย่าง Test Case1
- row = 3, col = 3
 costGrid         memo
 | 10  15  20 |   | -1   25    45 | 
 | 25  30  35 |   | 35   55    80 | 
 | 40  45  50 |   | 75  100   130 | 
* ผลลัพธ์ คือ 130
- เดินจาก (0, 0) → (0, 1) → (0, 2)
                              ↓
                            (1, 2)
                              ↓
                            (2, 2)
- cost = 10 + 15 + 20 + 35 + 50 = 130
*/