#ifndef _CORE_KEYBOARDMODE_HPP
#define _CORE_KEYBOARDMODE_HPP

#include "core/InputMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

#include <TUKeyboard.hpp>

class KeyboardMode : public InputMode {
  public:
    KeyboardMode(socd::SocdType socd_type);
    ~KeyboardMode();
    void SendReport(InputState &inputs);

  protected:
    void Press(uint8_t keycode, bool press);
    virtual void UpdateKeys(InputState &inputs) = 0;

  private:
    TUKeyboard *_keyboard;
};

#endif
