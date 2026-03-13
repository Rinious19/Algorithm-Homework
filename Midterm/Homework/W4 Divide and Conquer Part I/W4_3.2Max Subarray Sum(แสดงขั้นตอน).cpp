#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
using namespace std;

string getIndent(int depth) {
    return string(depth * 4, ' ');
}

int maxSubarraySumTrace(const vector<int>& arr, int left, int right, int depth) {
    string indent = getIndent(depth);
    //* แสดงช่วงข้อมูลที่กำลังทำงาน
    cout<<indent<<">> [Depth "<<depth<<"] Check Range ["<<left<<" to "<<right<<"]: { ";
    for(int i=left; i<=right; i++) cout<<arr[i]<<" ";
    cout<<"}"<<endl;
    //@ Base Case
    if (left == right) {
        cout<<indent<<"   Base Case: Return "<<arr[left]<<endl;
        return arr[left];
    }
    int mid = (left + right) / 2;
    //@ Recursive Calls
    int leftMSS = maxSubarraySumTrace(arr, left, mid, depth + 1);
    int rightMSS = maxSubarraySumTrace(arr, mid + 1, right, depth + 1);
    //@ Calculate Crossing Sum
    int currentSum = 0;
    int leftCrossMax = INT_MIN;
    //* วิ่งจาก mid ไปซ้าย
    for(int i = mid; i >= left; i--){
        currentSum += arr[i];
        if (currentSum > leftCrossMax) {
            leftCrossMax = currentSum;
        }
    }
    currentSum = 0;
    int rightCrossMax = INT_MIN;
    //* วิ่งจาก mid+1 ไปขวา
    for(int i = mid + 1; i <= right; i++){
        currentSum += arr[i];
        if (currentSum > rightCrossMax) {
            rightCrossMax = currentSum;
        }
    }
    int crossMSS = leftCrossMax + rightCrossMax;
    //@ Combine & Result
    int finalMax = max({leftMSS, rightMSS, crossMSS});
    cout<<indent<<"   Combine Step:"<<endl;
    cout<<indent<<"     Left Max (L)  = "<<leftMSS<<endl;
    cout<<indent<<"     Right Max (R) = "<<rightMSS<<endl;
    cout<<indent<<"     Cross Max (C) = "<<leftCrossMax<<" + "<<rightCrossMax<<" = "<<crossMSS<<endl;
    cout<<indent<<"  <<Winner for Range ["<<left<<","<<right<<"] is "<<finalMax<<endl;
    return finalMax;
}

int main() {
    vector<int> data = {16, -25, 2, -54, 36, 9, -12, 66};
    cout<<"=== Start Max Subarray Trace ==="<<endl;
    int result = maxSubarraySumTrace(data, 0, data.size() - 1, 0);
    cout<<"================================"<<endl;
    cout<<"Final Answer: "<<result<<endl;
    return 0;
}