#include "server.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
server::server(int MAXBUFFER)
{
     queue = new packet[MAXBUFFER];
    length = 0;
}


double server::calcaTime(double rate)
{
    double u;
    double temp;
    u = drand48();
    
    temp = ((-1/rate)*log(1-u));
    return temp;
}

double server::calcdTime()
{
    double u;
    double temp;
    u = drand48();
    temp = ((-1)*log(1-u));
    return temp;
}

double server::remove_head_queue()
 {
     double using_this_for_next_departure = 0;
     int j = 1;
     for(int i = 0; i < length+1; i++)
     {
         queue[i].time = queue[j].time;
     }
     if(length != 0)
     {
         using_this_for_next_departure = queue[0].time;
     }
     return using_this_for_next_departure;
 }