#include <bits/stdc++.h>
using namespace std;

unsigned long long C_Bottom_Up(int n, int k){
    //* ใช้ Array 1 มิติ ขนาด k+1
    vector<unsigned long long> memory(k + 1, 0);
    memory[0] = 1; //* Base case: C(n, 0) = 1
    for(int i = 0; i <= n; i++){
        //! อัปเดตจากหลังมาหน้า (j ไล่จาก min(i, k) ถอยหลังมา 1)
        for(int j = min(i, k); j > 0; j--)
            memory[j] = memory[j - 1] + memory[j];
    }
    return memory[k];
}


int main(){
    int n, k;
    cin>>n>>k;
    if(k < 0 || k > n){
        cout<<"ค่า k ต้องอยู่ระหว่าง 0 ถึง n"<<endl;
        return 0;
    } 
    unsigned long long result = C_Bottom_Up(n, k);
    cout<<"C("<<n<<", "<<k<<") = "<<result<<endl;
    return 0;
}

/*
* ลดการใช้ Memory ให้เหลือแค่ O(k) (Space Optimization)
- ถ้าเราสังเกตตาราง DP ดีๆ การคำนวณแถวปัจจุบัน (แถวที่ i) เราใช้ข้อมูลจากแถวที่แล้ว (แถวที่ i-1) เท่านั้น 
  แถวที่เก่ากว่านั้นเราไม่ได้ใช้เลย! 
- ดังนั้น เราสามารถยุบตาราง 2 มิติ ให้เหลือแค่ Array 1 มิติขนาด k+1 ได้ โดยมีข้อควรระวังคือ ต้องอัปเดตค่า
  จากหลังมาหน้า (จากขวาไปซ้าย) เพื่อไม่ให้ข้อมูลเก่าถูกทับก่อนที่จะถูกนำไปใช้คำนวณครับ
*/