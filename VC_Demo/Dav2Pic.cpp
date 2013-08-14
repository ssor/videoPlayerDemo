#include "stdafx.h"

#define default_pic_save_path  "c:\\pics"   


char* str_PicName = NULL;
int bSavePic = 1;
void setPicName(char* name)
{
	if(str_PicName != NULL)
	{
		free(str_PicName);
		str_PicName = NULL;
	}
	int len1 = strlen(default_pic_save_path);
	int len2 = strlen(name);
	str_PicName = (char*)malloc(len1+len2+5+1);
	sprintf(str_PicName,"%s\\%s.bmp",default_pic_save_path,name);
	str_PicName[len1+len2+5] = '\0';
	//str_PicName = name;
	bSavePic = 1;
}
int  savePic()
{
	if(bSavePic == 1){
		bSavePic = 0;
		return 1;
	}else{
	return 0;
	}
}
char* getPicName()
{

	//str_PicName = "../Pic/cap_temp.bmp";
	//str_PicName = "c:\\cap_temp.bmp";
	//str_PicName = "c:\\cap_temp.jpg";
	
	if(str_PicName == NULL){
		return "c:\\cap_temp.bmp";
	}
	else{
		return str_PicName;
	}
}
void GetPicFromDav(char* fileName)
{
	/*
	StuPicData m_picData;
	m_picData.nCapacity = 720*576*3/2;
	m_picData.buf = (char*)malloc(m_picData.nCapacity);
	m_picData.isHasData = 0;

    if(nSize <= dlg->m_picData.nCapacity)
	{
		dlg->m_picData.nSize = nSize;
		dlg->m_picData.nWidth = nWidth;
		dlg->m_picData.nHeight = nHeight;
		dlg->m_picData.nType = nType;
		memcpy(dlg->m_picData.buf,pBuf,nSize);
		dlg->m_picData.isHasData = 1;
	}

	VN_PLAY_OpenFile(m_lPort, fileName);
    GetPic(m_picData.buf,m_picData.nSize,m_picData.nWidth,m_picData.nHeight,m_picData.nType);

	char* sFilePath = "C:\\capture%02d.bmp";
	char* sFilePath = "C:\\capture%02d.jpeg";

	BOOL ret=	VN_PLAY_ConvertToBmpFile(pImage,nBufSize,nWidth,nHeight,nType,sFilePath.GetBuffer(0));
	*/
  }