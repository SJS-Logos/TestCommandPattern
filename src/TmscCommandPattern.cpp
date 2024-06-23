#include "TmscFindInterfaceIdCommand.h"
#include "mock_tmsc_invoker.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

int main()
{
  auto operations = std::make_unique<TmscFindInterfaceIdOperation<mock_tmsc_invoker>>();
  auto callback = [](bool ok, int interfaceId) {
    if (ok) {
      std::cout << "Found interface hello " << interfaceId << "\n";
    }
    else {
      std::cout << "Something went wrong\n";
    }
  };
  std::string helloString = std::string("hello");
  operations->action( helloString, callback );

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "Program end\n";
}