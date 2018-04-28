#include<bits/stdc++.h>
#define ll long long
using namespace std;

void smith_waterman(string &a,string &b,ll s,ll mm,ll g){             //Dynamic Programming Function for finding alignment 
    
    ll n,m,max_score=0,iidx=0,jidx=0;             
    n=a.length();
    m=b.length();   
    ll dp[n+1][m+1];
    int bt[n+1][m+1];        //Declaration of matrix

    for(ll i=0;i<=n;i++){
        dp[i][0]=0;  
        bt[i][0]=0;           //Initialisation
    }
    for(ll j=0;j<=m;j++){
        dp[0][j]=0;
        bt[0][j]=0;
    }

    for(ll i=1;i<=n;i++){       //Computation
        for(ll j=1;j<=m;j++){
            (a[i-1]==b[j-1]) ? dp[i][j]=dp[i-1][j-1]+s : dp[i][j]=dp[i-1][j-1]+mm;
            dp[i][j]=max(max(dp[i][j],(ll)0),max(dp[i-1][j]+g,dp[i][j-1]+g));
           
            if(dp[i][j]==dp[i-1][j-1]+s && a[i-1]==b[j-1]) bt[i][j]=2;
            else if(dp[i][j]==dp[i-1][j]+g) bt[i][j]=3;
            else if(dp[i][j]==dp[i][j-1]+g) bt[i][j]=1;
            else bt[i][j]=2;

            if(max_score<dp[i][j]){
                max_score=dp[i][j];
                iidx=i;
                jidx=j;
            }
        
        }
    }

    
    cout<<"\nScore: "<<max_score<<endl;

    string ans1="",ans2="";
    ll i=iidx,j=jidx;
    while(bt[i][j]>0){
        if(bt[i][j]==2){
            ans1=a[i-1]+ans1;
            ans2=b[j-1]+ans2;
            i--;j--;
        }
        else if(bt[i][j]==1){
            ans1="_"+ans1;
            ans2=b[j-1]+ans2;
            j--;
        }
        else if(bt[i][j]==3){
            ans1=a[i-1]+ans1;
            ans2="_"+ans2;
            i--;
        }
    }
    cout<<"\nAlignment:\n"<<ans1<<'\n'<<ans2<<endl;
}

int main(){                
    string a,b;             //Declaration of Variables
    ll scoring;
    ll gap_penalty,mismatch;

    cout<<"\n--- Program for DNA/RNA Sequence Alignment ---\n";
    cout<<"\nMatch Score: ";          //Input
    cin>>scoring;
    cout<<"\nMismatch Score: ";
    cin>>mismatch;
    cout<<"\nGap Penalty: ";
    cin>>gap_penalty;
    cout<<"\nSequence 1: ";
    cin>>a;
    cout<<"\nSequence 2: ";
    cin>>b;
            
    smith_waterman(a,b,scoring,gap_penalty,mismatch);       //Alignment

    return 0;
}