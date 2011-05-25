/*
 * Logic-Statements approach to handle a state machine.
 */
#include "statemachine.h"

#include <assert.h>

static STATE_T process_interface_not_ok( STATE_T current_state )
{
    STATE_T next_state;

    next_state = State_Invalid;

    switch ( current_state ) {
        case State_LinkDown:
            next_state = State_LinkDown;
            break;
        case State_StartSending:
            next_state = State_LinkDown;
            break;
        case State_StartReceived:
            next_state = State_LinkDown;
            break;
        case State_LinkOK:
            next_state = State_LinkDown;
            break;
        default:
            assert( 0 );
            break;
    }

    return next_state;
}


static STATE_T process_interface_ok( STATE_T current_state )
{
    STATE_T next_state;

    next_state = State_Invalid;

    switch ( current_state ) {
        case State_LinkDown:
            next_state = State_StartSending;
            break;
        case State_StartSending:
            next_state = State_Invalid;
            break;
        case State_StartReceived:
            next_state = State_Invalid;
            break;
        case State_LinkOK:
            next_state = State_Invalid;
            break;
        default:
            assert( 0 );
            break;
    }

    return next_state;
}


static STATE_T process_packet_received( STATE_T current_state )
{
    STATE_T next_state;

    next_state = State_Invalid;

    switch ( current_state ) {
        case State_LinkDown:
            next_state = State_LinkDown;
            break;
        case State_StartSending:
            next_state = State_StartReceived;
            break;
        case State_StartReceived:
            next_state = State_LinkOK;
            break;
        case State_LinkOK:
            next_state = State_LinkOK;
            break;
        default:
            assert( 0 );
            break;
    }

    return next_state;
}


static STATE_T process_packet_not_received( STATE_T current_state )
{
    STATE_T next_state;

    next_state = State_Invalid;

    switch ( current_state ) {
        case State_LinkDown:
            next_state = State_LinkDown;
            break;
        case State_StartSending:
            next_state = State_StartSending;
            break;
        case State_StartReceived:
            next_state = State_StartReceived;
            break;
        case State_LinkOK:
            next_state = State_StartSending;
            break;
        default:
            assert( 0 );
            break;
    }

    return next_state;
}


static STATE_T process_no_answer( STATE_T current_state )
{
    STATE_T next_state;

    next_state = State_Invalid;

    switch ( current_state ) {
        case State_LinkDown:
            next_state = State_LinkDown;
            break;
        case State_StartSending:
            next_state = State_StartSending;
            break;
        case State_StartReceived:
            next_state = State_StartSending;
            break;
        case State_LinkOK:
            next_state = State_StartSending;
            break;
        default:
            assert( 0 );
            break;
    }

    return next_state;
}


STATE_T update_state_logic(
    STATE_T current_state,
    EVENT_T event
)
{
    STATE_T next_state;

    switch ( event ) {
        case Event_InterfaceNotOK:
            next_state = process_interface_not_ok( current_state );
            break;
        case Event_InterfaceOK:
            next_state = process_interface_ok( current_state );
            break;
        case Event_PacketReceived:
            next_state = process_packet_received( current_state );
            break;
        case Event_PacketNotReceived:
            next_state = process_packet_not_received( current_state );
            break;
        case Event_NoAnswer:
            next_state = process_no_answer( current_state );
            break;
        default:
            assert( 0 );
            break;
    }

    return next_state;
}
