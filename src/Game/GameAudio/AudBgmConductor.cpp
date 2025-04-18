#include "Game/GameAudio/AudBgmConductor.hpp"
#include "Game/AudioLib/AudBgm.hpp"
#include "Game/AudioLib/AudWrap.hpp"
#include "Game/NameObj/NameObj.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "Game/Util/SceneUtil.hpp"
#include "Game/Util/SoundUtil.hpp"

AudBgmConductor::AudBgmConductor() : NameObj("AudBgmConductor") {
    _C = 0;
    _10 = 0;
    _14 = -1;
    _18 = -1;
    _1C = false;
}

AudBgmConductor::~AudBgmConductor() {
    
}

void AudBgmConductor::init(const JMapInfoIter &rIter) {
    MR::connectToScene(this, 25, -1, -1, -1);

    if (MR::isEqualStageName("IceVolcanoGalaxy") || MR::isEqualStageName("OceanRingGalaxy"))
        MR::registerDemoSimpleCastAll(this);
}

#ifdef NON_MATCHING
void AudBgmConductor::movement() {
    movementPinchEventBgm();
    AudBgm *pBgm = AudWrap::getStageBgm();

    if (pBgm) {
        // Todo
    }
}
#endif

#ifdef NON_MATCHING
void AudBgmConductor::playPinchEventBgmLevel(bool a1) {
    if (MR::isPlayingSubBgmID(0x1000017) ||
        MR::isPlayingSubBgmID(0x1000036) ||
        MR::isPlayingSubBgmID(0x100001D) ||
        MR::isPlayingSubBgmID(0x1000037) ||
        MR::isPlayingSubBgmID(0x1000042) ||
        MR::isPlayingSubBgmID(0x1000043)) {
        _14 = -1;
        _18 = -1;
    }
    else {
        if (!MR::isPlayerDead() && !MR::isPowerStarGetDemoActive()) {
            if (_14 < 0) {
                if (a1)
                    MR::startSubBGM("BGM_PINCH_2", false);
                else
                    MR::startSubBGM("BGM_PINCH_1", false);

                if (a1) {
                    MR::moveVolumeSubBGM(0.0f, 0);
                    _18 = 2;
                }
                
                _1C = false;
            }
            
            _14 = 3;
        }
    }
}
#endif

void AudBgmConductor::setStateBit(u32 a1) {
    _C |= a1;
}

void AudBgmConductor::stopPinchEventBgmSoon() {
    _14 = 0;
    _1C = true;
}

#ifdef NON_MATCHING
void AudBgmConductor::movementPinchEventBgm() {
    if (!MR::isPlayingSubBgmID(0x1000017) &&
        !MR::isPlayingSubBgmID(0x1000036) &&
        !MR::isPlayingSubBgmID(0x100001D) &&
        !MR::isPlayingSubBgmID(0x1000037) &&
        !MR::isPlayingSubBgmID(0x1000042) &&
        !MR::isPlayingSubBgmID(0x1000043)) {
        if (MR::isPowerStarGetDemoActive() || MR::isPlayerDead()) {
            _14 = -1;
            _18 = -1;
            _1C = false;
        }
        else if (_14 >= 0) {
            if (!_18) {
                MR::moveVolumeSubBGM(1.0f, 90);
                _18 = -1;
            }

            if (_18 > 0)
                _18--;

            if (_14-- - 1 <= 0) {
                if (_1C)
                    MR::stopSubBGM(1);
                else
                    MR::stopSubBGM(90);

                _14 = -1;
                _18 = -1;
                _1C = false;
            }
        }
    }
}
#endif
