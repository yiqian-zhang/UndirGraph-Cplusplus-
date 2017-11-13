#include "Assistance.h"				
#include "AdjMatrixUndirGraph.h"	

int main(void)
{
    try								
    {
        int infity = DEFAULT_INFINITY;
        char vexs[] = {'A', 'B', 'C', 'D', 'E'};
        int m[5][5] = {
            {infity, 2, infity, 3, 4},
            {2, infity, 4, 5, infity},
            {infity, 4, infity, 1, 6},
            {3, 5, 1, infity, infity},
            {4, infity, 6, infity, infity},
        };
        char c = '0', e, e1, e2;
        int n = 5, v, v1, v2, e3;
        
        AdjMatrixUndirGraph<char,int> g(vexs, n, 7);
        
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (m[u][v] != infity) g.InsertArc(u, v,m[u][v]);
        
        while (c != '9')	{
            cout << endl << "1. 图清空.";
            cout << endl << "2. 显示图.";
            cout << endl << "3. 取指定顶点的值.";
            cout << endl << "4. 设置指定顶点的值.";
            cout << endl << "5. 删除顶点.";
            cout << endl << "6. 插入顶点.";
            cout << endl << "7. 删除边.";
            cout << endl << "8. 插入边.";
            cout << endl << "0. 取指定顶点的度数.";
            cout << endl << "a. 求图的连通分量数目.";
            cout << endl << "b. 取指定边的权值.";
            cout << endl << "c. 重置指定边的权值.";
            cout << endl << "9. 退出.";
            cout << endl << "选择功能(1~9):";
            cin >> c;
            switch (c) 		{
                case '1':
                    g.Clear();
                    break;
                case '2':
                    if (g.IsEmpty())
                        cout << "该图为空。" << endl;
                    else
                        g.Display();
                    break;
                case '3':
                    cout << endl << "输入顶点序号（图的顶点序号从0开始）:";
                    cin >> v;
                    g.GetElem(v, e);
                    cout << "序号为" << v << "的顶点为" << e;
                    break;
                case '4':
                    cout << endl << "输入顶点序号（图的顶点序号从0开始）:";
                    cin >> v;
                    cout << endl << "输入" << v <<"号顶点的值:";
                    cin >> e;
                    g.SetElem(v, e);
                    break;
                case '5':
                    cout << endl << "输入被删除顶点的值:";
                    cin >> e;
                    g.DeleteVex(e);
                    break;
                case '6':
                    cout << endl << "输入插入顶点的值:";
                    cin >> e;
                    g.InsertVex(e);
                    break;
                case '7':
                    cout << endl << "输入与被删除边关联的两个顶点值:";
                    cin >> e1 >> e2;
                    v1 = g.GetOrder(e1);
                    v2 = g.GetOrder(e2);
                    g.DeleteArc(v1, v2);
                    break;
                case '8':
                    cout << endl << "输入与插入边关联的两个顶点值:";
                    cin >> e1 >> e2;
                    cout << endl << "输入权值:";
                    cin >> e3;
                    v1 = g.GetOrder(e1);
                    v2 = g.GetOrder(e2);
                    g.InsertArc(v1, v2, e3);
                    break;
                case'0':
                    cout<<endl<<"输入顶点:";
                    cin >> v;
                    g.CountDegree(v);
                    break;
                case'a':
                    g.ConnectedComponent();
                    break;
                case'b':
                    cout << endl << "输入与求权值边关联的两个顶点值:";
                    cin >> e1 >> e2;
                    v1 = g.GetOrder(e1);
                    v2 = g.GetOrder(e2);
                    g.GetWeight(v1,v2,e3);
                    break;
                case'c':
                    cout << endl << "输入与重置权值边关联的两个顶点值:";
                    cin >> e1 >> e2;
                    cout << endl << "输入权值:";
                    cin >> e3;
                    v1 = g.GetOrder(e1);
                    v2 = g.GetOrder(e2);
                    g.SetWeight(v1,v2,e3);
                    break;
            }
        }
    }
    catch (Error err)				
    {
        err.Show();				
    }
    
    system("PAUSE");				
}

