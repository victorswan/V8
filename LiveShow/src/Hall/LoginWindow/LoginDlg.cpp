// LoginDlg.cpp : 实现文件

///////////////51ktv//////////////
#include "stdafx.h"
#include "../Hall.h"
#include "LoginDlg.h"
#include "skin_i.h"
#include "SkinUtil.h"
#include "../CommonLibrary/include/utility/SystemHelper.h"
#include "../CommonLibrary/include/utility/Md5.h"
#include "../CommonLibrary/include/utility/StringHelper.h"
#include "../CommonLibrary/include/utility/FileHelper.h"
#include "../CommonLibrary/include/ui/rbpasswordctrl.h"
#include "../CommonLibrary/include/utility/ConfigManager.h"
#include "../HallWindow/HallDlg.h"
#include "RegisterDlg.h"
#include "VerifyDlg.h"

#include "coredefine.h"
#include "HallDefine.h"
#include "RoomDefine.h"
#include "../SysSettingIni.h"
#include "QQLoginDlg.h"
#include "179TipCtrl.h"
#include "GGHelper.h"
#include "..\src\CommonLibrary\thirdlibrary\CxImage\include\ximage.h"
#include "..\..\x179\x179.h"

#define SKIN_ON_CLICK_GUESTLOGIN            3
#define SKIN_ON_CLICK_REGISTER              4
#define SKIN_ON_CLICK_LOGIN                 5

#define SKIN_ON_CLICK_MINIMIZE              6
#define SKIN_ON_CLICK_CLOSE                 7

#define SKIN_ON_CLICK_CLEAR_RECORD          8
#define SKIN_ON_CLICK_GETBACK_PASSWORD      9

#define NOTIFY_LOGIN_BY_179NUM              10
#define NOTIFY_LOGIN_BY_51NUM               11

//#define SKIN_ON_CLICK_IMAGE_AD            12
#define SKIN_ON_DIALOG_RESIZE               13
#define SKIN_ON_CLICK_LOGIN_AD              14
#define SKIN_ON_CLICK_BTN_QQ_LOGIN          15

//关于qq登录窗口的大小的位置
#define QQ_LOGIN_TIP_LEFT_MARGIN            -25 //QQ登录提示框left到QQ登录tab的left
#define QQ_LOGIN_TIP_TOP_MARGIN             35 //QQ登录提示框top 到QQ登录tab的bottom

#define LOBBY_WIDTH 1100
#define LOBBY_HEIGHT 700
/////////////////////////////////////////

#define MAXLOGINUSER 20
#define VISITOR_PASSWORD_MD5 "2c34e9801b5a6dda658c45f5eec7ce0e"

#include "LoginVerifyHander.h"
#include "VerifyDlg.h"
#include "webdefine.h"

#define LOGIN_TRAY_TIMER_IDEVENT		 1      //定时器  登录过程中大厅托盘动态切换显示
#define LOGIN_TRAY_TIMER_INTERVALTIME    150    //
// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(IModuleManager* pModuleManager,CHallDlg *pHallDlg,CWnd* pParent /*=NULL*/)
: CDialog(CLoginDlg::IDD, pParent)
{
	m_pPasswordCtrl = NULL;
	m_pPasswordCtrl = new CRBPasswordCtrl;

	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);

	m_pHallDlg = NULL;
	m_pHallDlg = pHallDlg;

	m_pVerifydg = NULL;

	//added
	m_pModuleManager=pModuleManager;//added

	m_pQQLoginDlg = NULL;
	//DragonZ:
	m_p179TipCtrl = NULL;
	m_pAccoutTip = NULL;
	m_pPasswordTip = NULL;
	m_pQQLoginTip = NULL;
	m_bCurQQLogin = FALSE;

	m_bVerifyOpen=false;
	m_bVerifyCodeError=false;
	m_isClear = true;
	m_pReconnectMsgBox = NULL;
}

CLoginDlg::~CLoginDlg()
{	

	CloseNonModalDlg((CDialog*&)m_pPasswordCtrl);	
	CloseNonModalDlg((CDialog*&)m_pVerifydg);
	CloseNonModalDlg((CDialog*&)m_pQQLoginDlg);
	CloseNonModalDlg((CDialog*&)m_p179TipCtrl);
	CloseNonModalDlg((CDialog*&)m_pAccoutTip);
	CloseNonModalDlg((CDialog*&)m_pPasswordTip);
	CloseNonModalDlg((CDialog*&)m_pQQLoginTip);
	CloseNonModalDlg((CDialog*&)m_pReconnectMsgBox);
	
}

//P
void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlSavePassword);
	DDX_Control(pDX, IDC_CHECK2, m_ctrlAutoLogin);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, *m_pPasswordCtrl);

}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_WM_CREATE()
	//	ON_WM_CTLCOLOR()
	ON_SKIN_MESSAGE
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_TIMER()

    ON_MESSAGE(UM_QQLOGIN_SET, &CLoginDlg::OnSetQQLogin)
	ON_MESSAGE(WM_AUTO_LOGIN, &CLoginDlg::OnAutoLogin)
	ON_MESSAGE(UM_179REGISTER_AUTOLOGIN,&CLoginDlg::On179RegisterLogin)
	ON_MESSAGE(UM_179REGISTER_QQLOGIN,&CLoginDlg::On179RegisterQQLogin)
	ON_MESSAGE(UM_QQLOGIN_AUTOLOGIN,&CLoginDlg::OnQQLogin179Account)
	ON_MESSAGE(UM_LOGIN_DLG_SETFOCUS,&CLoginDlg::OnLoginDlgSetFocus)
	ON_MESSAGE(UM_QQLOGIN_MOVEWINDOW,&CLoginDlg::OnQQLoginMoveWindow)
	ON_MESSAGE( WM_ITEM_DELETE, OnClickDeleteAccount)
	ON_MESSAGE( WM_COMBOBOX_SEL_CHANGE, OnSelectComboAccount)
	ON_BN_CLICKED(IDC_CHECK2, &CLoginDlg::OnBnClickedCheckAutoLogin)
	ON_BN_CLICKED(IDC_CHECK1, &CLoginDlg::OnBnClickedCheckSavePassword)
	ON_MESSAGE(WM_COMBOBOX_EDIT_CHANGE, &CLoginDlg::OnCbnEditchangeComboAccount)
	ON_MESSAGE(WM_WEBPLUGIN_MESSAGE, &CLoginDlg::OnWebPluginMessage)
	ON_MESSAGE(WM_PWD_CTRL_TIP,&CLoginDlg::OnEditPasswordCtrl)
	ON_MESSAGE(PASSWORD_CTRL_SETFOCUS,&CLoginDlg::OnSetFocusPasswordCtrl)
	ON_MESSAGE(PASSWORD_CTRL_MOUSE_HOVER,&CLoginDlg::OnMouseHoverPasswordCtrl)
	ON_MESSAGE(PASSWORD_CTRL_MOUSE_LEAVE,&CLoginDlg::OnMouseLeavePasswordCtrl)
	ON_MESSAGE(ACCOUNT_CTRL_MOUSE_HOVER,&CLoginDlg::OnMouseHoverAccountCtrl)
	ON_MESSAGE(ACCOUNT_CTRL_MOUSE_LEAVE,&CLoginDlg::OnMouseLeaveAccountCtrl)
	ON_MESSAGE(COMMONLIB_UM_NONDOMODAL_MSGBOX_CLOSE,&CLoginDlg::OnCloseReconnectMsgBox)

	ON_MESSAGE( WM_TIP_CLICK_BTN , &CLoginDlg::OnTipClickBtn )
	ON_MESSAGE( WM_TIP_CLICK_CLOSE , &CLoginDlg::OnTipClickClose )
	ON_WM_MOVING()
	ON_WM_MOVE()
END_MESSAGE_MAP()

// CLoginDlg 消息处理程序

int CLoginDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//DragonZ:  test for Account ComboBox
	m_testLoginComboBox.Create( CRect(0,0, 220, 21), this, IDC_COMBO_ACCOUNT_TEST);
	m_testLoginComboBox.SetTextColor( RGB(117,160,203));
	m_testLoginComboBox.ShowWindow(SW_SHOWNOACTIVATE);

	//Create Password Ctrl
	ASSERT(m_pPasswordCtrl != NULL);
	if (m_pPasswordCtrl == NULL ||
		! m_pPasswordCtrl->Create(CRect(0, 0, 0, 0), this, IDC_EDIT_PASSWORD) ) {
			return -1;
	}
	m_pPasswordCtrl->ModifyStyle(WS_BORDER, 0);
	//////////////////////////////////////////////////////////////////////////


	//Load Skin
	ASSERT(m_pSkinEngine != NULL);
	if (m_pSkinEngine != NULL){
		HRESULT result = m_pSkinEngine->LoadSkin(GetSafeHwnd(), L"LoginDlg");
		ASSERT(result == S_OK && __LINE__);
	}

	if (NULL == m_pQQLoginDlg)
	{
		m_pQQLoginDlg = new CQQLoginDlg;
		m_pQQLoginDlg->Create(CQQLoginDlg::IDD, this);
		m_pQQLoginDlg->SetWindowPos(NULL, 0,0,QQ_LOGIN_DLG_WIDTH,QQ_LOGIN_DLG_HEIGHT,SWP_HIDEWINDOW);
	}	

	return 0;
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ModifyStyleEx(0, WS_EX_APPWINDOW );
	this->SetWindowText(_T("登录"));

	//标题字体首选微软雅黑
	std::wstring strFont;
	common::utility::systemhelper::GetDefaultFontName(strFont);
	CComVariant var = (CComVariant) strFont.c_str();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"textTitle",L"fontFamily",var);

	/*m_font.CreatePointFont(80,strFont.c_str(),NULL);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_COMBO_ACCOUNT);
	pEdit->SetFont(&m_font);*///账号输入框字体：微软雅黑

	// 初始化登陆账号下拉列表框
	//密码最大长度限制
	m_pPasswordCtrl->LimitText(16);	
	m_testLoginComboBox.LimitText(50);//这句一定要啊。不然默认是0，就啥也输不进去。

	m_pPasswordCtrl->SetFocus();//这个要加。否则第一次点击密码框会无焦点

	//////////////////////////////////////////////////////////////////////////

	m_ctrlAutoLogin.SetBtnTip(L"为了您的账号安全，请勿在公用电脑上勾选此项");

	LoadAccountComboBox();  //给用户列表控件加载179账号名列表

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


//////////////////////////////////////////////////////////////////////////
LRESULT CLoginDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_LOGIN:   //登录对话框中点击了“登录”按扭的消息
		{
			m_loginType = CLICK_LOGIN_BUTTON;  //用户点击"登录"按扭进行的登录
			AccountLogin(); //用户登录
		}
		break;	
		//////////////////51ktv added////////////////////////////////////////////////////////	
	case SKIN_ON_CLICK_GUESTLOGIN:  //登录对话框中点击了“游客登录”的消息
		{			
			m_loginType = CLICK_GUEST_LOGIN_BUTTON;  //用户点击"游客登录"按扭进行的登录
			AccountLogin(); //用户登录
		}
		break;

	case SKIN_ON_CLICK_MINIMIZE:  //最小化
		{
			PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			::PostMessage(m_pHallDlg->GetSafeHwnd(),WM_SYSCOMMAND, SC_MINIMIZE, 0);			
		}
		break;
	case SKIN_ON_DIALOG_RESIZE:  //最小化还原
		{
			if(IsWindowVisible())
			{
				m_pHallDlg->EnableWindow(TRUE);	
				SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
				::SendMessage(m_pHallDlg->GetSafeHwnd(),WM_SYSCOMMAND, SC_RESTORE, 0);
				m_pHallDlg->EnableWindow(FALSE);
				HideAccoutTip();
				HidePasswordTip();
				SetFocus();
			}			
		}
		break;
	case SKIN_ON_CLICK_CLOSE:
		{
			OnClickClose();
		}
		break;

		////////////////////end 51ktv added//////////////////////////////////////////////////////

	case SKIN_ON_CLICK_GETBACK_PASSWORD:
		OnClickFindPassword();
		break;
	case SKIN_ON_CLICK_REGISTER:
		OnClickRegister();
		break;	
		//case SKIN_ON_CLICK_IMAGE_AD:  //点击了登录框上方的图片消息
		//	{
		//		CString s179Official;
		//		CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_HALL179OFFICIAL,s179Official);
		//		s179Official = AppendUrlParamet(s179Official);
		//		common::utility::systemhelper::OpenUrl(wstring(s179Official));   //使用浏览器打开179官方首页		
		//	}
		//	break;
	case SKIN_ON_CLICK_LOGIN_AD:
		{
			OnClickLoginAd();
		}
		break;
	case SKIN_ON_CLICK_BTN_QQ_LOGIN:
		{
			OnClickBtnQQLogin();
		}
		break;
	default:
		break;
	}
	return TRUE;
}

//给用户列表控件加载179账号名列表
void  CLoginDlg::LoadAccountComboBox()
{
	m_testLoginComboBox.DeleteAllItem();

	list<UserInfoHead> userLast;
	CConfigManager::Instance()->GetUserInfo_List(userLast);	

	CString imgPath,CurAccount;
	list<UserInfoHead>::iterator iter;
	for(iter = userLast.begin();iter != userLast.end();iter++)
	{
		UserInfoHead &userInfo = *iter;	

		common::ui::CImageImpl* pImage = new common::ui::CImageImpl;
		imgPath = g_HallModule->GetLoaclHeadImage(userInfo.unUIN,userInfo.bMan);
		pImage->Load(imgPath);
		pImage->Resample(40,40,3);
		m_testLoginComboBox.AddItem(userInfo.unUIN, userInfo.strLoginAccount, userInfo.nickName, pImage);
	}	

	if(m_testLoginComboBox.GetCount() > 0)
	{
		m_testLoginComboBox.SetCurSel(0);
		m_testLoginComboBox.GetLBAccountText(0,CurAccount);
	}	
	else
	{
		ClearAccountInUI();
	}
	SelectAccountInfoInUI(CurAccount);		


}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void CLoginDlg::ClearPasswordInUI()
{
	m_pPasswordCtrl->ClearPassword();	
}

//清空界面上的用户名
void CLoginDlg::ClearAccountInUI()
{
	m_testLoginComboBox.SetWindowText(_T(""));		

}

CString CLoginDlg::GetPasswordInUI()
{
	ASSERT(::IsWindow(m_pPasswordCtrl->GetSafeHwnd()));
	if (! ::IsWindow(m_pPasswordCtrl->GetSafeHwnd()))
		return FALSE;
	CString s = m_pPasswordCtrl->GetPassword().c_str();
	return s;
}

