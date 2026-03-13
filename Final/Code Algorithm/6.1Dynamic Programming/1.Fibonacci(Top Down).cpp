#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชันคำนวณ Fibonacci แบบ Top-Down (Memoization)
long long fiboTopDown(int n, vector<long long>& memory){
    //@ 1. Base cases (กรณีพื้นฐาน)
    if(n == 0 || n == 1)
        return n;
    //@ 2. ถ้าเคยคำนวณค่าของลำดับที่ n ไว้แล้ว ให้ดึงค่าจาก memo มาใช้ได้เลย (ไม่ต้องคำนวณใหม่)
    if(memory[n] != -1)
        return memory[n];
    //@ 3. ถ้ายังไม่เคยคำนวณ ให้เรียก Recursion เพื่อหาค่า 
    //* และเมื่อได้ผลลัพธ์แล้ว ให้นำไปเก็บไว้ใน memo[n] ก่อนคืนค่ากลับไป
    memory[n] = fiboTopDown(n - 1, memory) + fiboTopDown(n - 2, memory);
    return memory[n];
}

int main(){
    int n;
    cin>>n;
    //* สร้าง Vector สำหรับเก็บค่า Memoization ขนาด n + 1 
    // และกำหนดค่าเริ่มต้นทุกช่องให้เป็น -1 (เพื่อใช้เช็คว่าช่องนี้ยังไม่เคยถูกคำนวณ)
    vector<long long> memory(n + 1, -1);
    long long result = fiboTopDown(n, memory);
    cout<<"Fibo("<<n<<") = "<<result<<endl;
    return 0;
}

/*
- Fibonacci แบบ Top-Down คือการใช้เทคนิค Memoization (จดจำสิ่งที่เคยทำไปแล้ว) เพื่อไม่ให้คอมพิวเตอร์
  ต้องคำนวณซ้ำซากในปัญหาเดิมๆ
@ คำศัพท์ 
* Memorization 
- คือเทคนิคการเพิ่มประสิทธิภาพ โดยการจดจำผลลัพธ์ของปัญหาย่อย (Subproblem) ที่คำนวณเสร็จแล้วไว้ในหน่วย
  ความจำ (Cache/Array/Hash Table) เพื่อนำมาใช้ซ้ำเมื่อต้องการคำนวณค่านั้นอีก ลดการคำนวณซ้ำซ้อนแบบ
  ซ้ำซาก (Redundant Computation) ช่วยเปลี่ยนเวลาการทำงานจาก Exponential ให้เป็น Linear ได้
@ แนวคิดหลัก (Top-Down with Memoization)
1. Base Case: ถ้า n = 0 ได้ 0 และ n = 1 ได้ 1
2. Check Memory: ก่อนจะคำนวณ ให้ดูในตารางก่อนว่าเคยคำนวณค่านี้ไปหรือยัง
3. Recursive Step: ถ้ายังไม่เคยคำนวณ ให้ใช้สูตร
    ● F(n) = F(n - 1) + F(n - 2)
4. Store Result: คำนวณเสร็จแล้วให้ "จดลง Memory" ก่อนจะส่งค่ากลับไป
@ Time Complexity
- T(n) ∈ O(n) → เร็วมาก ทำงานเป็นเส้นตรง
- เทียบกับแบบ Recursive ธรรมดา O(2^n) → ช้ามากเมื่อ n เพิ่มขึ้น
*/