# CS-Operating-Systems-HW2
4/23/24  
Homework assignment #2 for Operating Systems class. Deals with the banker algorithm.  

### Description
Code is a class assignment covering the banker algorithm. In this it takes a table of programs and their currently allocated resources, max possible resources it could need and finally the system's currently free resources. With this info the program then finds if there is a safe sequence (the order the processes are allocated their requested resoures to ensure the system/bank can satisy them all) and then prints it or if there is not a safe sequence (system can not fulfill all processes's requests).
### Enviroment
Developed and tested in C++ on CentOS Linux via ssh using VSCode.

### Building & Running
g++ Banker.cpp -o banker  
./banker

### File Input
Input is divided into 3 files for easier processing.
  - Allocation and max must be same dimensions
  - All must have the same number of types of resources
  - Only spaces, newlines and carriage returns are filtered
  - Each input must be ended with a semicolon

### File Explanation
Each file has a designated purpose
 - allocation.txt is for what is currently allocated by a process.
 - max.txt is for the max possible resources a program can need.
 - resources.txt is for what the system currently has free, expects only one line.
##### Sample input format
```
1 2 3;
4 5 6;
```

### Sample Output
```
$ ./banker
Safe order : P:1 P:3 P:0 P:2 P:4 
```

### Known Bugs
None that I'm aware of.
