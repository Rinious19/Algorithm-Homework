#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

//? โครงสร้างข้อมูลสำหรับจุด (x, y)
class Point {
public:
    int x, y;
};

//? function ช่วยเปรียบเทียบสำหรับการ Sort ตามแกน X
//* เรียง x จากน้อยไปมาก ถ้า x เท่ากัน ให้เรียง y จากน้อยไปมาก
bool comparePoints(const Point& a, const Point& b){
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y; //* ถ้า X เท่ากัน ให้เอา Y น้อยขึ้นก่อน (เพื่อให้ตัว Y มากอยู่หลังสุดเวลาเช็ค)
}

//? function หลัก Divide and Conquer
vector<Point> findMaximaDAC(const vector<Point>& points, int left, int right){
    //@ 1. Base Case: ถ้ามีจุดเดียว หรือไม่มีจุด
    if(left > right)
        return {};
    if(left == right)
        return {points[left]};
    //@ 2. Divide: หาจุดกึ่งกลาง
    int mid = (left + right) / 2;
    //@ 3. Conquer: หา Maxima ของฝั่งซ้ายและฝั่งขวา
    vector<Point> leftMaxima = findMaximaDAC(points, left, mid);
    vector<Point> rightMaxima = findMaximaDAC(points, mid + 1, right);
    //@ 4. Combine: รวมคำตอบ
    vector<Point> result;
    //* 4.1 หาค่า Y สูงสุด ของฝั่งขวา (เพื่อนำมาตัดตัวในฝั่งซ้ายทิ้ง)
    int maxRightY = INT_MIN;
    for(const auto& p : rightMaxima)
        maxRightY = max(maxRightY, p.y);
    //* 4.2 กรองฝั่งซ้าย: เอาเฉพาะจุดที่มี Y สูงกว่า maxRightY
    for(const auto& p : leftMaxima){
        if(p.y > maxRightY)
            result.push_back(p);
    }
    //* 4.3 เอาฝั่งขวาทั้งหมดใส่ลงไป (เพราะ X ฝั่งขวาชนะฝั่งซ้ายเสมอ)
    for(const auto& p : rightMaxima)
        result.push_back(p);
    return result;
}

int main(){
    //* ข้อมูลตัวอย่าง
    vector<Point> points = {
        {2, 10}, {5, 8}, {7, 2}, {3, 5}, 
        {6, 11}, {1, 4}, {10, 6}, {8, 9}
    };
    //* ขั้นตอนที่ 0: ต้อง Sort ข้อมูลตามแกน X ก่อนเสมอ
    sort(points.begin(), points.end(), comparePoints);
    //* เรียกใช้ฟังก์ชัน DAC
    vector<Point> maximaSet = findMaximaDAC(points, 0, points.size() - 1);
    //* แสดงผลลัพธ์ (อาจจะไม่เรียงลำดับ)
    //! เพื่อความสวยงาม เราจะ Sort ผลลัพธ์ก่อนแสดงค่า
    sort(maximaSet.begin(), maximaSet.end(), comparePoints);
    cout<<"Maxima Set Points: "<<endl;
    for(const auto& p : maximaSet)
        cout<<"("<<p.x<<", "<<p.y<<") ";
    cout<<endl;
    return 0;
}

