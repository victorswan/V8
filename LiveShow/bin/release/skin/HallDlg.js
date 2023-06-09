var cx;
var cy;


var SKIN_DLG_IN_DLG = 1;
var SKIN_ON_CLICK_MINIMIZE = 2;
var SKIN_ON_CLICK_MAXIMIZE = 3;
var SKIN_ON_CLICK_CLOSE = 4;
//var SKIN_ON_SPLITTER_MOVE = 5;

//var SKIN_NOTIFY_SPLITTER_MOVE = 6;
var SKIN_ON_DIALOG_RESIZE = 7;

var SKIN_NOTIFY_SEARCH_DLG_HWND = 8;

var SKIN_ON_CLICK_TAB_HALLLIST = 9;
var SKIN_ON_CLICK_TAB_MYROOM = 10;

//var SKIN_ON_CLICK_SYSSET = 11;
var SKIN_ON_CLICK_HEAD = 12;

var SKIN_ON_CLICK_SAFEBOX = 13;
var SKIN_ON_CLICK_SYSSETTING = 14;
var SKIN_ON_CLICK_MGRCENTER = 15;

var SKIN_ON_CLICK_LOBBY_HOME = 16;
var SKIN_ON_CLICK_ACCOUNT_PAY = 17;
var SKIN_ON_CLICK_RANK = 18;
var SKIN_ON_CLICK_OFFICIAL_FORUM = 19;
var SKIN_ON_CLICK_REFRESH = 20;
var SKIN_ON_CLICK_CHANGE_LINE = 21;
var SKIN_ON_CLICK_HOME_PAGE = 22;
var SKIN_ON_CLICK_GAME = 23;
var SKIN_ON_CLICK_USER_HELP = 24;

var SKIN_ON_CLICK_VIP = 25;
var SKIN_ON_CLICK_BTN_BACK = 26;

var SKIN_NOTIFY_IS_GUEST = 27;//是游客登录
var SKIN_NOTIFY_NO_GUEST = 28;//非游客登录

var SKIN_ON_CLICK_BTN_LOGIN = 29;//游客登录时可以点登录和注册
var SKIN_ON_CLICK_BTN_REGISTER = 30;

var SKIN_ON_CLICK_BTN_SAFESETTING = 31 ;	//安全中心
//var SKIN_NOTIFY_MOVE_TREE_CTRL = 32;

var SKIN_ON_CLICK_SYS_FEEDBACK = 33;

var cxRoomList = 0;
//var oldSplitterLeft = 0;

var bIsGuest = false;//是否是游客进入大厅
var bFirstShow = true;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysMinimize.AttachEvent("OnClick", OnClickbtnSysMinimize);
btnSysMaximize.AttachEvent("OnClick", OnClickbtnSysMaximize);
btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);
btnSysFeedback.visible = false;//不能放在OnInit或OnSize里，否则刚开始时会不出现，要最大化一下才行，这个与btnSysClose的实现不同

btnSetting.AttachEvent("OnClick",OnClickSysSetting);
btnManager.AttachEvent("OnClick",OnClickMgrCenter);
btnSafeSetting.AttachEvent("OnClick",OnClickSafeSetting) ; //安全中心

btnLobbyHome.AttachEvent("OnClick",OnClickLobbyhome);
btnAccountPay.AttachEvent("OnClick",OnClickAccountPay);
btnRank.AttachEvent("OnClick",OnClickRank);
btnOfficialForum.AttachEvent("OnClick",OnClickOfficialForum);
linkHomePage.AttachEvent("OnClick",OnClickHomePage);
btnUserHelp.AttachEvent("OnClick",OnClickUserHelp);

//btnSysFeedback.AttachEvent("OnClick", OnClickbtnSysFeedback);

