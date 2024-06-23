#pragma once

#include "TmscGetValueCommand.h"
#include "mock_tmsc.h"
#include <functional>
#include <memory>
#include <string>

class TmscFindInterfaceIdCommand {
public:
  TmscFindInterfaceIdCommand(const std::string& interfaceName,
    std::function<void(bool ok, int interfaceIndex)> callback,
    uint32_t maxNoOfInterfaces = MAX_NO_OF_INTERFACES);

  void execute();

private:
  const std::string interfaceName_;
  std::function<void(bool ok, int interfaceIndex)> callback_;
  std::unique_ptr<TmscGetValueCommand> command_;
  uint32_t maxNoOfInterfaces_;
};
