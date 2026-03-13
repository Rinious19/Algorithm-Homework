#include <bits/stdc++.h>
using namespace std;

//* Space Complexity = O(1)
unsigned long long fiboBottomUpOptimized(int n){
    int current; //* F(i - 2) + F(i - 1)
    int prev2 = 0; //* F(i - 2)
    int prev1 = 1; //* F(i - 1)
    for(int i = 2; i <= n; i++){
        current = prev2 + prev1; 
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

int main(){
    int n;
    cin>>n;
    unsigned long long result = fiboBottomUpOptimized(n);
    cout<<"Fibo("<<n<<") = "<<result<<endl;
    return 0;
}