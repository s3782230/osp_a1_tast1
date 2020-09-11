#include "./Scheduler.h"

Scheduler::Scheduler(std::vector<Process*>* process_list, Queue* ready_queue) {
    this->ready_queue = ready_queue;
    this->process_list = process_list;

    this->clock_ticks = 0;
        
    /* shortest job first */
    this->active_process_id = -1;

    /* Round Robin */
    this->first_process_pickedup = false;
    this->context_switch_time = 0.1;
    this->quantum = 2;
}

Scheduler::~Scheduler() {

}

void Scheduler::move_process_to_ready_queue(int clock_ticks) {
    for(int index = 0; index < process_list->size(); index++) {
        //If theres a process who's arrival time is equal to the number of clock ticks, it can now be moved to the ready queue.
        if(process_list->at(index)->get_arrival_time() == clock_ticks) {
            //Add the process to the ready queue
            ready_queue->add_to_list(process_list->at(index), true);

            /*
            std::cout << "At [" << clock_ticks << "] ticks, process [" << process_list->at(index)->get_process_id() << 
                "] was added, with a burst time of [" << process_list->at(index)->get_burst_time() << "]" << std::endl;
            */

            //Remove the process from the process list
            process_list->erase(process_list->begin());
        }
    }
}

void Scheduler::first_come_first_serve_scheduler() {
    //While the processes still exist within the ready queue or process list...
    while(ready_queue->get_num_processes() > 0 || process_list->size() > 0) {        
        //Loop through process list and add processes to ready queue if waiting time is 0, then remove from process_list
        move_process_to_ready_queue(clock_ticks);
        //Decrement burst time by 1 clock tick
        if(!ready_queue->is_empty()) {
            
            //Set process as active process
            this->ready_queue->get_process_at_index(0)->set_is_active(true);

            //Increment burst time of active process
            this->ready_queue->get_process_at_index(0)->decrement_burst_time();

            //Increment waiting time for waiting processes.
            this->increment_waiting_time_for_processes();

            //unset active process
            this->ready_queue->get_process_at_index(0)->set_is_active(false);

            //if recently decremented process now has a burst time of 0, then remove it
            if(this->ready_queue->get_process_at_index(0)->get_burst_time() == 0) {
                Process* popped_process = this->ready_queue->pop_top_process();
                //std::cout << "Process [" << popped_process->get_process_id() << "] has been completed at [" << clock_ticks << "] ticks." << std::endl;
            }

        }
        
        tick();
    }

    //ready_queue->print_waiting_time_and_turnaround_time();
}

void Scheduler::smallest_job_first_scheduler() {
    Process* shortest_job = NULL;
    //While the processes still exist within the ready queue or waiting queue...
    while(ready_queue->get_num_processes() > 0 || process_list->size() > 0) {        
        //Loop through process list and add processes to ready queue if waiting time is 0, then remove from process_list
        move_process_to_ready_queue(clock_ticks);      
        
        if(!ready_queue->is_empty()) {
            //Find the shortest job only if there is no active job currently
            if(shortest_job == NULL) {
                for(int index = 0; index < ready_queue->get_num_processes(); index++) {
                    Process* current_process = ready_queue->get_process_at_index(index);
                    if(shortest_job == NULL || current_process->get_burst_time() < shortest_job->get_burst_time()) {
                        shortest_job = current_process; 
                    }
                }
            }
            
            
            //Set active process
            shortest_job->set_is_active(true);

            //Decrement the burst time of shortest job
            shortest_job->decrement_burst_time(); 

            //Increment waiting time of non active processes
            this->increment_waiting_time_for_processes();

            //Unset active process
            shortest_job->set_is_active(false);


            //if recently decremented process now has a burst time of 0, then remove it
            if(shortest_job->get_burst_time() == 0) {
                this->ready_queue->delete_from_list(shortest_job->get_process_id());
                //Set the current job to null when it is completed.
                shortest_job = NULL;
            }
        }
        tick();
        
    }
}

void Scheduler::round_robin_scheduler() {

    double current_quantum = 0;
    Process* current;

    Process* process;
    bool added_context_switch = false;
    bool is_first_process = false;

    /////////
    int current_id = -1;


    while(ready_queue->get_num_processes() > 0 || process_list->size() > 0) { 

        this->move_process_to_ready_queue(clock_ticks);

        //Then...
        if(ready_queue->get_num_finished_processes() == 0 && current == NULL) {
            is_first_process = true;
        }


        /*
            Check if maximum quantum has been used on current process. if it has, move 
            it to the end of the ready queue
        */

       if(current_id != -1 && current_quantum == quantum) {
            ready_queue->move_process_to_back_of_queue(current_id);
            current_id = -1;
            current_quantum = 0;
       } 


       /* if there is no current proces running, schedule a new process to begin */
       if(current_id == -1 && !ready_queue->is_empty()) {
           /* the new process to begin running is the first in the queue */
           current_id = ready_queue->get_process_at_index(0)->get_process_id();
           //ready_queue->get_process_at_index(0)->set_is_active(true);
           /* remove the running process from the ready queue */


            //i dont actually remove processes from ready queue, so this line was causing errors
            // ready_queue->pop_top_process();


           /*
                apply context switch to waiting time of current process if:
                1. the current process was not the only process in the ready queue
                2. the current process was not the first process
           */
          if(!ready_queue->is_empty() && is_first_process == false) {
              //current->increment_rr_waiting_time(context_switch_time);
              ready_queue->get_process_at_index(0)->increment_rr_waiting_time(context_switch_time);
              added_context_switch = true;
          }
       }

       if(added_context_switch == true) {
           //current->decrement_rr_burst_time(1 - context_switch_time);
           ready_queue->get_process_at_index(0)->decrement_rr_burst_time(1 - context_switch_time);
       }
       else {
           //current->decrement_rr_burst_time(1);
           ready_queue->get_top_process()->decrement_rr_burst_time(1);
       }

       current_quantum = current_quantum + 1;
       /* if the burst time of the current proces is 0, that means 
        the process has finished running and can be removed 
        */
       if(ready_queue->get_process_at_index(0)->get_rr_burst_time() <= 0) {
            //ready_queue->move_process_to_back_of_queue(current->get_process_id());
            //ready_queue->move_process_to_back_of_queue(current_id);
            ready_queue->delete_from_list(current_id);
            current_id = -1;
       }

       /* Increase the waiting time of each process still in the ready queue by one clock tick */

       this->increment_waiting_time_for_processes(1, current_id);
        tick();
    }

    

}

void Scheduler::increment_waiting_time_for_processes() {

    for(int index = 0; index < this->ready_queue->get_num_processes(); index++) {

        //If the process is not the active process, increment its waiting time.
        if(ready_queue->get_process_at_index(index)->get_is_active() == false) {
            ready_queue->get_process_at_index(index)->increment_waiting_time();
        }
        
    }

}

void Scheduler::increment_waiting_time_for_processes(double value, int current_id) {

    for(int index = 0; index < this->ready_queue->get_num_processes(); index++) {
        //If the process is not the active process, increment its waiting time.

        if(ready_queue->get_process_at_index(index)->get_process_id() != current_id) {
            ready_queue->get_process_at_index(index)->increment_rr_waiting_time(value);
        }
    }

}

void Scheduler::tick() {
    clock_ticks++;
}