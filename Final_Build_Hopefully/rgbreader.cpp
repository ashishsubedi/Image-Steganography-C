#include "rgbreader.h"

vector<BYTE> RGBReader::data =  vector<BYTE>();
vector<BYTE> RGBReader::pad = vector<BYTE>();
EncodeAndDecode Encode;



//FOR ENCODE
    void RGBReader::GetPixels(long h,long w,long offset, FILE * fp,FILE *fq,string msg,string key,bool & success){

        string encChecksum = Encrypt::EncryptDecryptMsg(checksum,key);
        string Initial = STEG + encChecksum;
        string encMsg = Encrypt::EncryptDecryptMsg(msg,key);

        int noOfPad;

        noOfPad = 4 - ((w*3)%4);
        data.resize(w*3);

        pad.resize(noOfPad);


        BYTE c=0;//Used For padding

        //Go to the offset position
        fseek(fp,offset,SEEK_SET);

        msgLength = msg.size();

        if(msg.size()*NO_OF_BIT > ((data.size()*h)-((Initial.length() + 4)* NO_OF_BIT))){
            cout<<"Message too long"<<endl;
            success = false;
            return;
        }

        //For ENCODE

        //To know if encoding message is complete or not
        bool isComplete= false;
        //To know if encoding header is complete or not
        bool isCompleteCheck = false;

        //To know if encoding header inital is complete or not
        bool check1 = false;

        for(int i = 0; i < h; i++)
        {
            fread(&data[0], sizeof(BYTE), data.size(), fp);

            if(!isCompleteCheck){


                if(!check1 ){
                    //ENCODE HEADER
                    //make check1 true if complete
                    check1 = Encode.Encode(Initial,data);
                    fwrite(&data[0],sizeof(BYTE),data.size(),fq);

                }else if(check1 ){
                    //ENCODE length
                    isCompleteCheck = Encode.Encode(msgLength,data);
                    fwrite(&data[0],sizeof(BYTE),data.size(),fq);
                }

            }
            else{

                if(!isComplete)
                    isComplete = Encode.Encode(encMsg,data);   // if msg is more than h, cannot fit, so
                                                            //making sure that it is less

                fwrite(&data[0],sizeof(BYTE),data.size(),fq);

                data.clear();

                data.resize(w*3);


            }
            AddPad(noOfPad,fp,fq);

        }
        success = true;

    }
//FOR DECODE
    void RGBReader::GetPixels(long h, long w, long offset, FILE * fp, string key,bool &success){
        int noOfPad = 4 - ((w*3)%4);

        bool ISCOMPLETECHECK = false;
        bool isComplete = false;


        bool check1 = false;
        bool allConditionMeet = false;

        data.resize(w*3);


        pad.resize(noOfPad);
        string value = "";
        string encMsg = "";
        string msg = "";
        int _length = 12;

        BYTE c=0;

        fseek(fp,offset,SEEK_SET);


        for(int i=0;i<h;i++){
            fread(&data[0],sizeof(BYTE),data.size(),fp);

            if(!ISCOMPLETECHECK){
                if(!check1){
                    string temp =Encode.Decode(data,_length,check1);
                    value += temp;
                }else{
                    msgLength = Encode.Decode(data,ISCOMPLETECHECK);
                }
            }
            else{
                if(STEG == value.substr(0,STEG.size())){
                    if(!allConditionMeet){
                        string _value = value.substr(4,checksum.size());
                        string _value_ = Encrypt::EncryptDecryptMsg(_value, key);
                        if(checksum == _value_){
                            allConditionMeet = true;
                        }else{
                            //PASSWORD INCORRECT
                            cout<<"PASSWORD INCORRECT"<<endl;
                            success = false;
                            return;
                        }
                    }

                }
                else{
                    //NOT STEG IMAGE
                    cout<<"NOT AN STEG IMAGE"<<endl;
                    success = false;
                    return;
                }
            }
            if(allConditionMeet){
                    if(!isComplete){
                        encMsg += Encode.Decode(data, msgLength, isComplete);
                    }
                    else break;
            }
            data.clear();
            data.resize(w*3);

            GetPad(noOfPad,fp);

        }
        msg = Encrypt::EncryptDecryptMsg(encMsg, key);
        cout << "Your message is: \n" << msg << endl;
        success = true;

    }
    void RGBReader::AddPad(int noOfPad, FILE *fp, FILE *fq){
        for(int j=0;j<noOfPad;j++)
            {
            //  pad[(i*h)+j] = getc(fp);
                BYTE c = getc(fp);
                fwrite(&c,sizeof(BYTE),1,fq);
            }
    }
    void RGBReader::GetPad(int noOfPad,FILE *fp){
        for(int j=0; j<noOfPad; j++)
            BYTE c=getc(fp);
    }
    void RGBReader::ReadHeader( BitMap & Header,FILE* fp){
        fread(&Header.Type, sizeof Header.Type, 1, fp);
        fread(&Header.Size, sizeof Header.Size, 1, fp);
        fread(&Header.Reserve1, sizeof Header.Reserve1, 1, fp);
        fread(&Header.Reserve2, sizeof Header.Reserve2, 1, fp);
        fread(&Header.OffBits, sizeof Header.OffBits, 1, fp);
        fread(&Header.biSize, sizeof Header.biSize, 1, fp);
        fread(&Header.biWidth, sizeof Header.biWidth, 1, fp);
        fread(&Header.biHeight, sizeof Header.biHeight, 1, fp);
        fread(&Header.biPlanes, sizeof Header.biPlanes, 1, fp);
        fread(&Header.biBitCount, sizeof Header.biBitCount, 1, fp);
        fread(&Header.biCompression, sizeof Header.biCompression, 1, fp);
        fread(&Header.biSizeImage, sizeof Header.biSizeImage, 1, fp);
        fread(&Header.biXPelsPerMeter, sizeof Header.biXPelsPerMeter, 1, fp);
        fread(&Header.biYPelsPerMeter, sizeof Header.biYPelsPerMeter, 1, fp);
        fread(&Header.biClrUsed, sizeof Header.biClrUsed, 1, fp);
        fread(&Header.biClrImportant, sizeof Header.biClrImportant, 1, fp);
    }

