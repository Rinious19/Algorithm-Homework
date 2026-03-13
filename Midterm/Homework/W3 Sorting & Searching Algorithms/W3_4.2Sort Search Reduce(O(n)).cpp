#include <bits/stdc++.h>
using namespace std;

//? coutingSort(): O(n)
void countingSort(vector<int>& arr){
    int n = arr.size();
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);
    for(int el:arr)
        count[el - minVal]++;
    for(int i=1;i<range;i++)
        count[i] += count[i - 1];
    vector<int> output(n, 0);
    for(int i=n-1;i>=0;i--){
        int index = arr[i] - minVal;
        int pos = count[index] - 1;
        output[pos] = arr[i];
        count[index]--;
    }
    for(int i=0;i<n;i++)
        arr[i] = output[i];
}

int main(){
    //@ 1. รับข้อมูล
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0;i<n;i++)
        cin>>nums[i];
    //@ 2. เรียงลำดับ (Sort)
    countingSort(nums);
    //@ 3. สร้างสตริงยาว (Concatenate) - แสดงผลบรรทัดที่ 1
    string text = "";
    for(int el:nums)
        text += to_string(el);
    cout<<text<<endl;
    //@ 4. ค้นหาตัวซ้ำสูงสุด (Search Max Consecutive) - แสดงผลบรรทัดที่ 2
    //* 4.1 หาความถี่สูงสุด
    int currentCount = 1;
    int maxCount = 1;
    char prevChar = '\0';
    for(char c:text){
        if(prevChar == c)
            currentCount++;
        else
            currentCount = 1;
        if(currentCount > maxCount) 
            maxCount = currentCount;
        prevChar = c;
    }
    //* 4.2 ทำการหา element ที่ซ้ำมากที่สุด และทำการเรียงข้อมูล
    currentCount = 1;
    prevChar = '\0';
    vector<int> elMaxFrequency;
    for(char c:text){
        if(prevChar == c)
            currentCount++;
        else
            currentCount = 1;
        if(currentCount == maxCount) 
            elMaxFrequency.push_back(c - '0');
        prevChar = c;
    }
    countingSort(elMaxFrequency);
    //* 4.3 ทำการแสดงผล element ที่ซ้ำมากที่สุด แค่ครั้งเดียว เช่น 1112111 แสดงแค่ 1
    int prevInt = -999999;
    for(int el:elMaxFrequency){
        if(prevInt != el)
            cout<<el<<" ";
        prevInt = el;
    }cout<<endl;
    //@ 5. ยุบตัวเลข (Reduce) - แสดงผลบรรทัดที่ 3
    prevChar = '\0';
    for(char c:text){
        if(prevChar != c)
            cout<<c;
        prevChar = c;
    }cout<<endl;
    return 0;
}