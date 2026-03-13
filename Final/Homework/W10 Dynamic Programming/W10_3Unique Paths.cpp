#include <bits/stdc++.h>

using namespace std;

//? ฟังก์ชันหาจำนวนเส้นทางทั้งหมดในป่า
//* รับค่า rows (จำนวนแถว หรือพิกัดเป้าหมายแนวแกน x) และ cols (จำนวนคอลัมน์ หรือพิกัดเป้าหมายแนวแกน y)
long long countUniquePaths(int targetRow, int targetCol){
    //@ สร้างตาราง 2 มิติสำหรับเก็บจำนวนเส้นทาง
    //* paths[r][c] แทน "จำนวนเส้นทางทั้งหมดที่สามารถเดินมาถึงแถวที่ r และคอลัมน์ที่ c"
    vector<vector<long long>> paths(targetRow + 1, vector<long long>(targetCol + 1, 0));
    //@ เริ่มต้นคำนวณแบบ Bottom-Up
    for(int r = 1; r <= targetRow; r++){
        for(int c = 1; c <= targetCol; c++){
            //* Base Case: จุดเริ่มต้นมี 1 เส้นทาง (คือการอยู่กับที่)
            if (r == 1 && c == 1){
                paths[r][c] = 1;
            } 
            else{
                //* ดึงจำนวนเส้นทางจากช่องด้านบน (ถ้าไม่ใช่แถวบนสุด แถว 0)
                long long pathsFromTop = (r > 1) ? paths[r - 1][c] : 0;
                //* ดึงจำนวนเส้นทางจากช่องด้านซ้าย (ถ้าไม่ใช่คอลัมน์ซ้ายสุด หลัก 0)
                long long pathsFromLeft = (c > 1) ? paths[r][c - 1] : 0;
                //* นำเส้นทางมารวมกัน
                paths[r][c] = pathsFromTop + pathsFromLeft;
            }
        }
    }
    //* คืนค่าผลลัพธ์ที่ช่องเป้าหมาย (targetRow, targetCol)
    return paths[targetRow][targetCol];
}

int main(){
    int rows, cols;
    cin>>rows>>cols;
    long long totalPaths = countUniquePaths(rows, cols);
    cout<<totalPaths<<endl;
    return 0;
}

/*
* Test Case1
    Input: 2 3
    Output: 3
* Test Case2
    Input: 2 5
    Output: 5
@ Unique Paths
- ต้องการหาจำนวนเส้นทางทั้งหมดที่เป็นไปได้ในการเดินบนตารางกริด (Grid) จากจุดเริ่มต้นไปยังจุดหมาย โดยมีข้อ
  จำกัดเรื่องทิศทางการเดิน
@ หลักการ (Dynamic Programming Approach)
- ข้อนี้เราสามารถใช้ Bottom-Up DP แบบตาราง 2 มิติ (2D Array) ได้เลย เพราะเส้นทางที่จะเดินมาถึงช่อง
  ปัจจุบันได้ จะต้องมาจากช่องด้านซ้าย หรือ ช่องด้านบน เท่านั้น
    ● กำหนด State: ให้ paths[r][c] แทน "จำนวนเส้นทางทั้งหมดที่สามารถเดินมาถึงแถวที่ r และคอลัมน์ที่ c"
    ● กรณีพื้นฐาน (Base Case): * จุดเริ่มต้น paths[1][1] = 1 (เพราะเรายืนอยู่จุดเริ่มต้นแล้ว นับเป็น 1 วิธี)
        - ช่องที่อยู่แถวบนสุดทั้งหมด (Row 1) จะมีวิธีเดินมาถึงแค่ 1 วิธีเสมอ (คือเดินขวามาเรื่อยๆ)
        - ช่องที่อยู่คอลัมน์ซ้ายสุดทั้งหมด (Column 1) จะมีวิธีเดินมาถึงแค่ 1 วิธีเสมอ (คือเดินลงมาเรื่อยๆ)
    ● สมการเปลี่ยนผ่าน (Transition): สำหรับช่องอื่นๆ (r, c) จำนวนเส้นทางจะเกิดจากผลรวมของเส้นทางที่
      เดินมาจาก ช่องด้านบน และ ช่องด้านซ้าย
        * paths[r][c] = paths[r - 1][c] + paths[r][c - 1]
@ Time Complexity: 
- Time Complexity: O(m x n) เพราะต้องใช้ Loop 2 ชั้นวนเข้าไปคำนวณหาค่าในตารางกริดทุกช่อง 
  ช่องละ 1 ครั้ง 
- Space Complexity: O(m x n) สำหรับการเก็บข้อมูลตาราง vector 2 มิติ
@ ตัวอย่าง Test Case2
- row = 2, col = 5
        0  1  2  3  4  5
    0 | 0  0  0  0  0  0 
    1 | 0  1  1  1  1  1 
    2 | 0  1  2  3  4  5
- จึงมีวิธีเรียงลำดับได้ 5 แบบ
    1️⃣ ขวา → ขวา → ขวา → ขวา → ลง
    2️⃣ ลง → ขวา → ขวา → ขวา → ขวา
    3️⃣ ขวา → ลง → ขวา → ขวา → ขวา
    4️⃣ ขวา → ขวา → ลง → ขวา → ขวา
    5️⃣ ขวา → ขวา → ขวา → ลง → ขวา
* ผลลัพธ์
- countUniquePaths = 5
*/