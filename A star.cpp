//Implementation of A* for UVA problem 10181.Can not pass time limit.Use IDA*
//#include <bits/stdc++.h>
#include<cstdio>
#include<sstream>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<algorithm>
#include<set>
#include<queue>
#include<stack>
#include<list>
#include<iostream>
#include<fstream>
#include<numeric>
#include<string>
#include<vector>
#include<cstring>
#include<map>
#include<iterator>
#include<limits>
#include<iomanip>
#define inf 10000000
#define Max(v) *max_element(v.begin(),v.end())
#define Min(v) *min_element(v.begin(),v.end())
#define inp1(x) scanf("%d",&x)
#define inp2(x,y) scanf("%d %d",&x,&y)
#define Unique(v) v.resize(unique(v.begin(),v.end())-v.begin())
#define Sort(v) sort(v.begin(),v.end(),greater<int>());
#define fread() freopen("inp.txt","r",stdin)
#define fwrite() freopen("out.txt","w",stdout)
#define mem(n,m) memset(n,m,sizeof n)
int Set(int N,int pos){return N=N | (1<<pos);}
int reset(int N,int pos){return N= N & ~(1<<pos);}
bool check(int N,int pos){return (bool)(N & (1<<pos));}
int cnt_leading_zero_bits(int N){return __builtin_clz(N);}
int cnt_trailing_zero_bits(int N){return __builtin_ctz(N);}
int cnt_no_of_bits_on(int N){return __builtin_popcount(N);}
int mod_of_negative_number(int n,int m){return ((n%m)+m)%m;}
// solvability of a puzzle board( (grid width odd) && (#inversions even) )  ||  ( (grid width even) && ((blank on odd row from bottom) == (#inversions even)) )
//catalan(n+1)=(2*(2*n+1)*catalan(n))/(n+2) ... catalan(0)=1
//priority_queue< int, vector<int>, greater<int> > PQ;// keeps in ascending order
// bool operator < ( const node& b ) const


using namespace std;


int manh[20][20];

bool done;
int bound;

int man()
{
    int i,j,r1,c1,r2,c2;
    for(i=0;i<16;i++)
    {
        r1=i/4;
        r1++;
        c1=(i+1)%4;
        if(c1==0)
        c1=4;
        for(j=0;j<16;j++)
        {
            r2=j/4;
            r2++;
            c2=(j+1)%4;
            if(c2==0)
            c2=4;
            manh[i][j]=abs(r1-r2)+abs(c1-c2);
        }
    }
}

int h(vector<int>grid)
{
    int i,k=0;
    for(i=0;i<16;i++)
    {
       if(grid[i]!=0)
       k=k+manh[i][grid[i]-1];
    }
    return k;
}

bool solvable(vector<int> grid)
{
    int i,j,k=0,blnk;
    for(i=0;i<16;i++)
    {
        if(grid[i]==0)
        {
            blnk=i/4;
            blnk=4-blnk;
            continue;
        }
        for(j=i+1;j<16;j++)
        {
            if(grid[j]<grid[i]&&grid[j]!=0)
               k++;
        }
    }
    if(k%2!=blnk%2)
        return true;
    return false;
}


int mx;
string s;

struct node
{
    string path;
    vector<int>board;
    int h_val,g_val,blank_position;
    bool operator < ( const node& b ) const
    {
        return h_val+g_val>b.h_val+b.g_val;
    }
}st1,st2;

int main()
{
    int i,j,k,m,n,cs=0;
    string ans;
    man();
    //fwrite();
    cin>>cs;
    while(cs--)
    {
        st1.board.clear();
        for(i=0;i<16;i++)
        {
            cin>>m;
            if(m==0)
            {
                st1.blank_position=i;
            }
            st1.board.push_back(m);
        }
        if(solvable(st1.board))
        {
            map< vector<int>,int>mp;
            priority_queue<node>pq;
            st1.g_val=0;
            st1.h_val=h(st1.board);
            pq.push(st1);
            st1.path.clear();
            st1.path="";
            int cost=51,f_val;
            while(!pq.empty())
            {
                st1=pq.top();
                pq.pop();
                f_val=st1.h_val+st1.g_val;
                if(f_val>cost||f_val>50)
                    continue;
                if(st1.h_val==0)
                {
                    if(f_val<cost)
                    {
                        cost=f_val;
                        ans=st1.path;
                    }
                    continue;
                }
                if(st1.blank_position%4!=0)
                {
                    st2.blank_position=st1.blank_position-1;
                    st2.g_val=st1.g_val+1;
                    st2.board=st1.board;
                    swap(st2.board[st1.blank_position],st2.board[st1.blank_position-1]);
                    if(mp[st2.board]==0)
                    {
                        st2.path=st1.path;
                        st2.path.push_back('L');
                        k=st1.h_val-manh[st1.board[st1.blank_position-1]-1][st1.blank_position-1];
                        st2.h_val=k+manh[st2.board[st1.blank_position]-1][st1.blank_position];
                        mp[st2.board]=1;
                        pq.push(st2);
                    }
                }
                if(st1.blank_position>3)
                {
                    st2.blank_position=st1.blank_position-4;
                    st2.g_val=st1.g_val+1;
                    st2.board=st1.board;
                    swap(st2.board[st1.blank_position],st2.board[st1.blank_position-4]);
                    if(mp[st2.board]==0)
                    {
                        st2.path=st1.path;
                        st2.path.push_back('U');
                        k=st1.h_val-manh[st1.board[st1.blank_position-4]-1][st1.blank_position-4];
                        st2.h_val=k+manh[st2.board[st1.blank_position]-1][st1.blank_position];
                        mp[st2.board]=1;
                        pq.push(st2);
                    }
                }
                if(st1.blank_position!=3&&st1.blank_position!=7&&st1.blank_position!=11&&st1.blank_position!=15)
                {
                    st2.blank_position=st1.blank_position+1;
                    st2.g_val=st1.g_val+1;
                    st2.board=st1.board;
                    swap(st2.board[st1.blank_position],st2.board[st1.blank_position+1]);
                    if(mp[st2.board]==0)
                    {
                        st2.path=st1.path;
                        st2.path.push_back('R');
                        k=st1.h_val-manh[st1.board[st1.blank_position+1]-1][st1.blank_position+1];
                        st2.h_val=k+manh[st2.board[st1.blank_position]-1][st1.blank_position];
                        mp[st2.board]=1;
                        pq.push(st2);
                    }
                }
                if(st1.blank_position<12)
                {
                    st2.blank_position=st1.blank_position+4;
                    st2.g_val=st1.g_val+1;
                    st2.board=st1.board;
                    swap(st2.board[st1.blank_position],st2.board[st1.blank_position+4]);
                    if(mp[st2.board]==0)
                    {
                        st2.path=st1.path;
                        st2.path.push_back('D');
                        k=st1.h_val-manh[st1.board[st1.blank_position+4]-1][st1.blank_position+4];
                        st2.h_val=k+manh[st2.board[st1.blank_position]-1][st1.blank_position];
                        mp[st2.board]=1;
                        pq.push(st2);
                    }
                }
            }
            if(cost<=50)
                cout<<ans<<endl;
            else
                cout<<"This puzzle is not solvable.\n";
        }
        else
        {
            cout<<"This puzzle is not solvable.";
        }
    }
    return 0;
}