BOOL CLoginDlg::SetPasswordInUI(LPCTSTR passwd)
{
	ASSERT(::IsWindow(m_pPasswordCtrl->GetSafeHwnd()));
	if (! ::IsWindow(m_pPasswordCtrl->GetSafeHwnd()))
		return FALSE;

	m_pPasswordCtrl->SetPassword(passwd);	

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//就是界面上的"记住密码"
BOOL CLoginDlg::GetSavePasswordInUI()
{
	ASSERT(::IsWindow(m_ctrlSavePassword.GetSafeHwnd()));
	if (! ::IsWindow(m_ctrlSavePassword.GetSafeHwnd()))
		return FALSE;

	return m_ctrlSavePassword.GetCheck() != 0;
}

BOOL CLoginDlg::SetSavePasswordInUI(BOOL bTrue)
{
	ASSERT(::IsWindow(m_ctrlSavePassword.GetSafeHwnd()));
	if (! ::IsWindow(m_ctrlSavePassword.GetSafeHwnd()))
		return FALSE;
	
	m_ctrlSavePassword.SetCheck(bTrue);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOL CLoginDlg::GetAutoLoginInUI()
{
	ASSERT(::IsWindow(m_ctrlAutoLogin.GetSafeHwnd()));
	if (! ::IsWindow(m_ctrlAutoLogin.GetSafeHwnd()))
		return FALSE;

	return m_ctrlAutoLogin.GetCheck() != 0;
}

BOOL CLoginDlg::SetAutoLoginInUI(BOOL bTrue)
{
	ASSERT(::IsWindow(m_ctrlAutoLogin.GetSafeHwnd()));
	if (! ::IsWindow(m_ctrlAutoLogin.GetSafeHwnd()))
		return FALSE;

	m_ctrlAutoLogin.SetCheck(bTrue);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

void CLoginDlg::NotifyCreateSkinItem()
{
	//Do Nothing
}

void CLoginDlg::OnOK()
{

}

void CLoginDlg::OnCancel()
{
	OnClose();
}

//下面的这个函数实际上很多地方都在进行一些前期的检查工作，到了最后才调用SendLoginRequest函数发送登录请求
void CLoginDlg::OnClickLogin()
{
	//DragonZ:	

	CString sAccount;//界面上的用户框中的用户名
	CString sPassword;//界面上的密码框中的密码
	m_testLoginComboBox.GetWindowText(sAccount);
	sPassword = GetPasswordInUI();//界面上的密码框中的密码	

	SendLoginRequest(sAccount, sPassword,NULL);

}

//点击了"找回密码"按扭时的响应函数
void CLoginDlg::OnClickFindPassword()
{
	CString passUrl;	
	CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_179FINDPASSWORD,passUrl); //找回密码

	common::utility::systemhelper::OpenUrl(wstring(passUrl));
}

//点击了"新注册"按扭时的响应函数
void CLoginDlg::OnClickRegister()
{

	m_pHallDlg->CreateAndShowRegisterDlg(true,this);  //创建并显示注册对话框
	if(!m_pHallDlg->RoomRegisterDlgIsShow())
	{
		EnableWindow(FALSE); //登录框不能操作
	}
	

}

//点击登录框广告图片
void CLoginDlg::OnClickLoginAd()
{
	OnClickRegister(); //弹出注册框
}

//点击"清删记录"按扭时的响应函数
HRESULT CLoginDlg::OnClickDeleteAccount(WPARAM w, LPARAM l)
{	
	int ret = C179MsgBox::Show(this,NewMsgBox::MSGBOX_ICO_OK_CANCEL_ONE_STRING ,NewMsgBox::ICONTYPE_WARNING,DELETE_ACCOUNT_TIP);	
	if (ret == RET_OK)
	{
		uint32 deleteUin = (uint32)w;
		CConfigManager::Instance()->RemoveUserInfo(deleteUin);	

		LoadAccountComboBox(); //重新给用户列表控件加载179账号名列表
	}

	return 1;
}

HRESULT CLoginDlg::OnSelectComboAccount(WPARAM w, LPARAM l)
{	

	HideAccoutTip();
	HidePasswordTip();
	return 1;
}


//保存当前登录成功后的用户信息至配置文件中
void CLoginDlg::SaveUserAccount()
{
	if(m_loginType == AUTOLOGIN_FIRST51)
	{
		return;
	}

	core::CurInfo m_MyCurInfo = GetCurInfo();
	if(m_MyCurInfo.enmAccountType == core::ACCOUNTTYPE_179)
	{
		list<UserInfoHead> saveUserList;
		UserInfoHead saveHead;
		UserInfoLogin saveUser;

		saveHead.strLoginAccount.Format(_T("%s"),m_MyCurInfo.strLoginAccount.c_str());
		saveHead.unUIN =  m_MyCurInfo.unUIN;
		saveHead.nickName.Format(_T("%s"),m_pHallDlg->GetCurNickName());
		saveHead.bMan = m_MyCurInfo.bMan;
		CConfigManager::Instance()->GetUserInfo_Login( m_MyCurInfo.unUIN, saveUser);	

		saveUser.strLoginPassword.Format(_T("%s"),m_pPasswordCtrl->GetPassword().c_str());
		saveUser.bAutoLogin = GetAutoLoginInUI();  //是否"自动登录"
		saveUser.bSavePassword = GetSavePasswordInUI();  //是否"记住密码"	

		CConfigManager::Instance()->GetUserInfo_List(saveUserList);	

		saveUserList.remove(saveHead); //若用户列表中已有该用户，则删除
		if(saveUserList.size() >= 10) //若用户列表数大于等于10，则从列表尾部删除一用户 
		{
			saveUserList.pop_back(); //从列表尾部删除一用户，即删除最老的用户
		}	
		saveUserList.push_front(saveHead); //用户列表头部插入当前用户

		CConfigManager::Instance()->SetUserInfo_List(saveUserList);	//保存用户列表
		CConfigManager::Instance()->SetUserInfo_Login(saveUser);                        //保存当前用户信息

		LoadAccountComboBox(); //重新给用户列表控件加载179账号名列表
	}	

}

void CLoginDlg::SelectAccountInfoInUI(CString strAccount)
{

	UserInfoHead selUser;	
	CConfigManager::Instance()->GetUserInfo_Head(strAccount,selUser);	

	if(selUser.unUIN >0 )
	{		
		UserInfoLogin selUserInfo;
		CConfigManager::Instance()->GetUserInfo_Login(selUser.unUIN,selUserInfo);	

		SetAutoLoginInUI(selUserInfo.bAutoLogin?TRUE:FALSE);	

		if(selUserInfo.bSavePassword) //如果是"记住密码"，则在界面上显示账户相关信息
		{					
			SetPasswordInUI(selUserInfo.strLoginPassword);
			SetSavePasswordInUI(TRUE);
		}
		else //不需要保存密码的情况:没有选中"自动登录"，也没有选中"记住密码"
		{
			ClearPasswordInUI(); //界面上密码框清空
			SetSavePasswordInUI(FALSE);//界面上"保存密码"复选框设置为没有选中的状态
			SetAutoLoginInUI(FALSE);  //界面上的"保存密码"设置为没有选中的状态
		}	

		m_isClear = true; //可以清空界面上的"保存密码"，"自动登录"，"密码"

	}
	else if(m_isClear == true) //没有某个账户
	{
		ClearPasswordInUI();
		SetSavePasswordInUI(FALSE);
		SetAutoLoginInUI(FALSE);  //界面上的"保存密码"设置为没有选中的状态

		m_isClear = false; //不可清空界面上的"保存密码"，"自动登录"，"密码"

		
	}

	//设置登录对话框用户应对头像
	CString imgPath;	
	imgPath = g_HallModule->GetLoaclHeadImage(selUser.unUIN,selUser.bMan);
	CComVariant varImage = g_HallModule->LoadImageWrapper(imgPath);
	HRESULT hr = m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgHeadPic", L"externalImage", varImage);
	
}

void CLoginDlg::HideLoginAllTip()
{	

	if (m_p179TipCtrl != NULL)
	{
		m_p179TipCtrl->ShowWindow(SW_HIDE);
	}
	HideAccoutTip();
	HidePasswordTip();
	HideQQLoginTip();
	HideAutoLoginTip();

}

//登录过程中大厅托盘动态切换显示
void CLoginDlg::LoginingHallTray()
{
	SetTimer(LOGIN_TRAY_TIMER_IDEVENT,LOGIN_TRAY_TIMER_INTERVALTIME,NULL);
}



void CLoginDlg::OnTimer(UINT_PTR nIDEvent)
{	
	CDialog::OnTimer(nIDEvent);
	if(nIDEvent == LOGIN_TRAY_TIMER_IDEVENT )
	{
		g_HallModule->LoginingTrayMgr(); //登录过程中大厅托盘动态切换显示
	}

}

//停止登录过程中大厅托盘动态切换显示
void CLoginDlg::StopLoginingHallTray()
{
	KillTimer(LOGIN_TRAY_TIMER_IDEVENT);	
}

BOOL CLoginDlg::SendGuestLoginRequest()
{
	core::LoginEvent * loginEvent = new core::LoginEvent();	
	loginEvent->enmAccountType = core::ACCOUNTTYPE_VISITOR;
	loginEvent->strPassword = VISITOR_PASSWORD_MD5;

	Event _event = MakeEvent<MODULE_ID_HALL>()(core::EVENT_VALUE_CORE_LOGIN, 
		MODULE_ID_CORE,0,0,0,loginEvent);

	m_pModuleManager->PushEvent(_event);
	return TRUE;
}

BOOL CLoginDlg::SendLoginRequest(LPCTSTR account, LPCTSTR password,CLoginVerifyHander *pHander)
{
	//记录

	BOOL bSuc = FALSE;

	///////////////////////////////给evtLogin赋值///////////////////////////////////////////
	core::LoginEvent * loginEvent = new core::LoginEvent();

	loginEvent->strAccount = account;//填写用户名

	if(m_loginType == AUTOLOGIN_QQLOGIN)
	{
		loginEvent->enmAccountType = core::ACCOUNTTYPE_QQ; //qq登录
	}	
	else
	{
		loginEvent->enmAccountType = core::ACCOUNTTYPE_179; //179账号
	}
	


	//现在的51ktv中为string类型的loginEvent->strPassword 
	wstring wstrPassword=password;
	loginEvent->strPassword = common::utility::stringhelper::UnicodeToAscii(wstrPassword);//填写密码

	if (pHander != NULL)
	{
		loginEvent->bVerify = true;
		loginEvent->strVerifyCode = pHander->GetStrVerifyCode();
		loginEvent->strVerifyKey = pHander->GetKey();
	}

	//////////////////////////////////////////////////////////////////////////	
	Event _event = MakeEvent<MODULE_ID_HALL>()(core::EVENT_VALUE_CORE_LOGIN, 
		MODULE_ID_CORE,0,0,0,loginEvent);

	m_pModuleManager->PushEvent(_event);	

	return bSuc;
}

//界面上的“账号”“密码”输入框以及登录”“游客登录”“注册”按扭是否可用
void CLoginDlg::UIEnable(bool bEnable)
{
	CComVariant var = bEnable?L"false":L"true";
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnLogin",L"disabled",var);  //“登录”按扭是否可用
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnGuestLogin",L"disabled",var); //“游客登录”按扭是否可用
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnRegister",L"disabled",var); //“注    册”按扭是否可用
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnQQLogin",L"disabled",var); //“QQ登录”按扭是否可用

	m_testLoginComboBox.EnableWindow((BOOL)bEnable);  //“用户名”控件是否可用
	m_pPasswordCtrl->EnableWindow((BOOL)bEnable); //“密码”框控件是否可用

}

BOOL CLoginDlg::OnFirstLogin()//程序首次启动
{
	//下面的GetAutoLoginInUI()表示是否自动登录，只有自动登录的话，上面从配置文件中加载的信息才有用
	if (GetAutoLoginInUI())
	{
		m_loginType = AUTOLOGIN_FIRST; //首次启动客户端时的自动登录
		AccountLogin(); //用户登录
	}
	else if(b51AutoLogin179())  //检查是否为从彩红登录白兔KTV的
	{
		m_loginType = AUTOLOGIN_FIRST51; 
		AccountLogin(); //用户登录
	}

	return TRUE;
}

//重新登录
void CLoginDlg::ReLogin()
{
	LoginingHallTray(); //登录过程中大厅托盘动态切换显示
	UIEnable(false); //界面上的“账号”“密码”输入框以及登录”“游客登录”“注册”按扭不可用

	Event _event = MakeEvent<MODULE_ID_HALL>()(core::EVENT_VALUE_CORE_RELOGIN, 
		MODULE_ID_CORE,0,0,0,NULL);

	m_pModuleManager->PushEvent(_event);

	CloseNonModalDlg((CDialog*&)m_pReconnectMsgBox);

	m_pReconnectMsgBox = C179MsgBox::ShowNonDomodal(this, 
		NewMsgBox::MSGBOX_ICO_OK_ONE_STRING_NONDOMODAL, NewMsgBox::ICONTYPE_WARNING, L"连接已断开，正在重新登陆");

}

void CLoginDlg::CloseReconnectMsgBox()
{
	CloseNonModalDlg((CDialog*&)m_pReconnectMsgBox);
}

//用户登录
void CLoginDlg::AccountLogin()
{	
	
	UIEnable(false); //界面上的“账号”“密码”输入框以及登录”“游客登录”“注册”按扭不可用
	m_pHallDlg->SetLoginToServer(false);	

	if(m_loginType != CLICK_GUEST_LOGIN_BUTTON)  //不是"游客登录"时需要检测账号、密码是否为空
	{
		CString sAccount;//界面上的用户框中的用户名
		CString sPassword;//界面上的密码框中的密码
		m_testLoginComboBox.GetWindowText(sAccount);
		sPassword = GetPasswordInUI();//界面上的密码框中的密码
		sAccount = sAccount.Trim();  //去除左右空格

		if (sAccount.IsEmpty() || sAccount == DEFAULT_ACCOUNT_TEXT ||  sPassword.IsEmpty() )
		{
			if (sAccount.IsEmpty() || sAccount == DEFAULT_ACCOUNT_TEXT)
			{					
				ShowAccoutTip(LOGIN_EMPTY_179ACCOUNT_TIP);		
			}
			if( sPassword.IsEmpty() )
			{				
				ShowPasswordTip(LOGIN_PWD_EMPTY_TIP);	
				//GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();

			}	
			UIEnable(true); //界面上的“账号”“密码”输入框以及登录”“游客登录”“注册”按扭可用
			DISPPARAMS dispParams = {0, 0, 0, 0};
			m_pSkinEngine->CallSubSkinMethod(GetSafeHwnd(),L"btnLogin",L"SetFocus",NULL,&dispParams);
			return;
		}	

		DISPPARAMS dispParams = {0, 0, 0, 0};
		m_pSkinEngine->CallSubSkinMethod(GetSafeHwnd(),L"btnLogin",L"SetFocus",NULL,&dispParams);


	}
	else
	{
		DISPPARAMS dispParams = {0, 0, 0, 0};
		m_pSkinEngine->CallSubSkinMethod(GetSafeHwnd(),L"btnGuestLogin",L"SetFocus",NULL,&dispParams);
	}

	m_isClear = true; //可以清空界面上的"保存密码"，"自动登录"，"密码"
	LoginingHallTray(); //登录过程中大厅托盘动态切换显示

	if(m_loginType == AUTOLOGIN_FIRST || m_loginType == AUTOLOGIN_179REGISTER || m_loginType == AUTOLOGIN_FIRST51)
	{
		PostMessage(WM_AUTO_LOGIN);  //发送自动登录消息
		return;
	}
	if(m_loginType == CLICK_LOGIN_BUTTON)
	{
		OnClickLogin(); //点击“登录”按扭时的登录
		return;
	}
	if(m_loginType == CLICK_GUEST_LOGIN_BUTTON)
	{
		SendGuestLoginRequest(); //点击“游客登录”按扭时的登录
		return; 
	}		

}

//登录成功
BOOL CLoginDlg::OnLoginSuccess()
{	

	if (m_pVerifydg && m_pVerifydg->GetSafeHwnd())
	{
		m_pVerifydg->OnCodeSuccess();//关闭对话框
	}
	core::CurInfo m_MyCurInfo = GetCurInfo();	
	SaveUserAccount();  //保存当前登录成功后的用户信息至配置文件中		

	m_pHallDlg->ChangeUserInit(); //切换用户之后的大厅初始化

	UIEnable(true); //界面上的“账号”“密码”输入框以及登录”“游客登录”“注册”按扭可用
	PostMessage(WM_CLOSE);		

	UserInfoLogin userinfo;	
	CConfigManager::Instance()->GetUserInfo_Login(m_MyCurInfo.unUIN,userinfo);

	uint32 opensund;
	opensund = userinfo.bOpenSound;
	m_pModuleManager->PushMessage(MakeMessage<MODULE_ID_HALL>()(Hall::MESSAGE_VALUE_HALL_OPENSOUND, opensund, 0, 0, 0));	

	if(m_loginType == AUTOLOGIN_QQLOGIN) //QQ登录成功
	{		
		SetQQLoginTip(true);
	}
	else
	{
		SetQQLoginTip(false);
	}

	m_pHallDlg->SetLoginToServer(true);

	CloseNonModalDlg((CDialog*&)m_pReconnectMsgBox);
	m_bCurQQLogin = FALSE;

	return TRUE;
}

//发送验证码请求返回响应函数
void CLoginDlg::OnVerfiyCodeResp(Event const &evt)
{
	if(m_pVerifydg != NULL)
	{
		m_pVerifydg->OnGetVerifyCodeRep(evt);
	}
	
}

void CLoginDlg::OnLoginResp(Event const &evt)
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	core::LoginRspEvent *pEvent=static_cast<core::LoginRspEvent*>(evt.m_pstExtraInfo);
	CString loginRespError,loginRespError2;
	bool isQQLoginError = false; //是否为QQ登录失败

	CloseNonModalDlg((CDialog*&)m_pReconnectMsgBox);
	CWnd *pParentWnd = this;

	if(pEvent->enmLoginResult != core::LOGIN_ERROR_SUCCESS) //登录失败
	{					
		UIEnable(true); //界面上的“账号”“密码”输入框以及登录”“游客登录”“注册”按扭可用
		if(m_loginType == AUTOLOGIN_QQLOGIN)
		{
			isQQLoginError  = true;
			pParentWnd = m_pQQLoginDlg;
		}

		m_pHallDlg->SetLoginToServer(false);
		
	}				

	if (m_bVerifyOpen && pEvent->enmLoginResult != core::LOGIN_ERROR_TOKEN_NEED_VERIFY && 
		pEvent->enmLoginResult != core::LOGIN_ERROR_TOKEN_VERIFY_ERROR && pEvent->enmLoginResult !=core::LOGIN_ERROR_TOKEN_VERIFY_TIMEOUT)
	{
		CloseVerifyDlg();  //验证码验证通过，关闭验证对话框
		if(m_loginType == AUTOLOGIN_QQLOGIN)
		{
			isQQLoginError  = false;
		}
	}
	
	if(pEvent->enmLoginResult != core::LOGIN_ERROR_SUCCESS && m_loginType == AUTOLOGIN_FIRST51)
	{
		if(pEvent->enmLoginResult == core::LOGIN_ERROR_TOKEN_NEED_VERIFY)
		{
			ShowPasswordTip(LOGINREP_PWDERROR_TIP);
		}
		
		ClearAccountInUI();
		ClearPasswordInUI();
	}	

	switch (pEvent->enmLoginResult)
	{					

	case core::LOGIN_ERROR_SUCCESS://登录成功
		{

		}
		break;
	case core::LOGIN_ERROR_TOKEN_PASSWORD_ERROR://密码错误
		{			
			if(m_loginType != AUTOLOGIN_QQLOGIN)
			{
				ShowPasswordTip(LOGINREP_PWDERROR_TIP);
				ClearPasswordInUI();
			}
			
		}
		break;
	case core::LOGIN_ERROR_TOKEN_ACCOUNT_ERROR://账号错误
		{			
			ShowAccoutTip(LOGINREP_ACCOUNT_NOEXIST_TIP);	
			//ClearAccountInUI();
			//ClearPasswordInUI();
		}
		break;
	case core::LOGIN_ERROR_TOKEN_ACCOUNT_FORBIDE://您的账号已被锁定
		{
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_TWO_STRING ,NewMsgBox::ICONTYPE_ERROR,LOGINREP_TOKEN_LOCKED,LOGINREP_TOKEN_LOCKED2); 
		}
		break;	
	case core::LOGIN_ERROR_TOKEN_NEED_VERIFY://需要验证码验证
		{
			m_bVerifyOpen = true;
			int ret =OpenVerifyDlg();	
			m_bVerifyOpen = false;			
		}
		break;
	case core::LOGIN_ERROR_TOKEN_VERIFY_ERROR://验证码验证失败，
		{
			OnVerfiyCodeError(VERIFY_TEXT_ERROR);
			m_bVerifyCodeError = true;
		}
		break; 
	case core::LOGIN_ERROR_TOKEN_VERIFY_TIMEOUT://验证码过期
		{
			OnVerfiyCodeError(VERIFY_TEXT_EXPIRED);
			m_bVerifyCodeError = true;
		}
		break;
	case core::LOGIN_ERROR_TOKEN_EMAIL_NOT_ACTIVATE://邮箱未激活，请激活后再登录
		{
			loginRespError.Format(_T("%s"),LOGINREP_EMAIL_TIP);
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_ONE_STRING ,NewMsgBox::ICONTYPE_ERROR,loginRespError);
		}
		break;	
	case core::LOGIN_ERROR_CLIENT_STATE_ERROR: //状态错误，请勿重复登陆(客户端bug)
		{
			loginRespError.Format(_T("%s"),LOGINREP_ACCOUNT_LOGINED_TIP);
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_ONE_STRING ,NewMsgBox::ICONTYPE_ERROR,loginRespError);
		}
		break;
	case core::LOGIN_ERROR_CLIENT_NET_TYPE_ERROR:
		{
			loginRespError.Format(_T("%s"),LOGINREP_NET_TYPE_ERROR_TIP);
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_ONE_STRING ,NewMsgBox::ICONTYPE_ERROR,loginRespError);
		}
		break;
	case core::LOGIN_ERROR_CLIENT_TOKEN_CONNECT_ERROR: //token连接失败		
	case core::LOGIN_ERROR_CLIENT_TOKEN_TIMEOUT_ERROR: //token登录超时		
	case core::LOGIN_ERROR_CLIENT_GET_TOKEN_HOST_ERROR://token域名解析失败
	case core::LOGIN_ERROR_CLIENT_GET_HALL_HOST_ERROR: //hall域名解析失败			
	case core::LOGIN_ERROR_CLIENT_HALL_CONNECT_ERROR: //hall连接失败		
	case core::LOGIN_ERROR_CLIENT_HALL_TIMEOUT_ERROR: //hall登录超时
	case core::LOGIN_ERROR_179_TIMEOUT: //hall登录超时(服务器返回)
		{			
			loginRespError.Format(_T("(错误码：%04d)                        "),pEvent->enmLoginResult);
			LoginRespMaintanError(LOGINREP_ERROR_TIP,loginRespError);			
			
		}
		break;	

	case core::LOGIN_ERROR_TOKEN_ERROR://账号认证失败	
	case core::LOGIN_ERROR_TOKEN_OTHER_ERROR:
		{
			loginRespError.Format(_T("(错误码：%04d)                 "),pEvent->enmLoginResult);
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_TWO_STRING ,NewMsgBox::ICONTYPE_ERROR,LOGINREP_TOKEN_ERROR,loginRespError);
		}
		break;

	case core::LOGIN_ERROR_TOKEN_REFUSED://账号认证错误次数过多，请稍后再试
		{
			loginRespError.Format(_T("请十分钟后再试   (错误码：%04d)"),pEvent->enmLoginResult);
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_TWO_STRING ,NewMsgBox::ICONTYPE_ERROR,LOGINREP_TOKEN_REFUSE,loginRespError);
		}
		break;

	case core::LOGIN_ERROR_179_VERSION_ERROR:  //版本不匹配
		{
			CString s179Official;
			CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_179OFFICIALDOWNLOAD,s179Official);
			loginRespError.Format(_T("%s"),LOGINREP_VERSION_ERROR_TIP);
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_OK_ONE_STRING_WITH_LINK ,loginRespError,_T(""),_T(""),LOGINREP_VERSION_LINKS_TIP,s179Official);
		}
		break;

	case core::LOGIN_ERROR_179_ACCOUNT_LOCK: //179账号被锁定
		{			
			if ( pEvent->lockDays >= 365*10 )
			{
				loginRespError2 = L"如有疑问，请联系官方客服" ;
				C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_OK_TWO_STRING ,NewMsgBox::ICONTYPE_ERROR,L"您当前的账号已被永久封停",loginRespError2);
			}
			else
			{
				
				loginRespError.Format( LOGINREP_ACCOUNT_LOCKED_TIP , pEvent->lockDays ) ;		
				C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_OK_TWO_STRING ,loginRespError ,L"如有疑问，请联系官方客服");
			}
						
		}
		break;

	case core::LOGIN_ERROR_179_IP_LOCK: //ip被锁定
		{	
			if ( pEvent->lockDays >= 3650 )
			{
				loginRespError = L"您当前的IP地址已被永久封停" ;
			}
			else
			{
				loginRespError.Format( L"您当前的IP地址已被封停%d天",pEvent->lockDays );
			}			
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_OK_TWO_STRING ,NewMsgBox::ICONTYPE_ERROR, loginRespError ,L"如有疑问，请联系官方客服" );			
		}
		break;

	case core::LOGIN_ERROR_179_MAC_LOCK: //mac被锁定
		{
			if(pEvent->lockDays >= 3650)
			{
				loginRespError = L"您当前的mac地址已被永久封停" ;
			}
			else
			{
				loginRespError.Format(L"您当前的mac地址已被封停%d天", pEvent->lockDays);
			}

			loginRespError2 = L"如有疑问，请联系官方客服";
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_OK_TWO_STRING ,NewMsgBox::ICONTYPE_ERROR,loginRespError,loginRespError2);			
		}
		break;
		
	case core::LOGIN_ERROR_179_MAINTAN: //179服务器在维护
		{
			loginRespError.Format(_T("%s         "),LOGINREP_MAINTAN_TIP);
			CString appTip = CAutoUpdate::GetAppTip();
			if(appTip.IsEmpty())
			{
				C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_ONE_STRING ,NewMsgBox::ICONTYPE_ERROR,loginRespError);
			}
			else
			{
				LoginRespMaintanError(loginRespError,_T(""));
			}
			
		}	
		break;

	default:
		{				

			if(pEvent->enmLoginResult >= core::LOGIN_ERROR_179_ERROR_BEGIN)
			{					
				loginRespError.Format(_T("(错误码：%04d)                        "),pEvent->enmLoginResult);				
				C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_TWO_STRING ,NewMsgBox::ICONTYPE_ERROR,LOGINREP_ERROR_TIP,loginRespError);
			}
			else
			{			
				loginRespError.Format(_T("(错误码：%04d)                        "),pEvent->enmLoginResult);				
				LoginRespMaintanError(LOGINREP_ERROR_TIP,loginRespError);
			}

		}
		break;
	}

	if(isQQLoginError) //QQ登录失败
	{
		m_pQQLoginDlg->QQloginError();
	}

	
}

