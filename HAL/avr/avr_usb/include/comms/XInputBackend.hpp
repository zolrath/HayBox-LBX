#ifndef _COMMS_XINPUTBACKEND_HPP
#define _COMMS_XINPUTBACKEND_HPP

#include "core/CommunicationBackend.hpp"
#include "core/ControllerMode.hpp"
#include "core/InputSource.hpp"
#include "stdlib.hpp"

#include <XInput.h>

class XInputBackend : public CommunicationBackend {
  public:
    XInputBackend(InputSource **input_sources, size_t input_source_count);
    ~XInputBackend();
    void SendReport();
};

#endif
