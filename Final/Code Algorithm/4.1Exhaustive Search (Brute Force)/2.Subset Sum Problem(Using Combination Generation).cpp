#include <bits/stdc++.h>
using namespace std;

int fnCallCount = 0; //* นับจำนวนครั้งที่ฟังก์ชันถูกเรียกใช้ (2^n)

//? ฟังก์ชันตรวจสอบและพิมพ์ผลรวม
void checkAndPrint(int selectedIndices[], int currentSize, int arr[], int targetSum){
    int sum = 0;
    //* หาผลรวมจาก Index ที่เราเลือกเก็บไว้ใน selectedIndices
    for(int i = 0; i < currentSize; i++){
        sum += arr[selectedIndices[i]];
    }
    //* ถ้าผลรวมเท่ากับเป้าหมาย ให้แสดงผล
    if(sum == targetSum){
        for(int i = 0; i < currentSize; i++){
            cout<<arr[selectedIndices[i]]<<(i == currentSize - 1 ? "" : " + ");
        }
        cout<<" = "<<targetSum<<endl;
    }
}

/* 
@param 
 * selectedIndices: อาร์เรย์เก็บ "ตำแหน่ง" ของตัวเลขที่ถูกเลือก
 * currentDepth: บอกว่าตอนนี้เราเลือกตัวเลขมาแล้วกี่ตัว
 * n: จำนวนสมาชิกทั้งหมดในเซต
 * arr: อาร์เรย์ตัวเลขโจทย์
 * targetSum: ผลรวมที่ต้องการ
 */
void findCombinations(int selectedIndices[], int currentDepth, int n, int arr[], int targetSum){
    fnCallCount++;
    //* ทุกครั้งที่เข้ามา ให้ลองเช็คผลรวม (เพราะเซตย่อยมีขนาดตั้งแต่ 0 ถึง n)
    checkAndPrint(selectedIndices, currentDepth, arr, targetSum);
    //* หาจุดเริ่มต้นที่จะเลือกตัวถัดไป (เพื่อไม่ให้เลือกซ้ำตัวเดิมหรือย้อนกลับไปตัวก่อนหน้า)
    int startIdx = (currentDepth == 0) ? 0 : selectedIndices[currentDepth - 1] + 1;
    //* วนลูปเพื่อเลือกตัวเลขตัวถัดไปใส่ในตำแหน่งถัดไป (currentDepth)
    for(int i = startIdx; i < n; i++){
        selectedIndices[currentDepth] = i; //* บันทึกว่าเลือกตัวเลข Index ที่ i
        findCombinations(selectedIndices, currentDepth + 1, n, arr, targetSum); // ลงลึกไปเลือกตัวต่อไป
    }
}

int main(){
    int n = 5;
    int selectedIndices[n]; // * เก็บ Index ของตัวที่เลือก
    int arr[5] = {25, 10, 9, 2, 1};
    int targetSum = 12;
    cout<<"Looking for subsets that sum to "<<targetSum<<"..."<<endl;
    findCombinations(selectedIndices, 0, n, arr, targetSum);
    cout<<"Function Call Count = "<<fnCallCount<<endl;
    return 0;
}

