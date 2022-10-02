#ifndef _MODES_STRIVEKEYBOARDMODE_HPP
#define _MODES_STRIVEKEYBOARDMODE_HPP

#include "core/KeyboardMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class StriveKeyboardMode : public KeyboardMode {
  public:
    StriveKeyboardMode(socd::SocdType socd_type);

  private:
    void UpdateKeys(InputState &inputs);
};

#endif
