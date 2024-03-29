#ifndef _PLAY_H
#define _PLAY_H

#define PLAY_API  __declspec(dllexport)

#define CALLMETHOD __stdcall
#define CALLBACK __stdcall

#define  FUNC_MAX_PORT 101              //max number of play channel [最大播放通道数]
//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100
//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 
//buffer type [缓冲类型]
#define BUF_VIDEO_SRC 1		//video source buffer [视频源缓冲]       
#define BUF_AUDIO_SRC 2		//audio source buffer [音频源缓冲]
#define BUF_VIDEO_RENDER 3  //video data buffer after decode [解码后视频数据缓冲]
#define BUF_AUDIO_RENDER 4  //audeo data buffer after decode [解码后音频数据缓冲]

//error type [错误类型]
#define	PLAY_NOERROR					0              //no error [没有错误；]
#define PLAY_PARA_OVER					1              //inputed param invalid [输入参数非法；]
#define PLAY_ORDER_ERROR				2              //called sequency incorrect [调用顺序不对；]
#define PLAY_TIMER_ERROR				3              //set multimedia clock fail [多媒体时钟设置失败；]
#define PLAY_DEC_VIDEO_ERROR			4	           //video decode fail [视频解码失败；]
#define PLAY_DEC_AUDIO_ERROR			5	           //audio decode fail [音频解码失败；]
#define PLAY_ALLOC_MEMORY_ERROR			6		       //alloc memory fail [分配内存失败；]
#define PLAY_OPEN_FILE_ERROR			7			   //operate file fail [文件操作失败；]
#define PLAY_CREATE_OBJ_ERROR			8	           //create thread event fail [创建线程事件等失败；]
#define PLAY_CREATE_DDRAW_ERROR			9		       //create directDraw fail [创建directDraw失败；]
#define PLAY_CREATE_OFFSCREEN_ERROR		10		       //create tail buffer fail [创建后端缓存失败；]
#define PLAY_BUF_OVER					11	           //buffer is full, and input stream fail [缓冲区满，输入流失败；]
#define PLAY_CREATE_SOUND_ERROR			12		       //create audio device fail [创建音频设备失败；]
#define PLAY_SET_VOLUME_ERROR			13	           //set audio volume fail [设置音量失败；]
#define PLAY_SUPPORT_FILE_ONLY			14		       //you can use this interface only on playing file [只能在播放文件时才能使用此接口；]
#define PLAY_SUPPORT_STREAM_ONLY		15		       //you can use this interface only on playing stream [只能在播放流时才能使用此接口；]
#define PLAY_SYS_NOT_SUPPORT			16		       //system don't support, decoder only can work on Pentium 3 or above [系统不支持，解码器只能工作在Pentium 3以上；]
#define PLAY_FILEHEADER_UNKNOWN			17		       //no file header [没有文件头；]
#define PLAY_VERSION_INCORRECT			18	           //decoder's and encoder's version don't match [解码器和编码器版本不对应；]
#define PLAY_INIT_DECODER_ERROR			19		       //initialize decoder fail [初始化解码器失败；]
#define PLAY_CHECK_FILE_ERROR			20		       //file is too short or bit-stream can't be distinguished [文件太短或码流无法识别；]
#define PLAY_INIT_TIMER_ERROR			21		       //initialize multimedia clock fail [初始化多媒体时钟失败；]
#define PLAY_BLT_ERROR					22		       //bit copy fail [位拷贝失败；]
#define PLAY_UPDATE_ERROR				23			   //show overlay fail [显示overlay失败；]


//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL  1   
#define DISPLAY_QUARTER 2	

//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 6

#define MAX_PLAYING_BUF_NUM (50)
#define MIN_PLAYING_BUF_NUM (1)
#define DEF_PLAYING_BUF_NUM (3)

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100

#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7

