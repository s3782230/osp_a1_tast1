#include "Process.h"


Process::Process(int process_id, int burst_time, int arrival_time) {
    this->process_id = process_id;
    this->burst_time = burst_time;
    this->original_burst_time = burst_time;
    this->arrival_time = arrival_time;

    this->rr_burst_time = burst_time;
    this->rr_waiting_time = waiting_time;

    this->waiting_time = 0;
    this->turnaround_time = 0;
    this->is_active = false;

}

//Constructor for priority based
Process::Process(int process_id, int burst_time, int arrival_time, int priority) {
    this->process_id = process_id;
    this->burst_time = burst_time;
    this->arrival_time = arrival_time;
    this->priority = priority;
}

Process::~Process() {

}

int Process::calculate_turnaround_time() {
    return original_burst_time + waiting_time;
}

double Process::calculate_rr_turnaround_time() {
    return original_burst_time + rr_waiting_time;
}

void Process::decrement_burst_time() {

    this->burst_time = burst_time - 1;
}

void Process::increment_waiting_time() {

    this->waiting_time = waiting_time + 1;
}

int Process::get_waiting_time() {
    return this->waiting_time;
}

int Process::get_process_id() {
    return this->process_id;
}

int Process::get_burst_time() {
    return this->burst_time;
}

int Process::get_arrival_time() {
    return this->arrival_time;
}

bool Process::get_is_active() {
    return this->is_active;
}

void Process::decrement_rr_burst_time(double value) {
    this->rr_burst_time = rr_burst_time - value;
}

void Process::increment_rr_waiting_time(double value) {
    this->rr_waiting_time = rr_waiting_time + value;
}

double Process::get_rr_burst_time() {
    return this->rr_burst_time;
}

double Process::get_rr_waiting_time() {
    return this->rr_waiting_time;
}

void Process::set_is_active(bool is_active) {
    this->is_active = is_active;
}