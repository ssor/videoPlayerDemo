/////////////////////////////////////////////////////////////////////////////////////
// PlayerDlg.h : header file
/////////////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_PLAYERDLG_H__BC7E7078_7E67_40B3_85A4_591E51BB1A4A__INCLUDED_)
#define AFX_PLAYERDLG_H__BC7E7078_7E67_40B3_85A4_591E51BB1A4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XColorStatic.h"
#include "XScrollBar.h"
#include "VolumeCtrl.h"
#include "seek.h"
#include "displayRect.h"
#include "VideoCtrlDlg.h"
#include "WatermarkDlg.h"


//文件头标
// 海康格式封装
#define HKM4_FILE_CODE		0x484B4D34	// "HKM4" 海康文件层，M卡老版本非标准MPEG4
#define HKH4_FILE_CODE		0x484B4834	// "HKH4" 海康H.264
#define HSM4_FILE_CODE		0x48534D34	// "HSM4" 海康系统层，标准MPEG4

// MPEG2-PS
#define PSM4_FILE_CODE		0x50534D34	// "PSM4" PS系统层，标准MPEG4
#define PSH4_FILE_CODE		0x50534834	// "PSH4" PS系统层，标准H264

// MPEG2-TS
#define TSM4_FILE_CODE		0x54534D34	// "PSM4" TS系统层，标准MPEG4
#define TSH4_FILE_CODE		0x54534834	// "PSH4" TS系统层，标准H264

// RTP
#define RTM4_FILE_CODE		0x52544D34	// "RTM4" RTP封装标准MPEG4
#define RTH4_FILE_CODE		0x52544834	// "RTH4" RTP封装标准H264

// 系统封装格式	
#define SYSTEM_NULL			0x0				// 没有系统层，纯音频流或视频流	
#define SYSTEM_HIK          0x1				//add 20071218
#define SYSTEM_MPEG2_PS     0x2				//add 20071218
#define SYSTEM_MPEG2_TS     0x3				//add 20071218
#define SYSTEM_RTP          0x4				//add 20071218

// 视频编码类型
#define VIDEO_NULL          0x0 // 没有视频
#define VIDEO_H264          0x1 // 标准H.264和海康H.264都可以用这个定义
#define VIDEO_MPEG4         0x3 // 标准MPEG4

// 音频编码类型
#define AUDIO_NULL          0x0000 // 没有音频
#define AUDIO_ADPCM         0x1000 // ADPCM 
#define AUDIO_MPEG          0x2000 // MPEG 系列音频，解码器能自适应各种MPEG音频
// G系列音频
#define AUDIO_G711_U		0x7110
#define AUDIO_G711_A		0x7111
#define AUDIO_G722_1		0x7221
#define AUDIO_G723_1        0x7231
#define AUDIO_G726          0x7260
#define AUDIO_G729          0x7290

#ifndef HIK_RTP_STREAM_TYPE_DEFINITION
#define HIK_RTP_STREAM_TYPE_DEFINITION

//RTP 负载类型，与TS/PS解析系统定义相同
/* 输入流类型声明 */
#define HIK_STD_STREAM_TYPE_RTP_NULL    0x00    /* 没有RTP流      */
#define HIK_STD_STREAM_TYPE_RTP_STM     0x91    /* 未定义的其他流 */
#define HIK_STD_STREAM_TYPE_RTP_G711    0x71    /* G711 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G722    0x72    /* G722 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G723    0x73    /* G723 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G726    0x76    /* G726 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G727    0x77    /* G727 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G728    0x78    /* G728 音频流    */
#define HIK_STD_STREAM_TYPE_RTP_G729    0x79    /* G729 音频流    */

#define HIK_STD_STREAM_TYPE_RTP_M1V     0x01    /* mpeg1 视频流   */
#define HIK_STD_STREAM_TYPE_RTP_M2V     0x02    /* mpeg2 视频流   */
#define HIK_STD_STREAM_TYPE_RTP_M1A     0x03    /* mpeg1 音频流   */
#define HIK_STD_STREAM_TYPE_RTP_M2A     0x04    /* mpeg2 音频流   */
#define HIK_STD_STREAM_TYPE_RTP_M4V     0x10    /* MPEG4视频流    */
#define HIK_STD_STREAM_TYPE_RTP_264     0x1b    /* H.264视频流	  */

#endif

#define HIK_STD_STREAM_TYPE_MPG2_TS		7    	/* TS流           */
#define HIK_STD_STREAM_TYPE_MPG2_PS     8       /* PS流           */

