#include <stdio.h>
#include <stdlib.h>

int main()
{
    int token;
    
   Begining: 
        scanf("%d", &token);
        
        if(token ==0 || token ==1) goto Begining;
        goto END;
    
    END:
        printf ("The program has ended");
        return 0;
}
