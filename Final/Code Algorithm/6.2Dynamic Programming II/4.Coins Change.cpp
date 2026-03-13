#include <bits/stdc++.h>
using namespace std;

// ใช้ 1e9 แทน 10e8 เพื่อหลีกเลี่ยงปัญหา Type Casting เป็น double ในบางคอมไพเลอร์
const int INF = 1e9; 

void findChanges(vector<int>& coinsValue, vector<int>& numCoins, int changes) {
    int N = coinsValue.size();
    // dp[i][j] = จำนวนเหรียญน้อยที่สุดเมื่อพิจารณาถึงเหรียญชนิดที่ i และทำยอดได้ j
    vector<vector<int>> dp(N + 1, vector<int>(changes + 1, INF));
    // pick[i][j] = เก็บว่าในสถานะนี้ เราใช้เหรียญชนิดที่ i ไปกี่เหรียญ (เพื่อย้อนรอย)
    vector<vector<int>> pick(N + 1, vector<int>(changes + 1, 0));
    dp[0][0] = 0; // Base Case: ยอด 0 ใช้เหรียญ 0
    for(int i = 1; i <= N; i++) {
        int val = coinsValue[i-1];
        int limit = numCoins[i-1];
        for(int j = 0; j <= changes; j++) {
            // ทางเลือกที่ 1: ไม่หยิบเหรียญชนิดนี้เลย (ดึงคำตอบจากแถวบน)
            dp[i][j] = dp[i-1][j];
            pick[i][j] = 0;
            // ทางเลือกที่ 2: ลองหยิบเหรียญชนิดนี้ตั้งแต่ 1 ถึง limit เหรียญ
            for(int k = 1; k <= limit; k++) {
                if (j >= k * val) {
                    // ถ้าหยิบแล้วยอดเงินไม่เกิน และสถานะก่อนหน้าสามารถทำได้
                    if (dp[i-1][j - k * val] != INF) {
                        // ถ้าจำนวนเหรียญรวมน้อยกว่าเดิม ให้อัปเดตค่าและจดไว้ว่าหยิบกี่เหรียญ
                        if (dp[i-1][j - k * val] + k < dp[i][j]) {
                            dp[i][j] = dp[i-1][j - k * val] + k;
                            pick[i][j] = k;
                        }
                    }
                } else {
                    break; // ถ้ายอดเงิน j ไม่พอให้หยิบ k เหรียญแล้ว ก็หยุดลูป k ได้เลย
                }
            }
        }
    }
    // --- ส่วนแสดงผลลัพธ์ ---
    if(dp[N][changes] == INF) {
        cout << "impossible" << endl;
    } else {
        cout << dp[N][changes] << endl;
        // ใช้ greater<int> เพื่อให้ map เรียง key จากมากไปน้อยให้อัตโนมัติตามโจทย์
        map<int, int, greater<int>> resultCount;
        int curr = changes;
        // ย้อนรอยจากแถวล่างสุด ขึ้นไปแถวบนสุด
        for(int i = N; i >= 1; i--) {
            int k = pick[i][curr]; // ดูว่าใช้เหรียญชนิดนี้ไปกี่เหรียญ
            if (k > 0) {
                resultCount[coinsValue[i-1]] += k;
                curr -= k * coinsValue[i-1]; // หักยอดเงินออกเพื่อไปหาเหรียญชนิดถัดไป
            }
        }
        // ปริ้นท์รายละเอียดเหรียญ [มูลค่า]:[จำนวน]
        for(auto const& [val, count] : resultCount) {
            cout << val << ":" << count << endl;
        }
    }
}

int main(){
    int numTypeCoin;
    cin>>numTypeCoin;
    vector<int> coinsValue(numTypeCoin);
    for(int i=0; i<numTypeCoin; i++)
        cin>>coinsValue[i];
    vector<int> numCoins(numTypeCoin);
    for(int i=0; i<numTypeCoin; i++)
        cin>>numCoins[i];
    int changes;
    cin>>changes;
    findChanges(coinsValue, numCoins, changes);
    return 0;
}

/*
* Test Case1
    Input: 3
           1 2 5
           10 20 10
           1000
    Output: impossible
* Test Case2
    Input: 3
           1 10 20
           5 2 3
           85
    Output: 10
            20:3
            10:2
            1:5
*/