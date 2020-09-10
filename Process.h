#ifndef PROCESS
#define PROCESS

#include <iostream>

class Process {

    private:

        int process_id = 0;
        int burst_time = 0;
        int original_burst_time = 0;
        int arrival_time = 0;
        int priority = 0;
        int waiting_time = 0;
        int turnaround_time = 0;

        bool is_active = false;

        /* round robin */
        double rr_waiting_time = 0;
        double rr_burst_time = 0;

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

        double get_rr_waiting_time();
        double get_rr_burst_time();

        bool get_is_active();

        void set_is_active(bool is_active);

        int calculate_turnaround_time();

        void decrement_rr_burst_time(double value);
        void increment_rr_waiting_time(double value);

        void decrement_burst_time();
        void increment_waiting_time();


};

#endif //PROCESS