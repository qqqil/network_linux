#include <stdio.h>
#include <string.h>

int main()
{
    char buf[1024];
    memset(buf,0,sizeof(buf));
    printf("please input:\n");
    scanf("%s",buf);
    
    printf("%s\n",buf);

    return 0;
}
