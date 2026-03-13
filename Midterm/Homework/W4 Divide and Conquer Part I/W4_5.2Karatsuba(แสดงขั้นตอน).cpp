#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

string getIndent(int depth){
    return string(depth * 4, ' ');
}

int getLength(long long n){
    if(n == 0) return 1;
    string s = to_string(n);
    return s.length();
}

long long karatsubaTrace(long long a, long long b, int depth){
    string indent = getIndent(depth);
    int lenA = getLength(a);
    int lenB = getLength(b);
    int n = max(lenA, lenB);
    cout<<indent<<">> [Depth "<<depth<<"] Multiply("<<a<<", "<<b<<")"<<endl;
    //@ Base Case
    if(n <= 1){
        long long res = a * b;
        cout<<indent<<"   Base Case: "<<res<<endl;
        return res;
    }
    //@ Partition: แบ่งตัวเลขเป็น 2 ส่วน (ซ้ายและขวา)
    int halfN = n/2; //! ปัดเศษลง
    long long splitter = pow(10, halfN);
    long long a1 = a / splitter;
    long long a2 = a % splitter;
    long long b1 = b / splitter;
    long long b2 = b % splitter;
    cout<<indent<<"   Split: a1="<<a1<<", a2="<<a2<<" | b1="<<b1<<", b2="<<b2<<endl;
    //@ Recursive Calls (หาค่า A, B, C)
    long long A = karatsubaTrace(a1, b1, depth + 1);
    long long B = karatsubaTrace(a2, b2, depth + 1);
    long long C = karatsubaTrace(a1 + a2, b1 + b2, depth + 1);
    //@ Combine ขั้นตอน
    long long middleTerm = C - A - B;
    long long result = (A * (long long)pow(10, 2 * halfN)) + (middleTerm * (long long)pow(10, halfN)) + B;
    cout<<indent<<"   Combine:"<<endl;
    cout<<indent<<"     A="<<A<<", B="<<B<<", C="<<C<<endl;
    cout<<indent<<"     Middle (C-A-B) = "<<middleTerm<<endl;
    cout<<indent<<"     Result = "<<result<<endl;
    return result;
}

int main(){
    long long a = 4568;
    long long b = 3275;
    cout<<"--- Start Karatsuba Trace ---"<<endl;
    long long finalRes = karatsubaTrace(a, b, 0);
    cout<<"-----------------------------"<<endl;
    cout<<"Final Answer: "<<finalRes<<endl;
    return 0;
}