#include<iostream>
#include<unistd.h>
#include<wiringPi.h>
#include<iomanip>

using namespace std;

#define Using_DHT11 true
#define DHT_GPIO 22
#define LH_THRESHOLD 28 //26-28 -> low 

int main() {
    int humid, temp;
    wiringPiSetup();
    piHiPri(99);
    LOOP:
        char data[5] = {};

        //sends a start signal for DHT11
        pinMode(DHT_GPIO,OUTPUT);
        digitalWrite(DHT_GPIO, LOW);
        usleep(18000);
        digitalWrite(DHT_GPIO, HIGH);
        usleep(40000);
        pinMode(DHT_GPIO, INPUT);
        do { delayMicroseconds(1); } while(digitalRead(DHT_GPIO)==HIGH);
        do { delayMicroseconds(1); } while(digitalRead(DHT_GPIO)==LOW);
        do { delayMicroseconds(1); } while(digitalRead(DHT_GPIO)==HIGH);

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                do { delayMicroseconds(1);} while (digitalRead(DHT_GPIO) == LOW);
                int width = 0;
                do {
                    width++;
                    delayMicroseconds(1);
                    if (width > 1000) break;
                } while(digitalRead(DHT_GPIO) == HIGH);
                data[i] = data[i] | ((width > LH_THRESHOLD) << (7 - i));
            }
        }
        if (Using_DHT11){
            humid = data[0] * 10;
            temp = data[2] * 10;
        }
        else //DHT22 MSB-LSB
        {
            humid = (data[0]<<8 | data[1]); 
            temp = (data[2]<<8 | data[3]);
        }
        unsigned char check = 0; 
        for(int i = 0; i < 4; i++){ 
            check += data[i]; 
        }
        if(check == data[4]){
            cout << "The temperature is " << (float)temp/10 << "°C" << endl;
            cout << "The humidity is " << (float)humid/10 << "%" << endl;
        }
        else 
        {
            cout <<"CheckSum bad !!!"<<endl;
            usleep(1000000);
            goto LOOP;
        }
    return 0;
}