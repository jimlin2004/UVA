#include <bits/stdc++.h>
using namespace std;


/*
    很麻煩的模擬題
    1. 觀察到水量等於需要的時間
    2. 找左邊最高高度LH，右邊最高高度RH
    3. 以LH跟RH的高度比較確認最終是左邊溢出還是右邊溢出或是兩邊溢出(分情況討論)
    4. 分情況討論時，分成左邊水池vL、中間水池vCenter、右邊水池vR去計算答案
    細節看下方程式
*/

int leftx, rightx;
int Lheights[1005];
int Rheights[1005];
int numL, numR;
int LH, RH; // 左邊最高以及右邊最高的高度
int reqL[1005]; // 左邊要溢出時需要的水量
int reqR[1005]; // 右邊要溢出時需要的水量


int main()
{
    while (scanf("%d %d", &leftx, &rightx))
    {
        if (leftx == 0 && rightx == 0)
            break;

        numL = (-1 - leftx) / 2 + 1;
        for (int i = 0; i < numL; ++i)
            scanf("%d", &Lheights[numL - i - 1]); // Lheights要倒過來存比較方便

        numR = (rightx - 1) / 2 + 1;
        for (int i = 0; i < numR; ++i)
            scanf("%d", &Rheights[i]);

        // 找到從0到左最高的高度
        LH = *max_element(Lheights, Lheights + numL);
        // 找到從0到右最高的高度
        RH = *max_element(Rheights, Rheights + numR);

        // 計算出左邊要溢出時，每一個區間會有的水量
        // 要往左邊溢出，該區間的水位需要高於左邊所有檔板的最高高度
        reqL[numL - 1] = Lheights[numL - 1];
        for (int i = numL - 2; i >= 0; --i)
            reqL[i] = max(Lheights[i], reqL[i + 1]);
        
        // 計算出右邊要溢出時，每一個區間會有的水量
        // 要往右邊溢出，該區間的水位需要高於右邊所有檔板的最高高度
        reqR[numR - 1] = Rheights[numR - 1];
        for (int i = numR - 2; i >= 0; --i)
            reqR[i] = max(Rheights[i], reqR[i + 1]);
        
        // 找出兩邊各自第一個能擋住高度為H的檔板，就是中間水池的邊界
        int H = min(LH, RH);
        int LCenterBound = 0;
        while (LCenterBound < numL && Lheights[LCenterBound] < H)
            ++LCenterBound;
        int RCenterBound = 0;
        while (RCenterBound < numR && Rheights[RCenterBound] < H)
            ++RCenterBound;
        
        // 中間水池的水量
        int vCenter = H * (LCenterBound + RCenterBound + 1) * 2;

        int totalTime = 0;

        if (LH > RH) // 最後是右邊溢出
        {
            int vR = 0;
            for (int i = RCenterBound + 1; i < numR; ++i)
                vR += reqR[i] * 2;

            int LStop = LCenterBound;
            // 算算看左邊最多會溢出多少，也就是撞到 > H的檔板為止
            while (LStop < numL && Lheights[LStop] <= H)
                ++LStop;
            int vL = (LStop - LCenterBound) * H * 2;

            // 左邊不一定流滿，所以用min(vL, vR)
            totalTime = vR + vCenter + min(vL, vR);
        }
        else if (LH < RH) // 最後是左邊溢出
        {
            int vL = 0;
            for (int i = LCenterBound + 1; i < numL; ++i)
                vL += reqL[i] * 2;

            int RStop = RCenterBound;
            // 算算看右邊最多會溢出多少，也就是撞到 > H的檔板為止
            while (RStop < numR && Rheights[RStop] <= H)
                ++RStop;
            int vR = (RStop - RCenterBound) * H * 2;

            // 右邊不一定流滿，所以用min(vL, vR)
            totalTime = vL + vCenter + min(vL, vR);
        }
        else // 兩邊一樣高
        {
            // 左邊額外的水量
            int vL = 0;
            for (int i = LCenterBound + 1; i < numL; ++i)
                vL += reqL[i] * 2;

            // 右邊額外的水量
            int vR = 0;
            for (int i = RCenterBound + 1; i < numR; ++i)
                vR += reqR[i] * 2;
            
            // min是因為選擇先溢出的水量
            totalTime = vCenter + 2 * min(vL, vR);
        }

        printf("%d\n", totalTime);
    }

    return 0;
}