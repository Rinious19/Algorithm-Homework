#include <bits/stdc++.h>
using namespace std;

unsigned long long fiboBottomUp(int n){
    //@ สร้างตารางเก็บคำตอบตั้งแต่ 0 ถึง n
    vector<unsigned long long> memory(n + 1, -1);
    //* กำหนดค่าเริ่มต้น (Base Cases)
    memory[0] = 0;
    memory[1] = 1;
    //* วนลูปสร้างคำตอบจากล่างขึ้นบน
    for(int i = 2; i <= n; i++)
        memory[i] = memory[i - 1] + memory[i - 2];
    return memory[n]; 
}

int main(){
    int n;
    cin>>n;
    unsigned long long result = fiboBottomUp(n);
    cout<<"Fibo("<<n<<") = "<<result<<endl;
    return 0;
}

/*
- Fibonacci แบบ Bottom-Up (หรือที่เรียกว่า Tabulation) เป็นวิธีที่ทรงพลังในสาย Dynamic Programming 
  แทนที่เราจะเริ่มจากปัญหาใหญ่แล้วแตกย่อยลงไป (แบบ Top-Down) เราจะเริ่มสร้างจาก "ฐาน" ขึ้นไปหาคำตอบ
  ที่ต้องการ เหมือนการต่อเลโก้จากพื้นขึ้นไปนั่นเอง
@ แนวคิดหลัก (Bottom-Up / Tabulation)
1. Iterative Approach: ใช้การวนลูป for แทนการใช้ Recursion ทำให้ไม่ต้องกังวลเรื่อง Stack Overflow
2. Table (DP Table): สร้างตาราง (Array) เพื่อเก็บค่า F(0) ไปจนถึง F(n)
3. Base Cases: กำหนดค่าเริ่มต้น dp[0] = 0 และ dp[1] = 1
4. Fill the Table: ใช้ลูปคำนวณค่าถัดไปจากผลรวมของสองค่าก่อนหน้าตามสูตร:
    ● F[i] = F[i - 1] + F[i - 2]
@ Time Complexity
- T(n) ∈ O(n) → เร็วมาก ทำงานเป็นเส้นตรง
- เทียบกับแบบ Recursive ธรรมดา O(2^n) → ช้ามากเมื่อ n เพิ่มขึ้น
- เทียบกับแบบ Top-Down (Memoization) → Bottom-Up ประสิทธิภาพดีกว่า, ไม่เสี่ยง Stack Overflow
*/