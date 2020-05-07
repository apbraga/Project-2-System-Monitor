#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>

Processor::Processor(): prev_idle(0), prev_total(0){};

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> utilization_txt = LinuxParser::CpuUtilization();
    std::vector<long> all_utilization;

    for(std::string utilization: utilization_txt){
        try{
            all_utilization.push_back(std::stol(utilization));
        } catch(const std::invalid_argument& arg){
            all_utilization.push_back((long)0);
        }
            
    }

    float total_time = all_utilization[LinuxParser::kUser_] + 
                       all_utilization[LinuxParser::kNice_] + 
                       all_utilization[LinuxParser::kSystem_] +
                       all_utilization[LinuxParser::kIdle_] +
                       all_utilization[LinuxParser::kIOwait_] +
                       all_utilization[LinuxParser::kIRQ_] +
                       all_utilization[LinuxParser::kSoftIRQ_] +
                       all_utilization[LinuxParser::kSteal_];

    float idle_time = all_utilization[LinuxParser::kIdle_] +
                      all_utilization[LinuxParser::kIOwait_];

    float delta_idle = idle_time - prev_idle;
    float delta_total = total_time - prev_total;
    float delta_idle = idle_time - prev_idle;

    float usage = (delta_total-delta_idle)/delta_total;

    prev_total = total_time;
    prev_idle = idle_time;


    return usage; }