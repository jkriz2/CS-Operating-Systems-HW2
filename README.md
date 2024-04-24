# CS-Operating-Systems-HW2
4/23/24  
Homework assignment #2 for Operating Systems class. Deals with the banker algorithm.  

### Description
Code is a class assignment covering the banker algorithm. In this it takes a table of programs and their currently allocated resources, max possible resources it could need and finally the systems resources. With this info the program then finds if there is a safe sequence (the order the processes are allocated their requested resoures to ensure the system/bank can satisy them all) or if there is not a safe sequence (system can not fulfill all processes's requests).
### Enviroment
Developed and tested in C++ on CentOS Linux via ssh using VSCode.

### Building & Running
g++ Banker.cpp -o banker 
./banker

### Sample Output
```
$ ./banker
Safe order : P:1 P:3 P:0 P:2 P:4 
```
