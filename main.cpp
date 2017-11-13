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
            cout << endl << "1. ͼ���.";
            cout << endl << "2. ��ʾͼ.";
            cout << endl << "3. ȡָ�������ֵ.";
            cout << endl << "4. ����ָ�������ֵ.";
            cout << endl << "5. ɾ������.";
            cout << endl << "6. ���붥��.";
            cout << endl << "7. ɾ����.";
            cout << endl << "8. �����.";
            cout << endl << "0. ȡָ������Ķ���.";
            cout << endl << "a. ��ͼ����ͨ������Ŀ.";
            cout << endl << "b. ȡָ���ߵ�Ȩֵ.";
            cout << endl << "c. ����ָ���ߵ�Ȩֵ.";
            cout << endl << "9. �˳�.";
            cout << endl << "ѡ����(1~9):";
            cin >> c;
            switch (c) 		{
                case '1':
                    g.Clear();
                    break;
                case '2':
                    if (g.IsEmpty())
                        cout << "��ͼΪ�ա�" << endl;
                    else
                        g.Display();
                    break;
                case '3':
                    cout << endl << "���붥����ţ�ͼ�Ķ�����Ŵ�0��ʼ��:";
                    cin >> v;
                    g.GetElem(v, e);
                    cout << "���Ϊ" << v << "�Ķ���Ϊ" << e;
                    break;
                case '4':
                    cout << endl << "���붥����ţ�ͼ�Ķ�����Ŵ�0��ʼ��:";
                    cin >> v;
                    cout << endl << "����" << v <<"�Ŷ����ֵ:";
                    cin >> e;
                    g.SetElem(v, e);
                    break;
                case '5':
                    cout << endl << "���뱻ɾ�������ֵ:";
                    cin >> e;
                    g.DeleteVex(e);
                    break;
                case '6':
                    cout << endl << "������붥���ֵ:";
                    cin >> e;
                    g.InsertVex(e);
                    break;
                case '7':
                    cout << endl << "�����뱻ɾ���߹�������������ֵ:";
                    cin >> e1 >> e2;
                    v1 = g.GetOrder(e1);
                    v2 = g.GetOrder(e2);
                    g.DeleteArc(v1, v2);
                    break;
                case '8':
                    cout << endl << "���������߹�������������ֵ:";
                    cin >> e1 >> e2;
                    cout << endl << "����Ȩֵ:";
                    cin >> e3;
                    v1 = g.GetOrder(e1);
                    v2 = g.GetOrder(e2);
                    g.InsertArc(v1, v2, e3);
                    break;
                case'0':
                    cout<<endl<<"���붥��:";
                    cin >> v;
                    g.CountDegree(v);
                    break;
                case'a':
                    g.ConnectedComponent();
                    break;
                case'b':
                    cout << endl << "��������Ȩֵ�߹�������������ֵ:";
                    cin >> e1 >> e2;
                    v1 = g.GetOrder(e1);
                    v2 = g.GetOrder(e2);
                    g.GetWeight(v1,v2,e3);
                    break;
                case'c':
                    cout << endl << "����������Ȩֵ�߹�������������ֵ:";
                    cin >> e1 >> e2;
                    cout << endl << "����Ȩֵ:";
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

