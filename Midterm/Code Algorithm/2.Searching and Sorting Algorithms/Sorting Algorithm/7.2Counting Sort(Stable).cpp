#include <iostream>
#include <vector>
#include <algorithm> //* สำหรับ min_element, max_element
using namespace std;

void optimizedCountingSort(vector<int>& arr){
    int n = arr.size();
    if (n == 0) return;
    //@ 1. หาค่าต่ำสุด (Min) และ สูงสุด (Max)
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    //@ 2. คำนวณขนาดช่วง (Range) ที่ต้องใช้จริง
    //* เช่น 10 ถึง 15 -> ขนาดคือ 15 - 10 + 1 = 6 ช่อง
    int range = maxVal - minVal + 1;
    //@ 3. สร้าง Count Array ตามขนาดช่วงจริง
    vector<int> count(range, 0);
    //@ 4. นับความถี่ (Count)
    //! จุดสำคัญ: ต้องลบ minVal เพื่อ Map ค่าให้เริ่มที่ index 0 ***
    for(int i = 0; i < n; i++){
        int index = arr[i] - minVal; 
        count[index]++;
    }
    //@ 5. ผลรวมสะสม (Cumulative Sum)
    for(int i = 1; i < range; i++)
        count[i] += count[i - 1];
    //@ 6. สร้าง Output (วนลูปย้อนหลังเพื่อความ Stable)
    //* การวนจากหลังมาหน้า ทำให้ตัวที่อยู่หลังสุด ได้ที่นั่งหลังสุดในกลุ่มตัวเอง จึงรักษาลำดับสัมพัทธ์เดิมไว้ได้
    vector<int> output(n);
    for(int i = n - 1; i >= 0; i--){
        int val = arr[i];
        int index = val - minVal; //* แปลงค่าเป็น index ใน count array
        int position = count[index] - 1; //* ลบ 1 เพราะ index เริ่มที่ 0
        output[position] = val;
        count[index]--; //* ลดค่าลง
    }
    //@ 7. ก๊อปปี้กลับ
    for(int i = 0; i < n; i++)
        arr[i] = output[i];
}

int main(){
    //* ตัวอย่างที่มีเลขเยอะๆ และเลขติดลบ
    vector<int> data = {1005, 1002, -5, 1002, -2, 1005, -5};
    cout<<"Original: ";
    for(int x : data) 
        cout<<x<<" ";
    cout<<endl;
    optimizedCountingSort(data);
    cout<<"Sorted:   ";
    for(int x : data) 
        cout<<x<<" ";
    cout<<endl;
    return 0;
}

