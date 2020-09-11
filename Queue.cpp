#include "./Queue.h"


Queue::Queue() {
    this->ready_queue =  new std::vector<Process*>;
    this->completed_processes = new std::vector<Process*>;
}

Queue::~Queue() {

}

bool Queue::initialise_processes(std::string processes_directory) {

}

bool Queue::decrement_busrt_time_of_running_process() {
    bool process_removed = false;

    if(ready_queue->size() > 0) {
        this->ready_queue->at(0)->decrement_burst_time();
        //if recently decremented process now has a burst time of 0, then remove it
        if(this->ready_queue->at(0)->get_burst_time() == 0) {
            
            std::cout << "Process" << this->ready_queue->at(0)->get_process_id() << " has finished";
            this->ready_queue->erase(ready_queue->begin());
            process_removed = true;
        }

        return process_removed;
    }

    return process_removed;    
}

bool Queue::add_to_list(Process* process, bool add_to_end) {
    //If add_to_end is true, add the process to the end of the list
    if(add_to_end) {
        ready_queue->insert(ready_queue->end(), process);
    } else { // If add_to_end is not true, add the process to the start of the list.
        ready_queue->insert(ready_queue->begin(), process);
    }
    
}

Process* Queue::search_in_list(int process_id) {
    Process* found_process = NULL;
    
    // for(it = this->ready_queue.get()->begin(); it != this->ready_queue.get()->end(); ++it) {

    //     if((*it)->get_process_id() == process_id) {
    //         found_process = (*it);
    //     }
    // }

    return found_process;
}

bool Queue::delete_from_list(int process_id) {

    bool deleted;

    for(int index = 0; index < ready_queue->size(); index++) {
        if(ready_queue->at(index)->get_process_id() == process_id) {

            this->completed_processes->insert(completed_processes->end(), ready_queue->at(index));

            ready_queue->erase(ready_queue->begin() + index);
            deleted = true;
        }
    }
    return deleted;
}

Process* Queue::pop_top_process() {
    Process* popped_process = NULL;

    if(!is_empty()) {
        popped_process = ready_queue->at(0);

        this->completed_processes->insert(completed_processes->end(), popped_process);

        ready_queue->erase(ready_queue->begin());
    }

    return popped_process;
}

Process* Queue::get_top_process() {
    return this->ready_queue->at(0);
}

Process* Queue::get_process_at_index(int index) {
    Process* process = NULL;

    if(index < ready_queue->size() && ready_queue->at(index) != NULL) {
        process = ready_queue->at(index);
    }

    return process;
}

/*
    If there is a memory error, its probably this method
*/
void Queue::move_process_to_back_of_queue(int process_id) {
    Process* process = NULL;

    for(int index = 0; index < ready_queue->size(); index++) {
        if(ready_queue->at(index)->get_process_id() == process_id) {
            process = ready_queue->at(index);
            ready_queue->erase(ready_queue->begin() + index);
        }
    }

    ready_queue->insert(ready_queue->end(), process);
    
}

bool Queue::is_empty() {
    bool empty = false;
    
    if(ready_queue->size() <= 0 ) {
        empty = true;
    }

    return empty;
}

int Queue::get_num_processes() {
    return this->ready_queue->size();
}

void Queue::print_waiting_time_and_turnaround_time() {
    for(int index = 0; index < this->completed_processes->size(); index++) {
        std::cout << "ProcessID: [" << completed_processes->at(index)->get_process_id() <<
                    "], Waiting Time [" << completed_processes->at(index)->get_waiting_time() << 
                    "], Turnaround Time: [" << completed_processes->at(index)->calculate_turnaround_time() << "]" << std::endl;
    }
}

std::vector<Process*>* Queue::get_completed_processes() {
    return this->completed_processes;
}

void Queue::print_list() {
    // for(it = this->ready_queue.get()->begin(); it != this->ready_queue.get()->end(); ++it) {
    //     std::cout << (*it)->get_process_id() << std::endl;
    // }
}

int Queue::get_num_finished_processes() {
    return this->completed_processes->size();
}