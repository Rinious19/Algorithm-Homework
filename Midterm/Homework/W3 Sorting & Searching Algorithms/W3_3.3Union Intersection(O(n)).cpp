#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin>>n; 
    vector<int> A(n), B(n);
    int maxVal = 0; //* หาค่าสูงสุดเพื่อจองขนาด Array ให้พอดี
    //@ 1. รับค่าและหา Max Value ไปด้วย
    for(int i=0; i<n; i++){
        cin>>A[i];
        if(A[i] > maxVal) maxVal = A[i];
    }
    for(int i=0; i<n; i++){
        cin>>B[i];
        if(B[i] > maxVal) maxVal = B[i];
    }
    //* สร้าง Array สำหรับนับ (หัวใจของ Counting Sort)
    //* ใช้ขนาด maxVal + 1 เพราะ index เริ่มที่ 0 ถึง maxVal
    //* ใช้ vector<bool> หรือ int ก็ได้ (int ดีกว่าถ้าต้องนับจำนวนซ้ำ, bool ดีกว่าถ้าแค่เช็คว่ามีไหม)
    vector<bool> existInB(maxVal + 1, false);
    vector<bool> isPrinted(maxVal + 1, false);
    //@ 2. ส่วน Intersection (O(N))
    //* Step 1: "Count" หรือ Mark ข้อมูลฝั่ง B ลงตาราง
    for(int elB : B){
        existInB[elB] = true; 
    }
    //* Step 2: วน A เพื่อเช็คกับตาราง B ว่ามี สมาชิก A ตัวไหนที่มีใน B บ้าง และยังไม่เคยปริ้นท์
    for(int elA : A){
        //* เช็คว่า 1. มีใน B มั้ย? และ 2. ปริ้นท์ไปหรือยัง?
        if(existInB[elA] && !isPrinted[elA]){
            cout<<elA<<" ";
            isPrinted[elA] = true; //* Mark ว่าปริ้นท์แล้ว
        }
    }
    cout<<endl;
    //@ 3. ส่วน Union (O(N))
    //* รีเซ็ตตาราง isPrinted หรือสร้างใหม่
    //* fill(iterator begin, iterator end, value): เติมค่าที่ระบุลงในช่วง [begin, end) ด้วย value
    fill(isPrinted.begin(), isPrinted.end(), false); 
    //* Step 1: กวาด A ทั้งหมด
    for(int x : A){
        if(!isPrinted[x]){
            cout<<x<<" ";
            isPrinted[x] = true; //* Mark ว่าใช้แล้ว
        }
    }
    //* Step 2: กวาด B ทั้งหมด
    for(int x : B){
        if(!isPrinted[x]){ //* ถ้ายังไม่เคยถูกใช้ (ทั้งจาก A หรือ B ตัวก่อนหน้า)
            cout<<x<<" ";
            isPrinted[x] = true; //* Mark ว่าใช้แล้ว
        }
    }
    cout<<endl;
    return 0;
}