void CLoginDlg::LoginRespMaintanError(CString respError1,CString respError2)
{
	CWnd *pParentWnd = this;
	CString appTip = CAutoUpdate::GetAppTip();  //获取NewVersion.ini文件中AppTip的tip值
	if(appTip.IsEmpty())
	{
		C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_ICO_OK_TWO_STRING ,NewMsgBox::ICONTYPE_ERROR,respError1,respError2);
	}
	else
	{	
		//字符串载取，最多显示三行，
		int rowLen = 38;  //每行显示字符串
		std::wstring strAppTip = appTip;				
		int Tiplen = common::utility::stringhelper::CalcStringAsciiLength(strAppTip);
		int TipSublen = 0;
		int TipRowLen = 0;
		std::wstring sAppTip[3];
		for( int i=1;i< 4;i++)
		{
			if(TipSublen >= Tiplen)
			{
				break;
			}
			if(i<3)
			{
				TipRowLen = rowLen*i-TipSublen;
			}
			else
			{
				TipRowLen = Tiplen;
			}
			TipSublen = common::utility::stringhelper::GetSubstrInAnsi(strAppTip,sAppTip[i-1],TipSublen+1,TipRowLen);
		}
		if(sAppTip[1].size() == 0)
		{
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_OK_ONE_STRING ,sAppTip[0].c_str());	
		}
		else if(sAppTip[2].size() == 0)
		{
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_OK_TWO_STRING ,sAppTip[0].c_str(),sAppTip[1].c_str());	
		}
		else
		{
			C179MsgBox::Show(pParentWnd,NewMsgBox::MSGBOX_OK_THREE_STRING ,sAppTip[0].c_str(),sAppTip[1].c_str(),sAppTip[2].c_str());	
		}

	}

}