//system supported functions, by bits [系统支持的功能，用于按位表示系统功能]
#define SUPPORT_DDRAW		1	//support DIRECTDRAW, if not support, player can't work [支持DIRECTDRAW；如果不支持，则播放器不能工作。]
#define SUPPORT_BLT         2	//display card support BLT, if not support, player can't work [显卡支持BLT操作；如果不支持，则播放器不能工作]
#define SUPPORT_BLTFOURCC   4	//display card BLT support color transport [显卡BLT支持颜色转换；]
#define SUPPORT_BLTSHRINKX  8	//display card BLT support coordinate X zoom out [显卡BLT支持X轴缩小；]
#define SUPPORT_BLTSHRINKY  16	//display card BLT support coordinate Y zoom out [显卡BLT支持Y轴缩小；]
#define SUPPORT_BLTSTRETCHX 32	//display card BLT support coordinate X zoom in [显卡BLT支持X轴放大；]
#define SUPPORT_BLTSTRETCHY 64	//display card BLT support coordinate Y zoom in [显卡BLT支持Y轴放大；]
#define SUPPORT_SSE         128 //CPU support SSE commands, Intel Pentium3 or above support SSE commands [CPU支持SSE指令,Intel Pentium3以上支持SSE指令；]
#define SUPPORT_MMX			256 //CPU support MMX commands [CPU支持MMX指令集。]

