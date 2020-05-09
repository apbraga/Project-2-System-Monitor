#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
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
    std::vector<float> values = LinuxParser::CpuUtilization(Pid());
    if(values.size() == 5){
        long system_uptime_ = LinuxParser::UpTime();
        float time_1 = values[kUtime_] + values[kStime_] + values[kCutime_] + values[kCstime_];
        float time_2 = system_uptime_ - values[4];
        cpu_utilization_ = time_1/time_2;
    }
    else{
        cpu_utilization_ = 0;
    }
    // set ram utilization for a process
    try{
        long temp = floorf(std::stof(LinuxParser::Ram(Pid()))/float(1024));
        ram_ = std::to_string(temp);
    } catch(const std::invalid_argument& arg){
        ram_ = "0";
    }
    //set command line 
    command_ = LinuxParser::Command(pid);
    //set up time   
    uptime_ = LinuxParser::UpTime(pid);
}

//Return this process's ID
int Process::Pid() const { return pid_; }

//Return this process's CPU utilization
float Process::CpuUtilization() const { return cpu_utilization_; }

//Return the command that generated this process
string Process::Command() const { return command_; }

//Return this process's memory utilization
string Process::Ram() const { return ram_; }

//Return the user (name) that generated this process
string Process::User() const { return user_; }

//Return the age of this process (in seconds)
long int Process::UpTime() const { return uptime_; }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    return ( a.CpuUtilization() < this->CpuUtilization()) ; }

