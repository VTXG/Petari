#pragma once

#include "Game/NameObj/NameObj.hpp"
#include <revolution.h>

class AudBgmConductor : public NameObj {
public:
    AudBgmConductor();

    virtual ~AudBgmConductor();
    
    virtual void init(const JMapInfoIter &rIter);
    virtual void movement();

    void playPinchEventBgmLevel(bool);
    void setStateBit(u32);
    void stopPinchEventBgmSoon();
    void movementPinchEventBgm();

    s32 _C;
    s32 _10;
    s32 _14;
    s32 _18;
    bool _1C;
};
