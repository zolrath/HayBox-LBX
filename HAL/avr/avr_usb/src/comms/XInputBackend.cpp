#include "comms/XInputBackend.hpp"

#include "core/CommunicationBackend.hpp"
#include "core/state.hpp"

#include <XInput.h>

XInputBackend::XInputBackend(InputSource **input_sources, size_t input_source_count)
    : CommunicationBackend(input_sources, input_source_count) {
    XInput.setAutoSend(false);
    XInput.setJoystickRange(0, 255);
    XInput.setTriggerRange(0, 255);
    XInput.begin();
}

XInputBackend::~XInputBackend() {
    XInput.reset();
}

void XInputBackend::SendReport() {
    // Update inputs from all sources at once.
    ScanInputs();

    UpdateOutputs();

    // Digital outputs
    XInput.setButton(BUTTON_B, _outputs.b);
    XInput.setButton(BUTTON_A, _outputs.a);
    XInput.setButton(BUTTON_Y, _outputs.y);
    XInput.setButton(BUTTON_X, _outputs.x);
    XInput.setButton(BUTTON_RB, _outputs.buttonR);
    XInput.setButton(TRIGGER_RIGHT, _outputs.triggerRDigital);
    XInput.setButton(BUTTON_LB, _outputs.buttonL);
    XInput.setButton(TRIGGER_LEFT, _outputs.triggerLDigital);
    XInput.setButton(BUTTON_BACK, _outputs.select);
    XInput.setButton(BUTTON_START, _outputs.start);
    XInput.setButton(BUTTON_R3, _outputs.rightStickClick);
    XInput.setButton(BUTTON_L3, _outputs.leftStickClick);
    XInput.setButton(BUTTON_LOGO, _outputs.home);

    // Analog outputs
    XInput.setJoystickX(JOY_LEFT, _outputs.leftStickX);
    XInput.setJoystickY(JOY_LEFT, 255 - _outputs.leftStickY);
    XInput.setJoystickX(JOY_RIGHT, _outputs.rightStickX);
    XInput.setJoystickY(JOY_RIGHT, 255 - _outputs.rightStickY);
    XInput.setTrigger(TRIGGER_LEFT, _outputs.triggerLAnalog + 1);
    XInput.setTrigger(TRIGGER_RIGHT, _outputs.triggerRAnalog + 1);

    // D-pad
    XInput.setDpad(_outputs.dpadUp, _outputs.dpadDown, _outputs.dpadLeft, _outputs.dpadRight);

    XInput.send();
}