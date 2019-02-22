//
// Created by 123 on 2019/2/22.
//

#include "XShader.h"
#include "XLog.h"
#include <GLES2/gl2.h>

//顶点着色器glsl
#define GET_STR(x) #x
static const char *vertexShader = GET_STR(
        attribute vec4 aPosition; //顶点坐标
        attribute vec2 aTexCoord; //材质坐标
        varying vec2 vTexCoord; //输出的材质坐标
        void main(){
            vTexCoord = vec2(aTexCoord.x, 1.0-aTexCoord.y);
            gl_Position = aPosition;
        }
);


//片元着色器,软解码和部分x86硬解码
static const char *fragYUV420P = GET_STR(
        precision mediump float; //精度
        varying vec2 vTexCoord; //顶点着色器传递的坐标
        uniform sampler2D yTexture; //输入的材质(不透明灰度，单像素)
        uniform sampler2D uTexture;
        uniform sampler2D vTexture;
        void main(){
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(yTexture,vTexCoord).r;
            yuv.g = texture2D(uTexture,vTexCoord).r - 0.5;
            yuv.b = texture2D(vTexture,vTexCoord).r - 0.5;
            rgb = mat3(1.0,      1.0,     1.0,
                       0.0, -0.39465, 2.03211,
                       1.13983,-0.58060, 0.0)*yuv;
            //输出像素颜色
            gl_FragColor = vec4(rgb, 1.0);
        }
);

static GLuint InitShader(const char *code, GLint type)
{
    //c创建shader
    GLuint sh = glCreateShader(type);
    if(sh == 0){
        XLOGD("glCreateShader %d failed!", type);
        return 0;
    }
    //加载shader
    glShaderSource(sh,
                   1, //shader数量
                   &code, //shader代码
                   0); //代码长度
    //编译shader
    glCompileShader(sh);

    //获取编译情况
    GLint status;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
    if(status == 0)
    {
        XLOGD("GL_COMPILE_STATUS failed!");
        return 0;
    }
    XLOGD("GL_COMPILE_STATUS success!");
    return sh;
}

bool XShader::Init() {
    //顶点与片元shader初始化
    //订点shader初始化
    vsh = InitShader(vertexShader, GL_VERTEX_SHADER);
    if(vsh == 0)
    {
       XLOGE("InitShader GL_VERTEX_SHADER failed!");
       return false;
    }
    XLOGI("InitShader GL_VERTEX_SHADER success!");
    //片元yuv420 shader初始化
    fsh = InitShader(fragYUV420P, GL_FRAGMENT_SHADER);
    if(fsh == 0)
    {
        XLOGE("InitShader GL_VERTEX_SHADER failed!");
        return false;
    }
    XLOGI("InitShader GL_VERTEX_SHADER success!");

    //创建渲染程序
    program = glCreateProgram();
    if(program == 0)
    {
        XLOGD("glCreateProgram failed!");
        return false;
    }
    //渲染程序加入着色器代码
    glAttachShader(program, vsh);
    glAttachShader(program, fsh);

    //链接程序
    glLinkProgram(program);
    GLint status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        XLOGD("glGetProgramiv failed!");
        return false;
    }
    glUseProgram(program);
    XLOGD("glGetProgramiv success!");

    //加入三维顶点数据，两个三角形组成正方形
    static float vers[] = {
            1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f
    };
    GLuint apos = glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(apos);
    //传递顶点
    glVertexAttribPointer(apos, 3, GL_FLOAT, GL_FALSE, 12, vers);

    //加入材质坐标数据
    static float txts[] = {
            1.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };
    GLuint atex = glGetAttribLocation(program, "aTexCoord");
    glEnableVertexAttribArray(atex);
    glVertexAttribPointer(atex, 2, GL_FLOAT, GL_FALSE, 8, txts);

    //材质纹理初始化
    //设置纹理层
    glUniform1i(glGetUniformLocation(program, "yTexture"), 0); //对应纹理第一层
    glUniform1i(glGetUniformLocation(program, "uTexture"), 1);
    glUniform1i(glGetUniformLocation(program, "vTexture"), 2);

    XLOGI("初始化Shader成功！");


    return false;
}
