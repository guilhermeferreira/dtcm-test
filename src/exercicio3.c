#include <assert.h>

typedef enum State {
    State_Invalid = 0,
    State_LinkDown = 1,
    State_StartSending = 2,
    State_StartReceived = 3,
    State_LinkOK = 4
} STATE_T ;

typedef enum Event {
    Event_Invalid,
    Event_InterfaceNotOK,
    Event_InterfaceOK,
    Event_PacketReceived,
    Event_PacketNotReceived,
    Event_NoAnswer
} EVENT_T;


STATE_T process_interface_not_ok( STATE_T current_state )
{
    STATE_T next_state;

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


STATE_T process_interface_ok( STATE_T current_state )
{
    STATE_T next_state;

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


STATE_T process_packet_received( STATE_T current_state )
{
    STATE_T next_state;

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


STATE_T process_packet_not_received( STATE_T current_state )
{
    STATE_T next_state;

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


STATE_T process_no_answer( STATE_T current_state )
{
    STATE_T next_state;

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


STATE_T update_state(
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


int main()
{
    STATE_T initial_state;
    STATE_T next_state;

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
