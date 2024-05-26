#ifndef _MODES_BINDINGMODELBX_HPP
#define _MODES_BINDINGMODELBX_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class BindingModeLBX : public ControllerMode {
  public:
    BindingModeLBX(socd::SocdType socd_type);

  protected:
    virtual void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    virtual void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
