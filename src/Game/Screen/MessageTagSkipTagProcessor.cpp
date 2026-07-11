#include "Game/Screen/MessageTagSkipTagProcessor.hpp"

MessageTagSkipTagProcessor::MessageTagSkipTagProcessor() : nw4r::ut::TagProcessorBase< wchar_t >() {
}

nw4r::ut::TagProcessorBase< wchar_t >::Operation MessageTagSkipTagProcessor::CalcRect(nw4r::ut::Rect* pRect, u16 code, ContextType* pPrintContext) {
    if (code != 0x1A) {
        return nw4r::ut::TagProcessorBase< wchar_t >::CalcRect(pRect, code, pPrintContext);
    } else {
        return skipTag(pRect, pPrintContext, false);
    }
}

nw4r::ut::TagProcessorBase< wchar_t >::Operation MessageTagSkipTagProcessor::Process(u16 code, ContextType* pPrintContext) {
    if (code != 0x1A) {
        return nw4r::ut::TagProcessorBase< wchar_t >::Process(code, pPrintContext);
    } else {
        return skipTag(nullptr, pPrintContext, false);
    }
}

nw4r::ut::TagProcessorBase<wchar_t>::Operation MessageTagSkipTagProcessor::skipTag(nw4r::ut::Rect* pRect, ContextType* pPrintContext, bool a3) {
    pPrintContext->str += (pPrintContext->getTagHeader()->size - 2u) >> 1;
    return OPERATION_DEFAULT;
}

MessageEditorMessageTag::MessageEditorMessageTag(const nw4r::ut::PrintContext<wchar_t>* pPrintContext) : mMessage(pPrintContext->str) {

}

MessageEditorMessageTag::MessageEditorMessageTag(const wchar_t* pMessage) : mMessage(pMessage) {

}

u32 MessageEditorMessageTag::getTagLength() const {
    return mTagHeader->size - 2u;
}

u32 MessageEditorMessageTag::getSkipLength() const {
    return (mTagHeader->size - 2u) >> 1;
}

u32 MessageEditorMessageTag::getParamLength() const {
    return mTagHeader->size - 6u;
}

u8 MessageEditorMessageTag::getParam8(int idx) const {
    return *(reinterpret_cast<const u8*>(mMessage + 2u) + idx);
}

u16 MessageEditorMessageTag::getParam16(int idx) const {
    return *(reinterpret_cast<const u16*>(mMessage + 2u) + idx);
}

u32 MessageEditorMessageTag::getParam32(int idx) const {
    return *(reinterpret_cast<const u32*>(mMessage + 2u) + idx);
}

const wchar_t* MessageEditorMessageTag::getParamPtr(int idx) const {
    return reinterpret_cast<const wchar_t *>((reinterpret_cast<const u8*>(mMessage + 2u) + idx));
}
