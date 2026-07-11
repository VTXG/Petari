#include "Game/Screen/CustomTagProcessor.hpp"
#include "Game/System/Language.hpp"
#include "nw4r/ut/TextWriterBase.h"
#include "revolution/gx/GXStruct.h"
#include "revolution/types.h"

namespace {
    const GXColor cTextColor[] = {
        {0xFF, 0xFF, 0xFF, 0xFF},
        {0xDC, 0x82, 0x82, 0xFF},
        {0x50, 0xAA, 0x50, 0xFF},
        {0x50, 0x8C, 0xD2, 0xFF},
        {0xEB, 0xC8, 0x00, 0xFF},
        {0xB4, 0x6E, 0xC8, 0xFF},
        {0xFF, 0xBE, 0xBE, 0xFF},
        {0x6E, 0xF3, 0x46, 0xFF},
        {0x78, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0x50, 0xFF},
        {0xFB, 0xBC, 0xFA, 0xFF},
        {0xBE, 0xBE, 0xC8, 0xFF},
    };

    const GXColor cTextColorKor[] = {
        {0xFF, 0xFF, 0xFF, 0xFF},
        {0xE6, 0xA0, 0x00, 0xFF},
        {0x50, 0xAA, 0x50, 0xFF},
        {0x50, 0x8C, 0xD2, 0xFF},
        {0xEB, 0xC8, 0x00, 0xFF},
        {0xB4, 0x6E, 0xC8, 0xFF},
        {0xFF, 0xD2, 0x50, 0xFF},
        {0x6E, 0xF3, 0x46, 0xFF},
        {0x78, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0x50, 0xFF},
        {0xFB, 0xBC, 0xFA, 0xFF},
        {0xBE, 0xBE, 0xC8, 0xFF},
    };

    const GXColor* getTextColor(s32 id) {
        const GXColor* pColor;

        if (MR::getLanguage() == LANGUAGE_KRKOREAN) {
            pColor = &cTextColorKor[id];
        }
        else {
            pColor = &cTextColor[id];
        }

        return pColor;
    }

    u8 clampU8(s32 val) {
        u32 ret;

        if (val < 0) {
            ret = 0;
        }
        else {
            ret = 0xFF;

            if (val <= 0xFF) {
                ret = val;
            }
        }

        return ret;
    }

    GXColor setGXColor(GXColorS10 col) {
        GXColor ret;
        ret.r = clampU8(col.r);
        ret.g = clampU8(col.g);
        ret.b = clampU8(col.b);
        ret.a = clampU8(col.a);
        return ret;
    }

    void setTextColor(nw4r::ut::TextWriterBase<wchar_t>* pTextWriter, s32 id) {

    }
};  // namespace

CustomTagAlphaCtrl::CustomTagAlphaCtrl() : _0(), _4(), _8(), _1C(), _20() {
    _C = 0;
    _14 = 0;
    _10 = 0;
    _18 = false;
}

void CustomTagAlphaCtrl::init(u32 a1, f32 a2, f32 a3, s32 a4, s32 a5) {
    if (a2 == 0.0f) {
        _18 = false;
        return;
    }

    _18 = true;
    _8 = -a4;
    _C = 0;
    _1C = a3;
    _20 = a2;
    _14 = a1;
    _10 = 0;
    _0 = a4;
    _4 = a5;
}

u8 CustomTagAlphaCtrl::alpha() const {
    if (_18) {
        f32 v = _20 * (_10 - _8) - _C * _1C;
        f32 ret;

        if (v <= 0.0f) {
            ret = 0.0f;
        }
        else if (v >= 1.0f) {
            ret = 1.0f;
        }
        else {
            ret = v;
        }

        return ret * 255.0f;
    }
    
    return 0xFF;
}

void CustomTagAlphaCtrl::update() {

}

bool CustomTagAlphaCtrl::isEnd() const {

}

CustomTagProcessor::CustomTagProcessor(nw4r::lyt::TextBox*) {
    
}
