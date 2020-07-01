#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "libraries/hostControl.h"

const int kPin = 6;
const uint8_t kMatrixLayout = NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS;
const neoPixelType kLedType = NEO_GRB + NEO_KHZ800;
const uint8_t kBrightness = 40;
const uint8_t kWidth = 8;
const uint8_t kHeight = 5;

Adafruit_NeoMatrix gMatrix = Adafruit_NeoMatrix(8, 5, kPin, kMatrixLayout, kLedType);

uint8_t x, y;

hvk::Host* gHost;
hvk::Packet gPacket;

void setup()
{
    gMatrix.begin();
    gMatrix.setBrightness(40);
    x = y = 0;

    gHost = new hvk::Host(kWidth, kHeight);
    gMatrix.fillScreen(0);
}

void loop()
{

    bool packetComplete = gHost->checkForPacket(gPacket);
    if (packetComplete)
    {
        // gMatrix.fillScreen(0);
        for (size_t i = 0; i < gPacket.height; ++i)
        {
            for (size_t j = 0; j < gPacket.width; ++j)
            {
                hvk::Color pixelColor = gPacket.colors[i * gPacket.width + j];
                gMatrix.drawPixel(j, i, gMatrix.Color(pixelColor.r, pixelColor.g, pixelColor.b));
            }
        }
        memset(gPacket.colors, 0, 256);
    }

    // gMatrix.drawPixel(x, y, gMatrix.Color(255, 0, 0));
    // x++;
    // if (x >= 5)
    // {
    //     x = 0;
    //     y++;
    //     if (y >= 8)
    //     {
    //         y = 0;
    //     }
    // }

    gMatrix.show();
    delay(16);
}