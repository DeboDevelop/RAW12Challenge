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
    unsigned int RedChannel,GreenChannel_1,GreenChannel_2,BlueChannel;
    int rowNum=0;
    int i=0;
    int pixel=1;
    while(rowNum<3072)
    {
        infile.read(reinterpret_cast<char*>(bufferRow), BUFFERSIZE);
        if(rowNum%2==0)
        {
            //RedChannel = buf[0]<<4 | (buf[1] & 0xF0)>>4;
            //GreenChannel = (buf[1] & 0x0F)<<8 | buf[2];
            while(i<BUFFERSIZE)
            {
                RedChannel=(uint8_t)bufferRow[i];
                GreenChannel_1=((uint8_t)(bufferRow[i+1] & 0x0F) << 4) | ((uint8_t)(bufferRow[i+2] >> 4) & 0x0F);
                i+=3;
                if(pixel<=3 && rowNum<5)
                {
                    cout<<"RedChannel: "<<RedChannel<<endl;
                    if(pixel!=3)
                        cout<<"GreenChannel 1: "<<GreenChannel_1<<endl;
                }
                pixel++;

            }

        
        }
        else
        {
            //GreenChannel = buf[0]<<4 | (buf[1] & 0xF0)>>4;
            //BlueChannel = (buf[1] & 0x0F)<<8 | buf[2];
            while(i<BUFFERSIZE)
            {
                GreenChannel_2=(uint8_t)bufferRow[i];
                BlueChannel=((uint8_t)(bufferRow[i+1] & 0x0F) << 4) | ((uint8_t)(bufferRow[i+2] >> 4) & 0x0F);
                i+=3;
                if(pixel<=3 && rowNum<5)
                {
                    cout<<"GreenChannel 2: "<<GreenChannel_2<<endl;
                    if(pixel!=3)
                        cout<<"BlueChannel: "<<BlueChannel<<endl;
                }
                pixel++;
            }
        }
        rowNum++;
        i=0;
        pixel=1;
        if(rowNum<5)
            cout<<" "<<endl;
    }
    infile.close();
}
    