function OnClickLobbyhome()
{
   Window.PostSkinMessage(SKIN_ON_CLICK_LOBBY_HOME,0); 
   btnLobbyHome.checked = true;
   btnAccountPay.checked = false;
   btnRank.checked = false;
}
function OnClickAccountPay()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_ACCOUNT_PAY,0);
	btnLobbyHome.checked = false;
    btnAccountPay.checked = true;
    btnRank.checked = false;
}
function OnClickRank()
{   
    Window.PostSkinMessage(SKIN_ON_CLICK_RANK,0); 
	btnLobbyHome.checked = false;
    btnAccountPay.checked = false;
    btnRank.checked = true;
}
function OnClickOfficialForum(){ Window.PostSkinMessage(SKIN_ON_CLICK_OFFICIAL_FORUM,0); }
function OnClickRefresh(){ Window.PostSkinMessage(SKIN_ON_CLICK_REFRESH,0); }
function OnClickHomePage(){ Window.PostSkinMessage(SKIN_ON_CLICK_HOME_PAGE,0); }
function OnClickGame(){ Window.PostSkinMessage(SKIN_ON_CLICK_GAME,0); }
function OnClickUserHelp(){ Window.PostSkinMessage(SKIN_ON_CLICK_USER_HELP,0); }


//imgMyHead.AttachEvent("OnClick",OnClickHead);
imgMyHeadCtrlBack_N.AttachEvent("OnClick",OnClickHead);
imgMyHeadCtrlBack_H.AttachEvent("OnClick",OnClickHead);
imgVIP.AttachEvent("OnClick",OnClickVIP);


btnBack.AttachEvent("OnClick",OnClickBtnBack);

btnLogin.AttachEvent("OnClick",OnClickBtnLogin);
btnRegister.AttachEvent("OnClick",OnClickRegister);

function OnMouseHoverHeadCtrl()
{
	Window.DebugMessage("hover");
}

function OnMouseLeaveHeadCtrl()
{
	Window.DebugMessage("leave");
}

function OnClickBtnLogin()
{
   Window.PostSkinMessage(SKIN_ON_CLICK_BTN_LOGIN,0);
}

function OnClickRegister()
{
   Window.PostSkinMessage(SKIN_ON_CLICK_BTN_REGISTER,0);
}

function OnClickbtnSysMinimize()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_MINIMIZE, 0);
}

function OnClickbtnSysMaximize()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_MAXIMIZE, 0);
}

function OnClickbtnSysClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function OnClickHead()
{
    if(!bIsGuest)
	{
		Window.PostSkinMessage(SKIN_ON_CLICK_HEAD,0);
	}
    
}

function OnClickVIP()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_VIP,0);
}

function OnClickSafeBox()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_SAFEBOX,0);
}

function OnClickSysSetting()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_SYSSETTING,0);
}

function OnClickMgrCenter()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_MGRCENTER,0);
}

function OnClickSafeSetting()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SAFESETTING,0) ;
}

function OnClickBtnBack()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_BACK,0);
}

// function OnClickbtnSysFeedback()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_SYS_FEEDBACK,0);
// }


function OnInit()
{
    textTitle.visible = false;
	// btnSysRestore.normalImage = "HallV3_btnRestore_N.png";
	// btnSysRestore.hoverImage = "HallV3_btnRestore_H.png";
	// btnSysRestore.downImage = "HallV3_btnRestore_D.png";
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    Window.BeginPaint();
   
    OnSizeSubDlg(cx, cy);
	Window.PostSkinMessage(SKIN_ON_DIALOG_RESIZE, 0);
	Window.EndPaint();
 
}