//CMainFrameDlg::Create的OnStatusChanged函数中调用ShowWindow函数
void CLoginDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if( nStatus != 0)  
	{ 
		return;  //不响应父窗口发送的显示隐藏消息
	}

	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		CenterWindow(m_pHallDlg);	//登录框居中显示	
		LoadAccountComboBox();		
		ShowSelectQQTip();	
		ShowQQLoginTip();

		CComVariant var = L"LoginV3_btnQQLogin_N.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"normalImage", var);
		var = L"LoginV3_btnQQLogin_H.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"hoverImage", var);
		var = L"LoginV3_btnQQLogin_D.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"downImage", var);
		var = L"LoginV3_btnQQLogin_Dis.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"disabledImage", var);
		m_bCurQQLogin = FALSE;

		var = L"true";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnLogin",L"visible",var);  //“登录”按扭显示		
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnRegister",L"visible",var); //“注    册”按扭显示

		m_pQQLoginDlg->ShowWindow(SW_HIDE);
	}
	else
	{	
		m_pQQLoginDlg->ShowWindow(SW_HIDE);
		HideLoginAllTip();
	}

	
}

//点击“保存密码”复选框时的响应函数
void CLoginDlg::OnBnClickedCheckSavePassword()
{
	// TODO: Add your control notification handler code here	
	BOOL bCheck = GetSavePasswordInUI();//就是界面上的"是否记住密码"
	if(! bCheck)  //记住密码  不选中时,自动登录自动也不选中
	{
		SetAutoLoginInUI(FALSE);//界面上自动登录不选中	
	}
}

