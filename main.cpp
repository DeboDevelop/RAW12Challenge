#include <fstream>
#include <iostream>
using namespace std;
 
const int BUFFERSIZE = 4096;

struct Collect
{
    char r,g,b;
};

int main () 
{
    ifstream infile;
    infile.open("portrait.raw12", ios::binary | ios::in);
    ofstream outfile;
    outfile.open("Redtwo.ppm", ios::binary);
    /*
    outfile.write("P6 ", 3);
    outfile.write("1536 2048 ", 8);
    outfile.write("2048 ", 4);
    outfile.write("255 ", 4);
    */
    //outfile << "P6\n" << 1536 << "\n" << 2048 << "\n255\n";
    outfile << "P6"     << "\n"
        << 1536  << " "
        << 2048  << "\n"
        << 255   << "\n"
       ;
    uint8_t * bufferRow = new uint8_t[BUFFERSIZE];

    if(!infile)
    {
        cout<<"Failed to open"<<endl;
    }
    int size=1536*2048*3;
    char * RedChannel=new char[size];
    int GreenChannel_1,GreenChannel_2,BlueChannel;
    int rowNum=0;
    int i=0;
    int j=0;
    int pixel=1;
    while(rowNum<3072)
    {
        infile.read(reinterpret_cast<char*>(bufferRow), BUFFERSIZE);
        if(rowNum%2==0)
        {
            while(i<BUFFERSIZE)
            {
                RedChannel[j]=(uint8_t)bufferRow[i];
                GreenChannel_1=((uint8_t)(bufferRow[i+1] & 0x0F) << 4) | ((uint8_t)(bufferRow[i+2] >> 4) & 0x0F);
                i+=3;
                Collect s;
                //s.r=(char)RedChannel[j];
                //s.g=(char)0;
                //s.b=(char)0;
                //unsigned char c = (unsigned char)(255.0f * (float)RedChannel[j] + 0.5f); 
                //outfile.write((char*) &c, 3);
                //outfile.write((char*) 255, sizeof(c));
                //outfile.write(reinterpret_cast<char*>(&RedChannel), 4);
                if(pixel<=3 && rowNum<5)
                {
                    cout<<"RedChannel: "<<RedChannel[j]<<endl;
                    if(pixel!=3)
                        cout<<"GreenChannel 1: "<<GreenChannel_1<<endl;
                }
                pixel++;
                j++;

            }
            RedChannel[j]='\n';
            j++;
        
        }
        else
        {
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
    outfile.write(RedChannel, size);
    outfile.close();
}
    
