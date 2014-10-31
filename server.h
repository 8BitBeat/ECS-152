
#ifndef SERVER_H
#define SERVER_H


#include <math.h>
#include <stdlib.h>


class server
{
private:
    
     public:
    int length;
    server(int MAXBUFFER);

    struct packet{
        double time;
    };
    
    packet* queue;
    double calcaTime(double rate); //calculates packet's Arrival time
    double calcdTime(); //calculates the amount of time it takes for a packet to be transmitted
    double remove_head_queue();
};

#endif // SERVER_H
