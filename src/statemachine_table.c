/*
 * Table-Driven approach to handle a state machine.
 */
#include "statemachine.h"

static STATE_T state_machine[ State_Count ][ Event_Count ] =
{
    /*                    Interface nok | Interface OK | Packet received | Packet not received | No answer */
    /* Invalid        */ { State_Invalid, State_Invalid, State_Invalid, State_Invalid, State_Invalid },
    /* Link down      */ { State_LinkDown, State_StartSending, State_LinkDown, State_LinkDown, State_LinkDown },
    /* Start sending  */ { State_LinkDown, State_Invalid, State_StartReceived, State_StartSending, State_StartSending },
    /* Start received */ { State_LinkDown, State_Invalid, State_LinkOK, State_StartReceived, State_StartSending },
    /* Link OK        */ { State_LinkDown, State_Invalid, State_LinkOK, State_StartSending, State_StartSending }
};

STATE_T update_state_table(
    STATE_T current_state,
    EVENT_T event
)
{
    STATE_T next_state;

    next_state = state_machine[ current_state ][ event ];

    return next_state;
}
