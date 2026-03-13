#include <iostream>
#include <vector>
#include <algorithm> //* สำหรับ std::max
#include <climits>   //* สำหรับ INT_MIN ใช้กำหนดค่าน้อยสุดของ int คือ -2147483648
using namespace std;

//? ฟังก์ชันหลักสำหรับหาผลรวมย่อยสูงสุด (Maximum Subarray Sum)
int maxSubarraySum(const vector<int>& arr, int left, int right){
    //@ Base Case: ถ้าเหลือสมาชิกตัวเดียว ให้คืนค่าค่านั้นกลับไป
    if(left == right) 
        return arr[left];
    //@ 1. Divide: หาจุดกึ่งกลาง
    int mid = (left + right) / 2;
    //@ 2. Conquer: หาค่าสูงสุดทางฝั่งซ้ายและขวาแบบ Recursive
    int leftMSS = maxSubarraySum(arr, left, mid);      //* leftMSS = Left Maximum Subarray Sum
    int rightMSS = maxSubarraySum(arr, mid + 1, right); //* rightMSS = Right Maximum Subarray Sum
    //@ 3. Combine: หาค่าสูงสุดที่ข้ามจุดกึ่งกลาง (Crossing Sum)
    //@ 3.1 คำนวณส่วนซ้ายที่ติดกับ mid (วิ่งจาก mid ถอยไปทางซ้าย)
    int currentSum = 0;
    int leftCrossMax = INT_MIN; //* ใช้ INT_MIN(-2147483648) เพื่อรองรับกรณีค่าเป็นลบ 
    for(int i = mid; i >= left; i--){ //* วิ่งจาก mid ไปทางซ้าย
        currentSum += arr[i];
        if(currentSum > leftCrossMax){
            leftCrossMax = currentSum;
        }
    }
    //@ 3.2 คำนวณส่วนขวาที่ติดกับ mid (วิ่งจาก mid+1 ไปทางขวา)
    currentSum = 0;
    int rightCrossMax = INT_MIN;
    for(int i = mid + 1; i <= right; i++){ //* วิ่งจาก mid+1 ไปทางขวา
        currentSum += arr[i];
        if(currentSum > rightCrossMax)
            rightCrossMax = currentSum;
    }
    //* ผลรวมสูงสุดที่ข้ามจุดกึ่งกลาง คือ ผลรวมที่มากที่สุดของซ้ายและขวารวมกัน
    int crossMSS = leftCrossMax + rightCrossMax;
    //@ 4. Return: คืนค่าที่มากที่สุดจาก 3 กรณี (ซ้ายสุด, ขวาสุด, หรือ ข้ามตรงกลาง)
    return max({leftMSS, rightMSS, crossMSS});
}

int main(){
    //* ข้อมูลตัวอย่างจากโจทย์
    vector<int> data = {16, -25, 2, -54, 36, 9, -12, 66};
    int n = data.size();
    //* เรียกใช้งานฟังก์ชัน (ส่ง index เริ่มต้น 0 และสุดท้าย n-1)
    int result = maxSubarraySum(data, 0, n - 1);
    //* แสดงผลลัพธ์
    cout<<"Maximum Subarray Sum is: "<<result<<endl;
    return 0;
}

