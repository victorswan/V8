// RoomParentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Room.h"
#include "RoomParentDlg.h"
#include "skin_i.h"
#include "SkinUtil.h"
#include "RoomLeftDlg.h"
#include "RoomMidDlg.h"
#include "RoomRightDlg.h"
#include "UserMessageDefine.h"
#include "micwindow\PrivateMicDlg.h"
#include "micwindow\P2PChatDlg.h"
#include "emotion\EmotionDlg.h"
#include "stamp\StampDlg.h"
//#include "PngDlg.h"
#include "gift\ChangeVoiceDlg.h"
#include "screeneffect\FlyingTextInputDlg.h"

#include "utility\ScrollBtnDlg.h"
#include "paodao\PaodaoBtnDlg.h"

#include "avlogic\RoomAVLogic.h"
#include "GlobalRoomDefine.h"

#include "loudspeaker\SpeakerDlg.h"
#include "loudspeaker\WishSpeakerDlg.h"
#include "userlist\KickDlg.h"
#include "personalsetting\PersonalConfig.h"
#include "SendEventManager.h"
#include "roomsetting\RoomOption.h"
#include "userinfo\UserInfoCardDlg.h"
#include "SysSetting\SysSettingDlg.h"
#include "userinfo\OtherUserInfoDlg.h"
#include "userlist\ListIconManager.h"

#include "..\CommonLibrary\include\utility\SystemHelper.h"
#include "..\CommonLibrary\include\ui\UIHelper.h"
#include "..\CommonLibrary\include\ui\C179MsgBox.h"
#include "..\CommonLibrary\include\utility\StringHelper.h"
#include "userlist\UserListMenu.h"
#include "autoreply\AutoReplyConfig.h"
#include "autoreply\AutoReplySettingDlg.h"
//#include "SysSetting\ShowAudioTestDlg.h"
#include "utility\CoverWnd.h"
#include "gift\GiftWordsDlg.h"
#include "utility\ModifyNameTipWnd.h"
#include "..\CommonLibrary\include\utility\ConfigManager.h"
#include "richlevel\RichLevelManager.h"
#include "Task\TaskDlg.h"
#include "guide\EnterRoomGuide.h"
#include "ordersong\OrderSongDlg.h"
#include "RoomBottomLeftDlg.h"
#include "selfinfoandset\SelfInfoAndSetDlg.h"
#include "RoomTopManager.h"
#include "micwindow/PublicMicDlg.h"
#include "paodao\PaodaoStaitc.h"
#include "userlist\IconIntroductionDlg.h"
#include "pay\PayDlg.h"

#define SKIN_ON_CLICK_SYS_CLOSE           1
#define SKIN_ON_CLICK_SYS_MINIMIZE        2
#define SKIN_ON_CLICK_SYS_MAXIMIZE        3
#define SKIN_ON_CLICK_BTN_COLLECT_ROOM    4

#define NOTIFY_SKIN_ROOM_LEFT_DLG         5
#define NOTIFY_SKIN_ROOM_MID_DLG		  6
#define NOTIFY_SKIN_ROOM_RIGHT_DLG        7

#define SKIN_ON_CLICK_BTN_STATUS          8
#define SKIN_ON_CLICK_BTN_AUDIOSET        9

#define SKIN_ON_CLICK_ICON_MICON		 10
#define SKIN_ON_CLICK_ICON_MICOFF		 11
#define SKIN_ON_CLICK_ICON_SPEAKERON	 12
#define SKIN_ON_CLICK_ICON_SPEAKEROFF	 13

#define SKIN_ON_CLICK_ICON_USERLEVEL	 14
#define SKIN_ON_CLICK_ICON_USERHEAD		 15
#define SKIN_ON_CLICK_ICON_USERROLE		 16

#define SKIN_ON_CLICK_SYS_FEEDBACK		 17
#define NOTIFY_SKIN_ROOM_BOTTOM_POS      18

#define NOTIFY_SKIN_ROOM_BOTTOMLEFT_DLG  19
#define NOTIFY_SKIN_ROOM_PUBLIC_MIC1_DLG 20
#define NOTIFY_SKIN_ROOM_PUBLIC_MIC2_DLG 21
#define NOTIFY_SKIN_ROOM_PUBLIC_MIC3_DLG 22
#define SKIN_ON_CLICK_PAIMIC			 23
#define NOTIFY_MOVE_PAODAO               24
#define SKIN_ON_CLICK_BTN_ICON_INTRO     25

#define SKIN_ON_CLICK_BTN_ROOM_ACTOR_UP				26
#define SKIN_ON_CLICK_BTN_ROOM_ACTOR_DOWN			27
#define SKIN_ON_CLICK_BTN_ROOM_ACTOR_TITLE_CLOSE	28
#define SKIN_ON_CLICK_BIN_ROOM_ACTOR_TOPTITLE_DOWN  29
#define SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD1  30
#define SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD2  31
#define SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD3  32
#define SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD4  33
#define SKIN_ON_CLICK_BTN_SPEAKER 34

#define ROOM_LEFT_DLG_LEFT                2
#define ROOM_LEFT_DLG_TOP                 55
#define ROOM_LEFT_DLG_WIDTH               1016
#define ROOM_LEFT_DLG_HEIGHT              350

#define ROOM_BOTTOMLEFT_DLG_LEFT		  2
#define ROOM_BOTTOMLEFT_DLG_TOP			  405
#define ROOM_BOTTOMLEFT_DLG_WIDTH		  250
#define ROOM_BOTTOMLEFT_DLG_HEIGHT		  333

#define ROOM_MID_DLG_LEFT                 252
#define ROOM_MID_DLG_TOP			      405
#define ROOM_MID_DLG_WIDTH                512            
#define ROOM_MID_DLG_HEIGHT               333

#define ROOM_RIGHT_DLG_LEFT               770
#define ROOM_RIGHT_DLG_TOP			      405
#define ROOM_RIGHT_DLG_WIDTH              250             
#define ROOM_RIGHT_DLG_HEIGHT             333


#define SPEAKER_WIDTH		425
#define SPEAKER_HEIGHT		327

#define KICK_WIDTH			373
#define KICK_HEIGHT			240

#define MODIFYNAME_TIP_LEFT_MARGIN      35   //修改昵称提示框距房间左边的距离
#define MODIFYNAME_TIP_BOTTOM_MARGIN    24   //距房间底部的距离

//#define  WM_CLICK_AUDIOSET_MENU   WM_USER+3333 
#define  WM_ROOM_STATREPORT       WM_USER+3334


#define ICON_INTRO_WIDTH	477
#define ICON_INTRO_HEIGHT	760
// CRoomParentDlg 对话框

IMPLEMENT_DYNAMIC(CRoomParentDlg, CDialog)

CRoomParentDlg::CRoomParentDlg(uint32 uRoomID, RoomOption * pRoomOption, CWnd* pParent /*=NULL*/)
: CDialog(CRoomParentDlg::IDD, pParent),
m_uRoomID(uRoomID),
m_pRoomOption(pRoomOption),
m_SpeakerLogic(this, false)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);

	m_pRoomAvLogic = NULL ;

	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg = NULL;
	m_pRoomTopManager = NULL;

	m_pRoomMidDlg = NULL;
	m_pRoomRightDlg = NULL;
	m_pP2PChatDlg = NULL ;
	m_pEmotionDlg = NULL ;
	m_pStampDlg = NULL ;
	m_pScrollBtnDlg = NULL ;
	m_pSpeakerDlg = NULL;
	m_pWishSpeakDlg = NULL;
	m_pSelectUserItem = NULL;
	m_pKickDlg = NULL ;
	m_pSpeakerDlg = NULL ;
	m_pWishSpeakDlg = NULL ;
	//m_pPngDlg = NULL ;
	m_pChangeVoiceDlg = NULL;
	m_pFlyingTextInputDlg = NULL;
	m_pHtmlOutPutManager = NULL ;
	m_pUserInfoCardDlg = NULL ;
	m_pUserInfoDlg = NULL ;
	m_pOtherUserInfoDlg = NULL ;
	m_pAnchorFansCardDlg = NULL;
	m_pEffectManager = NULL;
	m_pLoudSpeakerManager = NULL;
	m_nOutGiftIndex  = 0 ;
	//m_pAudioTest = NULL;
	m_pCoverWnd = NULL ;
	m_pGiftWordsDlg = NULL ;
	m_pModifyNameTipWnd = NULL;
	//m_pRichLevelBtn = NULL;
	m_bShowRichLevel = false;
	//m_pTaskDlg = NULL;
	//m_pBtnTask = NULL;
	m_pGuideFlash = NULL;

	m_pEnterRoomGuideDlg = NULL;
	m_pOrderSongDlg = NULL;
	m_pRoomBottomLeftDlg = NULL;
	m_pPaodaoStatic = NULL ;
	m_pIconIntroducDlg = NULL;
	m_pPayDlg = NULL;
}

CRoomParentDlg::~CRoomParentDlg()
{
	if ( m_pRoomAvLogic != NULL )
	{
		m_pRoomAvLogic->ClearRoomAV() ;
		delete m_pRoomAvLogic ;
	}

	map<uint32 , CPrivateMicDlg*>::iterator iter_private ;
	for ( iter_private = m_mPrivateMicDlg.begin() ;iter_private !=m_mPrivateMicDlg.end() ; ++iter_private )
	{
		CPrivateMicDlg* pPrivateMicDlg = iter_private->second ;
		SAFE_DELETE_DIALOG(pPrivateMicDlg);
	}
	SAFE_DELETE_DIALOG(m_pP2PChatDlg);
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	map<int ,CPublicMicDlg*>::iterator iter_public ;
	for ( iter_public = m_mPublicMicDlg.begin() ; iter_public != m_mPublicMicDlg.end() ; ++iter_public )
	{
		CPublicMicDlg* pPublicMicDlg = iter_public->second ;
		SAFE_DELETE_DIALOG(pPublicMicDlg);
	}
	//SAFE_DELETE_DIALOG(m_pRoomLeftDlg) ;
	if (m_pRoomTopManager != NULL)
	{	

		delete m_pRoomTopManager;
		m_pRoomTopManager = NULL;
	}

	SAFE_DELETE_DIALOG(m_pRoomMidDlg);
	SAFE_DELETE_DIALOG(m_pRoomRightDlg) ;
	SAFE_DELETE_DIALOG(m_pStampDlg) ;
	SAFE_DELETE_DIALOG(m_pEmotionDlg) ;
	//SAFE_DELETE_DIALOG(m_pPngDlg) ;
	SAFE_DELETE_DIALOG(m_pChangeVoiceDlg);
	SAFE_DELETE_DIALOG(m_pFlyingTextInputDlg);
	SAFE_DELETE_DIALOG(m_pUserInfoCardDlg) ;
	SAFE_DELETE_DIALOG(m_pUserInfoDlg) ;
	SAFE_DELETE_DIALOG(m_pOtherUserInfoDlg) ;
	SAFE_DELETE_DIALOG(m_pAnchorFansCardDlg) ;
	SAFE_DELETE_DIALOG(m_pCoverWnd) ;
	SAFE_DELETE_DIALOG(m_pGiftWordsDlg) ;
	SAFE_DELETE_DIALOG(m_pModifyNameTipWnd);
	//SAFE_DELETE_DIALOG(m_pTaskDlg);
	SAFE_DELETE_DIALOG(m_pEnterRoomGuideDlg);
	SAFE_DELETE_DIALOG(m_pOrderSongDlg);
	SAFE_DELETE_DIALOG(m_pRoomBottomLeftDlg);
	if (m_pEffectManager != NULL)
	{
		delete m_pEffectManager;
		m_pEffectManager = NULL;
	}
	if (m_pLoudSpeakerManager != NULL)
	{
		delete m_pLoudSpeakerManager;
		m_pLoudSpeakerManager = NULL;
	}
	if (m_pRoomBusiness != NULL)
	{
		delete m_pRoomBusiness;
		m_pRoomBusiness = NULL;
	}
	if (m_pHtmlOutPutManager != NULL)
	{
		delete m_pHtmlOutPutManager;
		m_pHtmlOutPutManager = NULL;
	}
	/*if (m_pAudioTest != NULL)
	{
	m_pAudioTest->DestroyWindow();
	delete m_pAudioTest;
	m_pAudioTest = NULL;
	}*/
	/*if (m_pBtnTask != NULL)
	{
	m_pBtnTask->DestroyWindow();
	delete m_pBtnTask;
	m_pBtnTask = NULL;
	}*/

	std::map<int , common::ui::PngButton*>::iterator iter ;
	for ( iter = m_pMapFansBtn.begin() ; iter != m_pMapFansBtn.end() ; ++iter)
	{
		common::ui::PngButton* pPngBtn = iter->second ;
		if ( pPngBtn != NULL && pPngBtn->GetSafeHwnd() != NULL )
		{
			pPngBtn->DestroyWindow();
			delete pPngBtn;
			pPngBtn = NULL;
		}
	}
	m_pMapFansBtn.clear();

	for ( iter = m_pMapUnDealSongBtn.begin() ; iter != m_pMapUnDealSongBtn.end() ; ++iter)
	{
		common::ui::PngButton* pPngBtn = iter->second ;
		if ( pPngBtn != NULL && pPngBtn->GetSafeHwnd() != NULL )
		{
			pPngBtn->DestroyWindow();
			delete pPngBtn;
			pPngBtn = NULL;
		}
	}
	m_pMapUnDealSongBtn.clear();

	SAFE_DELETE_DIALOG(m_pPaodaoStatic) ;
	SAFE_DELETE_DIALOG(m_pIconIntroducDlg);
	SAFE_DELETE_DIALOG(m_pPayDlg);
}

void CRoomParentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HTML_ROOM_TITLE2, m_RoomTitleTicker);
}


BEGIN_MESSAGE_MAP(CRoomParentDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_MESSAGE(WM_CLICK_STAMP, OnClickStamp)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_ACTIVATE()
	ON_MESSAGE(WM_PRIVATEMICDLG_CLOSE , OnPrivateMicDlgClose )
	ON_MESSAGE(WM_P2PMICDLG_CLOSE , OnP2PMicDlgClose )
	ON_MESSAGE(WM_CLICK_SPEAKER, OnClickSpeaker)
	ON_MESSAGE(WM_CLICK_WISHSONG, OnClickWishSong)
	ON_MESSAGE(WM_CLICK_USERLIST, OnClickUserList)
	ON_MESSAGE(WM_DBCLICK_USERLIST, OnDBClickUserList)
	ON_MESSAGE(WM_CLICK_STAMPLIST, OnClickStampList)
	ON_MESSAGE(WM_CLICK_CHANGEVOICE, OnClickChangeVoice)
	ON_MESSAGE(WM_CLICK_CHANGEVOICELIST, OnClickChangeVoiceList)
	ON_MESSAGE(WM_CLICK_FLYINGTEXT, OnClickFlyingText)
	//ON_MESSAGE(WM_CLICK_AUTOREPLY_MENU, OnClickBtnAutoReplyMsg)
	//ON_MESSAGE(WM_CLICK_AUDIOSET_MENU, OnClickMenuAudioSet)
	ON_MESSAGE(WM_SKIN_PAINT,	&CRoomParentDlg::OnPostPaint)
	ON_MESSAGE(WM_ROOM_STATREPORT,	OnIpStatReport)
	ON_MESSAGE(WM_CLICK_SOFA_NAME, OnClickSofaName)
	ON_WM_SIZE()
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_ONCLICK_MODIFYNAME_CLOSE , &CRoomParentDlg::OnModifyNameClickClose )
	//ON_MESSAGE(WM_ONCLICK_PNGBUTTON , &CRoomParentDlg::OnBtnTaskClick )
	ON_MESSAGE(WM_ONMOUSERHOVER_PNGBUTTON , &CRoomParentDlg::OnBtnFansHover )
	ON_MESSAGE(WM_ONMOUSERLEAVE_PNGBUTTON , &CRoomParentDlg::OnBtnFansLeave )
	ON_MESSAGE(COMMONLIB_UM_NONDOMODAL_MSGBOX_GOTOREGISTER, &CRoomParentDlg::OnClickMsgBoxGoToRegister)
	ON_WM_NCMOUSEMOVE()
	//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRoomParentDlg 消息处理程序

int CRoomParentDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//LoadSkin
	ASSERT(NULL != m_pSkinEngine);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"RoomParentDlg");
		ASSERT(hr== S_OK && __LINE__);
	}

	return 0;
}


BOOL CRoomParentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//最小化时到任务栏，而不是托盘
	ModifyStyleEx(0,WS_EX_APPWINDOW);
	ModifyStyle( 0 , WS_CLIPCHILDREN ) ;

	//创建房间主题IE控件
	m_RoomTitleTicker.SetPause( false ) ;
	m_RoomTitleTicker.SetClickTitle( false ) ;
	//	m_RoomTitleTicker.SetTickerColor( RGB(240,240,240) , RGB(240,240,240 ) ) ;

	//创建左中右三个子对话框
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManager，公麦窗口在这创建
	/*m_pRoomLeftDlg = new CRoomLeftDlg(this);
	if (m_pRoomLeftDlg)
	{
	m_pRoomLeftDlg->Create(CRoomLeftDlg::IDD, this);
	m_pRoomLeftDlg->SetWindowPos(NULL,ROOM_LEFT_DLG_LEFT,ROOM_LEFT_DLG_TOP,ROOM_LEFT_DLG_WIDTH,ROOM_LEFT_DLG_HEIGHT,SWP_SHOWWINDOW);
	}*/
	m_pRoomTopManager = new CRoomTopManager(this);
	for(int i=1;i<=3;++i)
	{
		CPublicMicDlg *pPublicMicDlg = new CPublicMicDlg(this, i) ;
		if (pPublicMicDlg)
		{
			pPublicMicDlg->Create(CPublicMicDlg::IDD,this);
			m_mPublicMicDlg[i] = pPublicMicDlg;
		}
	}
	m_pRoomTopManager->SetAllPublicMic(m_mPublicMicDlg);

	//创建喇叭IE控件
	m_pSpeakerHtml = new COutputHtmlEditImpl(ROOM_OUTPUTSPEAKER_MAX_HOLD_LINE , HTML_TYPE_SPEAK ) ;
	m_pSpeakerHtml->SetHtmlEditLogic( &m_SpeakerLogic ) ;
	m_pSpeakerHtml->Create( this ,IDC_HTML_ROOM_SPEAKER , CRect(0,0,0,0) , WS_CHILD|WS_VISIBLE) ;
	CComVariant var = (long)m_pSpeakerHtml->GetSafeHwnd() ;
	if(m_pSkinEngine != NULL)
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"itemHtmlSpeaker",L"hwnd",var);

	m_pRoomTopManager->SetSpeakerHtml(m_pSpeakerHtml);
	m_pSpeakerHtml->ShowWindow(SW_HIDE);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomSpeakerBK", L"visible", (CComVariant)false);

	m_pLoudSpeakerManager = new CLoudSpeakerManager(this);

	m_pRoomBottomLeftDlg = new CRoomBottomLeftDlg(this);
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->Create(CRoomBottomLeftDlg::IDD, this);
		m_pRoomBottomLeftDlg->SetWindowPos(NULL,ROOM_BOTTOMLEFT_DLG_LEFT,ROOM_BOTTOMLEFT_DLG_TOP,ROOM_BOTTOMLEFT_DLG_WIDTH,ROOM_BOTTOMLEFT_DLG_HEIGHT,SWP_SHOWWINDOW);
	}

	m_pRoomMidDlg = new CRoomMidDlg(this);
	if (m_pRoomMidDlg)
	{
		m_pRoomMidDlg->Create(CRoomMidDlg::IDD, this);
		m_pRoomMidDlg->SetWindowPos(NULL,ROOM_MID_DLG_LEFT,ROOM_MID_DLG_TOP,ROOM_MID_DLG_WIDTH,ROOM_MID_DLG_HEIGHT,SWP_SHOWWINDOW);
	}

	m_pRoomRightDlg = new CRoomRightDlg(this);
	if (m_pRoomRightDlg)
	{
		m_pRoomRightDlg->Create(CRoomRightDlg::IDD, this);
		m_pRoomRightDlg->SetWindowPos(NULL,ROOM_RIGHT_DLG_LEFT,ROOM_RIGHT_DLG_TOP,ROOM_RIGHT_DLG_WIDTH,ROOM_RIGHT_DLG_HEIGHT,SWP_SHOWWINDOW);
	}

	//跑道
	m_pPaodaoStatic = new CPaodaoStaitc(this);
	m_pPaodaoStatic->Create( NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this ,IDC_ROOM_NEW_PAODAO) ;
	//CComVariant var = (LONG)m_pPaodaoStatic->GetSafeHwnd();
	//m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"itemHtmlPaoDao", L"hwnd", var) ;

	m_pEffectManager = new ScreenEffectManager(this);

	InitMicSlider();

	NotifyCreateSkinItem();

	SetTimer( ROOM_NET_STATE_TIMER_ID , ROOM_NET_STATE_INTERVAL , NULL ) ;
	SetNetState() ;

	if (AutoReplyMgr->IsAutoReply())
	{	
		SetMyStatus(FALSE);
	}else
	{
		SetMyStatus(TRUE);
	}

	CString ipCity;
	ipCity = CStatReport::GetIpCity();
	if(ipCity.IsEmpty())
	{
		m_ipStatReport.IPStatReportRequest(this->GetSafeHwnd(),WM_ROOM_STATREPORT);//发送获取本机IP地址申请
	}

	if (GetCurInfo().enmAccountType != ACCOUNTTYPE_VISITOR)
	{
		CString strModifyName = L"";
		CConfigManager::Instance()->GetUserInfo_Setting(GetCurInfo().unUIN, USERINFO_MODIFY_NAME, strModifyName);

		if (strModifyName == L""  || strModifyName == L"true")
		{
			m_pModifyNameTipWnd = new CModifyNameTipWnd;
			if (m_pModifyNameTipWnd->CreateEx(this))
			{
				CString strApp = common::utility::systemhelper::Get179AppPath().c_str();
				CString strTemp;
				strTemp.Format(L"%sresource\\other\\Room_imgModifyNamaTips.png",strApp);
				m_pModifyNameTipWnd->SetTipsImage(strTemp);
				strTemp.Format(L"%sresource\\other\\Room_imgModifyNamaClose.png",strApp);
				m_pModifyNameTipWnd->SetCloseImage(strTemp);
			}
		}
	}

	//DrawGifButton();
	//DrawBtnTask();

	//DragonZ:这里要改
	//SetCollectRoom(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CRoomParentDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//屏蔽ESC按键和ENTER键
	if ( pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			return TRUE ;
		default: break;
		}	
	}

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CRoomParentDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_SYS_CLOSE:
		{
			PostMessage(WM_CLOSE,NULL,NULL);
		}
		break;
	case SKIN_ON_CLICK_SYS_MINIMIZE:
		{
			PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		break;
	case SKIN_ON_CLICK_SYS_MAXIMIZE:
		{
			PostMessage(WM_SYSCOMMAND, IsZoomed() ? SC_RESTORE : SC_MAXIMIZE, 0);
		}
		break;
	case SKIN_ON_CLICK_BTN_COLLECT_ROOM:
		{
			OnClickBtnCollectRoom();
		}  
		break;
	case SKIN_ON_CLICK_BTN_ROOM_ACTOR_UP:
		{
			if(m_pRoomTopManager != NULL)
			{
				m_pRoomTopManager->OnClickBtnRoomActorUp();
			}
		}
		break;
	case SKIN_ON_CLICK_BTN_ROOM_ACTOR_DOWN:
		{
			if(m_pRoomTopManager != NULL)
			{
				m_pRoomTopManager->OnClickBtnRoomActorDown();
			}
		}
		break;
	case SKIN_ON_CLICK_BTN_ROOM_ACTOR_TITLE_CLOSE:
		{
			if(m_pRoomTopManager != NULL)
			{
				m_pRoomTopManager->OnClickBtnRoomActorTitle();
			}
		}
		break;
	case SKIN_ON_CLICK_BIN_ROOM_ACTOR_TOPTITLE_DOWN:
		{
			if(m_pRoomTopManager != NULL)
			{
				m_pRoomTopManager->OnClickBtnRoomActorTitle();
			}
		}
		break;
	case SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD1:
		{
			if(m_pRoomTopManager != NULL)
			{
				m_pRoomTopManager->OnClickBtnActorHead(1);
			}
		}
		break;
	case SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD2:
		{
			if(m_pRoomTopManager != NULL)
			{
				m_pRoomTopManager->OnClickBtnActorHead(2);
			}
		}
		break;
	case SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD3:
		{
			if(m_pRoomTopManager != NULL)
			{
				m_pRoomTopManager->OnClickBtnActorHead(3);
			}
		}
		break;
	case SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD4:
		{
			if(m_pRoomTopManager != NULL)
			{
				m_pRoomTopManager->OnClickBtnActorHead(4);
			}
		}
		break;
	case SKIN_ON_CLICK_BTN_STATUS:
		{
			//OnClickBtnStatus();
		}
		break;
	case SKIN_ON_CLICK_BTN_AUDIOSET:
		{
			//OnClickBtnAudioSet();
		}
		break;
	case SKIN_ON_CLICK_ICON_MICON:
		{
			//m_pRoomLeftDlg->CloseMic() ;
			//g_RoomModule->CloseMic();
		}
		break;
	case SKIN_ON_CLICK_ICON_MICOFF:
		{
			//m_pRoomLeftDlg->OpenMic() ;
			//g_RoomModule->OpenMic();
		}
		break;
	case SKIN_ON_CLICK_ICON_SPEAKERON:
		{
			//OnClickBtnCloseSound();
		}
		break;
	case SKIN_ON_CLICK_ICON_SPEAKEROFF:
		{
			//OnClickBtnOpenSound();
		}
		break;
	case SKIN_ON_CLICK_ICON_USERLEVEL:
		{
			//common::utility::systemhelper::OpenUrl( GetRoomBusiness()->GetUpdateVipUrl().GetBuffer() ) ;
		}
		break;
	case SKIN_ON_CLICK_ICON_USERHEAD:
		{
			//ShowSelfUserInfo();
		}
		break;
	case SKIN_ON_CLICK_ICON_USERROLE:
		{
			/*if (m_pRoomBottomLeftDlg != NULL && GetRoomBusiness()->GetUserManager()->GetSelfUserItem() != NULL )
			{
			m_pRoomBottomLeftDlg->ShowUserItem( GetRoomBusiness()->GetUserManager()->GetSelfUserItem() );
			}*/
		}
		break;
	case SKIN_ON_CLICK_SYS_FEEDBACK:
		{
			common::utility::systemhelper::OpenUrl( GetRoomBusiness()->GetFeedBackRoomUrl().GetBuffer());
		}
		break;
	case SKIN_ON_CLICK_PAIMIC:
		{
			m_pRoomTopManager->OnClickPaiMic();
		}
		break;
	case NOTIFY_MOVE_PAODAO:
		{
			MovePaoDao();
		}
		break;
	case SKIN_ON_CLICK_BTN_ICON_INTRO:
		{
			OnClickBtnIconIntro();
		}
		break;
	case SKIN_ON_CLICK_BTN_SPEAKER:
		{
			OnClickSpeaker(0, 0);
		}
		break;
	default:break;
	}

	return TRUE;
}

