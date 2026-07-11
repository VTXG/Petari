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

CustomTagProcessor::CustomTagProcessor(nw4r::lyt::TextBox*) {
    
}
