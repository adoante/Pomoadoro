# Pomoadoro
### Background

[Pomodoro Technique](https://github.com/adoante/Pomoadoro/blob/main/Pomodoro%20Technique.md)
### Functionality

### To Do:

- [x] Add Tasks
- [x] Set Pomodoro Length (default 25min)
- [x] Set Break length (default Short 5min, Long 15min)
- [x] Set Break interval (default short break after each pomodoro, long break after 4 pomodoros )
- [x] Start Pomodoro (single, not task specific)
- [ ] Start Task
- [x] Print task list
- [x] Delete tasks
- [x] Help page
- [ ] Add comments
### User input

```
./pomoadoro add 'math hw'
./pomoadoro start 5
./pomoadoro start
./pomoadoro end
./pomoadoro print
./pomoadoro remove 1
./pomoadoro clear
./pomoadoro help
./pomoadoro -n 4 -p 30 -s 10 -l 20 -i 2
./pomoadoro restore
```

- `add` requires a `string` input and can take all flags
- `start` requires no input and can take all flags
- `end` requires no input and cannot take flags
- `print` prints task list
- `remove` requires the task id
- `clear` deletes all tasks
- `help` prints help page
- `restore` sets flag values to default
- `load_config` loads flag values from file
- `-t` task id to start, cannot be paired with other flags
- `-n` flag for number of pomodoros
- `-p` flag for pomodoro time length
- `-s` flag for short break length
- `-l` flag for long break length
- `-i` flag for long break intervals
### Functions

```c++
/*
Starts a count down timer. Time is in minutes with format M:ss
*/
void timer(int time){
	
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
```

```c++
/*
Adds a task to the end of the task list
*/
void add() {
	std::ofstream myfile;
	myfile.open("tasks.txt", std::ios_base::app);
	myfile << task << std::endl;
	myfile.close();
}
```

```c++
/*
Removes a specific task from the task list
*/
void remove() {
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
```

```c++
/*
Prints all tasks
*/
void print() {
	std::ifstream infile("tasks.txt");
	std::string line;
	int index = 0;
	while (std::getline(infile, line)) {
		std::cout << "[" << index  << "]: " << line << std::endl;
		index++;
	}
}
```

```c++
/*
Removes all tasks from task list
*/
void clear() {
	std::ofstream myfile;
	myfile.open("tasks.txt");
	myfile.close();
	std::cout << "All tasks were removed." << std::endl;
}
```

```c++
/*
Prints all flags and commands with thier uses
*/
void help() {
std::cout << "add    : takes a string input and appends the task list." << std::endl;
std::cout << "remove : takes the task index integer and removes the task from task list." << std::endl;
std::cout << "print  : takes no input and prints all tasks with thier index." << std::endl;
std::cout << "clear  : takes no input and removes all tasks from task list file." << std::endl;
std::cout << "help   : takes no input and prints this help text." << std::endl;
std::cout << "restore: takes no input and sets default pomodoro values." << std::endl;
std::cout << "-n flag for number of pomodoros." << std::endl;
std::cout << "-p flag for pomodoro time length." << std::endl;
std::cout << "-s flag for short break length." << std::endl;
std::cout << "-l flag for long break length." << std::endl;
std::cout << "-i flag for long break intervals." << std::endl;
}
```

```c++
/*
Loads the values for n, i, p, s, l.
*/
void load_config() {
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
```

```c++
/*
Restores the default values for n, i, p, s, l.
*/
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
```