void CRoomParentDlg::NotifyCreateSkinItem()
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManager
	/*if (m_pRoomLeftDlg->GetSafeHwnd())
	{
	NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ROOM_LEFT_DLG,m_pRoomLeftDlg->GetSafeHwnd());
	}*/
	if (m_pRoomMidDlg->GetSafeHwnd())
	{
		NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ROOM_MID_DLG,m_pRoomMidDlg->GetSafeHwnd());
	}
	if (m_pRoomRightDlg->GetSafeHwnd())
	{
		NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ROOM_RIGHT_DLG,m_pRoomRightDlg->GetSafeHwnd());
	}
	if (m_pRoomBottomLeftDlg->GetSafeHwnd())
	{
		NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ROOM_BOTTOMLEFT_DLG,m_pRoomBottomLeftDlg->GetSafeHwnd());
	}

	map<int , CPublicMicDlg*>::iterator iter ;
	int i = 0 ;
	for ( iter = m_mPublicMicDlg.begin() ; iter != m_mPublicMicDlg.end() ; ++iter ,++i)
	{
		CPublicMicDlg* pPbulicMicDlg = iter->second ;
		if ( pPbulicMicDlg->GetSafeHwnd() != NULL )
		{
			NotifySkinHelper( GetSafeHwnd() ,NOTIFY_SKIN_ROOM_PUBLIC_MIC1_DLG+i , pPbulicMicDlg->GetSafeHwnd() ) ;
		}
	}
}

void CRoomParentDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ASSERT(m_pRoomBusiness != NULL);
	CSendEventManager::SendLeaveRoomEvent(m_uRoomID);
	__super::OnClose();
	CleanAVLogic();
	//CFlashWnd::StopAllFlash();
	//GetEffectManager()->StopAllFlash();
	//CFlashWnd::StopAllFlash();
	DestroyWindow();
}


void CRoomParentDlg::OnTimer(UINT_PTR nIDEvent) 
{
	switch( nIDEvent )
	{
	case ROOM_CAISHEN_TIMER_FIRST_ID:
	case ROOM_CAISHEN_TIMER_INTERVAL_ID:
		{
			PlutusAward() ;
		}
		break;
	case ROOM_GIFT_TIMER_ID:
		{
			if(OutPutGift())
			{
				OutPutGift();
			}
		}
		break;
	case ROOM_NET_STATE_TIMER_ID:  //网络状态
		{
			SetNetState() ;
		}
		break;
	case ROOM_FLASH_WINDOW_TIMER:
		{
			FlashWindow(TRUE) ;
		}
		break;
	case ROOM_GUEST_REGISTER_TIMER:
		{
			KillTimer( ROOM_GUEST_REGISTER_TIMER ) ;
			if ( !IsIconic() )
			{
				if ( m_pCoverWnd == NULL )
				{
					m_pCoverWnd = new CCoverWnd ;
					CRect Rc ;
					GetWindowRect( &Rc ) ;
					m_pCoverWnd->CreateEx( this , Rc ) ;
				}

				m_pCoverWnd->ShowWindow( SW_SHOWNOACTIVATE ) ;			
				CSendEventManager::SendGuestRegisterRequest( GetSafeHwnd() );			
				SetActiveWindow() ;
			}
			else
			{
				SetTimer( ROOM_GUEST_REGISTER_TIMER , ROOM_GUEST_REGISTER_SECOND_INTERVAL , NULL ) ;
			}
		}
		break;
	default:break;
	}
}

void CRoomParentDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	__super::OnActivate(nState, pWndOther, bMinimized);
	if ( nState == WA_ACTIVE && !IsIconic() )
	{
		KillTimer( ROOM_FLASH_WINDOW_TIMER ) ;		
	}	
	// TODO: 在此处添加消息处理程序代码
}

//收藏房间
void CRoomParentDlg::OnClickBtnCollectRoom()
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.enmVIPLevel == core::VIPLEVEL_NONE )
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能收藏房间，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
	}
	else
	{
		m_pRoomBusiness->CollectRoom() ;
	}	
}

void CRoomParentDlg::OnClickStamp() 
{
	SwitchResourceToModule(_T("Room"));
	if ( m_pStampDlg == NULL )
	{
		m_pStampDlg = new CStampDlg(this) ;
		m_pStampDlg->Create(CStampDlg::IDD, this);
		m_pStampDlg->SetWindowPos(NULL,200,200,403,288,SWP_SHOWWINDOW);//width=479有六列印章,现改为414，五列印章 
		m_pStampDlg->CenterWindow() ;
	}
	else
	{
		m_pStampDlg->ShowWindow(SW_SHOW) ;
	}
}

void CRoomParentDlg::OnClickEmotion(  CWnd* pParentWnd )
{
	common::ui::CCursorPos pt;
	SwitchResourceToModule(_T("Room"));
	CRoomMidDlg* pRoomMidDlg = (CRoomMidDlg*)pParentWnd;
	bool bShowPanel = (pRoomMidDlg == m_pRoomMidDlg);
	int nHeight = (pRoomMidDlg == m_pRoomMidDlg) ? 292 : 262;
	if ( m_pEmotionDlg == NULL )
	{
		m_pEmotionDlg = new CEmotionDlg(pParentWnd) ;
		m_pEmotionDlg->Create(CEmotionDlg::IDD,this);
		m_pEmotionDlg->SetWindowPos(NULL,pt.x,pt.y-nHeight,282,nHeight,SWP_SHOWWINDOW);
	}
	else
	{
		m_pEmotionDlg->SetWindowPos(NULL,pt.x,pt.y-nHeight,282,nHeight,SWP_SHOWWINDOW);
		m_pEmotionDlg->SetParentWnd(pParentWnd);
	}

	(pRoomMidDlg == m_pRoomMidDlg) ? ( m_pEmotionDlg->SetRoomMidDlg(pRoomMidDlg) ) : ( m_pEmotionDlg->SetRoomMidDlg(NULL) );

}

void CRoomParentDlg::SetNetState() //设置自己的网路状态
{
	if ( m_pRoomAvLogic != NULL )
	{
		float fRate = 0.0f;
		int nIndex = 0 ;
		m_pRoomAvLogic->GetNetState( fRate ) ;
		CString strTip ;
		if ( fRate>= -0.01 && fRate<= 0.01 )
		{
			nIndex = 5 ;
			strTip = L"网络状态：非常好" ;			
		}
		else if ( fRate < 0.04 )
		{
			nIndex = 4 ;
			strTip = L"网络状态：较好" ;
		}
		else if ( fRate < 0.08 )
		{
			nIndex = 3 ;
			strTip = L"网络状态：一般" ;
		}
		else if ( fRate < 0.15 )
		{
			nIndex = 2 ;
			strTip = L"网络状态：较差" ;
		}
		else if ( fRate < 0.25 )
		{
			nIndex = 1 ;
			strTip = L"网络状态：非常差" ;
		}
		else
		{
			nIndex = 0 ;
			strTip = L"与服务器连接已断开" ;
		}
		CString strFileName ;
		strFileName.Format( L"Room_imgRoomSignal%d.png" , nIndex ) ;
		CComVariant var = strFileName ;
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgNetSignal",L"image",var);
		var = strTip ;
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgNetSignal",L"tip",var);
	}
}

void CRoomParentDlg::OnClickHerfLink( CString& strName , CString& strUUID , CString& str179ID , int nType , CString strIndex ) 
{
	switch( nType )
	{
	case CLICK_TYPE_NAME:
		{
			OnClickNameLink( strName , strUUID ) ;
		}
		break;
	case CLICK_TYPE_STAMP:
		{
			OnClickStampLink( strName , strUUID ) ;
		}
		break;
	case CLICK_TYPE_PRIVATEVIDEO:
		{
			OnClickPrivateLink( strName , strUUID , str179ID ) ;
		}
		break;
	case CLICK_TYPE_P2P_ACCEPT:
		{
			OnClickP2PAccept( strName , strUUID ) ;
		}
		break;
	case CLICK_TYPE_P2P_REFUSE:
		{
			OnClickP2PRefuse( strName , strUUID ) ;
		}
		break;
	case CLICK_TYPE_TEMP_NOTICE:
		{
			OnClickTempNotice( strName , strUUID ) ;
		}
		break;
	case CLICK_TYPE_VOICE:
		{
			OnClickVoiceLink( strName, strUUID ) ;
		}
		break;
	case CLICK_TYPE_NO_REMIND:
		{
			OnClickNoRemind(strUUID);
		}
		break;
	case CLICK_TYPE_REGISTER:
		{
			OnClickRegister() ;
		}
		break;
	case CLICK_TYPE_PUBLIC_ACCEPT:
		{
			OnClickPublicAccept(strName, strUUID, strIndex);
		}
		break;
	case CLICK_TYPE_PUBLIC_REFUSE:
		{
			OnClickPublicRefuse(strName, strUUID, strIndex);
		}
		break;
	case CLICK_TYPE_MARK:
		{
			OnClickHrefMark();
		}
	default:break ;
	}
}


//输入框，点击了盖章
void CRoomParentDlg::OnClickStampLink( CString& strName , CString& strUUID ) 
{
	OnClickNameLink( strName , strUUID ) ;
	OnClickStamp() ;
}

//输入、输出聊天框，点击了 名字
void CRoomParentDlg::OnClickNameLink( CString& strName , CString& strUUID ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	uint32 unUUID = _wtol( strUUID.GetBuffer() ) ;
	if ( unUUID == myCurInfo.unUIN   )
	{
		m_pRoomBottomLeftDlg->OnClickBtnWhereIAm();
		return ;
	}
	else if ( m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unUUID ) == NULL )
	{
		GetHtmlOutPutManager()->InsertPrivateTips(L"【提示】： " ,L"抱歉，对方已离开该房间" , COLOR_OPERATE );
		return ;
	}
	//用户列表选中用户
	m_pRoomMidDlg->OnClickNameLink( strName , unUUID ) ;
	m_pRoomRightDlg->OnClickNameLink( strName , unUUID ) ;
	m_pRoomBottomLeftDlg->OnClickNameLink( strName, unUUID ) ;
}

void CRoomParentDlg::OnClickNameLink( CString& strName , uint32 unUUID )
{
	if (m_pPaodaoStatic != NULL)
	{
		m_pPaodaoStatic->OnClickNameLink( strName , unUUID ) ;
	}
}
//点击查看私麦链接
void CRoomParentDlg::OnClickPrivateLink( CString& strName , CString& strUUID , CString& str179ID ) 
{
	IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( _wtol(strUUID) ) ;
	if ( pUserItem == NULL )
	{
		CString strTemp ;
		strTemp.Format( L"%s(%s)已下私麦" , common::utility::stringhelper::XMLEncode( strName.GetBuffer()).c_str() , str179ID ) ;
		GetHtmlOutPutManager()->InsertPrivateTips(L"【提示】： " ,strTemp , COLOR_OPERATE );
		return ;
	}
	if ( pUserItem->GetUserStatus()&USERSTATUSTYPE_PRIVATE )
	{
		SendOpenPrivate( pUserItem->GetUserUIN() ) ;
	}	
	else
	{
		GetHtmlOutPutManager()->OnPrivateShowOff( pUserItem ) ;
	}
}


//同意一对一私聊
void CRoomParentDlg::OnClickP2PAccept( CString& strName ,CString& strUUID ) 
{
	uint32 unDstUIN = _wtol(strUUID) ;
	IUserItem* pDstUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDstUserItem == NULL )
	{
		CString strTemp ;
		if (unDstUIN > 999999)
		{
			strTemp = common::utility::stringhelper::XMLEncode( strName.GetBuffer()).c_str();
		}
		else
		{
			strTemp.Format( L"%s(%u) 已离开本房间" ,common::utility::stringhelper::XMLEncode( strName.GetBuffer()).c_str() , unDstUIN ) ;
		}
		GetHtmlOutPutManager()->InsertPrivateTips(L"【提示】： " ,strTemp , COLOR_OPERATE );
		return ;
	}
	CSendEventManager::SendResponseP2PEvent( m_uRoomID , unDstUIN , true ) ;
}

//拒绝一对一私聊
void CRoomParentDlg::OnClickP2PRefuse( CString& strName ,CString& strUUID ) 
{
	GetHtmlOutPutManager()->OnResponseP2PRspRefuse( _wtol(strUUID) ) ;
	CSendEventManager::SendResponseP2PEvent( m_uRoomID , _wtol(strUUID) , false );
}

void CRoomParentDlg::OnClickTempNotice( CString& strTempNotice , CString& strUUID ) 				//转发到临时公告
{
	std::wstring strText = strTempNotice.GetBuffer();
	common::utility::systemhelper::FilterWords(strText);

	core::SendMessageEvent * pEvent = new core::SendMessageEvent();
	pEvent->roomid = GetRoomBusiness()->GetRoomID();
	pEvent->message = strText;
	pEvent->enmType = core::SENDMESSAGETYPE_TEMP_NOTICE;
	pEvent->stFont = CPersonalConfig::GetInstance()->GetTempMessageFont()  ;

	g_RoomModule->m_pModuleManager->PushEvent(MakeEvent<MODULE_ID_ROOM>()(core::EVENT_VALUE_CORE_SEND_MESSAGE, MODULE_ID_CORE, 0, 0, 0, pEvent));
	BackMessage( 0 , CPersonalConfig::GetInstance()->GetTempMessageFont() , strText , core::SENDMESSAGETYPE_TEMP_NOTICE ) ;
}

void CRoomParentDlg::OnClickNoRemind(CString& strUUID)
{
	m_pRoomMidDlg->OnClickNoRemind(_wtoi(strUUID));
}
//
//void CRoomParentDlg::OnClickBtnStatus()
//{
//	CRect rcBtnStatus(0, 0, 0, 0);
//	m_pSkinEngine->GetSubSkinPos(GetSafeHwnd(), L"btnStatus", &(rcBtnStatus.left), &(rcBtnStatus.top), &(rcBtnStatus.right), &(rcBtnStatus.bottom));
//	CPoint pt(rcBtnStatus.left, rcBtnStatus.bottom);
//	ClientToScreen(&pt);
//
//	common::ui::CMenuEx* pm = new common::ui::CMenuEx();
//	pm->CreatePopupMenu();
//	pm->SetWidth(80);
//
//	CImageList *pImgList = new CImageList;
//	pImgList->Create(11, 11, TRUE | ILC_COLOR24, 16, 0);
//	pm->SetImageList(pImgList);
//	if (pImgList==NULL)
//	{
//		ASSERT(0);
//		delete pm;
//		return;
//	}
//
//	AutoReplyMenu autoReplyMenu(this) ;
//	SwitchResourceToModule(_T("Room"));
//
//	int iIndex = pImgList->Add(AfxGetApp()->LoadIcon(IDI_STATUS_ONLINE));
//	pm->AppendMenuEx(0, ID_STATUS_ONLINE, L"在线", iIndex);
//	iIndex = pImgList->Add(AfxGetApp()->LoadIcon(IDI_STATUS_LEAVE));
//	pm->AppendMenuEx(MF_POPUP, (UINT)autoReplyMenu.GetAutoReplyMenu()->GetSafeHmenu(), L"离开",  iIndex);
//	int nReturn = pm->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, this);
//	SendMessage(WM_CLICK_AUTOREPLY_MENU, 0, nReturn);
//	autoReplyMenu.DeleteReplyMenu();
//	pm->DestroyMenu();
//	delete pm;
//	pm = NULL;
//}
//
//void CRoomParentDlg::OnClickBtnAudioSet()
//{
//	CRect rcBtnAudioSet(0, 0, 0, 0);
//	m_pSkinEngine->GetSubSkinPos(GetSafeHwnd(), L"btnAudioSet", &(rcBtnAudioSet.left), &(rcBtnAudioSet.top), &(rcBtnAudioSet.right), &(rcBtnAudioSet.bottom));
//	CPoint pt(rcBtnAudioSet.left, rcBtnAudioSet.bottom);
//	ClientToScreen(&pt);
//
//	common::ui::CMenuEx* pm = new common::ui::CMenuEx();
//	common::ui::CMenuEx* pmSub = new common::ui::CMenuEx();
//	pm->CreatePopupMenu();
//	pmSub->CreatePopupMenu();
//	pm->SetWidth(80);
//	pmSub->SetWidth(80);
//
//	EnMixerControlMode enmMode = (EnMixerControlMode)(CPersonalConfig::GetInstance()->GetOnMicPurpose());
//
//	if (enmMode == MIXER_CONTROL_SING || enmMode == MIXER_CONTROL_OTHER)
//	{
//		pmSub->AppendMenuEx(MF_STRING | MF_CHECKED, 1, L"唱歌");
//	}
//	else
//	{
//		pmSub->AppendMenuEx(MF_STRING, 1, L"唱歌");
//	}
//	if (enmMode == MIXER_CONTROL_CHAT)
//	{
//		pmSub->AppendMenuEx(MF_STRING | MF_CHECKED, 2, L"聊天");
//	}
//	else
//	{
//		pmSub->AppendMenuEx(MF_STRING, 2, L"聊天");
//	}
//	if (enmMode == MIXER_CONTROL_PLAY)
//	{
//		pmSub->AppendMenuEx(MF_STRING | MF_CHECKED, 3, L"放歌");
//	}
//	else
//	{
//		pmSub->AppendMenuEx(MF_STRING, 3, L"放歌");
//	}
//
//	pm->AppendMenuEx(MF_POPUP, (UINT)pmSub->GetSafeHmenu(), L"音频模式");
//	pm->AppendMenuEx(MF_STRING, ID_AUDIOSET_TEST, L"音频测试");
//	pm->AppendMenuEx(MF_STRING, ID_AUDIOSET_SETTING, L"音频设置");
//
//	int nReturn = pm->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, this);
//
//	SendMessage(WM_CLICK_AUDIOSET_MENU, 0, nReturn);
//
//	pmSub->DestroyMenu();
//	delete pmSub;
//	pmSub = NULL;
//
//	pm->DestroyMenu();
//	delete pm;
//	pm = NULL;
//}

void CRoomParentDlg::OnMenuOnline()//点击在线
{
	AutoReplyMgr->SetAutoReply(FALSE);

	g_RoomModule->UpdateAllRoomStatus(TRUE);
}

void CRoomParentDlg::SetMyStatus(BOOL bOnLine)
{
	//if (bOnLine)//设置为在线状态
	//{
	//	CComVariant var = L"Room_btnIconStatusOnLine.png";
	//	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnStatus", L"iconImage", var);
	//	var = L"在线";
	//	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnStatus", L"tip", var);
	//}else
	//{
	//	CComVariant var = L"Room_btnIconStatusLeave.png";
	//	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnStatus", L"iconImage", var);
	//	var = L"离开";
	//	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnStatus", L"tip", var);
	//}

	//DragonZ: V2.21后布局更改版用
	m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->SetMyStatus(bOnLine);
}
//
//LRESULT CRoomParentDlg::OnClickBtnAutoReplyMsg(WPARAM wParam, LPARAM lParam)
//{
//	int nIndex = lParam ;
//	if (nIndex == 0)
//	{
//		return S_FALSE;
//	}
//	core::CurInfo myCurInfo = GetCurInfo() ;
//	if (myCurInfo.enmVIPLevel == core::VIPLEVEL_REGISTER)//注册用户
//	{
//		C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING_WITH_LINK, L"只有VIP以上用户才能设置自动回复", L"", L"", L"马上升级VIP", GetRoomBusiness()->GetUpdateVipUrl().GetBuffer(0));
//		return S_FALSE;
//	} 
//	if (myCurInfo.enmVIPLevel == core::VIPLEVEL_NONE)//游客
//	{
//		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能设置自动回复，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
//		return S_FALSE;
//	}
//		
//	if (ID_STATUS_ONLINE == nIndex)
//	{
//		OnMenuOnline();
//	}
//	else
//	{
//		if (nIndex == SET_AUTOREPLY_MENU)//点击自定义
//		{	
//			SwitchResourceToModule(_T("Room"));
//			CAutoReplySettingDlg pDlg;
//			if (IDOK == pDlg.DoModal())
//			{
//				if (pDlg.GetAutoReplyChange())
//				{
//					AutoReplyMgr->UpdateAutoReplyList(pDlg.GetNewAutoReply());
//				}
//				if (pDlg.GetAutoReplyState())//开启自动回复
//				{
//					if (pDlg.GetSelectedItem() < 0)
//					{
//						AutoReplyMgr->SetAutoReply(false);
//						g_RoomModule->UpdateAllRoomStatus(TRUE);
//					}else
//					{
//						AutoReplyMgr->SetAutoReply(true);
//						AutoReplyMgr->UpdateAutoReplyList(pDlg.GetNewAutoReply());
//						g_RoomModule->UpdateAllRoomStatus(FALSE);
//					}
//				}else
//				{
//					AutoReplyMgr->SetAutoReply(false);
//				}
//			}
//		}
//		else if (nIndex == CANCEL_AUTOREPLY_MENU)//点击无回复消息
//		{
//			AutoReplyMgr->SetAutoReply(FALSE);
//			g_RoomModule->UpdateAllRoomStatus(TRUE);
//		}
//		else //选择了自动回复的语句
//		{
//			stAutoReplyMenuItem stItem;
//			AutoReplyMgr->SetCheckedByIndex(nIndex - 1);
//			g_RoomModule->UpdateAllRoomStatus(FALSE);
//		}
//	}
//
//	return S_OK;
//}
//
//LRESULT CRoomParentDlg::OnClickMenuAudioSet(WPARAM wParam, LPARAM lParam)
//{
//	int nIndex = lParam;
//	if (nIndex == ID_AUDIOSET_TEST)//点了音频测试
//	{
//		ShowAudioTest();
//	}
//	else if(nIndex == ID_AUDIOSET_SETTING)//点了音频设置
//	{
//		if (m_pRoomLeftDlg != NULL)
//		{
//			m_pRoomLeftDlg->ShowUserSetting(Show_Sound_Setting_Dlg);
//		}
//	}
//	else if (nIndex == 1)//唱歌
//	{
//		CPersonalConfig::GetInstance()->SetOnMicPurpose(MIXER_CONTROL_SING);
//		m_pRoomAvLogic->SetMixerControlSingMode(true);
//	}
//	else if (nIndex == 2)//聊天
//	{
//		CPersonalConfig::GetInstance()->SetOnMicPurpose(MIXER_CONTROL_CHAT);
//		m_pRoomAvLogic->SetMixerControlChatMode(true);
//	}
//	else if (nIndex == 3)//放歌
//	{
//		CPersonalConfig::GetInstance()->SetOnMicPurpose(MIXER_CONTROL_PLAY);
//		m_pRoomAvLogic->SetMixerControlPlayMode(true);
//	}
//
//	return S_OK;
//}

