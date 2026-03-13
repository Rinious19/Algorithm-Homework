#include <bits/stdc++.h>
using namespace std;

//* ฟังก์ชันเสริม C(i, j) ตามที่โจทย์กำหนด
long long C(int i, int j){
    return 2*i + j;
}

//? ฟังก์ชัน P คำนวณแบบ Top-Down DP (Memoization)
long long P_Top_Down(int i, int j, vector<vector<long long>>& memory){
    //@ 1. จัดการ Base Cases → P(0, j) = 3j, P(i, 0) = 2i
    if(i == 0) return 3*j;
    else if(j == 0) return 2*i;
    //@ 2. ถ้าเคยคำนวณ P(i, j) ไว้แล้ว ให้ดึงจากตาราง memo มาตอบเลย
    if(memory[i][j] != -1)
        return memory[i][j];
    //@ 3. ถ้ายังไม่เคย ให้คำนวณทั้ง 3 choice ตามสมการ Recurrence Relation และเลือก choice ที่ค่าน้อยที่สุด
    //* P(i, j) = min{P(i - 1, j) + 2, P(i, j - 1) + 3, P(i - 1, j - 1) + C(i, j)}
    memory[i][j] = min({P_Top_Down(i - 1, j, memory) + 2, P_Top_Down(i, j - 1, memory) + 3, 
                   P_Top_Down(i - 1, j - 1, memory) + C(i, j)});
    return memory[i][j];
}

int main(){
    int i, j;
    cin>>i>>j;
    //* สร้างตาราง 2 มิติ ขนาด (i + 1) x (j + 1) และกำหนดค่าเริ่มต้นทุกช่องเป็น -1
    vector<vector<long long>> memory(i + 1, vector<long long>(j + 1, -1));
    long long result = P_Top_Down(i, j, memory);
    cout<<"P("<<i<<", "<<j<<") = "<<result<<endl;
    return 0;
}

/*
* Test Case1
    Input: 10 5
    Output: 33
* Test Case2
    Input: 2 3
    Output: 11
@ ตัวอย่าง F(6, 4) ตัวอย่างตารางเมื่อมีขนาด (n + 1) x (k + 1) 
! k > n ได้จึงต้องมีขนาด (n + 1) x (k + 1) 
* ไม่อัปเดตค่า ตำแหน่งที่เป็น Basecase ให้มีค่าเป็น 1 ใน memory 
         0       1       2       3       4       5      
0   |   -1      -1      -1      -1      -1      -1
1   |   -1       3       6       9      12      15
2   |   -1       5       8      11      14      17
3   |   -1       7      10      13      16      19
4   |   -1       9      12      15      18      21
5   |   -1      11      14      17      20      23
6   |   -1      13      16      19      22      25
7   |   -1      15      18      21      24      27
8   |   -1      17      20      23      26      29
9   |   -1      19      22      25      28      31
10  |   -1      21      24      27      30      33
* อัปเดตค่า ตำแหน่งที่เป็น Basecase ให้มีค่าเป็น 2i หรือ 3j ใน memory 
         0       1       2       3       4       5      
0   |    0       3       6       9      12      15
1   |    2       3       6       9      12      15
2   |    4       5       8      11      14      17
3   |    6       7      10      13      16      19
4   |    8       9      12      15      18      21
5   |   10      11      14      17      20      23
6   |   12      13      16      19      22      25
7   |   14      15      18      21      24      27
8   |   16      17      20      23      26      29
9   |   18      19      22      25      28      31
10  |   20      21      24      27      30      33
*/