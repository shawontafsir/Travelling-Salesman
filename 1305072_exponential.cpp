#include <bits/stdc++.h>
using namespace std;

struct point{
    int x;
    int y;
};

double dist(vector<point> arr, int i, int j){
    return sqrt((arr[i].x-arr[j].x)*(arr[i].x-arr[j].x)+(arr[i].y-arr[j].y)*(arr[i].y-arr[j].y));
}


double cycleCost(vector<point> arr, vector<int> temp, int V){
    double cost=0;
    for(int i=0;i<V;i++){
        if(i==V-1){
            cost+=dist(arr, temp[i], temp[0]);
        }
        else{
            cost+=dist(arr, temp[i], temp[i+1]);
        }
    }
    return cost;
}

/* for exponential(permutation times):

void brance_and_bound(vector<point> arr, vector<int> path, int level, vector<int> &opt_path, double &cost){
    if(level < arr.size()-1){
        for(int i=1;i<arr.size();i++){
            if(is_in_path(path, i)==false){
                vector<int> t = path;
                path.push_back(i);
                brance_and_bound(arr, path, level+1, opt_path, cost);
                path = t;
            }
        }
    }
    else{
        double tcost = cycleCost(arr, path, path.size());
        if(tcost<cost){
            cost = tcost;
            opt_path = path;
        }
    }
}
*/

vector<int> permutation(vector<point> arr, int V){
    vector<int> temp(V);
    for(int i=0;i<V;i++) temp[i]=i;
    vector<int> path = temp;
    double mincost= cycleCost(arr, temp, V);
    do {
        double tcost = cycleCost(arr, temp, V);
        if(tcost<mincost){
            mincost = tcost;
            path = temp;
        }
        //cout<<tcost<<"  ";for(int i=0;i<temp.size();i++) cout<<temp[i]<<" ";cout<<endl;
    }while(next_permutation(temp.begin(), temp.end()) );

    return path;
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

    /*double cost = INT_MAX;
    vector<int> opt_path;
    brance_and_bound(arr, path, level, opt_path, cost);*/
    //clock_t start = clock();
    vector<int> shortestPath = permutation(arr, V);
    //cout<<(start-clock())/(double)CLOCKS_PER_SEC<<endl;

    for(int i=0;i<V;i++) cout<<shortestPath[i]<<" ";
    double optimalCost = cycleCost(arr, shortestPath, V);
    cout<<"\nOptimal Cost : "<<optimalCost;

    return 0;
}
