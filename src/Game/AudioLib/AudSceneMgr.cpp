#include "Game/AudioLib/AudSceneMgr.hpp"
#include "Game/AudioLib/AudEffector.hpp"
#include "Game/AudioLib/AudSystem.hpp"
#include "Game/AudioLib/AudWrap.hpp"
#include "Game/Speaker/SpkSystem.hpp"
#include "JSystem/JAudio2/JAUSectionHeap.hpp"
#include "revolution/types.h"

namespace {
    const AudSceneSoundInfo cSceneInfo[] = {
        {"dummy", "dummy", 0, -1 },
        {"Game", "HellProminenceGalaxy", 1, -1 },
        {"Game", "OceanRingGalaxy", 2, 5 },
        {"Game", "OceanFloaterLandGalaxy", 3, -1 },
        {"Game", "OceanPhantomCaveGalaxy", 4, 2 },
        {"Game", "EggStarGalaxy", 6, 0 },
        {"Game", "StarDustGalaxy", 7, 1 },
        {"Game", "BattleShipGalaxy", 8, -1 },
        {"Game", "CannonFleetGalaxy", 9, -1 },
        {"Game", "PhantomGalaxy", 0xA, -1 },
        {"Game", "CosmosGardenGalaxy", 0xB, -1 },
        {"Game", "AstroDome", 0xC, -1 },
        {"Game", "IceVolcanoGalaxy", 0xE, -1 },
        {"Game", "HeavenlyBeachGalaxy", 0xF, -1 },
        {"Game", "KoopaBattleVs1Galaxy", 0x10, -1 },
        {"Game", "AstroGalaxy", 0x11, -1 },
        {"Game", "HoneyBeeKingdomGalaxy", 0x12, 3 },
        {"Game", "ReverseKingdomGalaxy", 0x13, 4 },
        {"Game", "FileSelect", 0x14, -1 },
        {"Game", "SurfingLv1Galaxy", 0x15, -1 },
        {"Game", "SandClockGalaxy", 0x16, -1 },
        {"Game", "TriLegLv1Galaxy", 0x17, -1 },
        {"Game", "TriLegLv2Galaxy", 0x18, -1 },
        {"Game", "KoopaJrShipLv1Galaxy", 0x19, -1 },
        {"Game", "KoopaJrDriverGalaxy", 0x1B, -1 },
        {"Game", "FactoryGalaxy", 0x1C, -1 },
        {"Game", "HoneyBeeExGalaxy", 0x1D, -1 },
        {"Game", "TamakoroExLv1Galaxy", 0x1E, -1 },
        {"Game", "TamakoroExLv2Galaxy", 0x1F, -1 },
        {"Game", "HeavensDoorGalaxy", 0x20, -1 },
        {"Game", "FloaterOtaKingGalaxy", 0x21, -1 },
        {"Game", "TransformationExGalaxy", 0x22, -1 },
        {"Game", "LibraryRoom", 0x23, -1 },
        {"Game", "PeachCastleGardenGalaxy", 0x24, -1 },
        {"Game", "FishTunnelGalaxy", 0x25, -1 },
        {"Game", "TearDropGalaxy", 0x26, -1 },
        {"Game", "EpilogueDemoStage", 0x27, -1 },
        {"Game", "KoopaBattleVs3Galaxy", 0x28, -1 },
        {"Game", "DarkRoomGalaxy", 0x29, -1 },
        {"Game", "PeachCastleFinalGalaxy", 0x2A, -1 },
        {"Game", "SkullSharkGalaxy", 0x2B, -1 },
        {"Game", "KoopaBattleVs2Galaxy", 0x10, -1 },
        {"Game", "SurfingLv2Galaxy", 0x15, -1 },
        {"Game", "BeltConveyerExGalaxy", 0x1E, -1 },
        {"Game", "CocoonExGalaxy", 0, -1 },
        {"Game", "TeresaMario2DGalaxy", 0, -1 },
        {"Game", "BreakDownPlanetGalaxy", 0, -1 },
        {"Game", "CubeBubbleExLv1Galaxy", 0, -1 },
        {"Game", "CubeBubbleExLv2Galaxy", 0, -1 },
        {"Game", "FlipPanelExGalaxy", 0, -1 },
        {"Game", "SnowCapsuleGalaxy", 0, -1 },
        {"Game", "E3HeavenlyBeachGalaxy", 0xF, -1 },
    };

