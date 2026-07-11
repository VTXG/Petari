#pragma once

#include "Game/Screen/MessageTagSkipTagProcessor.hpp"
#include "nw4r/ut/TagProcessorBase.h"
#include "revolution/gx/GXStruct.h"
#include <nw4r/lyt/textBox.h>

class CustomTagAlphaCtrl {
public:
    CustomTagAlphaCtrl();

    void init(u32, f32, f32, s32, s32);
    u8 alpha() const;
    void update();
    bool isEnd() const;

    /* 0x00 */ u32 _0;
    /* 0x04 */ u32 _4;
    /* 0x08 */ u32 _8;
    /* 0x0C */ u32 _C;
    /* 0x10 */ u32 _10;
    /* 0x10 */ u32 _14;
    /* 0x18 */ bool _18;
    /* 0x1C */ f32 _1C;
    /* 0x20 */ f32 _20;
};

class CustomTagProcessor : public MessageTagSkipTagProcessor {
public:
    CustomTagProcessor(nw4r::lyt::TextBox*);

    virtual nw4r::ut::TagProcessorBase< wchar_t >::Operation Process(u16, nw4r::ut::PrintContext< wchar_t >*);
    virtual nw4r::ut::TagProcessorBase< wchar_t >::Operation CalcRect(nw4r::ut::Rect*, u16, nw4r::ut::PrintContext< wchar_t >*);

    /* 0x04 */ CustomTagAlphaCtrl mAlphaCtrl;
    /* 0x28 */ u8 pad[0x28];
    /* 0x*/
};