enum _VIDEO_PLAY_STATE 
{ 
	State_Close  = 0,
	State_Play   = 1,
	State_Pause  = 2,
	State_Stop   = 3,
	State_Step   = 4
};


typedef struct tagPicData
{
	char* buf;
	int nSize;
	int nWidth;
	int nHeight;
	int nType;
	int isHasData;
	int nCapacity;
}StuPicData;
/////////////////////////////////////////////////////////////////////////////
// CPlayerDlg dialog
/////////////////////////////////////////////////////////////////////////////
class CPlayerDlg : public CDialog
{
// Construction
public:
	CPlayerDlg(CWnd* pParent = NULL);			// standard constructor

public:
	BOOL		m_bInited;

	/************************************************************************/
	/* para used to cap pic */
	UINT		m_nCapPicType;					// 0 indicates default bmp, 1 indicates jpeg
	UINT		m_npic_bmp;						// capped bmp  pic number
	UINT		m_npic_jpeg;					// capped jpeg pic number
	CString		m_strCapPicPath;				// capped pic path
	/************************************************************************/

	BOOL		m_bStartDraw;                   // start drawing?
	BOOL		m_bFileRefCreated;              // has file ref created?
	BOOL		m_bFileEnd;                     // has file played to end?
	BOOL		m_bStreamType;                  // played as stream?
	BOOL		m_bPicQuality;                  // use high picture quality?
	BOOL        m_bDeflash;	                    // set I frame deflashing?
	BOOL		m_bHighFluid;					// hight fluid motion?
	BOOL		m_bSound;                       // open the sound or not?
	BOOL		m_bOpen;                        // has file opend?
	BOOL		m_bRepeatPlay;                  // play the file rewind?
	BOOL		m_bFullScreen;                  // full screen or not?
	BOOL		m_bConvertAVI;                  // convert to AVI or not?
	
	LONG		m_nSpeed;                       // video play speed
	LONG		m_nWidth;                       // image width
	LONG		m_nHeight;                      // image height
	LONG		m_nPrePlayPos;                  // pre play slider pos
	
	DWORD		m_dwScreenHeight;               // screem height
	DWORD		m_dwScreenWidth;                // screen width	
	CRect		m_rcScreen;						// dlg in which screen now

    DWORD       m_dwSysFormat;
	DWORD		m_dwHeadSize;                   // file header length
	DWORD		m_dwMaxFileSize;                // file size
	DWORD		m_dwTotalFrames;                // total frames
	DWORD		m_dwMaxFileTime;                // total file time(s)
	DWORD		m_dwDisplaySecond;              // seconds displayed at the statusbar
	DWORD		m_dwDisplayMinute;              // minutes displayed at the statusbar
	DWORD		m_dwDisplayHour;                // hours   displayed at the statusbar
	DWORD		m_dwDlgTopSize;                 // dlg top  space height
	DWORD		m_dwDlgEdge;                    // dlg edge space width 
	DWORD       m_dwImageSharpenLevel;          // image sharpen level (0 ~6)
	DWORD		m_dwOldDeviceNum;				// old display device sequence

	CRect		m_rcWindow;						// window rect
	CRect		m_rcDraw;						// draw rect
	CRect		m_rcDisplay;                    // mutli display rect
	CPoint		m_StartPoint;                   // start point

	HANDLE		m_hEventKill;                   // kill inputstream thread event
	HANDLE		m_hEventInput;                  // inputstream thread event
	HANDLE		m_hThread;                      // inputstream thread handle
	HANDLE		m_hStreamFile;                  // input file

	HANDLE      m_hUDPThread;

	CString		m_strPlayFileName;              // playing h264 file path
	CString     m_strSaveAVIPath;               // saveing avi  file path
	
	CBitmap		m_VDBmp;                 // bmp
	CBitmap		m_BlackBmp;                     // black bmp
	CBitmap		m_OverlayBmp;                   // overlay bmp
	
	CMenu*		      m_pMainMenu;              // pointer to the menu
	CSeek*			  m_pSeek;                  // seek dialog
	CDisplayRect*     m_pDisplayRegion;         // display region dialog
	CVideoCtrlDlg*    m_pVideoControl;			// video control dialog
	WINDOWPLACEMENT   m_OldWndpl;               // save dialog window pos
	CWatermarkDlg*     m_pWatermarkDlg;			// watermark dialog
	PBYTE			  m_pQcifTempBuf;			// convert qcif to avi

	
	_VIDEO_PLAY_STATE m_enumState;              // now the play state

	BOOL m_bCapImage;
	StuPicData m_picData;

public:
	
