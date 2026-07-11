#pragma once

#include <revolution.h>
#include "nw4r/ut/Rect.h"

namespace nw4r {
    namespace ut {
        template <typename CharType>
        class TextWriterBase;

        struct TagHeader {
            /* 0x00 */ u8 size;
            /* 0x01 */ u8 type;
        };

        template<typename CharType>
        struct PrintContext {
            TextWriterBase<CharType>* writer;
            const CharType* str;
            const f32 xOrigin;
            const f32 yOrigin;
            u32 flags;

            const inline TagHeader* getTagHeader() const {
                return reinterpret_cast<const TagHeader*>(str);
            }
        };

        template<typename CharT>
        class TagProcessorBase {
        public:
            typedef CharT CharType;
            typedef PrintContext<CharType>  ContextType;

            enum Operation {
                OPERATION_DEFAULT,
                OPERATION_NO_CHAR_SPACE,
                OPERATION_CHAR_SPACE,
                OPERATION_NEXT_LINE,
                OPERATION_END_DRAW,
                NUM_OF_OPERATION
            };

            TagProcessorBase();
        
            virtual ~TagProcessorBase();
            virtual Operation Process(u16, ContextType *);
            virtual Operation CalcRect(Rect *, u16, ContextType *);

            void ProcessLinefeed(ContextType *);
            void ProcessTab(ContextType *);
        };
    };
};
