#ifndef PROCESS
#define PROCESS

#include <iostream>

class Process {

    private:

        int process_id;
        int burst_time;
        int original_burst_time;
        int arrival_time;
        int priority;
        int waiting_time = 0;
        int turnaround_time = 0;

        bool is_active = false;

    public:
        /*
        * Constructor for non priority based schedulers
        */
        Process(int process_id, int burst_time, int arrival_time);

        /*
        * Constructor for priority based schedulers
        */
        Process(int process_id, int burst_time, int arrival_time, int priority);
        ~Process();

        int get_process_id();
        int get_burst_time();
        int get_arrival_time();
        int get_waiting_time();

        bool get_is_active();

        void set_is_active(bool is_active);

        int calculate_turnaround_time();
        void decrement_burst_time();
        void increment_waiting_time();


};

#endif //PROCESS