//点击“自动登录”复选框时的响应函数
void CLoginDlg::OnBnClickedCheckAutoLogin()
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = GetAutoLoginInUI();
	if (bCheck)
	{//如果为自动登录
		SetSavePasswordInUI(TRUE);		
	}
}

//////////////////////////////////////////////////////////////////////////
BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg && pMsg->message == WM_KEYDOWN && ( pMsg->wParam == VK_RETURN))  //在登录界面中按回车键
	{
		OnLoginDlgKeyReturn();
		return TRUE;
	}
	if(pMsg->message == WM_SYSCOMMAND)
	{
		if(pMsg->wParam == SC_MINIMIZE)  //最小化
		{
			m_pHallDlg->EnableWindow(TRUE);		//大厅EnableWindow设置为TRUE之后， 才能接收到之后的最小化消息
			::SendMessage(m_pHallDlg->GetSafeHwnd(),WM_SYSCOMMAND, SC_MINIMIZE, 0);
			m_pHallDlg->EnableWindow(FALSE);	
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CLoginDlg::On179RegisterQQLogin(WPARAM wParam, LPARAM lParam)
{
	SetQQLogin(TRUE); //设置QQ登录
	return S_OK;
}

//179注册成功后自动登录的响应函数
LRESULT CLoginDlg::On179RegisterLogin(WPARAM wParam, LPARAM lParam)
{
	Register179Account *pReg179 = (Register179Account *)wParam;		

	m_testLoginComboBox.SetWindowText(pReg179->m_Account);	
	SetSavePasswordInUI(FALSE);
	SetAutoLoginInUI(FALSE);  //界面上的"保存密码"设置为没有选中的状态

	std::string strPlainPass = common::utility::stringhelper::UnicodeToAscii(pReg179->m_Password.GetBuffer());
	pReg179->m_Password.ReleaseBuffer();

	std::string strMd5Pass = common::utility::md5::GetStringMd5(strPlainPass);  //MD5加密
	std::wstring strMd5PassW = common::utility::stringhelper::AsciiToUnicode(strMd5Pass);
	SetPasswordInUI(strMd5PassW.c_str());

	m_loginType = AUTOLOGIN_179REGISTER;  //179注册成功后的自动登录
	AccountLogin(); //用户登录

	return 1;
}

//QQ对应179账号自动登录的响应函数
LRESULT CLoginDlg::OnQQLogin179Account(WPARAM wParam, LPARAM lParam)
{
	QQLogin179Account *pQQ179 = (QQLogin179Account *)wParam;	

	LoginingHallTray(); //登录过程中大厅托盘动态切换显示
	UIEnable(false); //界面上的“账号”“密码”输入框以及登录”“游客登录”“注册”按扭不可用
	m_pHallDlg->SetLoginToServer(false);	

	m_loginType = AUTOLOGIN_QQLOGIN;  //QQ对应179账号的自动登录
	SendLoginRequest(pQQ179->m_Account, pQQ179->m_Password,NULL);

	return 1;
}

LRESULT CLoginDlg::OnSetQQLogin(WPARAM wParam, LPARAM lParam)
{
	BOOL bQQ = (BOOL)wParam;
	SetQQLogin(bQQ);
	
	return S_OK;
}

//用户点击了m_pReconnectMsgBox非模态关闭按扭的响应函数
LRESULT CLoginDlg::OnCloseReconnectMsgBox(WPARAM wParam, LPARAM lParam)
{

	CMsgBox *CloseMsgBox = (CMsgBox*)wParam;
	if(CloseMsgBox == m_pReconnectMsgBox)
	{
		CloseNonModalDlg((CDialog*&)m_pReconnectMsgBox);
	}

	return S_OK;
	
}

//登录对话框按了回车键的吶应函数
void CLoginDlg::OnLoginDlgKeyReturn()
{
	CWnd* pFocus = GetFocus();
	if (m_testLoginComboBox.IsChild(pFocus)) 
	{
		m_pPasswordCtrl->SetFocus();
	}
	else
	{
		m_loginType = CLICK_LOGIN_BUTTON;  //用户点击"登录"按扭进行的登录		
		AccountLogin(); //用户登录
	}
}


LRESULT CLoginDlg::OnAutoLogin(WPARAM wParam, LPARAM lParam)
{
	LoginingHallTray(); //登录过程中大厅托盘动态切换显示
	UIEnable(false); //界面上的“账号”“密码”输入框以及登录”“游客登录”“注册”按扭不可用

	CString account;
	m_testLoginComboBox.GetWindowText(account);
	SendLoginRequest(account, GetPasswordInUI(),(CLoginVerifyHander*)wParam);

	return TRUE;
}

//51彩红自动登录白兔KTV
bool CLoginDlg::b51AutoLogin179()
{
	//__targv为获取命令行参数

	CString strCaiHong = __targv[1]; //51彩红自动登录白兔KTV时参数为 caihong 	 
	if(strCaiHong != _T("caihong"))
	{
		return false;  //不是从51彩红登录白兔KTV的
	}

	CString strAccount = __targv[2]; //51彩红自动登录白兔KTV时参数为 对应的179号
	CString strPassword = __targv[3]; //51彩红自动登录白兔KTV时参数为 对应的MD5密码	
	 
	m_testLoginComboBox.SetWindowText(strAccount);
	m_pPasswordCtrl->SetPassword(wstring(strPassword));	

	OutputDebugString(_T("\nb51AutoLogin179"));
	OutputDebugString(strAccount);
	OutputDebugString(strPassword);	

	return true;  //从51彩红自动登录白兔KTV

}

LRESULT CLoginDlg::OnLoginDlgSetFocus(WPARAM wParam, LPARAM lParam)
{
	m_ctrlSavePassword.SetFocus();
	return TRUE;

}

//当用户输入4次密码错误后就会执行到这里
int CLoginDlg::OpenVerifyDlg()
{
	if(m_loginType == AUTOLOGIN_QQLOGIN || m_loginType == AUTOLOGIN_FIRST51)
	{
		return 0;  //防止QQ或51登录白兔KTV时对应的179号MD5密码错误过多时出现的验证码对话框， 注：正常情况下QQ或51登录时获取的对应179号和MD5加密密码是无错的，若有错则为web端返回的179号MD5加密密码出错了
	}

	if (m_pVerifydg != NULL)  
	{		
		CloseVerifyDlg();
		delete m_pVerifydg;
		m_pVerifydg = NULL;		
	}

	SwitchResourceToModule(_T("Hall"));
	m_pVerifydg = new CVerifyDlg(this);
	int ret = 0;
	if(m_pVerifydg != NULL)
	{
		 ret = m_pVerifydg->DoModal();
		delete m_pVerifydg;
		m_pVerifydg = NULL;
	}

	return ret;
}

void CLoginDlg::CloseVerifyDlg()
{
	ASSERT(m_pVerifydg != NULL);
	if (m_pVerifydg)
		m_pVerifydg->OnClickClose();
}

void CLoginDlg::OnVerfiyCodeError(CString errorText)
{
	ASSERT(m_pVerifydg != NULL);
	if (m_pVerifydg)
		m_pVerifydg->OnCodeError(errorText);
}


void CLoginDlg::OnClose()
{
	OnClickClose();
}

void CLoginDlg::OnClickClose()
{
	core::CurInfo curInfo = GetCurInfo();

	if (!curInfo.bLogined)
	{

		m_pModuleManager->PushEvent(MakeEvent<MODULE_ID_CORE>()(EVENT_VALUE_SYS_MAIN_LOOP_EXIT,MODULE_ID_HALL));
	}
	else
	{
		g_HallModule->ShowLoginDialog(false);
	}
}

void CLoginDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialog::OnMoving(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindowVisible())
	{   
		BOOL bDragWithContent;//拖动窗口时是否显示内容
		SystemParametersInfo(SPI_GETDRAGFULLWINDOWS,0,&bDragWithContent,NULL);
		if (bDragWithContent)
		{
					
			if (m_pQQLoginDlg && m_pQQLoginDlg->IsWindowVisible())
			{
				SendMessage(UM_QQLOGIN_MOVEWINDOW,0,0);
			}
			if (m_p179TipCtrl != NULL && m_p179TipCtrl->GetSafeHwnd() && m_p179TipCtrl->IsWindowVisible())
			{				
				ShowSelectQQTip();
			}
			if (m_pQQLoginTip != NULL && m_pQQLoginTip->GetSafeHwnd() && m_pQQLoginTip->IsWindowVisible())
			{
				ShowQQLoginTip();
			}
		}

		HideAccoutTip();
		HidePasswordTip();
	}
}

//设置登录方式
//TRUE 为QQ登录，FALSE为179登录
void CLoginDlg::SetQQLogin(BOOL bQQLogin)
{
	//设置QQ登录框位置

	HideAccoutTip();
	HidePasswordTip();

	if (bQQLogin)
	{		
		CComVariant var = L"LoginV3_btn179Login_N.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"normalImage", var);
		var = L"LoginV3_btn179Login_H.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"hoverImage", var);
		var = L"LoginV3_btn179Login_D.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"downImage", var);
		var = L"LoginV3_btn179Login_Dis.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"disabledImage", var);
		m_bCurQQLogin = TRUE;

		var =L"false";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnLogin",L"visible",var);  //“登录”按扭隐藏		
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnRegister",L"visible",var); //“注    册”按扭隐藏

		SendMessage(UM_QQLOGIN_MOVEWINDOW,0,0);
		HideSelectQQTip();
		HideQQLoginTip();
		
			
	}
	else
	{
		CComVariant var = L"LoginV3_btnQQLogin_N.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"normalImage", var);
		var = L"LoginV3_btnQQLogin_H.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"hoverImage", var);
		var = L"LoginV3_btnQQLogin_D.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"downImage", var);
		var = L"LoginV3_btnQQLogin_Dis.png";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"btnQQLogin", L"disabledImage", var);
		m_bCurQQLogin = FALSE;

		var = L"true";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnLogin",L"visible",var);  //“登录”按扭显示		
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnRegister",L"visible",var); //“注    册”按扭显示

		ShowSelectQQTip();
	}
	ShowQQLogin(bQQLogin);	
	
}

