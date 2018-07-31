#include"rgbreader.h"

#include<limits>

using namespace std;

typedef unsigned char BYTE;


int main()
{
    //BitMap Header;
    FILE * fp;
    FILE * fq;
    struct BitMap Header;

    string fileAddress;
    string fileName;
    string key;
    string msg;

    vector<BYTE> data();
    vector<BYTE> pad();

    RGBReader rgbReader;

    int mode;
    bool success = true;

    //For filename copy
    int posIndex;
    system("color 03");
    cout<<"\t\t\t\t\tWelcome to Image Steganography."<<endl;
    cout<<"You can choose to either hide message in new image or decode the message from Stego Image\n"<<endl;
    cout<<"Enter the file address of image you want to encode or decode: "<<endl;
    cin>>fileAddress;

    //sizeof(FileAddress);

    fp = fopen(fileAddress.c_str(),"rb");//FileAddress.c_str is used to convert string to char*

    if(fp==NULL){
        printf("File Not Found. The program will now exit.\n");
        system("Pause");
        return 0;
    }

    posIndex = fileAddress.rfind("\\");
    if(posIndex == string::npos){
        fileName = fileAddress;
    }else{
        fileName = fileAddress.substr(posIndex);
    }


    rgbReader.ReadHeader(Header,fp);
    long h=Header.biHeight;
    long w=Header.biWidth;
    long o=Header.OffBits;

    cout<<"Enter 0 or 1 to either Encode or Decode\n0. Encode\n1. Decode "<<endl;
    cin>>mode;
    if(mode == Mode::e){

        fileName = "Steg_"+fileName;
        fq = fopen(fileName.c_str(),"wb");
        rgbReader.WriteFileHeader(Header,fq);


        cout<<"Enter the message you want to hide"<<endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,msg);


        cout<<"Enter the encryption key"<<endl;
        getline(cin,key);

        rgbReader.GetPixels(h,w,o,fp,fq,msg,key,success);
        if(success)
            cout<<"The message has been successfully encoded. New file called \""<<fileName<<"\" has been created in same folder as this application."<<endl;

    }else if(mode == Mode::d){
        cout<<"Enter the encryption key"<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,key);
        //Encrypt public key

        rgbReader.GetPixels(h,w,o,fp,key,success);


    }
    if(!success){

        if(posIndex != string::npos){

            remove ((fileAddress.substr(0,posIndex)+fileName).c_str());

        }
        else{
            fclose(fq);
            remove(fileName.c_str());
        }
    }

    system("Pause");


    fclose(fp);
    if(success)
        fclose(fq);

    return 0;

}


