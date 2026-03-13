#include <bits/stdc++.h>
using namespace std;

//* อาร์เรย์สำหรับกำหนดทิศทางการเดิน 4 ทิศ: {บน, ล่าง, ซ้าย, ขวา} [cite: 9]
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int R, C;
vector<string> grid;
vector<vector<bool>> visited;

//? ฟังก์ชัน BFS สำหรับสำรวจและหาขนาดของพายุ 1 ลูก
int bfsFindStormSize(int startR, int startC) {
    queue<pair<int, int>> q;
    q.push({startR, startC});
    visited[startR][startC] = true;
    int stormSize = 0;
    while(!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        stormSize++; //* นับจำนวนเมฆพายุที่เชื่อมต่อกัน
        //* ลองเดินไปทั้ง 4 ทิศทาง [cite: 9]
        for(int i = 0; i < 4; i++) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            //* ขอบเขตความปลอดภัย (ต้องไม่ล้นตาราง)
            if(nextR >= 0 && nextR < R && nextC >= 0 && nextC < C) {
                // ถ้าเป็นเมฆพายุ (#) และยังไม่เคยมาเยือน 
                if(grid[nextR][nextC] == '#' && !visited[nextR][nextC]) {
                    visited[nextR][nextC] = true; //* มาร์กไว้ว่ามาเยือนแล้ว
                    q.push({nextR, nextC});       //* เอาเข้าคิวเพื่อไปสำรวจต่อ
                }
            }
        }
    }
    return stormSize;
}

int main() {
    cin>>R>>C;
    grid.resize(R);
    visited.assign(R, vector<bool>(C, false));
    //* รับข้อมูลแผนที่ดาวเทียม [cite: 15]
    for(int i = 0; i < R; i++) 
        cin>>grid[i];
    int maxSize = 0;
    int maxCount = 0;
    //@ กวาดสายตาสำรวจทีละช่องทั้งตาราง
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            //* ค้นพบจุดเริ่มต้นของพายุลูกใหม่! (เป็น # และยังไม่เคยถูกสำรวจในพายุลูกไหนมาก่อน)
            if(grid[i][j] == '#' && !visited[i][j]) {
                // ใช้ BFS กระจายตัวเพื่อหาว่าพายุลูกนี้มีพื้นที่กี่ช่อง
                int currentStormSize = bfsFindStormSize(i, j);
                //* นำมาเทียบเพื่อบันทึกสถิติ
                if(currentStormSize > maxSize) {
                    maxSize = currentStormSize; // ทำลายสถิติใหม่
                    maxCount = 1;               // นับเป็นพายุไซส์ยักษ์ลูกแรกที่เจอ
                } 
                else if(currentStormSize == maxSize) {
                    maxCount++;                 // เจอพายุที่มีขนาดเท่ากับสถิติสูงสุดเพิ่มอีก 1 ลูก
                }
            }
        }
    }
    //* แสดงผลลัพธ์: <ขนาดพายุใหญ่สุด> <จำนวนพายุไซส์นั้น> [cite: 18]
    // หมายเหตุ: ถ้าไม่เจอ # เลย ตัวแปร maxSize และ maxCount จะเป็น 0 อยู่แล้ว ซึ่งตรงเงื่อนไขโจทย์เป๊ะ 
    cout << maxSize << " " << maxCount << "\n";
    return 0;
}

/*
* Test Case1
    Input: 5 6
	       ...#..
	       ..###.
	       ....#.
	       .#....
	       ###...
    Output: 5 1
* Test Case2
    Input: 4 5
		   ##...
		   ##...
		   ...##
		   ...##
    Output: 4 2
* Test Case3
    Input: 3 3
		   #..
		   .#.
		   ..#
    Output: 1 3
* Test Case4
    Input: 2 2
		   ..
		   ..
    Output: 0 0
*/