HRESULT CLoginDlg::OnWebPluginMessage( WPARAM w, LPARAM l)
{
	USES_CONVERSION;

	::OpenClipboard(::GetDesktopWindow());
	HGLOBAL hGlobal = ::GetClipboardData(RegisterClipboardFormatA(WEBPLUGIN_DATA_FORMAT));
	char* p = (char*)::GlobalLock(hGlobal);
	CString str = A2T(p);
	::GlobalUnlock(hGlobal);
	::CloseClipboard();

	g_HallModule->OnWebPluginCommand(str);

	return S_OK;
}

HRESULT CLoginDlg::OnCbnEditchangeComboAccount( WPARAM w, LPARAM l)
{
	if(IsWindowVisible())
	{
		CString straccount;
		m_testLoginComboBox.GetWindowText(straccount);

		if(straccount != DEFAULT_ACCOUNT_TEXT )
		{
			HideAccoutTip();
		}
		
		SelectAccountInfoInUI(straccount);
	}

	return 0;
}

HRESULT CLoginDlg::OnEditPasswordCtrl(WPARAM w, LPARAM l)
{	
	HidePasswordTip();
	return 0;
}
HRESULT CLoginDlg::OnSetFocusPasswordCtrl(WPARAM w, LPARAM l)
{
	HidePasswordTip();
	return 0;
}

HRESULT CLoginDlg::OnMouseHoverPasswordCtrl(WPARAM w, LPARAM l)
{
	CComVariant var = FALSE;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgItemEditPasswordBk", L"visible",var);
	var = TRUE;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgItemEditPasswordBkHover", L"visible",var);

	return 0;
}

HRESULT CLoginDlg::OnMouseLeavePasswordCtrl(WPARAM w, LPARAM l)
{
	CComVariant var = TRUE;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgItemEditPasswordBk", L"visible",var);
	var = FALSE;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgItemEditPasswordBkHover", L"visible",var);

	return 0;
}

HRESULT CLoginDlg::OnMouseHoverAccountCtrl(WPARAM w, LPARAM l)
{
	CComVariant var = FALSE;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgItemEditAccountBk", L"visible",var);
	var = TRUE;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgItemEditAccountBkHover", L"visible",var);

	return 0;
}

HRESULT CLoginDlg::OnMouseLeaveAccountCtrl(WPARAM w, LPARAM l)
{
	CComVariant var = TRUE;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgItemEditAccountBk", L"visible",var);
	var = FALSE;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"imgItemEditAccountBkHover", L"visible",var);

	return 0;
}



HRESULT CLoginDlg::OnTipClickBtn( WPARAM w, LPARAM l)
{
	
	return S_OK ;
}

HRESULT CLoginDlg::OnTipClickClose( WPARAM w, LPARAM l)
{
	C179TipCtrl *pTip = (C179TipCtrl*)w;
	if(pTip == m_p179TipCtrl)
	{
		HideSelectQQTip();
	}
	if (pTip == m_pQQLoginTip)//点击QQ登录提示框的关闭
	{
		HideQQLoginTip();
		SetQQLoginTip(false);
	}
	return S_OK ;
}

void CLoginDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
	// TODO: 在此处添加消息处理程序代码
	if (IsWindowVisible())
	{   
		BOOL bDragWithContent;//拖动窗口时是否显示内容
		SystemParametersInfo(SPI_GETDRAGFULLWINDOWS,0,&bDragWithContent,NULL);
		if (!bDragWithContent)
		{					
			if (m_pQQLoginDlg && m_pQQLoginDlg->IsWindowVisible())
			{
				SendMessage(UM_QQLOGIN_MOVEWINDOW,0,0); //调整位置
			}
			if (m_p179TipCtrl != NULL && m_p179TipCtrl->GetSafeHwnd() && m_p179TipCtrl->IsWindowVisible())
			{				
				ShowSelectQQTip();
			}
			if (m_pQQLoginTip != NULL && m_pQQLoginTip->GetSafeHwnd() && m_pQQLoginTip->IsWindowVisible())
			{
				ShowQQLoginTip();
			}
		}
	}
}

//QQ登录框设置位置的响应函数
LRESULT CLoginDlg::OnQQLoginMoveWindow(WPARAM wParam, LPARAM lParam)
{
	CRect rcLoginDlg(0,0,0,0);
	GetClientRect(&rcLoginDlg);
	ClientToScreen(&rcLoginDlg);
	int leftQQDlg = rcLoginDlg.left;
	int qqwidth, qqheight;
	m_pQQLoginDlg->GetQQHtmlSize(qqwidth,qqheight);
	int topQQDlg = rcLoginDlg.bottom - qqheight - QQ_LOGIN_DLG_BOTTOM_MARGIN;
	m_pQQLoginDlg->MoveWindow(leftQQDlg,topQQDlg,qqwidth,qqheight,TRUE);

	return S_OK;
}

