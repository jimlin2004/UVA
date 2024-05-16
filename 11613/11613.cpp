#include <cstdio>

/*
    最小費用最大流MCMF
    首先，建模
    
    參考 建模1.png
    這樣的建模比較容易想的到
    創一個源點s及終點t
    node 1 有邊指到t代表銷售
    node 1 有邊指到node 2代表month 1囤貨到month2
    node 2, node 3 ...一路建下去
    
    然而這樣的有個主要的問題是
    我沒辦法分辨出
    如month 1囤貨到month 2再由month 2銷售出去的量
    以及month 2製造且month 2當月即銷售的量
    這兩種量的意義，cost不同
    所以需要換一種建法

    拆點(參考 建模2.png)
    node 1拆出一個node 1'
    node 2拆出一個node 2'
    node 3...
    node 1有邊連向node 1', node 2'...(根據題目的E_i決定連向多少個node)
    node 2...
    統一由node 1', node 2'...連向t代表每個月的銷售量
    但與 建模1.png不同的在於可以分辨出囤多少的貨到那些月份
    如 建模2.png中node 1 -> node 2' -> t即代表month 1囤貨到month 2且在month 2銷售

    邊上屬性(參考 建模3.png)
    首先，s到month 1, 2 ...的邊
    它們的屬性是<最多那個month能生產多少, 每單位生產成本>
*/

int main()
{
    return 0;
}