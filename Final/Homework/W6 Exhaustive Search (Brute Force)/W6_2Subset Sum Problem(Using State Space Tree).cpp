#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชันนี้มีหน้าที่ "ตรวจคำตอบ" เมื่อเราเลือกตัวเลขครบทุกตัวแล้ว
void checkAndPrint(int binary[], int n, int arr[], int targetSum){
    int sum = 0;
    //@ 1. วนลูปดูสวิตช์ (binary) ทั้งหมด 5 ตัว (0 ถึง n-1)
    for(int i = 0; i < n; i++){
        if(binary[i] == 1) //* ถ้าสวิตช์ตัวที่ i เป็น 1 (แปลว่าเราเลือกตัวเลขนี้)
            sum += arr[i]; //* เอาค่าจาก arr[i] มาบวกเข้า sum
    }
    //@ 2. เช็คว่าผลรวมเท่ากับเป้าหมาย (12) หรือไม่?
    if(sum == targetSum){
        //* ส่วนนี้คือการจัดรูปแบบการพิมพ์ให้สวยงาม (เช่น "10 + 2 = 12")
        bool first = true;
        for(int i = 0; i < n; i++){
            if(binary[i] == 1){
                if(!first) cout<<" + "; //* พิมพ์เครื่องหมายบวก ถ้าไม่ใช่ตัวแรก
                cout<<arr[i];
                first = false;
            }
        }
        cout<<" = "<<targetSum<<endl;
    }
}

//? ฟังก์ชันนี้คือหัวใจหลัก (Recursive) ทำหน้าที่ "ตัดสินใจ" ทีละตัว
//* index: คือ "เข็มชี้" ว่าตอนนี้เรากำลังตัดสินใจที่ตัวเลขตัวไหน (0, 1, 2, 3, 4)
void generateSubsets(int binary[], int index, int n, int arr[], int targetSum){
    //@ Base Case: ถ้า index เท่ากับ n แปลว่าตัดสินใจครบ 5 ตัวแล้ว (เดินมาสุดทาง)
    if(index == n){
        checkAndPrint(binary, n, arr, targetSum); //* ไปตรวจคำตอบซิว่าผลรวมได้เท่าไหร่
    }
    //@ จุดแตกกิ่ง (Recursive Step)
    else{
        //* ทางเลือกที่ 1: "เอา" ตัวเลขตำแหน่งนี้ (Set เป็น 1) 
        binary[index] = 1; //! ถ้าสลับเป็น 1 และ ข้างล่างเป็น 0 จะเริ่มจาก 0000... แทน 1111...
        generateSubsets(binary, index + 1, n, arr, targetSum); //* ขยับเข็ม (index+1) ไปทำตัวต่อไป
        //* ทางเลือกที่ 2: "ไม่เอา" ตัวเลขตำแหน่งนี้ (Set เป็น 0)
        //* นี่คือการ Backtrack (ย้อนกลับมาเปลี่ยนใจ)
        binary[index] = 0;
        generateSubsets(binary, index + 1, n, arr, targetSum); //* ขยับเข็ม (index+1) ไปทำตัวต่อไป
    }
}

int main(){
    int targetSum; //* เป้าหมายผลรวม
    cin>>targetSum;
    int n = 5; //* จำนวนสมาชิกทั้งหมด
    int binary[n]; //* Array ที่เก็บสถานะ (0 หรือ 1) ใช้แทนการเลือก/ไม่เลือก
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    generateSubsets(binary, 0, n, arr, targetSum); //* เริ่มต้นเรียกฟังก์ชัน: เริ่มที่ index 0 (ตัวแรกสุด)
    return 0;
}

