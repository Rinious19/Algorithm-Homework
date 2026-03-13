#include <bits/stdc++.h>
using namespace std;

long long G_Bottom_Up(int n){
    vector<long long> memory(n + 1);
    //@ 1. กำหนดค่า Base Cases → G(0) = 0, G(1) = G(2) = 1 
    memory[0] = 0;
    memory[1] = 1;
    memory[2] = 1;
    //@ 2. เริ่มคำนวณจาก 3 ขึ้นไปจนถึง n (Bottom-Up)
    //* G(n) = G(n - 1) + G(n - 2) - G(n - 3)
    for(int i = 3; i <= n; i++)
        memory[i] = memory[i - 1] + memory[i - 2] - memory[i - 3];
    return memory[n];
}

int main(){
    int n;
    cin>>n;
    long long result =  G_Bottom_Up(n);
    cout<<"G("<<n<<") = "<<result<<endl;
    return 0;
}

/*
* Test Case1
    Input: 7
    Output: 4
@ ตัวอย่าง F(7)
* 0 1 1 2 2 3 3 4
*/