#include "Game/Screen/LayoutManager.hpp"
#include "Game/Screen/LayoutCoreUtil.hpp"
#include "Game/System/LayoutHolder.hpp"
#include "Game/Util/FileUtil.hpp"
#include "Game/Util/LayoutUtil.hpp"
#include "Game/Util/MemoryUtil.hpp"
#include "Game/Util/MessageUtil.hpp"
#include "Game/Util/StringUtil.hpp"
#include "nw4r/lyt/layout.h"
#include "nw4r/lyt/pane.h"
#include "nw4r/lyt/textBox.h"
#include "nw4r/math/types.h"
#include "nw4r/ut/LinkList.h"
#include "revolution/mtx.h"
#include "revolution/types.h"
#include <cstdio>
#include <cstring>

namespace {
    const char* cRemoveString[] = {
        "4x3",
        "16x9",
        "Replace",
    };
}  // namespace

LayoutManager::LayoutManager(const char* pFileName, bool isFullPath, u32 ar6, u32 textBoxAllocSize)
    : mLayoutHolder(), mLayout(), mAnimTransList(nullptr), mDrawInfo(), mIsScreenHidden(), _61(true), _64(), mPaneCount(), mPaneInfo(), _70(), _74(),
      mLayoutName() {
    if (isFullPath) {
        char filePathNoExtension[0x60];
        char filePath[0x80];

        MR::makeLayoutArchiveFileNameFromPrefix(filePath, sizeof(filePath), pFileName, true);
        MR::removeExtensionString(filePathNoExtension, sizeof(filePathNoExtension), filePath);
        pFileName = MR::getBasename(filePathNoExtension);
    }

    char archiveName[0x40];
    snprintf(archiveName, sizeof(archiveName), "%s.arc", pFileName);

    char layoutName[0x40];
    MR::copyString(layoutName, pFileName, sizeof(layoutName));

    for (int i = 0; i < sizeof(::cRemoveString) / sizeof(*::cRemoveString); i++) {
        char* pRemoveString = strstr(layoutName, ::cRemoveString[i]);

        if (pRemoveString) {
            pRemoveString[0] = '\0';
            break;
        }
    }

    int len = strlen(layoutName) + 1;
    char* pLayoutName = new char[len];
    mLayoutName = pLayoutName;
    MR::copyString(pLayoutName, layoutName, len);

    initArc(archiveName, pFileName);
    initPaneInfo();
    initGroupCtrlList();
    initDrawInfo();
    initTextBoxRecursive(mLayout->mpRootPane, nullptr, mLayoutName, textBoxAllocSize);
    replaceIndDummyTexture();

    if (ar6 != 0) {
        createAndAddRootPaneCtrl(ar6);
    }

    mLayout->Animate(0);
    mLayout->CalculateMtx(mDrawInfo);
}

// ! regswap
void LayoutManager::initArc(const char* pArchiveName, const char* pFileName) {
    mLayoutHolder = MR::createAndAddLayoutHolder(pArchiveName);

    char layoutFileName[0x80];
    snprintf(layoutFileName, sizeof(layoutFileName), "%s.brlyt", pFileName);

    void* pLayoutData = mLayoutHolder->GetResource('blyt', layoutFileName, nullptr);
    mLayout = new nw4r::lyt::Layout();
    mLayout->Build(pLayoutData, mLayoutHolder);

    if (mLayoutHolder->mAnimRes.mCount != 0) {
        mAnimTransList = new nw4r::lyt::AnimTransform*[mLayoutHolder->mAnimRes.mCount];

        for (int i = 0; i < mLayoutHolder->mAnimRes.mCount; i++) {
            mAnimTransList[i] = mLayout->CreateAnimTransform(mLayoutHolder->mAnimRes.getRes(i), mLayoutHolder);
        }
    }

    removeUnnecessaryPanes(mLayout->mpRootPane);
}

