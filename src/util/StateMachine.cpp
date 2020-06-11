#include "StateMachine.h"

namespace util {
    StateMachine::StateMachine(StateID initial_state) :
        current_state_(initial_state),
        new_state_(0),
        transiting_(false) {
    }

    void StateMachine::startup(StateID new_state) {
        transit(new_state);
        // 启动状态机，状态迁移至某一终态后，该函数返回
        if (new_state_ != CANNOT_HAPPEN) {
            stateEngine();
        }
    }

    void StateMachine::transit(StateID new_state) {
        transiting_ = true;
        new_state_ = new_state;
    }

    void StateMachine::stateEngine() {
        // 状态迁移尚未完成之前
        while (transiting_) {
            transiting_ = false;

            auto state_map = getStateMap();

            // 从状态图取得对应下一状态的指针
            auto state = state_map[new_state_].state;

            // 切换到新的状态
            setCurrentState(new_state_);

            assert(state != nullptr);
            state->invokeStateAction(this);
        }
    }
}
