#ifndef _MODES_MULTIVERSUSLBX_HPP
#define _MODES_MULTIVERSUSLBX_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class MultiVersusLBX : public ControllerMode {
  public:
    MultiVersusLBX(socd::SocdType socd_type);

  protected:
    virtual void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    virtual void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
