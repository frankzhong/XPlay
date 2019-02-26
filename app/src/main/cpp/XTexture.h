//
// Created by 123 on 2019/2/22.
//

#ifndef XPLAY_XTEXTURE_H
#define XPLAY_XTEXTURE_H

enum XTextureType
{
    XTEXTURE_YUV420P = 0, // Y 4   U 1   V1
    XTEXTURE_NV12 = 25,  //Y4  UV1
    XTEXTURE_NV21 = 26  //Y4   VU1
};

class XTexture {

public:
    static XTexture *Create();
    virtual bool Init(void *win, XTextureType type = XTEXTURE_YUV420P) = 0;
    virtual void Draw(unsigned char *data[], int width, int height) = 0;
};


#endif //XPLAY_XTEXTURE_H