void CLoginDlg::ShowAccoutTip(CString TipText)
{


	CRect rc(0,0,0,0);
	m_testLoginComboBox.GetWindowRect(&rc);
	CPoint pt(rc.left,rc.bottom - 9);
	if (!m_pAccoutTip->GetSafeHwnd())
	{
		m_pAccoutTip = new C179TipCtrl(eArrowPos::ARROW_TOP_LEFT);
		m_pAccoutTip->CreateEx(this,0);
		m_pAccoutTip->SetTipText(TipText);
		int nWidth,nHeight;
		m_pAccoutTip->ShowTip(TipText.GetLength(),nWidth,nHeight);
		m_pAccoutTip->MoveWindow(pt.x,pt.y,nWidth,nHeight,TRUE);
		m_pAccoutTip->ShowWindow(SW_SHOWNOACTIVATE);
	}
	else
	{
		m_pAccoutTip->SetTipText(TipText);
		int nWidth,nHeight;
		m_pAccoutTip->ShowTip(TipText.GetLength(),nWidth,nHeight);
		m_pAccoutTip->MoveWindow(pt.x,pt.y,nWidth,nHeight,TRUE);
		m_pAccoutTip->ShowWindow(SW_SHOWNOACTIVATE);

	}
}


void CLoginDlg::ShowPasswordTip(CString TipText)
{	

	CRect rc(0,0,0,0);
	m_pPasswordCtrl->GetWindowRect(&rc);
	CPoint pt(rc.left,rc.bottom - 9);
	if (!m_pPasswordTip->GetSafeHwnd())
	{
		m_pPasswordTip = new C179TipCtrl(eArrowPos::ARROW_TOP_LEFT);
		m_pPasswordTip->CreateEx(this,0);
		m_pPasswordTip->SetTipText(TipText);
		int nWidth,nHeight;
		m_pPasswordTip->ShowTip(TipText.GetLength(),nWidth,nHeight);
		m_pPasswordTip->MoveWindow(pt.x,pt.y,nWidth,nHeight,TRUE);
		m_pPasswordTip->ShowWindow(SW_SHOWNOACTIVATE);
	}
	else
	{
		m_pPasswordTip->SetTipText(TipText);
		int nWidth,nHeight;
		m_pPasswordTip->ShowTip(TipText.GetLength(),nWidth,nHeight);
		m_pPasswordTip->MoveWindow(pt.x,pt.y,nWidth,nHeight,TRUE);
		m_pPasswordTip->ShowWindow(SW_SHOWNOACTIVATE);

	}


}

void CLoginDlg::ShowSelectQQTip()
{
	CString strQQTip;
	bool qqTipIsShow;
	CConfigManager::Instance()->GetKeyValue(SECTION_QQSELECTTIP,KEY_QQTIPISSHOW,strQQTip,_T("1"));
	qqTipIsShow = (bool)_ttoi(strQQTip);
	if(!qqTipIsShow)
	{
		return;
	}
	

	CRect rc179LoginTab(0,0,0,0);
	m_pSkinEngine->GetSubSkinPos(GetSafeHwnd(), L"btnQQLogin", &(rc179LoginTab.left), &(rc179LoginTab.top), &(rc179LoginTab.right), &(rc179LoginTab.bottom));
	ClientToScreen(&rc179LoginTab);
	CPoint pt(rc179LoginTab.left,rc179LoginTab.top - QQ_LOGIN_TIP_TOP_MARGIN);
	int nWidth = 0 ;
	int nHeight = 0 ;
	if ( m_p179TipCtrl == NULL )
	{
		m_p179TipCtrl = new C179TipCtrl(eArrowPos::ARROW_BOTTOM_LEFT);
		m_p179TipCtrl->CreateEx(this,0);
		m_p179TipCtrl->SetTipText(L"点击这里，使用QQ登录");		
		m_p179TipCtrl->SetClose(TRUE);
		m_p179TipCtrl->ShowTip( 10 , nWidth , nHeight );
		m_p179TipCtrl->MoveWindow( pt.x ,pt.y , nWidth , nHeight ) ;
		m_p179TipCtrl->ShowWindow( SW_SHOWNOACTIVATE ) ;
	}
	else
	{
		m_p179TipCtrl->ShowTip( 10 , nWidth , nHeight );
		m_p179TipCtrl->MoveWindow( pt.x ,pt.y , nWidth , nHeight ) ;
		m_p179TipCtrl->ShowWindow( SW_SHOWNOACTIVATE ) ;
	}	

}

void CLoginDlg::ShowQQLoginTip()
{
	CString strQQTip;
	bool qqLoginTip;
	CConfigManager::Instance()->GetKeyValue(SECTION_QQSELECTTIP,KEY_QQLOGINTIP,strQQTip,_T("0"));
	qqLoginTip = (bool)_ttoi(strQQTip);
	if(!qqLoginTip)
	{
		return;
	}

	CRect rcQQtab(0,0,0,0);
	m_pSkinEngine->GetSubSkinPos(GetSafeHwnd(), L"btnQQLogin", &(rcQQtab.left), &(rcQQtab.top), &(rcQQtab.right), &(rcQQtab.bottom));
	ClientToScreen(&rcQQtab);
	CPoint pt(rcQQtab.left, rcQQtab.top - QQ_LOGIN_TIP_TOP_MARGIN);
	int nWidth = 0 ;
	int nHeight = 0 ;
	if ( m_pQQLoginTip == NULL )
	{
		m_pQQLoginTip = new C179TipCtrl(eArrowPos::ARROW_BOTTOM_LEFT);
		m_pQQLoginTip->CreateEx(this,0);
		m_pQQLoginTip->SetTipText(L"您上次使用的是QQ登录");		
		m_pQQLoginTip->SetClose(TRUE);
		m_pQQLoginTip->ShowTip( 40 , nWidth , nHeight );
		m_pQQLoginTip->MoveWindow( pt.x ,pt.y , nWidth , nHeight ) ;
		m_pQQLoginTip->ShowWindow( SW_SHOWNOACTIVATE ) ;
	}
	else
	{
		m_pQQLoginTip->ShowTip( 40 , nWidth , nHeight );
		m_pQQLoginTip->MoveWindow( pt.x ,pt.y , nWidth , nHeight ) ;
		m_pQQLoginTip->ShowWindow( SW_SHOWNOACTIVATE ) ;
	}	
}

void CLoginDlg::HideAccoutTip()
{
	if (m_pAccoutTip != NULL)
	{
		m_pAccoutTip->ShowWindow(SW_HIDE);		
	}
}
void CLoginDlg::HidePasswordTip()
{
	if (m_pPasswordTip != NULL)
	{
		m_pPasswordTip->ShowWindow(SW_HIDE);
	}

}

void CLoginDlg::HideSelectQQTip()
{
	if (m_p179TipCtrl != NULL)
	{
		m_p179TipCtrl->ShowWindow(SW_HIDE);
		CConfigManager::Instance()->SetKeyValue(SECTION_QQSELECTTIP,KEY_QQTIPISSHOW,_T("0"));
	}
}

void CLoginDlg::HideQQLoginTip()
{
	if (m_pQQLoginTip != NULL)
	{
		m_pQQLoginTip->ShowWindow(SW_HIDE);
	}	
}

void CLoginDlg::HideAutoLoginTip()
{
	if (m_ctrlAutoLogin.GetSafeHwnd())
	{
		m_ctrlAutoLogin.HideBtnTip();
	}
}

void CLoginDlg::SetQQLoginTip(bool isShow)
{
	CConfigManager::Instance()->SetKeyValue(SECTION_QQSELECTTIP,KEY_QQLOGINTIP,isShow ? _T("1") : _T("0"));
}

void CLoginDlg::ShowQQLogin(BOOL bShow)
{
	if (m_pQQLoginDlg && m_pQQLoginDlg->GetSafeHwnd())
	{
		if (bShow)
		{
			m_pQQLoginDlg->QQloginPreLoad();
			m_pQQLoginDlg->Show();		
			
		}
		else
		{
			m_pQQLoginDlg->Hide();  
		}
	}
}


void CLoginDlg::OnClickBtnQQLogin()
{
	SetQQLogin(!m_bCurQQLogin);
}

 //获取C179MsgBox显示时所需的父窗口
CWnd* CLoginDlg::Get179MsgBoxParent()
{
	if(m_bCurQQLogin)
	{
		//当前为QQ登录界面时，C179MsgBox显示时所需的父窗口为QQ登录框
		return m_pQQLoginDlg;
	}
	else
	{
		//当前不为QQ登录界面时，C179MsgBox显示时所需的父窗口为179登录框
		return this;
	}
}