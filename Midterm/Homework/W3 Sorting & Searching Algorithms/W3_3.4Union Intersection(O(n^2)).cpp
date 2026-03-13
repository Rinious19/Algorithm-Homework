#include <iostream>
#include <vector>
using namespace std;

//? hasValue(): เช็คว่าใน list มีค่า value อยู่หรือยัง?
bool hasValue(vector<int> list, int target){
    for(int member : list){
        if (member == target) 
            return true; //* ถ้ามี return true, ถ้าไม่มี return false
    }
    return false; //* ถ้าไม่มี return false
}

int main(){
    int N; //* รับค่าจำนวนข้อมูล
    cin >> N;
    vector<int> A(N), B(N);
    //@ รับข้อมูลใส่ Vector A และ B 
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < N; i++) cin >> B[i];
    //@ ส่วนหา Intersection (ตัวที่ซ้ำกัน) 
    vector<int> intersectResult;
    for(int memberA : A){
        //* เงื่อนไข: (ต้องมีใน B) และ (ต้องยังไม่เคยถูกเก็บมาก่อน)
        if (hasValue(B, memberA) && !hasValue(intersectResult, memberA))
            intersectResult.push_back(memberA);
    }
    //@ ส่วนหา Union (เอามารวมกัน)
    vector<int> unionResult;
    //* ขั้นแรก: เก็บของ A ให้หมดก่อน (เฉพาะที่ไม่ซ้ำ)
    for(int memberA : A){
        if (!hasValue(unionResult, memberA))
            unionResult.push_back(memberA);
    }
    //* ขั้นสอง: เก็บของ B เฉพาะตัวที่ยังไม่มีใน A
    for(int memberB : B){
        if (!hasValue(unionResult, memberB))
            unionResult.push_back(memberB);
    }
    //@ แสดงผล
    //* บรรทัดที่ 1: Intersection
    for(int i = 0; i < intersectResult.size(); i++)
        cout<<intersectResult[i]<<" ";
    cout<<endl;
    //* บรรทัดที่ 2: Union
    for(int i = 0; i < unionResult.size(); i++) 
        cout<<unionResult[i]<<" ";
    cout<<endl;
    return 0;
}