    const s8 cTable80530CFC[] = {0, 0, 0, 1, 3, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 0, 0xA, 0, 0xB, 1, 0xC, 0, 0xD, 0, 0xE, 3, 0xF, 0, 0x10, 0, 0x11, 0, 0x12, 0, 0x13, 1, 0x14, 3, 0x15, 0, 0x16, 0, 0x17, 0, 0x18, 0, 0x19, 0, 0x1A, 0, 0x1B, 0, 0x1C, 0, 0x1D, 0, 0x1E, 0, 0x1F, 0, 0x20, 0, 0x21, 0, 0x22, 2, 0x23, 0, 0x24, 0, 0x25, 0, 0x26, 0, 0x27, 0, 0x28, 0, 0x29, 0, 0x2A, 0, 0x2B};
    const s8 cTable80530D54[] = {0xFF,0xFF,0x17,0xFF,0x17,0xFF,0xA,0xFF};
    const s8 cTable80530D5C[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xD, 0x10, 0x14, 0x21, 0xE, 9, 0xFF, 0xFF, 0xE, 0x29, 9, 0x23, 0xE, 9, 0xFF, 0xFF, 0xF, 0x11, 0xC, 0xFF, 0xE, 0x2E, 0xFF, 0xFF, 0xD, 0xFF, 0xFF, 0xFF, 0xC, 0x15, 0x10, 0x2E, 0x15, 0x10, 9, 0xFF, 0x27, 0x2E, 0xFF, 0xFF, 0x16, 0x1D, 0xE, 0xD, 0x1A, 0x25, 0x26, 0xFF, 0x18, 0x19, 0xFF, 0xFF, 0xD, 0xE, 0x23, 0x28, 0xE, 9, 0x23, 0xFF, 0x1B, 0xFF, 0xFF, 0xFF, 0x26, 0x25, 0x2E, 0xFF, 0x18, 0x24, 0x2E, 0xFF, 0x18, 0x24, 0xFF, 0xFF, 0x1A, 0x2F, 0xFF, 0xFF, 9, 0x20, 0x23, 0xFF, 0x1E, 0xE, 0xFF, 0xFF, 0xC, 0x15, 0xFF, 0xFF, 0xC, 0xFF, 0xFF, 0xFF, 0x15, 0xFF, 0xFF, 0xFF, 0x15, 0xFF, 0xFF, 0xFF, 0x15, 0xFF, 0xFF, 0xFF, 0x1F, 0xD, 0xFF, 0xFF, 0x18, 0x24, 0xFF, 0xFF, 0x21, 0xFF, 0xFF, 0xFF, 0x21, 0xFF, 0xFF, 0xFF, 0x2C, 0x26, 0x25, 0x2A, 0x11, 0x15, 0xFF, 0xFF, 0x1E, 0xFF, 0xFF, 0xFF, 0x1A, 0x25, 0x26, 0xFF, 0x25, 0x2B, 0xFF, 0xFF, 0xE, 9, 0x13, 0x23, 0xE, 9, 0x23, 0xFF, 0x2D, 0x25, 0xFF, 0xFF, 0x1B, 0x15, 0xFF, 0xFF, 0x16, 0xFF, 0xFF, 0xFF, 0x25, 0x2B, 0x24, 0x23, 0xE, 0x13, 9, 0xFF};
}

AudSceneMgr::AudSceneMgr(JAUSectionHeap* pSectionHeap) : _4(0), _8(0), _C(-1), _10(0), mPlayerMode(0), _18(0), _1C(0), _1D(false) {
    mSectionHeap = pSectionHeap;
}

bool AudSceneMgr::isLoadDoneSystemInit() {
    return mSectionHeap->isWaveLoaded(0x7, 0);
}

void AudSceneMgr::loadStaticResource() {
    mSectionHeap->loadWaveArc(0x0);
    mSectionHeap->loadWaveArc(0x1);
    mSectionHeap->loadWaveArc(0x2);
    mSectionHeap->loadWaveArc(0x3);
    mSectionHeap->loadWaveArc(0x4);
    mSectionHeap->loadWaveArc(0x5);
    mSectionHeap->loadWaveArc(0x6);
    mSectionHeap->loadWaveArc(0x8);
    mSectionHeap->loadWaveArc(0xB);
}

bool AudSceneMgr::isLoadDoneStaticResource() {
    bool v = false;
    bool isWave0x0Loaded = mSectionHeap->isWaveLoaded(0x0, 0);
    bool isWave0x1Loaded = mSectionHeap->isWaveLoaded(0x1, 0);
    bool isWave0x2Loaded = mSectionHeap->isWaveLoaded(0x2, 0);
    bool isWave0x3Loaded = mSectionHeap->isWaveLoaded(0x3, 0);
    bool isWave0x4Loaded = mSectionHeap->isWaveLoaded(0x4, 0);
    bool isWave0x5Loaded = mSectionHeap->isWaveLoaded(0x5, 0);
    bool isWave0x6Loaded = mSectionHeap->isWaveLoaded(0x6, 0);
    bool isWave0x8Loaded = mSectionHeap->isWaveLoaded(0x8, 0);
    bool isWave0xBLoaded = mSectionHeap->isWaveLoaded(0xB, 0);

    if (isWave0x0Loaded && isWave0x1Loaded && isWave0x2Loaded &&
        isWave0x3Loaded && isWave0x4Loaded && isWave0x5Loaded &&
        isWave0x6Loaded && isWave0x8Loaded && isWave0xBLoaded) {
        v = true;
    }

    return v;
}

void AudSceneMgr::loadStageResource(const char* pSceneName, const char* pStageName) {
    loadStageResource(findSceneSoundInfo(pSceneName, pStageName));
}

