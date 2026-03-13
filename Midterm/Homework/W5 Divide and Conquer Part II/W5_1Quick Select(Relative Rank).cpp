#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชันแบ่งส่วน (Partition) → จัด pivot ให้อยู่ตำแหน่งที่ถูกต้อง, และคืน index ของ pivot กลับมา
int partition(vector<int>& arr, int low, int high){
    int mid = (low + high) / 2;
    //@ หา Median ของ 3 ค่า (low, mid, high) และจัดเรียงเบื้องต้น
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    //* ตอนนี้ arr[mid] คือค่ามัธยฐาน (Median)
    //! สลับ Median ไปไว้ตัวแรกสุด(Hoare Partition) เพื่อใช้เป็น Pivot
    swap(arr[mid], arr[low]);
    int pivot = arr[low]; //* ใช้ตัวแรกของช่วงเป็น pivot
    //@ i → วิ่งจากซ้ายไปขวา, j → วิ่งจากขวาไปซ้าย
    int i = low; 
    int j = high + 1; //* ให้เริ่มที่ right + 1 เพื่อให้ลูปข้างล่างทำงานถูกต้อง(decrement ก่อนใช้งาน)
    while(true){ //* ลูปนี้จะทำงานจนกว่า i และ j จะชนกัน
        //@ ขยับ i → เลื่อน i ไปทางขวา
        do{ 
            i++;
        } while(i <= high && arr[i] < pivot); 
        /* หยุดเมื่อ: 
            ● i ชนขอบขวา → เกิน right
              ! กรณีที่ไม่ดักไว้ อาจทำให้ array out of bound แต่อาจจะไม่ Crash เพราะอาจจะไปอ่านค่าขยะที่มากกว่า pivot ก็ได้
            ● เจอค่าที่ มากกว่าหรือเท่ากับ pivot */ 
        //@ ขยับ j → เลื่อน j ไปทางซ้าย
        do{ 
            j--;
         } while(arr[j] > pivot); //* หยุดเมื่อเจอค่าที่ น้อยกว่าหรือเท่ากับ pivot
        if(i >= j) break; //* ถ้า i กับ j สวนทางกันแล้ว ให้หยุด → แบ่งเสร็จแล้ว
        swap(arr[i], arr[j]); //* ค่าทางซ้ายที่ใหญ่เกิน → ไปอยู่ขวา, ค่าทางขวาที่เล็กเกิน → มาอยู่ซ้าย
    }
    //* สลับ pivot (ตำแหน่ง left) ไปไว้ที่ตำแหน่ง j (ตำแหน่งที่ถูกต้อง)
    swap(arr[low], arr[j]);
    return j; //* คืนค่า pivot index → j คือจุดที่ pivot ควรอยู่
}

//? ฟังก์ชัน Quick Select แบบ Relative Rank
int quickSelect(vector<int>& arr, int low, int high, int k){
    //@ Base Case: เหลือตัวเดียว ตัวนั้นคือคำตอบ
    if (low == high)
        return arr[low];
    //@ หาตำแหน่ง Pivot
    int pivotIndex = partition(arr, low, high);
    //@ คำนวณลำดับของ Pivot ในช่วงปัจจุบัน (Rank)
    //* Pivot อยู่ที่ index pivotIndex ดังนั้นมันเป็นตัวที่ (p - low + 1) ในช่วงนี้
    //* เช่น low = 0, pivotIndex = 3 (คือ index ที่ 3) -> มีสมาชิก 0,1,2,3 รวมเป็น 4 ตัว
    //  ดังนั้น มี pivotRank = 3 - 0 + 1 = 4 แปลว่าอยู่ลำดับที่ 4 ในช่วงนี้
    int pivotRank = pivotIndex - low + 1; 
    //@ กรณี 1: เจอพอดี (เช่นหาลำดับ 4 แล้วฝั่งซ้ายมี 4 ตัวพอดี)
    if (k == pivotRank) //! เทียบ k กับ pivotRank แบบ Relative นับลำดับจากในช่วงข้อมูล(Subarray)ที่ถูกเรียก
        return arr[pivotIndex]; //* คืนค่า arr[pivotIndex] เพราะเป็นตำแหน่งข้อมูลจริงๆใน array
    //@ กรณี 2: k น้อยกว่า (คำตอบอยู่ทางซ้าย)
    //* k ไม่เปลี่ยน เพราะลำดับในฝั่งซ้ายยังเป็นลำดับเดิม
    else if (k < pivotRank)
        return quickSelect(arr, low, pivotIndex - 1, k);
    //@ กรณี 3: k มากกว่า (คำตอบอยู่ทางขวา)
    else
        //! ตรงนี้คือ Relative Rank
        //* เราจะไปหาทางขวา แต่ต้องลดค่า k ลง เท่ากับจำนวนคนที่ตัดทิ้งไป (count)
        return quickSelect(arr, pivotIndex + 1, high, k - pivotRank);
}

