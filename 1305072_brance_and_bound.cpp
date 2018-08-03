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

double pathCost(vector<point> arr, vector<int> temp, int V){
    double cost=0;
    for(int i=0;i<V-1;i++) cost+=dist(arr, temp[i], temp[i+1]);

    return cost;
}


bool is_in_path(vector<int> path, int i){
    for(int j=0;j<path.size();j++){
        if(path[j]==i) return true;
    }
    return false;
}


void brance_and_bound(vector<point> arr, vector<int> path, int level, vector<int> &opt_path, double &min_cost){
    if(level < arr.size()-1){
        for(int i=1;i<arr.size();i++){
            if(is_in_path(path, i)==false){
                vector<int> t = path;
                path.push_back(i);
                if(pathCost(arr, path, path.size())<min_cost || min_cost==0)
                    brance_and_bound(arr, path, level+1, opt_path, min_cost);
                path = t;
            }
        }
    }
    else{
        double tcost = cycleCost(arr, path, path.size());
        if(min_cost==0 || tcost<min_cost){
            min_cost = tcost;
            opt_path = path;
        }
        //cout<<tcost<<"  ";for(int i=0;i<path.size();i++) cout<<path[i]<<" ";cout<<endl;
    }
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

    vector<int> path;
    int level=0;
    path.push_back(0);
    //double cost = INT_MAX;  exponential
    double min_cost = 0;
    vector<int> opt_path;

    //clock_t start = clock();
    brance_and_bound(arr, path, level, opt_path, min_cost);    //cost for exponential
    //cout<<(start-clock())/(double)CLOCKS_PER_SEC<<endl;

    for(int i=0;i<V;i++) cout<<arr[opt_path[i]].x<<","<<arr[opt_path[i]].y<<" ";
    double optimalCost = cycleCost(arr, opt_path, opt_path.size());
    cout<<"\nOptimal Cost : "<<optimalCost;

    return 0;
}

