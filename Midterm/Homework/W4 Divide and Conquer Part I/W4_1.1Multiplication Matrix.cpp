#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

//? ฟังก์ชันสำหรับบวกเมทริกซ์
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B){
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

//? ฟังก์ชันคูณแบบ Divide and Conquer (8 Calls)
vector<vector<int>> recursiveMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B){
    int n = A.size();
    //@ Base Case
    if (n == 1){
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    //* ขนาดใหม่สำหรับเมทริกซ์ย่อย (n/2)
    int k = n / 2;
    //@ ประกาศเมทริกซ์ย่อย
    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)), A21(k, vector<int>(k)), A22(k, vector<int>(k));
    vector<vector<int>> B11(k, vector<int>(k)), B12(k, vector<int>(k)), B21(k, vector<int>(k)), B22(k, vector<int>(k));
    //@ แบ่งข้อมูล (Partition)
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }
    //@ 8 Recursive Calls (หัวใจสำคัญของวิธีนี้) คำนวณแต่ละพจน์ของการคูณ
    vector<vector<int>> P1 = recursiveMultiply(A11, B11);
    vector<vector<int>> P2 = recursiveMultiply(A12, B21);
    vector<vector<int>> P3 = recursiveMultiply(A11, B12);
    vector<vector<int>> P4 = recursiveMultiply(A12, B22);
    vector<vector<int>> P5 = recursiveMultiply(A21, B11);
    vector<vector<int>> P6 = recursiveMultiply(A22, B21);
    vector<vector<int>> P7 = recursiveMultiply(A21, B12);
    vector<vector<int>> P8 = recursiveMultiply(A22, B22);
    //@ รวมผลลัพธ์ (Combine)
    //* C11 = P1 + P2 = A11*B11 + A12*B21
    vector<vector<int>> C11 = add(P1, P2);
    //* C12 = P3 + P4 = A11*B12 + A12*B22
    vector<vector<int>> C12 = add(P3, P4);
    //* C21 = P5 + P6 = A21*B11 + A22*B21
    vector<vector<int>> C21 = add(P5, P6);
    //* C22 = P7 + P8 = A21*B12 + A22*B22
    vector<vector<int>> C22 = add(P7, P8);
    //@ ประกอบร่างกลับเป็นเมทริกซ์ใหญ่ C
    vector<vector<int>> C(n, vector<int>(n));
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
    return C;
}

//* ฟังก์ชันหาเลขยกกำลังของ 2 (Padding)
int getNextPowerOfTwo(int n){
    int power = 1;
    while(power < n)
        power *= 2;
    return power;
}

int main(){
    int n;
    cout<<"Enter matrix size (n): ";
    if (!(cin >> n)) return 0;
    int m = getNextPowerOfTwo(n); //* Calculate padded size
    vector<vector<int>> A(m, vector<int>(m, 0));
    vector<vector<int>> B(m, vector<int>(m, 0));
    cout<<"Enter Matrix A:"<<endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> A[i][j];

    cout<<"Enter Matrix B:"<<endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> B[i][j];
    vector<vector<int>> C = recursiveMultiply(A, B);
    cout<<"Result Matrix:"<<endl;
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