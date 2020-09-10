#include "./Queue.h"


Queue::Queue() {

}

Queue::~Queue() {

}

bool Queue::initialise_processes(std::string processes_directory) {
    std::ifstream processes;
    processes.open(processes_directory, std::ios::in);

    std::string line;

    while(std::getline(processes, line)) {
        
        //Split string by delimiter and place it in a vector
        std::stringstream ss(line);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);

        /*
        *WARNING!! VALUES ARE HARDCODED AT THE MOMENT. ONLY WORKS IF THERE ARE THREE COLUMNS. BE SURE TO CHANGE LATER!!!!!!!!
        */

        Process* process = new Process(std::stoi(vstrings.at(0)), std::stoi(vstrings.at(1)), std::stoi(vstrings.at(2)));
        this->add_to_list(process, true);

        vstrings.clear();        
    }

    return true;
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
    
    std::vector<Process*>* queue = this->ready_queue.get();

    //If add_to_end is true, add the process to the end of the list
    if(add_to_end) {
        queue->insert(queue->end(), process);
    } else { // If add_to_end is not true, add the process to the start of the list.
        queue->insert(queue->begin(), process);
    }
    
}

Process* Queue::search_in_list(int process_id) {
    Process* found_process = nullptr;
    
    for(it = this->ready_queue.get()->begin(); it != this->ready_queue.get()->end(); ++it) {

        if((*it)->get_process_id() == process_id) {
            found_process = (*it);
        }
    }

    return found_process;
}

bool Queue::delete_from_list(int process_id) {
    std::vector<Process*>* queue = this->ready_queue.get();

    bool deleted;

    for(int index = 0; index < queue->size(); index++) {
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
    std::vector<Process*>* queue = this->ready_queue.get();

    if(!is_empty()) {
        popped_process = queue->at(0);

        this->completed_processes->insert(completed_processes->end(), popped_process);

        queue->erase(queue->begin());
    }

    return popped_process;
}

Process* Queue::get_top_process() {
    return this->ready_queue->at(0);
}

Process* Queue::get_process_at_index(int index) {
    std::vector<Process*>* queue = this->ready_queue.get();
    Process* process = NULL;

    if(index < queue->size() && queue->at(index) != nullptr) {
        process = queue->at(index);
    }

    return process;
}

/*
    If there is a memory error, its probably this method
*/
void Queue::move_process_to_back_of_queue(int process_id) {
    Process* process = NULL;
    std::vector<Process*>* queue = this->ready_queue.get();

    for(int index = 0; index < queue->size(); index++) {
        if(queue->at(index)->get_process_id() == process_id) {
            process = queue->at(index);
            ready_queue->erase(ready_queue->begin() + index);
        }
    }

    queue->insert(queue->end(), process);
    
}

bool Queue::is_empty() {
    std::vector<Process*>* queue = this->ready_queue.get();
    bool empty = false;
    
    if(queue->size() <= 0 ) {
        empty = true;
    }

    return empty;
}

int Queue::get_num_processes() {
    return this->ready_queue.get()->size();
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
    for(it = this->ready_queue.get()->begin(); it != this->ready_queue.get()->end(); ++it) {
        std::cout << (*it)->get_process_id() << std::endl;
    }
}

int Queue::get_num_finished_processes() {
    return this->completed_processes->size();
}