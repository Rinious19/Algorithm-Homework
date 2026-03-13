#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชันสำหรับผสาน 2 อาร์เรย์ย่อย (Sub-arrays)
//* อาร์เรย์แรกคือ arr[left..mid]
//* อาร์เรย์สองคือ arr[mid+1..right]
//! ใน Header <bits/stdc++.h>, <algorithm> มี fn merge อยู่แล้ว จึงตั้งชื่อเป็น mergeArrays
void mergeArrays(vector<int>& arr, int left, int mid, int right){
    //@ เตรียมข้อมูล อาร์เรย์ชั่วคราว
    int nL = mid - left + 1; //* ขนาดของฝั่งซ้าย
    int nR = right - mid;    //* ขนาดของฝั่งขวา
    //* สร้างอาร์เรย์ชั่วคราว (Temp arrays)
    vector<int> L(nL), R(nR);
    //* ก๊อปปี้ข้อมูลลงอาร์เรย์ชั่วคราว
    for(int i = 0; i < nL; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < nR; j++)
        R[j] = arr[mid + 1 + j];
    //@ เริ่มกระบวนการผสาน (Merge)
    int l = 0; //* index ของ L
    int r = 0; //* index ของ R
    int i = left; //* index ของอาร์เรย์หลัก (arr)
    while(l < nL && r < nR){
        if(L[l] <= R[r]){ //* ถ้าซ้ายน้อยกว่าหรือเท่ากับขวา
            arr[i] = L[l];  //* เอาซ้ายใส่
            l++;
        } 
        else{            //* ถ้าขวาน้อยกว่า
            arr[i] = R[r];  //* เอาขวาใส่
            r++;
        }
        i++;
    }
    //@ เก็บตกสมาชิกที่เหลือ (ถ้าฝั่งไหนยังไม่หมด)
    while(l < nL){
        arr[i] = L[l];
        l++;
        i++;
    }
    while(r < nR){
        arr[i] = R[r];
        r++;
        i++;
    }
}

//? ฟังก์ชันหลัก Merge Sort
void mergeSort(vector<int>& arr, int left, int right){
    if(left < right){
        //* หาจุดกึ่งกลาง (ป้องกัน Overflow ดีกว่า (l+r)/2)
        int mid = left + (right - left) / 2;
        //* 1. Divide: แบ่งซ้าย แบ่งขวา
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        //* 2. Conquer: ผสานร่าง
        mergeArrays(arr, left, mid, right);
    }
}

int main(){
    vector<int> data = {12, 11, 13, 5, 6, 7};
    cout<<"Original: ";
    for(int x : data) 
        cout<<x<<" ";
    cout<<endl;
    mergeSort(data, 0, data.size() - 1);
    cout<<"Sorted:   ";
    for(int x : data) 
        cout<<x<<" ";
    cout<<endl;
    return 0;
}

/*
- Merge Sort (การเรียงลำดับแบบผสาน) คืออัลกอริทึมที่ใช้หลักการ "Divide and Conquer" (แบ่งแยกและ
  เอาชนะ) เหมือนกับ Quick Sort แต่มีวิธีการทำงานที่ "เสถียร" และ "นุ่มนวล" กว่า
@ คอนเซปต์การทำงาน (2 เฟสหลัก)
* 1. Divide(แบ่ง): แบ่งครึ่งข้อมูลไปเรื่อยๆ จนกว่าจะเหลือกลุ่มละ 1 ตัว (เพราะข้อมูล 1 ตัว ถือว่าเรียงลำดับแล้ว
     โดยธรรมชาติ)
* 2. Merge(ผสาน): นำกลุ่มย่อยๆ มา "เปรียบเทียบและรวมร่าง" กลับขึ้นมา โดยตอนรวมร่างจะเรียงลำดับไปด้วย
     คอนเซปต์หลักคือ: "แบ่งให้เล็กที่สุด แล้วค่อยๆ รูดซิปรวมกลับมา"
@ Time Complexity (ความซับซ้อนของเวลา)
- Time Complexity: O(n log n) ใน ทุกกรณี (Best, Average, Worst) 
  ● ไม่ว่าข้อมูลจะเละแค่ไหน หรือเรียงมาแล้ว ก็ใช้เวลาเท่าเดิม เพราะมันต้องแบ่งและรวมเสมอ
  ● เทียบกับ Quick Sort: Quick Sort อาจหลุดไปเป็น O(n^2) ได้ แต่ Merge Sort การันตีความเร็วคงที่
@ สรุป: Merge Sort vs Quick Sort
* เลือก Merge Sort: เมื่อต้องการความชัวร์ (Stable Sort) หรือข้อมูลมีขนาดใหญ่มากจนต้องเก็บใน Hard Disk 
  (External Sorting) และไม่มีปัญหาเรื่อง RAM
* เลือก Quick Sort: เมื่อต้องการความเร็วสูงสุดในทางปฏิบัติ และต้องการประหยัด RAM
@ ตัวอย่าง
arr = [38, 27, 43, 3]
    * Phase 1: Divide(แบ่งครึ่งไปเรื่อยๆ)
        - แบ่งครึ่ง → [38, 27] และ [43, 3]
        - แบ่งอีก → [38], [27], [43], [3] (เหลือตัวเดียวแล้ว หยุดแบ่ง!)
    * Phase 2: Merge(รวมร่าง)
        ● รวมคู่แรก [38] กับ [27]:
            - เทียบ 27 กับ 38 → 27 มาก่อน
            - ได้ [27, 38]
        ● รวมคู่สอง [43] กับ [3]:
            - เทียบ 3 กับ 43 → 3 มาก่อน
            - ได้ [3, 43]
        ● รวมสองกลุ่มใหญ่ [27, 38] กับ [3, 43]:
            - เทียบตัวหน้าสุด: 27 vs 3 → 3 ชนะ (เอา 3 ลงตะกร้า) → เหลือ [27, 38] กับ [43]
            - เทียบตัวหน้าสุด: 27 vs 43 → 27 ชนะ (เอา 27 ลงตะกร้า) → เหลือ [38] กับ [43]
            - เทียบตัวหน้าสุด: 38 vs 43 → 38 ชนะ (เอา 38 ลงตะกร้า) → เหลือ [] กับ [43]
            - หมดคู่เทียบ → เอา 43 ลงตะกร้า
- ผลลัพธ์: arr = [3, 27, 38, 43]
*/