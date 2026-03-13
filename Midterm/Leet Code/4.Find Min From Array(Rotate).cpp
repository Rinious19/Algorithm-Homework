#include <iostream>
#include <vector>

using namespace std;

//? ใช้หาค่า min ได้เฉพาะ Array ที่ถูกหมุน
int findMin(vector<int>& nums) {
    int low = 0;
    int high = nums.size() - 1;
    //* ถ้าอาร์เรย์มีตัวเดียว ให้ตอบตัวนั้นเลย
    if (nums.size() == 1) return nums[0];
    while (low < high) {
        int mid = low + (high - low) / 2;
        //* ถ้าค่าตรงกลาง มากกว่า ค่าขวาสุด แสดงว่า "จุดต่ำสุด" อยู่ในครึ่งขวาแน่นอน
        if (nums[mid] > nums[high]) {
            low = mid + 1;
        } 
        //* ถ้าค่าตรงกลาง น้อยกว่าหรือเท่ากับ ค่าขวาสุด แสดงว่า "จุดต่ำสุด" อยู่ในครึ่งซ้าย หรือคือตัว mid เอง
        else
            high = mid;
    }
    //* เมื่อจบ loop, low จะเท่ากับ high ซึ่งคือตำแหน่งของค่าที่น้อยที่สุด
    return nums[low];
}

int main() {
    //* Test Case 1
    vector<int> nums1 = {3, 4, 5, 1, 2}; //* จุดมหุนคือ 5
    cout << "Min of nums1: " << findMin(nums1) << endl; // Output: 1
    //* Test Case 2
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2}; //* จุดมหุนคือ 7
    cout << "Min of nums2: " << findMin(nums2) << endl; // Output: 0
    //* Test Case 3
    vector<int> nums3 = {11, 13, 15, 17}; //* ไม่ได้มหุน
    cout << "Min of nums3: " << findMin(nums3) << endl; // Output: 11
    return 0;
}

/*
@ หลักการคิด (Logic)
- ในอาร์เรย์ที่ถูกหมุน (Rotated Sorted Array) จะมีส่วนหนึ่งที่เรียงลำดับถูกต้องเสมอ:
    ● ถ้า nums[mid] > nums[high] แปลว่าจุดที่ค่าน้อยที่สุดต้องอยู่ ทางขวา ของ mid (เพราะค่ามันควรจะลดลง
      ไปหาทางขวา แต่ดันมากกว่า แสดงว่าฝั่งขวามีจุดที่ค่ากระโดดลงไปเริ่มต้นใหม่)
    ● ถ้า nums[mid] <= nums[high] แปลว่าจุดที่ค่าน้อยที่สุดอยู่ ทางซ้าย หรืออาจจะเป็นตัว mid เอง
*/