function OnSizeSubDlg(cx,cy){

	// InfoGuid.visible = true;
	// InfoGuid.left = left;
	// InfoGuid.top = top;
	// InfoGuid.width = width;
	// InfoGuid.height = 86;
	
	InfoGuidLeftBk.left = 1;
	InfoGuidLeftBk.top = 1;
	
	InfoGuidRightBk.width = 477;
	InfoGuidRightBk.height = 75;
	InfoGuidRightBk.left = cx - 1 - InfoGuidRightBk.width;
	InfoGuidRightBk.top = InfoGuidLeftBk.top;
	
	InfoGuidMidBk.left = InfoGuidLeftBk.left + InfoGuidLeftBk.width;
	InfoGuidMidBk.top = InfoGuidLeftBk.top;
	InfoGuidMidBk.width = InfoGuidRightBk.left - InfoGuidMidBk.left;
	InfoGuidMidBk.height = InfoGuidLeftBk.height;
	
	imgHallLogo.left = InfoGuidLeftBk.left + 5;
	imgHallLogo.top = InfoGuidLeftBk.top + 3;
	
	textVersion.width = 120;
	textVersion.height = 10;
	textVersion.left = imgHallLogo.left + imgHallLogo.width;
	textVersion.top = imgHallLogo.top + imgHallLogo.height - textVersion.height - 3;

	imgHallBottomLeftBk.left = 1;
	imgHallBottomLeftBk.height = 57;
	imgHallBottomLeftBk.width = 190;
	imgHallBottomLeftBk.top = cy - 1 - imgHallBottomLeftBk.height;
	
	imgHallBottomRightBk.width = 188;
	imgHallBottomRightBk.height = 57;
	imgHallBottomRightBk.left = cx - 1 - imgHallBottomRightBk.width;
	imgHallBottomRightBk.top = imgHallBottomLeftBk.top;
	
	imgHallBottomMidBk.left = imgHallBottomLeftBk.left + imgHallBottomLeftBk.width;
	imgHallBottomMidBk.top = imgHallBottomLeftBk.top;
	imgHallBottomMidBk.width = imgHallBottomRightBk.left - imgHallBottomMidBk.left;
	imgHallBottomMidBk.height = imgHallBottomLeftBk.height;
	
	imgHallLeftBk.left = InfoGuidLeftBk.left;
	imgHallLeftBk.top = InfoGuidLeftBk.top + InfoGuidLeftBk.height;
	imgHallLeftBk.width = 250;
	imgHallLeftBk.height = imgHallBottomLeftBk.top - imgHallLeftBk.top;
	
	////////////////////////
	imgHallUserInfoBk.left = InfoGuidLeftBk.left;
	imgHallUserInfoBk.top = InfoGuidLeftBk.top + InfoGuidLeftBk.height;
	imgHallUserInfoBk.width = 250;
	imgHallUserInfoBk.height = imgHallBottomLeftBk.top - imgHallUserInfoBk.top;
	
	imgMyHead.left = imgHallUserInfoBk.left + 12;
	imgMyHead.top = imgHallUserInfoBk.top + 10;
	imgMyHead.width = 45;
	imgMyHead.height = 45;

	imgMyHeadCtrlBack_N.left = imgMyHead.left - 4;
	imgMyHeadCtrlBack_N.top = imgMyHead.top - 4;
	imgMyHeadCtrlBack_N.width = 52;
	imgMyHeadCtrlBack_N.height = 52;
	
	imgMyHeadCtrlBack_H.left = imgMyHeadCtrlBack_N.left;
	imgMyHeadCtrlBack_H.top = imgMyHeadCtrlBack_N.top;
	imgMyHeadCtrlBack_H.width = imgMyHeadCtrlBack_N.width;
	imgMyHeadCtrlBack_H.height = imgMyHeadCtrlBack_N.height;
	
	textName.visible = true;
	textName.left = imgMyHeadCtrlBack_N.left + imgMyHeadCtrlBack_N.width + 10;
	textName.top = imgMyHeadCtrlBack_N.top + 5;
	textName.height = textName.textHeight;
	textAccount.visible = true;
	textAccount.width = textAccount.textWidth;
	textAccount.height = textName.height;
	textAccount.top = textName.top;
	
	var totalWidth = imgHallUserInfoBk.left + imgHallUserInfoBk.width - textName.left;//这个是name+Accoune的总长度
	
	if(textName.width + textAccount.width > totalWidth)
	{
	   textName.width = totalWidth - textAccount.width;
	   textAccount.left = textName.left + textName.width;
	}else
	{
	   textName.width = textName.textWidth;
	   textAccount.left = textName.left + textName.width;
	}
	
	var bNoGuest = !bIsGuest;
  if(!bFirstShow)
  { //非游客登录

	imgVIP.visible = bNoGuest;
	btnSetting.visible = bNoGuest;
	btnManager.visible = bNoGuest;
	imgRichLevel.visible = bNoGuest;
        //安全中心
	btnSafeSetting.visible = bNoGuest ;
	//游客登录
    btnLogin.visible = bIsGuest;
	btnRegister.visible = bIsGuest;
	
  }else
  {
	imgVIP.visible = false;
	//btnProofBox.visible = false;
	imgRichLevel.visible = false;
	btnSetting.visible = false;
	btnManager.visible = false;

        //安全中心
	btnSafeSetting.visible = false ;
	//游客登录
    btnLogin.visible = false;
	btnRegister.visible = false;
  }
  	
	imgVIP.left = textName.left;
	imgVIP.top = imgMyHeadCtrlBack_N.top + imgMyHeadCtrlBack_N.height - imgVIP.height;
	
	imgRichLevel.left = imgVIP.left + imgVIP.width +5 ;
	imgRichLevel.top = imgVIP.top + 4;

    btnSafeSetting.left = imgRichLevel.left + imgRichLevel.width +5 ;
	btnSafeSetting.top = imgVIP.top ;
	
	btnManager.left = btnSafeSetting.left + btnSafeSetting.width + 5;
	btnManager.top = btnSafeSetting.top;
	
	btnSetting.left = btnManager.left + btnManager.width + 5;
	btnSetting.top = btnManager.top;


  //游客登录
	btnRegister.width = 67;
	btnRegister.height = 27;
	btnRegister.left = imgMyHeadCtrlBack_N.left + imgMyHeadCtrlBack_N.width + 10;
	btnRegister.top = imgMyHeadCtrlBack_N.top + imgMyHeadCtrlBack_N.height - btnLogin.height;
	
	btnLogin.left = btnRegister.left + btnRegister.width;
	btnLogin.top = btnRegister.top;
	btnLogin.width = btnRegister.width;
	btnLogin.height = btnRegister.height;
	
   //
	var dis = 5;
	
	btnLobbyHome.left = 260;
	btnLobbyHome.top = InfoGuidLeftBk.top + 7;
	btnLobbyHome.width = 48;
	btnLobbyHome.height = 61;
	
	btnAccountPay.left = btnLobbyHome.left + btnLobbyHome.width + dis;
	btnAccountPay.top = btnLobbyHome.top;
	btnAccountPay.width = 84;
	btnAccountPay.height = 61;
	
	btnRank.left = btnAccountPay.left + btnAccountPay.width + dis;
	btnRank.top = btnAccountPay.top;
	btnRank.width = 65;
	btnRank.height = 61;
	
	btnOfficialForum.left = btnRank.left + btnRank.width + dis;
	btnOfficialForum.top = btnRank.top;
	btnOfficialForum.width = 78;
	btnOfficialForum.height = 61;
	
	btnUserHelp.left = btnOfficialForum.left + btnOfficialForum.width;
	btnUserHelp.top = btnOfficialForum.top;
	btnUserHelp.width = 52;
	btnUserHelp.height = 61;
	
	linkHomePage.left = btnUserHelp.left + btnUserHelp.width + 15;
	linkHomePage.top = btnUserHelp.top;
	linkHomePage.width = 48;
	linkHomePage.height = 61;
	
	//////////////////
	var cxx = 224;
	var cyy = cy;

    OnSizeBrowser(cxx,cyy);
	
	imgLoginToServer.width = 24;
	imgLoginToServer.height = 18;
	
	textLoginToServer.width = textLoginToServer.textWidth;
	textLoginToServer.height = textLoginToServer.textHeight;
	
	imgLoginToServer.left =  (cx - 29 - textLoginToServer.width)/2;
	imgLoginToServer.top = imgHallBottomLeftBk.top + (imgHallBottomLeftBk.height - imgLoginToServer.height)/2;
	
	textLoginToServer.left = imgLoginToServer.left + imgLoginToServer.width + 5;
	textLoginToServer.top = imgLoginToServer.top + 3;
	
}



