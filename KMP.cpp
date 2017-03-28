#include <bits/stdc++.h>

using namespace std;

int lps[1000002];
// lps[i] holds length of longest proper prefix that is also proper suffix if the string had ended at index i(inclusive).


string pattern,text;

int compute_lps()
{
    lps[0]=0;
    int i,j;
    j=pattern.size();
    for(i=1;i<j;i++)
    {
        if(lps[i-1])
        {
            if(pattern[lps[i-1]]==pattern[i])
                lps[i]=lps[i-1]+1;
            else
            {
                if(pattern[i]==pattern[0])
                    lps[i]=1;
                else
                    lps[i]=0;
            }
        }
        else
        {
            if(pattern[i]==pattern[0])
                lps[i]=1;
            else
                lps[i]=0;
        }
    }
}



int kmp()
{
    int m=pattern.size(),n=text.size(),i,j=0,val=0;
    for(i=0;i<n;)
    {
        if(text[i]==pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            if(j==0)
            {
                i++;
            }
            else
            {
                j=lps[j-1];
            }
        }
        if(j==m)
        {
            //cout<<"pattern found at "<<i-j<<endl;
            val++;
            j=lps[j-1];
        }
    }
    return val;
}

int main()
{
    int t,T;
    cin>>T;
    getchar();
    for(t=1;t<=T;t++)
    {
        getline(cin,text);
        getline(cin,pattern);
        compute_lps();
        cout<<"Case "<<t<<": "<<kmp()<<endl;
    }
    return 0;
}