void CRoomParentDlg::SendOpenPrivate( uint32 unDstUin ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	if ( myCurInfo.enmVIPLevel == core::VIPLEVEL_NONE && pUserItem->GetUserTitleLevel() != core::TITLELEVEL_SUPER_MANAGER )
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能观看私麦，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
		return ;
	}
	if ( myCurInfo.enmVIPLevel < core::VIPLEVEL_HONOR && pUserItem->GetUserTitleLevel() != core::TITLELEVEL_SUPER_MANAGER )
	{
		GetHtmlOutPutManager()->OnOpenPrivateRsp_NotPermission() ;
		return ;
	}
	CSendEventManager::SendOpenPrivateEvent(m_uRoomID, unDstUin);
}

void CRoomParentDlg::SendRequestP2PMic( uint32 unDstUin ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.enmVIPLevel < core::VIPLEVEL_VIP )
	{
		GetHtmlOutPutManager()->OnRequestP2PFailed_NotPermission() ;
		return ;
	}
	CSendEventManager::SendRequestP2PEvent( m_uRoomID, unDstUin );
}

void CRoomParentDlg::OnResponseP2PRspAccept( uint32 dstuin ) 
{
	CreateP2PMic( dstuin ) ;
}

void CRoomParentDlg::OnSetMicStatus( int16 nIndex , int16 nStatus ) 
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->OnSetMicStatus( nIndex , nStatus ) ;
	m_pRoomTopManager->OnSetMicStatus( nIndex , nStatus ) ;
}

void CRoomParentDlg::CleanAVLogic() 
{
	map<uint32 , CPrivateMicDlg*>::iterator iter_private ;
	for ( iter_private = m_mPrivateMicDlg.begin() ;iter_private !=m_mPrivateMicDlg.end() ; ++iter_private )
	{
		CPrivateMicDlg* pPrivateMicDlg = iter_private->second ;
		pPrivateMicDlg->CleanAVLogic() ;
	}
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->CleanAVLogic() ;
	m_pRoomTopManager->CleanAVLogic();

	if ( m_pP2PChatDlg != NULL )
	{
		m_pP2PChatDlg->CleanAVLogic() ;
	}
}

void CRoomParentDlg::OnOutPutHtmlMouseOver( CRect& CWindowRect , ENM_HTML_TYPE nHtmlType ) 
{
	SwitchResourceToModule(_T("Room"));
	if (m_pScrollBtnDlg == NULL )
	{
		m_pScrollBtnDlg = new CScrollBtnDlg(this) ;
		m_pScrollBtnDlg->Create(CScrollBtnDlg::IDD,this);
		m_pScrollBtnDlg->Init( nHtmlType ) ;
		m_pScrollBtnDlg->MoveWindow( CWindowRect.right-127,CWindowRect.top + 2,110,19 ) ;
		m_pScrollBtnDlg->ShowWindow( SW_SHOWNOACTIVATE ) ;
	}
	else
	{
		common::ui::CCursorPos pt;
		if ( !m_pScrollBtnDlg->IsWindowVisible() && CWindowRect.PtInRect( pt ) )
		{
			m_pScrollBtnDlg->Init( nHtmlType ) ;
			m_pScrollBtnDlg->MoveWindow( CWindowRect.right-127,CWindowRect.top + 2,110,19 ) ;
			m_pScrollBtnDlg->ShowWindow( SW_SHOWNOACTIVATE ) ;
		}
	}
}

void CRoomParentDlg::OnOutPutHtmlMouseOut( CRect& CWindowRect , ENM_HTML_TYPE nHtmlType ) 
{
	common::ui::CCursorPos pt;
	if ( m_pScrollBtnDlg != NULL && m_pScrollBtnDlg->IsWindowVisible() && !CWindowRect.PtInRect( pt ) )
	{
		m_pScrollBtnDlg->ShowWindow( SW_HIDE ) ;
	}
}


void CRoomParentDlg::OnSendMsg() 
{
	//m_pRoomMidDlg->OnSendMsg() ;
	m_pRoomMidDlg->OnClickBtnSendMsg();
}

void CRoomParentDlg::OnSendAutoMsg(uint32 unDstUin)
{
	m_pRoomMidDlg->OnSendAutoMsg(unDstUin);
}

void CRoomParentDlg::OnClickSpeakerShortCut( std::wstring strName, bool bBigSpeaker/* = false*/ )
{
	if (GetCurInfo().enmVIPLevel == core::VIPLEVEL_NONE)
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能发送小喇叭，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
		return;
	}

	if (GetCurInfo().enmVIPLevel > core::VIPLEVEL_NONE)
	{
		core::ENM_LoudSpeakerType enmType = core::LOUDSPEAKERTYPE_SMALL;
		if (bBigSpeaker)
		{
			enmType =  core::LOUDSPEAKERTYPE_BIG;
		}
		std::wstring strContent = strName + L":";
		if (m_pSpeakerDlg == NULL)
		{

			CreateSpeakerDlg( common::utility::stringhelper::XMLDecode(strContent).c_str(), enmType);
			m_pSpeakerDlg->SetInitContent(strContent.c_str());
			return;
		}
		if (m_pSpeakerDlg != NULL && m_pSpeakerDlg->GetSafeHwnd())
		{
			m_pSpeakerDlg->SetContent(common::utility::stringhelper::XMLDecode(strContent).c_str() );
			m_pSpeakerDlg->ShowWindow(SW_SHOW);
			m_pSpeakerDlg->SetType(enmType);
			m_pSpeakerDlg->SetForegroundWindow();
		}
	}
	//else
	//{
	//	C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING_WITH_LINK, L"只有VIP以上用户才能发送喇叭", L"", L"", L"立即升级", GetRoomBusiness()->GetUpdateVipUrl().GetBuffer(0));
	//}

}

void CRoomParentDlg::OnClickWishShortCut(std::wstring strName)
{
	if (GetCurInfo().enmVIPLevel == core::VIPLEVEL_NONE)
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能使用道具，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
		return;
	}

	if (GetCurInfo().enmVIPLevel > core::VIPLEVEL_REGISTER)
	{
		std::wstring strContent = strName + L":";
		if (m_pWishSpeakDlg == NULL)
		{
			CreateWishSpeakerDlg(strContent.c_str());
			return;
		}
		if (m_pWishSpeakDlg != NULL && m_pWishSpeakDlg->GetSafeHwnd())
		{
			m_pWishSpeakDlg->SetContent(strName.c_str());
			m_pWishSpeakDlg->ShowWindow(SW_SHOW);
			m_pWishSpeakDlg->SetForegroundWindow();
			m_pWishSpeakDlg->SetContent(strContent.c_str());
		}
	}
	else
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING_WITH_LINK, L"VIP以上用户才能使用道具", L"", L"", L"立即升级", GetRoomBusiness()->GetUpdateVipUrl().GetBuffer(0));
	}
}

void CRoomParentDlg::OnClickRoomShortCut( uint32 unRoomID )
{
	CSendEventManager::SendEnterRoomRequest(unRoomID);
}


void CRoomParentDlg::CreateSpeakerDlg(CString strInitContent, core::ENM_LoudSpeakerType enmType)
{
	SwitchResourceToModule(_T("Room"));
	if (m_pSpeakerDlg == NULL)
	{
		m_pSpeakerDlg = new CSpeakerDlg(this, enmType);
		if (m_pSpeakerDlg)
		{
			if (strInitContent != L"")
			{
				m_pSpeakerDlg->SetInitContent(strInitContent);
			}
			m_pSpeakerDlg->Create(CSpeakerDlg::IDD,NULL);
			int cx = GetSystemMetrics(SM_CXSCREEN);
			int cy = GetSystemMetrics(SM_CYSCREEN);
			m_pSpeakerDlg->SetWindowPos(NULL,cx/2 - SPEAKER_WIDTH/2,cy/2 - SPEAKER_HEIGHT/2,SPEAKER_WIDTH,SPEAKER_HEIGHT,SWP_SHOWWINDOW);
		}
	}
}


void CRoomParentDlg::CreateWishSpeakerDlg(CString strInitContent)
{
	SwitchResourceToModule(_T("Room"));
	if (m_pWishSpeakDlg == NULL)
	{
		m_pWishSpeakDlg = new CWishSpeakerDlg(this);
		if (m_pWishSpeakDlg)
		{
			if (strInitContent != L"")
			{
				m_pWishSpeakDlg->SetInitContent(strInitContent);
			}
			m_pWishSpeakDlg->Create(CWishSpeakerDlg::IDD,NULL);
			int cx = GetSystemMetrics(SM_CXSCREEN);
			int cy = GetSystemMetrics(SM_CYSCREEN);
			m_pWishSpeakDlg->SetWindowPos(NULL,cx/2 - SPEAKER_WIDTH/2,cy/2 - SPEAKER_HEIGHT/2,SPEAKER_WIDTH,SPEAKER_HEIGHT,SWP_SHOWWINDOW);
		}
	}
}

//私聊对话框按X按钮关闭
LRESULT CRoomParentDlg::OnPrivateMicDlgClose( WPARAM wParam ,LPARAM lParam ) 
{
	ClosePrivateMic( wParam ) ;
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.unUIN == wParam )
	{
		CSendEventManager::SendExitShow(m_uRoomID , EXIT_SHOW_OTHER );
		m_pRoomBusiness->OnUserStatusChange( wParam , USERSTATUSTYPE_PRIVATE , false ) ;
		GetHtmlOutPutManager()->InsertPrivateTips( L"【提示】： " , L"您已下私麦" , COLOR_OPERATE ) ;
	}
	else
	{
		CSendEventManager::SendClosePrivateEvent(m_uRoomID, wParam);
	}		
	return S_OK ;
}

LRESULT CRoomParentDlg::OnP2PMicDlgClose( WPARAM wParam ,LPARAM lParam )	//一对一私聊对话框关闭
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	GetHtmlOutPutManager()->OnExitP2P( myCurInfo.unUIN ) ;
	CloseP2PMic( wParam ) ;	
	CSendEventManager::SendExitShow(m_uRoomID , EXIT_SHOW_P2P );
	return S_OK ;
}

void CRoomParentDlg::PlutusAward( )
{
	std::vector<PlutusAwardInfo>::iterator vIter = m_vPlutusAwardMoneys.begin() ;
	if ( vIter != m_vPlutusAwardMoneys.end() )
	{
		PlutusAwardInfo plutusawardinfo = *vIter ;
		int unIndex = plutusawardinfo.unIndex ;
		if ( unIndex == 1 )
		{
			KillTimer( ROOM_CAISHEN_TIMER_FIRST_ID ) ;
			SetTimer( ROOM_CAISHEN_TIMER_INTERVAL_ID , ROOM_CAISHEN_TIMER_INTERVAL , NULL ) ;
		}

		uint32 nMoney = plutusawardinfo.vPlutusAwardMoneys[unIndex-1] ;
		m_pHtmlOutPutManager->PlutusAward( unIndex , nMoney ) ;

		CString strTemp ;
		strTemp.Format( L"钱PlutusAward unIndex=%d\r\n" , unIndex ) ;
		OutputDebugString( strTemp ) ;
		g_RoomModule->UpdatePlutusAwardOrLuckMoney( nMoney ) ;

		++ (vIter->unIndex );
		if ( vIter->unIndex > plutusawardinfo.vPlutusAwardMoneys.size() )
		{
			m_vPlutusAwardMoneys.erase( vIter ) ;
			KillTimer( ROOM_CAISHEN_TIMER_INTERVAL_ID ) ;
			if ( !m_vPlutusAwardMoneys.empty() )
			{
				std::vector<PlutusAwardInfo>::iterator vIter = m_vPlutusAwardMoneys.begin() ;
				m_pHtmlOutPutManager->OnNotifyPlutusAward( vIter->unSrcUIN , vIter->un179ID , vIter->strDecodeName , 
					vIter->strRoomName , vIter->vPlutusAwardMoneys , vIter->unGiftID ) ;
				GetEffectManager()->ProcessSendPlutus();
				SetTimer( ROOM_CAISHEN_TIMER_FIRST_ID , ROOM_CAISHEN_TIMER_FIRST_INTERVAL , NULL ) ;
			}
		}
	}
}

bool CRoomParentDlg::OutPutGift() 
{
	bool canOutputMoreone = false;

	//刷公屏
	list<GiftInfo>::iterator giftiter = m_vGiftInfoList.begin() ; 

	if ( m_nOutGiftIndex >= m_vGiftInfoList.size() )
	{
		m_nOutGiftIndex = 0 ;//刷完了一遍，索引重新置0

		if ( m_vGiftInfoList.empty() )
		{
			KillTimer( ROOM_GIFT_TIMER_ID ) ;
		}
	}

	advance( giftiter, m_nOutGiftIndex );	

	if ( giftiter != m_vGiftInfoList.end() )
	{
		//刷中奖信息
		std::map<uint32, std::list<LuckyInfo>>::iterator it = m_vLuckyInfoList.find(giftiter->time);

		if(it != m_vLuckyInfoList.end())
		{
			for ( list<LuckyInfo>::iterator luckyiter = it->second.begin() ; luckyiter != it->second.end() ; )
			{
				if ( --luckyiter->unIndex == 0 )
				{
					m_pHtmlOutPutManager->OutPutLucky( *luckyiter ) ;
					LuckyInfo luckinfo = *luckyiter;
					if (luckinfo.unLuckyTimes >= 500)
					{
						GetEffectManager()->ProcessLucky(luckinfo.src179ID, luckinfo.unLuckyTimes, luckinfo.strSrcName, L"", true);
					}
					luckyiter = it->second.erase( luckyiter ) ;
				}		
				else
				{
					++luckyiter ;
				}
			}

			if(it->second.size() == 0)
			{
				m_vLuckyInfoList.erase(it);
			}
		}

		//该条件下，进入作弊式输出
		canOutputMoreone = m_pHtmlOutPutManager->OutPutGift( *giftiter, 
			m_vGiftInfoList.size() > 1 && giftiter->unCount > ROOM_OUTPUTCHAT_PUBLIC_MAX_HOLD_LINE) ;

		if ( --(giftiter->unCount)== 0 )
		{
			m_vGiftInfoList.erase( giftiter ) ;
		}
		else
		{
			if (!canOutputMoreone)
			{
				++m_nOutGiftIndex ;
			}
		}
	}

	return canOutputMoreone;
}

void CRoomParentDlg::CreatePrivateMic( CString strSrcName ,uint32 srcuin , uint32 un179ID , uint16 nUserStatus ) 
{
	CPrivateMicDlg *pPrivateMicDlg = NULL ;
	map<uint32 , CPrivateMicDlg*>::iterator iter = m_mPrivateMicDlg.find( srcuin ) ;
	if (  iter == m_mPrivateMicDlg.end() )
	{
		SwitchResourceToModule(_T("Room"));
		int nPosX , nPosY ,nIndex ;
		m_pRoomBusiness->GetPrivateMicDlgPos( nPosX , nPosY , nIndex ) ;
		pPrivateMicDlg = new CPrivateMicDlg(this , nIndex ) ;
		pPrivateMicDlg->Create( CPrivateMicDlg::IDD , this ) ;
		pPrivateMicDlg->SetWindowPos( NULL , nPosX ,nPosY ,ROOM_PRIVATE_MIC_DLG_WIDTH ,ROOM_PRIVATE_MIC_DLG_HEIGTH , SWP_SHOWWINDOW ) ;
		m_mPrivateMicDlg[srcuin] = pPrivateMicDlg ;		
	}
	else
	{
		pPrivateMicDlg = iter->second ;
	}
	pPrivateMicDlg->Init( srcuin , un179ID , nUserStatus , strSrcName ) ;

}

void CRoomParentDlg::CreateP2PMic( uint32 UIN ) 
{
	IUserItem* pSrcUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( UIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ; 
	IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	m_pP2PChatDlg = new CP2PChatDlg(this , UIN );
	if (m_pP2PChatDlg)
	{
		int cx = GetSystemMetrics(SM_CXSCREEN);
		int cy = GetSystemMetrics(SM_CYSCREEN);
		int clientCx = 520;
		int clientCy = 306;
		SwitchResourceToModule(_T("Room"));
		m_pP2PChatDlg->Create(CP2PChatDlg::IDD,NULL);
		m_pP2PChatDlg->SetWindowPos(NULL,cx/2 - clientCx/2,cy/2 - clientCy/2,clientCx,clientCy,SWP_SHOWWINDOW);
		m_pP2PChatDlg->Init( pSrcUserItem->GetUserUIN() , pSrcUserItem->GetUser179ID() ,pSrcUserItem->GetUserStatus() , pSrcUserItem->GetUserName().c_str() ) ;
		m_pP2PChatDlg->InitMySelf( pUserItem->GetUserUIN() , pUserItem->GetUserStatus() ) ;
	}
}

void CRoomParentDlg::ClosePublicMic(uint32 UIN ) 
{
	//DeleteFansBtn(UIN);
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->ClosePublicMic( UIN ) ;
	m_pRoomTopManager->ClosePublicMic(UIN);

	//if (m_pOrderSongDlg != NULL && m_pOrderSongDlg->IsWindowVisible())
	//{
	//SendGetSongList();

	//m_pOrderSongDlg->InitHeadList(GetCurInfo().unUIN, 0, true);
	//}
}

BOOL CRoomParentDlg::ClosePrivateMic(uint32 UIN ) 
{
	map<uint32 , CPrivateMicDlg*>::iterator iter = m_mPrivateMicDlg.find( UIN ) ;
	if ( iter != m_mPrivateMicDlg.end() )
	{		
		CPrivateMicDlg* pPrivateMicDlg = iter->second ;
		m_pRoomBusiness->ErasePrivateMicDlgPos( pPrivateMicDlg->GetIndex() ) ;
		pPrivateMicDlg->CleanAVLogic() ;
		pPrivateMicDlg->DestroyWindow() ;
		delete pPrivateMicDlg ;
		m_mPrivateMicDlg.erase( iter ) ;
		return TRUE ;
	}
	return FALSE ;
}

void CRoomParentDlg::CloseP2PMic( uint32 UIN ) 
{
	if ( m_pP2PChatDlg != NULL && m_pP2PChatDlg->GetOppsiteUIN() == UIN )
	{		
		m_pP2PChatDlg->CleanAVLogic() ;
		m_pP2PChatDlg->DestroyWindow() ;
		delete m_pP2PChatDlg ;
		m_pP2PChatDlg = NULL ;
		m_pRoomBusiness->OnUserStatusChange( UIN , USERSTATUSTYPE_P2P , false ) ;
		core::CurInfo myCurInfo = GetCurInfo() ;
		m_pRoomBusiness->OnUserStatusChange( myCurInfo.unUIN , USERSTATUSTYPE_P2P , false ) ;		
	}
}

void CRoomParentDlg::SetRoomName()
{
	if ( m_pRoomBusiness->GetRoomOption() != NULL )
	{
		CString strRoomInfo ;		 
		strRoomInfo.Format( L" %s(%d)" , m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() , m_uRoomID ) ;
		CComVariant var = strRoomInfo;
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"textRoomInfo",L"text",var);

		core::CurInfo myCurInfo = GetCurInfo() ;
		if (myCurInfo.strName != L"")
		{
			strRoomInfo.Format( L"%s(%s)" ,myCurInfo.strName.c_str() , m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() ) ; //标题栏为 用户昵称(房间名)
			SetWindowText( strRoomInfo ) ;
		}
		else
		{
			strRoomInfo.Format( L"%d(%s)" ,myCurInfo.un179id , m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() ) ; //标题栏为 用户昵称(房间名)
			SetWindowText( strRoomInfo ) ;
		}

	}
}

void CRoomParentDlg::CloseMicPassive(  IUserItem* pSrcUserItem  ) 
{
	if ( pSrcUserItem->GetUserStatus()&USERSTATUSTYPE_PRIVATE )
	{
		if ( ClosePrivateMic( pSrcUserItem->GetUserUIN() ) )
		{
			CSendEventManager::SendClosePrivateEvent(m_uRoomID, pSrcUserItem->GetUserUIN());
		}
		CString strTemp ;
		strTemp.Format( L"%s已下私麦" , m_pHtmlOutPutManager->GetNameAndID(pSrcUserItem) ) ;

		m_pHtmlOutPutManager->InsertPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ;
	}
	else if ( pSrcUserItem->GetUserStatus()&USERSTATUSTYPE_PUBLIC_3 || pSrcUserItem->GetUserStatus()&USERSTATUSTYPE_PUBLIC_2 ||
		pSrcUserItem->GetUserStatus()&USERSTATUSTYPE_PUBLIC_1 )
	{
		ClosePublicMic( pSrcUserItem->GetUserUIN() ) ;
	}
}

void CRoomParentDlg::CloseP2PPassive( IUserItem* pSrcUserItem ) 
{
	if ( (pSrcUserItem->GetUserStatus()&USERSTATUSTYPE_P2P) && m_pP2PChatDlg != NULL )
	{
		GetHtmlOutPutManager()->OnExitP2P( m_pP2PChatDlg->GetOppsiteUIN() ) ;
		CloseP2PMic( m_pP2PChatDlg->GetOppsiteUIN() ) ;
	}
}

void CRoomParentDlg::CloseMicActive( IUserItem* pMyUserItem ) 
{
	if ( pMyUserItem->GetUserStatus()&USERSTATUSTYPE_PRIVATE )
	{
		ClosePrivateMic( pMyUserItem->GetUserUIN() ) ;		
		m_pRoomBusiness->OnUserStatusChange( pMyUserItem->GetUserUIN() ,USERSTATUSTYPE_PRIVATE  , false ) ;
	}
	else if ( pMyUserItem->GetUserStatus()&USERSTATUSTYPE_PUBLIC_3 || pMyUserItem->GetUserStatus()&USERSTATUSTYPE_PUBLIC_2 ||
		pMyUserItem->GetUserStatus()&USERSTATUSTYPE_PUBLIC_1 )
	{
		ClosePublicMic( pMyUserItem->GetUserUIN() ) ;
		m_pRoomBusiness->OnUserStatusChange( pMyUserItem->GetUserUIN() ,USERSTATUSTYPE_PUBLIC_1|USERSTATUSTYPE_PUBLIC_2|USERSTATUSTYPE_PUBLIC_3  , false ) ;
	}
	m_pRoomBusiness->OnUserStatusChange( pMyUserItem->GetUserUIN() , USERSTATUSTYPE_VIDEO , true ) ;
	m_pRoomBusiness->OnUserStatusChange( pMyUserItem->GetUserUIN() , USERSTATUSTYPE_AUDIO , false ) ;
}

