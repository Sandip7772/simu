#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Event types
#define ARRIVAL 1
#define DEPARTURE 2

typedef struct Event {
    int type;
    double time;
    struct Event* next;
} Event;

typedef struct QueueSystem {
    int server_busy;
    double arrival_rate;
    double service_rate;
    double simulation_time;
    Event* events;
} QueueSystem;

Event* create_event(int type, double time) {
    Event* event = (Event*)malloc(sizeof(Event));
    event->type = type;
    event->time = time;
    event->next = NULL;
    return event;
}

void insert_event(Event** event_list, Event* new_event) {
    if (*event_list == NULL || new_event->time < (*event_list)->time) {
        new_event->next = *event_list;
        *event_list = new_event;
    } else {
        Event* current = *event_list;
        while (current->next != NULL && current->next->time <= new_event->time) {
            current = current->next;
        }
        new_event->next = current->next;
        current->next = new_event;
    }
}

void handle_arrival(QueueSystem* system, double current_time) {
    printf("%.2f: Arrival. ", current_time);
    insert_event(&system->events, create_event(ARRIVAL, current_time + (-1 / system->arrival_rate) * log(rand() / (RAND_MAX + 1.0))));
    if (!system->server_busy) {
        printf("Server is idle. Departure scheduled.\n");
        insert_event(&system->events, create_event(DEPARTURE, current_time + (-1 / system->service_rate) * log(rand() / (RAND_MAX + 1.0))));
        system->server_busy = 1;
    } else {
        printf("Server is busy.\n");
    }
}

void handle_departure(QueueSystem* system, double current_time) {
    printf("%.2f: Departure. ", current_time);
    if (system->events != NULL && system->events->type == ARRIVAL) {
        Event* next_arrival = system->events;
        system->events = system->events->next;
        free(next_arrival);
        printf("Server is busy. Next departure scheduled.\n");
        insert_event(&system->events, create_event(DEPARTURE, current_time + (-1 / system->service_rate) * log(rand() / (RAND_MAX + 1.0))));
    } else {
        printf("Server is now idle.\n");
        system->server_busy = 0;
    }
}

void run_simulation(QueueSystem* system) {
    srand(time(NULL));

    double current_time = 0.0;
    insert_event(&system->events, create_event(ARRIVAL, current_time + (-1 / system->arrival_rate) * log(rand() / (RAND_MAX + 1.0))));

    while (current_time < system->simulation_time) {
        Event* current_event = system->events;
        system->events = current_event->next;

        current_time = current_event->time;

        switch (current_event->type) {
            case ARRIVAL:
                handle_arrival(system, current_time);
                break;
            case DEPARTURE:
                handle_departure(system, current_time);
                break;
        }

        free(current_event);
    }
}

int main() {
    QueueSystem system;
    system.server_busy = 0;
    system.arrival_rate = 2.0;
    system.service_rate = 3.0;
    system.simulation_time = 10.0;
    system.events = NULL;

    run_simulation(&system);

    return 0;
}

