#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n; //* รับจำนวนคู่ของขวัญ
    int size = n*2; //* ของขวัญทั้งหมด
    vector<int> items(size);
    for(int i = 0; i < size; i++)
        cin>>items[i];
    //@ 1. เรียงจากมากไปน้อย (สำคัญมากสำหรับ Greedy)
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(items[j] < items[j + 1])
                swap(items[j], items[j+1]);
        }
    }
    int sumA = 0, sumB = 0;
    //@ 2. เลือกใส่กลุ่มที่ผลรวมน้อยกว่า ณ ขณะนั้น
    for(int i = 0; i < size; i++) {
        if(sumA <= sumB) //* ถ้า sumA น้อยกว่าหรือเท่ากับ sumB → ใส่ A
            sumA += items[i];
        else //* ถ้า sumA มากกว่า sumB → ใส่ B
            sumB += items[i];
    }
    cout<<abs(sumA - sumB)<<endl; //! ไม่การันตีว่าจะได้คำตอบที่ดีที่สุด (Optimal)
    return 0;
}

/*
* Test Case1
    Input:  4
            3 5
            7 11
            8 8
            2 9
    Output: 1
? Number Partitioning Problem
@ หลักการคิด (Greedy Strategy)
- แนวคิดให้เซตของตัวเลขมาแบ่งออกเป็น 2 กลุ่ม ให้ผลรวมของทั้งสองกลุ่ม “ต่างกันน้อยที่สุด”
1. เรียงลำดับ (Sort): ข้อมูลของขวัญ/ตัวเลขทั้งหมดจาก มากไปน้อย
2. เตรียมกลุ่ม: สร้างตัวแปรเก็บผลรวม 2 กลุ่ม (เช่น sumA = 0, sumB = 0)
3 แจกจ่าย (Greedy Choice): วนลูปหยิบข้อมูลที่เรียงแล้วทีละตัว
    ● ถ้า sumA <= sumB ให้บวกค่าใส่ sumA
    ● ถ้า sumA > sumB ให้บวกค่าใส่ sumB
4. คำตอบ: ผลต่างคือ abs(sumA - sumB)
@ ตัวอย่าง
- สมมติของขวัญ 5 ชิ้น (คี่): 10, 2, 8, 4, 7
1. เรียงลำดับ (Sort): 10, 8, 7, 4, 2
2. เริ่มแจกจ่าย:
    ● หยิบ 10: sumA = 10, sumB = 0 (เพราะ 0 <= 0 เลยใส่กลุ่ม A)
    ● หยิบ 8:  sumA = 10, sumB = 8 (เพราะ 10 > 0 เลยใส่กลุ่ม B)
    ● หยิบ 7:  sumA = 10, sumB = 15 (เพราะ 10 > 8 เลยใส่กลุ่ม B)
    ● หยิบ 4:  sumA = 14, sumB = 15 (เพราะ 10 < 15 เลยใส่กลุ่ม A)
    ● หยิบ 2:  sumA = 16, sumB = 15 (เพราะ 14 < 15 เลยใส่กลุ่ม B)
3. ผลต่าง: |16 - 15| = 1
@ ข้อควรระวัง (Greedy vs Dynamic Programming)
- สำหรับการแบ่งกลุ่ม (Partition Problem) วิธีแบบ Greedy อาจจะได้คำตอบที่ "ดีที่สุด" ในหลายกรณี 
  แต่ไม่ใช่ทุุกกรณี (มันเป็นเพียงคำตอบที่ใกล้เคียงที่สุดในเวลาอันสั้น หรือ Heuristic)
- ถ้าโจทย์ต้องการคำตอบที่แม่นยำที่สุด 100%: ต้องใช้ Dynamic Programming (0/1 Knapsack variation) 
  แต่โค้ดจะยากกว่าและกินเวลาเครื่องมากกว่า
*/