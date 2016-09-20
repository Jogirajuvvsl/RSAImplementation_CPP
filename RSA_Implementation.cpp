#include <iostream>
//we used string functions so we need to add string library
#include<string>
// stdlib has the random function so we added it
#include<stdlib.h>
//created prime function to verify if the random generated numbers are prime or not
int prime(int x);
using namespace std;
//inpowerexponenet is to find value of  a to the power of b using least multiplications
unsigned long inpowerexponenet(unsigned long int a,unsigned long int b);
//gcd function is to find the gcd of a and b using euclidean process
int gcd(int a,int b);
//Bearcatconversion is to convert string to bearcatformat
unsigned long Bearcatconversion(string  a);
//modular_exponent is to find the remainder of large numbers effectively
unsigned long modular_exponent(unsigned long int b,unsigned long int e,unsigned long int m);
//gcd_Extended is used to multiplicate inverse of number using extended euclidean gcd
unsigned long int gcd_Extended(unsigned long int a,unsigned long int b, int *x, int *y);
// multiplicate inverse to call extended gcd and find the inverse
unsigned long int multilplicate_Inverse(unsigned long int a,unsigned long int m);
//convert the decoded message to message format
string Bearcatconversionreverse(unsigned long int a,string b);
#include <math.h>
int main()
{
    //cypher is used to save cypher integer
    unsigned long int e,p,q,n,n1,m,m1,c,d,i=1,ct=0,p1=0,q1=0,k=0,cypher[100];
    string message;
    //me is used to store decrypted message after RSA
    char me[100];


    //below while loop is to get random P and Q primary keys
    //when ct=2 both prime numbers are obtained else loop is called once again.
     while (ct<2)
    {
        //if p1 is 0 then prime number is not yet found need to call random funciton once again
        if(p1==0)
        {
        p=rand() %50;

//calling prime function to verify if the number is prime or not
        if(prime(p)==1)
         {
            p1=1;ct=ct+1;
          }
        }
        //if p1 is 0 then prime number is not yet found need to call random funciton once again
        if(q1==0)
        {
          q=rand()%65;
          //calling prime function to verify if the number is prime or not
          if(prime(q)==1)
           q1=1;ct=ct+1;
        }
    }
    n=p*q;
    //n1 is totient product which is Q in RSA
    n1=(p-1)*(q-1);
    //Code to ask the user to input E value coprime to totient product (p-1)*(q-1)
    while (i)
    {
    //asking the user to enter the public key till th
    cout<<"Please..Enter the primary key which is coprime to  totient product"<<n1<<"\n";
    cin>>e;
    //to ignore the enter pressesd after giving primary key
    cin.ignore();
     //to check co prime condition
     if (gcd(n1,e)==1)
         i=0;
     else
     cout<<"Entered Primary Key is not coprime.Please enter once again";
    }
         //calling function to get multiplicate inverse of primary key modulo n1
         d=multilplicate_Inverse(e,n1);
         //Mess
        cout<<"Enter the message to be encoded in Uppercase.Message till nextline is read"<<"\n";
        getline(cin,message,'\n');
        //starting encrypt and decrypt character wise
       for(i=0;i<message.size();i++)
         {
        if (message[i]==' ')
        m=0;
        else
        m=message[i]-'A'+1;
//modular exponenetion procedure find the remainder effectively
  //encrytion procedure call
    cypher[i]=modular_exponent(m,e,n);
    //decryption procedure call
    k=modular_exponent(cypher[i],d,n);
    if (k==0)
    me[i]=' ';
    else
    me[i]=k%27+'A'-1;
    }
cout<<" P and Q and N is "<<p <<" " <<q<<" "<<n<<"\n";
cout<<"Message entered is"<<message<<"\n";
cout<<"Cypher test is"<<"\n";
for(k=0;k<i;k++)
cout<<cypher[k];
cout<<"\n";
cout<<" Message after Decryption  is"<<"\n";
for(k=0;k<i;k++)
cout<<me[k];
}
//to find the mod of big numbers at encryption and decryption
unsigned long modular_exponent(unsigned long int b,unsigned long int e,unsigned long int m)
{
    unsigned long int e1=0,c=1;

    while(e1<e)
    {   e1=e1+1;
        c=(b*c)%m;
    }
    return c;

}



//using the
unsigned long inpowerexponenet(unsigned long int a,unsigned long int b)
{
    if (b==0)
    {
            return 1;
    }
    else if(b==1)
    {
        return a;
    }
    //when b is even squaring the number and halfing the power
    else if(b%2==0)
    {
        return inpowerexponenet(a*a,b/2);
    }
    //when b is odd need
    else  return (a*inpowerexponenet(a*a,(b-1)/2));;

}

int prime(int x)
{
    int i;
    //checking only till squareroot of p not till p
    for(i=2;i<=sqrt(x); i++)
    {
        if(x%i==0)
        return 0;

    }

   return 1;
}
//using Euclidean procedure to find gcd of two numbers
int gcd(int a,int b)
{

    if (b==0)
        return a;
    else
        return gcd(b,a%b);
}
//converting message to Bearcat conversion
unsigned long Bearcatconversion(string  a)
{

    int i=0;
    unsigned long sum=0;
    for (i=0; i<a.size();i++)
    {
        if(a[i]==' ')
            sum=sum+0;

        else
        {

           sum=sum+((a[i]-'A'+1)*inpowerexponenet(27,a.size()-i-1));
        }

    }

    return sum;
}

//convert from bearcatconversion to message times
 string Bearcatconversionreverse (unsigned long int n,string a)
{
    int i=a.size();
    a[i]=n%27+'A';
    a[i+1]='/0';
    if (n/27>27)
    {a=Bearcatconversionreverse(n/27,a);
    return a;
    }
    else
    {
        a[i+1]=n/27;
        a[i+2]='\0';
    return a;
    }
}




//Procedure to call multiplcative inverse i.e d in RSA
unsigned long int multilplicate_Inverse(unsigned long int a,unsigned long int  m)
{
    int x, y,res=0;
    //calling extended euclidean gcd process to find multilplicate_Inverse
    int g = gcd_Extended(a, m, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist";
    else
    {
        // when x is neagtive
        if(x>0)
        {res=x;}
        //when x is negative need to do mod of M to get correct number;
        else
        {

            res=m+x;
            res=res%m;

        }


    }

    return res;
}
//Implementation of gcd_extended to fin
unsigned long int gcd_Extended( unsigned long int a, unsigned long int b, int *x, int *y)
{

    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    unsigned long int gcd = gcd_Extended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
 }
