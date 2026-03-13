#include <bits/stdc++.h>
using namespace std;

int fnCallCount = 0; //* นับจำนวนครั้งที่ฟังก์ชันถูกเรียกใช้
int tryCount = 0; //* นับจำนวนครั้งที่เราลองเลือกตัวเลขนี้ในลูป

/* 
@param 
 * selectedIndices: อาร์เรย์เก็บ "ตำแหน่ง" ของตัวเลขที่ถูกเลือก
 * currentDepth: บอกว่าตอนนี้เราเลือกตัวเลขมาแล้วกี่ตัว
 * n: จำนวนสมาชิกทั้งหมดในเซต
 * arr: อาร์เรย์ตัวเลขโจทย์
 * currentSum: ผลรวมปัจจุบัน
 * targetSum: ผลรวมที่ต้องการ
 */
void findCombinations(int selectedIndices[], int currentDepth, int n, int arr[], int currentSum, int targetSum){
    fnCallCount++;
    if(currentSum == targetSum){ //* ถ้าผลรวมปัจจุบันเท่ากับเป้าหมาย แสดงผล
        for(int i=0;i<currentDepth;i++)
            cout<<arr[selectedIndices[i]]<<((i != currentDepth - 1)?" + ":"");
        cout<<" = "<<targetSum<<endl;
        return;
    }
    //* หาจุดเริ่มต้นที่จะเลือกตัวถัดไป (เพื่อไม่ให้เลือกซ้ำตัวเดิมหรือย้อนกลับไปตัวก่อนหน้า)
    int startIdx = (currentDepth == 0) ? 0 : selectedIndices[currentDepth - 1] + 1;
    //* วนลูปเพื่อเลือกตัวเลขตัวถัดไปใส่ในตำแหน่งถัดไป (currentDepth)
    for(int i = startIdx; i < n; i++){
        selectedIndices[currentDepth] = i; //* บันทึกว่าเลือกตัวเลข Index ที่ i
        tryCount++; //* นับจำนวนครั้งที่เราลองเลือกตัวเลขนี้
        //! ใช้ arr[i] ไม่ใช่ arr[selectedIndices[i]] เพราะว่า i คือ index ของ arr อยู่แล้ว
        if(currentSum + arr[i] <= targetSum) //* Pruning Condition ถ้าเกินเป้าหมายก็ไม่ต้องไปต่อ 
            findCombinations(selectedIndices, currentDepth + 1, n, arr, currentSum + arr[i], targetSum); 
            //! currentSum + arr[i] อัพเดตผลรวมปัจจุบันใน function call ถัดไป
    }
}

int main(){
    int n = 5;
    int selectedIndices[n]; // * เก็บ Index ของตัวที่เลือก
    int arr[5] = {25, 10, 9, 2, 1};
    int targetSum = 12;
    cout<<"Looking for subsets that sum to "<<targetSum<<"..."<<endl;
    findCombinations(selectedIndices, 0, n, arr, 0, targetSum);
    cout<<"Function Call Count = "<<fnCallCount<<", Try Count = "<<tryCount<<endl;
    return 0;
}

/*
- Pruning (การตัดแต่งกิ่ง) ใน Backtracking คือเทคนิคการ "เลิกเดินต่อ" ในเส้นทางที่เรารู้แน่ๆ แล้วว่า 
  "ไม่มีทางเจอคำตอบ" เพื่อลดจำนวนการเรียกฟังก์ชัน (Recursive Calls) ทำให้โปรแกรมทำงานเร็วขึ้นอย่างมหาศาล
@ จุดที่ควรนับ
* จุดที่ 1: fnCallCount (วางที่หัวฟังก์ชัน)
- จุดนี้คุณวางถูกแล้วครับ มันคือการนับ "จำนวนโหนดที่โปรแกรมตัดสินใจเดินเข้าไป" (Nodes in Decision Tree) 
  ยิ่งเลขนี้ต่ำ แปลว่าโปรแกรมฉลาด (Pruning ได้เยอะ)
* จุดที่ 2: iterationCount (วางใน Loop for) - แนะนำให้เพิ่ม
- จุดนี้จะบอกว่าโปรแกรมต้อง "พยายามเช็คเงื่อนไข" ไปทั้งหมดกี่ครั้ง ก่อนจะตัดสินใจว่าจะเข้าไปรันฟังก์ชันถัดไปหรือไม่
@ เทคนิคเสริม: ทำให้ fnCallCount ลดลงไปอีก (Sort)
- หาก sort(arr, arr + n); จากน้อยไปมาก และใส่ break ในลูป:
    for(int i = startIdx; i < n; i++){
        tryCount++;
        if(currentSum + arr[i] > targetSum) break; //* ถ้าตัวนี้เกิน ตัวถัดไปที่ใหญ่กว่าก็ต้องเกิน!
        selectedIndices[currentDepth] = i;
        findCombinations(selectedIndices, currentDepth + 1, n, arr, currentSum + arr[i], targetSum);
    }
- การใส่ break จะทำให้ทั้ง fnCallCount และ tryCount ลดลงมหาศาล เพราะเราหยุดวนลูปทันทีที่เจอตัวที่
  ใหญ่เกินไป
*/