/*
@ Vocabulary
- leftMSS = Left Maximum Subarray Sum → ผลรวมย่อยใน Subarray ทางซ้าย ที่มีค่าสูงสุด
- rightMSS = Right Maximum Subarray Sum → ผลรวมย่อยใน Subarray ทางขวา ที่มีค่าสูงสุด
- crossMSS = Crossing Maximum Subarray Sum → ผลรวมย่อยที่ข้ามจุดกึ่งกลาง ที่มีค่าสูงสุด
  มาจากการรวมกันของผลรวมย่อยทางซ้ายสุดที่ติดกับ mid และผลรวมย่อยทางขวาสุดที่ติดกับ mid+1 หรือ
  crossMSS = leftCrossMax + rightCrossMax
- leftCrossMax → ผลรวมย่อยทางซ้ายสุดที่ติดกับ mid ที่มีค่าสูงสุด
- rightCrossMax → ผลรวมย่อยทางขวาสุดที่ติดกับ mid+1 ที่มีค่าสูงสุด
! leftMSS, rightMSS, crossMSS สามารถเป็น leftCrossMax หรือ rightCrossMax ได้เช่นกัน
@ ตัวอย่าง 
arr = [16, -25, 2, -54, 36, 9, -12, 66] (n=8)
    * 1. แบ่งข้อมูล (Divide Phase)
    - อัลกอริทึมจะแบ่งครึ่งข้อมูล (m = n/2) ลงไปเรื่อยๆ จนถึง Base case (n=1):
    - Level 0: [16, -25, 2, -54, 36, 9, -12, 66] แบ่งเป็น:
        ● ซ้าย (L1): [16, -25, 2, -54]
        ● ขวา (R1): [36, 9, -12, 66]
    - Level 1 (ฝั่งซ้าย): [16, -25, 2, -54] แบ่งเป็น:
        ● ซ้าย (L2a): [16, -25]
        ● ขวา (R2a): [2, -54]
    - Level 1 (ฝั่งขวา): [36, 9, -12, 66] แบ่งเป็น:
        ● ซ้าย (L2b): [36, 9]
        ● ขวา (R2b): [-12, 66]
    - Level 2: แบ่งย่อยจนเหลือตัวเดียว [16], [-25], [2], [-54], [36], [9], [-12], [66] 
      (เมื่อ n=1 จะ return ค่าของตัวมันเองกลับไป)
    * 2. คำนวณกลับและรวมผล (Conquer & Combine Phase) → เราจะไล่คำนวณจากชั้นล่างสุดขึ้นมาบนสุด
    📌 Level 2 Combine
    - กลุ่มที่ 1: [16, | -25]
        ● leftMSS (ซ้าย) = 16
        ● rightMSS (ขวา) = -25
        ● หา crossMSS:
            - leftCrossMax = 16
            - rightCrossMax = -25
            - crossMSS = 16 + (-25) = -9
        ● ผลลัพธ์: Max(16, -25, -9) = 16
    - กลุ่มที่ 2: [2, | -54]
        ● leftMSS (ซ้าย) = 2
        ● rightMSS (ขวา) = -54
        ● หา crossMSS:
            - leftCrossMax = 2
            - rightCrossMax = -54
            - crossMSS = 2 + (-54) = -52
        ● ผลลัพธ์: Max(2, -54, -52) = 2
    - กลุ่มที่ 3: [36, | 9]
        ● leftMSS (ซ้าย) = 36
        ● rightMSS (ขวา) = 9
        ● หา crossMSS:
            - leftCrossMax = 36
            - rightCrossMax = 9
            - crossMSS = 36 + 9 = 45
        ● ผลลัพธ์: Max(36, 9, 45) = 45
    - กลุ่มที่ 4: [-12, | 66]
        ● leftMSS (ซ้าย) = -12
        ● rightMSS (ขวา) = 66
        ● หา crossMSS:
            - leftCrossMax = -12
            - rightCrossMax = 66
            - crossMSS = -12 + 66 = 54
        ● ผลลัพธ์: Max(-12, 66, 54) = 66
    📌 Level 1 Combine
    - กลุ่มที่ 1: [16, -25, | 2, -54]
        ● leftMSS (ซ้าย) = 16
        ● rightMSS (ขวา) = 2
        ● หา crossMSS:
            - leftCrossMax = -25 + 16 = -9
            - rightCrossMax = 2
            - crossMSS = -9 + 2 = -7
        ● ผลลัพธ์: Max(16, 2, -7) = 16
    - กลุ่มที่ 2: [36, 9, | -12, 66]
        ● leftMSS (ซ้าย) = 45
        ● rightMSS (ขวา) = 66
        ● หา crossMSS:
            - leftCrossMax = 9 + 36 = 45
            - rightCrossMax = -12 + 66 = 54
            - crossMSS = 45 + 54 = 99
        ● ผลลัพธ์: Max(45, 66, 99) = 99
    📌 Level 0 Combine
    - [16, -25, 2, -54, | 36, 9, -12, 66]
        ● leftMSS (ซ้าย) = 16
        ● rightMSS (ขวา) = 99
        ● หา crossMSS:
            - leftCrossMax = -54 + 2 = -52
            - rightCrossMax = 36 + 9 - 12 + 66 = 99
            - crossMSS = -52 + 99 = 47
        ● ผลลัพธ์: Max(16, 99, 47) = 99
- ดังนั้น Maximum Subarray Sum ของ arr = [16, -25, 2, -54, 36, 9, -12, 66] คือ 99
  คือ ผลรวมย่อยของ [36, 9, -12, 66]
*/