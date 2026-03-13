#include <iostream>
#include <string>
#include <cmath>
#include <algorithm> //* สำหรับ std::max
using namespace std;

//? ฟังก์ชันนับจำนวนหลักของตัวเลข
int getLength(long long number) {
    string str = to_string(number);
    return str.length();
}

//? ฟังก์ชันคูณแบบ Divide and Conquer
long long multiplyRecursive(long long a, long long b) {
    //@ 1. หาความยาวของตัวเลข (n)
    int lengthA = getLength(a);
    int lengthB = getLength(b);
    int n = max(lengthA, lengthB);
    //@ 2. Base Case: ถ้าเหลือหลักเดียว (หรือเป็น 0) ให้คูณกันตรงๆ แล้วคืนค่า
    if(n <= 1)
        return a * b;
    //@ 3. Partition: แบ่งตัวเลขเป็น 2 ส่วน (ซ้ายและขวา)
    //* ใช้ halfN เพื่อแบ่งครึ่ง (เช่น n=4 แบ่งที่ 10^2)
    int halfN = n / 2; //! ปัดเศษลง
    long long splitter = pow(10, halfN);
    //* a = a1 * 10^(n/2) + a2
    long long a1 = a / splitter; //* ส่วนหน้า (Left part of a)
    long long a2 = a % splitter; //* ส่วนหลัง (Right part of a)
    //* b = b1 * 10^(n/2) + b2
    long long b1 = b / splitter; //* ส่วนหน้า (Left part of b)
    long long b2 = b % splitter; //* ส่วนหลัง (Right part of b)
    //@ 4-7. Recursive Calls (หาค่า A, B, C, D)
    long long A = multiplyRecursive(a1, b1); //* A
    long long B = multiplyRecursive(a2, b1); //* B
    long long C = multiplyRecursive(a1, b2); //* C
    long long D = multiplyRecursive(a2, b2); //* D
    //@ 8. Return: รวมผลลัพธ์ตามสูตร
    //* Result = A * 10^n + (B + C) * 10^(n/2) + D
    //* หมายเหตุ: 10^n คือ splitter * splitter (หรือ 10^(2*halfN))
    long long term1 = A * pow(10, 2 * halfN); // A * 10^n
    long long term2 = (B + C) * splitter;     // (B + C) * 10^(n/2)
    long long term3 = D;                      // D
    return term1 + term2 + term3;
}

int main() {
    //* ข้อมูลนำเข้าตามโจทย์
    long long numA = 4568;
    long long numB = 3275;
    //* เรียกใช้ฟังก์ชัน
    long long result = multiplyRecursive(numA, numB);
    //* แสดงผลลัพธ์
    cout<<"Input A: "<<numA<<endl;
    cout<<"Input B: "<<numB<<endl;
    cout<<"Multiplication Result: "<<result<<endl;
    return 0;
}

/*
- long long ชนิดข้อมูลสำหรับเก็บ จำนวนเต็มที่มีขนาดใหญ่มาก ( 64-bit integer ) ซึ่งใหญ่กว่า int และ 
  long ทำให้สามารถเก็บค่าได้ในช่วงกว้างกว่ามาก (ประมาณ (±9 x 10^(18))) โดยรับประกันว่ามีขนาดอย่างน้อย 
  64 บิต (8 ไบต์) เหมาะสำหรับปัญหาที่ต้องการจัดการตัวเลขที่เกินขอบเขตของ int
@ การคูณแบบแบ่งแยกและเอาชนะ (Divide and Conquer Multiplication)
- เป็นการคูณที่เรียนในจิณตคณิตน่าจะ ป.3 หรือ ป.4 โดยการแยกตัวเลขออกเป็นสองส่วน (ซ้ายและขวา) แล้วคูณแยก
  กัน จากนั้นนำผลลัพธ์มารวมกันตามตำแหน่งหลัก
@ Time Complexity
- T(n) = 4T(n/2) + cn, G(n) = O(n^2)
- เนื่องจากมีการแบ่งปัญหาออกเป็น 4 ส่วนย่อย (4T(n/2)) และมีการรวมผลลัพธ์ที่ใช้เวลาเชิงเส้น (cn)
@ ขั้นตอนการทำงาน
  1. หาความยาวของตัวเลขทั้งสอง (n)
  2. ถ้า n <= 1 (Base Case) ให้คูณกันตรงๆ แล้วคืนค่า
  3. แบ่งตัวเลขทั้งสองออกเป็นสองส่วน (a1, a2) และ (b1, b2)
  4. คำนวณค่า A = a1 * b1
  5. คำนวณค่า B = a2 * b1
  6. คำนวณค่า C = a1 * b2
  7. คำนวณค่า D = a2 * b2
  8. คืนค่าผลลัพธ์ตามสูตร: Result = A * 10^n + (B + C) * 10^(n/2) + D
*/