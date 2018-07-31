
#include "encodeanddecode.h"



    bool EncodeAndDecode::Encode(string& msg, vector<BYTE>& data){


        int length = 0;
        bool isComplete = false;

        if(msg.size()*8 <= data.size()){
            length = (msg.size()) ;
            isComplete = true;

        }
        else{
            length = (data.size()-(data.size()%8))/8;
            isComplete = false;

        }

        for(int j = 0; j < length; j++){
            // HideOneByte(msg[(i*length)+j],data,j);

            HideOneByte(msg[j],data,j);
        }
        msg = msg.substr(length);

        return isComplete;
        // @TODO: Maybe use try-catch and also throw error and other advanced stuff and also make this
        //function int-type
    }
    //FOR ENCODING INTEGER
    bool EncodeAndDecode::Encode(int& msg, vector<BYTE>& data){


        int temp = 0;

        for(int k=0;k<32;k++){
            //Hiding
            temp = msg & HIDEINTBIT; //HIDEINTBIT helps to get 1st bit of a and store it in temp
            temp >>= 31;


            data[k] = data[k] - (BYTE)((data[k])%2); //Making LSB of data 0
            data[k] = data[k] | temp;


            msg <<= 1;


        }


        return true;
    }
    void EncodeAndDecode::HideOneByte(BYTE a,vector<BYTE>& data, int j){
        BYTE temp = 0;

        for(int k=0;k<NO_OF_BIT;k++){
            //Hiding
            temp = a&HIDEBIT; //HIDEBIT helps to get 1st bit of a and store it in temp
            temp >>= 7;


            data[(j*NO_OF_BIT)+k] = data[(j*NO_OF_BIT)+k] - (BYTE)((data[(j*NO_OF_BIT)+k])%2); //Making LSB of data 0
            data[(j*NO_OF_BIT)+k] = data[(j*NO_OF_BIT)+k] | temp;


            a <<= 1;


        }

    }

    string EncodeAndDecode::Decode(vector<BYTE>& data,int& length, bool& isComplete){
        int tempLength = 0;
        string tempString = "";



        if((unsigned int)length > data.size()/8){
            tempLength = ((data.size()-(data.size()%8))/8);
            length -= (tempLength);
            isComplete = false;
        }
        else{
            tempLength = length;
            isComplete = true;
        }

        for(int j=0;j<(tempLength);j++){
            BYTE temp = ExtractOneByte(data,j);
            tempString += temp;
        }

        return tempString;
        

    }
    //FOR DECODING INTEGER
    int EncodeAndDecode::Decode(vector<BYTE>& data,bool& isComplete){


        int temp = 0;
        int num = 0;
        for(int k=0;k<32;k++){
            num <<= 1;
            temp = data[k] & EXTRACTBIT;
            num = num | temp;
        }
        isComplete = true;
        return num;
        // @TODO: Maybe use try-catch and also throw error and other advanced stuff and also make this
        //function int-type
    }

    BYTE EncodeAndDecode::ExtractOneByte(vector<BYTE>& data,int j){
        BYTE temp,  character = (char)0;
        for(int k=0;k<NO_OF_BIT;k++){
            //Extracting
            character <<= 1;
            temp = data[(j*NO_OF_BIT)+k] & EXTRACTBIT; //EXTRACTBIT helps to get last bit of data and store it in temp
            character = character | temp;
        }

        return (BYTE)character;
    }




