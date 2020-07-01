// #include <HardwareSerial.h>

namespace hvk
{
    const char kPacketTerminator = '>';
    const size_t kSerialBufferSize = 256;

    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    struct Packet
    {
       Color colors[256]; 
       uint8_t width;
       uint8_t height;
    };

    class Host
    {
    public:
        Host(uint8_t width, uint8_t height);
        bool checkForPacket(Packet& packet);
    private:
        uint8_t mWidth;
        uint8_t mHeight;
        uint8_t mSerialBuffer[kSerialBufferSize];
        size_t mWriteIndex;
        bool mPacketComplete;
    };

    Host::Host(uint8_t width, uint8_t height)
        : mWidth(width)
        , mHeight(height)
        , mWriteIndex(0)
        , mPacketComplete(false)
    {
        Serial.begin(9600);
        memset(mSerialBuffer, '\0', kSerialBufferSize);
    }

    bool Host::checkForPacket(Packet& packet)
    {
        char readData;
        while (Serial.available() && !mPacketComplete)
        {
            readData = Serial.read();
            if (readData != kPacketTerminator)
            {
                mSerialBuffer[mWriteIndex++] = readData;
                if (mWriteIndex >= kSerialBufferSize)
                {
                    mWriteIndex = 0;
                }
            }
            else
            {
                mPacketComplete = true;
            }
            
        }

        if (mPacketComplete)
        {
            mPacketComplete = false;

            packet.width = mWidth;
            packet.height = mHeight;

            // Serial.println("Data Received:");
            // Serial.println(mWriteIndex);

            size_t bufferIndex = 0;
            size_t colorIndex = 0;
            while (mSerialBuffer[bufferIndex+2] != '\0')
            {
                Color pixelColor = {
                    mSerialBuffer[bufferIndex],
                    mSerialBuffer[bufferIndex+1],
                    mSerialBuffer[bufferIndex+2]
                };
                packet.colors[colorIndex++] = pixelColor;
                bufferIndex += 3;
            }

            memset(mSerialBuffer, 0, kSerialBufferSize);
            mWriteIndex = 0;

            // Serial.println("Updated Colors");
            if (colorIndex == 0)
            {
                // Serial.println("No LEDs updated");
            }
            for (size_t i = 0; i < colorIndex; ++i)
            {
                // Serial.print("LED: ");
                // Serial.print("\t");
                // Serial.print(colorIndex);
                // Serial.print(": ");
                // Serial.print(packet.colors[colorIndex].r);
                // Serial.print(", ");
                // Serial.print(packet.colors[colorIndex].g);
                // Serial.print(", ");
                // Serial.print(packet.colors[colorIndex].b);
                // Serial.println("\n");
            }

            return true;
        }

        return false;
    }
}