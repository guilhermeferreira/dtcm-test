#include <assert.h>

#include "statemachine.h"

int main()
{
    STATE_T initial_state;
    STATE_T next_state;

    update_state = update_state_table;

    /* 1 - test LINK DOWN state for each of the 5 events */
    initial_state = State_LinkDown;
    next_state = update_state( initial_state, Event_InterfaceNotOK );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_InterfaceOK );
    assert( next_state == State_StartSending );
    next_state = update_state( initial_state, Event_PacketReceived );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_PacketNotReceived );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_NoAnswer );
    assert( next_state == State_LinkDown );

    /* 2 - test START SENDING state for each of the 5 events */
    initial_state = State_StartSending;
    next_state = update_state( initial_state, Event_InterfaceNotOK );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_InterfaceOK );
    assert( next_state == State_Invalid );
    next_state = update_state( initial_state, Event_PacketReceived );
    assert( next_state == State_StartReceived );
    next_state = update_state( initial_state, Event_PacketNotReceived );
    assert( next_state == State_StartSending );
    next_state = update_state( initial_state, Event_NoAnswer );
    assert( next_state == State_StartSending );

    /* 3 - test START RECEIVED state for each of the 5 events */
    initial_state = State_StartReceived;
    next_state = update_state( initial_state, Event_InterfaceNotOK );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_InterfaceOK );
    assert( next_state == State_Invalid );
    next_state = update_state( initial_state, Event_PacketReceived );
    assert( next_state == State_LinkOK );
    next_state = update_state( initial_state, Event_PacketNotReceived );
    assert( next_state == State_StartReceived );
    next_state = update_state( initial_state, Event_NoAnswer );
    assert( next_state == State_StartSending );

    /* 4 - test LINK OK state for each of the 5 events */
    initial_state = State_LinkOK;
    next_state = update_state( initial_state, Event_InterfaceNotOK );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_InterfaceOK );
    assert( next_state == State_Invalid );
    next_state = update_state( initial_state, Event_PacketReceived );
    assert( next_state == State_LinkOK );
    next_state = update_state( initial_state, Event_PacketNotReceived );
    assert( next_state == State_StartSending );
    next_state = update_state( initial_state, Event_NoAnswer );
    assert( next_state == State_StartSending );

    return 0;
}