	HANDLE	m_hTestFile;
	//错误信息
	char* MyErrorToString(DWORD error);

	BOOL PreTranslateMessage(MSG* lpmsg);       // overload to handle keydown message

	/*************************************************************************/
	/* button operation begin
	/*************************************************************************/
	// play / pause / stop
	void  Play();
	void  Pause();
	void  Stop();

	// gotostart / slow / fast / gotoend
	void  GotoStart();
	void  Slow();
	void  Fast();
	void  AdjustSpeed(int nSpeed);
	void  GotoEnd();

	// stepback / stepfore / cap picture
	void  StepBackward();
	void  StepForward();
	void  GetPic(char* pImage, DWORD nBufSize,long nWidth,long nHeight,long nType);
	void  Cappic();

	// close or open sound
	void  Sound();
	// adjust sound
	void  AdjustSound(BOOL bFlag);
	/*************************************************************************/
	/* button operation over
	/*************************************************************************/
	

	
	/*************************************************************************/
	/* menu operation begin
	/*************************************************************************/
	// file operation:
	void  Open();
	void  Close();
	void  CutFile();
	void  SetSecretKey();

	// view operation:
	void  ViewFullScreen();
	void  ViewZoom(UINT nID);
	void  Infomation();
	void  SetDisplay();
	BOOL  SetDevice(UINT nID);
	void  GetWatermark();
	
	// control operation:
	void  VideoControl();
	void  Repeat();
	void  Locate();
  
	// option operation:
	void  StreamType();
	
	void  Deflash();
	void  Quality();
	void  HighFluid();
	void  ImageSharpenLevel(UINT nID);
	void  ThrowB(UINT nID);
	void  SetDecodeType(UINT nID);
	
	void  DisplayType(UINT nID);
	void  SelectTimer(UINT nID);
	void  ResetBuf();
	
	void  CapPicType(UINT nID);
	void  CappicPath();
	
	void  ConvertToAVI();

	// help operation:
	void  AppAbout();
	void  AppHelp();
	/*************************************************************************/
	/* menu operation over
	/*************************************************************************/



	/*************************************************************************/
	/*  assistant operation begin
	/*************************************************************************/	
	// open/close file or stream
	BOOL  BrowseFile(CString *strFileName);
	void  OpenFile();
	void  OpenDavFile(char *fileName);
	void  CloseFile();
	void  OpenStream();
	void  CloseStream();

	// set play state
	void  DrawStatus();
	void  SetState();
	void  SetAVIState();
	DWORD GetSpeedModulus(); 
	
	// sort the dialog control
	void  SetWindowSize();
	void  SortControl();
	void  InitWindowSize(DWORD cx, DWORD cy);

	// others
	CRect GetOnPicRect(CRect rcWnd, CRect rcOnWnd, LONG nPicWidth, LONG nPicHeight);	
	void  TestCapability(DWORD nDeviceNum);
	void  SetDisplayRegion(RECT);

	/*************************************************************************/
	/*  assistant operation over
	/*************************************************************************/


// Dialog Data
	//{{AFX_DATA(CPlayerDlg)
	enum { IDD = IDD_PLAYER_DIALOG };
	CButtonST		m_ctrlBtnCapPic;
	CButtonST		m_ctrlBtnSound;
	CButtonST		m_ctrlStepBackward;
	CButtonST		m_ctrlStepForward;
	CButtonST		m_ctrlBtnSlow;
	CButtonST		m_ctrlBtnFast;
	CButtonST		m_ctrlBtnGStart;
	CButtonST		m_ctrlBtnGEnd;
	CButtonST		m_ctrlBtnStop;
	CButtonST		m_ctrlBtnPlay;
	CButtonST		m_ctrlBtnPause;
	CStatic			m_ctrlVideoPic;
	CString			m_strPlayStateText;
	CXColorStatic	m_ctrlPlayText;
	//}}AFX_DATA
	CVolumeCtrl		m_SoundSlider;
	CXScrollBar		m_PlaySlider;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void DisplayOk(WPARAM wParam, LPARAM lParam);
	afx_msg void WatermarkOk(WPARAM wParam, LPARAM lParam);
	afx_msg void SeekOk(WPARAM wParam, LPARAM lParam);
	afx_msg void VideoCtrlOK(WPARAM wParam, LPARAM lParam);
	afx_msg void PlayMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void EncChangeMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuItem(UINT nID);
	afx_msg void OnButtonItem(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERDLG_H__BC7E7078_7E67_40B3_85A4_591E51BB1A4A__INCLUDED_)
