#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชัน Counting Sort
void countingSort(char arr[], int n){
    int maxValue = *max_element(arr, arr + n);
    int minValue = *min_element(arr, arr + n);
    int range = maxValue - minValue + 1; //* หาช่วงของข้อมูล
    vector<int> count(range);
    for(int i=0;i<n;i++) //* นับความถี่
        count[arr[i] - minValue]++;
    for(int i=1;i<range;i++) //* หาความถี่สะสม
        count[i] += count[i - 1];
    vector<int> output(n);
    for(int i=n-1;i>=0;i--){ //* ทำการเรียงข้อมูล
        int index = arr[i] - minValue;
        int pos = count[index] - 1;
        output[pos] = arr[i];
        count[index]--;
    }
    for(int i=0;i<n;i++)
        arr[i] = output[i];
}

//? ฟังก์ชันแสดงผล
void printPermutation(char result[], int n){
    for(int i = 0; i < n; i++)
        cout << result[i] << " ";
    cout << endl;
}

//? ฟังก์ชัน Permutation แบบเรียงตามพจนานุกรม (Lexicographic)
//* original[]: อาเรย์ต้นฉบับที่เรียงแล้ว
//* result[]: อาเรย์สำหรับเก็บผลลัพธ์ทีละตัว
//* used[]: อาเรย์เช็คว่า index ไหนใช้ไปแล้ว
//* index: ความลึกของการตัดสินใจ
void generatePermutation(char original[], char result[], int used[], int index, int n){
    //@ Base Case: ถ้าเลือกครบ n ตัวแล้ว
    if(index == n){
        printPermutation(result, n);
        return;
    }
    //@ Recursive Step:
    //* วนลูปตั้งแต่ตัวแรกถึงตัวสุดท้าย (เพราะ input เราเรียงมาแล้ว 0->n)
    for(int i = 0; i < n; i++){
        //* ถ้าตัวที่ i ยังไม่ถูกใช้
        if(used[i] == 0){
            //* 1. เลือกตัวนี้
            used[i] = 1; // ทำเครื่องหมายว่าใช้แล้ว
            result[index] = original[i]; // เอาค่ามาใส่ในคำตอบ
            //* 2. ไปตัดสินใจตำแหน่งถัดไป (index + 1)
            generatePermutation(original, result, used, index + 1, n);
            //* 3. Backtrack (สำคัญมาก!): คืนค่าเพื่อให้รอบถัดไปของลูปใช้งานได้
            used[i] = 0; 
        }
    }
}

int main(){
    int n;
    cin >> n;
    if(n >= 1 && n <= 26){
        char original[n];
        for(int i = 0; i < n; i++) cin >> original[i];
        //* 1. เรียงข้อมูลให้เป็น A-Z ก่อน (สำคัญที่สุดสำหรับ Lexicographic)
        countingSort(original, n);
        //* 2. เตรียมตัวแปรสำหรับ Recursion
        char result[n]; // ที่พักข้อมูล
        int used[n]; // เช็คว่าใช้ไปรึยัง
        //* set ค่าเริ่มต้นให้ used เป็น 0 (false) ทั้งหมด
        for(int i=0; i<n; i++) used[i] = 0; 
        //* 3. เริ่มรัน
        generatePermutation(original, result, used, 0, n);
    }
    return 0;
}

