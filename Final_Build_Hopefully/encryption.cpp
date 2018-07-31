#include "encryption.h"

string Encrypt::encMsg = "";
string Encrypt::msg = "";
string Encrypt::encKey = "";

    string Encrypt::EncryptDecryptMsg(string msg,string key){
        encMsg = msg;
        encKey = key;
        encKey = encryptDecrypt(key,KEY);

        encMsg = encryptDecrypt(msg,encKey);

        return encMsg;
    }
    string Encrypt::GetEncryptedMsg(){

        if(!encMsg.empty())
            return encMsg;
        return msg;
    }
    void Encrypt::SetMsg(string _m){

        msg = _m;
    }


    string Encrypt::encryptDecrypt(string msg, string key){
        string s = msg;
        int key_len = key.size(),i;

        for(i=0;i<msg.size();i++){
            s[i] = msg[i] ^ key[i% key_len];
        }
        return s;
    }







