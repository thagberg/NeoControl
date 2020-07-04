
namespace hvk
{
    const char kPacketTerminator = '>';
    const size_t kSerialBufferSize = 120;

    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    struct Packet
    {
        Color* colors;
        uint8_t width;
        uint8_t height;
    };

    class Host
    {
    public:
        Host(uint8_t width, uint8_t height);
        bool checkForPacket(Packet& packet);
        bool acknowledgePacket(uint8_t pixelsUpdated);
    private:
        uint8_t mWidth;
        uint8_t mHeight;
        uint8_t mSerialBuffer[kSerialBufferSize];
        size_t mWriteIndex;
        bool mPacketComplete;
        bool mReady;
    };

    Host::Host(uint8_t width, uint8_t height)
        : mWidth(width)
        , mHeight(height)
        , mWriteIndex(0)
        , mPacketComplete(false)
        , mReady(false)
    {
        Serial.begin(9600);
        memset(mSerialBuffer, 0, kSerialBufferSize);
    }

    bool Host::checkForPacket(Packet& packet)
    {
        int bytesAvailable = Serial.available();
        if (bytesAvailable > 0)
        {
            int bytesToRead = min(bytesAvailable, kSerialBufferSize - mWriteIndex);
            size_t bytesRead = Serial.readBytes(mSerialBuffer + mWriteIndex, bytesToRead);
            mWriteIndex += bytesToRead;

            if (mWriteIndex >= kSerialBufferSize)
            {
                packet.colors = reinterpret_cast<Color*>(mSerialBuffer);
                packet.width = mWidth;
                packet.height = mHeight;
                mWriteIndex = 0;
                return true;
            }
        }

        return false;
    }

    bool Host::acknowledgePacket(uint8_t pixelsUpdated)
    {
        // Serial.write(pixelsUpdated);
        // Serial.flush();
    }
}