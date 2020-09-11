#ifndef SCHEDULER
#define SCHEDULER

#include "./Queue.h"

class Scheduler {

    private:
        int clock_ticks;

        std::vector<Process*>* process_list;

        Queue* ready_queue;
        
        /* shortest job first */
        int active_process_id;

        /* Round Robin */
        bool first_process_pickedup;
        double context_switch_time;
        int quantum;
        

        

    public:
        Scheduler(std::vector<Process*>* process_list, Queue* ready_queue);
        ~Scheduler();

        void first_come_first_serve_scheduler();

        void smallest_job_first_scheduler();

        void round_robin_scheduler();

        void move_process_to_ready_queue(int clock_ticks);

        void increment_waiting_time_for_processes();

        void increment_waiting_time_for_processes(double value, int current_id);

        void tick();

};

#endif //SHEDULER