#include <fstream>
#include <iostream>
using namespace std;
 
int main () 
{
    ifstream infile;
    infile.open("portrait.raw12", ios::binary | ios::in);
    //char buf[3];
    //char RedChannel,GreenChannel,BlueChannel;
    
    if(!infile)
    {
        cout<<"Failed to open"<<endl;
    }
    unsigned char buf[3];
    unsigned int RedChannel,GreenChannel,BlueChannel;
    int count=0;
    while(count<4096)
    {
    infile.read(reinterpret_cast<char*>(buf), 3);
    if(count%2==0)
    {
        //RedChannel = buf[0]<<4 | (buf[1] & 0xF0)>>4;
        //GreenChannel = (buf[1] & 0x0F)<<8 | buf[2];
        RedChannel=(uint8_t)buf[0];
        GreenChannel=((uint8_t)(buf[1] & 0xf) << 4) | ((uint8_t)(buf[2] >> 4) & 0xf);

        cout<<"RedChannel: "<<RedChannel<<endl;
        cout<<"GreenChannel: "<<GreenChannel<<endl;
    }
    else
    {
        //GreenChannel = buf[0]<<4 | (buf[1] & 0xF0)>>4;
        //BlueChannel = (buf[1] & 0x0F)<<8 | buf[2];
        GreenChannel=(uint8_t)buf[0];
        BlueChannel=((uint8_t)(buf[1] & 0xf) << 4) | ((uint8_t)(buf[2] >> 4) & 0xf);
        cout<<"GreenChannel: "<<GreenChannel<<endl;
        cout<<"BlueChannel: "<<BlueChannel<<endl;
    }
    count++;
    }
    infile.close();
}
    
