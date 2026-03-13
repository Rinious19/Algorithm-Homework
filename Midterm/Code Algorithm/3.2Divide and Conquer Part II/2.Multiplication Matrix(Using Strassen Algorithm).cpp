#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//? ฟังก์ชันสำหรับบวกเมทริกซ์
//! ใส่ const & เพื่อป้องกันบัค (C++ ห้ามเอา temporary ไปผูกกับ non-const reference ❌)
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B){
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

//? ฟังก์ชันสำหรับลบเมทริกซ์
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B){
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

//? ฟังก์ชันหลัก Strassen
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B){
    int n = A.size();
    //@ Base Case: ถ้าเหลือ 1x1 ก็คูณกันธรรมดา
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
    //@ แบ่งข้อมูล (Splitting)
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
    //@ คำนวณ M1 ถึง M7
    //! C++ ห้ามเอา temporary ไปผูกกับ non-const reference ❌)
    vector<vector<int>> M1 = strassen(add(A11, A22), add(B11, B22));
    vector<vector<int>> M2 = strassen(add(A21, A22), B11);
    vector<vector<int>> M3 = strassen(A11, subtract(B12, B22));
    vector<vector<int>> M4 = strassen(A22, subtract(B21, B11));
    vector<vector<int>> M5 = strassen(add(A11, A12), B22);
    vector<vector<int>> M6 = strassen(subtract(A21, A11), add(B11, B12));
    vector<vector<int>> M7 = strassen(subtract(A12, A22), add(B21, B22));
    //@ คำนวณ C11, C12, C21, C22
    vector<vector<int>> C11 = add(subtract(add(M1, M4), M5), M7);
    vector<vector<int>> C12 = add(M3, M5);
    vector<vector<int>> C21 = add(M2, M4);
    vector<vector<int>> C22 = add(add(subtract(M1, M2), M3), M6);
    //@ รวมเมทริกซ์ย่อย(C11, C12, C21, C22) กลับเป็นเมทริกซ์ผลลัพธ์(C)
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

//? ฟังก์ชันหาเลขยกกำลังของ 2 ที่ใกล้เคียงที่สุด (Next Power of 2) เพื่อใช้ในการ Padding
int getNextPowerOfTwo(int n){
    int power = 1;
    while(power < n)
        power *= 2;
    return power;
}

int main(){
    int n;
    //* อ่านขนาด Matrix จริง
    if (!(cin >> n)) return 0;
    //* หาขนาดใหม่ที่เป็น Power of 2 (Padding size)
    int m = getNextPowerOfTwo(n);
    //* สร้าง Matrix ขนาด m x m (ส่วนเกินจะเป็น 0 โดยอัตโนมัติ)
    vector<vector<int>> A(m, vector<int>(m, 0));
    vector<vector<int>> B(m, vector<int>(m, 0));
    //* อ่าน Input ใส่แค่ส่วน n x n (ส่วนที่เหลือปล่อยเป็น 0)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin >> A[i][j];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin >> B[i][j];
    }
    //* เรียกใช้ Strassen ด้วยขนาด m (ขนาดที่ Pad แล้ว)
    vector<vector<int>> C = strassen(A, B);
    //* แสดงผลลัพธ์แค่ขนาด n x n
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout<<C[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}

/*
@ Padding
- Padding: การเพิ่มขนาดเมทริกซ์ให้เป็นขนาดที่เหมาะสมกับอัลกอริทึม (เช่น ขนาดเป็นกำลังของ 2)
  โดยการเพิ่มแถวและคอลัมน์ที่มีค่าเป็น 0 เข้าไป
- ตัวอย่าง: เมทริกซ์ขนาด 3x3 จะถูกเพิ่มเป็น 4x4 โดยเพิ่มแถวและคอลัมน์ที่มีค่าเป็น 0
  A = [1 2 3]                   Padded A = [1 2 3 0]
      [4 5 6]                              [4 5 6 0]
      [7 8 9]                              [7 8 9 0]
                                           [0 0 0 0]
  B = [9 8 7]                   Padded B = [9 8 7 0]
      [6 5 4]                              [6 5 4 0]
      [3 2 1]                              [3 2 1 0]
                                           [0 0 0 0]
  A x B = [ 30   24   18]       Padded A x B = [ 30   24  18  0]
          [ 84   69   54]                      [ 84   69  54  0]
          [138  114   90]                      [138  114  90  0]
                                               [  0    0   0  0]
- เมื่อคูณเมทริกซ์ที่ถูก Padding แล้ว ผลลัพธ์ที่ได้จะมีขนาดใหญ่ขึ้น แต่ผลลัพธ์ที่แท้จริงจะอยู่ในส่วน n x n แรก
@ Strassen Algorithm Steps
* 1. Divide: แบ่งเมทริกซ์ A และ B ออกเป็น 4 เมทริกซ์ย่อยขนาด n/2 x n/2
* 2. Conquer: คำนวณค่า M1 ถึง M7 โดยใช้เมทริกซ์ย่อยเหล่านี้
    ● M1 = (A11 + A22) * (B11 + B22)
    ● M2 = (A21 + A22) * B11 
    ● M3 = A11 * (B12 - B22)
    ● M4 = A22 * (B21 - B11)
    ● M5 = (A11 + A12) * B22
    ● M6 = (A21 - A11) * (B11 + B12)
    ● M7 = (A12 - A22) * (B21 + B22)
* 3. Combine: คำนวณเมทริกซ์ผลลัพธ์ C จาก
    ● C11 = M1 + M4 - M5 + M7
    ● C12 = M3 + M5
    ● C21 = M2 + M4
    ● C22 = M1 - M2 + M3 + M6
* 4. รวมเมทริกซ์ย่อย C11, C12, C21, C22 กลับเป็นเมทริกซ์ผลลัพธ์ C ขนาด n x n
*/