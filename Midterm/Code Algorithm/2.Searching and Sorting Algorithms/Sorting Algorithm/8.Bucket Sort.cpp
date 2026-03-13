#include <iostream>
#include <vector>
#include <algorithm> //* สำหรับ sort()
using namespace std;

void bucketSort(vector<float>& arr){
    int n = arr.size();
    if(n <= 0) return;
    //@ 1. สร้าง Buckets (Array of Vectors)
    //* สมมติสร้าง n ถัง
    vector<vector<float>> buckets(n);
    //@ 2. กระจายข้อมูลลงถัง (Scatter)
    for(int i = 0; i < n; i++){
        //* สูตรหา Index: n * value (สำหรับค่า 0.0 - 0.999...)
        int bucketIndex = n * arr[i]; 
        buckets[bucketIndex].push_back(arr[i]);
    }
    //@ 3. เรียงข้อมูลภายในแต่ละถัง (Sort Internal)
    for(int i = 0; i < n; i++)
        sort(buckets[i].begin(), buckets[i].end());
    //@ 4. รวบข้อมูลกลับมาที่อาเรย์หลัก (Gather)
    int index = 0;
    for(int i = 0; i < n; i++){
        for(float val : buckets[i]){
            arr[index++] = val;
        }
    }
}

int main(){
    vector<float> data = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    cout<<"Original: ";
    for(float x : data) 
        cout<<x<<" ";
    cout<<endl;
    bucketSort(data);
    cout<<"Sorted:   ";
    for(float x : data) 
        cout<<x<<" ";
    cout<<endl;
    return 0;
}