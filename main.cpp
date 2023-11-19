#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <windows.h>

void timer(int);
void remove(int);
void help();
void clear();
void print();
void add(std::string);
void load_config(int&, int&, int&, int&, int&);
void restore();

int main (int argc, char *argv[]) {

	int n = 0;	// number of pomodoros
	int i = 0;	// interval of long breaks
	int p = 0;	// length of pomodoro
	int s = 0;	// length of short break
	int l = 0;	// length of long break

	load_config(n, i, p, s, l);

	int opt;
	
	// allows user to set config
	while ((opt = getopt(argc, argv, "n:p:s:l:i:")) != -1) {
	    switch (opt) {
			case ('n'):
				n = atoi(optarg);
				std::cout << "Set number of pomodoros: " << n << std::endl;
				break;
			case ('p'):
				p = atoi(optarg);
				std::cout << "Set length of pomodoro: " << p << std::endl;
				break;
			case ('s'):
				s = atoi(optarg);
				std::cout << "Set length of short break: " << s << std::endl;
				break;
			case ('l'):
				l = atoi(optarg);
				std::cout << "Set length of long break: " << l << std::endl;
				break;
			case ('i'):
				i = atoi(optarg);
				std::cout << "Set interval of breaks: " << i << std::endl;
				break;
		}
	}

	// add task to list
	if (strcmp(argv[1], "add") == 0) {
		add(argv[2]);
	}

	//print task list
	if (strcmp(argv[1], "print") == 0) {
		print();
	}

	//clear all task from list
	if (strcmp(argv[1], "clear") == 0) {
		clear();
	}

	//remove task from list
	if (strcmp(argv[1], "remove") == 0) {
		remove(atoi(argv[2]));
	}

	//print help page with command and flag
	if (strcmp(argv[1], "help") == 0) {
		help();
	}

	//restores config to default
	if (strcmp(argv[1], "restore") == 0) {
		restore();
	}

	//start pomodoro or a specific task
	if (strcmp(argv[1], "start") == 0) {
		int interval_count = 0;
		if (argc == 3) {
			std::cout << "Starting task: " << argv[2] << std::endl;
			for (int j = 0; j < n; j++) {
				timer(p);
				interval_count++;

				if (interval_count % i == 0) {
					timer(i);
					interval_count++;
				}
				else {
					timer(s);
					interval_count++;
				}
			}
			remove(atoi(argv[2]));
		}
		else {
			timer(p);
		}
	}

	return 0;
}

void timer(int time) {
	int counter = 60 * time; //amount of seconds

		int min = time - 1;
		int sec = 59;

	    Sleep(1000);
	    while (counter >= 1)
	    {
	        if (sec < 10) {
				std::cout << "\rTime remaining: " << min << ":0" << sec  << std::flush;
			}
			else {
				std::cout << "\rTime remaining: " << min << ":" << sec  << std::flush;
			}
	        Sleep(1000);
			sec--;
	        counter--;
			if (sec == 0) {
				min--;
				sec = 59;
			}
	    }
		min = 0;
		sec = 0;
		std::cout << "\rTime remaining: " << min << ":" << sec  << std::flush;
}

void remove(int id) {
	std::ifstream infile("tasks.txt");
	std::string line;

	std::vector<std::string> tasks;
	int index = id;

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

void help() {
	std::cout << "add   : takes a string input and appends the task list file." << std::endl;
	std::cout << "remove: takes the task index integer and removes the task from task list file." << std::endl;
	std::cout << "print : takes no input and prints all tasks with thier index." << std::endl;
	std::cout << "clear : takes no input and removes all tasks from task list file." << std::endl;
	std::cout << "help  : takes no input and removes all tasks from task list file." << std::endl;
}

void print() {
	std::ifstream infile("tasks.txt");
	std::string line;
	int index = 0;
	while (std::getline(infile, line)) {
		std::cout << "[" << index  << "]: " << line << std::endl;
		index++;
	}
}

void clear() {
	std::ofstream myfile;
	myfile.open("tasks.txt");
	myfile.close();
	std::cout << "All tasks were removed." << std::endl;
}

void add(std::string task) {
	std::ofstream myfile;
	myfile.open("tasks.txt", std::ios_base::app);
	myfile << task << std::endl;
	myfile.close();
}

void load_config(int &n, int &i, int &p, int &s, int &l) {
	// load default config
	std::ifstream infile("config.txt");
	std::string line;
	std::getline(infile, line);
	n = stoi(line);
	std::getline(infile, line);
	i = stoi(line);
	std::getline(infile, line);
	p = stoi(line);
	std::getline(infile, line);
	s = stoi(line);
	std::getline(infile, line);
	l = stoi(line);
}

void restore() {
	std::ofstream myfile;
	myfile.open("config.txt");
	myfile << "1" << std::endl;
	myfile << "4" << std::endl;
	myfile << "25" << std::endl;
	myfile << "5" << std::endl;
	myfile << "15" << std::endl;
	myfile.close();
}