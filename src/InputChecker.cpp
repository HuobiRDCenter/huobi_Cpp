#include "InputChecker.h"

namespace Huobi {

    InputChecker* InputChecker::instance = nullptr;

    InputChecker* InputChecker::checker() {
        if (instance == nullptr) {
            instance = new InputChecker();
        }
        return instance;
    }
}
