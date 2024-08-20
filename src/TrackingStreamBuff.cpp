#include "TrackingStreamBuf.h"

TrackingStreamBuf::TrackingStreamBuf(streambuf* originalBuffer)
    : originalBuffer(originalBuffer), hasWritten(false) {}

bool TrackingStreamBuf::hasWrittenToCerr() const {
    return hasWritten;
}

int TrackingStreamBuf::sync() {
    return originalBuffer->pubsync();
}

int TrackingStreamBuf::overflow(int c) {
    if (c != EOF) {
        hasWritten = true;  
        originalBuffer->sputc(c);  
    }
    return c;
}
