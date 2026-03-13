#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

//? ฟังก์ชันช่วยสร้างย่อหน้าตามระดับความลึก
string getIndent(int depth){
    return string(depth * 4, ' ');
}

//? ฟังก์ชันพิมพ์เมทริกซ์
void printMatrix(const vector<vector<int>>& M, string name, int depth){
    string indent = getIndent(depth);
    cout<<indent<<name<<": ["<<M.size()<<"x"<<M.size()<<"]"<<endl;
    for(const auto& row : M){
        cout<<indent<<"  ";
        for(int val : row){
            cout<<setw(4)<<val<<" ";
        }
        cout<<endl;
    }
}

//? ฟังก์ชันบวกเมทริกซ์
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B){
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

//? ฟังก์ชันหลัก: Recursive Matrix Multiply (Standard 8 Calls)
vector<vector<int>> recursiveMultiplyTrace(const vector<vector<int>>& A, const vector<vector<int>>& B, int depth){
    int n = A.size();
    string indent = getIndent(depth);
    cout<<indent<<">> [Depth "<<depth<<"] Multiply Size "<<n<<"x"<<n<<endl;
    //@ Base Case
    if(n == 1){
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        cout<<indent<<"   Base Case: "<<A[0][0]<<" * "<<B[0][0]<<" = "<<C[0][0]<<endl;
        return C;
    }
    int k = n / 2;
    //@ Partition (แบ่งเมทริกซ์)
    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)), A21(k, vector<int>(k)), A22(k, vector<int>(k));
    vector<vector<int>> B11(k, vector<int>(k)), B12(k, vector<int>(k)), B21(k, vector<int>(k)), B22(k, vector<int>(k));
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            A11[i][j] = A[i][j]; A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j]; A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j]; B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j]; B22[i][j] = B[i + k][j + k];
        }
    }
    //@ 8 Recursive Calls (คำนวณ P1 - P8)
    //* สตร:
    // C11 = A11*B11 + A12*B21
    // C12 = A11*B12 + A12*B22
    // C21 = A21*B11 + A22*B21
    // C22 = A21*B12 + A22*B22
    cout<<indent<<"   --- Calculating P1 to P8 ---"<<endl;
    vector<vector<int>> P1 = recursiveMultiplyTrace(A11, B11, depth + 1);
    vector<vector<int>> P2 = recursiveMultiplyTrace(A12, B21, depth + 1);
    vector<vector<int>> P3 = recursiveMultiplyTrace(A11, B12, depth + 1);
    vector<vector<int>> P4 = recursiveMultiplyTrace(A12, B22, depth + 1);
    vector<vector<int>> P5 = recursiveMultiplyTrace(A21, B11, depth + 1);
    vector<vector<int>> P6 = recursiveMultiplyTrace(A22, B21, depth + 1);
    vector<vector<int>> P7 = recursiveMultiplyTrace(A21, B12, depth + 1);
    vector<vector<int>> P8 = recursiveMultiplyTrace(A22, B22, depth + 1);
    //@ Combine (รวมผลลัพธ์)
    vector<vector<int>> C11 = add(P1, P2);
    vector<vector<int>> C12 = add(P3, P4);
    vector<vector<int>> C21 = add(P5, P6);
    vector<vector<int>> C22 = add(P7, P8);
    //@ ประกอบร่างกลับ
    vector<vector<int>> C(n, vector<int>(n));
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
    printMatrix(C, "Result Combined (C)", depth);
    return C;
}

//? ฟังก์ชันหาเลขยกกำลังของ 2 (Padding)
int getNextPowerOfTwo(int n){
    int power = 1;
    while(power < n) power *= 2;
    return power;
}

int main(){
    int n;
    cout<<"Enter matrix size (n): ";
    if(!(cin >> n)) return 0;
    //* Padding ให้เป็น Power of 2 เพื่อความง่ายในการคำนวณ
    int m = getNextPowerOfTwo(n);
    vector<vector<int>> A(m, vector<int>(m, 0));
    vector<vector<int>> B(m, vector<int>(m, 0));
    cout<<"Enter Matrix A ("<<n<<"x"<<n<<"):"<<endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> A[i][j];
    cout<<"Enter Matrix B ("<<n<<"x"<<n<<"):"<<endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> B[i][j];
    cout<<"\n=== Start Standard D&C Trace (8 Recursive Calls) ===\n"<<endl;
    vector<vector<int>> C = recursiveMultiplyTrace(A, B, 0);
    cout<<"\n=== Final Answer ("<<n<<"x"<<n<<") ===\n"<<endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout<<setw(4)<<C[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}

/*
@ หลักการทำงาน
- Divide and Conquer Algorithm สำหรับการคูณเมทริกซ์
- แบ่งเมทริกซ์ A และ B ออกเป็นเมทริกซ์ย่อยขนาด n/2 x n/2 (4 เมทริกซ์ย่อยต่อเมทริกซ์)
- ใช้สมบัติการคูณเมทริกซ์แบบแบ่งย่อย
    C11 = A11*B11 + A12*B21
    C12 = A11*B12 + A12*B22
    C21 = A21*B11 + A22*B21
    C22 = A21*B12 + A22*B22
- คำนวณแบบ Recursive โดยมี 8 Calls ต่อการคูณเมทริกซ์ขนาด n x n
- รวมผลลัพธ์ย่อยกลับเป็นเมทริกซ์ขนาด n x n
*/