#include <bits/stdc++.h>

using namespace std;

int lps[1000002];
// lps[i] holds length of longest proper prefix that is also proper suffix if the string had ended at index i(inclusive).

int lps[1000002];
string pattern,text;


int compute_lps()
{
    lps[0]=0;
    int i,j;
    j=pattern.size();
    for(int i=1;i<j;i++)
    {
        int len = lps[i-1];
        while(true)
        {
            if(len==0)
            {
                if(pattern[0]==pattern[i])
                    lps[i] = 1;
                else
                    lps[i] = 0;
                break;
            }
            if(pattern[len]==pattern[i])
            {
                lps[i] = len + 1;
                break;
            }
            else
            {
                len = lps[len-1];
            }
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
    for(t=1;t<=T;t++)
    {
        cin>>text>>pattern;
        compute_lps();
        cout<<"Case "<<t<<": "<<kmp()<<endl;
    }
    return 0;
}
