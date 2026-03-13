#include <bits/stdc++.h>
using namespace std;

class Item{
public:
    int value;
    int weight;
    Item() : value(0), weight(0){} //* Default Constructor
    Item(int value, int weight) : value(value), weight(weight){} //* Parameterized Constructor
};

//? ฟังก์ชัน checkAndPrint (ตัวคำนวณและหาค่าดีที่สุด)
void checkAndPrint(int binary[], int n, Item* items, Item* resultItems, int maxWeight){
    int sumValue = 0;
    int sumWeight = 0;
    //@ วนลูปดูว่าในรอบนี้ เราเลือกหยิบชิ้นไหนบ้าง
    for(int i = 0; i < n; i++){
        if(binary[i] == 1){ //* ถ้า binary เป็น 1 แปลว่าหยิบ
            //* การเข้าถึง array ผ่าน pointer
            //    (items + i) คือขยับ pointer ไปที่ object ตัวที่ i
            //    ->value คือดึงค่า value ออกมา
            sumValue += (items + i)->value;
            sumWeight += (items + i)->weight;
        }
    }
    //@ เช็คเงื่อนไข: น้ำหนักต้องไม่เกินกำหนด AND มูลค่าต้องมากกว่าสถิติเดิมที่เคยทำได้
    if(sumWeight <= maxWeight && sumValue > resultItems->value){
        //* อัปเดตสถิติใหม่ที่ดีที่สุดลงใน pointer resultItems
        resultItems->value = sumValue;
        resultItems->weight = sumWeight;
    }
}

//? ฟังก์ชัน findSubsets (ตัวสร้างทางเลือก): 0 = ไม่หยิบของชิ้นนี้, 1 = หยิบของชิ้นนี้
void findSubsets(int binary[], int index, int n, Item* items, Item* resultItems, int maxWeight){
    //@ Base Case: เมื่อตัดสินใจครบทุกชิ้นแล้ว (index วิ่งไปจนเท่ากับ n)
    if (index == n)
        checkAndPrint(binary, n, items, resultItems, maxWeight); //* คำนวณผลลัพธ์ของรอบนี้
    else {
        //* กรณีที่ 1: เลือกหยิบของชิ้นที่ index (ให้ค่าเป็น 1)
        binary[index] = 1;
        findSubsets(binary, index + 1, n, items, resultItems, maxWeight); //* ไปตัดสินใจชิ้นถัดไป
        //* กรณีที่ 2: ไม่หยิบของชิ้นที่ index (ให้ค่าเป็น 0)
        // ต้องถอยกลับมาแก้เป็น 0 (Backtracking) เพื่อลองอีกทางเลือก
        binary[index] = 0;
        findSubsets(binary, index + 1, n, items, resultItems, maxWeight); //* ไปตัดสินใจชิ้นถัดไป
    }
}

int main(){
    int maxWeight; //* weight สูงสุดที่รับได้
    cin>>maxWeight;
    int n = 4;
    //* ตรงนี้ items เป็นชื่อ Array แต่เวลาส่งเข้าฟังก์ชัน มันจะลดรูป (Decay) เป็น Pointer (Item*)
    Item items[n];
    for(int i=0;i<n;i++) cin>>items[i].value; //* รับ value ของ obj แต่ละตัว
    for(int i=0;i<n;i++) cin>>items[i].weight; //* รับ weight ของ obj แต่ละตัว
    Item* resultItems = new Item(); 
    int binary[n]; // Array เก็บสถานะ 0/1 (หยิบ/ไม่หยิบ)
    findSubsets(binary, 0, n, items, resultItems, maxWeight); 
    cout<<"Max Value = "<<resultItems->value<<", Weight = "<<resultItems->weight<<endl;
    return 0;
}

/*
@ การทำงาน
- โค้ดนี้คือการแก้โจทย์ปัญหา 0/1 Knapsack Problem (ปัญหาการเลือกของใส่กระเป๋าให้ได้มูลค่ามากที่สุดโดยน้ำ
  หนักไม่เกินกำหนด)
- โดยใช้วิธี Brute Force (Exhaustive Search) คือการ "ลองทุกความเป็นไปได้" ว่าจะหยิบชิ้นไหนบ้าง 
  (หยิบ/ไม่หยิบ) ผ่านการเขียนฟังก์ชันเรียกตัวเอง (Recursion)
*/