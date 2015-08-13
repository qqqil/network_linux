#include <stdio.h>
#include <string.h>

#include "net.h"
class Test{
public:
    Test(){
        log("test constructor");
    }
    ~Test(){
        log("test distory");
    }
    void showMsg(){
        log("haha");
    }
};
int main()
{
    log("hello world");
    Test t;
    t.showMsg();
    return 0;
}
