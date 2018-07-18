/// below code is done in c++ programming language
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define pi pair<int,int>
#define F first
#define S second

#define MAX 100
vector<pi>adj[MAX];
bool visited[MAX];
int minimum_distance[MAX];
map<string,int>str_int;
map<int,string>int_str;
int destination;
int cost[MAX];

struct cmp/// compare function for making priority queue min heap
{
    bool operator ()(pi&a,pi&b)
    {
        return a.F>b.F;
    }

};
/// it takes source as  input ans return the desired minimum distance
int a_star_search(int s)///  i followed wikipedia during implement it
{
    priority_queue<pi,vector<pi>,cmp>priority_Queue;///min heap
    cost[s]=0;///actual  cost
    int h=minimum_distance[s];
    int f=cost[s]+h;

    priority_Queue.push(mp(f,s));/// pair<cost,node>
    while(!priority_Queue.empty())
    {
        pi top=priority_Queue.top();
        int cur_node=top.S;
        int cur_cost=top.F;
        if(cur_node==destination)
        {
            return cost[cur_node];
        }
        priority_Queue.pop();///Add to closed set
        //visited[cur_node]=true;/// remove from open set

        /// loop for each of its neighbors
        for(int i=0;i<adj[cur_node].size();i++)
        {
            int neighbor_node=adj[cur_node][i].F;
            int neighbor_cost=adj[cur_node][i].S;

            //if(visited[node]==false)visited[node]=true;

            int g=cost[cur_node]+neighbor_cost;
            if(g>=cost[neighbor_node])continue;
            cost[node]=g;
            //cout<<int_str[node]<<' '<<cost[node]<<endl;
            int h=minimum_distance[node];
            int f=cost[node]+h;
            priority_Queue.push(mp(f,node));

        }


    }
}
/// this code is for assignment purpose
/// input file is taken from book:(artificial intelligence :a modern approach)
/// all-input is taken from file .only take source as input
/// destination is all time Bucharest
/// minimum distance is given as input
int main()
{
    ifstream in("a_star.txt");
    int node,edge;
    in>>node>>edge;
    int ct=1;
    str_int.clear();
    for(int i=0;i<edge;i++)
    {
        string s1,s2;
        in>>s1>>s2;
        int distance;
        in>>distance;
        //if(str_int.find(s1)==str_int.end())/// not found in map
        if(str_int[s1]==0)
        {
            str_int[s1]=ct;
            int_str[ct]=s1;
            ct++;
        }
        //if(str_int.find(s2)==str_int.end())/// not found in map
        if(str_int[s2]==0)
        {
            str_int[s2]=ct;
            int_str[ct]=s2;
            ct++;
        }

        int ind_s1=str_int[s1];
        int ind_s2=str_int[s2];

        adj[ind_s1].push_back(mp(ind_s2,distance));
        adj[ind_s2].push_back(mp(ind_s1,distance));
    }
    //cout<<ct<<endl;
    /// minimum distance from every node to destination which is Bucharest
    for(int i=0;i<node;i++)
    {
        string s;
        in>>s;
        //cout<<s<<' '<<str_int[s]<<endl;
        int dist;
        in>>dist;
        int ind=str_int[s];
        cost[ind]=9999999;
        minimum_distance[ind]=dist;
    }
    string source;
    cin>>source;
    destination=str_int["Bucharest"];
    int ind_s=str_int[source];

    int ans=a_star_search(ind_s);
    cout<<"ans :"<<ans<<endl;
    return 0;
}
