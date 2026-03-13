#include <bits/stdc++.h>
using namespace std;

//? สร้าง Class สำหรับเก็บข้อมูลสิ่งของแต่ละชิ้น
class Item{
public:
    int id; //* เก็บตำแหน่งลำดับเดิม (เพื่อให้ตอนปริ้นท์กลับมาเรียงเหมือนเดิมได้)
    double weight; //* น้ำหนัก
    double value; //* มูลค่า
    double ratio; //* ความคุ้มค่า (value / weight)
    double fraction; //* สัดส่วนที่ถูกเลือกหยิบ (0.0 ถึง 1.0)
    //* Constructor กำหนดค่าเริ่มต้น
    Item(int id, double weight, double value){
        this->id = id;
        this->weight = weight;
        this->value = value;
        this->ratio = value / weight;
        this->fraction = 0.0; // เริ่มต้นยังไม่ถูกหยิบ
    }
};

//? เรียงข้อมูชจากมากไปน้อย ตาม ratio (value / weight)
void sortItemDescending(vector<Item>& arr){
    int n = arr.size();
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j].ratio < arr[j + 1].ratio)
                swap(arr[j], arr[j+1]);
        }
    }
}

//? ฟังก์ชันสำหรับคำนวณ Fractional Knapsack โดยเฉพาะ
double calculateKnapsack(vector<Item>& items, double maxWeight){
    //@ 1. จัดเรียงสิ่งของตามความคุ้มค่า (Greedy Choice)
    sortItemDescending(items);
    double totalValue = 0.0; //* เก็บมูลค่ารวมสูงสุด
    double remainingWeight = maxWeight;
    //@ 2. เริ่มหยิบของใส่กระเป๋า
    for(int i = 0; i < items.size(); i++){
        if(remainingWeight == 0) break; //* ถ้ากระเป๋าเต็มแล้ว ให้หยุดหยิบ
        if(items[i].weight <= remainingWeight){
            //* ถ้าของชิ้นนี้น้ำหนักน้อยกว่าหรือเท่ากับที่ว่างในกระเป๋า -> หยิบทั้งชิ้น
            items[i].fraction = 1.0;
            totalValue += items[i].value;
            remainingWeight -= items[i].weight;  //* หักลบน้ำหนักกระเป๋า
        }else{
            //* ถ้าของชิ้นนี้หนักกว่าที่ว่าง -> หั่นเอาไปแค่เศษส่วนที่พอดี (Fractional)
            items[i].fraction = remainingWeight / items[i].weight; //* คำนวณสัดส่วนที่หยิบ
            totalValue += items[i].fraction * items[i].value;
            remainingWeight = 0; //* กระเป๋าเต็มแล้ว
        }
    }
    return totalValue; //* คืนค่ามูลค่ารวมสูงสุดกลับไป
}

int main(){
    int n;
    double maxWeight; //* กระเป๋ารับน้ำหนักได้
    //* รับค่าบรรทัดที่ 1 (จำนวน item และ น้ำหนักกระเป๋า)
    cin>>n>>maxWeight;
    vector<double> weights(n), values(n);
    //* รับค่าบรรทัดที่ 2 (น้ำหนักของแต่ละชิ้น)
    for(int i = 0; i < n; i++)
        cin>>weights[i];
    //* รับค่าบรรทัดที่ 3 (มูลค่าของแต่ละชิ้น)
    for(int i = 0; i < n; i++)
        cin>>values[i];
    //* สร้าง Object Item ยัดลง Vector
    vector<Item> items;
    for(int i = 0; i < n; i++)
        items.push_back(Item(i, weights[i], values[i]));
    double totalValue = calculateKnapsack(items, maxWeight); //* คำนวณค่า Value สูงสุด
    //* เตรียมพิมพ์คำตอบ ตั้งค่าให้แสดงทศนิยม 2 ตำแหน่งเป๊ะๆ
    cout<<fixed<<setprecision(2);
    //* เนื่องจาก Items ถูกสลับที่ตอน Sort ไปแล้ว เราต้องสร้าง Array มารับค่าสัดส่วนกลับคืนตาม id เดิม
    vector<double> resultFractions(n, 0.0);
    for(int i = 0; i < n; i++)
        resultFractions[items[i].id] = items[i].fraction;
    //* พิมพ์บรรทัดที่ 1: สัดส่วนการหยิบ
    for(int i = 0; i < n; i++)
        cout<<resultFractions[i]<<" ";
    cout<<endl<<totalValue<<endl;
    return 0;
}

/*
* Test Case1
    Input:  4 25 
            18 15 10 5
            25 24 5 8
    Output: 0.28 1.00 0.00 1.00
            38.94
? Fractional Knapsack Problem (ใช้ Greedy Algorithm)
@ หลักการทำงานของ Greedy ในข้อนี้คือ:
1. หา "ความคุ้มค่า" ของสิ่งของแต่ละชิ้น โดยเอา มูลค่า (Value) หารด้วย น้ำหนัก (Weight)
    ratio = value / weight
2. เรียงลำดับสิ่งของจากคุ้มค่ามากที่สุด (Descending) ไปหาน้อยที่สุด
3. หยิบของที่คุ้มค่าที่สุดใส่กระเป๋าก่อน เวลาหยิบของต้อง update ค่า remainingWeight(-), totalValue(+) 
    ● ถ้าใส่ได้เต็มชิ้นก็หยิบหมด (fraction = 1.00)
    ● ถ้ากระเป๋าเหลือที่ว่างไม่พอ ก็หั่นเอาไปแค่เศษส่วนที่พอดีกับกระเป๋า 
      (fraction = remainingWeight / weight[i]) โดย จะได้ค่า value ของ Item ชิ้นนี้ไปบางส่วน คือ
      fractionValue = value[i] * fraction;
@ ตัวอย่าง
- ให้ n = 4, maxWeight = 25
     id:      0   1   2   3
     weight: 18  15  10   5 
     value:  25  24   5   8
* 1. คำนวณ ratio (value / weight)
    ● ratio id 0 = 25 / 18 = 1.39 
    ● ratio id 1 = 24 / 15 = 1.60 
    ● ratio id 2 = 5 / 10 = 0.50
    ● ratio id 3 = 8 / 5 = 1.60
* 2. เรียงจาก ratio มาก → น้อย
- จะได้ลำดับประมาณนี้: id 1 (1.60), id 3 (1.60), id 0 (1.39), id 2 (0.50)
- (ตัวที่ ratio เท่ากัน ลำดับขึ้นกับ sort แต่ไม่กระทบคำตอบสุดท้าย)
* 3. เริ่มหยิบใส่กระเป๋า (Greedy)
- หยิบ id 1
    ● น้ำหนัก = 15
    ● เหลือที่ว่าง = 25 - 15 = 10
    ● หยิบทั้งชิ้น (fraction = 1.00)
    ● value รวม = 24
- หยิบ id 3
    ● น้ำหนัก = 5
    ● เหลือที่ว่าง = 10 - 5 = 5
    ● หยิบทั้งชิ้น (fraction = 1.00)
    ● value รวม = 24 + 8 = 32
- หยิบ id 0
    ● น้ำหนัก = 18
    ● แต่เหลือพื้นที่แค่ 5
    ● จึงต้อง “หั่นเอาเศษส่วน”
    ● fraction = 5 / 18 ≈ 0.28
    ● มูลค่าที่ได้ = 0.28 × 25 ≈ 6.94
    ● value รวม = 32 + 6.94 = 38.94
    ● กระเป๋าเต็มแล้ว ❌
* 4. ผลลัพธ์ คือ 38.94
*/