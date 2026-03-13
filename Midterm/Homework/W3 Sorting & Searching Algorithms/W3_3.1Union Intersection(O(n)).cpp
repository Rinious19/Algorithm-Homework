#include <bits/stdc++.h>
using namespace std;

int main(){
  int n;
  cin>>n;
  vector<int> A(n), B(n);
  int maxValue = -999;
  //* Input vector A B and Find Max Value
  for(int i=0;i<n;i++){
    cin>>A[i];
    if(A[i] > maxValue) maxValue = A[i];
  }
  for(int i=0;i<n;i++){
    cin>>B[i];
    if(B[i] > maxValue) maxValue = B[i];
  }
  /* state: 
      -1 = el ที่มีการ print ในขั้นตอน Union แล้ว
      0 = ไม่มี el ใน A และ B
      1 = มี el ใน A หรือ B
      2 = มี el ใน A และ B
      3 = มี el ใน A และ B และ print ค่าที่ intersect ออกมาแล้ว */
  vector<int> state(maxValue + 1, 0);
  //* ตรวจสอบว่า el A มีที่ index เท่าไหร่บ้าง
  for(int elA:A){
    state[elA] = 1;
  }
  //@ Intersect 
  for(int elB:B){ 
    if(state[elB] == 1) //* ถ้าที่ index elB มีค่า 1 แสดงว่า มีใน A(เราเก็บข้อมูลแค่ A ในตอนนี้)
      state[elB] = 2; 
  }
  for(int elA:A){
    if(state[elA] == 2){ //* ถ้าที่ index elA มีค่า 2 แสดงว่า มีใน A และ B
      cout<<elA<<" ";
      state[elA] = 3;
    }
  }
  cout<<endl;
  //@ Union 
  //* ตรวจสอบว่า el B มีที่ index เท่าไหร่บ้าง
  for(int elB:B){
    state[elB] = 1;
  }
  //* ถ้าที่ index el มีค่า > 0 แสดงว่ามีสมาชิกนั้นอยู่ใน vector
  //* ถ้าที่ index el มีค่า = 0 แสดงว่ามีไม่มีสมาชิกนั้นอยู่ใน vector
  //* ถ้าที่ index el มีค่า < 0 แสดงว่ามีสมาชิกนั้นอยู่ใน vector แต่ print แล้ว
  for(int elA:A){
    if(state[elA] > 0){ 
      cout<<elA<<" ";
      state[elA] = -1; 
    }
  }
  for(int elB:B){
    if(state[elB] > 0){
      cout<<elB<<" ";
      state[elB] = -1;
    }
  }
  return 0;
}