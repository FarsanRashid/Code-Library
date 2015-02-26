#include <bits/stdc++.h>
//( (grid width odd) && (#inversions even) )  ||  ( (grid width even) && ((blank on odd row from bottom) == (#inversions even)) )
#define fwrite() freopen("out.txt","w",stdout)
using namespace std;

int grid[20],manh[20][20];
char path[50];

bool done;
int bound;


int man()
{
    int i,j,r1,c1,r2,c2;
    for(i=1;i<=16;i++)
    {
        r1=(i-1)/4;
        r1++;
        c1=i%4;
        if(c1==0)
        c1=4;
        for(j=1;j<=16;j++)
        {
            r2=(j-1)/4;
            r2++;
            c2=j%4;
            if(c2==0)
            c2=4;
            manh[i][j]=abs(r1-r2)+abs(c1-c2);
        }
    }
}

int h()
{
    int i,k=0;
    for(i=1;i<=16;i++)
    {
       if(grid[i]!=16)
       k=k+manh[grid[i]][i];
    }
    return k;
}

bool solvable()
{
    int i,j,k=0,blnk;
    for(i=1;i<=16;i++)
    {
        if(grid[i]==16)
        {
            blnk=(i-1)/4;
            blnk=4-blnk;
            continue;
        }
        for(j=i+1;j<=16;j++)
        {
            if(grid[j]<grid[i])
               k++;
        }
    }
    if(k%2!=blnk%2)
        return true;
    return false;
}


int mx;
string s;

int solve(int g_val,int h_val,int blank,int mv)
{
    int f_val=g_val+h_val;
    if(h_val==0)
    {
        done=true;
        if(f_val<mx)
        {
            mx=f_val;
            int i=0;
            s.clear();
            while(i<f_val)
            {
                s.push_back(path[i]);
                i++;
            }
        }
        else if(f_val==mx)
        {
            string s2;
            int i=0;
            while(i<f_val)
            {
                s2.push_back(path[i]);
                i++;
            }
            if(s2<s)
            {
                s.clear();
                s=s2;
            }
        }
        return f_val;
    }
    if(f_val>bound)
        return f_val;
    int i,j,k,mv1=1000,mv2=1000,mv3=1000,mv4=1000;
    if(blank%4!=1&&mv!=3)
    {
        path[g_val]='L';
        k=h_val-manh[blank-1][grid[blank-1]];
        swap(grid[blank],grid[blank-1]);
        k=k+manh[blank][grid[blank]];
        mv1=solve(g_val+1,k,blank-1,1);
        swap(grid[blank],grid[blank-1]);
    }
    if(blank>4&&mv!=4)
    {
        path[g_val]='U';
        k=h_val-manh[blank-4][grid[blank-4]];
        swap(grid[blank],grid[blank-4]);
        k=k+manh[blank][grid[blank]];
        mv2=solve(g_val+1,k,blank-4,2);
        swap(grid[blank],grid[blank-4]);
    }
    if(blank%4&&mv!=1)
    {
        path[g_val]='R';
        k=h_val-manh[blank+1][grid[blank+1]];
        swap(grid[blank],grid[blank+1]);
        k=k+manh[blank][grid[blank]];
        mv3=solve(g_val+1,k,blank+1,3);
        swap(grid[blank],grid[blank+1]);
    }
    if(blank<13&&mv!=2)
    {
        path[g_val]='D';
        k=h_val-manh[blank+4][grid[blank+4]];
        swap(grid[blank],grid[blank+4]);
        k=k+manh[blank][grid[blank]];
        mv4=solve(g_val+1,k,blank+4,4);
        swap(grid[blank],grid[blank+4]);
    }
    if(mv4<=mv1&&mv4<=mv2&&mv4<=mv3)
    {
        path[g_val]='D';
        return mv4;
    }
    else if(mv1<=mv2&&mv1<=mv3&&mv1<=mv4)
    {
        path[g_val]='L';
        return mv1;
    }
    else if(mv3<=mv1&&mv3<=mv2&&mv3<=mv4)
    {
        path[g_val]='R';
        return mv3;
    }
    else if(mv2<=mv1&&mv2<=mv3&&mv2<=mv4)
    {
        path[g_val]='U';
        return mv2;
    }
}

int ida(int pos)
{
    bound=h();
    int m=bound;
    while(bound<=35&&!done)
    {
        bound=solve(0,m,pos,10);
    }
    return bound;
}

int main()
{
    int i,j,k,m,n,cs=0;
    man();
    //fwrite();
    cin>>n;
    while(n--)
    {
        cs++;
        for(i=1;i<=16;i++)
        {
            cin>>grid[i];
            if(grid[i]==0)
            {
                grid[i]=16;
                j=i;
            }
        }
        cout<<"Case "<<cs<<": ";
        if(solvable())
        {
            done=false;
            s.clear();
            mx=100000;
            k=ida(j);
            if(done&&k<=35)
            {
                cout<<s;
            }
            else
                cout<<"This puzzle is not solvable.";
        }
        else
        {
            cout<<"This puzzle is not solvable.";
        }
        cout<<endl;
    }
    return 0;
}
