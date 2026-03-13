#include <bits/stdc++.h>
using namespace std;

int N = 4; //* กำหนดขนาดบอร์ด 4x4

//? ฟังก์ชันสำหรับแสดงผลลัพธ์ ตำแหน่งของ Queen แต่ละตัวที่ปลอดภัย
void printcolumn(vector<int>& column){
    cout<<"Solution: ";
    for(int i = 0; i < N; i++)
        cout<<column[i]<<" ";
    cout<<"\n(Positions: ";
    for(int i = 0; i < N; i++) 
        cout<<"("<<i<<","<<column[i]<<") ";
    cout<<")\n"<<endl;
}

//? ฟังก์ชันตรวจสอบแนวทแยง (Diagonal Check)
bool isValid(vector<int>& column){
    for(int i = 0; i < N; i++){
        for(int j = i + 1; j < N; j++){
            //@ สูตรเช็คแนวทแยง: |row1 - row2| == |col1 - col2|
            //* ในตาราง 2 มิติ เส้นทแยงมุมจะมีค่าความชันเป็น 1 หรือ -1 เสมอ (ทำมุม 45 องศา)
            //  นั่นหมายความว่า ระยะห่างของแถว จะต้องเท่ากับ ระยะห่างของคอลัมน์
            if (abs(i - j) == abs(column[i] - column[j])){
                return false; //* ถ้าเท่ากัน แสดงว่าชนกันในแนวทแยง
            }
        }
    }
    return true;
}

//? ฟังก์ชัน Permutation ที่ปรับปรุงมาใช้กับ 4-Queens
//* column: อาเรย์เก็บตำแหน่งคอลัมน์
//* index: index ปัจจุบันที่กำลังพิจารณา
void generatePermutation(vector<int>& column, int index){
    //@ Base Case: เมื่อสลับตำแหน่งครบทุกตัวแล้ว (index == N)
    if (index == N){
        //! ก่อนพิมพ์ ต้องเช็คกฎของ Queen ก่อน
        if (isValid(column)){
            printcolumn(column);
        }
        return;
    }
    //@ Recursive Step: วนลูปสลับค่า
    for(int i = index; i < N; i++){
        //* 1. Swap: ลองสลับตำแหน่ง
        swap(column[index], column[i]);
        //* 2. Recurse: ทำตำแหน่งถัดไป
        generatePermutation(column, index + 1);
        //* 3. Backtrack: สลับคืนที่เดิม เพื่อให้รอบถัดไปถูกต้อง
        swap(column[index], column[i]);
    }
}

int main(){
    //* กำหนดค่าเริ่มต้นเป็น 0, 1, 2, 3 (ตามขนาด 4x4)
    vector<int> column(N);
    for(int i=0; i<N; i++) column[i] = i;
    cout<<"All solutions for "<<N<<"-Queens on "<<N<<"x"<<N<<" column:\n"<<endl;
    //* เรียกฟังก์ชันเริ่มจาก index 0
    generatePermutation(column, 0);
    return 0;
}

/*
- ในโค้ดของคุณ i และ row คือดัชนีของแถว ส่วน column[i] และ column[row] คือค่าที่เก็บไว้ 
  (ซึ่งก็คือหมายเลขคอลัมน์)
    ● abs(i - row) : คือ ระยะห่างระหว่างแถว ของ Queen ตัวที่เคยเช็คไปแล้ว กับ Queen ตัวปัจจุบัน
    ● abs(column[i] - column[row]) : คือ ระยะห่างระหว่างคอลัมน์ ของ Queen ทั้งสองตัว
    ● if (...) { return false; } : ถ้าสองค่านี้เท่ากัน แสดงว่าพวกมันอยู่ในแนวทแยงเดียวกัน (กินกันได้) 
      จึงส่งค่ากลับว่าไม่ปลอดภัย
@ ตัวอย่างให้เห็นภาพ (N=4)
- สมมติเรามี Queen 2 ตัว:
  ● ตัวแรก (i): อยู่ที่แถว 0 คอลัมน์ 1 → (0, 1)
  ● ตัวที่สอง (row): อยู่ที่แถว 2 คอลัมน์ 3 → (2, 3)
- ลองคำนวณตามสูตร:
  ● ระยะห่างแถว: |0 - 2| = 2
  ● ระยะห่างคอลัมน์: |1 - 3| = 2
- ผลลัพธ์: 2 = 2 (จริง!) แสดงว่าสองตัวนี้ ชนกันในแนวทแยง โค้ดจะ return false ทันที
*/
