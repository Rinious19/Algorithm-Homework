#include <bits/stdc++.h>
using namespace std;

int fnCallCount = 0; //* นับจำนวนครั้งที่ฟังก์ชันถูกเรียกใช้
int tryCount = 0; //* นับจำนวนครั้งที่เราลองเลือกตัวเลขนี้ในลูป
int leafCount = 0; //* นับจำนวน subset ที่รอดมาจนครบชั้น

class Item{
public:
    int value;
    int weight;
    Item() : value(0), weight(0){} //* Default Constructor
    Item(int value, int weight) : value(value), weight(weight){} //* Parameterized Constructor
};

//? ฟังก์ชัน findSubsets (ตัวสร้างทางเลือก): 0 = ไม่หยิบของชิ้นนี้, 1 = หยิบของชิ้นนี้
void findSubsets(int binary[], int index, int n, Item* items, Item* resultItems, int maxWeight, int currentValue, int currentWeight){
    fnCallCount++;
    //@ Base Case 1: ถ้าผลรวมค่าปัจจุบันมากกว่าค่าสูงสุดที่เจอมา ให้บันทึกค่าใหม่
    if(currentValue > resultItems->value){
        resultItems->value = currentValue;
        resultItems->weight = currentWeight;
    }
    //@ Base Case 2: เมื่อตัดสินใจครบทุกชิ้นแล้ว (index วิ่งไปจนเท่ากับ n)
    if(index == n){
        leafCount++; //* นับ Subset ที่รอดมาจนครบชิ้น
        return;
    } 
    tryCount++; //* นับความพยายามในการหยิบ
    //@ จุดแตกกิ่ง (Recursive Step) - ทำ Pruning
    //* ทางเลือกที่ 1: "เอา" ตัวเลขตำแหน่งนี้ (Set เป็น 1) 
    // จะหยิบได้ก็ต่อเมื่อบวกเข้าไปแล้ว currentWeight ไม่เกิน maxWeight
    if(currentWeight + (items + index)->weight <= maxWeight){
        binary[index] = 1;
        findSubsets(binary, index + 1, n, items, resultItems, maxWeight, currentValue + (items + index)->value, currentWeight + (items + index)->weight); //* ไปตัดสินใจชิ้นถัดไป
        //! currentValue + (items + index)->value, currentWeight + (items + index)->weight 
        //  อัพเดตผลรวมปัจจุบันใน function call ถัดไป
    }
    //* ทางเลือกที่ 2: "ไม่เอา" ตัวเลขตำแหน่งนี้ (Set เป็น 0)
    // การไม่หยิบไม่มีทางทำให้ currentWeight เกิน ดังนั้นเดินต่อได้เสมอ
    binary[index] = 0;
    findSubsets(binary, index + 1, n, items, resultItems, maxWeight, currentValue, currentWeight); //* ไปตัดสินใจชิ้นถัดไป
    
}

int main(){
    int n = 4;
    //* ตรงนี้ items เป็นชื่อ Array แต่เวลาส่งเข้าฟังก์ชัน มันจะลดรูป (Decay) เป็น Pointer (Item*)
    Item items[n] = {{10, 5}, {20, 3}, {25, 8}, {8, 4}}; //* {value, weight}
    Item* resultItems = new Item(); 
    int binary[n]; // Array เก็บสถานะ 0/1 (หยิบ/ไม่หยิบ)
    int maxWeight = 13; // รับน้ำหนักได้สูงสุด 13
    findSubsets(binary, 0, n, items, resultItems, maxWeight, 0, 0); 
    cout<<"Max Value = "<<resultItems->value<<", Weight = "<<resultItems->weight<<endl;
    cout<<"Function Call Count = "<<fnCallCount<<", Try Count = "<<tryCount<<", Leaf Count = "<<leafCount<<endl;
    return 0;
}

/*
- Pruning (การตัดแต่งกิ่ง) ใน Backtracking คือเทคนิคการ "เลิกเดินต่อ" ในเส้นทางที่เรารู้แน่ๆ แล้วว่า 
  "ไม่มีทางเจอคำตอบ" เพื่อลดจำนวนการเรียกฟังก์ชัน (Recursive Calls) ทำให้โปรแกรมทำงานเร็วขึ้นอย่างมหาศาล
@ จุดที่ควรวางตัวนับ (Counter)
* จุดที่ 1: fnCallCount (วางที่หัวฟังก์ชัน)
- หน้าที่: นับจำนวนโหนดทั้งหมดที่โปรแกรม "ตัดสินใจเดินเข้าไป" จริงๆ
- ทำไมต้องนับ: เพื่อดูว่าจาก Brute Force เดิมที่ต้องรัน 2^{n+1}-1 ครั้ง (ในที่นี้คือ 31 ครั้ง) พอทำ Pruning 
  แล้วมันเหลือการทำงานจริงกี่ครั้ง (26 ครั้ง)
* จุดที่ 2: tryCount (วางก่อน if ที่เช็คน้ำหนัก)
- หน้าที่: นับจำนวนครั้งที่โปรแกรม "พยายามจะหยิบ" ของชิ้นนั้น
- ทำไมต้องนับ: เพื่อให้เห็นว่ามีกี่ครั้งที่เรายั้งมือไว้ทัน ไม่กระโดดเข้าไปในฟังก์ชันถัดไปเพราะรู้ว่าน้ำหนักจะเกิน (14 ครั้ง)
* จุดที่ 3: leafCount (วางใน if(index == n))
- หน้าที่: นับจำนวน Subset ที่เป็นไปได้ทั้งหมดที่ "รอด" ไปจนจบกระบวนการเลือก
- ทำไมต้องนับ: เพื่อดูว่ามีกี่รูปแบบที่น้ำหนักไม่เกินและพิจารณาครบทุกชิ้น (12 ครั้ง)
! fnCallCount = tryCount + leafCount → เพราะทุกครั้งที่ฟังก์ชันถูกรัน มันจะต้องผ่าน 1 ใน 2 กรณีนี้เสมอ
*/