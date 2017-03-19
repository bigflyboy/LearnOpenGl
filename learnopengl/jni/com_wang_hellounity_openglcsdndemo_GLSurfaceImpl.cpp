#include"com_wang_hellounity_openglcsdndemo_GLSurfaceImpl.h"

JNIEXPORT void JNICALL Java_com_wang_hellounity_openglcsdndemo_GLSurfaceImpl_initAsset
  (JNIEnv *env, jobject obj,jobject asset_manager){
    sAssetManager = AAssetManager_fromJava(env,asset_manager);
}

/*
 * Class:     com_wang_hellounity_openglcsdndemo_GLSurfaceImpl
 * Method:    onSurfaceCreated
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_wang_hellounity_openglcsdndemo_GLSurfaceImpl_onSurfaceCreated
(JNIEnv * env, jobject obj){
    glClearColor(0.1f,0.4f,0.7f,1.0f);

    float vertices[] = {
        0.0f,0.0f,-10.0f,0.0f,0.0f,
        1.0f,-1.0f,-10.0f,0.0f,0.0f,
        -1.0f,1.0f,-10.0f,1.0f,0.0f,

        1.0f,-1.0f,-10.0f,1.0f,1.0f,
        -1.0f,1.0f,-10.0f,1.0f,0.0f,
        1.0f,1.0f,-10.0f,0.0f,1.0f
    };

    simple_program = CreateProgram("vsCode.vs","fsCode.fs");

    positionLocation = glGetAttribLocation(simple_program,"position");
    texcoordLocation = glGetAttribLocation(simple_program,"texcoord");
    mainTextureLocation = glGetAttribLocation(simple_program,"U_MainTexture");

    MLocation = glGetUniformLocation(simple_program,"M");
    VLocation = glGetUniformLocation(simple_program,"V");
    PLocation = glGetUniformLocation(simple_program,"P");

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*30,vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    unsigned int indexes[]={0,1,2,3,4,5};

    glGenBuffers(1,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned char)*6,indexes,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    //init Texture
    char* bmpData=LoadFileContent("test.bmp");
    int width=0,height=0;
    unsigned char*imageData=DecodeBMP(bmpData,width,height);
//    createTexture-2D
    mainTexture=CreateTextureWithBMPData(imageData,width,height);
    delete bmpData;
//    mainTexture = CreateTexture(256);
}

/*
 * Class:     com_wang_hellounity_openglcsdndemo_GLSurfaceImpl
 * Method:    onSurfaceChanged
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_wang_hellounity_openglcsdndemo_GLSurfaceImpl_onSurfaceChanged
  (JNIEnv * env, jobject obj, jint width, jint height){
    glViewport(0,0,width,height);
    projectionMatrix = glm::perspective(50.0f,(float)width/height,0.1f,1000.0f);


}

/*
 * Class:     com_wang_hellounity_openglcsdndemo_GLSurfaceImpl
 * Method:    onDrawFrame
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_wang_hellounity_openglcsdndemo_GLSurfaceImpl_onDrawFrame
(JNIEnv * env, jobject obj){
    glClear(GL_COLOR_BUFFER_BIT);

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(simple_program);

    //update gpu program args
    glUniformMatrix4fv(MLocation,1,GL_FALSE,glm::value_ptr(identityMatrix));
    glUniformMatrix4fv(VLocation,1,GL_FALSE,glm::value_ptr(identityMatrix));
    glUniformMatrix4fv(PLocation,1,GL_FALSE,glm::value_ptr(projectionMatrix));

    glBindTexture(GL_TEXTURE_2D,mainTexture);
    glUniform1i(mainTextureLocation,0);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);

    //set vertex data
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,0);
    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(sizeof(float)*3));

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //draw
    glDrawArrays(GL_POINTS,0,1);
    glUseProgram(0);
    glFlush();
}

GLuint CompileShader(GLenum shaderType,const char* code){
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader,1,&code,nullptr);
    glCompileShader(shader);
    //check error
    GLint compileResult = 0;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compileResult);
    if(compileResult == GL_FALSE){
        info("compile shader error with code : %s",code);
        char szLogBuffer[1024];
        GLsizei realLogLen = 0;
        glGetShaderInfoLog(shader,1024,&realLogLen,szLogBuffer);
        info("%s",szLogBuffer);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint CreateProgram(const char* vsPath,const char* fsPath){
    char* vsCode = LoadFileContent(vsPath);
    char* fsCode = LoadFileContent(fsPath);
    if(vsCode == nullptr || fsCode == nullptr){
        info("load file failes");
        return 0;
    }
    GLuint program = glCreateProgram();
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER,vsCode);
    if(vsCode == 0){
        info("compile vs shader fail");
        return 0;
    }
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER,fsCode);
    if(fsCode == 0){
        info("compile fs shader fail");
        return 0;
    }

    glAttachShader(program,vsShader);
    glAttachShader(program,fsShader);

    glLinkProgram(program);

    glDetachShader(program,vsShader);
    glDetachShader(program,fsShader);

    glDeleteShader(vsShader);
    glDeleteShader(fsShader);

    GLint linkResult = 0;
    glGetProgramiv(program,GL_LINK_STATUS,&linkResult);
    if(linkResult == GL_FALSE){
        info("compile link error with code ");
        char szLogBuffer[1024];
        GLsizei realLogLen = 0;
        glGetShaderInfoLog(program,1024,&realLogLen,szLogBuffer);
        info("%s",szLogBuffer);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

char * LoadFileContent(const char *path){
    char *fileContent=nullptr;
    AAsset *asset=AAssetManager_open(sAssetManager,path,AASSET_MODE_UNKNOWN);
    if(asset == nullptr){
        info("load file failed");
        return nullptr;
    }
    size_t fileLen =AAsset_getLength(asset);
    fileContent = new char[fileLen+1];
    AAsset_read(asset,fileContent,fileLen);
    fileContent[fileLen]='\0';
    AAsset_close(asset);
    return fileContent;
}

GLuint CreateTextureWithBMPData(unsigned char *imageData,int width,int height){
    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,imageData);
    glBindTexture(GL_TEXTURE_2D,0);
    return texture;
}

unsigned char* DecodeBMP(char* bmpData,int&width,int&height){
    if(0x42==*((unsigned char*)bmpData)){
        unsigned long imageDataOffSet=*((unsigned int*)(bmpData+10));
        width = *((unsigned int*)(bmpData+18));
        height = *((unsigned int*)(bmpData+22));
        unsigned char *imageData = (unsigned char*)(bmpData+imageDataOffSet);
        info("decode bitmap imageDataSize %d,width %d,heigth %d",imageDataOffSet,width,height);
        for(int i=0;i<width*height*3;i+=3){
            //bgr->rgb
            unsigned char temp = imageData[i+2];
            imageData[i+2]=imageData[i];
            imageData[i]=temp;
        }
        return imageData;
    }else{
        info("load bitmap failed");
        return nullptr;
    }
}

GLuint CreateTexture(int size){
    unsigned char*imageData = new unsigned char[size*size];
    int maxDistance = size;
    float centerX = (float)size/2.0f;
    float centerY = (float)size/2.0f;
    for(int y=0;y<size;y++){
        for(int x=0;x<size;x++){
            float distance = sqrtf((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY));
            float alpha = powf((maxDistance-distance)/maxDistance,8.0f);
            alpha = alpha>1.0f?1.0f:alpha;
            imageData[x+y*size] = (unsigned char)(alpha*255.0f);
        }
    }
    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_ALPHA,size,size,0,GL_ALPHA,GL_UNSIGNED_BYTE,imageData);
    glBindTexture(GL_TEXTURE_2D,0);
    return texture;
}
