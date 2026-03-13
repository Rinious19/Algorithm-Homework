#include <iostream>
#include <vector>

using namespace std;

//? ฟังก์ชันค้นหาแบบ Sequential/Linear Search
//* คืนค่า index ที่เจอ, ถ้าไม่เจอคืนค่า -1
int sequentialSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i; //* เจอแล้ว! ส่งตำแหน่งกลับทันที
        }
    }
    return -1; //* หาจนจบแล้วไม่เจอ
}

int main() {
    vector<int> data = {10, 50, 30, 70, 80, 20};
    int target = 30;
    int result = sequentialSearch(data, target);
    if (result != -1)
        cout << "Found at index: " << result << endl;
    else
        cout << "Not found" << endl;
    return 0;
}

/*
- Sequential Search (หรือ Linear Search) คือวิธีการค้นหาข้อมูลที่พื้นฐานที่สุด โดยการ "ไล่เช็คทีละตัว" 
  ตั้งแต่ตัวแรกยันตัวสุดท้าย
@ Time Complexity (ความซับซ้อนของเวลา)
* 1. Best Case (ดวงดีสุด): O(1)
    ● คือ: ข้อมูลที่หา "อยู่ตัวแรกสุด" พอดี
    ● อธิบาย: เช็คครั้งเดียวเจอเลย จบงานทันที
* 2. Worst Case (ดวงซวยสุด): O(n)
    ● คือ: ข้อมูลที่หา "อยู่ตัวสุดท้าย" หรือ "ไม่มีข้อมูลนั้นเลย"
    ● อธิบาย: ต้องวนลูปเช็คจนครบทุกตัว (n ตัว) ถึงจะรู้ผล
* 3. Average Case (ดวงกลางๆ): O(n)
    ● คือ: ข้อมูลอยู่แถวๆ ตรงกลาง
    ● อธิบาย: โดยเฉลี่ยต้องเช็คประมาณ n/2 ตัว แต่ในทาง Big O เราตัดค่าคงที่ทิ้ง จึงเหลือแค่ O(n)
@ สรุปจุดเด่น
● ข้อดี: เขียนง่ายมาก, ข้อมูล "ไม่จำเป็นต้องเรียงลำดับ" (Unsorted) ก็หาได้
● ข้อเสีย: ช้ามากถ้าข้อมูลเยอะ (ถ้าข้อมูลเยอะๆ และมีการค้นหาบ่อยๆ ควรเรียงข้อมูลแล้วใช้ Binary Search แทนครับ)
*/