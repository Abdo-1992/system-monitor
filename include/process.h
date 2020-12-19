#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

    void Pid(int);                               // TODO: See src/process.cpp
    void User(std::string);                      // TODO: See src/process.cpp
    void Command(std::string);                   // TODO: See src/process.cpp
    void CpuUtilization(float);                  // TODO: See src/process.cpp
    void Ram(std::string);                       // TODO: See src/process.cpp
    void UpTime(long int);                       // TODO: See src/process.cpp
    void updateParameters(int pid);   

    std::string findCommandValue(int pid);
    long int findUpTimeValue(int pid);
    std::string findRamValue(int pid);
    float FindCpuUtilizationValue(int pid);
    std::string findUser(int pid);

  // TODO: Declare any necessary private members
 private:
    int PidValue ;
    std::string UserValue ;
    std::string CommandValue ;
    float CpuUtilizationValue ;
    std::string RamValue ;
    long int UpTimeValue ;

};

#endif