void AudSceneMgr::loadStageResource(const AudSceneSoundInfo* pInfo) {
    _1C = 0;

    if (!pInfo) {
        return;
    }

    s8 stageResourceIndex = pInfo->mStageResourceIndex;
    s32 bgmSetId = (s32)cTable80530CFC[stageResourceIndex];
    s32 soundSetId = (s32)cTable80530CFC[stageResourceIndex + 1];
    const s8* pBgmWaveSet = &cTable80530D54[bgmSetId * 2];
    const s8* pSoundWaveSet = &cTable80530D5C[soundSetId * 4];

    if (mPlayerMode != _18) {
        _1C = 1;
    }

    eraseLastSeScenarioWaveSet();
    if (soundSetId != _8 || _1C == 1) {
        eraseLastBgmWaveSet();
        eraseLastSeWaveSet();

        if (_1C) {
            mSectionHeap->eraseWaveArc(0x22, 2);
            mSectionHeap->eraseWaveArc(0x22, 4);
            loadPlayerResource();
        }

        loadWaveSet(pSoundWaveSet, 4);
        loadWaveSet(pBgmWaveSet, 2);
    }
    else if (bgmSetId != _10) {
        eraseLastBgmWaveSet();
        loadWaveSet(pBgmWaveSet, 2);
    }

    _10 = bgmSetId;
    _18 = mPlayerMode;
    _8 = soundSetId;
}

bool AudSceneMgr::isLoadDoneStageResource() {
    const s8* pBgmWaveSet = &cTable80530D54[_10 * 2];
    const s8* pSoundWaveSet = &cTable80530D5C[_8 * 4];

    for (int i = 0; i < 2; i++) {
        s8 wave = pBgmWaveSet[i];
        if (wave < 0) {
            continue;
        }

        if (!mSectionHeap->isWaveLoaded(wave, 0)) {
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        s8 wave = pSoundWaveSet[i];
        if (wave < 0) {
            continue;
        }

        if (!mSectionHeap->isWaveLoaded(wave, 0)) {
            return false;
        }
    }

    if (_1C && !isPlayerResourceLoaded()) {
        return false;
    }

    return true;
}

void AudSceneMgr::loadScenarioResource(const char* pSceneName, const char* pStageName, s32 scenarioNo) {
    loadScenarioResource(findSceneSoundInfo(pSceneName, pStageName), scenarioNo);
}

void AudSceneMgr::loadScenarioResource(const AudSceneSoundInfo* pInfo, s32 scenarioNo) {
    
}

bool AudSceneMgr::isLoadDoneScenarioResource() {

}

void AudSceneMgr::startScene() {
    _4 = 0;
    AudWrap::getSystem()->_82A = 0;
    AudWrap::getSystem()->_82B = 0;
    AudWrap::getSystem()->_82C = 0;
    AudWrap::getSystem()->initSceneVolume();

    AudEffector* pAudEffector = AudWrap::getSystem()->mAudEffector;
    if (pAudEffector) {
        pAudEffector->initParams();
    }

    _1D = false;
    SpkSystem::reconnect(-1);
}

const AudSceneSoundInfo* AudSceneMgr::findSceneSoundInfo(const char* pSceneName, const char* pStageName) {
    const AudSceneSoundInfo* pInfo = nullptr;

    for (int i = 0; i < (int)(sizeof(::cSceneInfo) / sizeof(*::cSceneInfo)); i++) {
        pInfo = &cSceneInfo[i];

        if (strcmp(pSceneName, pInfo->mSceneName) == 0 && strcmp(pStageName, pInfo->mStageName) == 0) {
            return pInfo;
        }
    }

    if (strcmp(pSceneName, "Game") == 0) {
        return &cSceneInfo[0];
    }

    return nullptr;
}

/*
void AudSceneMgr::eraseLastBgmWaveSet() {

}

void AudSceneMgr::eraseLastSeWaveSet() {

}

void AudSceneMgr::eraseLastSeScenarioWaveSet() {

}
*/

void AudSceneMgr::loadWaveSet(const s8* pWaveSet, s32 size) {
    for (int i = 0; i < size; i++) {
        s8 id = pWaveSet[i];

        if (id >= 0) {
            mSectionHeap->loadWaveArc(id);
        }
    }
}

void AudSceneMgr::setPlayerModeMario() {
    mPlayerMode = 1;
}

void AudSceneMgr::setPlayerModeLuigi() {
    mPlayerMode = 2;
}

bool AudSceneMgr::loadPlayerResource() {
    switch (mPlayerMode) {
    case 1:
        return mSectionHeap->loadWaveArc(0x22, 2);
    case 2:
        return mSectionHeap->loadWaveArc(0x22, 4);
    default:
        return false;
    }
}

bool AudSceneMgr::isPlayerResourceLoaded() {
    switch (mPlayerMode) {
    case 1:
        return mSectionHeap->isWaveLoaded(0x22, 1);
    case 2:
        return mSectionHeap->isWaveLoaded(0x22, 2);
    default:
        return true;
    }
}
