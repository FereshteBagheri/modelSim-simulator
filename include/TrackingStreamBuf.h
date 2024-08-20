#ifndef TRACKINGSTREAMBUF_H
#define TRACKINGSTREAMBUF_H

#include <streambuf>

using namespace std;

class TrackingStreamBuf : public streambuf {
public:
    TrackingStreamBuf(streambuf* originalBuffer);

    bool hasWrittenToCerr() const;

protected:    
    int sync() override;
    int overflow(int c) override;

private:
    streambuf* originalBuffer;  
    bool hasWritten;  
};

#endif 
