//* มีการเรียงข้อมูล Output จากน้อยไปมาก
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int max = INT_MIN;
    int min = INT_MAX;
    vector<int> A(n),B(n);
    for(int i=0;i<n;i++){
        cin>>A[i];
        if(A[i] > max) max = A[i];
        if(A[i] < min) min = A[i];
    }
    for(int i=0;i<n;i++){
        cin>>B[i];
        if(B[i] > max) max = B[i];
        if(B[i] < min) min = B[i];
    }
    int range = max - min + 1; //* ขนาดของ Array ที่จะใช้เก็บข้อมูล
    vector<int> countA(range), countB(range);
    for(int el:A)
        countA[el - min]++; //* ใช้ index = el - min; เพื่อให้ index เริ่มที่ 0 (offset) 
    for(int el:B)
        countB[el - min]++; 
    //@ Intersection
    for(int i=0;i<range;i++){
        if(countA[i] >= 1 && countB[i] >= 1){ //* มีในทั้ง A และ B
            cout<<i + min<<" ";
        }
    }cout<<endl;
    //@ Union
    for(int i=0;i<range;i++){
        if(countA[i] >= 1 || countB[i] >= 1){ //* มีใน A หรือ B อย่างใดอย่างหนึ่ง
            cout<<i + min<<" ";
        }
    }
    cout<<endl;
    //! ที่ 2 loop เรียงข้อมูลไปในตัว เพราะเราวนจากน้อยไปมากอยู่แล้ว และค่าจริงที่เก็บใน countA, countB 
    //  ก็เป็นการแมปค่าตัวเลขไปยัง index ที่เรียงกัน (ค่าจริง = index + min)
    return 0;
}