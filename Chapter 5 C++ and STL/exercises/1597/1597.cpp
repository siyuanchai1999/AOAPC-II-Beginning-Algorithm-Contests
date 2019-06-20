#include <iostream>
#include <algorithm>

using namespace std;

int main(){
   long T, N;
   cin >> T;
   long i = 0;
   
   while(i++ < T){
       long upper = 0 , lower = 0,lowerTracker = 0, distance = 0, rem = 0;
       long tenExp = 1; 
       cin >> N;
       long temp = N;
       while(temp > 0){
           long digit = temp % 10;
           rem = rem + tenExp * digit;
           if(digit%2 == 1){
               upper = tenExp *(digit + 1);
               if(digit == 9){
                   upper = upper *2;
               }
               lower = lowerTracker +  tenExp *(digit - 1);
            //    cout << "upper " << upper << " lower " << lower << endl;
               distance = min(upper - rem, rem - lower);
           }
           lowerTracker += tenExp * 8;
           tenExp *= 10;
           temp = temp /10;
       }
       cout << "Case #" << i << ": " << distance << endl;
    //    distance = 0;
   }
}