#ifndef _CORE_SOCD_HPP
#define _CORE_SOCD_HPP

#include "state.hpp"
#include "stdlib.hpp"

namespace socd {

    typedef enum {
        SOCD_NEUTRAL,
        SOCD_2IP,
        SOCD_2IP_NO_REAC,
        SOCD_KEYBOARD,
        SOCD_PRIORITY,
    } SocdType;

    typedef struct SocdPair {
        SocdPair() : prioritize_input_1(false) {}

        SocdPair(bool InputState::*input_dir1, bool InputState::*input_dir2)
            : prioritize_input_1(false) {
            this->input_dir1 = input_dir1;
            this->input_dir2 = input_dir2;
        }

        SocdPair(
            bool InputState::*input_dir1,
            bool InputState::*input_dir2,
            bool prioritize_input_1
        ) {
            this->input_dir1 = input_dir1;
            this->input_dir2 = input_dir2;
            this->prioritize_input_1 = prioritize_input_1;
        }

        bool InputState::*input_dir1;
        bool InputState::*input_dir2;
        bool prioritize_input_1;
    } SocdPair;

    typedef struct {
        bool was_dir1 = false;
        bool was_dir2 = false;
        bool lock_dir1 = false;
        bool lock_dir2 = false;
    } SocdState;

    void twoIPNoReactivate(bool &input_dir1, bool &input_dir2, SocdState &socd_state);

    void twoIP(bool &input_dir1, bool &input_dir2, SocdState &socd_state);

    void neutral(bool &input_dir1, bool &input_dir2);

    void priority(bool &input_dir1, bool &input_dir2, bool prioritize_input_1);
}

#endif
