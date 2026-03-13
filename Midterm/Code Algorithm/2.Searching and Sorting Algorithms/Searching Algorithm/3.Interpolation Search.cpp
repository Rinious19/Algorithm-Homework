#include <iostream>
#include <vector>
using namespace std;

int interpolationSearch(vector<int>& arr, int target){
    int low = 0;
    int high = arr.size() - 1;
    //@ เงื่อนไข Loop:
    //* 1. low ต้องไม่แซง high
    //* 2. target ต้องอยู่ในช่วงค่าของ [low...high] (ถ้าหลุดช่วงคือไม่เจอแน่ๆ)
    while(low <= high && target >= arr[low] && target <= arr[high]){
        if(arr[low] == arr[high]){ //* ป้องกันการหารด้วยศูนย์ เช่น arr = [8, 8, 8, 8, 8]
            if(arr[low] == target) return low; //* เจอ target
            return -1; //* หาไม่เจอ
        }
        //! สูตร Interpolation (ต้องระวังเรื่อง float/double ในการหาร)
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]));
        if(arr[pos] == target) //* เจอ target
            return pos;
        if(arr[pos] < target) //* ถ้าค่าที่เจอ "น้อยกว่า" เป้าหมาย -> ขยับไปทางขวา
            low = pos + 1;
        else
            high = pos - 1; //* ถ้าค่าที่เจอ "มากกว่า" เป้าหมาย -> ขยับไปทางซ้าย
    }
    return -1; //* หาไม่เจอ
}

int main(){
    //* ข้อมูลเรียงลำดับและกระจายตัวค่อนข้างดี
    vector<int> data = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
    int target = 18;
    int index = interpolationSearch(data, target);
    if(index != -1)
        cout<<"Found "<<target<<" at index "<<index<<endl;
    else
        cout<<"Element not found."<<endl;
    return 0;
}

/*
- Interpolation Search (การค้นหาแบบประมาณค่าในช่วง) คืออัลกอริทึมค้นหาที่พัฒนาต่อยอดมาจาก Binary 
  Search เพื่อให้หาข้อมูลได้เร็วยิ่งขึ้น โดยเลียนแบบพฤติกรรมมนุษย์เวลาเปิดพจนานุกรม
@ คอนเซปต์: ต่างจาก Binary Search ยังไง?
* Binary Search: 
- จะเจาะที่ "ตรงกลาง" เสมอ ไม่ว่าเราจะหาเลขอะไร
* Interpolation Search: 
- จะ "กะประมาณ" ตำแหน่งที่จะเปิด โดยดูจากค่าน้อยหรือมาก
    ● ตัวอย่าง: ถ้าคุณหาคำว่า "Ant" (มด) ในพจนานุกรม เราจะไม่เปิดตรงกลางเล่ม แต่จะเปิด "หน้าแรกๆ" เลย
    ● ตัวอย่าง: ถ้าหาคำว่า "Zebra" (ม้าลาย) เราก็จะเปิด "ท้ายเล่ม" ทันที
! เงื่อนไขสำคัญ: ข้อมูลต้อง เรียงลำดับ (Sorted) และควรมีการกระจายตัวของข้อมูลที่ สม่ำเสมอ เช่น 10, 20, 30,
  40... (ถ้าข้อมูลกระโดดไปมาแบบ 1, 2, 1000, 1005 อัลกอริทึมนี้จะทำงานได้แย่ลง)
@ สูตรคำนวณตำแหน่ง (The Formula)
* pos = low + (((high - low) / (arr[high] - arr[low])) * (target - arr[low]));
    ● (target - arr[low]): ค่าที่เราหา ห่างจากค่าต่ำสุดเท่าไหร่
    ● (arr[high] - arr[low]): ช่วงความกว้างของข้อมูลทั้งหมด (Max - Min)
    ● ความหมาย: เป็นการหา "สัดส่วน" ว่าค่าที่เราหามันอยู่ตรงกี่ % ของช่วงข้อมูล แล้วเอาไปคูณกับช่วง Index
@ Time Complexity (ความซับซ้อนของเวลา)
* 1. Best Case (ดวงดีสุด): O(log(log n))
    ● คือ: ข้อมูลเรียงลำดับและกระจายตัวค่อนข้างดี
    ● อธิบาย: เร็วกว่า Binary Search มาก 
* 2. Worst Case (ดวงซวยสุด): O(n)
    ● คือ: ข้อมูลกระจายตัวแบบทวีคูณ (Exponential) เช่น [1, 2, 4, 8, 16, 32, ...] แล้วเราหาตัวสุดท้าย
          สูตรจะคำนวณผิดพลาดและขยับทีละนิดเดียวครับ
    ● อธิบาย: ช้าเท่ากับ Sequential Search เลย
*/