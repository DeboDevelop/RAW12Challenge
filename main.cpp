#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

// Enough for one line of the input image
const int BUFFERSIZE = 4096 * 3;

int main(){

    ifstream infile;
    ofstream redfile;
    ofstream greenfile1;
    ofstream greenfile2;
    ofstream bluefile;

    infile.open("portrait.raw12", ios::binary | ios::in);
    redfile.open("Red Channel.pgm", ios::binary);
    greenfile1.open("Green Channel1.pgm", ios::binary);
    greenfile2.open("Green Channel2.pgm", ios::binary);
    bluefile.open("Blue Channel.pgm", ios::binary);

    // Write single channel PGM file
    redfile << "P5\n2048 1536\n255\n";
    greenfile1 << "P5\n2048 1536\n255\n";
    greenfile2 << "P5\n2048 1536\n255\n";
    bluefile << "P5\n2048 1536\n255\n";
    //To store input
    unsigned char * bufferRow = new unsigned char[BUFFERSIZE];

    if(!infile)
    {
        cout<<"Failed to open"<<endl;
        return 0;
    }
    int size=2048*1536;
    //Array to store the R,G,G,B Channels
    unsigned char * RedChannel=new unsigned char[size];
    unsigned char * GreenChannel_1=new unsigned char[size];
    unsigned char * GreenChannel_2=new unsigned char[size];
    unsigned char * BlueChannel=new unsigned char[size];
    //pointers of the array declared above.
    unsigned char * Redp = RedChannel;
    unsigned char * Greenp_1=GreenChannel_1;
    unsigned char * Greenp_2=GreenChannel_2;
    unsigned char * Bluep=BlueChannel;
    //useful for printing
    int pixel=1;
    int temp=0;

    for(int rowNum=0;rowNum<1536;rowNum++)
    {
        // Read an entire row
        infile.read(reinterpret_cast<char*>(bufferRow), BUFFERSIZE);
        if(rowNum%2==0)
        {
            for(int i=0;i<BUFFERSIZE;i+=3)
            {
                *Redp++=bufferRow[i];
                *Greenp_1++=((uint8_t)(bufferRow[i+1] & 0x0F) << 4) | ((uint8_t)(bufferRow[i+2] >> 4) & 0x0F);
                if(pixel<=3 && rowNum<5)
                {
                    temp=(uint8_t)bufferRow[i];
                    cout<<"RedChannel: "<<temp<<endl;
                    if(pixel!=3)
                        temp=((uint8_t)(bufferRow[i+1] & 0x0F) << 4) | ((uint8_t)(bufferRow[i+2] >> 4) & 0x0F);
                        cout<<"GreenChannel 1: "<<temp<<endl;
                }
                pixel++;
            }
        }
        else
        {
            for(int i=0;i<BUFFERSIZE;i+=3)
            {
                *Greenp_2++=bufferRow[i];
                *Bluep++=((uint8_t)(bufferRow[i+1] & 0x0F) << 4) | ((uint8_t)(bufferRow[i+2] >> 4) & 0x0F);

                if(pixel<=3 && rowNum<5)
                {
                    temp=(uint8_t)bufferRow[i];
                    cout<<"GreenChannel 2: "<<temp<<endl;
                    if(pixel!=3)
                        temp=(((uint8_t)bufferRow[i+1] & 0x0F) << 4) | ((uint8_t)(bufferRow[i+2] >> 4) & 0x0F);
                        cout<<"BlueChannel 1: "<<temp<<endl;
                }
                pixel++;
            }
        }
        pixel=1;
        if(rowNum<5)
            cout<<" "<<endl;
    }
    infile.close();
    redfile.write(reinterpret_cast<char*>(RedChannel), size);
    greenfile1.write(reinterpret_cast<char*>(GreenChannel_1), size);
    greenfile2.write(reinterpret_cast<char*>(GreenChannel_2), size);
    bluefile.write(reinterpret_cast<char*>(BlueChannel), size);
    redfile.close();
    greenfile1.close();
    greenfile2.close();
    bluefile.close();
}