function OnNotify(code,code1){
    switch(code){
	  case SKIN_DLG_IN_DLG:
	      {
	      }
		  break;
	
	  case SKIN_NOTIFY_SEARCH_DLG_HWND:
		{
			itemSearchDlg.SetClient(code1);
		}
		break;
	  case SKIN_NOTIFY_IS_GUEST:
	    {
		    bIsGuest = true;
			bFirstShow = false;
			//imgMyHead.background = true;
			OnSize(Window.width,Window.height);
		}
		break;
	  case SKIN_NOTIFY_NO_GUEST:
	    {
		    bIsGuest = false;
			bFirstShow = false;
			//imgMyHead.background = true;
			OnSize(Window.width,Window.height);
		}
		break;
	
	  default: break;
	}


}

function OnSizeBrowser(cxx,cyy){
	//搜索栏
	itemSearchDlg.width = 232;
	itemSearchDlg.height = 44;
	itemSearchDlg.left = imgHallUserInfoBk.left + (imgHallUserInfoBk.width - itemSearchDlg.width)/2;
	itemSearchDlg.top = imgMyHeadCtrlBack_N.top + imgMyHeadCtrlBack_N.height + 10;
	
	//搜索不到房间时的结果
	imgBtnBackBk.left = imgHallUserInfoBk.left;
	imgBtnBackBk.top = itemSearchDlg.top + itemSearchDlg.height + 10;
	imgBtnBackBk.width = imgHallUserInfoBk.width;
	imgBtnBackBk.height = imgHallBottomLeftBk.top - imgBtnBackBk.top;
	
	textSearch.width = textSearch.textWidth;
	textSearch.height = textSearch.textHeight;
	textSearch.left = imgBtnBackBk.left + 10;
	textSearch.top =  imgBtnBackBk.top + 5;
	
	btnBack.width = 77;
	btnBack.height = 30;
	btnBack.left = imgBtnBackBk.left + imgBtnBackBk.width - 2 - btnBack.width;
	btnBack.top = imgBtnBackBk.top + 1;
	
	textNoFound.left = imgBtnBackBk.left + 4;
	textNoFound.top = imgBtnBackBk.top + 50;
	textNoFound.width = imgBtnBackBk.width - 8;
	textNoFound.height = textNoFound.textHeight;
	
	/////////////
	// if(btnBack.visible == true && textNoFound.visible==false)//是查找，且查找成功
    // {
	  // itemHallTree.left = 0;
      // itemHallTree.top = imgHallUserInfoBk.top + imgHallUserInfoBk.height;	
	  // itemHallTree.width = imgHallUserInfoBk.width;
	  // itemHallTree.height = imgHallBottomBk.top - itemHallTree.top;
	// }else
	// {
	  // itemHallTree.left = 2;
      // itemHallTree.top = imgSearchDlgBk.top + imgSearchDlgBk.height;	
	  // itemHallTree.width = imgHallSplitter.left - itemHallTree.left;
	  // itemHallTree.height = imgHallBottomBk.top - itemHallTree.top;
	// }
	  itemHallTree.left =  2;
      itemHallTree.top = itemSearchDlg.top + itemSearchDlg.height + 10;	
	  itemHallTree.width = imgHallUserInfoBk.left + imgHallUserInfoBk.width - 5 - itemHallTree.left;
	  itemHallTree.height = imgHallBottomLeftBk.top - itemHallTree.top;
	///////////////////////////

	itemHtmlAllRoom.visible = true;
	itemHtmlAllRoom.left = imgHallUserInfoBk.left + imgHallUserInfoBk.width;
	itemHtmlAllRoom.top = InfoGuidMidBk.top + InfoGuidMidBk.height;
	itemHtmlAllRoom.width = Window.width - 1 - itemHtmlAllRoom.left;
	itemHtmlAllRoom.height = imgHallBottomLeftBk.top - itemHtmlAllRoom.top;

}
