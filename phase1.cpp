
//
//  main.cpp
//
//
//  Created by Donna Chow + Chris Chan on 5/5/14.
//
//


#include "event.h"
#include "server.h"
#include <math.h>
#include <stdlib.h>

using namespace std;

int main()
{
    
    Event GEL; //GEL List
    
    int packetAmount;
    
    double PiQ = 0; //average packets in queue
    double totalTime;
    
    double lambda;
    double arrival_time;
    double previous_time = 0;
    double departure_time;
    
    double idleTime=0;
    double idleStart=0;
    
    int MAXBUFFER;
    int packets_dropped = 0;
    cout << "# of packets: ";
    cin >> packetAmount;
    cout << "Lambda: ";
    cin >> lambda;
    cout << "MAXBUFFER: ";
    cin >> MAXBUFFER;
    /*  SET NUMBER OF PACKETS = 2
     SET NUMBER LAMBDA = 2
     SET NUMBER MAX BUFFER = 20      */
    //lambda = .2;
    //packetAmount = 1000;
    //MAXBUFFER = 1;
    ////////////////o
    
    server SSQ(MAXBUFFER);
    
    for(int i = 0; i < packetAmount; i++)
    {
        arrival_time = SSQ.calcaTime(lambda) + previous_time;
        GEL.inserting(arrival_time, 0);
        previous_time = arrival_time;
    }
    
    Event_Node testing_node;
    int i = 0;
    while( GEL.checking_for_head_null() != 1)
    //for(int i = 0; i<4; i++)
    {
        //cout<<"----------------------"<<i<<"---------------------\n";

        //arrival
        testing_node = GEL.head_return();
        
        //cout<<"Current Head Node: \n"<<testing_node.time<<"\n"<<testing_node.type<<"\n--------------\n";
        if(testing_node.type == 0)
        {
            PiQ = PiQ + SSQ.length;
            //queue is empty
            if( SSQ.length == 0)
            {
                (SSQ.length)++;
                
                idleTime = idleTime + (testing_node.time - idleStart);
                
                (SSQ.queue[ (SSQ.length)-1 ]).time = testing_node.time;
                //cout<<"0000000000000    Queue is empty    0000000000000000\n";
                //cout<<"Queue-Arrival Inserted Time: "<<(SSQ.queue[ (SSQ.length)-1 ]).time <<"\n----\n";
                departure_time = testing_node.time + SSQ.calcdTime();
                GEL.inserting(departure_time, 1);
                //cout<<"GEL-Inserted Departure Time:"<<departure_time<<"\n----------------------\n";
            }
            else if( (SSQ.length >0) && ((SSQ.length) < MAXBUFFER))
            {
                //cout<<"111111111111   Queue is not empty      1111111111111111\n";
                (SSQ.length)++;
                (SSQ.queue[ (SSQ.length)-1 ]).time = testing_node.time;
                //cout<<"Queue-Arrival Inserted Time: "<<(SSQ.queue[ (SSQ.length)-1 ]).time <<"\n----\n";
                //cout<<"Current Queue Length: "<<SSQ.length<<"\n--------------------\n";
                //update mean queue length stuff
            }
            else
            {
                //drop that packet and move onto the next one
                ++packets_dropped;
                //cout<<"Packets Dropped: "<<packets_dropped<<"\n";
            
            }
            //cout<<"\n";
            //cout<<"Queue Items After Arrival Events Inserted\n";
            ////for(int i = 0; i < SSQ.length; i++)
            ////{
                
             //   //cout<<(SSQ.queue[i]).time<<",  ";
        //   // }
            
            ////cout<<"\nGEL in the Arrival Loop\n";
            //GEL.printing();
            
        }
        else
        {
            //departure
            if(SSQ.length > 0)
            {
                //removing the head of the queue and also putting in the next departure time
                
              //  //cout<<"Processing a Departure Event...\n\n";
                SSQ.length = SSQ.length - 1;
                
                if(SSQ.length == 0)
                    idleStart = testing_node.time; 
                
                departure_time = SSQ.remove_head_queue();
                //cout<<"Arrival Time of the Head in the Queue\n"<<departure_time<<"\n---------\n";
                //cout<<"Queue Length After Head Removal: "<<SSQ.length<<"\n";
                //cout<<"What's inside the Queue after we removed the head:\n"; //because we remove head if we process a departure , we're getting the 'next' head's departure now
                //for(int i = 0; i < SSQ.length; i++)
                //{
                //    cout<<(SSQ.queue[i]).time<<"\n";
                //}
                //cout<<"\n";
                if(departure_time != 0)
                {
                    //cout<<"INSIDE QUEUE INSIDE QUEUE INSIDE QUEUE INSIDE QUEUE INSIDE QUEUE \n";
                
                    departure_time = departure_time + SSQ.calcdTime();
                    //cout<<"Calculated Departure Time of First Event in the Queue"<<departure_time<<"\n";
                    GEL.inserting(departure_time, 1);
                    totalTime = departure_time;
                }
            }
            
        }
        //last thing on the queue get the total time
        GEL.deleting();
                //may not have anything inserted if there's nothing in the queue
        //cout<<"GEL List after Deleting Head\n--------\n";
       // GEL.printing();
        //        cout<<"---------------------------------------\n";
        i++;
        //seg faulting because when we do the GEL.head_return() it returns a null pointer
        }
    //cout<<"-------------This is the GEL at the end:------------\n";
    //GEL.printing();
    cout<<"PACKETS DROPPED: "<<packets_dropped<<"\n";
    cout<<"Average packets in queue: "<<(PiQ/totalTime)<< endl;
    cout<<"Utilization Ratio: "<<(totalTime - idleTime)/totalTime<<endl;

    return 0;
}


