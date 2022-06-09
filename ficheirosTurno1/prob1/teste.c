#include <stdio.h>
#include <string.h>


int main(){

    char str[]="OLA";

    char str2[]="AU";
    
    int a=str[0];

    int b=str2[0];

    if(b<a){
        printf("%d--%d\n",a,b);
    }


    return 0;
}