#include <bits/stdc++.h>
using namespace std;

long long F_Top_Down(int n, int k, vector<vector<long long>>& memory){
    //@ 1. จัดการ Base Cases → F(n, 0) = F(n, 1) = F(n, n) = 1 
    if(k == 0 || k == 1 || k == n) 
        return 1;
    //@ 2. ถ้าเคยคำนวณแล้ว ให้ดึงค่าจากตาราง memo ไปใช้
    if(memory[n][k] != -1)
        return memory[n][k];
    //@ 3. ถ้ายังไม่เคย ให้คำนวณตามสมการ แล้วเก็บลงตารางก่อน return
    //* F(n, k) = F(n - 1, k) + F(n - 1, k - 2)
    memory[n][k] = F_Top_Down(n - 1, k, memory) + F_Top_Down(n - 1, k - 2, memory); 
    return memory[n][k];
}

int main(){
    int n, k;
    cin>>n>>k;
    if(n < k) return 0;
    //* สร้างตาราง 2 มิติ ขนาด (n+1) x (k+1) ใส่ค่าเริ่มต้นเป็น -1
    vector<vector<long long>> memory(n + 1, vector<long long>(k + 1, -1));
    long long result = F_Top_Down(n, k, memory);
    cout<<"F("<<n<<", "<<k<<") = "<<result<<endl;
    return 0;
}

/*
* Test Case1
    Input: 6 4
    Output: 8
@ ตัวอย่าง F(6, 4) ตัวอย่างตารางเมื่อมีขนาด (n + 1) x (n + 1)
* ไม่อัปเดตค่า ตำแหน่งที่เป็น Basecase ให้มีค่าเป็น 1 ใน memory 
        0       1       2       3       4       5       6
0   |  -1      -1      -1      -1      -1      -1      -1
1   |  -1      -1      -1      -1      -1      -1      -1
2   |  -1      -1      -1      -1      -1      -1      -1
3   |  -1      -1       2      -1      -1      -1      -1
4   |  -1      -1       3      -1      -1      -1      -1
5   |  -1      -1       4      -1       4      -1      -1
6   |  -1      -1      -1      -1       8      -1      -1
* อัปเดตค่า ตำแหน่งที่เป็น Basecase ให้มีค่าเป็น 1 ใน memory 
        0       1       2       3       4       5       6
0   |  -1      -1      -1      -1      -1      -1      -1
1   |  -1      -1      -1      -1      -1      -1      -1
2   |   1      -1       1      -1      -1      -1      -1
3   |   1      -1       2      -1      -1      -1      -1
4   |   1      -1       3      -1       1      -1      -1
5   |  -1      -1       4      -1       4      -1      -1
6   |  -1      -1      -1      -1       8      -1      -1
*/