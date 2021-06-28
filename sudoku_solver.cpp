//Rules
//each row and column should have the natural number from 1 to n only once
//each small block of sqrt(n)*sqrt(n) should have the natural number from 1 to n only once

#include <iostream>
#include <cmath>
using namespace std;

//This fuction checks if the sudoku is empty at a given index(i,j) or not
bool isempty(int **A,int i,int j)
{
    
    if(A[i][j]==0)
        return true;
    else
        return false;
}

//This fuction checks if a particular no. can be put into (i,j) by cross-checking with
//the numbers already present in rows, columns and the small sub grid.
bool check(int **A,int x,int i,int j,int n)
{
    
    for(int a=0;a<n;a++)
    {
        if(A[i][a]==x)
            return false;
    }
    for(int a=0;a<n;a++)
    {
        if(A[a][j]==x)
            return false;
    }
    //to check for the small grid of sqrt(n)*sqrt(n)
    int p=i/sqrt(n),q=j/sqrt(n);
    for(int r=sqrt(n)*p;r<(sqrt(n)*p+sqrt(n));r++)
        for(int s=sqrt(n)*q;s<(sqrt(n)*q+sqrt(n));s++)
            if(A[r][s]==x)
                return false;
    return true;

}

//This function recursively calls itself to solve for each element in the sudoku
bool solve(int **A,int n,int i,int j)
{
    //End cases to return if the sudoku is solved
    if(i==n-1 && j==n)
        return true;
    //increementing the row number and reinitiating the column number
    if(j==n)
    {
        i++;
        j=0;
    }
    //If the cell is not empty we move forward
    if(!isempty(A,i,j))
        return solve(A,n,i,j+1);
    //If it is empty we check for each number from 1 to n
    for(int x=1;x<=n;x++)
    {
        if(check(A,x,i,j,n))
        {
           
            A[i][j]=x;
            //If we can put that number without conflict we move forward
            if(solve(A,n,i,j+1))
                return true;
        }
        //If at any point of time we feel that no number could be put in the cell we backtrack to
        //previous cell and check further for other numbers .
        A[i][j]=0;
    }
    //If the number list exhaust sadly we cant solve that sudoku (unsolvable) and return false
    return false;
}
int main()
{
    int n;
    cout<<"Enter the dimention of sudoku: ";
    cin>>n;
    int sudoku[n][n];
    //making an array of pointers to pass to the functions
    int *A[n];
    for(int i=0;i<n;i++)
        A[i]=sudoku[i];

    cout<<"Enter the initial board (put 0 in place of empty cells)"<<endl;
    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>sudoku[i][j]; 

    //If sudoku is solvable we print the final result       
    if(solve(A,n,0,0))
    {
        cout<<"Yippe sudoku solved"<<endl;
        for (int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cout<<sudoku[i][j]<<" ";
            cout<<endl;
        }
    }
    else
        cout<<"Sudoku is Unsolvable"<<endl;
    
}