//* ดูว่าตัวอักษรที่รับมาสามารถสร้าง Palindrome ได้มั้ย
#include <bits/stdc++.h>
using namespace std;

int main(){
	string text;
	cin>>text;
	vector<int> arr;
	for(char c:text)
		arr.push_back(c - 'a');
	sort(arr.begin(), arr.end());
	int countOdd = -1; //* เอาไว้ดูว่าใน text มีจำนวนตัวอักษรกี่ตัว ที่มีจำนวนใน text เป็นเลขคี่
	int currentCount = 1;
	int prevInt = INT_MIN; //* ใช้เปรียบเทียบตัวก่อนหน้า
	for(int el:arr){
		if(el != prevInt){
			if(currentCount == 1) countOdd++;
			currentCount = 1;
		}
		else
			currentCount++;
		prevInt = el; //* บันทึกเป็นค่าก่อนหน้าในรอบถัดไป
	}
    //! ใน Loop ยังไม่ได้เช็คเงื่อนไขกับ Element สุดท้าย
	if(currentCount == 1)
		countOdd++;
    //! palindrome ต้องมีจำนวนความถี่ของตัวอักษรที่เป็นเลขคี่ ได้แค่ 0 หรือ 1 ตัว เช่น
    //* Level มี 1 ตัว คือ v, Mom มี 1 ตัว คือ o, Noon มี 0 ตัว, Racecar มี 1 ตัว คือ e
	if(countOdd > 1) cout<<"No"<<endl; 
	else cout<<"yes";
	return 0;
}

/*
@ Test Case
* 1. input: zoo
     output: yes
* 2. input: yes
     output: no
* 3. input: cacao
     output: yes
* 4. input: multinomiaalcoefficient
     output: yes
* 5. input: racecars
     output: no

*/