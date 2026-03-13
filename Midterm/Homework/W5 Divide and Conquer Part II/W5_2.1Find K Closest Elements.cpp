#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> A = {10, 12, 15, 17, 18, 20, 25};
    int k = 2; //* k = จำนวนของ "จำนวนค่าที่ใกล้เคียง target มากที่สุด"
    int target = 8; 
    int n = A.size(); 
    //@ Sort A
    sort(A.begin(), A.end());
    //@ Search index i → หาตำแหน่งแรกที่มีค่า >= target
    //* ใช้ Binary Search → O(log n), ถ้าใช้ Linear Search → O(n)
    int low = 0, high = n - 1;
    int i = 0; //* ถ้า target น้อยกว่าทุกตัว จะได้ index 0
    while(low <= high) {
        int m = (low + high) / 2;
        if (A[m] >= target) {
            high = m - 1;   //* หาตัวที่เล็กกว่าอีก เรื่อยๆ จนกว่าจะจบลูป while
        } else {
            low = m + 1;
        }
        i = m; //* อัพเดตค่า i
    }
    //@ Initialize left, right → ใช้สำหรับหาค่าใกล้เคียง k ตัว ใช้เป็นขอบเขตของคำตอบ
    int left = i - 1; //* left   i   right 
    int right = i;  //* คำตอบอยู่ในช่วง (left, right) คือ อยู่ระหว่าง left และ right
    //@ หาขอบเขตของช่วงที่มีค่าใกล้เคียง k ตัว
    //* เงื่อนไข (right - left) <= k จะทำให้ได้สมาชิกจำนวน k ตัวพอดีเมื่อจบลูป
    while ((right - left) <= k) {
        if(left < 0) {
            right = right + 1; //* กรณีซ้ายตกขอบ → บังคับเลือกขวา
        } 
        else if(right >= n) {
            left = left - 1; //* กรณีขวาตกขอบ → บังคับเลือกซ้าย
        } 
        else {
            //* กรณี index ปกติทั้งคู่ → เปรียบเทียบว่าฝั่งไหนค่าใกล้เคียง target น้อยกว่ากัน(distance น้อย)
            int distLeft = abs(A[left] - target);
            int distRight = abs(A[right] - target);
            if(distRight < distLeft)
                //* ถ้าฝั่งซ้ายห่างกว่า → เลือกตัวขวา (ขยายขวา)
                right = right + 1; 
            else
                //* ถ้าฝั่งขวาห่างกว่าหรือเท่ากัน → เลือกตัวซ้าย (ขยายซ้าย)
                left = left - 1; 
        }
    }
    //@ แสดงผลลัพธ์ → ช่วงของข้อมูลที่ถูกเลือกคือ index ตั้งแต่ [left + 1] ถึง [right - 1]
    cout<<"Result: ";
    for(int j = left + 1; j < right; j++)
        cout<<A[j]<<" ";
    cout<<endl;
    return 0;
}

/*
@ หลักการ
* 1. ทำการเรียงลำดับข้อมูลก่อน
* 2. หาตำแหน่งแรกที่มีค่า >= target (หา i)
     - ถ้า target น้อยกว่าทุกตัว จะได้ index 0
* 3. กำหนด left, right → ใช้สำหรับหาค่าใกล้เคียง k ตัว ใชเป็นขอบเขตของคำตอบ
    - left = i - 1
    - right = i
    - คำตอบอยู่ในช่วง (left, right) คือ อยู่ระหว่าง left และ right
* 4. หาขอบเขตของช่วงที่มีค่าใกล้เคียง k ตัว
    - เงื่อนไข (right - left) <= k จะทำให้ได้สมาชิกจำนวน k ตัวพอดีเมื่อจบลูป
    ● 4.1 กรณีซ้ายตกขอบ → บังคับเลือกขวา → right += 1
    ● 4.2 กรณีขวาตกขอบ → บังคับเลือกซ้าย → left -= 1
    ● 4.3 กรณี index ปกติทั้งคู่ → เปรียบเทียบว่าฝั่งไหนค่าใกล้เคียง target น้อยกว่ากัน(distance น้อย)
        - ถ้าฝั่งซ้ายห่างกว่า → เลือกตัวขวา (ขยายขวา) → right += 1
        - ถ้าฝั่งขวาห่างกว่าหรือเท่ากัน → เลือกตัวซ้าย (ขยายซ้าย) → left -= 1
* 5. แสดงผลลัพธ์ → ช่วงของข้อมูลที่ถูกเลือกคือ index ตั้งแต่ [left + 1] ถึง [right - 1]
@ Time Complexity
- T(n) = O(log2(n)) + O(k)
- G(n) = O(log n)
- ใช้ Binary Search หา index i และ while loop ทำ k ครั้ง
*/

