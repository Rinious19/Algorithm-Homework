#include <bits/stdc++.h>
using namespace std;

void meanDP(int i, int newX, int nArr, vector<double>& avg){
    double oldSum = avg[i] * (nArr - 1); //* nArr - 1 = num member Old Array
    double meanNew = (oldSum + newX) / nArr;
    avg.push_back(meanNew);
    cout<<"Add "<<newX<<" -> mean = "<<meanNew<<endl;
}

int main(){
    int nArr;
    cin>>nArr;
    vector<double> arr(nArr);
    int sumArr = 0;
    for(int i = 0; i < nArr; i++){
        cin>>arr[i];
        sumArr += arr[i];
    }
    vector<double> avg; 
    avg.push_back(sumArr / nArr);
    //* Show Member of Array
    cout<<"arr = ";
    for(int i = 0; i < nArr; i++)
        cout<<arr[i]<<" ";
    cout<<endl<<"mean = "<<avg[0]<<endl;
    int nAddData;
    cin>>nAddData;
    for(int i = 0; i < nAddData; i++){
        int newX;
        cin>>newX;
        meanDP(i, newX, ++nArr, avg);
    }    
    return 0;
}