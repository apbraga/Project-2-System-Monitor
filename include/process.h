#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);//constructor
  int Pid() const;                               // TODO: See src/process.cpp
  std::string User() const;                      // TODO: See src/process.cpp
  std::string Command() const;                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram() const;                       // TODO: See src/process.cpp
  long int UpTime()  const;                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp


  // TODO: Declare any necessary private members
 private:
 int pid_;
 std::string user_;
 float cpu_utilization_;
 std::string ram_;
 long uptime_;
 std::string command_;
 enum ProcessStates {
    kUtime_ = 0,
    kStime_ = 1,
    kCutime_ = 2,
    kCstime_ = 3,
    kStarttime_ = 4
 };

};

#endif