void CRoomParentDlg::FangMai( bool bTips )  //放麦
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	IUserItem *pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
	if ( pUserItem != NULL )
	{
		if ( bTips )
		{
			GetHtmlOutPutManager()->OnExitShowSelf( pUserItem ) ;
		}
		CSendEventManager::SendExitShow(m_uRoomID , EXIT_SHOW_OTHER );
		CloseMicActive( pUserItem ) ;
		//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
		//m_pRoomLeftDlg->SetPaiMaiBtnStatus( PAIMAIBTN_ANY ) ;
		//m_pRoomLeftDlg->DisableBtnPaiMai() ;
		m_pRoomTopManager->SetPaiMaiBtnStatus(PAIMAIBTN_ANY);
		m_pRoomTopManager->DisableBtnPaiMai();
	}
}

void CRoomParentDlg::ShowKickDlg(uint8 unType) 
{
	if (m_pSelectUserItem == NULL)
	{
		return;
	}
	SwitchResourceToModule(_T("Room"));
	if (m_pKickDlg == NULL)
	{
		//创建房间个人设置窗口
		m_pKickDlg = new CKickDlg(this,m_pSelectUserItem->GetUserUIN(), unType);
		if (m_pKickDlg)
		{
			m_pKickDlg->Create(CKickDlg::IDD, NULL);
			int cx = GetSystemMetrics(SM_CXSCREEN);
			int cy = GetSystemMetrics(SM_CYSCREEN);
			m_pKickDlg->SetWindowPos(NULL,cx/2 - KICK_WIDTH/2,cy/2 - KICK_HEIGHT/2,KICK_WIDTH,KICK_HEIGHT,SWP_SHOWWINDOW);
			return;
		}
	}
	if (m_pKickDlg != NULL && m_pKickDlg->GetSafeHwnd())
	{
		m_pKickDlg->SetKickType(unType);
		m_pKickDlg->SetKickDstUIN(m_pSelectUserItem->GetUserUIN());
		m_pKickDlg->ShowWindow(SW_SHOW);
		m_pKickDlg->SetForegroundWindow();
	}
}

bool CRoomParentDlg::InitAVLogic( uint32 unRoomID ,uint32 uRelayIP ,uint32 uRelayPort ,uint32 iKey , RoomModule& Module ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	m_pRoomAvLogic = new RoomAVLogic( unRoomID ,myCurInfo.unUIN ,Module ) ;
	if ( m_pRoomAvLogic == NULL )
	{
		return FALSE ;
	}
	else
	{
		m_pRoomAvLogic->InitMixerControl(GetSafeHwnd());
		m_pRoomAvLogic->SetAudioCfg( 0 , 0 ) ;
		m_pRoomAvLogic->SetVideoCfg( CPersonalConfig::GetInstance()->GetUseVideoDeviceIndex() , 240 , 320 , 26 ) ;
		m_pRoomAvLogic->SetKeyCfg( iKey ) ;
		m_pRoomAvLogic->ConnectRelayServer( uRelayIP , uRelayPort ) ;		
		return TRUE ;
	}	
}

void CRoomParentDlg::RestRelayServer( uint32 uRelayIP ,uint32 uRelayPort ) 
{
	if ( m_pRoomAvLogic != NULL )
	{
		m_pRoomAvLogic->ChangeRelayServer( uRelayIP , uRelayPort ) ;
	}
}

void CRoomParentDlg::SetRoomMicVolume( uint32 unMicVolume ) 
{
	m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->SetRoomMicVolume(unMicVolume);
}

void CRoomParentDlg::CloseMic() 
{
	/*if ( m_pRoomAvLogic != NULL )
	{
	CComVariant var = false;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgMicOn",L"visible",var);
	var = true;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgMicOff",L"visible",var);
	m_pRoomAvLogic->SetAllMicMute( true ) ;
	}*/
	//DragonZ: V2.21版本后用，新布局
	m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->CloseMic();
}

void CRoomParentDlg::OpenMic() 
{
	/*if ( m_pRoomAvLogic != NULL )
	{
	CComVariant var = true;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgMicOn",L"visible",var);
	var = false;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgMicOff",L"visible",var);
	m_pRoomAvLogic->SetAllMicMute( false ) ;
	}*/
	//DragonZ: V2.21版本后用，新布局
	m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->OpenMic();
}

void CRoomParentDlg::SetAllVideoCfg( int iDevice ) 
{
	if ( m_pRoomAvLogic != NULL )
	{
		m_pRoomAvLogic->SetVideoCfg( iDevice , 240 , 320 , 26 ) ;
	}
}

void CRoomParentDlg::OnUpdateMoney( uint32 lMoney , BOOL bFirstInit )	//更新钱币
{
	m_pRoomRightDlg->OnUpdateMoney( lMoney , bFirstInit ) ;
	//SetRichLevelTip();
	m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->SetRichLevelTip();
}

void CRoomParentDlg::InitPublicMic( std::vector<room_user_info>& vecPubMic ) 
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	/*if ( m_pRoomLeftDlg != NULL )
	{
	m_pRoomLeftDlg->InitPublicMic( vecPubMic ) ;
	}*/
	if (m_pRoomTopManager != NULL)
	{
		m_pRoomTopManager->InitPublicMic(vecPubMic);
	}
}

//用户信息(在线)
void CRoomParentDlg::OnUserInfo( IUserItem* pUserItem ) 
{
	if ( pUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.enmVIPLevel ==  core::VIPLEVEL_NONE )
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能查看详细信息，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
		return ;
	}

	SwitchResourceToModule(_T("Room"));	
	if ( myCurInfo.unUIN == pUserItem->GetUserUIN() )
	{
		//显示自己的用户信息		
		if ( m_pUserInfoDlg == NULL )
		{
			m_pUserInfoDlg = new CSysSettingDlg(this) ;
			m_pUserInfoDlg->Create( CSysSettingDlg::IDD , this ) ;
		}

		m_pUserInfoDlg->OpenDlg( Show_User_Info_Dlg ) ;
		m_pUserInfoDlg->SetToPersonalSetting() ;
		m_pUserInfoDlg->ShowWindow(SW_SHOW);

	}
	else
	{
		//显示他人的用户信息
		if ( m_pOtherUserInfoDlg == NULL )
		{
			m_pOtherUserInfoDlg = new COtherUserInfoDlg(this);
			m_pOtherUserInfoDlg->Create( COtherUserInfoDlg::IDD , this ) ;			
		}

		OtherUserInfo oUserInfo;
		oUserInfo.m_UserUin = pUserItem->GetUserUIN();
		oUserInfo.m_UserAccount = pUserItem->GetUser179ID();
		oUserInfo.m_Gender = pUserItem->IsMale();
		oUserInfo.m_UserRoleName = pUserItem->GetUserName();
		oUserInfo.m_VipLevel = pUserItem->GetUserVipLevel();
		oUserInfo.m_RichLevel = pUserItem->GetUserRichLevel();
		oUserInfo.m_IsActor = pUserItem->IsActor();
		oUserInfo.m_IsAgent = pUserItem->IsAgent();
		m_pOtherUserInfoDlg->SetUserInfo(oUserInfo);
		m_pOtherUserInfoDlg->ShowWindow(SW_SHOW);
	}
}

//其他用户信息(在线或离线)
void CRoomParentDlg::OnOtherUserInfo(uint32 unUIN,bool isMan,bool IsActor)
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.enmVIPLevel ==  core::VIPLEVEL_NONE )
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能查看详细信息，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
		return ;
	}

	SwitchResourceToModule(_T("Room"));	
	if ( myCurInfo.unUIN == unUIN )
	{
		//显示自己的用户信息		
		if ( m_pUserInfoDlg == NULL )
		{
			m_pUserInfoDlg = new CSysSettingDlg(this) ;
			m_pUserInfoDlg->Create( CSysSettingDlg::IDD , this ) ;
		}

		m_pUserInfoDlg->OpenDlg( Show_User_Info_Dlg ) ;
		m_pUserInfoDlg->SetToPersonalSetting() ;
		m_pUserInfoDlg->ShowWindow(SW_SHOW);

	}
	else
	{
		//显示他人的用户信息
		if ( m_pOtherUserInfoDlg == NULL )
		{
			m_pOtherUserInfoDlg = new COtherUserInfoDlg(this);
			m_pOtherUserInfoDlg->Create( COtherUserInfoDlg::IDD , this ) ;			
		}

		OtherUserInfo oUserInfo;
		oUserInfo.m_UserUin = unUIN;
		oUserInfo.m_UserAccount = 0;
		oUserInfo.m_Gender = isMan;
		oUserInfo.m_UserRoleName = _T("");
		oUserInfo.m_VipLevel = 0;
		oUserInfo.m_RichLevel = 0;
		oUserInfo.m_IsActor = IsActor;
		oUserInfo.m_IsAgent = false;
		m_pOtherUserInfoDlg->SetUserInfo(oUserInfo);
		m_pOtherUserInfoDlg->ShowWindow(SW_SHOW);

	}
	
}

void CRoomParentDlg::OnHallHeadImageUpdate(uint32 unUIN) 
{
	if ( m_pUserInfoCardDlg != NULL && m_pUserInfoCardDlg->IsWindowVisible() )
	{
		m_pUserInfoCardDlg->OnHallHeadImageUpdate() ;
	}
	if(m_pUserInfoDlg != NULL && m_pUserInfoDlg->IsWindowVisible())
	{		
		m_pUserInfoDlg->OnGetHeadImage(unUIN);
	}
	if(m_pOtherUserInfoDlg != NULL && m_pOtherUserInfoDlg->IsWindowVisible())
	{
		m_pOtherUserInfoDlg->OnGetHeadImage(unUIN);
	}
	if(m_pRoomTopManager != NULL)
	{
		m_pRoomTopManager->OnHallHeadImageUpdate(unUIN);
	}
	if (GetCurInfo().unUIN == unUIN)
	{
		OnMyHeadImgUpdate();
	}

	GetRoomBusiness()->GetSofaManager()->UpdateSofaHead(unUIN);

	IUserItem * pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN(unUIN);
	if (pUserItem != NULL && pUserItem->GetPublicMicIndex() != 0)
	{
		Hall::HeadImage headImage ;
		headImage.m_bMan = pUserItem->IsMale() ;
		headImage.m_unUIN = pUserItem->GetUserUIN() ;	
		headImage.m_isGuest = false;
		g_RoomModule->m_pModuleManager->CallService(Hall::SERVICE_VALUE_HALL_GET_HEAD_IMAGE_PATH, (param)&headImage);
		m_pRoomBusiness->GetOrderSongManager()->AddActorInfo(pUserItem->GetPublicMicIndex(), pUserItem->GetUserUIN(), pUserItem->GetUserName(), headImage.m_HeadImagePath);

		if (m_pOrderSongDlg != NULL)
		{
			m_pOrderSongDlg->InitHeadList(GetCurInfo().unUIN, 0, true);
		}
	}
}

void CRoomParentDlg::AddGiftInfo( uint32 srcuin , uint32 dstuin , uint32 unCount , 
								 uint16 unGiftid , uint16 unType, uint32 time )  
{
	IUserItem* pSrcItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcItem == NULL )
	{
		return ;
	}
	IUserItem* pDstItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstItem == NULL )
	{
		return ;
	}
	if ( unCount != 0  )
	{
		AdjustGiftBaseListCountAndGiftInfoList( dstuin , unGiftid ) ;

		GiftInfo giftinfo ;
		giftinfo.srcuin = srcuin ;
		giftinfo.strSrcName = pSrcItem->GetDecodeUserName() ;
		giftinfo.src179ID = pSrcItem->GetUser179ID() ;
		giftinfo.strSrcHead = m_pHtmlOutPutManager->GetUserHead( pSrcItem ) ;

		giftinfo.dstuin = dstuin ;
		giftinfo.strDstName = pDstItem->GetDecodeUserName() ;
		giftinfo.dst179ID = pDstItem->GetUser179ID() ;
		giftinfo.strDstHead = m_pHtmlOutPutManager->GetUserHead( pDstItem ) ;

		giftinfo.unCount = unCount ;
		giftinfo.unGiftid = unGiftid ;
		giftinfo.unType = unType ;
		giftinfo.time = time;

		m_vGiftInfoList.push_back( giftinfo ) ;

		if ( m_vGiftInfoList.size() == 1 )
		{
			SetTimer( ROOM_GIFT_TIMER_ID , ROOM_GIFT_TIMER_INTERVAL , NULL ) ;
		}
	}
}

void CRoomParentDlg::CreateLuckyInfoList( uint32 srcuin , uint32 dstuin ,uint32 unCount ,uint16 unGiftid,
										 std::vector<SendGiftLuckyInfo>& vecLuckyInfo, uint32 time )
{
	if ( vecLuckyInfo.empty() )
	{
		return ;
	}
	IUserItem* pSrcItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcItem == NULL )
	{
		return ;
	}

	std::list<LuckyInfo> luckList;

	for (std::vector<SendGiftLuckyInfo>::iterator LuckyInfoIter = vecLuckyInfo.begin() ; LuckyInfoIter != vecLuckyInfo.end() ; ++LuckyInfoIter )
	{
		LuckyInfo luckyinfo ;
		luckyinfo.srcuin = srcuin ;
		luckyinfo.strSrcHead = m_pHtmlOutPutManager->GetUserHead(pSrcItem) ;
		luckyinfo.strSrcLuckyHead = m_pHtmlOutPutManager->GetUserItemHeadImg( pSrcItem ) ;
		luckyinfo.src179ID = pSrcItem->GetUser179ID() ;
		luckyinfo.dstuin = dstuin ;
		luckyinfo.strSrcName = pSrcItem->GetDecodeUserName() ;
		luckyinfo.unGiftid = unGiftid ;
		luckyinfo.unIndex = LuckyInfoIter->unLuckyIndex ;
		luckyinfo.unLuckyMoney = LuckyInfoIter->unLuckyMoney ;
		luckyinfo.unLuckyTimes = LuckyInfoIter->unLuckyTimes ;
		luckList.push_back( luckyinfo ) ;
	}

	if(m_vLuckyInfoList.find(time) != m_vLuckyInfoList.end())
	{
		assert(0);
	}

	m_vLuckyInfoList[time] = luckList;
}

void CRoomParentDlg::OnNotifyPlutusAward( uint32 unSrcUIN , uint32 un179ID ,std::wstring& strDecodeName ,
										 std::wstring strRoomName ,std::vector<uint16>& vecMoneys , uint32 unGiftID ) 
{
	if ( vecMoneys.empty() )
	{
		return ;
	}
	PlutusAwardInfo plutusawardinfo ;
	plutusawardinfo.unIndex = 1 ;
	plutusawardinfo.unSrcUIN = unSrcUIN ;
	plutusawardinfo.un179ID = un179ID ;
	plutusawardinfo.strDecodeName = strDecodeName ;
	plutusawardinfo.unGiftID = unGiftID ;
	plutusawardinfo.vPlutusAwardMoneys = vecMoneys ;

	m_vPlutusAwardMoneys.push_back( plutusawardinfo ) ;
	if ( m_vPlutusAwardMoneys.size() == 1 )
	{
		m_pHtmlOutPutManager->OnNotifyPlutusAward( unSrcUIN , un179ID , strDecodeName , strRoomName , vecMoneys , unGiftID ) ;
		SetTimer( ROOM_CAISHEN_TIMER_FIRST_ID , ROOM_CAISHEN_TIMER_FIRST_INTERVAL , NULL ) ;
		GetEffectManager()->ProcessSendPlutus();
	}
	//DrawPng( DRAW_PLUTUS ) ;
}


int CRoomParentDlg::GetSenToComboInfo(vector<SenToComboInfo>& vSenToComboInfoList ) 
{
	return m_pRoomRightDlg->GetSenToComboInfo( vSenToComboInfoList ) ;
} 

uint32 CRoomParentDlg::GetGiftBaseListCount( uint32 unDstuin ,uint32 unGiftid ) 
{
	map<uint32 ,map<uint32 ,RecvGiftCountInfo > >:: iterator iter = m_mGiftBaseList.find( unDstuin ) ;
	if ( iter != m_mGiftBaseList.end() )
	{
		map< uint32 , RecvGiftCountInfo >::iterator giftcountiter = iter->second.find( unGiftid ) ;
		if ( giftcountiter != iter->second.end() )
		{
			++giftcountiter->second.unCount ;
			return giftcountiter->second.unCount ;
		}
		else
		{
			RecvGiftCountInfo recvcountinfo ;
			recvcountinfo.unCount = 1 ;
			recvcountinfo.bNewEnter = false ;
			iter->second.insert( make_pair( unGiftid , recvcountinfo ) ) ;
			return 1 ;
		}
	}
	else
	{
		map<uint32 , RecvGiftCountInfo > mGiftCount ;
		RecvGiftCountInfo recvcountinfo ;
		recvcountinfo.unCount = 1 ;
		recvcountinfo.bNewEnter = false ;
		mGiftCount.insert( make_pair( unGiftid , recvcountinfo ) ) ;
		m_mGiftBaseList.insert( make_pair( unDstuin , mGiftCount ) ) ;
		return 1 ;
	}
}

//退出房间再重新进入的用户，再收到同一礼物时将 刷新礼物的基数清零,并将以前未刷完的信息清除
void CRoomParentDlg::AdjustGiftBaseListCountAndGiftInfoList( uint32 unDstuin ,uint32 unGiftid ) 
{
	map<uint32 ,map<uint32 ,RecvGiftCountInfo > >:: iterator iter = m_mGiftBaseList.find( unDstuin ) ;
	if ( iter != m_mGiftBaseList.end() )
	{
		map< uint32 , RecvGiftCountInfo >::iterator giftcountiter = iter->second.find( unGiftid ) ;
		if ( giftcountiter != iter->second.end() )
		{
			if ( giftcountiter->second.bNewEnter )
			{
				giftcountiter->second.unCount = 0 ;
				giftcountiter->second.bNewEnter = false ;

				list<GiftInfo>::iterator giftinfoiter ;
				for ( giftinfoiter = m_vGiftInfoList.begin() ; giftinfoiter !=m_vGiftInfoList.end() ; )
				{
					if ( giftinfoiter->dstuin == unDstuin && giftinfoiter->unGiftid == unGiftid )
					{
						giftinfoiter = m_vGiftInfoList.erase( giftinfoiter ) ;
					}
					else
					{
						++giftinfoiter ;
					}
				}

				for ( std::map<uint32, std::list<LuckyInfo>>::iterator it = m_vLuckyInfoList.begin() ; 
					it != m_vLuckyInfoList.end();)
				{
					std::list<LuckyInfo>& listLucky = it->second;

					std::list<LuckyInfo>::iterator luckyiter = listLucky.begin(); 

					if(luckyiter != listLucky.end())
					{
						if ( luckyiter->dstuin == unDstuin && luckyiter->unGiftid == unGiftid )
						{
							it = m_vLuckyInfoList.erase(it);
						}
						else
						{
							++it;
							break;
						}
					}
				}
			}
		}
	}
}

uint32 CRoomParentDlg::GetPulicMicUINByIndex( int nIndex ) 
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//return m_pRoomLeftDlg->GetPulicMicUINByIndex( nIndex ) ;
	return m_pRoomTopManager->GetPulicMicUINByIndex(nIndex);
}

void CRoomParentDlg::SetSendObj( CString strName , uint32 unUIN ) 
{
	m_pRoomRightDlg->SetSendObj( strName , unUIN ) ;
	//DragonZ:跑道移到RoomParentDlg
	//m_pRoomMidDlg->SetSendObj( strName , unUIN ) ;
	if ( m_pPaodaoStatic != NULL )
	{
		m_pPaodaoStatic->OnClickNameLink( strName , unUIN ) ;
	}	
}

void CRoomParentDlg::SetChatObj( CString strName , uint32 unUIN ) 
{
	m_pRoomMidDlg->SetChatObj( strName , unUIN ) ;
}

void CRoomParentDlg::BackMessage( UINT32 dstuin , MessageFont& stFont , std::wstring strText , ENM_SendMessageType enmType , bool bAutoMsg) 
{
	m_pRoomMidDlg->BackMessage( dstuin , stFont , strText , enmType , bAutoMsg) ;
}

bool CRoomParentDlg::GetAMessageBack( SendMessageEvent& message )
{
	return m_pRoomMidDlg->GetAMessageBack( message ) ;
}

void CRoomParentDlg::SetPublicOutputGotoEndAble( BOOL bAble ) 
{
	m_pRoomMidDlg->SetPublicOutputGotoEndAble( bAble ) ;
}

void CRoomParentDlg::SetPrivateOutputGotoEndAble( BOOL bAble ) 
{
	m_pRoomMidDlg->SetPrivateOutputGotoEndAble( bAble ) ;
}

void CRoomParentDlg::SetSpeakerOutputGotoEndAble( BOOL bAble ) 
{
	m_pRoomRightDlg->SetSpeakerOutputGotoEndAble( bAble ) ;
}

void CRoomParentDlg::OnRoomRightSendToChange( CString& strSelText ) 
{
	//DragonZ:跑道移到RoomParentDlg
	//m_pRoomMidDlg->OnRoomRightSendToChange( strSelText ) ;
	if (m_pPaodaoStatic != NULL)
	{
		m_pPaodaoStatic->OnRoomRightSendToChange( strSelText ) ;
	}
}

void CRoomParentDlg::OnPaodaoSendToChange( CString& strSelText ) 
{
	m_pRoomRightDlg->OnPaodaoSendToChange( strSelText ) ;
}

//DragonZ:跑道移到RoomParentDlg
void CRoomParentDlg::InsertPaoDaoText(CString strSrcName , CString strDstName , CString strGiftWord , uint32 unSrc179ID , 
									  uint32 unDst179ID ,  uint16 unGiftID ,uint16 unCount , CString& strTime ) 
{
	//DragonZ:跑道移到RoomParentDlg
	/*m_pRoomMidDlg->InsertPaoDaoText( strSrcName , strDstName , strGiftWord ,unSrc179ID , 
	unDst179ID , unGiftID , unCount , strTime ) ;*/

	if (m_pPaodaoStatic != NULL)
	{
		m_pPaodaoStatic->InsertPaoDaoText( strSrcName , strDstName ,strGiftWord , unSrc179ID , unDst179ID , unGiftID , unCount , strTime );
	}
}

void CRoomParentDlg::InsertPrivateText(CString& strText )  //插入私屏且窗口最小化时闪烁窗口
{
	m_pRoomMidDlg->InsertPrivateText( strText ) ;
	FlashRoomWindow() ;
}


void CRoomParentDlg::InsertPublicText(CString& strText ) 
{
	m_pRoomMidDlg->InsertPublicText( strText ) ;
}

void CRoomParentDlg::InsertSpeakerText(CString& strText ) 
{
	//m_pRoomRightDlg->InsertSpeakerText( strText ) ;
	m_pSpeakerHtml->InsertText(strText);
	m_pSpeakerHtml->ShowWindow(SW_SHOW);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomSpeakerBK", L"visible", (CComVariant)true);
}

void CRoomParentDlg::FlashRoomWindow() 
{
	if ( IsIconic() )
	{
		FlashWindow( TRUE ) ;
		SetTimer( ROOM_FLASH_WINDOW_TIMER , ROOM_FLASH_WINDOW_INTERVAL , NULL ) ;
	}
}

void CRoomParentDlg::OnRequestShow_NeedSelect()
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->OnRequestShow_NeedSelect() ;
	m_pRoomTopManager->OnRequestShow_NeedSelect();
}