/*
- Counting Sort แบบ Stable (Offset) คืออัลกอริทึมการเรียงลำดับที่พัฒนาขึ้นมาเพื่อแก้จุดอ่อน 2 อย่างของ
  แบบดั้งเดิม:
    ● Offset (การเลื่อนค่า): แก้ปัญหาเรื่อง "เปลืองหน่วยความจำ" และ "รองรับเลขติดลบ" โดยการปรับจุดเริ่มต้น
                          การนับ จากเดิมเริ่มที่ 0 ให้ไปเริ่มที่ "ค่าต่ำสุดของข้อมูล" แทน
    ● Stable (ความเสถียร): แก้ปัญหาเรื่อง "ลำดับของข้อมูลที่ซ้ำกัน" โดยการใช้เทคนิคผลรวมสะสม 
                         (Cumulative Sum) และวางข้อมูลจากหลังมาหน้า เพื่อให้ข้อมูลที่มีค่าเท่ากัน ตัวที่
                         มาก่อนยังคงอยู่ข้างหน้าเหมือนเดิม
@ แนวคิดหลัก
- แทนที่จะเอาตัวเลขมาเทียบกันทีละคู่เหมือน Bubble / Selection เราทำแบบนี้แทน:
* 1. หาค่า ต่ำสุด (min) และ ค่าสูงสุด (max) ใน array 
    → เพื่อรู้ช่วงของข้อมูล และเตรียมเลื่อนค่า (offset) ให้เริ่มจากศูนย์
* 2. คำนวณ offset = -min
    →  index = arr[i] - min = arr[i] - offset
    → เพื่อเปลี่ยนค่าติดลบให้กลายเป็น index ที่ใช้ได้ใน array
* 3. สร้าง array count[] ขนาด (max - min + 1)
    → ใช้สำหรับ “นับจำนวนครั้งที่แต่ละค่าปรากฏ”
* 4. นับความถี่ (Count)
    → วน array เดิม → เจอเลขอะไร ก็เพิ่ม count ของเลขนั้น (โดยใช้ offset)
* 5. นับผลรวมสะสม (Cumulative Sum)
    → วน count[] จาก index 1 ถึง end
    → count[i] = count[i] + count[i - 1]
* 6. สร้าง array output[] ขนาด n
    → วน array เดิมจากหลังมาหน้า (i = n-1 ถึง 0)
    → หา index ใน count[] ด้วย offset
    → วาง arr[i] ลง output[count[index] - 1]
    → ลด count[index] ลง 1 
* 7. ก๊อปปี้ค่าใน output[] กลับไปที่ arr[]
@ Time Complexity (ความซับซ้อนของเวลา)
- Time Complexity: O(n + k) ใน ทุกกรณี (Best, Average, Worst) 
  ● n คือจำนวนข้อมูลทั้งหมด (ใช้ตอนวนลูปนับ)
  ● k คือค่าน้อยสุดถึงมากสุดของข้อมูล (ใช้ตอนวนลูปสร้างตารางนับและเขียนกลับ) k = max - min + 1
  ● มันเร็วกว่า O(n log n) มาก ถ้าช่วงของเลข (k) ไม่กว้างจนเกินไป
@ สิ่งที่เปลี่ยนแปลงและข้อดี
* 1. การจองพื้นที่ (Memory Efficient):
    ● แบบเดิม: ต้องจองขนาด maxVal + 1 (ถ้ามีเลข 1000 ก็ต้องจอง 1001 ช่อง ทั้งที่มีข้อมูลนิดเดียว)
    ● แบบใหม่: จองขนาด maxVal - minVal + 1 (จองเท่าช่วงข้อมูลที่มีอยู่จริง)
* 2. การแปลง Index (Mapping):
- ทุกครั้งที่จะเรียกใช้ count เราจะใช้ arr[i] - minVal
- เช่น ข้อมูล [100, 102] โดย minVal = 100
    ● เลข 100 จะถูกเก็บที่ count[100 - 100] = count[0]
    ● เลข 102 จะถูกเก็บที่ count[102 - 100] = count[2]
* 3. รองรับเลขติดลบ:
- เช่น ข้อมูล [-5, -2] โดย minVal = -5
- เลข -5 จะอยู่ที่ count[-5 - (-5)] = count[0] (กลายเป็นบวก ใช้เป็น index ได้)
@ ตัวอย่าง
- ❌ = จบลูป while, ✅ ผ่าน condition ลูป while
arr = [94, 92, 92, 98, 93, 93, 90]
    * 1. หาค่า max, min, range
        - max = 98
        - min = 90
        - range = 98 - 90 + 1 = 9
    * 2. สร้าง count array
        - count[range] = count[9] = [0,0,0,0,0,0,0,0,0]
        - index: 0 1 2 3 4 5 6 7 8
        - count: 0 0 0 0 0 0 0 0 0
    * 3. นับความถี่
        - เจอ 94 → index = 94 - 90 → count[4]++ → count = [0,0,0,0,1,0,0,0,0]
        - เจอ 92 → index = 92 - 90 → count[2]++ → count = [0,0,1,0,1,0,0,0,0]
        - เจอ 92 → index = 92 - 90 → count[2]++ → count = [0,0,2,0,1,0,0,0,0]
        - เจอ 98 → index = 98 - 90 → count[8]++ → count = [0,0,2,0,1,0,0,0,1]
        - เจอ 93 → index = 93 - 90 → count[3]++ → count = [0,0,2,1,1,0,0,0,1]
        - เจอ 93 → index = 93 - 90 → count[3]++ → count = [0,0,2,2,1,0,0,0,1]
        - เจอ 90 → index = 90 - 90 → count[0]++ → count = [1,0,2,2,1,0,0,0,1]
        - count = [1,0,2,2,1,0,0,0,1]
    * 4. ผลรวมสะสม
        - count[0] = 1
        - count[1] = 1 + 0 = 1
        - count[2] = 1 + 2 = 3
        - count[3] = 3 + 2 = 5
        - count[4] = 5 + 1 = 6
        - count[5] = 6 + 0 = 6
        - count[6] = 6 + 0 = 6
        - count[7] = 6 + 0 = 6
        - count[8] = 6 + 1 = 7
        - count = [1,1,3,5,6,6,6,6,7]
        - หมายความว่า:
          ● มี 1 ตัวที่น้อยกว่าหรือเท่ากับ 90 
          ● มี 1 ตัวที่น้อยกว่าหรือเท่ากับ 91 
          ● มี 3 ตัวที่น้อยกว่าหรือเท่ากับ 92 
          ● มี 5 ตัวที่น้อยกว่าหรือเท่ากับ 93
          ● มี 6 ตัวที่น้อยกว่าหรือเท่ากับ 94
          ● ...
        - ตำแหน่งสุดท้ายของข้อมูลแต่ละค่าใน output array จะอยู่ที่ count[value - minVal] - 1 เช่น: 
            ● ค่า 90 → ตำแหน่งสุดท้ายที่ index 0 (count[0]-1=0)
            ● ค่า 92 → ตำแหน่งสุดท้ายที่ index 2 (count[2]-1=2)
            ● ค่า 93 → ตำแหน่งสุดท้ายที่ index 4 (count[3]-1=4)
            ● ค่า 94 → ตำแหน่งสุดท้ายที่ index 5 (count[4]-1=5)
            ● ค่า 98 → ตำแหน่งสุดท้ายที่ index 6 (count[8]-1=6)
    * 5. สร้าง output array (วนจากหลังมาหน้า)
        ● index = arr[i] - minVal โดย minVal = 90
        ● position = count[index] - 1
        ● count = [1,1,3,5,6,6,6,6,7]
        ! ลด count[index] ลง 1 ทุกครั้งหลังใช้ เพื่อเตรียมตำแหน่งถัดไปของค่าเดียวกันใน Array output
        - i = 6: val = 90, index = 0, position = count[0]-1=0 → output[0]=90, count[0]--
          → count = [0,1,3,5,6,6,6,6,7]
          → output = [90, 0, 0, 0, 0, 0, 0]
        - i = 5: val = 93, index = 3, position = count[3]-1=4 → output[4]=93, count[3]--
          → count = [0,1,3,4,6,6,6,6,7]
          → output = [90, 0, 0, 0, 93, 0, 0]
        - i = 4: val = 93, index = 3, position = count[3]-1=3 → output[3]=93, count[3]--
          → count = [0,1,3,3,6,6,6,6,7]
          → output = [90, 0, 0, 93, 93, 0, 0]
        - i = 3: val = 98, index = 8, position = count[8]-1=6 → output[6]=98, count[8]--
          → count = [0,1,3,3,6,6,6,6,6]
          → output = [90, 0, 0, 93, 93, 0, 98]
        - i = 2: val = 92, index = 2, position = count[2]-1=2 → output[2]=92, count[2]--
          → count = [0,1,2,3,6,6,6,6,6]
          → output = [90, 0, 92, 93, 93, 0, 98]
        - i = 1: val = 92, index = 2, position = count[2]-1=1 → output[1]=92, count[2]--
          → count = [0,1,1,3,6,6,6,6,6]
          → output = [90, 92, 92, 93, 93, 0, 98]
        - i = 0: val = 94, index = 4, position = count[4]-1=5 → output[5]=94, count[4]--
          → count = [0,1,1,3,5,6,6,6,6]
          → output = [90, 92, 92, 93, 93, 94, 98]
    * 6. ก๊อปปี้กลับ
        - arr = [90, 92, 92, 93, 93, 94, 98]
*/