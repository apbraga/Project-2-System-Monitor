#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

//Constructor
Process::Process(int pid){
    //set process id
    pid_ = pid;
    // set user name for the process
    user_ = LinuxParser::User(pid);
    //set Cpu Utilization for a process
    long uptime = UpTime();
    std::vector<float> values = LinuxParser::CpuUtilization(pid);
    if(values.size() ==5){
        cpu_utilization_ = (values[kUtime_] + values[kStime_] + values[kCutime_] + values[kCstime_]);
        cpu_utilization_ /= (uptime_- values[kStarttime_]);
    }
    else{
        cpu_utilization_ = 0;
    }
    // set ram utilization for a process
    try{
        ram_ = std::to_string(std::stol(LinuxParser::Ram(pid))/1024);
    } catch(const std::invalid_argument& arg){
        ram_ = "0";
    }
    //set up time   
    uptime_ = LinuxParser::UpTime(pid);
    //set command line 
    command_ = LinuxParser::Command(pid);
}

//Return this process's ID
int Process::Pid() { return pid_; }

//Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_utilization_; }

//Return the command that generated this process
string Process::Command() { return command_; }

//Return this process's memory utilization
string Process::Ram() { return ram_; }

//Return the user (name) that generated this process
string Process::User() { return user_; }

//Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

//NOT USED
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

