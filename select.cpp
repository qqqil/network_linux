#include "select.h"
#include "logger.h"

Select::Select(){
    Logger::info("select create!");
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

}
void  Select::set(int fd,fd_set& _set){
    FD_SET(fd,&_set);
}

int Select::is_set(int fd,fd_set& _set){

    return FD_ISSET(fd,&_set);
}

void  Select::zero(fd_set& _set){
    FD_ZERO(&_set); 
}

void Select::clear(int fd,fd_set& _set){
    FD_CLR(fd,&_set);
}

fd_set& Select::get_rset(){
    return _rset;
}

fd_set& Select::get_wset(){
    return _wset;
}

fd_set& Select::get_exp_set(){
    return _expset;
}
void Select::set_rset(fd_set& rset){
    _rset = rset;
}

int Select::select(int nfds){
    return ::select(nfds,&_rset,&_wset,&_expset,&timeout);
}
