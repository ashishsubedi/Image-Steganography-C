#ifndef RGBREADER_H
#define RGBREADER_H


#include<stdio.h>
#include<stdlib.h>

#include"common.h"
#include"encodeanddecode.h"
#include"encryption.h"



class RGBReader{
   
    const string STEG ="STEG";
    string checksum = "PASSWORD";
    int msgLength;

public:

    static vector<BYTE> data;
    static vector<BYTE> pad;

//FOR ENCODE
    void GetPixels(long h,long w,long offset,FILE * fp,FILE *fq,string msg,string key,bool& success);
//FOR DECODE
    void GetPixels(long h, long w, long offset, FILE * fp,string key,bool& success);
    void AddPad(int noOfPad, FILE *fp, FILE *fq);

    void GetPad(int noOfPad,FILE *fp);
    void ReadHeader(BitMap& , FILE* fp);
  //  void PrintHeader(BitMap &);
    void WriteFileHeader(BitMap & , FILE* fq);

};

//extern BitMap Header;
//extern BitMapV5 HeaderV5;






#endif // RGBREADER_H
