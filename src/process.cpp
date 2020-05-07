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

// Not Tested: Return this process's ID
int Process::Pid() { return std::stoi(pid_); }

// Not Tested: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_utilization_; }

// Not Tested: Return the command that generated this process
string Process::Command() { return command_; }

// Not Tested: Return this process's memory utilization
string Process::Ram() { return ram_; }

// Not Tested: Return the user (name) that generated this process
string Process::User() { return user_; }

// Not Tested: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

//Constructor
Process::Process(int pid){
    pid_ = LinuxParser::Uid(pid);
    user_ = LinuxParser::User(pid);
    cpu_utilization_ = LinuxParser::ActiveJiffies(pid);
    ram_ = LinuxParser::Ram(pid);
    uptime_ = LinuxParser::UpTime(pid);
    command_ = LinuxParser::Command(pid);
}