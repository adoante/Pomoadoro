#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <windows.h>

void timer(int);
void remove(int, std::string);
void help();
void clear(std::string);
void print(std::string);
void add(std::string, std::string);
void load_config(int&, int&, int&, int&, int&, std::string);
void restore(std::string);

int main (int argc, char *argv[]) {

	std::string tasklist = "D:\\Documents\\CodingProjects\\pomodoro\\tasks.txt";
	std::string configfile = "D:\\Documents\\CodingProjects\\pomodoro\\config.txt";

	int n = 0;	// number of pomodoros
	int i = 0;	// interval of long breaks
	int p = 0;	// length of pomodoro
	int s = 0;	// length of short break
	int l = 0;	// length of long break

	load_config(n, i, p, s, l, configfile);

	int opt;
	
	// allows user to set config
	while ((opt = getopt(argc, argv, "n:p:s:l:i:")) != -1) {
	    switch (opt) {
			case ('n'):
				n = atoi(optarg);
				std::cout << "Set number of pomodoros: " << n << " per task."  << std::endl;
				break;
			case ('p'):
				p = atoi(optarg);
				std::cout << "Set length of pomodoro: " << p << " minutes." << std::endl;
				break;
			case ('s'):
				s = atoi(optarg);
				std::cout << "Set length of short break: " << s << " minutes." << std::endl;
				break;
			case ('l'):
				l = atoi(optarg);
				std::cout << "Set length of long break: " << l << " minutes." << std::endl;
				break;
			case ('i'):
				i = atoi(optarg);
				std::cout << "Set interval of long breaks: " << i << " (one long after " << i << " pomodoros.)" << std::endl;
				break;
		}
	}

	// add task to list
	if (strcmp(argv[1], "add") == 0) {
		add(argv[2], tasklist);
	}

	//print task list
	if (strcmp(argv[1], "print") == 0) {
		print(tasklist);
	}

	//clear all task from list
	if (strcmp(argv[1], "clear") == 0) {
		clear(tasklist);
	}

	//remove task from list
	if (strcmp(argv[1], "remove") == 0) {
		remove(atoi(argv[2]), tasklist);
	}

	//print help page with command and flag
	if (strcmp(argv[1], "help") == 0) {
		help();
	}

	//restores config to default
	if (strcmp(argv[1], "restore") == 0) {
		restore(configfile);
	}

	//start pomodoro or a specific task
	if (strcmp(argv[1], "start") == 0) {
		int interval_count = 0;
		if (argc == 3) {
			std::cout << "Starting task: " << argv[2] << std::endl;
			for (int j = 0; j < n; j++) {
				std::cout << std::endl;
				std::cout << "*** Time to focus! ***"<< std::endl;
				timer(p);
				std::cout << std::endl;
				interval_count++;

				if (interval_count % i == 0) {
					std::cout << std::endl;
					std::cout << "*** Time for a long break! ***"<< std::endl;
					timer(l);
					std::cout << std::endl;
					interval_count++;
				}
				else {
					std::cout << std::endl;
					std::cout << "*** Time for a short break! ***"<< std::endl;
					timer(s);
					interval_count++;
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
			remove(atoi(argv[2]), tasklist);
		}
		else {
			timer(p);
		}
	}

	return 0;
}

// Functions

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
}

void remove(int id, std::string tasklist) {
	std::ifstream infile(tasklist);
	std::string line;

	std::vector<std::string> tasks;
	int index = id;

	while (std::getline(infile, line)) {
		tasks.push_back(line);
	}

	std::cout << "Removed task [" << index << "]: " << tasks[index] << std::endl;
	tasks[index] = "";

	std::ofstream myfile;
	myfile.open(tasklist);
	for (int i = 0; i < tasks.size(); i++) {
		if (tasks[i] != "") {
			myfile << tasks[i] << std::endl;
		}
	}
	myfile.close();
}

void help() {
	std::cout << "******************************************************************************" << std::endl;
	std::cout << "* add    : takes a string input and appends the task list.                   *" << std::endl;
	std::cout << "* remove : takes the task index integer and removes the task from task list. *" << std::endl;
	std::cout << "* print  : takes no input and prints all tasks with thier index.             *" << std::endl;
	std::cout << "* clear  : takes no input and removes all tasks from task list file.         *" << std::endl;
	std::cout << "* help   : takes no input and prints this help text.                         *" << std::endl;
	std::cout << "* restore: takes no input and sets default pomodoro values.                  *" << std::endl;
	std::cout << "* -n flag for number of pomodoros.                                           *" << std::endl;
	std::cout << "* -p flag for pomodoro time length.                                          *" << std::endl;
	std::cout << "* -s flag for short break length.                                            *" << std::endl;
	std::cout << "* -l flag for long break length.                                             *" << std::endl;
	std::cout << "* -i flag for long break intervals.                                          *" << std::endl;
	std::cout << "******************************************************************************" << std::endl;
}

void print(std::string tasklist) {
	std::ifstream infile(tasklist);
	std::string line;
	int index = 0;
	while (std::getline(infile, line)) {
		std::cout << "[" << index  << "]: " << line << std::endl;
		index++;
	}
}

void clear(std::string tasklist) {
	std::ofstream myfile;
	myfile.open(tasklist);
	myfile.close();
	std::cout << "All tasks were removed." << std::endl;
}

void add(std::string task, std::string tasklist) {
	std::ofstream myfile;
	myfile.open(tasklist, std::ios_base::app);
	myfile << task << std::endl;
	myfile.close();
}

void load_config(int &n, int &i, int &p, int &s, int &l, std::string configfile) {
	std::ifstream infile(configfile);
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

void restore(std::string configfile) {
	std::ofstream myfile;
	myfile.open(configfile);
	myfile << "1" << std::endl;
	myfile << "4" << std::endl;
	myfile << "25" << std::endl;
	myfile << "5" << std::endl;
	myfile << "15" << std::endl;
	myfile.close();
}