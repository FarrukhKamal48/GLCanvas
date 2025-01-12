#pragma once
#include <GLBox.h>

typedef uint32_t FSMKey;
struct FSMData;

class State {
public:
    State(FSMKey state, FSMData& data) : m_State(state), m_CanvasData(data) {}
    virtual ~State() {}
    FSMKey GetState() { return m_State; }
    virtual void OnEnter() = 0;
    virtual void OnEvent(Event& event) = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnExit() = 0;
    virtual FSMKey GetNextState() = 0;
protected:
    FSMKey m_State;
    FSMData& m_CanvasData;
};
