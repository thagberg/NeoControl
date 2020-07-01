// #include <Adafruit_NeoMatrix.h>
// #include <gamma.h>

// struct Color
// {
//     int r;
//     int g;
//     int b;
// };

// enum Error
// {
//     OK,
//     InvalidColor
// };

// const int R_PIN = 9;
// const int G_PIN = 10;
// const int B_PIN = 11;
// const char kPacketTerminator = '>';
// const size_t kSerialBufferSize = 64;

// Color currentColor = {255, 0, 0};

// bool  gPacketComplete = false;

// uint8_t serialBuffer[kSerialBufferSize];
// char writeBackBuffer[kSerialBufferSize];
// size_t gWriteIndex;

// void setup()
// {
//     Serial.begin(9600);

//     memset(serialBuffer, '\0', kSerialBufferSize);
//     memset(writeBackBuffer, '\0', kSerialBufferSize);

//     gWriteIndex = 0;

//     pinMode(R_PIN, OUTPUT);
//     pinMode(G_PIN, OUTPUT);
//     pinMode(B_PIN, OUTPUT);
// }

// void loop()
// {
//     char readData;
//     while (Serial.available() && !gPacketComplete)
//     {
//         readData = Serial.read();
//         if (readData != kPacketTerminator)
//         {
//             serialBuffer[gWriteIndex++] = readData;
//             if (gWriteIndex >= kSerialBufferSize)
//             {
//                 gWriteIndex = 0;
//             }
//         }
//         else
//         {
//             gPacketComplete = true;
//         }
//     }

//     if (gPacketComplete)
//     {
//         gPacketComplete = false;

//         char colorChoice;
//         uint8_t colorValue;
//         for (size_t i = 0; i < gWriteIndex-1; i+=2)
//         {
//             colorChoice = serialBuffer[i];
//             colorValue = serialBuffer[i+1];
//             switch(colorChoice)
//             {
//                 case 'R':
//                 {
//                     currentColor.r = colorValue;
//                     break;
//                 }
//                 case 'G':
//                 {
//                     currentColor.g = colorValue;
//                     break;
//                 }
//                 case 'B':
//                 {
//                     currentColor.b = colorValue;
//                     break;
//                 }
//             }
//         }

//         Serial.println("New Colors:");
//         Serial.print("\tR: ");
//         Serial.println(currentColor.r);
//         Serial.print("\tG: ");
//         Serial.println(currentColor.g);
//         Serial.print("\tB: ");
//         Serial.println(currentColor.b);

//         gWriteIndex = 0;
//         memset(serialBuffer, 0, kSerialBufferSize);
//     }

//     analogWrite(R_PIN, currentColor.r);
//     analogWrite(G_PIN, currentColor.g);
//     analogWrite(B_PIN, currentColor.b);

//     delay(16);
// }