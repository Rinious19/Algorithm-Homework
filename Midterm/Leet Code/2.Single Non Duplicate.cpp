/*
@ โจทย์
- You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.
- Return the single element that appears only once.
* Your solution must run in O(log n) time and O(1) space.
- Example 1:
	Input: nums = [1,1,2,3,3,4,4,8,8]
	Output: 2
*/

#include <bits/stdc++.h>
using namespace std;

int singleNonDuplicate(vector<int>& arr){
	int low = 0;
	int high = arr.size() - 1;
	//* วนลูปจนกว่า low จะชนกับ high
	while(low < high){
		int mid = low + (high - low) / 2;
		//* เทคนิค: ทำให้ mid เป็นเลขคู่เสมอ เพื่อให้ง่ายต่อการเช็คคู่
		if(mid % 2 == 1) 
			mid--; // ถ้า mid เป็นเลขคี่ ให้ถอยหลังมา 1 ช่อง
		//* เช็คคู่ของมันทางขวา
		if(arr[mid] == arr[mid + 1])
			low = mid + 2; // ถ้าคู่ยังถูกต้อง (ตัวที่ index คู่ เหมือนกับตัวถัดไป) แปลว่าตัวเศษต้องอยู่ทางขวาของคู่นี้แน่นอน
		else
			high = mid; // ถ้าไม่เหมือน แสดงว่าระเบียบเสียแล้ว ตัวเศษอาจจะเป็นตัวนี้ (mid) หรืออยู่ทางซ้าย
	}
	return arr[low]; //! เมื่อ low == high นั่นคือคำตอบ
}

int main(){
	vector<int> arr = {1,1,2,3,3,4,4,8,8};
	int result = singleNonDuplicate(arr);
	for(int el:arr) cout<<el<<" "; cout<<endl;
	cout<<"Single Non Duplicate is "<<result<<endl;
	return 0;
}