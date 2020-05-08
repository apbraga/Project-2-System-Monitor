#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

//An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

//An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

//Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float memtotal = 0;
  float memfree = 0;
  std::string line, key, value;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::remove(line.begin(),line.end(),' ');
      std::replace(line.begin(),line.end(),':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "MemTotal"){
          memtotal = std::stof(value);
        }else if(key=="MemFree"){
          memfree = std::stof(value);
          break;
        }
      }
    }
  }
  return ((memtotal-memfree)/memtotal);
}

// Read and return the system uptime
long LinuxParser::UpTime() { 
  string line, time;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      while(linestream >> time){
        try {
          return std::stol(time);
        } catch(const std::invalid_argument& arg){
          return 0;
        }
      }
    }
  }
  return 0; 
}

//Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

//Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

//Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

//Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

//Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  std::vector<string> values;
  std::string line, key, vuser, vnice, vsystem, vidle, viowait, virq, vsoftirq, vsteal, vguest, vguest_nice;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> vuser >> vnice >> vsystem >> vidle >>
             viowait >> virq >> vsoftirq >> vsteal >> vguest >> vguest_nice) {
        if(key == "cpu"){
          values.push_back(vuser);
          values.push_back(vnice);
          values.push_back(vsystem);
          values.push_back(vidle);
          values.push_back(viowait);
          values.push_back(virq);
          values.push_back(vsoftirq);
          values.push_back(vsteal);
          values.push_back(vguest);
          values.push_back(vguest_nice);
          return values;
        }
      }
    }
  }
  return {}; 
}

//Read and return CPU utilization for a specific process
vector<float> LinuxParser::CpuUtilization(int pid) { 
  std::vector<float> utilization{};
  string line, value;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      for(int i = 1; i <= kStarttime_; i++){
        linestream >> value;
        if (i == kUtime_ || i == kStime_ || i == kCutime_ || i == kCstime_ || i == kStarttime_){
          utilization.push_back(std::stof(value)/sysconf(_SC_CLK_TCK));
        }
      }
    }
  }
  return utilization;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::string line, key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "processes"){
          try {
            return std::stol(value);
          }catch(const std::invalid_argument& arg){
            return 0;
          }
        }
      }
    }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string line, key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "procs_running"){
          try {
            return std::stol(value);
          }catch(const std::invalid_argument& arg){
            return 0;
          }
        }
      }
    }
  }
  return 0; 
}

//Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  std::string value = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if(filestream.is_open()){
    std::getline(filestream, value);
    return value;
  }
  return value;
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  std::string line, key, value = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "VmSize"){
          return value;
        }
      }
    }
  }
  return value; 
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line, key, value = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::replace(line.begin(), line.end(),':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value){
        if(key == "Uid"){
          return value;
        }
      }
    }
  }  
  return value;
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  std::string id = Uid(pid);
  std::string line, dummy, key, value = "";
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> value >> dummy >> key){
        if(key=="uid"){
          return value;
        }
      }
    }
  }
  return value;
}

//Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  std::string line, value = "";
  long time = 0;
  std::ifstream filestream (kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      for(int i = 1; i <- kStarttime_; i++) {
        linestream >> value;
        if (i == kStarttime_){
          try{
            time = std::stol(value) / sysconf(_SC_CLK_TCK);
            return time;
          }catch(const std::invalid_argument& arg){
            return 0;
          }
        }
      }
    }
  }  
  return time;
}