#include "TmscFindInterfaceIdCommand.h"

#include <iostream>
#include <thread>
#include <chrono>

int main()
{
  auto command = TmscFindInterfaceIdCommand("hello", [](bool ok, int interfaceId) {
    if (ok) {
      std::cout << "Found interface hello " << interfaceId << "\n";
    }
    else {
      std::cout << "Something went wrong\n";
    }
    });
  command.execute();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "Program end\n";
}