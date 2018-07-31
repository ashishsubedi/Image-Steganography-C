#ifndef ENCODEANDDECODE_H
#define ENCODEANDDECODE_H

#include<iostream>
#include<vector>
#include<string>

#define NO_OF_BIT 8

using namespace std;

typedef unsigned char BYTE;

class EncodeAndDecode{
    const BYTE HIDEBIT = 128;
    const BYTE EXTRACTBIT = 1;

    const unsigned int HIDEINTBIT = 2147483648;


public:

    bool Encode(string& msg, vector<BYTE>& data);
    bool Encode(int& msg, vector<BYTE>& data);//FOR Encoding INTEGER
    void HideOneByte(BYTE a,vector<BYTE>& data, int j);

    string Decode(vector<BYTE>& data,int& length, bool& isComplete);
    int Decode(vector<BYTE>& data,bool& isComplete);//FOR DECODING INTEGER

    BYTE ExtractOneByte(vector<BYTE>& data,int j);
};
extern EncodeAndDecode Encode;
#endif // ENCODEANDDECODE_H
