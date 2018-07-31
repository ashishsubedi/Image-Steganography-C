#ifndef COMMON_H_
#define COMMON_H_


extern "C"{
    struct BitMap {
        short Type;
        long Size;
        short Reserve1;
        short Reserve2;
        long OffBits;
        long biSize;
        long biWidth;
        long biHeight;
        short biPlanes;
        short biBitCount;
        long biCompression;
        long biSizeImage;
        long biXPelsPerMeter;
        long biYPelsPerMeter;
        long biClrUsed;
        long biClrImportant;
    };
    extern struct BitMap Header;
    enum Mode{e, d};
}



#endif