void CRoomParentDlg::OnRequestShow_Failed() 
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->OnRequestShow_Failed() ;
	m_pRoomTopManager->OnRequestShow_Failed();
}

void CRoomParentDlg::OnRequestShow_Public( uint8 unIndex , uint32 unTime ) //自己排上公麦
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->OnRequestShow_Public( unIndex , unTime ) ;
	m_pRoomTopManager->OnRequestShow_Public(unIndex, unTime);

	IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( GetCurInfo().unUIN ) ;
	if (pUserItem != NULL && pUserItem->IsActor())//如果自己是艺人
	{
		DrawBtnFans(unIndex);
		//DrawBtnUnDealSong(unIndex, 2);

		//如果自己是艺人且上麦
		if (GetCurInfo().unUIN == pUserItem->GetUserUIN())
		{
			CSendEventManager::SendGetOrderListEvent(m_uRoomID);
		}
	}
}

void CRoomParentDlg::OnRequestShow_WaitingList()
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->OnRequestShow_WaitingList() ;
	m_pRoomTopManager->OnRequestShow_WaitingList();
}

void CRoomParentDlg::OnRequestShow_PublicNotify( uint32 unSrcUIN , uint8 unIndex , uint16 unTime ) //别人排上公麦
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->OnRequestShow_PublicNotify( unSrcUIN , unIndex , unTime ) ;
	m_pRoomTopManager->OnRequestShow_PublicNotify(unSrcUIN, unIndex, unTime);

	IUserItem* pUserIterm = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if (pUserIterm != NULL && pUserIterm->IsActor())//如果上公麦的是艺人
	{
		DrawBtnFans(unIndex);
		//DrawBtnUnDealSong(unIndex);
	}
}

void CRoomParentDlg::OnRequestShow_Private()
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	IUserItem* pUserIterm = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
	if ( pUserIterm != NULL )
	{
		CreatePrivateMic( pUserIterm->GetUserName().c_str() , pUserIterm->GetUserUIN() , pUserIterm->GetUser179ID() ,pUserIterm->GetUserStatus() ) ;
		//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
		//m_pRoomLeftDlg->OnRequestShow_Private() ;
		m_pRoomTopManager->OnRequestShow_Private();
	}
}

void CRoomParentDlg::OnExitShowNotify( uint32 srcuin , int nType )
{
	IUserItem* pSrcUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	if ( nType == EXIT_SHOW_OTHER )
	{
		CloseMicPassive( pSrcUserItem ) ;
		//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
		//m_pRoomLeftDlg->OnExitShowNotify( srcuin ) ;
		m_pRoomTopManager->OnExitShowNotify(srcuin);
	}
	else
	{
		CloseP2PPassive( pSrcUserItem ) ;
	}
}

void CRoomParentDlg::OnOpenPrivate( uint32 unDstUIN )
{
	IUserItem* pDstUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	CreatePrivateMic( pDstUserItem->GetUserName().c_str() , unDstUIN , pDstUserItem->GetUser179ID() ,pDstUserItem->GetUserStatus() ) ;
}


void CRoomParentDlg::OnPushOnShow_Success( uint32 unDstUIN , uint8 unIndex ) //邀请上麦成功
{
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->OnPushOnShow_Success( unDstUIN , unIndex ) ;
	m_pRoomTopManager->OnPushOnShow_Success(unDstUIN, unIndex);

	IUserItem * pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if (pUserItem != NULL && pUserItem->IsActor())//如果上公麦的是艺人
	{
		DrawBtnFans(unIndex);
		//DrawBtnUnDealSong(unIndex, 2);

		//如果自己是艺人且上麦
		if (GetCurInfo().unUIN == pUserItem->GetUserUIN())
		{
			CSendEventManager::SendGetOrderListEvent(m_uRoomID);
		}
	}
}

void CRoomParentDlg::OnPullOffShowRsp_Success( uint32 unDstUIN )
{
	IUserItem* pDstUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	CloseMicPassive( pDstUserItem ) ;
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->OnPullOffShowRsp_Success( pDstUserItem ) ;
	m_pRoomTopManager->OnPullOffShowRsp_Success(pDstUserItem);
}

void CRoomParentDlg::OnOpVideoAudioRsp( uint32 nOpAVType ,uint32 unUIN )
{
	IUserItem* pSrcUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	map<uint32 , CPrivateMicDlg*>::iterator iter = m_mPrivateMicDlg.find( unUIN ) ;
	if ( iter != m_mPrivateMicDlg.end() )
	{
		CPrivateMicDlg* pPrivateMicDlg = iter->second ;
		pPrivateMicDlg->OnOpVideoAudioRsp(nOpAVType , unUIN ) ;
	}
	else
	{
		core::CurInfo myCurInfo = GetCurInfo() ;
		uint16 nIndex = pSrcUserItem->GetPublicMicIndex() ;
		if ( nIndex != 0 )
		{
			//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
			//m_pRoomLeftDlg->OnOpVideoAudioRsp( nIndex , nOpAVType , unUIN ) ;
			m_pRoomTopManager->OnOpVideoAudioRsp(nIndex, nOpAVType, unUIN);
		}
		else if ( (pSrcUserItem->GetUserStatus()&USERSTATUSTYPE_P2P) && m_pP2PChatDlg!= NULL 
			&& (m_pP2PChatDlg->GetOppsiteUIN() == unUIN || myCurInfo.unUIN == unUIN) )
		{
			m_pP2PChatDlg->OnOpVideoAudioRsp( nOpAVType , unUIN ) ;
		}
	}
}

void CRoomParentDlg::OnOpVideoAudioNotify( uint32 nOpAVType ,uint32 unUIN )
{
	IUserItem* pSrcUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	map<uint32 , CPrivateMicDlg*>::iterator iter = m_mPrivateMicDlg.find( unUIN ) ;
	if ( iter != m_mPrivateMicDlg.end() )
	{
		CPrivateMicDlg* pPrivateMicDlg = iter->second ;
		pPrivateMicDlg->OnOpVideoAudioNotify(nOpAVType , unUIN ) ;
	}
	else
	{
		core::CurInfo myCurInfo = GetCurInfo() ;
		uint16 nIndex = pSrcUserItem->GetPublicMicIndex() ;
		if ( nIndex != 0 )
		{
			//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
			//m_pRoomLeftDlg->OnOpVideoAudioNotify( nIndex , nOpAVType , unUIN ) ;
			m_pRoomTopManager->OnOpVideoAudioNotify(nIndex, nOpAVType, unUIN);
		}
		else if ( (pSrcUserItem->GetUserStatus()&USERSTATUSTYPE_P2P) && m_pP2PChatDlg!= NULL
			&& (m_pP2PChatDlg->GetOppsiteUIN() == unUIN || myCurInfo.unUIN == unUIN) )
		{
			m_pP2PChatDlg->OnOpVideoAudioNotify( nOpAVType , unUIN ) ;
		}
	}
}


void CRoomParentDlg::OnRespnseP2PNotifyAccept( uint32 unSrcUIN )  //一对一私聊
{
	CreateP2PMic( unSrcUIN ) ;
}


void CRoomParentDlg::OnNotifyPrivateShow( std::vector<uint32>& vecUIN)
{
	vector<uint32>::iterator iter ;
	for ( iter = vecUIN.begin() ; iter != vecUIN.end() ; ++iter )
	{
		IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( *iter ) ;
		if ( pUserItem != NULL )
		{
			CreatePrivateMic( pUserItem->GetUserName().c_str() , pUserItem->GetUserUIN() ,pUserItem->GetUser179ID() , pUserItem->GetUserStatus() ) ;
		}
	}
}

void CRoomParentDlg::OnSignature(  ) 
{
	std::wstring strSignature =  m_pRoomBusiness->GetRoomOption()->GetRoomSignature() ;
	vector<common::ui::tickerInfo> vtickerVec;   
	common::ui::tickerInfo newTicker;	
	newTicker.m_Message = strSignature.c_str() ;
	m_pHtmlOutPutManager->ProcessRecvMsgText( newTicker.m_Message ) ;	
	vtickerVec.push_back(newTicker);
	m_RoomTitleTicker.RunTicker( vtickerVec ,100 ) ;
	//DragonZ
	//房间主题 
	CComVariant varTitle = strSignature.c_str();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textRoomAnnounce", L"text", varTitle);
}

void CRoomParentDlg::OutPutNoticeMsg( ) //进房间时的房间公告
{
	std::vector<std::wstring> vNoticeList = m_pRoomBusiness->GetRoomOption()->GetRoomNotice() ;
	std::vector<std::wstring>::iterator iter ;
	for ( iter = vNoticeList.begin() ; iter != vNoticeList.end() ; ++iter )
	{
		m_pHtmlOutPutManager->OnNoticeMsg( L" "+CString( iter->c_str() ) ) ;
	}
}


void CRoomParentDlg::OnWelecomeWords( ) 
{	
	m_pHtmlOutPutManager->OnWelecomeWords( GetRoomBusiness()->GetRoomOption() ) ;
	OnActorSpeak();
	OnAgentSpeak();

	//GetEffectManager()->ProcessLuckyStar(L"陆文辉haha001", L"(191234234)");
	//GetEffectManager()->ProcessLucky(500, L"sdfsd<</>>sdfs", L"191234234", false);
}


void CRoomParentDlg::OnSetRoomInfo( uint32 unSrcUIN ) 
{
	RoomOption *pRoomOption = m_pRoomBusiness->GetRoomOption() ;
	if ( pRoomOption != NULL )
	{
		if ( pRoomOption->IsPublicChatChange() )
		{			
			m_pHtmlOutPutManager->OnPublicChatChange( pRoomOption->GetPublicChatType() , unSrcUIN ) ;
		}
		if ( pRoomOption->IsColorTextChange() )
		{
			m_pHtmlOutPutManager->OnColorTextChange( pRoomOption->CanColorText() , unSrcUIN ) ;
		}
		if ( pRoomOption->IsFreeShowChange() )
		{
			m_pHtmlOutPutManager->OnFreeShowChange( pRoomOption->CanFreeShow() , unSrcUIN ) ;
		}
		if ( pRoomOption->IsSignatureChange() )
		{
			OnSignature() ;
		}
	}
}

void CRoomParentDlg::OnGetUserList( std::map<uint32, IUserItem*> & mapAllUser )
{

}

void CRoomParentDlg::OnGetAdminList( std::map<uint32, IUserItem*> & mapAdminUser )
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnGetAdminList(mapAdminUser);
	}
}

void CRoomParentDlg::OnGetWaitingList( std::map<uint32, IUserItem*> & mapWaitingUser )
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnGetWaitingList(mapWaitingUser);
	}
}

void CRoomParentDlg::OnAddUser( IUserItem * pUserItem )
{
	/*if ( m_pRoomLeftDlg )
	{
	m_pRoomLeftDlg->OnAddUser( pUserItem ) ;
	}*/
	if (m_pRoomMidDlg)
	{
		m_pRoomMidDlg->OnAddUser(pUserItem);
	}
	if (m_pRoomRightDlg)
	{
		m_pRoomRightDlg->OnAddUser(pUserItem);
	}
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnAddUser(pUserItem);
		m_pRoomBottomLeftDlg->OnAddUserIsMgr(pUserItem);
	}

	if (pUserItem->GetUserUIN() == GetCurInfo().unUIN)
	{
		AddBottomUserInfo();

		if (pUserItem->GetUserVipLevel() == core::VIPLEVEL_TOP)
		{
			GetEffectManager()->ProcessVipTop(pUserItem->GetUserName(), pUserItem->GetUser179ID());
		}

		if (pUserItem->IsLuckyStar())
		{
			GetEffectManager()->ProcessLuckyStar(pUserItem->GetUserName(), pUserItem->GetUser179ID());
		}

		if (!pUserItem->IsOfficial())
		{
			ShowGuide();
		}		
	}

	if(m_pRoomTopManager)
	{
		m_pRoomTopManager->OnAddUser(pUserItem);
	}

}

void CRoomParentDlg::OnUpdateUser( IUserItem * pUserItem )
{
	/*if ( m_pRoomLeftDlg )
	{
	m_pRoomLeftDlg->OnUpdateUser( pUserItem ) ;
	}*/
	if (m_pRoomMidDlg)
	{
		m_pRoomMidDlg->OnUpdateUser(pUserItem);
	}
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnUpdateUser(pUserItem);
		m_pRoomBottomLeftDlg->OnUpdateUserIsMgr(pUserItem);
	}
}

void CRoomParentDlg::OnDeleteUser( IUserItem * pUserItem )
{
	if ( m_pSelectUserItem != NULL && m_pSelectUserItem->GetUserUIN() == pUserItem->GetUserUIN() )
	{
		m_pSelectUserItem = NULL ;
	}
	CloseMicPassive( pUserItem ) ;

	if (m_pRoomMidDlg)
	{
		m_pRoomMidDlg->OnDeleteUser(pUserItem);
	}
	//DragonZ:跑道移到RoomParentDlg
	if (m_pPaodaoStatic != NULL)
	{
		m_pPaodaoStatic->OnDeleteUser(pUserItem);
	}

	if (m_pRoomRightDlg)
	{
		m_pRoomRightDlg->OnDeleteUser(pUserItem);
	}
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnDeleteUser(pUserItem);
	}

	m_pHtmlOutPutManager->OnLeaveRoom(pUserItem->GetUserUIN());

	if(m_pRoomTopManager)
	{
		m_pRoomTopManager->OnDeleteUser(pUserItem);
	}
}

void CRoomParentDlg::OnAddAdminUser( IUserItem * pUserItem )
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnAddAdminUser(pUserItem);
	}
}

void CRoomParentDlg::OnDeleteAdminUser( IUserItem * pUserItem )
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnDeleteAdminUser(pUserItem);
	}
}

void CRoomParentDlg::OnAddWaitingUser( IUserItem * pUserItem )
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnAddWaitingUser(pUserItem);
	}
}

void CRoomParentDlg::OnDeleteWaitingUser( IUserItem * pUserItem )
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnDeleteWaitingUser(pUserItem);
	}
}

void CRoomParentDlg::OnUserListCountChange()
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnUserListCountChange();
	}
}

void CRoomParentDlg::SetRoomBusiness( RoomBusiness * pRoomBusiness )
{
	m_pRoomBusiness = pRoomBusiness;
	if (m_pRoomRightDlg)
	{
		m_pRoomRightDlg->SetRoomBusiness(pRoomBusiness);
	}
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->SetRoomBusiness(pRoomBusiness);
	}
	m_pHtmlOutPutManager = new HtmlOutPutManager( this ) ;
	SetRoomName() ;
}

RoomBusiness * CRoomParentDlg::GetRoomBusiness()
{
	return m_pRoomBusiness;
}

LRESULT CRoomParentDlg::OnClickStamp( WPARAM wParam, LPARAM lParam )
{
	SwitchResourceToModule(_T("Room"));
	if ( m_pStampDlg == NULL )
	{
		m_pStampDlg = new CStampDlg() ;
		m_pStampDlg->Create(CStampDlg::IDD,this);
		m_pStampDlg->SetWindowPos(NULL,200,200,403,288,SWP_SHOWWINDOW);
		m_pStampDlg->CenterWindow() ;
	}
	else
	{
		m_pStampDlg->ShowWindow(SW_SHOW) ;
	}

	return S_OK;
}

LRESULT CRoomParentDlg::OnClickSpeaker( WPARAM wParam, LPARAM lParam )
{
	if (GetCurInfo().enmVIPLevel == core::VIPLEVEL_NONE)
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能发送小喇叭，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
		return S_OK;
	}

	if (GetCurInfo().enmVIPLevel > core::VIPLEVEL_NONE)
	{
		if (m_pSpeakerDlg == NULL)
		{
			CreateSpeakerDlg(L"", core::LOUDSPEAKERTYPE_SMALL);
			return S_OK;
		}
		if (m_pSpeakerDlg != NULL && m_pSpeakerDlg->GetSafeHwnd())
		{
			m_pSpeakerDlg->ShowWindow(SW_SHOW);
			m_pSpeakerDlg->SetForegroundWindow();
		}	
	}
	//else
	//{
	//	C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING_WITH_LINK, L"只有VIP以上用户才能发送喇叭", L"", L"", L"立即升级", GetRoomBusiness()->GetUpdateVipUrl().GetBuffer(0));
	//}
	return S_OK;
}

LRESULT CRoomParentDlg::OnClickWishSong( WPARAM wParam, LPARAM lParam )
{
	if (GetCurInfo().enmVIPLevel == core::VIPLEVEL_NONE)
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_GUEST_OPERATE, L"游客不能赠送礼物，", L"想要畅玩白兔KTV？", L"", L"快去注册吧", GetRoomBusiness()->GetRegisteUrl().GetBuffer());
		return S_OK;
	}

	if (GetCurInfo().enmVIPLevel > core::VIPLEVEL_REGISTER)
	{
		SwitchResourceToModule(_T("Room"));
		if (m_pWishSpeakDlg == NULL)
		{
			CreateWishSpeakerDlg(L"");
			return S_OK;
		}

		if (m_pWishSpeakDlg != NULL && m_pWishSpeakDlg->GetSafeHwnd())
		{
			m_pWishSpeakDlg->ShowWindow(SW_SHOW);
			m_pWishSpeakDlg->SetForegroundWindow();
		}
	} 
	else
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING_WITH_LINK, L"只有VIP以上用户才能赠送礼物", L"", L"", L"立即升级", GetRoomBusiness()->GetUpdateVipUrl().GetBuffer(0));
	}
	return S_OK;
}

void CRoomParentDlg::OnCycleTrigger()
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnCycleTrigger();
	}

	if (m_pEffectManager)
	{
		m_pEffectManager->OnCycleTrigger();
	}

	if (m_pLoudSpeakerManager)
	{
		m_pLoudSpeakerManager->OnCycleTrigger();
	}

	if (m_pGuideFlash != NULL && m_pGuideFlash->GetSafeHwnd())
	{
		m_pGuideFlash->SetActiveWindow();
	}

	if (m_pGuideFlash != NULL && m_pGuideFlash->IsFinish())
	{
		//OnClickBtnOpenSound();
		m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->OnClickBtnOpenSound();

		m_pGuideFlash->DestroyWindow();
		delete m_pGuideFlash;
		m_pGuideFlash = NULL;

		EnableWindow(TRUE);

		if(m_pRoomTopManager != NULL)
		{
			m_pRoomTopManager->ShowGuide();
		}


	}

	CWnd * pWnd = GetActiveWindow();
	int n = 0;
}

void CRoomParentDlg::OnKickUserRsp( uint32 unDstUIN )
{
	m_pHtmlOutPutManager->OnKickOutRsp( unDstUIN ) ;
}

void CRoomParentDlg::OnKickUserNotify( uint32 unSrcUIN, uint32 unDstUIN )
{
	m_pHtmlOutPutManager->OnKickOutNotify( unSrcUIN  , unDstUIN ) ;
}

void CRoomParentDlg::OnAddBlackRsp( uint32 unDstUIN )
{
	m_pHtmlOutPutManager->OnAddBlackRsp_Success( unDstUIN ) ;
}

void CRoomParentDlg::OnAddBlackNotify( uint32 unSrcUIN, uint32 unDstUIN )
{
	m_pHtmlOutPutManager->OnAddBlackNotify( unSrcUIN , unDstUIN ) ;
}

void CRoomParentDlg::OnLockIpRsp( uint32 unDstUIN )
{
	m_pHtmlOutPutManager->OnLockIpRsp_Success( unDstUIN ) ;
}

void CRoomParentDlg::OnLockIpNotify( uint32 unSrcUIN, uint32 unDstUIN )
{
	m_pHtmlOutPutManager->OnLockIpNotify( unSrcUIN , unDstUIN ) ;
}

LRESULT CRoomParentDlg::OnClickUserList( WPARAM wParam, LPARAM lParam )
{
	IUserItem * pUserItem = (IUserItem*)lParam;
	CString strName = pUserItem->GetUserName().c_str() ;
	m_pRoomMidDlg->OnClickNameLink( strName , pUserItem->GetUserUIN() ) ;
	m_pRoomRightDlg->OnClickNameLink( strName, pUserItem->GetUserUIN() );
	if ( wParam == 3 )
	{
		if ( pUserItem->GetUserVipLevel() != core::VIPLEVEL_NONE )
		{
			SwitchResourceToModule(_T("Room"));
			if ( m_pUserInfoCardDlg == NULL )
			{
				m_pUserInfoCardDlg = new CUserInfoCardDlg(this) ;
				m_pUserInfoCardDlg->Create( CUserInfoCardDlg::IDD , NULL ) ;
			}
			common::ui::CCursorPos pt;
			CRect rcTemp;
			m_pSkinEngine->GetSubSkinPos(GetSafeHwnd(),L"itemRoomMidDlg",&(rcTemp.left),&(rcTemp.top),
				&(rcTemp.right),&(rcTemp.bottom));
			ClientToScreen( &rcTemp ) ;
			m_pUserInfoCardDlg->MoveWindow( rcTemp.left, pt.y , 274 , 116 ) ;
			m_pUserInfoCardDlg->Show( pUserItem ) ;
		}
	}
	return S_OK;
}

LRESULT CRoomParentDlg::OnClickStampList( WPARAM wParam, LPARAM lParam )
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.enmVIPLevel == core::VIPLEVEL_NONE )
	{
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_GUEST_OPERATE , L"游客不能使用道具，" , L"想要畅玩白兔KTV？" , L"" , L"快去注册吧" , 
			GetRoomBusiness()->GetRegisteUrl() ); 
		return S_OK;
	}
	uint32 unUIN = 0;
	if (!m_pRoomRightDlg->GetSendToUIN(unUIN))
	{
		m_pHtmlOutPutManager->InsertPrivateTips( L"【提示】： " ,L"请选择盖章对象" , COLOR_OPERATE ) ;
		return S_OK;
	}

	IUserItem * pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN(unUIN);
	if (pUserItem != NULL)
	{
		CSendEventManager::SendStampEvent( m_uRoomID, pUserItem->GetUserUIN() , (uint16)lParam ) ;
	}
	else
	{
		m_pHtmlOutPutManager->InsertPrivateTips( L"【提示】： " ,L"请选择盖章对象" , COLOR_OPERATE ) ;
	}
	return S_OK;
}

void CRoomParentDlg::PostNcDestroy()
{
	__super::PostNcDestroy();	
	core::CurInfo myCurInfo = GetCurInfo() ;
	long lMoney = 0 ;
	if ( myCurInfo.enmVIPLevel != core::VIPLEVEL_NONE )
	{
		lMoney = GetPlutusAwardLeftMoney() + GetLuckLeftMoney() ;
	}	
	g_RoomModule->OnRoomDlgClose(m_uRoomID);
	if ( lMoney != 0 )
	{
		g_RoomModule->m_pModuleManager->CallService( core::SERVICE_VALUE_CORE_UPDATE_MONEY ,(param)lMoney ) ;
		g_RoomModule->ReviseAllRoomMoney( lMoney + myCurInfo.unLeftMoney ) ;
		CString strTemp ;
		strTemp.Format( L"钱PostNcDestroy,LeftMoney=%ld ,myCurInfo.unLeftMoney=%ld,ReviseAllRoomMoney=%ld\r\n" , 
			lMoney ,myCurInfo.unLeftMoney , lMoney + myCurInfo.unLeftMoney ) ;
		OutputDebugString( strTemp ) ;
	}
	CPersonalConfig::GetInstance()->Save();
	delete this;
}


