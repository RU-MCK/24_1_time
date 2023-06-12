#include<iostream>
#include<ctime>
#include <map>

int choice(const std::string &str) {
  if (str == "exit")
    return 1;
  else if (str == "begin")
    return 2;
  else if (str == "end")
    return 3;
  else if (str == "status")
    return 4;
  else {
    std::cout << "Enter Error!" << std::endl;
    return 0;
  }
}
std::string time(int seconds) {
  int h = seconds / 3600;
  seconds -= h * 3600;
  int m = seconds / 60;
  seconds -= m * 60;
  std::string result = "hour: " + std::to_string(h)
      + " minutes: " + std::to_string(m)
      + " seconds: " + std::to_string(seconds) + ".";
  return result;
}
int main() {
  std::string command;
  std::string nameTask;
  std::string currentTask;
  bool task = false;
  int start = 0;
  int finish = 0;
  std::map<std::string, std::string> list;
  do {
    std::cout << "Input the command: " << std::endl
              << "<begin> or <end> or <status> or <exit>: " << std::endl;
    std::cin >> command;

    switch (choice(command)) {
      case 1://exit
        std::cout << "Exit" << std::endl;
        break;
      case 2://begin
        std::cout << "Input your task: " << std::endl;
        std::cin >> nameTask;
        if (!task) {
          start = static_cast<int>(std::time(nullptr));
          currentTask = nameTask;
          task = true;
        } else {
          finish = static_cast<int>(std::time(nullptr));
          list.emplace(time(finish - start), currentTask);
          start = static_cast<int>(std::time(nullptr));
          currentTask = nameTask;
        }
        break;
      case 3://end
        if (task) {
          finish = static_cast<int>(std::time(nullptr));
          list.emplace(time(finish - start), currentTask);
          task = false;
        } else
          std::cout << "No current task." << std::endl;
        break;
      case 4://status
        if (!list.empty()) {
          for (auto &item : list)
            std::cout << "Task: < " << item.second << " >  Spent - "
                      << item.first << std::endl;
        } else
          std::cout << "Task list is empty." << std::endl;
        if (task)
          std::cout << "Current task: " << currentTask << std::endl;
        break;
      default:break;
    }
  } while (command != "exit");
  return 0;
}