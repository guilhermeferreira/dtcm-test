#include <assert.h>
#include <stdio.h>

#include "statemachine.h"

static void execute_state_action( STATE_T state )
{
    switch ( state ) {
        case State_Invalid:
            printf( "Executing code of Invalid\n" );
            break;
        case State_LinkDown:
            printf( "Executing code of LinkDown\n" );
            break;
        case State_StartSending:
            printf( "Executing code of StartSending\n" );
            break;
        case State_StartReceived:
            printf( "Executing code of StartReceived\n" );
            break;
        case State_LinkOK:
            printf( "Executing code of LinkOK\n" );
            break;
        default:
            assert( 0 );
            break;
    }
}

int main()
{
    STATE_T initial_state;
    STATE_T next_state;

    update_state = update_state_table;

    /* 1 - test LINK DOWN state for each of the 5 events */
    initial_state = State_LinkDown;
    next_state = update_state( initial_state, Event_InterfaceNotOK );
    execute_state_action( next_state );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_InterfaceOK );
    execute_state_action( next_state );
    assert( next_state == State_StartSending );
    next_state = update_state( initial_state, Event_PacketReceived );
    execute_state_action( next_state );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_PacketNotReceived );
    execute_state_action( next_state );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_NoAnswer );
    execute_state_action( next_state );
    assert( next_state == State_LinkDown );

    /* 2 - test START SENDING state for each of the 5 events */
    initial_state = State_StartSending;
    next_state = update_state( initial_state, Event_InterfaceNotOK );
    execute_state_action( next_state );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_InterfaceOK );
    execute_state_action( next_state );
    assert( next_state == State_Invalid );
    next_state = update_state( initial_state, Event_PacketReceived );
    execute_state_action( next_state );
    assert( next_state == State_StartReceived );
    next_state = update_state( initial_state, Event_PacketNotReceived );
    execute_state_action( next_state );
    assert( next_state == State_StartSending );
    next_state = update_state( initial_state, Event_NoAnswer );
    execute_state_action( next_state );
    assert( next_state == State_StartSending );

    /* 3 - test START RECEIVED state for each of the 5 events */
    initial_state = State_StartReceived;
    next_state = update_state( initial_state, Event_InterfaceNotOK );
    execute_state_action( next_state );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_InterfaceOK );
    execute_state_action( next_state );
    assert( next_state == State_Invalid );
    next_state = update_state( initial_state, Event_PacketReceived );
    execute_state_action( next_state );
    assert( next_state == State_LinkOK );
    next_state = update_state( initial_state, Event_PacketNotReceived );
    execute_state_action( next_state );
    assert( next_state == State_StartReceived );
    next_state = update_state( initial_state, Event_NoAnswer );
    execute_state_action( next_state );
    assert( next_state == State_StartSending );

    /* 4 - test LINK OK state for each of the 5 events */
    initial_state = State_LinkOK;
    next_state = update_state( initial_state, Event_InterfaceNotOK );
    execute_state_action( next_state );
    assert( next_state == State_LinkDown );
    next_state = update_state( initial_state, Event_InterfaceOK );
    execute_state_action( next_state );
    assert( next_state == State_Invalid );
    next_state = update_state( initial_state, Event_PacketReceived );
    execute_state_action( next_state );
    assert( next_state == State_LinkOK );
    next_state = update_state( initial_state, Event_PacketNotReceived );
    execute_state_action( next_state );
    assert( next_state == State_StartSending );
    next_state = update_state( initial_state, Event_NoAnswer );
    execute_state_action( next_state );
    assert( next_state == State_StartSending );

    return 0;
}