void CRoomParentDlg::OnEnterRoom( IUserItem * pUserItem )
{
	map<uint32 ,map<uint32 ,RecvGiftCountInfo > >::iterator giftbaseiter = m_mGiftBaseList.find( pUserItem->GetUserUIN() ) ;
	if ( giftbaseiter != m_mGiftBaseList.end() )
	{
		map< uint32 , RecvGiftCountInfo >::iterator giftcountiter = giftbaseiter->second.begin() ;
		for ( ;giftcountiter != giftbaseiter->second.end() ; ++giftcountiter )
		{
			giftcountiter->second.bNewEnter = true ;
		}
	}

	if (pUserItem->GetUserVipLevel() == core::VIPLEVEL_TOP)
	{
		GetEffectManager()->ProcessVipTop(pUserItem->GetUserName(), pUserItem->GetUser179ID());
	}

	if (pUserItem->IsLuckyStar())
	{
		GetEffectManager()->ProcessLuckyStar(pUserItem->GetUserName(), pUserItem->GetUser179ID());
	}
	m_pHtmlOutPutManager->OnEnterRoom(pUserItem);
}

void CRoomParentDlg::OnEnterRoomGetUserList_VIPLevelTop( IUserItem* pUserItem ) 
{
	m_pHtmlOutPutManager->OnEnterRoomGetUserList_VIPLevelTop(pUserItem);
}

void CRoomParentDlg::OnEnterRoomGetUserList_VIPLevelDiamond( IUserItem* pUserItem ) 
{
	m_pHtmlOutPutManager->OnEnterRoomGetUserList_VIPLevelDiamond(pUserItem);
}

void CRoomParentDlg::OnEnterRoomGetUserList_GiftStar( IUserItem* pUserItem )
{
	m_pHtmlOutPutManager->OnEnterRoomGetUserList_GiftStar( pUserItem ) ;
}

//冠用户进场
void CRoomParentDlg::OnEnterRoomGetUserList_Crest(IUserItem * pUserItem)
{
	m_pHtmlOutPutManager->OnEnterRoomGetUserList_Crest(pUserItem);
}

//闪亮登场
void CRoomParentDlg::OnEnterRoomGetUserList_Blink(IUserItem* pUserItem ) 
{
	m_pHtmlOutPutManager->OnEnterRoomGetUserList_Blink(pUserItem);
}

//幸运星
void CRoomParentDlg::OnEnterRoomGetUserList_LuckyStar(IUserItem* pUserItem ) 
{
	m_pHtmlOutPutManager->OnEnterRoomGetUserList_LuckyStar( pUserItem ) ;
}

LRESULT CRoomParentDlg::OnClickChangeVoice( WPARAM wParam, LPARAM lParam )
{
	SwitchResourceToModule(_T("Room"));
	if ( m_pChangeVoiceDlg == NULL )
	{
		m_pChangeVoiceDlg = new CChangeVoiceDlg() ;
		m_pChangeVoiceDlg->Create(CChangeVoiceDlg::IDD,this);
		m_pChangeVoiceDlg->SetWindowPos(NULL,200,200,310,225,SWP_SHOWWINDOW);
		m_pChangeVoiceDlg->CenterWindow() ;
	}
	else
	{
		m_pChangeVoiceDlg->ShowWindow(SW_SHOW) ;
	}

	return S_OK;
}

void CRoomParentDlg::OnClickVoiceLink( CString& strName , CString& strUUID )
{
	OnClickNameLink( strName , strUUID ) ;
	OnClickChangeVoice(0, 0) ;
}

LRESULT CRoomParentDlg::OnClickChangeVoiceList( WPARAM wParam, LPARAM lParam )
{
	IGiftItem * pGiftItem = (IGiftItem *)lParam;
	ASSERT(pGiftItem != NULL);
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.enmVIPLevel == core::VIPLEVEL_NONE )
	{
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_GUEST_OPERATE , L"游客不能使用道具，" , L"想要畅玩白兔KTV？" , L"" , L"快去注册吧" ,  
			GetRoomBusiness()->GetRegisteUrl() , L"提 示" ) ;
		return S_OK;
	}
	uint32 unUIN = 0;
	if (!m_pRoomRightDlg->GetSendToUIN(unUIN))
	{
		m_pHtmlOutPutManager->InsertPrivateTips( L"【提示】： " ,L"请选择变声卡使用对象" , COLOR_OPERATE ) ;
		return S_OK;
	}

	IUserItem * pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN(unUIN);
	if (pUserItem != NULL)
	{
		CSendEventManager::SendChangeVoiceEvent(m_uRoomID, pUserItem->GetUserUIN(), pGiftItem->GetID());
	}
	else
	{
		m_pHtmlOutPutManager->InsertPrivateTips( L"【提示】： " ,L"请选择变声卡使用对象" , COLOR_OPERATE ) ;
	}
	return S_OK;
}

void CRoomParentDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_pEffectManager != NULL/* && nType != SIZE_MINIMIZED*/)
	{
		m_pEffectManager->OnSize(nType, cx, cy);
	}
	if ( IsWindowVisible() )
	{
		CComVariant var;
		m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(), L"imgRoomDlgBk", L"originWidth", &var);
		int bkOriginWidth = var.intVal;
		m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(), L"imgRoomDlgBk", L"originHeight", &var);
		int bkOriginHeight = var.intVal;
		int clipX = 0, clipY = 0, clipW = cx, clipH = 600;
		if (cx < bkOriginWidth)
		{
			clipX = (bkOriginWidth - cx)/2;
			clipW = cx;
		}else
		{
			clipW = bkOriginWidth;
		}
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomDlgBk", L"needClip", (CComVariant)TRUE);
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomDlgBk", L"clipLeft", (CComVariant)clipX);
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomDlgBk", L"clipTop", (CComVariant)clipY);
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomDlgBk", L"clipWidth", (CComVariant)clipW);
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomDlgBk", L"clipHeight", (CComVariant)clipH);

		MoveTicker() ;
		m_pRoomRightDlg->ShowCoinFlashWnd();
		//m_pRoomMidDlg->ShowSofaChat();

		MoveModifyNameTipWnd();

		/*CComVariant var;
		m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(), L"imgRichLevel", L"visible", &var);
		MoveGifButton(var.boolVal);*/
		//m_pRoomRightDlg->MoveThePayMoneyBtn(TRUE);
		//MoveBtnTask(TRUE);
		//MoveTaskDlg();
		MoveBtnFans(TRUE);
		MoveBtnUnDealSong(TRUE);
		//DragonZ:V2.21之后的新布局用
		m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->MoveBtnRichLevel(TRUE);
		m_pRoomTopManager->ShowSkinRoomActor();
	}
	if (IsIconic())
	{
		//MoveGifButton(FALSE);
		//m_pRoomRightDlg->MoveThePayMoneyBtn(FALSE);
		//MoveBtnTask(FALSE);
		MoveBtnFans(FALSE);
		MoveBtnUnDealSong(FALSE);
		m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->MoveBtnRichLevel(FALSE);
	}
}

ScreenEffectManager * CRoomParentDlg::GetEffectManager()
{
	return m_pEffectManager;
}

LRESULT CRoomParentDlg::OnClickFlyingText( WPARAM wParam, LPARAM lParam )
{
	SwitchResourceToModule(_T("Room"));
	if ( m_pFlyingTextInputDlg == NULL )
	{
		m_pFlyingTextInputDlg = new CFlyingTextInputDlg(this) ;
		m_pFlyingTextInputDlg->Create(CFlyingTextInputDlg::IDD,this);
		m_pFlyingTextInputDlg->SetType((int)lParam);
		m_pFlyingTextInputDlg->ShowWindow(SW_SHOW);
		//m_pFlyingTextInputDlg->SetWindowPos(NULL,200,200,479,308,SWP_SHOWWINDOW);
		m_pFlyingTextInputDlg->CenterWindow() ;
	}
	else
	{
		m_pFlyingTextInputDlg->SetType((int)lParam);
		m_pFlyingTextInputDlg->ShowWindow(SW_SHOW) ;
	}

	return S_OK;
}

void CRoomParentDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	__super::OnMoving(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	if (m_pEffectManager != NULL)
	{
		m_pEffectManager->OnMoving(pRect);
	}

	if (IsWindowVisible())
	{
		//BOOL bDragWithContent;//拖动窗口时是否显示内容
		//SystemParametersInfo(SPI_GETDRAGFULLWINDOWS,0,&bDragWithContent,NULL);
		m_pRoomRightDlg->ShowCoinFlashWnd();
		//m_pRoomMidDlg->ShowSofaChat();

		MoveModifyNameTipWnd();

		/*CComVariant var;
		m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(), L"imgRichLevel", L"visible", &var);
		MoveGifButton(var.boolVal);*/
		//m_pRoomRightDlg->MoveThePayMoneyBtn(TRUE);
		//MoveBtnTask(TRUE);
		//MoveTaskDlg();
		MoveBtnFans(TRUE);
		MoveBtnUnDealSong(TRUE);

		m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->MoveBtnRichLevel(TRUE);
	}
	if (IsIconic())
	{
		//MoveGifButton(FALSE);
		//m_pRoomRightDlg->MoveThePayMoneyBtn(FALSE);
		//MoveBtnTask(FALSE);
		MoveBtnFans(FALSE);
		MoveBtnUnDealSong(FALSE);

		m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->MoveBtnRichLevel(FALSE);
	}
}

int CRoomParentDlg::GetFlyTextEffect()
{
	if (m_pFlyingTextInputDlg != NULL)
	{
		return m_pFlyingTextInputDlg->GetType();
	}

	return -1;
}

void CRoomParentDlg::SetFlyTextEffect(int nType)
{
	if (m_pRoomMidDlg != NULL)
	{
		m_pRoomMidDlg->SetFlyTextType(nType);
	}
}

void CRoomParentDlg::InitMicSlider()
{
	if ( m_pRoomAvLogic != NULL )
	{
		int speaker = CPersonalConfig::GetInstance()->GetRoomSpeakerVolume() ;
		int mic = CPersonalConfig::GetInstance()->GetRoomMicVolume() ;
		m_pRoomAvLogic->SetSpeakerRoomVolume( speaker ) ;
		m_pRoomAvLogic->SetMicRoomAllVolume( mic ) ;
	}
}

//void CRoomParentDlg::OnClickBtnCloseSound()
//{
//	if (  m_pRoomAvLogic != NULL )
//	{
//		CComVariant var = false;
//		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgSpeakerOn",L"visible",var);
//		var = true;
//		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgSpeakerOff",L"visible",var);
//		m_pRoomAvLogic->SetSondMute( true ) ;
//	}
//}
//
//void CRoomParentDlg::OnClickBtnOpenSound()
//{
//	if ( m_pRoomAvLogic != NULL )
//	{
//		CComVariant var = true;
//		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgSpeakerOn",L"visible",var);
//		var = false;
//		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgSpeakerOff",L"visible",var);
//		m_pRoomAvLogic->SetSondMute( false ) ;
//	}
//}
//
//void CRoomParentDlg::ShowAudioTest()
//{
//	if (m_pAudioTest == NULL)
//	{
//		SwitchResourceToModule(_T("Room"));
//		m_pAudioTest = new CShowAudioTestDlg;
//		m_pAudioTest->Create(CShowAudioTestDlg::IDD,NULL);
//		int cx = GetSystemMetrics(SM_CXSCREEN);
//		int cy = GetSystemMetrics(SM_CYSCREEN);
//		int clientCx = 446;
//		int clientCy = 442;
//		m_pAudioTest->SetWindowPos(NULL,cx/2 - clientCx/2,cy/2 - clientCy/2,clientCx,clientCy,SWP_SHOWWINDOW);
//	}
//	else
//	{
//		if(m_pAudioTest->GetSafeHwnd() && (!m_pAudioTest->IsWindowVisible()))
//			m_pAudioTest->ShowWindow(SW_SHOW);
//	}
//}

void CRoomParentDlg::AddBottomUserInfo()
{
	IUserItem* pUserItem = GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pUserItem == NULL)
	{
		return;
	}

	if (pUserItem->IsOfficial() || pUserItem->GetUserVipLevel() == core::VIPLEVEL_NONE)
	{
		m_bShowRichLevel = false;
	}else
	{
		m_bShowRichLevel = true;
	}
	/*
	std::wstring strPath = ListIconManager::GetVIPIconStatic(pUserItem);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgUserLevel", L"absIconImage", (CComVariant)strPath.c_str());
	std::wstring strTip;
	if (pUserItem->GetUserVipLevel() > core::VIPLEVEL_REGISTER)
	{
	std::wstring strVip = ListIconManager::GetIconTipByVipLevel(pUserItem->GetUserVipLevel());
	strTip = L"您是 " + strVip + L" 用户";
	}
	else
	{
	strTip = L"升级为VIP";
	}
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgUserLevel", L"tip", (CComVariant)strTip.c_str());

	if (pUserItem->GetUserVipLevel() == core::VIPLEVEL_NONE)
	{
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgUserHead", L"tip", (CComVariant)L"");
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgUserHead", L"disabled", (CComVariant)true);
	}

	Hall::HeadImage headImage;
	headImage.m_bMan = pUserItem->IsMale();
	headImage.m_isGuest = (pUserItem->GetUserVipLevel() == core::VIPLEVEL_NONE ? true : false);
	headImage.m_unUIN = pUserItem->GetUserUIN();
	g_RoomModule->m_pModuleManager->CallService(Hall::SERVICE_VALUE_HALL_UPDATE_HEAD_IMAGE_PATH, (param)&headImage);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgUserHead", L"absIconImage", (CComVariant)(CString)headImage.m_HeadImagePath.c_str());

	std::wstring strRolePath = ListIconManager::GetThirdColumnIcon(pUserItem);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgUserRole", L"absIconImage", (CComVariant)strRolePath.c_str());

	strTip = L"您在此房间的身份为：" + ListIconManager::GetIconTipByUser(pUserItem);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgUserRole", L"tip", (CComVariant)strTip.c_str());

	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textUserName", L"text", (CComVariant)pUserItem->GetUserName().c_str());
	CComVariant var;
	m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(), L"textUserName", L"textWidth", &var);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textUserName", L"width", var);
	int nTemp = 0, btnStatusLeft = 0;
	nTemp = var.intVal;
	m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(), L"textUserName", L"left", &var);
	btnStatusLeft = var.intVal + nTemp;
	var = btnStatusLeft;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnStatus", L"left", var);

	SetRichLevel(pUserItem);*/
	MoveModifyNameTipWnd();
	//m_pRoomLeftDlg->OnUpdateUser(pUserItem);
	//DragonZ: V2.21之后的新布局版本用
	m_pRoomBottomLeftDlg->SetBottomUserInfo(pUserItem);
	m_pRoomBottomLeftDlg->OnUpdateUserIsMgr(pUserItem);
}

void CRoomParentDlg::ShowSelfUserInfo()
{
	SwitchResourceToModule(_T("Room"));
	if ( m_pUserInfoDlg == NULL )
	{
		m_pUserInfoDlg = new CSysSettingDlg(this) ;
		m_pUserInfoDlg->Create( CSysSettingDlg::IDD , this ) ;
	}

	m_pUserInfoDlg->OpenDlg( Show_User_Info_Dlg ) ;
	m_pUserInfoDlg->SetToPersonalSetting() ;
	m_pUserInfoDlg->ShowWindow(SW_SHOW);
}

//跑马灯位置调整
void CRoomParentDlg::MoveTicker()
{
	CComVariant var1,var2,var3,var4;
	m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(),L"imgRoomTitleBk",L"left",&var1);
	m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(),L"imgRoomTitleBk",L"width",&var2);
	m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(),L"imgRoomTitleBk",L"top",&var3);
	m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(),L"imgRoomTitleBk",L"height",&var4);
	int iTickerLeft = var1.intVal + 2;
	int iTickerTop = var3.intVal + 1;
	int iTickerWidth = var2.intVal -4 ;
	int iTickerHeight = var4.intVal - 2 ;
	m_RoomTitleTicker.MoveWindow(iTickerLeft,iTickerTop,iTickerWidth,iTickerHeight);
}


LRESULT CRoomParentDlg::OnPostPaint(WPARAM wParam, LPARAM lParam)
{
	if(wParam == 0)
		return S_FALSE;

	HDC hDC = (HDC)wParam;
	m_RoomTitleTicker.OnPostParentPaint(hDC);
	return S_OK;
}

void CRoomParentDlg::OnMyHeadImgUpdate()
{
	/*Hall::HeadImage headImage;
	headImage.m_bMan = GetCurInfo().bMan;
	headImage.m_unUIN = GetCurInfo().unUIN;
	headImage.m_isGuest = (GetCurInfo().enmVIPLevel == core::VIPLEVEL_NONE ? true : false);
	g_RoomModule->m_pModuleManager->CallService(Hall::SERVICE_VALUE_HALL_GET_HEAD_IMAGE_PATH, (param)&headImage);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgUserHead", L"absIconImage", (CComVariant)(CString)headImage.m_HeadImagePath.c_str());*/
	m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->OnMyHeadUpdate();
}

//获取财神降临时未加的剩余金币
long CRoomParentDlg::GetPlutusAwardLeftMoney() 
{	
	long lMoney = 0 ;
	std::vector<PlutusAwardInfo>::iterator iter ;
	for ( iter = m_vPlutusAwardMoneys.begin() ; iter != m_vPlutusAwardMoneys.end() ; ++iter )
	{
		int unIndex = iter->unIndex ;
		for ( ;unIndex <= iter->vPlutusAwardMoneys.size() ; ++unIndex )
		{
			lMoney += iter->vPlutusAwardMoneys[unIndex-1] ;
		}
	}
	return lMoney ;
}

long CRoomParentDlg::GetLuckLeftMoney() 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	long lMoney = 0 ;
	for( std::map<uint32, std::list<LuckyInfo>>::iterator it = m_vLuckyInfoList.begin() ; 
		it != m_vLuckyInfoList.end() ; ++it )
	{
		for(std::list<LuckyInfo>::iterator luckyiter = it->second.begin();
			luckyiter != it->second.end(); ++luckyiter)
		{
			if ( myCurInfo.unUIN == luckyiter->srcuin )
			{
				lMoney += luckyiter->unLuckyMoney ;
			}
		}
	}	
	return lMoney ;
}

void CRoomParentDlg::OnGetUserListComplete()
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnGetUserListComplete();
	}
}

void CRoomParentDlg::OnGetUserListBegin()
{
	if (m_pRoomBottomLeftDlg)
	{
		m_pRoomBottomLeftDlg->OnGetUserListBegin();
	}
}

void CRoomParentDlg::OnGuestRegister()
{
	//游客
	SwitchResourceToModule(_T("Room"));
	if (GetCurInfo().enmVIPLevel == core::VIPLEVEL_NONE)
	{
		SetTimer( ROOM_GUEST_REGISTER_TIMER , ROOM_GUEST_REGISTER_FIRST_INTERVAL , NULL ) ;
	}
}

BOOL CRoomParentDlg::IsCoverWndVisible() 
{
	if ( m_pCoverWnd != NULL && m_pCoverWnd->IsWindowVisible() )
	{
		return TRUE ;
	}
	return FALSE ;
}

void CRoomParentDlg::ClosedRegisterDlg( ) 
{
	if ( m_pCoverWnd != NULL )
	{
		m_pCoverWnd->ShowWindow( SW_HIDE ) ;
	}
	SetTimer( ROOM_GUEST_REGISTER_TIMER , ROOM_GUEST_REGISTER_SECOND_INTERVAL , NULL ) ;
}

void CRoomParentDlg::OnClickRegister()
{
	KillTimer( ROOM_GUEST_REGISTER_TIMER ) ;
	CSendEventManager::SendGuestRegisterRequest( GetSafeHwnd() );
}

void CRoomParentDlg::OnMove(int x, int y)
{
	__super::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindowVisible())
	{
		//BOOL bDragWithContent;//拖动窗口时是否显示内容
		//SystemParametersInfo(SPI_GETDRAGFULLWINDOWS,0,&bDragWithContent,NULL);
		m_pRoomRightDlg->ShowCoinFlashWnd();
		//m_pRoomMidDlg->ShowSofaChat();
		if ( m_pCoverWnd != NULL )
		{
			CRect rc ;
			GetWindowRect( &rc ) ;
			m_pCoverWnd->ShowCoverWnd( rc ) ;
		}

		MoveModifyNameTipWnd();

		/*CComVariant var;
		m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(), L"imgRichLevel", L"visible", &var);
		MoveGifButton(var.boolVal);*/
		//m_pRoomRightDlg->MoveThePayMoneyBtn(TRUE);
		//MoveBtnTask(TRUE);
		//MoveTaskDlg();
		MoveBtnFans(TRUE);
		MoveBtnUnDealSong(TRUE);

		m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->MoveBtnRichLevel(TRUE);
	}
	if (IsIconic())
	{
		//MoveGifButton(FALSE);
		//m_pRoomRightDlg->MoveThePayMoneyBtn(FALSE);
		//MoveBtnTask(FALSE);
		MoveBtnFans(FALSE);
		MoveBtnUnDealSong(FALSE);

		m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->MoveBtnRichLevel(FALSE);
	}
}

void CRoomParentDlg::OnLuckyMessage(uint32 unSrc179ID, uint16 unLuckyTimes, std::wstring strUserName, std::wstring strRoomName )
{
	GetEffectManager()->ProcessLucky(unSrc179ID, unLuckyTimes, strUserName, strRoomName, false);
}

void CRoomParentDlg::OnClickNeedGiftWord( IGiftItem * pGiftItem , IUserItem *pUserItem , uint16 unCount ) 
{
	if ( pGiftItem != NULL )
	{
		if ( m_pGiftWordsDlg == NULL )
		{
			SwitchResourceToModule(_T("Room"));
			m_pGiftWordsDlg = new CGiftWordsDlg(this) ;
			m_pGiftWordsDlg->Create(CGiftWordsDlg::IDD,this);	
			m_pGiftWordsDlg->UpdateGiftWordsInfo( pGiftItem , pUserItem->GetUser179ID() , pUserItem->GetUserUIN(),pUserItem->GetUserName() , unCount ) ;
			m_pGiftWordsDlg->ShowWindow( SW_SHOW) ;
			m_pGiftWordsDlg->CenterWindow() ;
		}				
		else
		{
			m_pGiftWordsDlg->UpdateGiftWordsInfo( pGiftItem , pUserItem->GetUser179ID() , pUserItem->GetUserUIN(),pUserItem->GetUserName() , unCount ) ;
			m_pGiftWordsDlg->ShowWindow( SW_SHOW) ;
		}
	}
}

LRESULT CRoomParentDlg::OnIpStatReport( WPARAM wParam, LPARAM lParam )
{
	m_ipStatReport.IPStatReportResp(lParam);
	return S_OK;
}

void CRoomParentDlg::MoveModifyNameTipWnd()
{
	if (m_pModifyNameTipWnd != NULL && m_pModifyNameTipWnd->GetSafeHwnd())
	{
		CRect rc(0, 0, 0, 0), rcModifyName(0, 0, 0, 0);
		GetWindowRect(&rc);
		m_pModifyNameTipWnd->GetWindowRect(&rcModifyName);

		//if (!m_bShowRichLevel)
		//{
			rc.left += MODIFYNAME_TIP_LEFT_MARGIN;
		//}else
		//{
		//	rc.left = rc.left + MODIFYNAME_TIP_LEFT_MARGIN + 40;
		//}

		rc.top = rc.bottom - MODIFYNAME_TIP_BOTTOM_MARGIN - rcModifyName.Height();

		m_pModifyNameTipWnd->ShowModifyNameTipsWnd(rc);
	}
}

