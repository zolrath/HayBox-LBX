#include "modes/extra/MultiVersusLBX.hpp"

#define ANALOG_STICK_MIN 0
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

MultiVersusLBX::MultiVersusLBX(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right   },
        socd::SocdPair{ &InputState::down,   &InputState::up      },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up    },
    };
}

// bindings in MV are
// X - attack
// Y - special
// B - dodge
// A - jump
// RT - neutral dodge -- this needs to be changed in-game
// LT - pickup item -- this needs to be changed in-game
// RB - neutral attack
// LB - neutral special
// dpad up - taunt 1
// dpad right - taunt 2
// dpad down - taunt 3
// dpad left - taunt 4
// Make sure to bind C buttons to right stick in Steam, in MV bindings
// by default right stick translates to input direction + attack, can be
// changed to specials in game bindings
void MultiVersusLBX::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Bind box layout X and Y to "jump" in-game - MV detault A button
    outputs.a = inputs.x || inputs.y;

    outputs.start = !inputs.nunchuk_c && inputs.start;

    // MY + Start for "Reset" in the Lab. Not supported by GameCube adapter.
    outputs.select = inputs.nunchuk_c && inputs.start;

    // Home not supported by GameCube adapter.
    outputs.home = inputs.home;

    // L or Nunchuk Z = Dodge  - MV default B button
    if (inputs.nunchuk_connected) {
        outputs.b = inputs.nunchuk_z;
    }

    // R = LT. Pickup item - MV default LT button
    outputs.triggerRDigital = inputs.r;

    // box layout L - "neutral evade" - RT in MV, *** BIND IN GAME ***
    outputs.triggerLDigital = inputs.l;

    if (!inputs.mod_x) {
        // box layout A - attack - MV default X button
        outputs.x = inputs.a;

        // box layout B - Special - MV default Y button
        outputs.y = inputs.b;

        // box layout Z = Dodge - MV default B button
        // OR in case nunchuhk Z already pressed
        outputs.b = outputs.b || inputs.z;

        // box layout LS = Neutral attack - MV default RB button
        outputs.buttonL = inputs.lightshield;

        // box layout MS = Neutral special - MV default LB button
        outputs.buttonR = inputs.midshield;
    }

    // MX activates a layer for "neutral" binds
    if (inputs.mod_x && !inputs.mod_y) {
        // MX + box layout A = "neutral attack" - MV default RB button
        outputs.buttonL = inputs.a;

        // MX + box layout B "neutral special" - MV default LB button
        outputs.buttonR = inputs.b;

        // MX + box layout Z = "neutral evade" - RT in MV, *** BIND IN GAME *** .
        outputs.triggerLDigital = outputs.triggerLDigital || inputs.z;

        // MX + box layout LS = D-Pad Up. - MV default "taunt 1"
        outputs.dpadUp = inputs.lightshield;

        // MX + box layout C down = pick up  - MV default LT button
        outputs.triggerRDigital = outputs.triggerRDigital || inputs.c_down;
    }

    // MY activates C-Stick to D-Pad conversion.
    if ((inputs.mod_y && !inputs.mod_x) || inputs.nunchuk_c) {
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadUp = inputs.c_up;
    }
}

void MultiVersusLBX::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.up,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    if (inputs.mod_y && !inputs.mod_x) {
        // MY slows down the cursor for easier menu navigation.
        // Menu cursor speed can also be turned down in-game under "Interface" settings.
        // 128 ± 76 results in the slowest cursor that still actuates directional inputs in-game.
        outputs.leftStickX = ANALOG_STICK_NEUTRAL + directions.x * 76;
        outputs.leftStickY = ANALOG_STICK_NEUTRAL + directions.y * 76;

        if (directions.diagonal) {
            // Maintain a consistent cursor velocity when MY is held.
            // ⌊76 × √2/2⌋ = 53
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + directions.x * 53;
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + directions.y * 53;
        }

        // Also shut off C-Stick for D-Pad conversion.
        outputs.rightStickX = ANALOG_STICK_NEUTRAL;
        outputs.rightStickY = ANALOG_STICK_NEUTRAL;
    }

    if (outputs.triggerLDigital) {
        outputs.triggerLAnalog = 140;
    }

    if (outputs.triggerRDigital) {
        outputs.triggerRAnalog = 140;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