/*
@ Vocabulary
1. Permutation (การเรียงสับเปลี่ยน): การนำสมาชิกทั้งหมดในชุดข้อมูลมา "จัดลำดับใหม่" โดยลำดับมีความสำคัญ 
  (เช่น {1, 2} ไม่เหมือนกับ {2, 1})
2. Swap & Fix: หลักการทำงานหลักของโค้ดนี้ คือการเลือกสมาชิกมาวาง "ล็อคตำแหน่ง" (Fix) ไว้ที่ index ปัจจุบัน 
  โดยการสลับ (Swap) กับสมาชิกตัวอื่นๆ ที่เหลือ แล้วปล่อยให้ Recursive ไปจัดการตำแหน่งถัดไป
3. Backtracking (การย้อนรอย): หลังจาก Recursive ลงไปจนสุดสายและทำงานเสร็จแล้ว ต้องทำการ Swap กลับ
  (Undo) เพื่อคืนค่าอาเรย์ให้เป็นสภาพเดิม เพื่อให้ Loop รอบถัดไปสามารถเลือกสลับตัวเลขได้อย่างถูกต้อง
4. Lexicographical Order (ลำดับพจนานุกรม): การเรียงลำดับข้อมูลตามลักษณะคล้ายการเรียงคำในพจนานุกรม
   เช่น {A, B, C} จะเรียงเป็น {A, B, C}, {A, C, B}, {B, A, C}, {B, C, A}, {C, A, B}, {C, B, A}
   คือ ขึ้นต้นด้วย A มาก่อนเสมอ ถัดไปคือ B และสุดท้ายคือ C
@ หลักการ
- มีกฎ 3 ข้อเพื่อให้ได้ผลลัพธ์เรียงตามพจนานุกรม (Lexicographic):
1. เรียงก่อนเริ่ม (Pre-sort): เราต้องเรียงข้อมูลขาเข้า (permute) ให้เป็น ก-ฮ (น้อยไปมาก) ก่อนเสมอ เพื่อให้
   การหยิบครั้งแรกสุด เราจะได้ตัวอักษรที่น้อยที่สุด (เช่น 'A') เสมอ
2. เลือกตัวที่ว่าง และน้อยที่สุด (Greedy Selection):ในแต่ละขั้นตอน (Depth) เราจะวนลูปหาตัวอักษรจากซ้าย
   ไปขวา (original[0] ถึง original[n-1])ถ้าเจอตัวที่ ยังไม่ถูกใช้ (used[i] == 0) หยิบตัวนั้นทันที! 
   เพราะมันคือตัวที่มีค่าน้อยที่สุดที่เหลืออยู่ ณ ขณะนั้น
3. จำแล้วลืม (State Management): 
    ● Mark: เมื่อหยิบมาใส่ result ต้องติ๊ก used ว่าใช้แล้ว เพื่อไม่ให้ชั้นถัดไปหยิบซ้ำ 
    ● Unmark (Backtrack): เมื่อทำจนสุดทางแล้วย้อนกลับมา ต้องลบติ๊ก used ออก เพื่อให้ Loop รอบถัดไป
      สามารถหยิบตัวนี้ไปใช้ในตำแหน่งอื่นได้
@ ภาพรวมการทำงาน (Tracing)
- เพื่อให้เห็นภาพชัดเจน สมมติ Input คือ n=3 และตัวอักษรคือ {'A', 'B', 'C'}
- เราจะเรียก generatePermutation(..., depth=0)
- เริ่มทำงาน:
* Depth 0 (ช่องแรก):
    ● Loop เจอ A (ว่าง) → หยิบ A ใส่ result[0] → Mark A → เรียก Depth 1
        * Depth 1 (ช่องสอง):
            ● Loop เจอ A (ใช้แล้ว) ข้าม
            ● Loop เจอ B (ว่าง) → หยิบ B ใส่ result[1] → Mark B → เรียก Depth 2
            * Depth 2 (ช่องสาม):
                ● Loop เจอ A, B (ใช้แล้ว) ข้าม
                ● Loop เจอ C (ว่าง) → หยิบ C ใส่ result[2] → Mark C → เรียก Depth 3
                * Depth 3 (สุดทาง):
                    ● index == n แล้ว! พิมพ์ "A B C"
                    ● return กลับไป Depth 2
            * Back to Depth 2:
                ● Backtrack: คืนค่า C (Unmark C)
                ● Loop จบแล้ว (ไม่มีตัวอื่นให้เลือก) → return กลับไป Depth 1
        * Back to Depth 1:
            ● Backtrack: คืนค่า B (Unmark B)
            ● Loop ต่อไป... เจอ C (ว่าง) → หยิบ C ใส่ result[1] แทน (ตอนนี้ได้ A C _)
            ● เรียก Depth 2 ใหม่... (จะได้ผลลัพธ์เป็น "A C B")
* สรุปลำดับการพิมพ์ที่จะเกิดขึ้น:
    ● A -> B -> C (พิมพ์ A B C)
    ● A -> C -> B (พิมพ์ A C B)
    ● B -> A -> C (พิมพ์ B A C) ... ไปเรื่อยๆ จนครบ
@ ตัวอย่างการทำงาน
- ข้อมูล 1 2 3
    generate(index=0)  used=[0 0 0]
    │
    ├── i=0 → choose 1
    │   result=[1 _ _]  used=[1 0 0]
    │   generate(index=1)
    │   │
    │   ├── i=1 → choose 2
    │   │   result=[1 2 _]  used=[1 1 0]
    │   │   generate(index=2)
    │   │   │
    │   │   └── i=2 → choose 3
    │   │       result=[1 2 3]  used=[1 1 1]
    │   │       generate(index=3) → PRINT
    │   │
    │   └── i=2 → choose 3
    │       result=[1 3 _]  used=[1 0 1]
    │       generate(index=2)
    │       │
    │       └── i=1 → choose 2
    │           result=[1 3 2]  used=[1 1 1]
    │           generate(index=3) → PRINT
    │
    ├── i=1 → choose 2
    │   result=[2 _ _]  used=[0 1 0]
    │   generate(index=1)
    │   │
    │   ├── i=0 → choose 1
    │   │   result=[2 1 _]  used=[1 1 0]
    │   │   generate(index=2)
    │   │   │
    │   │   └── i=2 → choose 3
    │   │       result=[2 1 3]  used=[1 1 1]
    │   │       generate(index=3) → PRINT
    │   │
    │   └── i=2 → choose 3
    │       result=[2 3 _]  used=[0 1 1]
    │       generate(index=2)
    │       │
    │       └── i=0 → choose 1
    │           result=[2 3 1]  used=[1 1 1]
    │           generate(index=3) → PRINT
    │
    └── i=2 → choose 3
        result=[3 _ _]  used=[0 0 1]
        generate(index=1)
        │
        ├── i=0 → choose 1
        │   result=[3 1 _]  used=[1 0 1]
        │   generate(index=2)
        │   │
        │   └── i=1 → choose 2
        │       result=[3 1 2]  used=[1 1 1]
        │       generate(index=3) → PRINT
        │
        └── i=1 → choose 2
            result=[3 2 _]  used=[0 1 1]
            generate(index=2)
            │
            └── i=0 → choose 1
                result=[3 2 1]  used=[1 1 1]
                generate(index=3) → PRINT

@ Time Complexity
- Big O = O(n!) (เพราะตำแหน่งแรกเลือกได้ n วิธี, ตำแหน่งสอง n-1 วิธี, ไปเรื่อยๆ จนถึง 1)
*/