void LayoutManager::initDrawInfo() {
    nw4r::math::MTX34 mtx;
    PSMTXIdentity(mtx);
    mDrawInfo.mViewMtx = mtx;
    mDrawInfo.mFlag.mulViewDraw = true;
    mDrawInfo.mViewRect = mLayout->GetLayoutRect();
    mDrawInfo.mFlag.locationAdjust = true;
}

void LayoutManager::initPaneInfo() {
    mPaneCount = countPanes(mLayout->mpRootPane);
    mPaneInfo = new PaneInfo[mPaneCount];

    u32 a1 = 0;
    initPaneInfoRecursive(a1, mLayout->mpRootPane);
}

void LayoutManager::initPaneInfoRecursive(u32& index, nw4r::lyt::Pane* pRootPane) {
    mPaneInfo[index].mName = pRootPane->mName;
    mPaneInfo[index]._4 = 0;
    mPaneInfo[index]._8 = 0;
    mPaneInfo[index]._C = 0;
    mPaneInfo[index].mPane = pRootPane;
    u32 tmp = index++;

    nw4r::lyt::PaneList* pList = pRootPane->GetChildList();
    for (nw4r::lyt::PaneList::Iterator it = pList->GetBeginIter(); it != pList->GetEndIter(); ++it) {
        initPaneInfoRecursive(index, &*it);
    }

    mPaneInfo[tmp]._10 = index - tmp;
}

u32 LayoutManager::countPanes(nw4r::lyt::Pane* pRootPane) {
    u32 count = 1;

    nw4r::lyt::PaneList* pList = pRootPane->GetChildList();
    for (nw4r::lyt::PaneList::Iterator it = pList->GetBeginIter(); it != pList->GetEndIter(); ++it) {
        count += countPanes(&*it);
    }

    return count;
}

void LayoutManager::initGroupCtrlList() {
}

void LayoutManager::initTextBoxRecursive(nw4r::lyt::Pane* pRootPane, nw4r::lyt::Pane* a2, const char* pLayoutName, u32 allocSize) {
    nw4r::lyt::TextBox* pTextBoxPane;

    // inlined DynamicCast<PCQ34nw4r3lyt7TextBox,CQ34nw4r3lyt4Pane>__Q24nw4r2utFPCQ34nw4r3lyt4Pane_PCQ34nw4r3lyt7TextBox?
    if (pRootPane != nullptr && pRootPane->GetRuntimeTypeInfo()->IsDerivedFrom(&nw4r::lyt::TextBox::typeInfo)) {
        pTextBoxPane = reinterpret_cast< nw4r::lyt::TextBox* >(pRootPane);
    } else {
        pTextBoxPane = nullptr;
    }

    char userData[9];
    LayoutCoreUtil::getPaneUserData(pRootPane, userData);
    if (!MR::isEqualString(userData, "")) {
        a2 = pRootPane;
    }

    if (pTextBoxPane) {
        if (a2) {
            LayoutCoreUtil::getPaneUserData(pRootPane, userData);
            char messageID[0x100];
            MR::getLayoutMessageID(messageID, pLayoutName, userData);
            LayoutCoreUtil::initTextBoxPane(pTextBoxPane, messageID, sizeof(messageID));
        } else {
            LayoutCoreUtil::initTextBoxPane(pTextBoxPane, nullptr, allocSize);
        }
    }

    nw4r::lyt::PaneList* pList = pRootPane->GetChildList();
    for (nw4r::lyt::PaneList::Iterator it = pList->GetBeginIter(); it != pList->GetEndIter(); ++it) {
        initTextBoxRecursive(&*it, a2, pLayoutName, allocSize);
    }
}

/* ????????????
void LayoutManager::replaceIndDummyTexture() {
    void* pIndDummy = mLayoutHolder->getResOther("IndDummy.tpl");
    if (pIndDummy == nullptr) {
        return;
    }

    JUTTexture texture;
    texture.mEmbPalette = nullptr;
    texture.storeTIMG(MR::getScreenResTIMG(), static_cast< u8 >(0));
    texture.setCaptureFlag(true);
}

void LayoutManager::removeUnnecessaryPanes(nw4r::lyt::Pane* pRootPane) {

}
*/
