#include "modes/extra/BindingModeLBX.hpp"

#define ANALOG_STICK_MIN 0
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

BindingModeLBX::BindingModeLBX(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right   },
        socd::SocdPair{ &InputState::down,   &InputState::up      },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up    },
    };
}

// This mode exists to make it easy to bind keys in Steam Settings -> Controller -> Select Arduino
// Leonardo -> Test Device Inputs -> Setup Device Inputs In this mode it will have you use each
// button on the controller, but in most of the game bindings not all buttons are bound. Here, we
// set it up so we can hit all buttons and dpad/joystick combinations so we can easily set the LBX
// up for Steam Input.

// For reference, the LBX is set up with the following buttons:

// Left hand cluster of 4:
// l left down right

// Left hand cluster of 3:
//                     1 2
//                       3
// mod_x nunchuk_c mod_y

// Center top button:
// start

// Right 8 buttons:
//       1 2 3 4
//       5 6 7 8
// r y lightshield midshield
// b x z up

// Right hand cluster of 5:
//    1 2 3
//    4 5
//  c_left c_up c_right
//  c_down a

// Now that we know the input binds, we can plan out and ensure we have all output bindings
// accounted for We need:
//    abxy
//    bumpers
//    triggers
//    dpad
//    sticks
//    stick buttons
//    start
//    select
//    home
void BindingModeLBX::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Let's use my default bindings for SF6 for our test

    // This means the right cluster of 8 are:
    //  X Y LB LT
    //  A B RB RT
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.buttonL = inputs.lightshield;
    outputs.buttonR = inputs.midshield;
    outputs.triggerLDigital = inputs.z;
    outputs.triggerRDigital = inputs.up;

    // On the left hand top cluster, we keep the buttons as L, left, down, right and bind L to left
    // stick click
    outputs.leftStickClick = !inputs.mod_y && inputs.l;
    outputs.rightStickClick = inputs.mod_y && inputs.l;

    // By default up/down/left/right are all analog it seems, so we'll use mod_x as the up in this
    // binding. Then we can use nunchuk_c to turn the right stick into the dpad.

    // Turn on D-Pad layer by holding Nunchuk C button.
    // Also, turn the L button (leftmost on the left button cluster) to right stick click.
    if (inputs.nunchuk_c) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }

    outputs.start = !inputs.nunchuk_c && !inputs.mod_y && inputs.start;
    outputs.select = inputs.nunchuk_c && !inputs.mod_y && inputs.start;
    outputs.home = inputs.mod_y && !inputs.nunchuk_c && inputs.start;
}

void BindingModeLBX::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // We'll use the mod_x button for up in this binding.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.mod_x,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    // nunchuk_c converts right stick to D-Pad
    if (inputs.nunchuk_c) {
        // Also shut off C-Stick for D-Pad conversion.
        outputs.rightStickX = ANALOG_STICK_NEUTRAL;
        outputs.rightStickY = ANALOG_STICK_NEUTRAL;
    }
}
