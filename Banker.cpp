#include <iostream>
#include <vector>
#include <fstream>


//Function to take txt input and convert it into a 2d vector (Assumes format "1 2 3\n4 5 6\n...") 
std::vector<std::vector<int>> convert(std::ifstream& readinput) {
	std::vector<std::vector<int>> processes;						
	std::vector<int> buffer;													//Accepts input to make a vector to be inserted into processes
	char charinput;																//Holds char input from file input

	if (readinput.is_open()) {													//Ensure file is open
		do {																	//Read till end of file
			readinput.get(charinput);											//Get next character
			if (charinput != ' ' && charinput != '\n' && charinput != '\r') {	//Ignore spaces
				if (charinput == ';') {											//Iterate vector to next row to indicate next 'process' when a newline is found
					if (!buffer.empty()) { processes.push_back(buffer); }		//Bugfix to prevent empty vectors being inserted
					buffer.clear();												//Wipe buffer to prepare for next row
				} else {
					buffer.push_back(int(charinput) - '0');
				}
			}
		} while (!readinput.eof());												//Loop till end of file
	} else {
		std::cout << "Error reading file.";										//Exit if file fails to open
		exit(0);
	}
	readinput.close();															//Housekeeping
	return processes;
}
//Function to take txt input and convert it into a vector (Assumes format "1 2 3\n")
std::vector<int> convertoneline(std::ifstream& readinput) {					
	std::vector<int> buffer;																		//Accepts input to make a vector to be inserted into processes
	char charinput;																					//Holds char input from file input

	if (readinput.is_open()) {																		//Ensure file is open
		do {																						//Read till end of file
			readinput.get(charinput);																//Get next character
			if (charinput != ' ' && charinput != ';' && charinput != '\n'&& charinput != '\r') {	//Ignore space & newlines
					buffer.push_back(int(charinput) - '0');
			}
		} while (!readinput.eof());																	//Loop till end of file
	} else {
		std::cout << "Error reading file.";															//Exit if file fails to open
		exit(0);
	}
	readinput.close();																				//Housekeeping
	return buffer;
}


int main() {
	//Declaration
	std::vector<std::vector<int>> max, allocation;		//Keeps track of a processes max allocation and currently allocated 
	std::vector<int> resources, order;					//Keeps track of available resources
	std::vector<bool> paidback;							//Denotes if a process has "paid back" it's resource loan

	//Get input
	std::ifstream maxinput("max.txt");
	std::ifstream allocated("allocation.txt");
	std::ifstream availableresources("resources.txt");

	//Convert from txt into a 2d vector
	max = convert(maxinput);
	allocation = convert(allocated);

	//Convert from txt to vector
	resources = convertoneline(availableresources);

	//Ready & check inputs
	int processcount = max.size();
	int numberofresources = resources.size();

	//Verify allocation is correct
	for (auto i : allocation) {
		if (i.size() != resources.size()) {
			std::cout << "Mismatched inputs! (allocation)";
			exit(0);
		}
	}
	//Verify max is correct
	for (auto i : max) {
		if (i.size() != resources.size()) {
			std::cout << "Mismatched inputs! (max)";
			exit(0);
		}
	}
	//Initialize flags denoting if a process has "paid back" their loan
	for (auto i : max) {
		paidback.push_back(false);
	}

	//Fixed size pointer to array just to avoid having to initialize a vector that doesn't really need it.
	int* maxneeded = new int[numberofresources]; //Keeps track of what else the loanee could possibly need.

	//Banker's Algorithm
	for (int i = 0; i < processcount; i++) {
		bool safe = true;

		if (paidback[i] != true) {										//Skip if resource has been paid back
			for (int g = 0; g < numberofresources; g++) {
				maxneeded[g] = max[i][g] - allocation[i][g];			//Calculate if enough can be allocated should it need max
				if ((resources[g] - maxneeded[g]) < 0) safe = false;	//Mark that process can't currently be repaid and skipped for now
				if (safe && g == numberofresources - 1) {				//If it can be serviced, then add it to the safe sequence
					for (int h = 0; h < numberofresources; h++) {
						resources[h] += allocation[i][h];				//Merge the 'loan'
					}
					order.push_back(i);									//Push number to final order
					paidback[i] = true;									//Prevent same one from running again
					i = -1;												//Reset back to beginning, this time skipping returned loans
				}
			}
		}
	}

	//Assumes that if every process isn't accounted for the algorithm failed to find a safe sequence
	if (order.size() < processcount) {										
		std::cout << "Not safe!";
	} else {
		std::cout << "Safe order : ";
		for (auto i : order) {
			std::cout << "P:" << i << " ";
		}
	}
	std::cout << '\n';  //Play nice with command line interfaces

	delete[] maxneeded; //Cleanup
}

/* debug print 2d vector
	for (std::vector<int> i : allocation) {
		for (int g : i) {
			std::cout << g << " ";
		}
	}
*/