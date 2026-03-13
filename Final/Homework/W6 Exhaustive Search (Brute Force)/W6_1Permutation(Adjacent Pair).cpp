#include <bits/stdc++.h>
using namespace std;

//? ฟังก์ชันสำหรับ "ตรวจคำตอบ" และ "แสดงผล"
//* หน้าที่: เช็คว่าในแถวที่เรียงมา มีเลขต้องห้ามอยู่ติดกันไหม?
void checkAndPrint(int permute[], int n, int target1, int target2, int& count){
    int hasAdjacentPair = 0; //* ตัวจับผิด (0 = ไม่เจอคู่ติดกัน, 1 = เจอคู่ติดกัน)
    //@ วนลูปเช็คทีละคู่ (i และ i+1) หา hasAdjacentPair
    for(int i = 0; i < n - 1; i++){ //* ต้องวิ่งถึงแค่ n-2 (หรือ < n-1) เพราะตัวสุดท้ายไม่มีคู่ขวาให้เช็ค
        //* เช็คเงื่อนไข: "ถ้าตัวปัจจุบันเป็น target1 และตัวขวาเป็น target2" หรือ "สลับกัน" (เช่น 1 ติดกับ 3 หรือ 3 ติดกับ 1)
        if((permute[i] == target1 && permute[i + 1] == target2) || (permute[i] == target2 && permute[i + 1] == target1)){
            hasAdjacentPair = 1; //* เจอแล้ว! ผิดกฎ
            break;
        }
    }
    //@ ถ้าตรวจสอบครบแล้ว เจอคู่ที่ติดกัน
    if(hasAdjacentPair == 1){
        for(int i = 0; i < n; i++){ //* พิมพ์สมาชิกในชุดนั้นออกมา
            cout<<permute[i]<<" ";
        }
        cout<<endl;
        count += 1; //* นับคะแนนเพิ่ม (สังเกตว่าเราแก้ที่อยู่ของ count โดยตรงเพราะส่งแบบ &)
    }
}

//? ฟังก์ชันสำหรับ "สร้างการเรียงสับเปลี่ยน" (Permutation Logic)
//* index: ตำแหน่งที่เรากำลังตัดสินใจว่าจะเอาเลขอะไรมาวาง
void generatePermutation(int permute[], int index, int n, int target1, int target2, int& count){
    //@ Base Case: ถ้า index == n แปลว่าเราวางครบทุกตำแหน่งแล้ว (สุดทาง)
    if(index == n){
        checkAndPrint(permute, n, target1, target2, count); //* ส่งไปตรวจคำตอบ
    }
    //@ Recursive Step: การแตกกิ่ง
    //* วนลูปเพื่อลองเอาตัวเลขในตำแหน่ง i มาสลับวางที่ตำแหน่ง index
    for(int i = index; i < n; i++){
        //* 1. Swap (สลับ): ลองเอาตัวที่ i มาวางที่ตำแหน่ง index
        //* เช่น รอบแรก index=0, i=0 (ไม่เปลี่ยน)
        //* รอบสอง index=0, i=1 (สลับเอาตัวที่ 2 มาไว้หน้าสุด)
        swap(permute[index], permute[i]);
        //* 2. Recurse (เรียกตัวเอง): ฟิกซ์ตำแหน่ง index เสร็จแล้ว ไปทำตำแหน่งถัดไป (index + 1)
        generatePermutation(permute, index + 1, n, target1, target2, count);
        //* 3. Backtrack (สลับคืน): สำคัญมาก!
        //* พอทำกิ่งนั้นเสร็จแล้ว ต้องสลับเลขกลับมาที่เดิม เพื่อให้ Loop รอบถัดไปเริ่มต้นจากอาเรย์สภาพเดิม
        swap(permute[index], permute[i]);
    }
}

int main(){
    int n;
    cin>>n;
    if(n >= 2 && n <= 10){
        int permute[n];
        for(int i=0;i<n;i++) permute[i] = i + 1;
        int target1 = 1; //* เลขที่ติดกันตัวที่ 1
        int target2 = 2; //* เลขที่ติดกันตัวที่ 2 (1 กับ 2 อยู่ติดกัน)
        int count = 0; //* ตัวนับจำนวนรูปแบบที่ผ่านเงื่อนไข count = (n - 1)! * 2!
        //* เรียกฟังก์ชันเริ่มจาก index 0
        //* สังเกตการส่ง count เราส่งไปเฉยๆ แต่รับแบบ Reference (&) ในฟังก์ชัน
        generatePermutation(permute, 0, n, target1, target2, count);
        cout<<"count = "<<count<<endl;
    }
    return 0;
}

