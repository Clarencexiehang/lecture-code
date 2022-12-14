#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;


#define INFINITE_DISTANCE 65535    // 无限大距离
#define COORDINATE_RANGE 100.0    // 横纵坐标范围为[-100,100]


typedef struct Point
{// 二维坐标上的点Point
    double x;
    double y;
}Point;

double Distance(Point a, Point b)
{//平面上任意两点对之间的距离公式计算
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool compareX(Point a, Point b)
{//自定义排序规则：依照结构体中的x成员变量升序排序
    return a.x < b.x;
}

bool compareY(Point a, Point b)
{//自定义排序规则：依照结构体中的x成员变量升序排序
    return a.y < b.y;
}

float ClosestPair(Point points[], int length, Point &a, Point &b)
{// 求出最近点对记录，并将两点记录再a、b中
    double distance;                   //记录集合points中最近两点距离
    double d1, d2;                     //记录分割后两个子集中各自最小点对距离
    int i = 0, j = 0, k = 0, x = 0;    //用于控制for循环的循环变量
    Point a1, b1, a2, b2;              //保存分割后两个子集中最小点对

    if (length < 2)
        return INFINITE_DISTANCE;    //若子集长度小于2，定义为最大距离，表示不可达
    else if (length == 2)
    {//若子集长度等于2，直接返回该两点的距离
        a = points[0];
        b = points[1];
        distance = Distance(points[0], points[1]);
    }
    else
    {//子集长度大于3，进行分治求解
        Point *pts1 = new Point[length];     //开辟两个子集
        Point *pts2 = new Point[length];

        sort(points, points + length, compareX);    //调用algorithm库中的sort函数对points进行排序，compareX为自定义的排序规则
        double mid = points[(length - 1) / 2].x;    //排完序后的中间下标值，即中位数

        for (i = 0; i < length / 2; i++)
            pts1[i] = points[i];
        for (int j = 0, i = length / 2; i < length; i++)
            pts2[j++] = points[i];

        d1 = ClosestPair(pts1, length / 2, a1, b1);             //分治求解左半部分子集的最近点
        d2 = ClosestPair(pts2, length - length / 2, a2, b2);    //分治求解右半部分子集的最近点

        if (d1 < d2) { distance = d1; a = a1; b = b1; }            //记录最近点，最近距离
        else { distance = d2; a = a2; b = b2; }

        //merge - 进行子集合解合并
        //求解跨分割线并在δ×2δ区间内的最近点对
        Point *pts3 = new Point[length];

        for (i = 0, k = 0; i < length; i++)                        //取得中线2δ宽度的所有点对共k个
            if (abs(points[i].x - mid) <= distance)
                pts3[k++] = points[i];

        sort(pts3, pts3 + k, compareY);                                       // 以y排序矩形阵内的点集合

        for (i = 0; i < k; i++)
        {
            if (pts3[j].x - mid >= 0)                                             // 只判断左侧部分的点
                continue;
            x = 0;
            for (j = i + 1; j <= i + 6 + x && j < k; j++)            //只需与有序的领接的的6个点进行比较
            {
                if (pts3[j].x - mid < 0)
                {//  假如i点是位于mid左边则只需判断在mid右边的j点即可
                    x++;
                    continue;
                }
                if (Distance(pts3[i], pts3[j]) < distance)
                {//如果跨分割线的两点距离小于已知最小距离，则记录该距离和两点
                    distance = Distance(pts3[i], pts3[j]);
                    a = pts3[i];
                    b = pts3[j];
                }
            }
        }
    }
    return distance;
}



int main()
{
   int num;
   cin>>num;
   Point p[num];
   for(int i=0;i<num;i++){
       cin>>p[i].x>>p[i].y;
   }

    Point a, b;            //最近点对
    double distance;    //点对距离

    distance = ClosestPair(p, num, a, b);
    printf("%.5f %.1f %.1f %.1f %.1f\n",distance,a.x,a.y,b.x,b.y);
    return 0;
}
