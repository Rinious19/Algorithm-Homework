#include <bits/stdc++.h>
using namespace std;

//? function หาค่า minCut 
//* สังเกตที่ int &minCut (มีเครื่องหมาย &) คือการส่งที่อยู่ของตัวแปรมาแก้ไขค่าโดยตรง
void findMinCut(int currentSum, int count, int targetLength, const int rangeCut[], int n, int &minCut){
    //@ 1. Optimization (Pruning): ตัดกิ่งที่ไม่จำเป็น
    //* ถ้าจำนวนท่อนที่ตัดไปแล้ว มากกว่าหรือเท่ากับสถิติที่ดีที่สุดที่เคยเจอ ก็หยุดทำได้เลย (เพราะเราหาค่าน้อยสุด)
    if(count >= minCut)
        return;
    //@ 2. Base Case: ตัดได้ครบความยาวพอดี
    if(currentSum == targetLength){
        //* อัปเดตค่า minCut (เนื่องจากเป็น pass by reference ค่าใน main จะเปลี่ยนตาม)
        if(count < minCut)
            minCut = count;
        return;
    }
    //@ 3. Base Case: ความยาวเกิน 
    if(currentSum > targetLength)
        return;
    //@ 4. Recursive Step: ลองตัดท่อนในความยาวที่กำหนดทุกแบบ
    for (int i = 0; i < n; i++) //* เพิ่มท่อนความยาว rangeCut[i], นับครั้งที่ตัด +1
        findMinCut(currentSum + rangeCut[i], count + 1, targetLength, rangeCut, n, minCut);
}

int main(){
    //@ 1. ประกาศตัวแปรทั้งหมดใน Local (ใน main)
    int targetLength = 8;
    int rangeCut[] = {2, 3, 5};
    int n = sizeof(rangeCut) / sizeof(rangeCut[0]); //* คำนวณขนาด array อัตโนมัติ
    int minCut = INT_MAX; //* ตัวแปรเก็บคำตอบ ตั้งค่าเริ่มต้นให้มากที่สุด
    //@ 2. ส่งตัวแปรทั้งหมดเข้าไปในฟังก์ชัน
    findMinCut(0, 0, targetLength, rangeCut, n, minCut);
    //@ 3. แสดงผล
    if(minCut == INT_MAX)
        cout<<"Cannot cut exactly"<<endl;
    else
        cout<<minCut<<endl;
    return 0;
}

/*
@ แนวคิด (Exhaustive Search)
- โจทย์สั่งให้ใช้ Exhaustive Search (ค้นหาทุกทางที่เป็นไปได้)เราต้องเขียน Recursive Function ที่ "ลองตัด"
  ทีละขนาด (2, 3, 5) ไปเรื่อยๆ จนกว่าความยาวจะครบ 8
    ● ทางตัน (Base Case - Fail): ตัดแล้วความยาวรวม เกิน 8 → หยุดทำ
    ● เจอคำตอบ (Base Case - Success): ตัดแล้วความยาวรวม เท่ากับ 8 พอดี → เปรียบเทียบจำนวนท่อนว่า
       "น้อยที่สุด" หรือยัง ถ้าใช่ให้จดค่าไว้
    ● แตกกิ่ง (Recursive Step): ถ้ายังไม่ครบ 8 ให้ลองตัดเพิ่มด้วยขนาด 2, 3, และ 5 ต่อไป
@ คำอธิบายการทำงาน
1. โปรแกรมจะเริ่มที่ findMinCut(0, 0) 
   ● currentSum = 0 (ความยาวที่ตัดได้ตอนนี้)
   ● count = 0 (จำนวนท่อนที่ตัดได้ตอนนี้)
2. มันจะแตกกิ่งลองบวก 2, บวก 3, บวก 5
   ● เช่น เส้นทาง 5 -> บวกอีก 3 = 8 (ได้ count = 2) → จำค่า 2 ไว้
   ● เส้นทาง 2 -> 2 -> 2 -> 2 = 8 (ได้ count = 4) → 4 มากกว่า 2 ไม่จำ
3. สุดท้ายจะตอบ 2 คือ 5 -> 3 (ตัด 2 ท่อน)
@ Time Complexity
- Big O = O(n^(targetLength/minCut)) 
  ● targetLength = ความยาวสายไฟทั้งหมด (เช่น 8)
  ● n = จำนวนขนาดท่อนที่ตัดได้ (ในที่นี้คือ 3 ขนาด: 2, 3, 5)
  ● minCut = จำนวนครั้งต่ำสุดที่ต้องตัด (ในที่นี้คือ 2 ครั้ง: 5 กับ 3)
- แต่ละระดับ แตกกิ่งได้ k ทางเลือก
*/