#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

//? ฟังก์ชันหาความยาวตัวเลข
int getLength(long long n){
    if(n == 0) return 1;
    return to_string(n).length();
}

long long karatsubaMultiply(long long a, long long b){
    int n = max(getLength(a), getLength(b)); //* หาความยาวสูงสุดของตัวเลขทั้งสอง
    //@ Base Case
    if(n <= 1) 
        return a * b;
    //@ Partition: แบ่งตัวเลขเป็น 2 ส่วน (ซ้ายและขวา)
    int halfN = n/2; //! ปัดเศษลง
    long long splitter = pow(10, halfN);
    long long a1 = a / splitter;
    long long a2 = a % splitter;
    long long b1 = b / splitter;
    long long b2 = b % splitter;
    //@ Recursive Calls (หาค่า A, B, C)
    long long A = karatsubaMultiply(a1, b1);
    long long B = karatsubaMultiply(a2, b2);
    long long C = karatsubaMultiply(a1 + a2, b1 + b2);
    //@ Combine ขั้นตอน
    long long middleTerm = C - A - B;
    //* สูตร: A*10^(2*halfN) + (C - A - B)*10^(halfN) + B
    return (A * (long long)pow(10, 2*halfN)) + (middleTerm * (long long)pow(10, halfN)) + B;
}

int main(){
    long long a = 4568;
    long long b = 3275;
    cout<<"Result: "<<karatsubaMultiply(a, b)<<endl;
    return 0;
}

/*
@ Karatsuba Algorithm คือ
- Karatsuba เป็นอัลกอริทึมสำหรับ คูณเลขจำนวนเต็มขนาดใหญ่ เป้าหมาย: ลดจำนวน “การคูณ” เพราะการคูณแพง
  กว่าการบวก 
@ Time Complexity
- T(n) = 3T(n/2) + cn → O(n^log2(3)) ≈ O(n^1.585)
- ดีกว่า O(n^2) ของการคูณแบบปกติ
@ ขั้นตอนการทำงาน
1. Base Case: ถ้าความยาวตัวเลข n <= 1 ให้คูณกันตรงๆ แล้วคืนค่า
2. Partition: แบ่งตัวเลข a และ b ออกเป็น 2 ส่วน (a1, a2) และ (b1, b2)
3. Recursive Calls: คำนวณค่า A, B, C โดยเรียกใช้ฟังก์ชัน karatsubaMultiply
   - A = karatsubaMultiply(a1, b1)
   - B = karatsubaMultiply(a2, b2)
   - C = karatsubaMultiply(a1 + a2, b1 + b2)
4. Combine: รวมผลลัพธ์โดยใช้สูตร Result = A*10^(2*halfN) + (C - A - B)*10^(halfN) + B
*/