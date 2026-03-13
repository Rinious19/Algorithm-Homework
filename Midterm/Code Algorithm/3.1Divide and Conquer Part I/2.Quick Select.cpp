#include <iostream>
#include <vector>
#include <algorithm> // สำหรับ swap

using namespace std;

//? ฟังก์ชันแบ่งส่วน (Partition) → จัด pivot ให้อยู่ตำแหน่งที่ถูกต้อง, และคืน index ของ pivot กลับมา
int partition(vector<int>& arr, int left, int right){
    int pivot = arr[left]; //* ใช้ตัวแรกของช่วงเป็น pivot
    //@ i → วิ่งจากซ้ายไปขวา, j → วิ่งจากขวาไปซ้าย
    int i = left; 
    int j = right + 1; //* ให้เริ่มที่ right + 1 เพื่อให้ลูปข้างล่างทำงานถูกต้อง(decrement ก่อนใช้งาน)
    while(true){ //* ลูปนี้จะทำงานจนกว่า i และ j จะชนกัน
        //@ ขยับ i → เลื่อน i ไปทางขวา
        do{ 
            i++;
        } while(i <= right && arr[i] < pivot); 
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
    swap(arr[left], arr[j]);
    return j; //* คืนค่า pivot index → j คือจุดที่ pivot ควรอยู่
}

//? ฟังก์ชัน Quick Select แบบ Recursive
//* kIndex คือ index ที่เราต้องการ (เช่น ถ้าหาลำดับที่ 3 ค่า kIndex ต้องเป็น 2)
// arr = [1,2,3,4,5], หาลำดับที่ 3 (kIndex=2) → คืนค่า 3
int quickSelect(vector<int>& arr, int left, int right, int kIndex){
    //@ Base Case: ถ้าเหลือตัวเดียว ก็คือตัวนั้นแหละ
    if(left == right) 
        return arr[left];
    //@ 1. แบ่งข้อมูล และหาตำแหน่ง Pivot ปัจจุบัน
    int pivotIndex = partition(arr, left, right);
    //@ 2. เช็คตำแหน่ง
    if(kIndex == pivotIndex)
        return arr[pivotIndex]; //* เจอแล้ว! ตำแหน่งนี้คือลำดับที่ต้องการพอดี
    else if(kIndex < pivotIndex)
        return quickSelect(arr, left, pivotIndex - 1, kIndex); //* คำตอบอยู่ทางซ้าย (ไปหาเฉพาะฝั่งซ้าย)
    else
        return quickSelect(arr, pivotIndex + 1, right, kIndex); //* คำตอบอยู่ทางขวา (ไปหาเฉพาะฝั่งขวา)
}

int main(){
    //* ข้อมูลดิบ (ยังไม่เรียง)
    vector<int> data = {10, 4, 5, 8, 6, 11, 26};
    int k = 3; //* ต้องการหาค่าที่น้อยที่สุด "ลำดับที่ 3"
    //* ลำดับที่ 3 หมายถึง index ที่ 2 (0, 1, 2)
    int kIndex = k - 1; 
    //@ ตรวจสอบขอบเขต
    if(kIndex >= 0 && kIndex < data.size()){
        int result = quickSelect(data, 0, data.size() - 1, kIndex); 
        cout<<"Unsorted Data: ";
        for(int x : data) cout<<x<<" "; //* สังเกตว่าข้อมูลจะเปลี่ยนตำแหน่งไปบ้างจากการ partition
        cout<<endl;
        cout<<"Sorted Data: ";
        sort(data.begin(), data.end()); //* เรียงข้อมูลเพื่อแสดงผล
        for(int x : data) cout<<x<<" ";
        cout<<endl;
        cout<<"The "<<k<<"-th smallest element is: "<<result<<endl;
    }else
        cout<<"Invalid k"<<endl;
    return 0;
}

/*
- พัฒนามาจาก Quick Sort โดยตัดการเรียงลำดับฝั่งที่ไม่จำเป็นออก
@ แนวคิดหลักของ Quick Select
- Quick Select ใช้แนวคิด Divide and Conquer (แบ่งแล้วพิชิต)
* 1. เลือกตัวหนึ่งเป็น Pivot
* 2. จัดเรียงให้
     ● ค่าที่ น้อยกว่า Pivot ไปอยู่ซ้าย
     ● ค่าที่ มากกว่า Pivot ไปอยู่ขวา
* 3. ตรวจสอบตำแหน่งของ Pivot ที่ได้
    ● ถ้า pivot index == kIndex → เจอคำตอบแล้ว
    ● ถ้า pivot index > kIndex → คำตอบอยู่ฝั่งซ้าย (ไปหาเฉพาะฝั่งซ้าย)
    ● ถ้า pivot index < kIndex → คำตอบอยู่ฝั่งขวา (ไปหาเฉพาะฝั่งขวา)
* 4. ทำแบบเดิมซ้ำ(Recursive) กับฝั่งที่มีคำตอบ หยุดเมื่อเหลือข้อมูล 0 หรือ 1 ตัว (เจอคำตอบ)
- จุดเด่นคือ ไม่ต้องใช้หน่วยความจำเพิ่มเยอะ และโดยเฉลี่ยเร็วมาก
@ ประสิทธิภาพ (Time Complexity)
* 1. กรณีดีที่สุด (Best Case): O(n) – เกิดขึ้นเมื่อ Pivot สามารถ "แบ่งข้อมูลออกเป็น 2 ฝั่งได้เท่าๆ กัน"
    (หรือใกล้เคียงกัน) เสมอ
    ● T(n) = T(n/2) + n
        - T(n/2) คือเราต้องแก้ปัญหาย่อยแค่ 1 ฝั่ง ซึ่งมีขนาดเหลือครึ่งเดียว 
        - n คือเวลาที่ใช้ในการ Partition (วนลูปเทียบข้อมูลทุกตัวกับ Pivot ในรอบนั้น)
* 2. กรณีทั่วไป (Average Case): O(n) – เร็วมาก และใช้บ่อยที่สุด
* 3. กรณีแย่ที่สุด (Worst Case): O(n^2) – เกิดขึ้นเมื่อข้อมูลเรียงลำดับมาอยู่แล้ว แล้วเราเลือกตัวสุดท้ายเป็น 
     Pivot เสมอ (แต่แก้ไขได้โดยการสุ่มเลือก Pivot)
    ● T(n) = T(n - 1) + n
        - T(n - 1) ปัญหาลดขนาดลงไปแค่ 1 ตัว (เหมือนปอกเปลือกหัวหอมทีละชั้น)
        - n เวลาที่ใช้ Partition 
*/