LRESULT CRoomParentDlg::OnModifyNameClickClose(WPARAM wParam, LPARAM lParam)
{
	if ((CWnd*)wParam == m_pModifyNameTipWnd)
	{
		if (m_pModifyNameTipWnd != NULL && m_pModifyNameTipWnd->GetSafeHwnd() != NULL)
		{
			SAFE_DELETE_DIALOG(m_pModifyNameTipWnd);
			CConfigManager::Instance()->SetUserInfo_Setting(GetCurInfo().unUIN,USERINFO_MODIFY_NAME, L"false");
		}
	}

	return S_OK;
}
//
//void CRoomParentDlg::SetRichLevel(IUserItem *pUserItem)
//{
//	//设置富豪图标
//	if (!pUserItem->IsOfficial() && (pUserItem->GetUserVipLevel() > core::VIPLEVEL_NONE) )
//	{
//		std::wstring strRichLevelIco = RichLevelManager::GetRichLevelImgPath(pUserItem);
//		if (!strRichLevelIco.empty())
//		{
//			CString strTemp;
//			strTemp.Format(L"%s", strRichLevelIco.c_str());
//			m_pRichLevelBtn->SetGifBtnGifIcon(strTemp);
//			CRect rcGifBtn;
//			m_pRichLevelBtn->GetWindowRect(&rcGifBtn);
//			m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRichLevel", L"width", (CComVariant)rcGifBtn.Width());
//			m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRichLevel", L"height", (CComVariant)rcGifBtn.Height());
//
//			CComVariant var;
//			m_pSkinEngine->GetSubSkinProp(GetSafeHwnd(), L"imgRichLevel", L"visible", &var);
//			MoveGifButton(var.boolVal);
//
//			SetRichLevelTip();
//			NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ROOM_BOTTOM_POS, (LONG)0);
//		}
//	}
//}

LRESULT CRoomParentDlg::OnDBClickUserList( WPARAM wParam, LPARAM lParam )
{
	IUserItem * pUserItem = (IUserItem*)lParam;
	if (pUserItem != NULL && wParam == 2)
	{
		if (GetCurInfo().enmVIPLevel > core::VIPLEVEL_NONE && pUserItem->IsPrivate())
		{
			SendOpenPrivate(pUserItem->GetUserUIN());
		}
	}

	return S_OK;
}

void CRoomParentDlg::OnClickPublicAccept( CString& strName, CString& strUUID, CString& strIndex )
{
	uint32 unDstUIN = _wtol(strUUID) ;
	uint32 unIndex = _wtol(strIndex) ;
	CSendEventManager::SendPushOnAnswerEvent(m_uRoomID, unDstUIN, unIndex, true);
}

void CRoomParentDlg::OnClickPublicRefuse( CString& strName, CString& strUUID, CString& strIndex )
{
	uint32 unDstUIN = _wtol(strUUID) ;
	uint32 unIndex = _wtol(strIndex) ;
	CSendEventManager::SendPushOnAnswerEvent(m_uRoomID, unDstUIN, unIndex, false);
}
//
//void CRoomParentDlg::SetRichLevelTip()
//{
//	CString strTemp, strCurLevelName, strNextLevelName;
//	if (GetCurInfo().unRichLevel == 0)
//	{
//		strTemp.Format(L"快去消费吧！指挥辣妹跟你玩,还能升级哦！");
//	}else
//	{
//		if (GetCurInfo().unRichLevel >= 25)//已到最高级别
//		{
//			strTemp.Format(L"您现在是 %s", RichLevelManager::GetRichLevelNameByLevel(25).c_str());
//		}else if (GetCurInfo().unRichLevel >= 0 && GetCurInfo().unRichLevel < 25)
//		{
//			uint32 nMoney = GetCurInfo().unRichUpdateMoney;
//			strCurLevelName.Format( L"%s", RichLevelManager::GetRichLevelNameByLevel(GetCurInfo().unRichLevel).c_str() );
//			strNextLevelName.Format( L"%s", RichLevelManager::GetRichLevelNameByLevel(GetCurInfo().unRichLevel + 1).c_str() );
//			strTemp.Format(L"您现在是 %s，离升级到 %s 还差%u币",strCurLevelName.GetBuffer(), strNextLevelName.GetBuffer(), nMoney);
//		}
//	}
//	m_pRichLevelBtn->SetGifBtnTipText(strTemp);
//}

void CRoomParentDlg::GetFleshGuidRect(CString& strRect)
{
	CRect rcMic1, rcCaiTiao, rcMeiYan, rcPublicScreen, rcGiftItem, rcBtnTask,rcProgress;
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//m_pRoomLeftDlg->GetPublicMicRect(1,rcMic1);
	m_pRoomTopManager->GetPublicMicRect(2, rcMic1);

	m_pRoomMidDlg->GetCaiTiaoAndPublicScreenRect(rcCaiTiao, rcPublicScreen);
	rcMeiYan.left = rcCaiTiao.right;
	rcMeiYan.right = rcMeiYan.left + 106; //彩条宽约106
	rcMeiYan.top = rcCaiTiao.top - 42;
	rcMeiYan.bottom = rcMeiYan.top + 22; //媚眼高约22
	m_pRoomRightDlg->GetGiftItemRect(rcGiftItem);
	//if (m_pBtnTask != NULL)
	//{
	//	m_pBtnTask->GetWindowRect(&rcBtnTask);
	//}
	//else
	//{
	//	ASSERT(0);
	rcBtnTask.left = rcBtnTask.right = rcBtnTask.top = rcBtnTask.bottom = 0;
	//}
	GetWindowRect(&rcProgress);
	rcProgress.left = rcProgress.Width()/2;
	rcProgress.right = rcProgress.left + 350;
	rcProgress.bottom = rcProgress.bottom - 150;
	rcProgress.top = rcProgress.bottom - 70;
	strRect.Format(L"%d,%d,%d,%d|%d,%d,%d,%d|%d,%d,%d,%d|%d,%d,%d,%d|%d,%d,%d,%d|%d,%d,%d,%d|%d,%d,%d,%d",
		rcMic1.left, rcMic1.top, rcMic1.Width(), rcMic1.Height(), 
		rcCaiTiao.left, rcCaiTiao.top, rcCaiTiao.Width(), rcCaiTiao.Height(), 
		rcMeiYan.left, rcMeiYan.top, rcMeiYan.Width(), rcMeiYan.Height(), 
		rcPublicScreen.left, rcPublicScreen.top, rcPublicScreen.Width(), rcPublicScreen.Height(), 
		rcGiftItem.left, rcGiftItem.top, rcGiftItem.Width(), rcGiftItem.Height(), 
		rcBtnTask.left, rcBtnTask.top, rcBtnTask.Width(), rcBtnTask.Height(),
		rcProgress.left, rcProgress.top, rcProgress.Width(), rcProgress.Height());

}


//void CRoomParentDlg::DrawGifButton()
//{
//	SwitchResourceToModule(_T("Room"));
//	m_pRichLevelBtn = new common::ui::GifButton();
//	CString strTemp = L"";
//	if (m_pRichLevelBtn->CreateEx(this, strTemp))
//	{
//		//m_pRichLevelBtn->ShowGifBtn(rcClient);
//		MoveGifButton(FALSE);
//	}
//}

//void CRoomParentDlg::MoveGifButton(BOOL bShow)
//{
//	if (m_pRichLevelBtn != NULL && m_pRichLevelBtn->GetSafeHwnd() != NULL)
//	{
//		if (!bShow)
//		{
//			m_pRichLevelBtn->ShowWindow(SW_HIDE);
//		}else
//		{
//			CRect rc;
//			m_pSkinEngine->GetSubSkinPos(GetSafeHwnd(), L"imgRichLevel", &(rc.left), &(rc.top), &(rc.right), &(rc.bottom));
//			ClientToScreen(&rc);
//			m_pRichLevelBtn->ShowGifBtn(rc);
//		}
//	}
//}

//void CRoomParentDlg::MoveTaskDlg()
//{
//	if (m_pTaskDlg != NULL && m_pTaskDlg->GetSafeHwnd() != NULL)
//	{
//		CRect rcClient, rcTaskDlg;
//		GetWindowRect(&rcClient);
//		m_pTaskDlg->GetWindowRect(&rcTaskDlg);
//		long taskLeft = rcClient.right - rcTaskDlg.Width();
//		long taskTop = rcClient.bottom - 28 - rcTaskDlg.Height();
//		m_pTaskDlg->MoveWindow(taskLeft, taskTop, rcTaskDlg.Width(), rcTaskDlg.Height());
//	}
//}
//
//void CRoomParentDlg::DrawBtnTask()
//{
//	CurInfo myInfo = GetCurInfo();
//	if ((myInfo.unarrTaskStat[0] == core::TASKSTATTYPE_UNOPEN))//不用做任务的
//	{
//		return;
//	}
//	bool bFinishTask = true;
//	for (int i = 0; i < core::TASK_SYSTEM_TASKNUM; ++i)
//	{
//		if (myInfo.unarrTaskStat[i] !=  core::TASKSTATTYPE_ISREWARD)
//		{
//			bFinishTask = false;
//			break;
//		}
//	}
//	if (bFinishTask)//做完任务的
//	{
//		return;
//	}
//
//	SwitchResourceToModule(_T("Room"));
//	if (m_pTaskDlg == NULL)
//	{
//		SwitchResourceToModule(_T("Room"));
//		m_pTaskDlg = new CTaskDlg(this);
//		m_pTaskDlg->Create(CTaskDlg::IDD, this);
//		//UpdateTaskInfo();
//	}
//
//	m_pBtnTask = new common::ui::PngButton();
//	std::wstring strTemp = common::utility::systemhelper::Get179AppPath();
//	CString imgNormal;
//	imgNormal.Format(L"%sresource\\other\\Room_btnTask_N.png", strTemp.c_str());
//	CString imgDown;
//	imgDown.Format(L"%sresource\\other\\Room_btnTask_D.png", strTemp.c_str());
//	if (m_pBtnTask->CreateEx(m_pTaskDlg, this))
//	{
//		m_pBtnTask->SetNormalImg(imgNormal);
//		m_pBtnTask->SetDownImg(imgDown);
//		m_pBtnTask->SetBtnHandCursor(TRUE);
//		MoveBtnTask(TRUE);
//	}
//}
//
//void CRoomParentDlg::MoveBtnTask(BOOL bShow)
//{
//	if (m_pBtnTask != NULL && m_pBtnTask->GetSafeHwnd() != NULL)
//	{
//		if (bShow)
//		{
//			CRect rcClient, rcBtnTask;
//			GetWindowRect(&rcClient);
//			m_pBtnTask->GetWindowRect(&rcBtnTask);
//			rcBtnTask.left = rcClient.right - rcBtnTask.Width();
//			rcBtnTask.top = rcClient.bottom - 2 - rcBtnTask.Height();
//			m_pBtnTask->ShowBtnTask(rcBtnTask);
//		}else
//		{
//			m_pBtnTask->ShowWindow(SW_HIDE);
//		}
//
//	}
//}
//
//LRESULT CRoomParentDlg::OnBtnTaskClick( WPARAM wParam ,LPARAM lParam )
//{
//	if ((CWnd*)wParam == m_pBtnTask)//点击的任务按钮
//	{
//		if ((int)lParam == 1)
//		{
//			m_pBtnTask->SetBtnChecked(FALSE);
//			if (m_pTaskDlg != NULL && m_pTaskDlg->GetSafeHwnd() != NULL)
//			{
//				m_pTaskDlg->ShowWindow(SW_HIDE);
//			}
//		}else if ((int)lParam == 0)
//		{
//			m_pBtnTask->SetBtnChecked(TRUE);
//
//			if (m_pTaskDlg != NULL && m_pTaskDlg->GetSafeHwnd() != NULL)
//			{
//				//MoveTaskDlg();
//				m_pTaskDlg->ShowWindow(SW_SHOWNOACTIVATE);
//			}
//		}
//	}
//
//	return S_OK;
//}


LRESULT CRoomParentDlg::OnBtnFansHover( WPARAM wParam ,LPARAM lParam )
{
	std::map<int , common::ui::PngButton*>::iterator iter ;
	for ( iter = m_pMapFansBtn.begin() ; iter != m_pMapFansBtn.end() ; ++iter)
	{
		common::ui::PngButton* pPngBtn = iter->second ;
		if ((CWnd*)wParam == pPngBtn && pPngBtn != NULL && pPngBtn->GetSafeHwnd() != NULL )
		{
			ShowFans(iter->first);
			OutputDebugString(_T("OnBtnFansHover 粉丝按扭"));
			break;
		}
	}

	return S_OK;
}


LRESULT CRoomParentDlg::OnBtnFansLeave( WPARAM wParam ,LPARAM lParam )
{
	std::map<int , common::ui::PngButton*>::iterator iter ;
	for ( iter = m_pMapFansBtn.begin() ; iter != m_pMapFansBtn.end() ; ++iter)
	{
		common::ui::PngButton* pPngBtn = iter->second ;
		if ((CWnd*)wParam == pPngBtn && pPngBtn != NULL && pPngBtn->GetSafeHwnd() != NULL )
		{
			OutputDebugString(_T("OnBtnFansLeave 粉丝按扭"));
			CPoint point ;
			GetCursorPos( &point ) ;  //鼠标当前point

			if(m_pAnchorFansCardDlg != NULL && m_pAnchorFansCardDlg->GetSafeHwnd() != NULL)
			{
				CRect rect ;
				m_pAnchorFansCardDlg->GetWindowRect(&rect) ;
				if (!rect.PtInRect(point) )
				{
					m_pAnchorFansCardDlg->Hide();
				}
			}

			break;
		}
	}


	return S_OK;
}

//DragonZ:V3.0去除房间右下角的任务
//void CRoomParentDlg::UpdateTaskInfo()
//{
//	if (m_pTaskDlg != NULL && m_pTaskDlg->GetSafeHwnd() != NULL)
//	{
//		m_pTaskDlg->UpdateTaskInfo();
//	}
//}

void CRoomParentDlg::OnMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (IsWindowVisible())
	{
		if(m_pRoomTopManager != NULL)
		{
			m_pRoomTopManager->OnMouseMove(nHitTest,point);
		}
	}

	CDialog::OnMouseMove(nHitTest, point);
}



//void CRoomParentDlg::TaskToRegister()
//{
//
//	if ( m_pCoverWnd == NULL )
//	{
//		m_pCoverWnd = new CCoverWnd ;
//		CRect Rc ;
//		GetWindowRect( &Rc ) ;
//		m_pCoverWnd->CreateEx( this , Rc ) ;
//	}
//
//	m_pCoverWnd->ShowWindow( SW_SHOWNOACTIVATE ) ;	
//	m_pCoverWnd->SetForegroundWindow();
//	CSendEventManager::SendGuestRegisterRequest( GetSafeHwnd() );			
//	SetActiveWindow() ;
//
//}

void CRoomParentDlg::ShowGuide()
{
	if (!GetCurInfo().bFirstLogin || GetCurInfo().enmVIPLevel == core::VIPLEVEL_NONE)
	{
		return;   
	}

	CString strGuide = L"";
	CConfigManager::Instance()->GetUserInfo_Setting(GetCurInfo().unUIN, USERINFO_BEGINNER_GUIDE, strGuide);
	if (strGuide == L"true")
	{ 
		return;   
	}

	if (!CFlashWnd::IsSupportFlash())
	{
		return;
	}

	//OnClickBtnCloseSound();
	m_pRoomBottomLeftDlg->GetSelfInfoAndSetDlg()->OnClickBtnCloseSound();

	CString strParam;
	GetFleshGuidRect(strParam);
	m_pGuideFlash = new CGuideFlash(strParam);
	flash_info * pInfo = ScreenEffectManager::GetFlashInfo(EFFECT_TYPE_GUIDE);
	if (pInfo != NULL)
	{
		CRect rc;
		GetWindowRect(&rc);

		int nWidth = pInfo->nWidth != 0 ? pInfo->nWidth : rc.Width();
		int nHeight = pInfo->nHeight != 0 ? pInfo->nHeight : rc.Height();
		if (!m_pGuideFlash->Play(nWidth, nHeight, pInfo->nPlayTime, pInfo->nInterval, pInfo->strFlashPath.c_str(), this))
		{
			m_pGuideFlash->DestroyWindow();
			delete m_pGuideFlash;
			m_pGuideFlash = NULL;
			return;
		}

		//m_pGuideFlash->ModifyStyleEx(0, WS_EX_TOPMOST);
		m_pGuideFlash->SetActiveWindow();
		m_pGuideFlash->ShowWindow(SW_SHOW);

		EnableWindow(FALSE);
	}

	CConfigManager::Instance()->SetUserInfo_Setting(GetCurInfo().unUIN, USERINFO_BEGINNER_GUIDE, L"true");
}

BOOL CRoomParentDlg::IsGuideWndVisible()
{
	if ( m_pGuideFlash != NULL && m_pGuideFlash->IsWindowVisible() )
	{
		return TRUE ;
	}
	return FALSE ;

}

void CRoomParentDlg::ReloadGiftData()
{
	if (m_pRoomRightDlg != NULL)
	{
		m_pRoomRightDlg->ReloadGiftData();
	}
	//DragonZ:跑道移到RoomParentDlg
	/*if (m_pRoomMidDlg != NULL)
	{
	m_pRoomMidDlg->ReloadGiftData();
	}*/
	if (m_pPaodaoStatic != NULL)
	{
		m_pPaodaoStatic->UpdateGiftList();
	}
}

void CRoomParentDlg::DrawBtnFans(int nIndex)
{
	std::map< int , common::ui::PngButton* >::iterator iter = m_pMapFansBtn.find(nIndex);
	if (iter != m_pMapFansBtn.end())
	{
		MoveBtnFans(!IsIconic());
		return;
	}
	SwitchResourceToModule(_T("Room"));
	common::ui::PngButton* pFansBtn = new common::ui::PngButton();
	std::wstring strTemp = common::utility::systemhelper::Get179AppPath();
	CString imgNormal;
	imgNormal.Format(L"%sresource\\other\\MyFans.png", strTemp.c_str());	
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//if (pFansBtn->CreateEx(m_pRoomLeftDlg, this))
	if (pFansBtn->CreateEx(this, this))
	{
		pFansBtn->SetNormalImg(imgNormal);
		pFansBtn->SetHoverImg(imgNormal);
		pFansBtn->SetBtnHandCursor(TRUE);
		m_pMapFansBtn.insert(std::pair<int, common::ui::PngButton*>(nIndex, pFansBtn) );
		MoveBtnFans(!IsIconic());
	}
}

void CRoomParentDlg::MoveBtnFans(BOOL bShow)
{
	std::map<int , common::ui::PngButton*>::iterator iter ;
	for ( iter = m_pMapFansBtn.begin() ; iter != m_pMapFansBtn.end() ; ++iter)
	{
		common::ui::PngButton* pPngBtn = iter->second ;
		if ( pPngBtn != NULL && pPngBtn->GetSafeHwnd() != NULL )
		{
			if (bShow)
			{
				CRect rcMic(0,0,0,0), rcBtnFans(0,0,0,0);
				//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
				//m_pRoomLeftDlg->GetPublicMicRect(iter->first, rcMic);
				m_pRoomTopManager->GetPublicMicRect(iter->first, rcMic);

				pPngBtn->GetWindowRect(&rcBtnFans);
				rcBtnFans.left = rcMic.right - rcBtnFans.Width() - 10;
				rcBtnFans.top = rcMic.bottom - rcBtnFans.Height() - 30;
				pPngBtn->ShowBtnTask(rcBtnFans);
			}else
			{
				pPngBtn->ShowWindow(SW_HIDE);
			}
		}
	}
}

void CRoomParentDlg::ShowFans(int nIndex)
{
	uint32 unDstUIN = GetPulicMicUINByIndex( nIndex ) ;
	IUserItem* pFansUserItem = NULL ;
	if ( unDstUIN != 0 )
	{
		pFansUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unDstUIN ) ;   //获取nIndex麦的主播信息
	}	

	if(unDstUIN == 0 || pFansUserItem == NULL)
	{
		return;
	}

	std::map< int , common::ui::PngButton* >::iterator iter = m_pMapFansBtn.find(nIndex);
	if (iter == m_pMapFansBtn.end())
	{		
		return;
	}
	common::ui::PngButton* fansBut = iter->second;

	SwitchResourceToModule(_T("Room"));
	if(m_pAnchorFansCardDlg == NULL)
	{		
		m_pAnchorFansCardDlg = new CAnchorFansCardDlg(this);
		m_pAnchorFansCardDlg->Create( CAnchorFansCardDlg::IDD , this ) ;
	}	

	CRect rcFansCard;	//粉丝卡片位置
	CRect rcMic(0,0,0,0), rcBtnFans(0,0,0,0);
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger	

	fansBut->GetWindowRect(&rcBtnFans);
	rcFansCard.top = rcBtnFans.bottom -5;
	rcFansCard.left = rcBtnFans.right-240;
	rcFansCard.right = rcFansCard.left + 267;
	rcFansCard.bottom = rcFansCard.top + 260;


	m_pAnchorFansCardDlg->MoveWindow( rcFansCard.left , rcFansCard.top , rcFansCard.Width() , rcFansCard.Height() ) ;
	m_pAnchorFansCardDlg->Show( pFansUserItem ) ;


}

void CRoomParentDlg::DeleteFansBtn(uint32 unSrc)
{
	IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unSrc ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	int nIndex = pUserItem->GetPublicMicIndex() ; 
	std::map<int, common::ui::PngButton*>::iterator iter = m_pMapFansBtn.find(nIndex);
	if (iter != m_pMapFansBtn.end())
	{
		common::ui::PngButton* pBtn = iter->second;
		pBtn->DestroyWindow();
		delete pBtn;
		pBtn = NULL;
		m_pMapFansBtn.erase(iter);
	}
}

void CRoomParentDlg::ShowEnterRoomGuide()
{
	IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( GetCurInfo().unUIN ) ;

	for (int i = 1; i <= 3; ++i)
	{
		//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
		//if (m_pRoomLeftDlg->GetPulicMicUINByIndex(i) != 0)//麦上有人
		if (m_pRoomTopManager->GetPulicMicUINByIndex(i) != 0)
		{
			return;
		}
	}
	if (pUserItem == NULL)
	{
		return;
	}
	if (pUserItem->GetUserTitleLevel() == core::TITLELEVEL_OWNER         ||
		pUserItem->GetUserTitleLevel() == core::TITLELEVEL_SECOND_OWNER  ||
		pUserItem->GetUserTitleLevel() == core::TITLELEVEL_MANAGER)//室主，副室主，管理員
	{
		return;
	}
	if (pUserItem->IsPatrolMan() || pUserItem->IsOperator() || pUserItem->IsAgent())//巡管，运营，销售
	{
		return;
	}

	if (m_pEnterRoomGuideDlg == NULL)
	{
		SwitchResourceToModule(_T("Room"));
		m_pEnterRoomGuideDlg = new CEnterRoomGuide(this);
		m_pEnterRoomGuideDlg->Create(CEnterRoomGuide::IDD, this);
	}

	m_pEnterRoomGuideDlg->ShowWindow(SW_SHOW);
	m_pEnterRoomGuideDlg->CenterWindow(this);
}

//void CRoomParentDlg::TaskToClose()
//{
//	if (m_pBtnTask != NULL && m_pBtnTask->GetSafeHwnd() != NULL)
//	{
//		::PostMessage(GetSafeHwnd() , WM_ONCLICK_PNGBUTTON, (WPARAM)m_pBtnTask, m_pBtnTask->GetBtnChecked());
//	}
//}

void CRoomParentDlg::InitSofaList()
{
	//if (m_pRoomMidDlg != NULL)
	//{
	//	m_pRoomMidDlg->InitSofaList();
	//}
}

void CRoomParentDlg::UpdateSofa( uint32 unIndex )
{
	//if (m_pRoomMidDlg != NULL)
	//{
	//	m_pRoomMidDlg->UpdateSofa(unIndex);
	//}
}


//获取粉丝排行数据返回函数
void CRoomParentDlg::OnGetFansRsp(Event const&evt)
{	
	if(m_pAnchorFansCardDlg != NULL && m_pAnchorFansCardDlg->IsWindowVisible())
	{
		m_pAnchorFansCardDlg->OnGetFansRsp(evt);
	}
	if(m_pOtherUserInfoDlg !=NULL && m_pOtherUserInfoDlg->IsWindowVisible())
	{
		m_pOtherUserInfoDlg->OnGetFansRsp(evt);
	}
	if(m_pUserInfoDlg != NULL && m_pUserInfoDlg->IsWindowVisible())
	{
		m_pUserInfoDlg->OnGetFansRsp(evt);
	}
}

