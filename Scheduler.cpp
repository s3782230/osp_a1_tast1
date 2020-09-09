#include "./Scheduler.h"

Scheduler::Scheduler(std::vector<Process*>* process_list, Queue* ready_queue) {
    this->ready_queue = ready_queue;
    this->process_list = process_list;
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
    //While the processes still exist within the ready queue or waiting queue...
    while(ready_queue->get_num_processes() > 0 || process_list->size() > 0) {        
        //Loop through process list and add processes to ready queue if waiting time is 0, then remove from process_list
        move_process_to_ready_queue(clock_ticks);      
        
        if(!ready_queue->is_empty()) {
            //Find the shortest job
            Process* shortest_job = NULL;

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

                //std::cout << "Process [" << shortest_job->get_process_id() << "] has been completed at [" << clock_ticks << "] ticks." << std::endl;
                //std::cout << "At [" << clock_ticks << "] ticks, process [" << shortest_job->get_process_id() << "] was completed" << std::endl;

                this->ready_queue->delete_from_list(shortest_job->get_process_id());
            }
        }
        tick();
        
    }
}

void Scheduler::round_robin_scheduler() {

    int current_quantum = this->quantum;

    while(ready_queue->get_num_processes() > 0 || process_list->size() > 0) { 
        //Loop through process list and add processes to ready queue if waiting time is 0, then remove from process_list
        move_process_to_ready_queue(clock_ticks);  

        Process* current_process = this->ready_queue->get_process_at_index(0);

        //If the current process is not active, switch in the process, set it as active and add context switch time to overhead
        if(current_process->get_is_active() == false) {
            current_process->set_is_active(true);
        }
        
        //Increment burst time of active process
        current_process->decrement_burst_time();

        //Increment waiting time for waiting processes.
        this->increment_waiting_time_for_processes();

        //If the current process is completed, remove it from the ready queue and reset the current quantum back to default
        if(this->ready_queue->get_process_at_index(0)->get_burst_time() == 0) {
            this->ready_queue->delete_from_list(current_process->get_process_id());
            current_quantum = this->quantum;
        } 
        //Else if the current process is NOT completed, decrement the current quantum. if the current quantum equals 0, reset it back to default and move the 
        //current process to the end of the ready queue.
        else {
            current_quantum--;
            if(current_quantum == 0) {
                current_quantum = this->quantum;
                ready_queue->move_process_to_back_of_queue(current_process->get_process_id());
                current_process->set_is_active(false);
            }
        }

        
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

void Scheduler::tick() {
    clock_ticks++;
}