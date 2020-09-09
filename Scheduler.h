#ifndef SCHEDULER
#define SCHEDULER

#include "./Queue.h"

class Scheduler {

    private:
        int clock_ticks = 0;

        std::vector<Process*>* process_list;

        Queue* ready_queue;
        
        /* Round Robin */
        double context_switch_time = 0.1;
        int quantum = 2;
        

        

    public:
        Scheduler(std::vector<Process*>* process_list, Queue* ready_queue);
        ~Scheduler();

        void first_come_first_serve_scheduler();

        void smallest_job_first_scheduler();

        void round_robin_scheduler();

        void move_process_to_ready_queue(int clock_ticks);

        void increment_waiting_time_for_processes();

        void tick();

};

#endif //SHEDULER