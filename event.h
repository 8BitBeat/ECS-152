//
//  event.h
//  
//
//  Created by Donna Chow + Chris Chan on 4/28/14.
//
//

#ifndef ____event__
#define ____event__

#include <iostream>


/*So what this header and class will do is handle anything that's considered an event and will handle the GEL...
 
 GEL: Doubly linked list; same implentation as a single linked list except now each node knows its previous and its next.
 Functions for GEL: insert() --> inserting each event in accordance to its TIME
 -->departure events can be placed in between arrival events depending on its time
 --------------------------------------------------------------------------------------
 How events are placed into GEL by generating one arrival event:
 1. Find time via equation
 2. Create new packet and determine total transmission time from equation
 3. Make packet into an arrival object and place into the linked list -->insert()
 TWO Options for departure events:
 1. Length in queue = 0  -->get transmission time of 'newest' arrival packet we just made; set time = current time + service time
 -->place departure into GEL in accordance to time
 2. Length in queue != 0 -->Put arrival packet into the queue...something else i didn't feel like reading the rest of the stuff
 so i'll do that tomorrow (READING DEPARTURE EVENT STUFF *___*)
 
 --------------------------------------------------------------------------------------*/
class Event_Node
{
    
    //!!!!!!!!this is the data inside each node!!!!!!!!!!!!!
  
    //  double time; //when the event occurs, we're going to use this so it's easier compare times in GEL when placing in new event (packet.time)
public:
    // doubly linked list knows previous and next event within the GEL
    Event_Node *next_event;
    Event_Node *previous_event;

    double time;
    bool type;
     //packet event_packet;    //packet object that is technically the 'event' s.t. it'll contain the time and type
    Event_Node(){}; //intializer for the class event_node
    
    friend class Event; //Event class (GEL) will now be able to have the attributes that event_node has
    
}; //GEL event nodes()

class Event
{
private:
    Event_Node* head; //Head node
    
    public:
 
    Event()
    {   //constructor
        head = NULL;
    };
    ~Event(){};//deconstructor
    
    Event& inserting(double time, bool type);
    //Event& operator +=(const packet &packet_event_copying); //this is how we're going to place event into GEL

    Event_Node& head_return(); //returns the head
    int checking_for_head_null();
    Event& deleting();
    
    int printing();
};

#endif /* defined(____event__) */
