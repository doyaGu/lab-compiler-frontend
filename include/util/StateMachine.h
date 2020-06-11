#ifndef UTIL_STATEMACHINE_H
#define UTIL_STATEMACHINE_H

#include <cassert>
#include <cstdint>

namespace util {
    class StateMachine;

    class StateBase {
    public:
        virtual void invokeStateAction(StateMachine *sm) const = 0;
    };

    template<typename SM, void (SM::*Func)()>
    class StateAction : public StateBase {
    public:
        void invokeStateAction(StateMachine *sm) const override {
            // 下行转换为 StateMachine 的派生类
            SM *derived_sm = static_cast<SM *>(sm);
            // 调用状态函数
            (derived_sm->*Func)();
        }
    };

    struct StateMapRow {
        const StateBase *const state;
    };
    using StateMap = const StateMapRow *;

    class StateMachine {
    public:
        using StateID = uint8_t;
        enum State : StateID {
            CANNOT_HAPPEN = 0xFF
        };

        explicit StateMachine(StateID initial_state = 0);

        virtual ~StateMachine() = default;

        [[nodiscard]] StateID getCurrentState() const { return current_state_; }

    protected:
        void startup(StateID new_state);

        void transit(StateID new_state);

    private:
        StateID current_state_;

        StateID new_state_;

        bool transiting_;

        virtual StateMap getStateMap() = 0;

        void setCurrentState(StateID new_state) { current_state_ = new_state; }

        void stateEngine();
    };

#define STATE_DECLARE(state_machine, state_name) \
    void ST_##state_name(); \
    StateAction<state_machine, &state_machine::ST_##state_name> state_name;

#define STATE_DEFINE(state_machine, state_name) \
    void state_machine::ST_##state_name()
}

#endif //UTIL_STATEMACHINE_H
