#ifndef SELECT_H
#define SELECT_H
#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

class Select{
    public:
        Select();
        void clear(int fd,fd_set& _set);
        int is_set(int fd,fd_set& _set);
        void  set(int fd,fd_set& _set);
        void zero(fd_set &_set);
        int select(int nfds);
        fd_set& get_rset();
        fd_set& get_wset();
        fd_set& get_exp_set();
        void set_rset(fd_set& rset);

    private:
        fd_set _rset;
        fd_set _wset;
        fd_set _expset;
        struct timeval timeout;

};

#endif /* SELECT_H*/
