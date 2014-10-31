//
//  event.cpp
//  
//
//  Created by Donna Chow + Chris Chan on 4/28/14.
//
//
#include <iostream>
#include "event.h"
using namespace std;


Event& Event::inserting(double time, bool type)
{
    Event_Node *node_with_packet_data;
    Event_Node *nodePtr; //this is a pointer to each node in the linked list so we can compare the previous and next day
    Event_Node *previous_node = NULL; //will keep track of original node
    
    //creating an event node that will hold what we're copying
    node_with_packet_data = new Event_Node;
   // node_with_packet_data->event_packet = packet_event_copying;
    node_with_packet_data->time = time;
    node_with_packet_data->type = type;
    
    //creating the new list if there doesn't exist one
    if(head == NULL)
    {
        head = node_with_packet_data;
        node_with_packet_data->next_event = NULL;
        node_with_packet_data->previous_event = NULL;
        
    }
    else
    {
        nodePtr = head; //this will keep track of the head
        //while we're not at the end this while loop will keep going until it breaks off right when there's an event that's bigger than it

        while(nodePtr != NULL ) //((nodePtr->event_packet).time) < (packet_event_copying.time)))
        {
         
            if((nodePtr->time) <time)
            {
                previous_node = nodePtr;
                nodePtr = nodePtr->next_event;
            }
            else
            {
                break;
            }
        }
       
        if(previous_node == NULL && (nodePtr == head))
        {
            Event_Node *temp = NULL;
            temp = head;
            temp->time = head->time;
            temp->type = head->type;
            temp->next_event = head->next_event;
            
            head = node_with_packet_data;
            head->time = node_with_packet_data->time;
            head->type = node_with_packet_data->type;
            
            head->next_event = temp;
            
            
        }
        else
        {
            previous_node->next_event = node_with_packet_data;
            if(previous_node != head && nodePtr!= NULL)
            {
                nodePtr->previous_event = node_with_packet_data;
            }
            node_with_packet_data->previous_event = previous_node;
            node_with_packet_data->next_event = nodePtr;
        }
        
       
        
        
        
        
/*  Now that we're out of the loop this is the data we have:
    previousNode = event < event_we're_inserting
    nodePtr = event > event_we're inserting
    node_with_packet_data = event_we're_inserting
 */
        
          }

    return *this;
}

Event_Node& Event::head_return()
{
    return *head;
}

Event& Event::deleting()
{
    if((head->next_event) != NULL)
    {
        Event_Node* temp_ptr = NULL;
        //setting temp ptr first so we can change the attributes
        temp_ptr = (head->next_event);
        //doing this just incase we collect garbage values
        temp_ptr->next_event = (head->next_event)->next_event;
        temp_ptr->time = (head->next_event)->time;
        temp_ptr->type = (head->next_event)->type;
        //replacing head's values 'deleting head'
        head->time = temp_ptr->time;
        head->next_event = temp_ptr->next_event;
        head->time = temp_ptr->time;
        head->type = temp_ptr->type;
    }
    else
    {
        head = NULL;
    }
    
    return *this;
}

int Event::checking_for_head_null()
{
    if(head == NULL)
    {
        return 1;
    }
    return 0;
}

//private variables using pointers require you to dot while public you can just access using ->
int Event::printing()
{
    Event_Node *current_node;
    current_node = head;
     int i = 0;
    while(current_node!= NULL)

    //for(int i = 0; i < 3; ++i)
    {
        cout<< "Node"<<i<<":  ";
        cout<< (current_node->time) << " - ";
         cout<< (current_node->type) << "\n";
         current_node = current_node->next_event;
         i++;
     }

        return 0;
}

