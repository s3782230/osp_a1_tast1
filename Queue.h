#ifndef QUEUE
#define QUEUE

#include <vector> 
#include <iterator>


#include "./Process.h"

class Queue {

    private:
        //std::shared_ptr<std::vector<Process*>> ready_queue = std::make_shared<std::vector<Process*>>();

        //std::vector<Process*>* completed_processes = new std::vector<Process*>;

        std::vector<Process*>* ready_queue;
        std::vector<Process*>* completed_processes;

        std::vector<Process*>::iterator it;
    public:
        Queue();
        ~Queue();

        bool initialise_processes(std::string processes_directory);

        bool add_to_list(Process* process, bool add_to_end);
        Process* search_in_list(int process_id);
        bool delete_from_list(int process_id);
        Process* pop_process(int process_id);
        bool is_empty();
        int get_num_processes();

        int get_num_finished_processes();
        

        /*
        *Pops the top process of the ready queue and returns ir
        */
        Process* pop_top_process();

        Process* get_top_process();

        /*
        returns true if process is completed and removed
        */
        bool decrement_busrt_time_of_running_process();
        Process* get_process_at_index(int index);

        void move_process_to_back_of_queue(int process_id);

        std::vector<Process*>* get_completed_processes();

        void print_waiting_time_and_turnaround_time();

        void print_list();

};

#endif //QUEUE