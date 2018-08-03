#include <bits/stdc++.h>
using namespace std;

struct point{
    int x;
    int y;
};

double dist(vector<point> arr, int i, int j){
    return sqrt((arr[i].x-arr[j].x)*(arr[i].x-arr[j].x)+(arr[i].y-arr[j].y)*(arr[i].y-arr[j].y));
}


int minKey(double key[], bool mstSet[], int V)
{
   // Initialize min value
   double min = INT_MAX;
   int min_index;

   for (int v = 0; v < V; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;

   return min_index;
}

vector<int> primMST(vector<point> arr, int V)
{
     vector<int> parent(V);
     double key[V];
     bool mstSet[V];

     for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

     key[0] = 0;
     parent[0] = -1;

     for (int count = 0; count < V-1; count++)
     {
        int u = minKey(key, mstSet, V);

        mstSet[u] = true;

        for (int v = 0; v < V; v++)
          if (dist(arr, u, v) && mstSet[v] == false && dist(arr, u, v) <  key[v])
             parent[v]  = u, key[v] = dist(arr, u, v);
     }

     return parent;
}

queue<int> preOrder(vector<point> arr, int V){
    queue<int> order;
    vector<int> parent = primMST(arr, V);
    stack<int> st;
    vector<int> c_ind;
    for(int i=0;i<V;i++) c_ind.push_back(-1);
    st.push(0);
    order.push(0);
    while(!st.empty()){
        int p = st.top();
        for(int i=c_ind[p];i<V;i++){
            if(parent[i]==p){
                parent[i]=-2;
                c_ind[p] = i;
                st.push(i);
                order.push(i);
                break;
            }
            if(i==V-1) st.pop();
        }
    }

    return order;
}

int main()
{
    int V=0;
    vector<point> arr;
    ifstream in("input.txt");
    if (in.is_open())
    {
        string line;
        int i=0;
        while(getline(in,line))
        {
            V++;
            stringstream ss(line);
            string s;
            point p;
            ss>>s;
            p.x = atoi(s.c_str());
            ss>>s;
            p.y = atoi(s.c_str());

            arr.push_back(p);// = p;
        }
        in.close();
    }
    //for(int i=0;i<V;i++) cout<<arr[i].x<<","<<arr[i].y<<endl;

    /*vector<vector<double> > graph(V, vector<double>(V));

    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            double t = dist(arr, i, j);
            graph[i][j] = t;
            graph[j][i] = t;
        }
    }

    for(int i=0;i<V;i++){
        cout<<endl;
        for(int j=0;j<V;j++) cout<<graph[i][j]<<" ";
    }*/
    //clock_t start = clock();
    queue<int> q = preOrder(arr, V);
    //cout<<(double)(start-clock())/(double)CLOCKS_PER_SEC<<endl;

    double cost=0;

    while(!q.empty()){
        int i=q.front();
        cout<<arr[i].x<<","<<arr[i].y<<"  ";
        q.pop();
        if(!q.empty()){
            int j=q.front();
            cost+=dist(arr, i, j);
        }
        else{
            cost+=dist(arr, i, 0);
        }
    }
    cout<<"\ncost : "<<cost;

    return 0;
}
