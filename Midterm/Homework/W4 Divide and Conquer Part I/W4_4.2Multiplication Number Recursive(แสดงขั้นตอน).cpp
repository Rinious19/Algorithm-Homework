#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip> //* สำหรับจัดย่อหน้า

using namespace std;

//? ฟังก์ชันสำหรับจัดย่อหน้าตามความลึกของ Recursion
string getIndent(int depth){
    return string(depth * 4, ' ');
}

//? ฟังก์ชันหาความยาวของตัวเลข
int getLength(long long number){
    string str = to_string(number);
    return str.length();
}

long long multiplyRecursive(long long a, long long b, int depth){
    string indent = getIndent(depth);
    int lengthA = getLength(a);
    int lengthB = getLength(b);
    int n = max(lengthA, lengthB);
    //* แสดงจุดเริ่มต้นของการทำงานในชั้นนี้
    cout<<indent<<">> [Depth "<<depth<<"] Calculate: "<<a<<" * "<<b<<" (n="<<n<<")"<<endl;
    //@ Base Case
    if(n <= 1){
        long long res = a * b;
        cout<<indent<<"   Base Case Reached: "<<a<<" * "<<b<<" = "<<res<<endl;
        return res;
    }
    //@ Partition
    int halfN = n / 2; //! ปัดเศษลง
    long long splitter = pow(10, halfN);
    long long a1 = a / splitter;
    long long a2 = a % splitter;
    long long b1 = b / splitter;
    long long b2 = b % splitter;
    cout<<indent<<"   Split: "<<endl;
    cout<<indent<<"     a -> "<<a1<<" | "<<a2<<endl;
    cout<<indent<<"     b -> "<<b1<<" | "<<b2<<endl;
    cout<<indent<<"     (Splitter 10^"<<halfN<<" = "<<splitter<<")"<<endl;
    //@ Recursive Calls
    cout<<indent<<"   --- Finding A (a1*b1) ---"<<endl;
    long long A = multiplyRecursive(a1, b1, depth + 1);
    cout<<indent<<"   --- Finding B (a2*b1) ---"<<endl;
    long long B = multiplyRecursive(a2, b1, depth + 1);
    cout<<indent<<"   --- Finding C (a1*b2) ---"<<endl;
    long long C = multiplyRecursive(a1, b2, depth + 1);
    cout<<indent<<"   --- Finding D (a2*b2) ---"<<endl;
    long long D = multiplyRecursive(a2, b2, depth + 1);
    //@ Combine
    long long term1 = A * pow(10, 2 * halfN);
    long long term2 = (B + C) * splitter;
    long long term3 = D;
    long long result = term1 + term2 + term3;
    cout<<indent<<"   Combine Step:"<<endl;
    cout<<indent<<"     A * 10^"<<(2 * halfN)<<" = "<<A<<" * "<<(long long)pow(10, 2 * halfN)<<" = "<<term1<<endl;
    cout<<indent<<"     (B + C) * 10^"<<halfN<<" = ("<<B<<" + "<<C<<") * "<<splitter<<" = "<<term2<<endl;
    cout<<indent<<"     D = "<<term3<<endl;
    cout<<indent<<"  <<Result for "<<a<<"*"<<b<<" = "<<result<<endl;
    return result;
}

int main(){
    long long numA = 4568;
    long long numB = 3275;
    cout<<"=== Start Multiplication Trace ==="<<endl;
    long long finalResult = multiplyRecursive(numA, numB, 0);
    cout<<"=================================="<<endl;
    cout<<"Final Answer: "<<finalResult<<endl;
    return 0;
}