int main(){
    vector<int> arr = {10, 4, 5, 8, 6, 11, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout<<"Sorted Array: ";
    sort(arr.begin(), arr.end());
    for(int el:arr){
        cout<<el<<" ";
    }cout<<endl;
    int k = 3; //* ต้องการหาค่าน้อยสุด "ลำดับที่ 3" (คือเลข 6)
    //! หมายเหตุ: ส่ง k ไปตรงๆ เลย ไม่ต้องลบ 1 เพราะในฟังก์ชันเราใช้ Logic แบบ Rank (นับ 1)
    cout<<"The "<<k<<"-th smallest element is "<<quickSelect(arr, 0, n - 1, k);
    return 0;
}

/*
@ median of three
- คือ การเลือก pivot โดยใช้ค่ากลาง (median) ของตัวเลข 3 ตัว
- แทนที่จะ:
    ● เลือกตัวแรก
    ● เลือกตัวสุดท้าย
    ● หรือสุ่มมั่ว ๆ
- เราจะเลือก pivot จาก 3 ตำแหน่งนี้:
    ● arr[low] = ตัวแรก
    ● arr[mid] = ตัวกลาง
    ● arr[high] = ตัวสุดท้าย
- แล้วเอา ค่าที่อยู่ตรงกลาง (ไม่มากสุด ไม่น้อยสุด) มาเป็น pivot
* ตัวอย่าง
    [ 1, 9, 5, 7, 3 ]
      ^     ^     ^
     low   mid   high
- ค่าที่ดูคือ:
    ● arr[low]  = 1
    ● arr[mid]  = 5
    ● arr[high] = 3
- เรียง 3 ตัวนี้: 1, 3, 5
* median = 3 ดังนั้น pivot = 3 (เราต้อง swap arr[mid] กับ arr[...] ... คือตำแหน่งของ Pivot)
* Code
    int medianOfThree(int arr[], int low, int high) {
        int mid = (low + high) / 2;

        if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
        if (arr[low] > arr[high]) swap(arr[low], arr[high]);
        if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);

        //* ตอนนี้ arr[mid] คือ median
        swap(arr[mid], arr[high]);  // เอา pivot ไปไว้ท้าย
        return arr[high];
    }
@ Relative Rank
- Rank = ลำดับเมื่อเรียงข้อมูลจากน้อย → มาก
- Relative Rank = อันดับของข้อมูล เมื่อพิจารณาเฉพาะใน subarray (ช่วงย่อย) ไม่ใช่อันดับใน array 
  ทั้งหมดแล้ว
* ตัวอย่าง
- arr = [1, 3, 5, 7, 9, 11], k = 5   //* อยากได้อันดับที่ 5
- สมมติ pivot = 5
    [1, 3] 5 [7, 9, 11]
    ● leftSize = 3 (1,3,5)
    ● k = 5 > 3 → ไปขวา
    ● pivotIndex = 2
    ● pivotRank = 2 - 0 + 1 = 3
    ● relative rank ใหม่:
        k = 5 - 3 = 2 //* คือ ไปฝั่งขวา จึงตัดฝั้งซ้ายออก ซึ่งฝั่งซ้ายมี 3 ตำแหน่งจึงลบ 3
- ใน subarray [7, 9, 11]
- เราหา อันดับที่ 2 → ได้ 9
*/