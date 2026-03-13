#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;
//? bubbleSort(): ส่ง vector แบบ reference → เรียงแล้วสะท้อนกลับไปที่ main
void bubbleSort(vector<int>& arr){
    int n = arr.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

int main(){
    //@ 1. รับข้อมูล
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    //@ 2. เรียงลำดับ (Sort)
    bubbleSort(nums);
    //@ 3. สร้างสตริงยาว (Concatenate) - แสดงผลบรรทัดที่ 1
    string text = "";
    for(int num : nums)
        text += to_string(num); //* to_string(): แปลง int → string
    cout<<text<<endl;
    //@ 4. ค้นหาตัวซ้ำสูงสุด (Search Max Consecutive) - แสดงผลบรรทัดที่ 2
    int maxRep = 0; //* maxRep: เก็บค่าจำนวนซ้ำที่มากที่สุด
    int currentRep = 0; //* currentRep: เก็บค่าจำนวนซ้ำปัจจุบัน
    char prev = '\0'; //* prev: เก็บค่าตัวก่อนหน้า
    //* 4.1 รอบแรก: หาค่าจำนวนซ้ำที่มากที่สุดก่อน (Find Max Count)
    for(char c : text){
        if(c == prev) //* ถ้าตัวอักษรเหมือนเดิม → นับเพิ่ม
            currentRep++;
        else//* ถ้าเปลี่ยน → เริ่มนับใหม่
            currentRep = 1; 
        if(currentRep > maxRep)
            maxRep = currentRep;
        prev = c; //! เก็บค่าตัวปัจจุบันเป็นตัวก่อนหน้า เพื่อใช้เปรียบเทียบในรอบถัดไป
    }
    set<char> winners; //* ใช้ set เพื่อเรียงลำดับและตัดตัวซ้ำให้อัตโนมัติ
    if(maxRep <= 1){ //! กรณีพิเศษ: ถ้าไม่มีตัวซ้ำเลย (maxRep == 1) ให้เอาทุกตัวเลขที่มี
        for(char c : text) winners.insert(c);
    }else { //* 4.2 รอบสอง: หาว่าใครบ้างที่ซ้ำเท่ากับ Max Count
        currentRep = 0;
        prev = '\0';
        for(char c : text){
            if(c == prev)
                currentRep++;
            else 
                currentRep = 1;
            if(currentRep == maxRep)
                winners.insert(c);
            prev = c; //! เก็บค่าตัวปัจจุบันเป็นตัวก่อนหน้า เพื่อใช้เปรียบเทียบในรอบถัดไป
        }
    }
    //* ปริ้นท์ตัวเลขที่ซ้ำมากที่สุด
    for(char c : winners)
        cout<<c<<" ";
    cout<<endl;
    //@ 5. ยุบตัวเลข (Reduce) - แสดงผลบรรทัดที่ 3
    //* ยุบเฉพาะตัวที่ซ้ำติดกัน (Consecutive duplicates)
    string reduced = "";
    if(text.length() > 0){
        reduced += text[0]; //* เก็บตัวแรกเสมอ
        for(int i = 1; i < text.length(); i++){
            if(text[i] != text[i-1]) //* ถ้าตัวนี้ ไม่เหมือน ตัวก่อนหน้า ให้เก็บ
                reduced += text[i];
        }
    }
    cout<<reduced<<endl;
    return 0;
}