void CRoomParentDlg::OnSofaChat( uint32 unSrcUIN, uint32 unDstUIN, CString strText, bool bPublic )
{
	//if (m_pRoomMidDlg != NULL)
	//{
	//	m_pRoomMidDlg->OnSofaChat(unSrcUIN, unDstUIN, strText, bPublic);
	//}
}

void CRoomParentDlg::OnBuySofaNotify( CSofaItem * pSofaItem )
{
	IUserItem * pUserItem = GetRoomBusiness()->GetUserManager()->SearchUserByUIN(pSofaItem->GetUserUIN());
	if (pUserItem == NULL)
	{
		return;
	}

	bool bSameUser = (pSofaItem->GetLastUserUIN() == pSofaItem->GetUserUIN() ? true : false);
	GetHtmlOutPutManager()->OnSofaPublicNotify(pUserItem, bSameUser);
	//自己被踢
	if (pSofaItem->GetLastUserUIN() == GetCurInfo().unUIN && pSofaItem->GetUserUIN() != GetCurInfo().unUIN)
	{
		GetHtmlOutPutManager()->OnSofaBeKicked(pUserItem);
		FlashRoomWindow();
	}
	else
	{
		if (pSofaItem->GetLastUserUIN() == GetCurInfo().unUIN && pSofaItem->GetUserUIN() == GetCurInfo().unUIN)
		{
			GetHtmlOutPutManager()->OnSofaMyUpdate(pUserItem);
		}
		else
		{
			//空沙发
			if (pSofaItem->GetLastUserUIN() == 0)
			{
				GetHtmlOutPutManager()->OnSofaNewUser(pUserItem, NULL, true);
			}
			else
			{
				IUserItem * pOldUserItem = GetRoomBusiness()->GetUserManager()->SearchUserByUIN(pSofaItem->GetLastUserUIN());
				if (pOldUserItem != NULL)
				{
					GetHtmlOutPutManager()->OnSofaNewUser(pUserItem, pOldUserItem);
				}
				else
				{
					GetHtmlOutPutManager()->OnSofaNewUser(pUserItem, pSofaItem);
				}
			}
		}
	}
}

void CRoomParentDlg::OnSofaInfoUpdate( std::vector<CSofaItem*> vecSofaItem )
{
	//if (m_pRoomMidDlg != NULL)
	//{
	//	m_pRoomMidDlg->OnSofaInfoUpdate(vecSofaItem);
	//}
}
//点击公麦上的点歌
void CRoomParentDlg::OnClickOrderSong(uint32 unIndex)
{
	if (GetCurInfo().enmAccountType == ACCOUNTTYPE_VISITOR)//游客
	{
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_GUEST_OPERATE , L"游客不能点歌，" , L"想要畅玩白兔KTV？" , L"" , L"快去注册吧" , 
			GetRoomBusiness()->GetRegisteUrl().GetBuffer() ); 
		return;
	}

	uint32 unActorIndex;
	if (unIndex == 0)
	{
		uint32 unFirstActorIndex = CheckActorOnMic();
		if (unFirstActorIndex == 0)
		{
			return;
		}
		else
		{
			unActorIndex = unFirstActorIndex;
		}
	}
	else
	{
		unActorIndex = unIndex;
	}

	ShowOrderSongDlg();

	if (m_pOrderSongDlg != NULL)
	{
		m_pOrderSongDlg->SetCurSelIndex(unActorIndex);
		m_pOrderSongDlg->Init();
	}
}

void CRoomParentDlg::ClearSofaList()
{
	//if (m_pRoomMidDlg != NULL)
	//{
	//	m_pRoomMidDlg->ClearSofaList();
	//}
}

LRESULT CRoomParentDlg::OnClickSofaName( WPARAM wParam, LPARAM lParam )
{
	if (GetCurInfo().un179id == (uint32)wParam)
	{
		m_pRoomBottomLeftDlg->OnClickBtnWhereIAm();
		return S_OK;
	}

	IUserItem* pUserItem = GetRoomBusiness()->GetUserManager()->SearchUserBy179ID((uint32)wParam) ;
	if ( pUserItem == NULL )
	{
		GetHtmlOutPutManager()->InsertPrivateTips(L"【提示】： " ,L"抱歉，对方已离开该房间" , COLOR_OPERATE );
		return S_OK;
	}
	//UserListMenu * pMenu = new UserListMenu(this);
	//if ( pMenu != NULL )
	//{
	//	m_pSelectUserItem = pUserItem ;
	//	IUserItem * pSelfItem = GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	//	if (pSelfItem != NULL)
	//	{
	//		pMenu->PopupMenu( pSelfItem, pUserItem ) ;
	//	}
	//	delete pMenu;
	//	pMenu = NULL;
	//}

	CString strName = pUserItem->GetUserName().c_str();
	uint32 unUIN = pUserItem->GetUserUIN();
	//用户列表选中用户
	m_pRoomMidDlg->OnClickNameLink( strName , unUIN ) ;
	m_pRoomRightDlg->OnClickNameLink( strName , unUIN ) ;

	return S_OK;
}

void CRoomParentDlg::OnEnterRoomGetUserList_Event( IUserItem * pUserItem, uint8 unIndex )
{
	m_pHtmlOutPutManager->OnEnterRoomGetUserList_Event(pUserItem, unIndex);
}

void CRoomParentDlg::OnEnterRoomGetUserList_VIPLevelBlackDiamond( IUserItem * pUserItem )
{
	m_pHtmlOutPutManager->OnEnterRoomGetUserList_VIPLevelBlackDiamond(pUserItem);
}

void CRoomParentDlg::OnClickGameReward( std::wstring strUrl )
{
	std::wstring strToken = strUrl;
	g_RoomModule->m_pModuleManager->CallService(Hall::SERVICE_VALUE_HALL_GET_TOKEN_URL, (param)&strToken);

	Hall::InLineUrl * pEvent = new Hall::InLineUrl();
	pEvent->m_InLineUrl = strToken;
	IModuleManager* pModuleManager = g_RoomModule->m_pModuleManager;
	if(pModuleManager != NULL)
	{
		pModuleManager->PushEvent(MakeEvent<MODULE_ID_ROOM>()(Hall::EVENT_VALUE_HALL_InLineURL_SHOW, MODULE_ID_HALL,0, 0, 0, pEvent));  //头像上传
	}
}

void CRoomParentDlg::ShowOrderSongDlg()
{
#if 0
	//test
	if (m_pOrderSongDlg != NULL)
	{
		m_pOrderSongDlg->DestroyWindow();
		delete m_pOrderSongDlg;
		m_pOrderSongDlg = NULL;
	}
#endif

	if (m_pOrderSongDlg == NULL)
	{
		SwitchResourceToModule(_T("Room"));
		m_pOrderSongDlg = new COrderSongDlg(this);
		m_pOrderSongDlg->Create(COrderSongDlg::IDD, this);
	}

	m_pOrderSongDlg->ShowWindow(SW_SHOW);
	m_pOrderSongDlg->CenterWindow(this);
	//m_pOrderSongDlg->Init();
}

void CRoomParentDlg::MoveBtnUnDealSong( BOOL bShow )
{
	std::map<int , common::ui::PngButton*>::iterator iter ;
	for ( iter = m_pMapUnDealSongBtn.begin() ; iter != m_pMapUnDealSongBtn.end() ; ++iter)
	{
		common::ui::PngButton* pPngBtn = iter->second ;
		if ( pPngBtn != NULL && pPngBtn->GetSafeHwnd() != NULL )
		{
			if (bShow)
			{
				CRect rcMic(0,0,0,0), rcBtnSong(0,0,0,0);
				//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
				//m_pRoomLeftDlg->GetPublicMicRect(iter->first, rcMic);
				m_pRoomTopManager->GetPublicMicRect(iter->first, rcMic);

				pPngBtn->GetWindowRect(&rcBtnSong);
				rcBtnSong.left = rcMic.left + 45;
				rcBtnSong.top = rcMic.bottom - rcBtnSong.Height() - 15;
				pPngBtn->ShowBtnTask(rcBtnSong);
			}else
			{
				pPngBtn->ShowWindow(SW_HIDE);
			}
		}
	}
}

void CRoomParentDlg::DrawBtnUnDealSong( int nIndex , int songCount)
{	
	uint32 unDstUIN = GetPulicMicUINByIndex( nIndex ) ;
	if (unDstUIN == 0 || unDstUIN != GetCurInfo().unUIN)//只能自己看得到自己的，而且是艺人身份
	{
		return;
	}
	std::map< int , common::ui::PngButton* >::iterator iter = m_pMapUnDealSongBtn.find(nIndex);
	if (iter != m_pMapUnDealSongBtn.end())
	{
		if (songCount > 0)
		{
			SetUnDealSongBtn(nIndex, songCount);
			MoveBtnUnDealSong(!IsIconic());
		}else
		{
			DeleteUnDealSongBtn(unDstUIN);
		}
		return;
	}

	if (songCount <= 0)
	{
		return;
	}

	SwitchResourceToModule(_T("Room"));
	common::ui::PngButton* pUnDealSong = new common::ui::PngButton();
	std::wstring strTemp = common::utility::systemhelper::Get179AppPath();
	CString imgNormal;
	imgNormal.Format(L"%sresource\\other\\Room_imgUnDealSong.png", strTemp.c_str());	
	//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
	//if (pUnDealSong->CreateEx(m_pRoomLeftDlg, this))
	if(pUnDealSong->CreateEx(this, this))
	{
		pUnDealSong->SetNormalImg(imgNormal);
		pUnDealSong->SetHoverImg(imgNormal);
		m_pMapUnDealSongBtn.insert(std::pair<int, common::ui::PngButton*>(nIndex, pUnDealSong) );
		SetUnDealSongBtn(nIndex, songCount);
		MoveBtnUnDealSong(!IsIconic());
	}
}

void CRoomParentDlg::DeleteUnDealSongBtn( uint32 unSrc )
{
	IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unSrc ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	int nIndex = pUserItem->GetPublicMicIndex() ; 
	std::map<int, common::ui::PngButton*>::iterator iter = m_pMapUnDealSongBtn.find(nIndex);
	if (iter != m_pMapUnDealSongBtn.end())
	{
		common::ui::PngButton* pBtn = iter->second;
		pBtn->DestroyWindow();
		delete pBtn;
		pBtn = NULL;
		m_pMapUnDealSongBtn.erase(iter);
	}
}

void CRoomParentDlg::SetUnDealSongBtn( int nIndex , int songCount)
{
	if (nIndex < 1 || nIndex > 3 || songCount < 0)
	{
		return;
	}
	std::map<int, common::ui::PngButton*>::iterator iter = m_pMapUnDealSongBtn.find(nIndex);
	if (iter == m_pMapUnDealSongBtn.end())
		return;

	common::ui::PngButton* pUnDealSong = iter->second;
	CString strCon;
	strCon.Format(L"%d", songCount);
	CString strFont = L"宋体";
	COLORREF color = RGB(255, 255, 255);
	int fontSize = 12;
	pUnDealSong->SetContent(strCon, strFont, color, fontSize);

}

void CRoomParentDlg::UpdateSongList( uint32 unIndex, uint32 unSongerID, bool bRefresh/* = false*/, bool bSort/* = true*/ )
{
	if (m_pOrderSongDlg != NULL)
	{
		m_pOrderSongDlg->InitSongList(unIndex, unSongerID, bRefresh);
		m_pOrderSongDlg->ClearSongListStat();
	}
}

void CRoomParentDlg::UpdateOrderList( uint32 unSelfID, bool bActor )
{
	if (m_pOrderSongDlg != NULL)
	{
		m_pOrderSongDlg->InitOrderList(unSelfID, bActor);
	}
}

void CRoomParentDlg::SendGetSongList()
{
	//重置主播头像信息
	GetRoomBusiness()->GetOrderSongManager()->ClearActorInfo();
	//发送获取主播点歌单的请求
	for (int i = 1; i <= 3; i++)
	{
		uint32 unUin = GetPulicMicUINByIndex(i);
		IUserItem * pUserItem = GetRoomBusiness()->GetUserManager()->SearchUserByUIN(unUin);
		if (pUserItem != NULL && pUserItem->IsActor())
		{
			Hall::HeadImage headImage ;
			headImage.m_bMan = pUserItem->IsMale() ;
			headImage.m_unUIN = pUserItem->GetUserUIN() ;	
			headImage.m_isGuest = false;
			g_RoomModule->m_pModuleManager->CallService(Hall::SERVICE_VALUE_HALL_UPDATE_HEAD_IMAGE_PATH, (param)&headImage);

			GetRoomBusiness()->GetOrderSongManager()->AddActorInfo(i, pUserItem->GetUserUIN(), pUserItem->GetUserName(), headImage.m_HeadImagePath);
			CSendEventManager::SendGetSongListEvent(m_uRoomID, pUserItem->GetUserUIN());
		}
	}
}

void CRoomParentDlg::OnOrderSongRsp( uint32 unSongerID, bool bSuccess )
{
	if (bSuccess)
	{
		//点歌成功以后，刷新被点歌主播的歌单，可以清除自定义点歌框中的内容，然后跳转到已点歌曲列表
		IUserItem * pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserByUIN(unSongerID);
		if (pUserItem != NULL && pUserItem->GetPublicMicIndex() != 0)
		{
			m_pOrderSongDlg->InitSongList(pUserItem->GetPublicMicIndex(), pUserItem->GetUserUIN());
			m_pOrderSongDlg->ShowOrderList();
		}
		C179MsgBox::ShowForOrderSong(m_pOrderSongDlg, NewMsgBox::MSGBOX_ORDERSONG_OK_TWO_STRING, L"点歌成功", L"坐等主播为您演唱吧~~", L"#0000ff", L"#0", L"关闭", L"", L"点歌成功");
	}
	else
	{
		int nRet = C179MsgBox::ShowForOrderSong(m_pOrderSongDlg, NewMsgBox::MSGBOX_ORDERSONG_OK_CANCEL_TWO_STRING, L"点歌失败", L"您当前的余额不足~~", L"#0000ff", L"#ff0000", L"立即充值", L"关闭", L"点歌失败");
		if (nRet == RET_OK)
		{
			common::utility::systemhelper::OpenUrl( GetRoomBusiness()->GetPayUrl().GetBuffer() ) ;
		}
	}
}

void CRoomParentDlg::UpdateUndealCount()
{
	IUserItem * pSelfItem = GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pSelfItem != NULL)
	{
		COrderSongManager * pOrderMgr = GetRoomBusiness()->GetOrderSongManager();
		if (pOrderMgr != NULL)
		{
			uint32 unCount = pOrderMgr->GetUndealCount(pSelfItem->GetUserUIN());
			if (pSelfItem->GetPublicMicIndex() != 0)
			{
				DrawBtnUnDealSong(pSelfItem->GetPublicMicIndex(), unCount);
			}
		}
	}
}

void CRoomParentDlg::OnSongTakeOrderRsp( uint32 unResult )
{
	switch (unResult)
	{
	case 0:
		{
			//发送获取已点歌曲列表请求，需要优化
			CSendEventManager::SendGetOrderListEvent(GetRoomID());
		}
		break;
	case 1:
		{

		}
		break;
	case 2:
		{
			C179MsgBox::ShowForOrderSong(m_pOrderSongDlg, NewMsgBox::MSGBOX_ORDERSONG_OK_TWO_STRING, L"您当前不可接受点歌", L"请在评价结果公布15秒后再试", L"#0", L"#0", L"确定", L"", L"提示");
		}
		break;
	default:
		break;
	}
}

void CRoomParentDlg::OnInitRoomActor()
{
	if(m_pRoomTopManager != NULL)
	{
		m_pRoomTopManager->InitRoomActor();
	}

}

void CRoomParentDlg::OnAgentInfo( IUserItem* pUserItem )
{
	if ( pUserItem == NULL )
	{
		return ;
	}
	if (!pUserItem->IsAgent())
	{
		return;
	}

	core::CurInfo myCurInfo = GetCurInfo() ;
	SwitchResourceToModule(_T("Room"));	
	if ( myCurInfo.unUIN == pUserItem->GetUserUIN() )
	{
		//显示自己的销售信息		
		if ( m_pUserInfoDlg == NULL )
		{
			m_pUserInfoDlg = new CSysSettingDlg(this) ;
			m_pUserInfoDlg->Create( CSysSettingDlg::IDD , this ) ;
		}
		m_pUserInfoDlg->SetToPersonalSetting() ;
		m_pUserInfoDlg->OpenDlg( Show_BankAccount_Dlg ) ;
		m_pUserInfoDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		//显示他人的用户信息
		if ( m_pOtherUserInfoDlg == NULL )
		{
			m_pOtherUserInfoDlg = new COtherUserInfoDlg(this);
			m_pOtherUserInfoDlg->Create( COtherUserInfoDlg::IDD , this ) ;			
		}

		OtherUserInfo oUserInfo;
		oUserInfo.m_UserUin = pUserItem->GetUserUIN();
		oUserInfo.m_UserAccount = pUserItem->GetUser179ID();
		oUserInfo.m_Gender = pUserItem->IsMale();
		oUserInfo.m_UserRoleName = pUserItem->GetUserName();
		oUserInfo.m_VipLevel = pUserItem->GetUserVipLevel();
		oUserInfo.m_RichLevel = pUserItem->GetUserRichLevel();
		oUserInfo.m_IsActor = pUserItem->IsActor();
		oUserInfo.m_IsAgent = pUserItem->IsAgent();
		m_pOtherUserInfoDlg->SetUserInfo(oUserInfo);
		m_pOtherUserInfoDlg->OpenOtherDlg(Show_Other_ItsBankAccount);
		m_pOtherUserInfoDlg->ShowWindow(SW_SHOW);
	}
}

uint32 CRoomParentDlg::CheckActorOnMic()
{
	for (int i = 1; i <= 3; ++i)
	{
		//DragonZ:CRoomLeftDlg抽象为CRoomTopManger
		//uint32 unUIN = m_pRoomLeftDlg->GetPulicMicUINByIndex(i);
		uint32 unUIN = m_pRoomTopManager->GetPulicMicUINByIndex(i);

		IUserItem * pUserItem = GetRoomBusiness()->GetUserManager()->SearchUserByUIN(unUIN);
		if (pUserItem != NULL)
		{
			if (pUserItem->IsActor())
			{
				return i;
			}
		}
	}

	return 0;
}

void CRoomParentDlg::ClearSpeakerMsg()
{
	m_pSpeakerHtml->ClearMsg();
	m_pSpeakerHtml->ShowWindow(SW_HIDE);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomSpeakerBK", L"visible", (CComVariant)false);
}

void CRoomParentDlg::MovePaoDao()
{
	if (m_pPaodaoStatic == NULL)
	{
		return;
	}

	CRect rcPaoDao;
	m_pSkinEngine->GetSubSkinPos(GetSafeHwnd(), L"itemHtmlPaodao", &(rcPaoDao.left), &(rcPaoDao.top), &(rcPaoDao.right), &(rcPaoDao.bottom));
	m_pPaodaoStatic->MoveWindow(&rcPaoDao);
}

void CRoomParentDlg::InsertRoomMidInputDefaultText( CString& strText )
{
	m_pRoomMidDlg->InsertInputMsgDefaultText(strText);
}

void CRoomParentDlg::OnClickBtnIconIntro()
{
	SwitchResourceToModule(_T("Room"));

	if (m_pIconIntroducDlg == NULL)
	{
		m_pIconIntroducDlg = new CIconIntroductionDlg(this);
		m_pIconIntroducDlg->Create(CIconIntroductionDlg::IDD,this);
	}
	m_pIconIntroducDlg->ShowWindow(SW_SHOW);
	m_pIconIntroducDlg->CenterWindow();
}

void CRoomParentDlg::CleanPublicOutput()
{
	m_pRoomMidDlg->CleanPublicOutput();
}

void CRoomParentDlg::CleanPrivateOutput()
{
	m_pRoomMidDlg->CleanPrivateOutput();
}

void CRoomParentDlg::CleanSpeakerOutput()
{
	m_pRoomRightDlg->CleanSpeakerOutput();
}

void CRoomParentDlg::SetCollectRoom( BOOL bCollected )
{
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnCollectRoom", L"visible", (CComVariant)(bCollected));
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnUnCollectRoom", L"visible", (CComVariant)(!bCollected));
}

void CRoomParentDlg::OnClickRoomPay(CString strUrl)
{
	if (m_pPayDlg == NULL)
	{
		SwitchResourceToModule(_T("Room"));
		m_pPayDlg = new CPayDlg(this);
		m_pPayDlg->Create(CPayDlg::IDD, this);
	}
	m_pPayDlg->ShowWindow(SW_SHOW);
	m_pPayDlg->CenterWindow(this);
	m_pPayDlg->SetTheUrl(strUrl);
}

LRESULT CRoomParentDlg::OnClickMsgBoxGoToRegister( WPARAM wParam, LPARAM lParam )
{
	if ((CRoomParentDlg*)wParam == this)
	{
		OnClickGotoRegister();
	}	

	return TRUE;
}

void CRoomParentDlg::OnClickGotoRegister()
{
	if ( m_pCoverWnd == NULL )
	{
		m_pCoverWnd = new CCoverWnd ;
		CRect Rc ;
		GetWindowRect( &Rc ) ;
		m_pCoverWnd->CreateEx( this , Rc ) ;
	}

	m_pCoverWnd->ShowWindow( SW_SHOWNOACTIVATE ) ;	
	m_pCoverWnd->SetForegroundWindow();

	CSendEventManager::SendGuestRegisterRequest( GetSafeHwnd() );			
	SetActiveWindow() ;
}

void CRoomParentDlg::OnActorSpeak()
{
	if (g_RoomModule->IsEnteredTheRoom(m_uRoomID))//进过此房间
	{
		return;
	}
	vector<IUserItem*> vActorList;
	m_pRoomBusiness->GetUserManager()->GetAllActorExceptSelf(vActorList);
	for (vector<IUserItem*>::iterator iter = vActorList.begin(); iter != vActorList.end() ; ++iter)
	{
		m_pHtmlOutPutManager->OnActorAutoSpeak(*iter);
	}
}

void CRoomParentDlg::OnAgentSpeak()
{
	if (g_RoomModule->IsEnteredTheRoom(m_uRoomID))//进过此房间
	{
		return;
	}
	vector<IUserItem*> vAgentList;
	m_pRoomBusiness->GetUserManager()->GetAllAgent(vAgentList);
	for (vector<IUserItem*>::iterator iter = vAgentList.begin(); iter != vAgentList.end() ; ++iter)
	{
		m_pHtmlOutPutManager->OnAgentAutoSpeak(*iter);
	}
}

void CRoomParentDlg::UpdateMarkList( uint32 unSelfID )
{
	if (m_pOrderSongDlg != NULL)
	{
		m_pOrderSongDlg->InitMarkList(unSelfID);
	}
}

void CRoomParentDlg::OnClickHrefMark()
{
	ShowOrderSongDlg();
	if (m_pOrderSongDlg != NULL)
	{
		m_pOrderSongDlg->ShowMarkList();
	}
}

void CRoomParentDlg::InsertSystemSpeaker( CString& strText )
{
	m_pRoomRightDlg->InsertSpeakerText( strText ) ;
}

void CRoomParentDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rcRoomInfo(0,0,0,0);
	m_pSkinEngine->GetSubSkinPos(GetSafeHwnd(), L"textRoomInfo", &(rcRoomInfo.left), &(rcRoomInfo.top), &(rcRoomInfo.right), &(rcRoomInfo.bottom));
	ClientToScreen(&rcRoomInfo);
	if (PtInRect(&rcRoomInfo, point))
	{
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomAnnounce", L"visible", (CComVariant)TRUE);
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textRoomAnnounce", L"visible", (CComVariant)TRUE);
	}else
	{
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgRoomAnnounce", L"visible", (CComVariant)FALSE);
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textRoomAnnounce", L"visible", (CComVariant)FALSE);
	}

	__super::OnNcMouseMove(nHitTest, point);
}


//void CRoomParentDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	__super::OnLButtonDown(nFlags, point);
//}