/*
@ Vocabulary
1. Combination Generation (การสร้างวิธีจัดหมู่)
- สังเกตจากบรรทัด int startIdx = (currentDepth == 0) ? 0 : selectedIndices[currentDepth - 1] + 1;
● นี่คือเทคนิคการสร้าง Subsets โดยบังคับลำดับ (Lexicographical order) เพื่อป้องกันการเลือกซ้ำ เช่น 
  ถ้าเลือก {1, 2} ไปแล้ว จะไม่กลับมาเลือก {2, 1} อีก
● เทคนิคนี้ช่วยลดขนาดของ Search Space ลงได้มหาศาลเมื่อเทียบกับการสุ่มเลือกมั่วๆ
2. Incremental Construction: การค่อยๆ หยิบสมาชิกใส่ "ตะกร้า" (selectedIndices) ทีละชิ้น 
   และตรวจสอบผลลัพธ์ในทุกขั้นตอนที่หยิบ
3. Start Index (Pivot): ตัวควบคุมไม่ให้เลือกย้อนกลับไปตัวเดิม เพื่อป้องกันเซตซ้ำ เช่น {10, 2} กับ {2, 10}
4. Exhaustive Search (การค้นหาแบบครอบคลุม) โค้ดนี้จะแวะไปที่ ทุก Node ใน State Space Tree (เพราะ
   เรียก checkAndPrint ทุกครั้งที่เข้าฟังก์ชัน) เพื่อตรวจสอบว่า Subset ณ จุดนั้นๆ รวมกันได้ targetSum หรือไม่
5. Backtracking (การย้อนรอย) ใช้การ Recursive เพื่อลองเลือกสมาชิกทีละตัวลงไปใน State Space Tree 
   เมื่อทำงานในกิ่งนั้นจนสุด (หรือเรียกฟังก์ชันเสร็จ) มันจะทำการ "ย้อนกลับ" มาเพื่อเลือกตัวเลือกอื่นในลูป for ถัดไป
@ หลักการ
- การหา "ทุกเซตย่อย (All Subsets)" โดยใช้หลักการเดินหน้าลูกเดียว (Forward-Only Selection)
- โครงสร้าง Tree จะไม่ใช่ Binary Tree ที่แตกออกทีละ 2 กิ่งคงที่ แต่จะเป็น "Multi-way Tree" 
  ที่กิ่งจะค่อยๆ ลดลงตามจำนวนสมาชิกที่เหลือให้เลือก
- ตัวอย่าง: ถ้ามีเลข {25, 10, 9} 
  ● ชั้นแรกเลือกได้ 3 ทาง (25 หรือ 10 หรือ 9)
  ● ถ้าเลือก 10 ชั้นต่อไปจะเลือกได้แค่ {9} (เพราะ 25 อยู่ข้างหลัง ห้ามหันกลับไปหยิบ)
@ ภาพรวมการทำงาน (Tracing)
1. เริ่มที่ currentDepth = 0 (ตะกร้าว่าง):
    ● วนลูปเลือกตัวแรก (startIdx = 0): ลองหยิบ 25 (index 0)
    ● กระโดดไปหาตัวที่สอง (currentDepth = 1) โดยเริ่มหาตั้งแต่ index 1 เป็นต้นไป
2. การทำงานของ startIdx:
    ● ถ้าตัวล่าสุดที่หยิบคือ index 1 (เลข 10) ตัวต่อไปที่หยิบได้ต้องเริ่มที่ index 2 (เลข 9) เสมอ
    ● สิ่งนี้ทำให้เราได้เซต {10, 9} และจะไม่เกิดเซต {9, 10} ซ้ำขึ้นมา
3. การถอยกลับ (Backtracking):
    ● เมื่อลองจนสุดสายพานแล้ว จะถอยกลับมา (Return) เพื่อ "วาง" เลขตัวล่าสุด 
      แล้วขยับ Loop ไปหยิบเลขตัวถัดไปในระดับเดียวกันมาลองใหม่
@ ตัวอย่างการทำงาน
- มีข้อมูล 4 ตัว ลำดับการหยิบข้อมูลมองเป็น index มองในรูป (currentDepth, startIdx) เป็นดังนี้
    (0, 0) → [] ❌
    │
    ├── (1, 1) → [0] 🖼️
    │     │
    │     ├── (2, 2) → [0 1] 🖼️
    │     │     │
    │     │     ├── (3, 3) → [0 1 2] 🖼️
    │     │     │     │
    │     │     │     └── (4, 4) → [0 1 2 3] 🖼️
    │     │     │
    │     │     └── (3, 4) → [0 1 3] 🖼️
    │     │
    │     ├── (2, 3) → [0 2] 🖼️
    │     │     │
    │     │     └── (3, 4) → [0 2 3] 🖼️
    │     │
    │     └── (2, 4) → [0 3] 🖼️
    │
    ├── (1, 2) → [1] 🖼️
    │     │
    │     ├── (2, 3) → [1 2] 🖼️
    │     │     │
    │     │     └── (3, 4) → [1 2 3] 🖼️
    │     │
    │     └── (2, 4) → [1 3] 🖼️
    │
    ├── (1, 3) → [2] 🖼️
    │     │
    │     └── (2, 4) → [2 3] 🖼️
    │
    └── (1, 4) → [3] 🖼️
- หรือ (currentSize จะขึ้นๆ ลงๆ แต่ต่างกันแค่ 1 ของ Output ก่อน กับ หลัง)
    [∅]

    [0]
    [0 1]
    [0 1 2]
    [0 1 2 3]
    [0 1 3]
    [0 2]
    [0 2 3]
    [0 3]

    [1]
    [1 2]
    [1 2 3]
    [1 3]

    [2]
    [2 3]
    [3]

@ Time Complexity
- Big O = O(2^n) (เนื่องจากจำนวนเซตย่อยทั้งหมดของเซตที่มีสมาชิก n ตัวคือ 2^n)
*/
