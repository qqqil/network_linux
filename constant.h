
#ifndef CONSTANT_H
#define CONSTANT_H
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <error.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>

#ifndef SERV_PORT
#define SERV_PORT 7000
#endif

#ifndef INADDR_ANY
#define INADDR_ANY "0.0.0.0"
#endif

#ifndef MAXLINE 
#define MAXLINE 100
#endif

#endif
