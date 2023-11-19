# Pomoadoro
### Background

[Pomodoro Technique](https://github.com/adoante/Pomoadoro/blob/main/Pomodoro%20Technique.md)
### Functionality

- [x] Add Tasks
- [x] Set Pomodoro Length (default 25min)
- [x] Set Break length (default Short 5min, Long 15min)
- [x] Set Break interval (default short break after each pomodoro, long break after 4 pomodoros )
- [x] Start Pomodoro (single, not task specific)
- [ ] Start Task (starts your preset number of pomodoros)
- [x] Print task list
- [x] Delete tasks
- [x] Help page
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
void timer(int time);
```

```c++
/*
Adds a task to the end of the task list
Using any flag inputs and default values to create a task
*/
void add();
```

```c++
/*
Removes a specific task from the task list and updates ids
*/
void remove();
```

```c++
/*
Prints all tasks and there remaining pomodoros
*/
void print();
```

```c++
/*
Removes all tasks from task list
*/
void clear();
```

```c++
/*
Prints all flags and commands with thier uses and examples
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
void load_config();
```

```c++
/*
Restores the default values for n, i, p, s, l.
*/
void restore();
```
