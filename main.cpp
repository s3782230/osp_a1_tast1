#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>

#include "./Queue.h"
#include "./Scheduler.h"

std::vector<Process*>* initialise_processes(std::string file_dir);



int main(int argc, char *argv[]) {
    std::string file_dir = "./files/processes-3";
    bool fcfs = false;
    bool sjf = true;
    bool rr = false;
    bool print_to_console = false;

    std::string output_file_name = "fcfs.txt";
    // ./cpuscheduler {file directory} {schedule} {print to console y/n}
    // int number_of_desired_arguments = 4;
    // if(argc != number_of_desired_arguments) {
    //     std::cout << "There are an incorrect number of arguments." << std::endl;
    //     return EXIT_FAILURE;
    // } else {
    //     file_dir = argv[1];
    //     std::cout << argv[2] << std::endl;
    //     std::string algorithm = argv[2];

    //     if(algorithm == "fcfs") {
    //         std::cout << "hi" << std::endl;
    //     } else {
    //         std::cout << "yea na" << std::endl;
    //     }

    //     if(argv[2] == "fcfs") {
    //         fcfs = true;
    //         output_file_name = "fcfs.txt";
            
    //     } else if (argv[2] == "sjb") {
    //         sjf = true;
    //         output_file_name = "sjf.txt";
    //     } else if (argv[2] == "rr") {
    //         rr = true;
    //         output_file_name = "rr.txt";
    //     }

    //     if(argv[3] == "y") {
    //         print_to_console = true;
    //     }

    // }

    

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
    std::ofstream outfile (output_file_name);
    std::vector<Process*>* completed_processes = ready_queue->get_completed_processes();

    for(int index = 0; index < completed_processes->size(); index++) {
        outfile << "ProcessID: [" << completed_processes->at(index)->get_process_id() <<
                    "], Waiting Time [" << completed_processes->at(index)->get_waiting_time() << 
                    "], Turnaround Time: [" << completed_processes->at(index)->calculate_turnaround_time() << "]" << std::endl;
    }

    return EXIT_SUCCESS;
}


std::vector<Process*>* initialise_processes(std::string file_dir) {
    std::vector<Process*>* process_list = new std::vector<Process*>();
    
    std::ifstream processes;
    processes.open(file_dir, std::ios::in);

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
        process_list->push_back(process);

        vstrings.clear();        
    }

    return process_list;
}