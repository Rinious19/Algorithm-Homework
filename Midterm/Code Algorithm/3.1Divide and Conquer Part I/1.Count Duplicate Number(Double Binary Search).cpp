#include <iostream>
#include <vector>
using namespace std;

//? ฟังก์ชันนับจำนวนเลขที่ซ้ำ (Divide and Conquer)
//* เป็นการทำ Binary Search ทั้งใน Left และ Right Subarray และ Recussive ไปจนเหลือสมาชิกตัวเดียว
int countFrequencyDAC(const vector<int>& arr, int left, int right, int target) {
    //@ Base Case: ถ้าเหลือสมาชิกตัวเดียว
    if(left == right) {
        if(arr[left] == target)
            return 1; //* เจอเลขที่ต้องการ นับเป็น 1
        else
            return 0; //* ไม่ใช่เลขที่ต้องการ ไม่นับอะไร
    }
    //@ Divide: หาจุดกึ่งกลาง
    int mid = (left + right) / 2;
    //@ Conquer: เรียกตัวเองซ้ำทางซ้ายและขวา
    int leftCount = countFrequencyDAC(arr, left, mid, target); //* นับจำนวนในซีกซ้าย
    int rightCount = countFrequencyDAC(arr, mid + 1, right, target); //* นับจำนวนในซีกขวา
    //@ Combine: รวมจำนวนที่นับได้จากทั้งสองฝั่ง
    return leftCount + rightCount;
}

int main() {
    //* ข้อมูลตัวอย่าง
    vector<int> data = {2, 5, 2, 8, 5, 6, 8, 8, 2, 1, 8};
    //* เลขที่กำหนดให้ค้นหา (Target)
    int targetNumber = 8;
    int n = data.size();
    //* เรียกใช้งานฟังก์ชัน
    int result = countFrequencyDAC(data, 0, n - 1, targetNumber);
    //* แสดงผลลัพธ์
    cout << "Data: { ";
    for(int x : data) cout << x << " ";
    cout << "}" << endl;
    cout << "Number " << targetNumber << " appears " << result << " times." << endl;
    return 0;
}

/*
- ฟังก์ชัน countFrequencyDAC ใช้หลักการ Divide and Conquer ในการนับจำนวนครั้งที่ตัวเลขเป้าหมาย 
  (target) ปรากฏในอาร์เรย์
@ ขั้นตอนการทำงาน:
* 1. Base Case: เมื่อช่วงที่พิจารณามีสมาชิกเพียงตัวเดียว จะตรวจสอบว่าตัวนั้นตรงกับ target หรือไม่
     - ถ้าใช่ คืนค่า 1 เพื่อบอกว่าเจอหนึ่งครั้ง
     - ถ้าไม่ใช่ คืนค่า 0 เพื่อบอกว่าไม่เจอ
* 2. Divide: แบ่งอาร์เรย์ออกเป็นสองส่วนที่มีขนาดใกล้เคียงกัน
     - หาจุดกึ่งกลาง (mid) ของช่วงปัจจุบัน
     - แบ่งอาร์เรย์เป็นซีกซ้าย (left ถึง mid) และซีกขวา (mid+1 ถึง right)
* 3. Conquer: เรียกฟังก์ชันตัวเองแบบ Recursive
     - นับจำนวนครั้งที่ target ปรากฏในซีกซ้าย
     - นับจำนวนครั้งที่ target ปรากฏในซีกขวา
* 4. Combine: รวมผลลัพธ์จากทั้งสองซีก
     - คืนค่าผลรวมของจำนวนครั้งที่ target ปรากฏในซีกซ้ายและขวา
@ ประสิทธิภาพ (Time Complexity)
- O(n): เนื่องจากในแต่ละระดับของการแบ่ง เราจะต้องตรวจสอบทุกสมาชิกในอาร์เรย์อย่างน้อยหนึ่งครั้ง
- T(n) = 2T(n/2) + c
*/