#include <fstream>
#include <iostream>
using namespace std;
 
const int BUFFERSIZE = 4096;

int main () 
{
    ifstream infile;
    infile.open("portrait.raw12", ios::binary | ios::in);
    //char buf[3];
    //char RedChannel,GreenChannel,BlueChannel;
    uint8_t * bufferRow = new uint8_t[BUFFERSIZE];

    if(!infile)
    {
        cout<<"Failed to open"<<endl;
    }
    unsigned char buf[3];
    unsigned int RedChannel,GreenChannel_1,GreenChannel_2,BlueChannel;
    int count=0;
    int i=0;
    while(count<3072)
    {
        infile.read(reinterpret_cast<char*>(bufferRow), BUFFERSIZE);
        if(count%2==0)
        {
            //RedChannel = buf[0]<<4 | (buf[1] & 0xF0)>>4;
            //GreenChannel = (buf[1] & 0x0F)<<8 | buf[2];
            while(i<BUFFERSIZE)
            {
                RedChannel=(uint8_t)buf[i];
                GreenChannel_1=((uint8_t)(buf[i+1] & 0x0f) << 4) | ((uint8_t)(buf[i+2] >> 4) & 0x0f);
                i+=3;
                cout<<"RedChannel: "<<RedChannel<<endl;
                cout<<"GreenChannel 1: "<<GreenChannel_1<<endl;
            }

        
        }
        else
        {
            //GreenChannel = buf[0]<<4 | (buf[1] & 0xF0)>>4;
            //BlueChannel = (buf[1] & 0x0F)<<8 | buf[2];
            while(i<BUFFERSIZE)
            {
                GreenChannel_2=(uint8_t)buf[0];
                BlueChannel=((uint8_t)(buf[1] & 0x0f) << 4) | ((uint8_t)(buf[2] >> 4) & 0x0f);
                i+=3;
                cout<<"GreenChannel 2: "<<GreenChannel_2<<endl;
                cout<<"BlueChannel: "<<BlueChannel<<endl;
            }
        }
        count++;
        i=0;
    }
    infile.close();
}
    
