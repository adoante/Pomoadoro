#include <iostream>
#include <chrono>
#include <unistd.h>
#include <list>
#include <string.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <thread>

#include <unistd.h>

using namespace std::chrono;

int main (int argc, char *argv[]) {

	int n = 1;
	int i = 4;
	int p = 25;
	int s = 5;
	int l = 15;

	// add task to list
	if (strcmp(argv[1], "add") == 0) {
		std::ofstream myfile;
		myfile.open("tasks.txt", std::ios_base::app);
		myfile << argv[2] << std::endl;
		myfile.close();
	}

	//print task list
	if (strcmp(argv[1], "print") == 0) {
		std::ifstream infile("tasks.txt");
		std::string line;
		int index = 0;
		while (std::getline(infile, line)) {
			std::cout << "[" << index  << "]: " << line << std::endl;
			index++;
		}
	}

	//clear all task from list
	if (strcmp(argv[1], "clear") == 0) {
		std::ofstream myfile;
		myfile.open("tasks.txt");
		myfile.close();
		std::cout << "All tasks were removed." << std::endl;
	}

	//remove task from list
	if (strcmp(argv[1], "remove") == 0) {
		std::ifstream infile("tasks.txt");
		std::string line;

		std::vector<std::string> tasks;
		int index = atoi(argv[2]);

		while (std::getline(infile, line)) {
			tasks.push_back(line);
		}

		std::cout << "Removed task [" << index << "]: " << tasks[index] << std::endl;
		tasks[index] = "";

		std::ofstream myfile;
		myfile.open("tasks.txt");
		for (int i = 0; i < tasks.size(); i++) {
			if (tasks[i] != "") {
				myfile << tasks[i] << std::endl;
			}
		}
		myfile.close();
	}

	//print help page with command and flag
	if (strcmp(argv[1], "help") == 0) {
		std::cout << "add: takes a string input and appends the task list file." << std::endl;
		std::cout << "remove: takes the task index integer and removes the task from task list file." << std::endl;
		std::cout << "print: takes no input and prints all tasks with thier index." << std::endl;
		std::cout << "clear: takes no input and removes all tasks from task list file." << std::endl;
	}

	//start pomodoro or a specific task
	if (strcmp(argv[1], "start") == 0) {
		if (argc == 3) {
			int index = atoi(argv[2]);
		}
		else {
			auto now = std::chrono::system_clock::now();
			auto end = now + minutes(p);
			std::time_t t_c1 = std::chrono::system_clock::to_time_t(end);
			std::cout << "The system clock is end at " << std::ctime(&t_c1);
			while (true) {
				now = std::chrono::system_clock::now();
				std::time_t t_c2 = std::chrono::system_clock::to_time_t(now);
				if (t_c1 == t_c2) {
					break;
				}
			    std::cout << "The system clock is currently at " << std::ctime(&t_c2);
				std::this_thread::sleep_for(seconds(1));
				system("@cls||clear");
			}
			std::cout << "Pomodoro Finished! " << std::endl;
		}
	}

	return 0;
}

/**
 * 
 int id = 0;
	int n = 1;
	int i = 4;
	int p = 0;
	int s = 0;
	int l = 0;
	int opt;

  while ((opt = getopt(argc, argv, "n:p:s:l:i:")) != -1) {
	    switch (opt) {
			case ('n'):
				n = atoi(optarg);
				break;
			case ('p'):
				p = atoi(optarg);
				break;
			case ('s'):
				s = atoi(optarg);
				break;
			case ('l'):
				l = atoi(optarg);
				break;
			case ('i'):
				i = atoi(optarg);
				break;
		}
	}

	

	

	//start pomodoro or a specific task
	if (strcmp(argv[1], "start") == 0) {

	}

	//end pomodoro
	if (strcmp(argv[1], "end") == 0) {

	}
 */