#include <bits/stdc++.h>
using namespace std;
 
int fnCallCount = 0; //* นับจำนวนครั้งที่ฟังก์ชันถูกเรียกใช้
int tryCount = 0; //* นับจำนวนครั้งที่เราลองเลือกตัวเลขนี้ในลูป
int leafCount = 0; //* นับจำนวน subset ที่รอดมาจนครบชั้น
int ansCount = 0; //* นับจำนวน subset ที่ได้ผลรวมตรงตามเป้าหมาย

//? ฟังก์ชันนี้คือหัวใจหลัก (Recursive) ทำหน้าที่ "ตัดสินใจ" ทีละตัว
//* index: คือ "เข็มชี้" ว่าตอนนี้เรากำลังตัดสินใจที่ตัวเลขตัวไหน (0, 1, 2, 3, 4)
void generateSubsets(int binary[], int index, int n, int arr[], int currentSum, int targetSum){
    fnCallCount++;
    //@ Base Case 1: ถ้าได้ sum เท่ากับเป้าหมายแล้ว พิมพ์ผลลัพธ์และหยุดกิ่งนี้ทันที
    if(currentSum == targetSum){
        ansCount++;
        //* ส่วนนี้คือการจัดรูปแบบการพิมพ์ให้สวยงาม (เช่น "10 + 2 = 12")
        bool first = true;
        for(int i = 0; i < n; i++){
            if(binary[i] == 1){
                if(!first) cout<<" + "; //* พิมพ์เครื่องหมายบวก ถ้าไม่ใช่ตัวแรก
                cout<<arr[i];
                first = false;
            }
        }
        cout<<" = "<<targetSum<<endl;
        return;
    }
    //@ Base Case 2: ถ้าเดินจนครบทุกตัวแล้วแต่ sum ยังไม่ถึง
    if(index == n){
        leafCount++; //* นับ Subset ที่รอดมาจนครบชิ้น
        return;
    }
    tryCount++; //* นับจำนวนครั้งที่เราลองเลือกตัวเลขนี้
    //@ จุดแตกกิ่ง (Recursive Step) - ทำ Pruning
    //* ทางเลือกที่ 1: "เอา" ตัวเลขตำแหน่งนี้ (Set เป็น 1) 
    // จะหยิบได้ก็ต่อเมื่อบวกเข้าไปแล้ว currentSum ไม่เกิน targetSum
    if(currentSum + arr[index] <= targetSum){
        binary[index] = 1; //! ถ้าสลับเป็น 1 และ ข้างล่างเป็น 0 จะเริ่มจาก 0000... แทน 1111...
        generateSubsets(binary, index + 1, n, arr, currentSum + arr[index], targetSum); //* ขยับเข็ม (index+1) ไปทำตัวต่อไป
        //! currentSum + arr[index] อัพเดตผลรวมปัจจุบันใน function call ถัดไป
    }
    //* ทางเลือกที่ 2: "ไม่เอา" ตัวเลขตำแหน่งนี้ (Set เป็น 0)
    // การไม่หยิบไม่มีทางทำให้ currentSum เกิน ดังนั้นเดินต่อได้เสมอ
    binary[index] = 0;
    generateSubsets(binary, index + 1, n, arr, currentSum, targetSum); //* ขยับเข็ม (index+1) ไปทำตัวต่อไป
    
}

int main(){
    int n = 5; //* จำนวนสมาชิกทั้งหมด
    int binary[n]; //* Array ที่เก็บสถานะ (0 หรือ 1) ใช้แทนการเลือก/ไม่เลือก
    int arr[5] = {25, 10, 9, 2, 1}; 
    int targetSum = 12; //* เป้าหมายผลรวม
    generateSubsets(binary, 0, n, arr, 0, targetSum); //* เริ่มต้นเรียกฟังก์ชัน: เริ่มที่ index 0 (ตัวแรกสุด)
    cout<<"Function Call Count = "<<fnCallCount<<", Try Count = "<<tryCount<<", Leaf Count = "<<leafCount<<", Answer Count = "<<ansCount<<endl;
    return 0;
}

/*
- Pruning (การตัดแต่งกิ่ง) ใน Backtracking คือเทคนิคการ "เลิกเดินต่อ" ในเส้นทางที่เรารู้แน่ๆ แล้วว่า 
  "ไม่มีทางเจอคำตอบ" เพื่อลดจำนวนการเรียกฟังก์ชัน (Recursive Calls) ทำให้โปรแกรมทำงานเร็วขึ้นอย่างมหาศาล
@ ทำไมมันถึงไวขึ้น?
1. ไม่ต้องวนลูปใน checkAndPrint: เราส่ง currentSum ไปเรื่อยๆ ทำให้เช็คเงื่อนไขได้ในเวลา O(1)
2. Short-circuit: ทันทีที่ currentSum == targetSum เราสั่ง return เพื่อไม่ให้โปรแกรมไปเสียเวลาลอง 
   "หยิบ 0" หรือ "หยิบตัวที่เหลือ" ต่อไปอีก
3. การคัดกรองก่อนเข้า Recursion: if (currentSum + arr[index] <= targetSum) คือ main ของงานนี้ 
   เพราะมันจะทำลายความเป็น 2^n ทิ้งไปในกิ่งที่ตัวเลขมีค่ามากเกินไป
@ จุดที่ควรวางตัวนับ (Counter)
* จุดที่ 1: fnCallCount (วางที่หัวฟังก์ชัน)
- หน้าที่: นับจำนวนโหนดทั้งหมดที่โปรแกรม "ตัดสินใจเดินเข้าไป" จริงๆ
- ทำไมต้องนับ: เพื่อดูว่าจาก Brute Force เดิมที่ต้องรัน 2^{n+1}-1 ครั้ง (ในที่นี้คือ 31 ครั้ง) พอทำ Pruning 
  แล้วมันเหลือการทำงานจริงกี่ครั้ง (23 ครั้ง)
* จุดที่ 2: tryCount (วางก่อน if ที่เช็ค currentSum)
- หน้าที่: นับจำนวนครั้งที่โปรแกรม "พยายามจะหยิบ" ของชิ้นนั้น
- ทำไมต้องนับ: เพื่อให้เห็นว่ามีกี่ครั้งที่เรายั้งมือไว้ทัน ไม่กระโดดเข้าไปในฟังก์ชันถัดไปเพราะรู้ว่าค่าจะเกิน (12 ครั้ง)
* จุดที่ 3: leafCount (วางใน if(index == n))
- หน้าที่: นับจำนวน Subset ที่เป็นไปได้ทั้งหมดที่ "รอด" ไปจนจบกระบวนการเลือก
- ทำไมต้องนับ: เพื่อดูว่ามีกี่รูปแบบที่ค่าไม่เกินและพิจารณาครบทุกชิ้น (9 ครั้ง)
* จุดที่ 4: ansCount (วางใน if(currentSum == targetSum))
- หน้าที่: นับจำนวน Subset ที่ได้ผลรวมตรงตามเป้าหมาย
- ทำไมต้องนับ: เพื่อดูว่ามีกี่รูปแบบที่ตรงตามเงื่อนไข (2 ครั้ง)
! fnCallCount = tryCount + leafCount + ansCount → เพราะทุกครั้งที่ฟังก์ชันถูกรัน มันจะต้องผ่าน 1-3 กรณีนี้เสมอ
*/