/*
- Maxima Set(Skyline) คือ เซตของจุดที่ไม่มีจุดอื่นที่ดีกว่าในทุกมิติ
- นิยาม: จุด A(x1, y1) ถูกครอบงำโดยจุด B(x2, y2) ถ้า x2 >= x1 และ y2 >= y1 โดยที่อย่างน้อยหนึ่งใน
  เงื่อนไขต้องเป็นจริง ดังนั้น จุด A จะไม่อยู่ใน Maxima Set ถ้ามีจุด B ที่ครอบงำมัน
- แต่ถ้าจุด C(x3, y3) มี x3 > x1 แต่ y3 < y1 จุด A จะยังคงอยู่ใน Maxima Set เพราะไม่มีจุดใดที่ครอบงำมัน
  ได้ทั้งสองมิติ ซึ่งจุด C ไม่ได้ครอบงำจุด A
@ แนวคิดหลักของ Divide and Conquer
- ก่อนเริ่ม ต้องเรียงจุดตามแกน X เสมอ เรียงจากน้อยไปมาก แต่ถ้า X เท่ากัน ให้เอา Y น้อยขึ้นก่อน
* 1. Base Case: ถ้ามีจุดเดียวหรือไม่มีจุด ให้คืนค่าจุดนั้น
* 2. Divide: แบ่งจุดออกเป็นสองส่วนที่มีขนาดใกล้เคียงกัน
     - หาจุดกึ่งกลาง (mid) ของช่วงปัจจุบัน
     - แบ่งจุดเป็นซีกซ้าย (left ถึง mid) และซีกขวา (mid+1 ถึง right)
* 3. Conquer: หา Maxima Set ของฝั่งซ้ายและขวาแบบ Recursive
     - หาค่า Maxima Set ของฝั่งซ้าย
     - หาค่า Maxima Set ของฝั่งขวา
* 4. Combine: รวมคำตอบจากทั้งสองฝั่ง
     - หาค่า Y สูงสุดของฝั่งขวา
     - กรองจุดในฝั่งซ้ายที่มีค่า Y น้อยกว่าหรือเท่ากับค่าสูงสุดของฝั่งขวาออก
     - รวมจุดที่เหลือจากฝั่งซ้ายกับจุดทั้งหมดจากฝั่งขวา
* 5. คืนค่า Maxima Set ที่ได้ Recursive จนกว่าจะได้คำตอบสุดท้าย
@ ประสิทธิภาพ (Time Complexity)
- O(n log n): เนื่องจากการแบ่งข้อมูลเป็นสองส่วนใช้เวลา O(log n) และการกรองจุดใช้เวลา O(n) ในแต่ละระดับ
  ไม่มี case ที่ต่างกัน เพราะต้องประมวลผลทุกจุดเสมอ
- T(n) = 2T(n/2) + O(n)
@ ตัวอย่าง
- สมมติข้อมูลหลัง Sort แล้วคือ: P1(2,10), P2(5,8), P3(7,2), P4(10,6)
* 1. Divide:
    Level 0: (2,10), (5,8), (7,2), (10,6)
        ● L: (2,10), (5,8)
        ● R: (7,2), (10,6)
        Level 1: (2,10), (5,8)
            ● L: (2,10)
            ● R: (5,8)
            Level 2: (2,10)
                - Base Case → Maxima = {(2,10)}
            Level 2: (5,8)
                - Base Case → Maxima = {(5,8)}
        Level 1: (7,2), (10,6)
            ● L: (7,2)
            ● R: (10,6)
            Level 2: (7,2)
                - Base Case → Maxima = {(7,2)}
            Level 2: (10,6)
                - Base Case → Maxima = {(10,6)}
* 2. Conquer & Combine
    📌 Level 1:
    1. {(2,10), (5,8)}
        - Maxima ของฝั่งซ้าย = {(2,10)} //* y ของฝั่งซ้าย > กว่า y ของฝั่งขวา = อยู่ใน Maxima Set
        - Maxima ของฝั่งขวา = {(5,8)} //* ฝั่งขวาอยู่ใน Maxima Set เสมอ
        - Maxima ของ Level 1 = {(2,10), (5,8)}
    2. {(7,2), (10,6)}
        - Maxima ของฝั่งซ้าย = {(7,2)} //* y ของฝั่งซ้าย < กว่า y ของฝั่งขวา = ไม่อยู่ใน Maxima Set
        - Maxima ของฝั่งขวา = {(10,6)} //* ฝั่งขวาอยู่ใน Maxima Set เสมอ
        - Maxima ของ Level 1 = {(10,6)}
    📌 Level 0:
    {(2,10), (5,8), (7,2), (10,6)}
        - Maxima ของฝั่งซ้าย = {(2,10), (5,8)} //* y ของฝั่งซ้าย > กว่า y ของฝั่งขวา = อยู่ใน Maxima Set
        - Maxima ของฝั่งขวา = {(10,6)} //* ฝั่งขวาอยู่ใน Maxima Set เสมอ
        - Maxima ของ Level 0 = {(2,10), (5,8), (10,6)}
- ผลลัพธ์ของ Maxima Set = {(2,10), (5,8), (10,6)}
*/