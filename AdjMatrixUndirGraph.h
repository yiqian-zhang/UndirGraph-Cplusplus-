#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__


template <class ElemType, class WeightType>
class AdjMatrixUndirGraph
{
protected:
    
    int vexNum, vexMaxNum, arcNum;			
    WeightType **arcs;						
    ElemType *vertexes;						
    mutable Status *tag;					
    
public:
  
    AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);
    AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_SIZE);
    ~AdjMatrixUndirGraph();					
    void Clear();			             
    bool IsEmpty();                 
    int GetOrder(ElemType &d) const;
    Status GetElem(int v, ElemType &d) const;
    Status SetElem(int v, const ElemType &d);
    int GetVexNum() const;					
    int GetArcNum() const;				
    int FirstAdjVex(int v) const;		
    int NextAdjVex(int v1, int v2) const;		 
    void InsertVex(const ElemType &d);			
    void InsertArc(int v1, int v2,WeightType n);			     
    void DeleteVex(const ElemType &d);			 
    void DeleteArc(int v1, int v2);			     
    Status GetTag(int v) const;			     
    void SetTag(int v, Status val) const;	  
    AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType,WeightType> &g);	
    AdjMatrixUndirGraph<ElemType,WeightType> &operator =(const AdjMatrixUndirGraph<ElemType,WeightType> &g);
    void Display();	                        
    void CountDegree(const int v);
    void ConnectedComponent( );
    void DFS(int v);
    void GetWeight(int v1, int v2,WeightType& n) const;	 
    void SetWeight(int v1, int v2, WeightType w);
};

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::CountDegree(const int v){
    int n=0;
    if (v < 0)
        throw Error("该顶点不合法!");        
    
    if (vexNum <= v)
        throw Error("该顶点不合法!");
    for(int j = 0 ; j <= vexNum ; j ++)
        if(arcs[v][j]==1)n++;
    cout<<v<<"的度数为:"<<n<<endl;
    return;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::ConnectedComponent(){
    int v=0;
    int n=0;
    for (v = 0; v < GetVexNum(); v++)
        SetTag(v, UNVISITED);
    for (v = 0; v < GetVexNum(); v++)
        
        if (GetTag(v) == UNVISITED){
            n++;
            DFS(v);
        }
    cout<<"连通分量数目为:"<<n<<endl;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::DFS(int v)
{
    ElemType e;
    SetTag(v, VISITED);		
    GetElem(v, e);			
    for (int w = FirstAdjVex(v); w != -1; w = NextAdjVex(v, w))
        if (GetTag(w) == UNVISITED)
            DFS(w);	
}
template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::GetWeight(int v1, int v2,WeightType& n) const{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1不合法!");	
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2不合法!");	
    if (v1 == v2)
        throw Error("v1不能等于v2!");
    if(arcs[v1][v2]!=DEFAULT_INFINITY){
        cout<<"该边的权值为:"<<arcs[v1][v2]<<endl;
        n=arcs[v1][v2];
    }
    else
        cout<<"图中不存在这条边:"<<endl;
}
template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::SetWeight(int v1, int v2, WeightType w){
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1不合法!");	
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2不合法!");	
    if (v1 == v2)
        throw Error("v1不能等于v2!");
    if(arcs[v1][v2]!=DEFAULT_INFINITY){
        arcs[v1][v2]=w;
        arcs[v2][v1]=w;
    }
    else
        cout<<"图中不存在这条边:"<<endl;
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType,WeightType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum)//change	
{
    if (vertexMaxNum < 0)
        throw Error("允许的顶点最大数目不能为负!");      
    
    if (vertexMaxNum < vertexNum)
        throw Error("顶点数目不能大于允许的顶点最大数目!");
    
    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;
    
    vertexes = new ElemType[vexMaxNum];      
    tag = new Status[vexMaxNum];			      
    arcs = (int **)new int *[vexMaxNum];     
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum];
    
    for (int v = 0; v < vexNum; v++) {
        vertexes[v] = es[v];
        tag[v] = UNVISITED;
        for (int u = 0; u < vexNum; u++)
            arcs[v][u] = DEFAULT_INFINITY;
    }
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType,WeightType>::AdjMatrixUndirGraph(int vertexMaxNum)
{
    if (vertexMaxNum < 0)
        throw Error("允许的顶点最大数目不能为负!");
    
    vexNum = 0;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;
    
    vertexes = new ElemType[vexMaxNum];     
    tag = new Status[vexMaxNum];			    
    arcs = (int **)new int *[vexMaxNum];    
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new int[vexMaxNum];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::Clear()
{
    vexNum = 0;
    arcNum = 0;
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirGraph<ElemType,WeightType>::IsEmpty()
{
    return vexNum == 0;
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType,WeightType>::~AdjMatrixUndirGraph()
{
    delete []vertexes;				
    delete []tag;						 
    
    for (int v = 0; v < vexMaxNum; v++)	
        delete []arcs[v];
    delete []arcs;					  
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType,WeightType>::GetOrder(ElemType &d) const
{
    for (int v = 0; v < vexNum; v++)
        if (vertexes[v] == d)
            return v;	    
    return -1;	        
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType,WeightType>::GetElem(int v, ElemType &d) const
{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;	
    else	{
        d = vertexes[v];	 
        return ENTRY_FOUND;
    }
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType,WeightType>::SetElem(int v, const ElemType &d)
{
    if (v < 0 || v >= vexNum)
        return RANGE_ERROR;	
    else	{
        vertexes[v] = d;	
        return SUCCESS;		
    }
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType,WeightType>::GetVexNum() const
{
    return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType,WeightType>::GetArcNum() const
{
    return arcNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType,WeightType>::FirstAdjVex(int v) const	//change
{
    if (v < 0 || v >= vexNum)
        throw Error("v不合法!");
    
    for (int u = 0; u < vexNum; u++)
        if (arcs[v][u] != DEFAULT_INFINITY)
            return u;
    
    return -1;				
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType,WeightType>::NextAdjVex(int v1, int v2) const   //change
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1不合法!");
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2不合法!");	
    if (v1 == v2) throw
        Error("v1不能等于v2!");		
    
    for (int u = v2 + 1; u < vexNum; u++)
        if (arcs[v1][u] != DEFAULT_INFINITY)
            return u;
    
    return -1;						
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::InsertVex(const ElemType &d)		 //change
{
    if (vexNum == vexMaxNum)
        throw Error("图的顶点数不能超过允许的最大数!");
    
    vertexes[vexNum] = d;
    tag[vexNum] = UNVISITED;
    for (int v = 0; v <= vexNum; v++) {
        arcs[vexNum][v] = DEFAULT_INFINITY;
        arcs[v][vexNum] = DEFAULT_INFINITY;
    }
    vexNum++;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::InsertArc(int v1, int v2,WeightType n)	//change
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1不合法!");	
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2不合法!");	
    if (v1 == v2)
        throw Error("v1不能等于v2!");
    
    if (arcs[v1][v2] == DEFAULT_INFINITY)	{	 
        arcNum++;
        arcs[v1][v2] = n;
        arcs[v2][v1] = n;
    }
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::DeleteVex(const ElemType &d)	//change
{
    int v;
    for (v = 0; v < vexNum; v++)
        if	(vertexes[v] == d)
            break;
    if (v == vexNum)
        throw Error("图中不存在要删除的顶点!");	
    
    for (int u = 0; u < vexNum; u++)             
        if (arcs[v][u] != DEFAULT_INFINITY) {
            arcNum--;
            arcs[v][u] = DEFAULT_INFINITY;
            arcs[u][v] = DEFAULT_INFINITY;
        }
    
    vexNum--;
    if (v < vexNum) {
        vertexes[v] = vertexes[vexNum];
        tag[v] = tag[vexNum];
        for (int u = 0; u <= vexNum; u++)
            arcs[v][u] = arcs[vexNum][u];
        for (int u = 0; u <= vexNum; u++)
            arcs[u][v] = arcs[u][vexNum];
    }
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::DeleteArc(int v1, int v2) //change
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1不合法!");	
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2不合法!");	
    if (v1 == v2)
        throw Error("v1不能等于v2!");
    
    if (arcs[v1][v2] !=  DEFAULT_INFINITY)	{
        arcNum--;
        arcs[v1][v2] =  DEFAULT_INFINITY;
        arcs[v2][v1] =  DEFAULT_INFINITY;
    }
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType,WeightType>::GetTag(int v) const
{
    if (v < 0 || v >= vexNum)
        throw Error("v不合法!");	
    
    return tag[v];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::SetTag(int v, Status val) const
{
    if (v < 0 || v >= vexNum)
        throw Error("v不合法!");	
    
    tag[v] = val;
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType,WeightType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType,WeightType> &g)	//change
{
    vexNum = g.vexNum;
    vexMaxNum = g.vexMaxNum;
    arcNum = g.arcNum;
    
    vertexes = new ElemType[vexMaxNum];		
    tag = new Status[vexMaxNum];			
    arcs = (WeightType **)new int *[vexMaxNum];	
    for (int v = 0; v < vexMaxNum; v++)
        arcs[v] = new WeightType[vexMaxNum];
    
    for (int v = 0; v < vexNum; v++)	{	
        vertexes[v] = g.vertexes[v];
        tag[v] = g.tag[v];
        for (int u = 0; u < vexNum; u++)
            arcs[v][u] = g.arcs[v][u];
    }
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType,WeightType> &AdjMatrixUndirGraph<ElemType,WeightType>::operator =(const AdjMatrixUndirGraph<ElemType,WeightType> &g) //change
{
    if (&g != this)	{
        delete []vertexes;			
        delete []tag;						 
        
        for (int v = 0; v < vexMaxNum; v++)	
            delete []arcs[v];
        delete []arcs;					  
        vexNum = g.vexNum;
        vexMaxNum = g.vexMaxNum;
        arcNum = g.arcNum;
        
        vertexes = new ElemType[vexMaxNum];	 
        tag = new Status[vexMaxNum];			 
        arcs = (WeightType **)new WeightType *[vexMaxNum]; 
        for (int v = 0; v < vexMaxNum; v++) 
            arcs[v] = new WeightType[vexMaxNum];	
        
        for (int v = 0; v < vexNum; v++)	{	 
            vertexes[v] = g.vertexes[v];
            tag[v] = g.tag[v];
            for (int u = 0; u < vexNum; u++)
                arcs[v][u] = g.arcs[v][u];
        }
    }
    return *this;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType,WeightType>::Display()   //change
{
    int infity = DEFAULT_INFINITY;          
    for (int v = 0; v < vexNum; v++)
        cout << "\t" << vertexes[v];
    cout << endl;
    
    for (int v = 0; v < vexNum; v++)	{
        cout << vertexes[v];
        for (int u = 0; u < vexNum; u++)
            if(arcs[v][u]==infity)
                cout << "\t" << "none";
            else
                cout << "\t" << arcs[v][u];
        cout << endl;
    }
}

#endif