/*     void RGBReader::PrintHeader( BitMap & Header){

        printf("%d\n",Header.Type);
        printf("%ld\n",Header.Size);
        printf("%ld\n",Header.Reserve1);
        printf("%ld\n",Header.Reserve2);
        printf("%ld\n",Header.OffBits);
        printf("%ld\n",Header.biSize);
        printf("%ld\n",Header.biWidth);
        printf("%ld\n",Header.biHeight);
        printf("%ld\n",Header.biPlanes);
        printf("%ld\n",Header.biBitCount);
        printf("%ld\n",Header.biCompression);
        printf("%ld\n",Header.biSizeImage);
        printf("%ld\n",Header.biXPelsPerMeter);
        printf("%ld\n",Header.biYPelsPerMeter);
        printf("%ld\n",Header.biClrUsed);
        printf("%ld\n",Header.biClrImportant);
    } */
void RGBReader::WriteFileHeader( BitMap & Header, FILE* fq){
        fwrite(&Header.Type,sizeof Header.Type,1,fq);
        fwrite(&Header.Size,sizeof Header.Size,1,fq);
        fwrite(&Header.Reserve1,sizeof Header.Reserve1,1,fq);
        fwrite(&Header.Reserve2,sizeof Header.Reserve2,1,fq);
        fwrite(&Header.OffBits,sizeof Header.OffBits,1,fq);
        fwrite(&Header.biSize,sizeof Header.biSize,1,fq);
        fwrite(&Header.biWidth,sizeof Header.biWidth,1,fq);
        fwrite(&Header.biHeight,sizeof Header.biHeight,1,fq);
        fwrite(&Header.biPlanes,sizeof Header.biPlanes,1,fq);
        fwrite(&Header.biBitCount,sizeof Header.biBitCount,1,fq);
        fwrite(&Header.biCompression,sizeof Header.biCompression,1,fq);
        fwrite(&Header.biSizeImage,sizeof Header.biSizeImage,1,fq);
        fwrite(&Header.biXPelsPerMeter,sizeof Header.biXPelsPerMeter,1,fq);
        fwrite(&Header.biYPelsPerMeter,sizeof Header.biYPelsPerMeter,1,fq);
        fwrite(&Header.biClrUsed,sizeof Header.biClrUsed,1,fq);
        fwrite(&Header.biClrImportant,sizeof Header.biClrImportant,1,fq);
    }




