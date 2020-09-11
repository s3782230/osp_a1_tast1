#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <cstdlib>


#include <iostream>

#include <fstream>
#include <sstream>

#include "./Queue.h"
#include "./Scheduler.h"

std::vector<Process*>* initialise_processes(std::string file_dir);

/*
    1. 0 - 10
    2. 11 - 20
    3. 21 - 50
    4. 51 - 100
    5. 101 - 200
    6. 201 - 500
    7. 501 - 1000
    8. 1001 - 1500
    9. 1501 - 2000
*/
double waiting_time_stats[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double turnaroung_time_stats[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int main(int argc, char *argv[]) {
    std::string file_dir = "./files/processes-3";
    bool fcfs = false;
    bool sjf = false;
    bool rr = false;

    std::string output_file_name = "fcfs.txt";
    // ./cpuscheduler {file directory} {schedule}
    int number_of_desired_arguments = 2;
    if(argc != number_of_desired_arguments) {
        std::cout << "There are an incorrect number of arguments." << std::endl;
        return EXIT_FAILURE;
    } else {

        std::string algorithm = argv[1];

        if(algorithm == "fcfs") {
            fcfs = true;
            output_file_name = "fcfs.txt";
            
        } else if (algorithm == "sjf") {
            sjf = true;
            output_file_name = "sjf.txt";
        } else if (algorithm == "rr") {
            rr = true;
            output_file_name = "rr.txt";
        } else {
            std::cout << "A valid algorithm was not selected." << std::endl;
            return EXIT_FAILURE;
        }
    }

    

    //Create list of all processes from given file, specified by the file directory string, 'file_dir'
    std::vector<Process*>* process_list = initialise_processes(file_dir);

    //Create a ready queue.
    Queue* ready_queue = new Queue();   

    //Create a Scheduler.
    Scheduler* scheduler = new Scheduler(process_list, ready_queue);

    if(fcfs) {
        //Run FCFS schedule
        scheduler->first_come_first_serve_scheduler();
    } else if(sjf) {
        //Run SJF schedule
        scheduler->smallest_job_first_scheduler();
    } else if(rr) {
        //Run round robin schedule
        scheduler->round_robin_scheduler();
    }
    

    //Print to file
    std::ofstream outfile ("output.txt");
    std::vector<Process*>* completed_processes = ready_queue->get_completed_processes();

    for(int index = 0; index < completed_processes->size(); index++) {

        if(rr) {
            outfile << "ProcessID: [" << completed_processes->at(index)->get_process_id() <<
                    "], Waiting Time [" << completed_processes->at(index)->get_rr_waiting_time() << 
                    "], Turnaround Time: [" << completed_processes->at(index)->calculate_rr_turnaround_time() << "]" << std::endl;              

        } else {
            outfile << "ProcessID: [" << completed_processes->at(index)->get_process_id() <<
                    "], Waiting Time [" << completed_processes->at(index)->get_waiting_time() << 
                    "], Turnaround Time: [" << completed_processes->at(index)->calculate_turnaround_time() << "]" << std::endl;
        }
    }
    return EXIT_SUCCESS;
}


std::vector<Process*>* initialise_processes(std::string file_dir) {
    std::vector<Process*>* process_list = new std::vector<Process*>();
    
    std::ifstream processes(file_dir);
    //processes.open(file_dir, std::ios::in);

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
       //int test = atoi(vstrings.at(0).c_str())
        Process* process = new Process(std::atoi(vstrings.at(0).c_str()), std::atoi(vstrings.at(1).c_str()), std::atoi(vstrings.at(2).c_str()));
        process_list->push_back(process);

        vstrings.clear();        
    }

    processes.close();

    return process_list;
}