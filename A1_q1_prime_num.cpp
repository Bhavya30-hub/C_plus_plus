#include <iostream>
using namespace std;
int main() 
{
    int num;
    cout<<"Enter a positive integer: "; 
    cin>>num;
    int flag =1;
    if (num <= 1) //checking if -ve 
    { 
        cout<<"Wrong Input !"<<endl;
    } 
    for (int i = 2; i < num/2; i++) 
    { 
        if (num % i == 0) 
        {
            flag=0;
            break;
        }
    }
    if (flag==0)
    {
        cout<<num<<" is not a prime number."<<endl;
        cout<<"Factors of " <<num<<" are : ";
        for (int i = 1; i <= num; i++) // divisibility up to n
        { 
            if (num % i == 0) 
            {
                cout<<i<< " ";
            }
        }
        cout<<endl;
    }
    else if(flag==1)
    {
        cout<<num <<" is a prime number."<<endl;
        int next = num+1;
        while (true) 
        {
            flag =1;
            for (int i = 2; i < next; i++) 
            { 
                if (next % i == 0) 
                {
                    flag= 0; //not prime
                    break; 
                }
            }
            if (flag==1){
                cout<<"The next prime number greater than "<<num<<" is "<<next<<endl;
                break;
            }
            else{
                next++;
            }
        }
    }
    else
    {
        cout<<"ERROR"<<endl;
    }
    return 0;
}