#include <iostream>
#include <iomanip>

using namespace std;

//      A - B

// 題目給平行四邊形的 相鄰的兩條邊，也就是 A B C D 這個平行四邊形   A + D = B + C               D ------ C
                                                                            //          |        |
                                                                            //      |        |          
                                                                            //   A ------ B             
int main()
{
    double x1 , x2 , x3 , x4 , y1 , y2 , y3 , y4;
    while ( cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 )
    {
        double ans_x , ans_y;
        
        // 四個點中會有一組座標相同，代表兩條邊共用的端點。
        // 可能重複的組合有：p1 == p3、p1 == p4、p2 == p3、p2 == p4。
        // 找到重複點後，答案座標 = 不重複的兩點相加 - 重複點。
        if ( x1 == x4 && y1 == y4 )                    
        {
            ans_x = x2 + x3 - x1;
            ans_y = y2 + y3 - y1;
        }
        else if ( x1 == x3 && y1 == y3 )
        {
            ans_x = x2 + x4 - x1;
            ans_y = y2 + y4 - y1;
        }
        else if ( x2 == x3 && y2 == y3 )
        {
            ans_x = x1 + x4 - x2;
            ans_y = y1 + y4 - y2;
        }
        else if ( x2 == x4 && y2 == y4 )        
        {

            ans_x = x1 + x3 - x2;
            ans_y = y1 + y3 - y2;
        }
        cout << fixed << setprecision(3) << ans_x << " " << ans_y << endl;
    }
    return 0;

}