//Frame position
typedef struct{
	long nFilePos;
	long nFrameNum;
	long nFrameTime;
	long nErrorFrameNum;
	SYSTEMTIME *pErrorTime;
	long nErrorLostFrameNum;
	long nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

//Frame Info
typedef struct{
	long nWidth;		//width of picture, unit is pixel. if it is audio, this is 0 [画面宽，单位像素。如果是音频数据则为0；]
	long nHeight;		//height of picture, unit is pixel. if it is audio, this is 0 [画面高。如果是音频数据则为0；]
	long nStamp;		//time stamp information, unit is millisecond [时标信息，单位毫秒。]
	long nType;			//data type, T_AUDIO16,T_RGB32,T_YV12 detail showed in macro definition [数据类型，T_AUDIO16，T_RGB32， T_YV12，详见宏定义说明。]
	long nFrameRate;	//picture frame rate while coding [编码时产生的图像帧率。]
}FRAME_INFO;

typedef struct 
{
	char *pDataBuf;
	long nSize;
	long nFrameNum;
	BOOL bIsAudio;
	long nReserved;
}FRAME_TYPE;

//bellow are interfaces, for customer's second development [以下为对外接口，供用户作二次开发调用]
//bellow two interfaces can be not called [以下两个是可以不需要调用的接口]
PLAY_API BOOL CALLMETHOD VN_PLAY_InitDDraw(HWND hWnd);
PLAY_API BOOL CALLMETHOD VN_PLAY_RealeseDDraw();

PLAY_API BOOL CALLMETHOD VN_PLAY_OpenFile(LONG nPort,LPSTR sFileName);
PLAY_API BOOL CALLMETHOD VN_PLAY_CloseFile(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_Play(LONG nPort, HWND hWnd);
PLAY_API BOOL CALLMETHOD VN_PLAY_Stop(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_Pause(LONG nPort,DWORD nPause);
PLAY_API BOOL CALLMETHOD VN_PLAY_Fast(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_Slow(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_OneByOne(LONG nPort);//single frame replay by network [网络回放单帧]
PLAY_API BOOL CALLMETHOD VN_PLAY_SetPlayPos(LONG nPort,float fRelativePos);
PLAY_API float CALLMETHOD VN_PLAY_GetPlayPos(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetVolume(LONG nPort,WORD nVolume);
PLAY_API BOOL CALLMETHOD VN_PLAY_StopSound();
PLAY_API BOOL CALLMETHOD VN_PLAY_PlaySound(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAY_API BOOL CALLMETHOD VN_PLAY_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAY_API BOOL CALLMETHOD VN_PLAY_CloseStream(LONG nPort);
PLAY_API int  CALLMETHOD VN_PLAY_GetCaps();
PLAY_API DWORD CALLMETHOD VN_PLAY_GetFileTime(LONG nPort);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetPlayedTime(LONG nPort);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetPlayedFrames(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_Back(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_BackOne(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDecCallBack(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,	long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2));
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDisplayCallBack(LONG nPort,void (CALLBACK* DisplayCBFun)(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved), long nUser = 0);
PLAY_API BOOL CALLMETHOD VN_PLAY_ConvertToBmpFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetFileTotalFrames(LONG nPort);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetCurrentFrameRate(LONG nPort);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetPlayedTimeEx(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetPlayedTimeEx(LONG nPort,DWORD nTime);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetCurrentFrameNum(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetStreamOpenMode(LONG nPort,DWORD nMode);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetFileHeadLength();
PLAY_API DWORD CALLMETHOD VN_PLAY_GetSdkVersion();
PLAY_API DWORD CALLMETHOD VN_PLAY_GetLastError(LONG nPort);
PLAY_API BOOL  CALLMETHOD VN_PLAY_RefreshPlay(LONG nPort);
PLAY_API BOOL  CALLMETHOD VN_PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
PLAY_API BOOL  CALLMETHOD VN_PLAY_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
PLAY_API BOOL  CALLMETHOD VN_PLAY_SetPicQuality(LONG nPort,BOOL bHighQuality);
PLAY_API BOOL  CALLMETHOD VN_PLAY_PlaySoundShare(LONG nPort);
PLAY_API BOOL  CALLMETHOD VN_PLAY_StopSoundShare(LONG nPort);
PLAY_API LONG CALLMETHOD VN_PLAY_GetStreamOpenMode(LONG nPort);
PLAY_API LONG CALLMETHOD VN_PLAY_GetOverlayMode(LONG nPort);
PLAY_API COLORREF CALLMETHOD VN_PLAY_GetColorKey(LONG nPort);
PLAY_API WORD CALLMETHOD VN_PLAY_GetVolume(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetSourceBufferRemain(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_ResetSourceBuffer(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetSourceBufCallBack(LONG nPort,DWORD nThreShold,void (CALLBACK * SourceBuf__stdcall)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered),DWORD dwUser,void *pReserved);
PLAY_API BOOL CALLMETHOD VN_PLAY_ResetSourceBufFlag(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetDisplayBuf(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_OneByOneBack(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetFileRefCallBack(LONG nPort, void (CALLBACK *pFileRefDone)(DWORD nPort,DWORD nUser),DWORD nUser);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
PLAY_API BOOL CALLMETHOD VN_PLAY_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAY_API BOOL CALLMETHOD VN_PLAY_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAY_API BOOL CALLMETHOD VN_PLAY_InitDDrawDevice();
PLAY_API void CALLMETHOD VN_PLAY_ReleaseDDrawDevice();
PLAY_API DWORD CALLMETHOD VN_PLAY_GetDDrawDeviceTotalNums();
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);

PLAY_API BOOL CALLMETHOD VN_PLAY_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,long *hhMonitor);
PLAY_API int   CALLMETHOD VN_PLAY_GetCapsEx(DWORD nDDrawDeviceNum);
PLAY_API BOOL CALLMETHOD VN_PLAY_ThrowBFrameNum(LONG nPort,DWORD nNum);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDisplayType(LONG nPort,LONG nType);
PLAY_API long CALLMETHOD VN_PLAY_GetDisplayType(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDecCBStream(LONG nPort,DWORD nStream);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
PLAY_API BOOL CALLMETHOD VN_PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);
PLAY_API BOOL CALLMETHOD VN_PLAY_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);
PLAY_API BOOL CALLMETHOD VN_PLAY_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAY_API BOOL CALLMETHOD VN_PLAY_CloseStreamEx(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAY_API BOOL CALLMETHOD VN_PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAY_API BOOL CALLMETHOD VN_PLAY_RigisterDrawFun(LONG nPort,void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);
PLAY_API BOOL CALLMETHOD VN_PLAY_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);
PLAY_API BOOL CALLMETHOD VN_PLAY_ResetBuffer(LONG nPort,DWORD nBufType);
PLAY_API DWORD CALLMETHOD VN_PLAY_GetBufferValue(LONG nPort,DWORD nBufType);

PLAY_API BOOL CALLMETHOD VN_PLAY_AdjustWaveAudio(LONG nPort,LONG nCoefficient);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, void (CALLBACK * funVerify)(long nPort, FRAME_POS * pFilePos, DWORD bIsVideo, DWORD nUser),  DWORD  nUser);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetAudioCallBack(LONG nPort, void (CALLBACK * funAudio)(long nPort, char * pAudioBuf, long nSize, long nStamp, long nType, long nUser), long nUser);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetEncTypeChangeCallBack(LONG nPort,void(CALLBACK *funEncChange)(long nPort, long nUser),long nUser);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
PLAY_API BOOL CALLMETHOD VN_PLAY_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);

PLAY_API BOOL CALLMETHOD VN_PLAY_SetMDRange(LONG nPort,RECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold) ;
PLAY_API DWORD CALLMETHOD VN_PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue) ;

PLAY_API BOOL CALLMETHOD VN_PLAY_CatchPic(LONG nPort,char* sFileName) ;

PLAY_API BOOL CALLMETHOD VN_PLAY_SetFileEndCallBack(LONG nPort, void (CALLBACK *pFileEnd)(DWORD nPort,DWORD nUser),DWORD nUser);
//data type, 0:origin stream, 1:AVI stream [dataType 0 是原始码流， 1是AVI]
PLAY_API BOOL CALLMETHOD VN_PLAY_StartDataRecord(LONG nPort, char *sFileName, int idataType=0);
PLAY_API BOOL CALLMETHOD VN_PLAY_StopDataRecord(LONG nPort);
PLAY_API BOOL CALLMETHOD VN_PLAY_AdjustFluency(LONG nPort, int level);
PLAY_API BOOL CALLMETHOD VN_PLAY_ChangeRate(LONG nPort, int rate);
PLAY_API BOOL CALLMETHOD VN_PLAY_SetDemuxCallBack(LONG nPort, void (CALLBACK* DecCBFun)(long nPort,char * pBuf,	long nSize,void * pParam, long nReserved,long nUser), long nUser);
#define HIK_CMD_GetTime 1
#define HIK_CMD_GetFileRate 2
PLAY_API BOOL CALLMETHOD VN_PLAY_QueryInfo(LONG nPort , int cmdType, char* buf, int buflen, int* returnlen);

typedef void (WINAPI *pCallFunction)(LPBYTE pDataBuffer, DWORD DataLength, long nUser);

PLAY_API BOOL CALLMETHOD VN_PLAY_OpenAudioRecord(pCallFunction pProc, long nBitsPerSample, long nSamplesPerSec, long nLength, long nReserved, long nUser);

PLAY_API BOOL CALLMETHOD VN_PLAY_CloseAudioRecord();

//reserved 0:watermark information in I frame data, 1:watermark in frame, 2:watermark verify, 3:intelligently analyze frame [reserved 0 表I帧帧数据水印信息 1 表帧水印 2 表水印校验 3表智能分析帧]
typedef int (__stdcall* GetWaterMarkInfoCallbackFunc)(char* buf, long key, long len, long reallen, long reserved, long nUser);	//get watermark information [水印信息获取函数]

PLAY_API BOOL CALLMETHOD VN_PLAY_SetWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, long nUser);

PLAY_API DWORD CALLMETHOD VN_PLAY_CreateFile(LPSTR sFileName);
PLAY_API BOOL CALLMETHOD VN_PLAY_DestroyFile(LONG nPort);
PLAY_API DWORD CALLMETHOD VN_PLAY_CreateStream(DWORD nBufPoolSize);
PLAY_API BOOL CALLMETHOD VN_PLAY_DestroyStream(LONG nPort);

PLAY_API BOOL CALLMETHOD VN_PLAY_SetPlayingBufNum(LONG nPort, int iBufNum);



#endif
