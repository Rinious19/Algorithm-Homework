#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int left, int right){
	int pivot = arr[right];
	int j = left;
	for(int i=left;i<right;i++){
		if(arr[i] > pivot) //! Descending
			swap(arr[i], arr[j++]);
	}
	swap(arr[right], arr[j]);
	return j;
}

int quickSelect(vector<int>& arr, int left, int right, int kIndex){
	if(left == right) return arr[left];
	int pi = partition(arr, left, right);
	if(pi == kIndex) return arr[pi];
	else if(pi > kIndex)
		return quickSelect(arr, left, pi - 1, kIndex);
	else
		return quickSelect(arr, pi + 1, right, kIndex);
}

int main(){
	int n, k;
	cin>>n>>k;
	int kIndex = k - 1;
	vector<int> arr(n);
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	int result = quickSelect(arr, 0, n - 1, kIndex);
	cout<<result<<endl;
	return 0;
}