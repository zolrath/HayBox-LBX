#ifndef _MODES_MULTIVERSUSLBXFURD_HPP
#define _MODES_MULTIVERSUSLBXFURD_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class MultiVersusLBXFurd : public ControllerMode {
  public:
    MultiVersusLBXFurd(socd::SocdType socd_type);

  protected:
    virtual void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    virtual void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
