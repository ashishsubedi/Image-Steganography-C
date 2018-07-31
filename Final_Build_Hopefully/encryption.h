#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include<string>

using namespace std;

static const string KEY = "a1233";
class Encrypt{
    private:
    static string encMsg;
    static string msg;
    static string encKey;
    public:
    static string EncryptDecryptMsg
    (string msg,string key);
    static string GetEncryptedMsg();
    static void SetMsg(string _m);

    private:
    static string encryptDecrypt(string msg, string key);
};









#endif // ENCRYPTION_H
