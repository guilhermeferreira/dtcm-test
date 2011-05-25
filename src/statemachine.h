#ifndef STATEMACHINE_H
#define STATEMACHINE_H

typedef enum State {
    State_Invalid,
    State_LinkDown,
    State_StartSending,
    State_StartReceived,
    State_LinkOK,
    State_Count = 5
} STATE_T ;

typedef enum Event {
    Event_InterfaceNotOK,
    Event_InterfaceOK,
    Event_PacketReceived,
    Event_PacketNotReceived,
    Event_NoAnswer,
    Event_Count = 5
} EVENT_T;

STATE_T (*update_state)(
    STATE_T current_state,
    EVENT_T event
);

STATE_T update_state_logic(
    STATE_T current_state,
    EVENT_T event
);

STATE_T update_state_table(
    STATE_T current_state,
    EVENT_T event
);

#endif /* STATEMACHINE_H */
