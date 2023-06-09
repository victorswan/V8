
var SKIN_ON_CLICK_GUESTLOGIN = 3;
var SKIN_ON_CLICK_REGISTER = 4;
var SKIN_ON_CLICK_LOGIN = 5;
var SKIN_ON_CLICK_MINIMIZE = 6;
var SKIN_ON_CLICK_CLOSE = 7;
//var SKIN_ON_CLICK_CLEAR_RECORD = 8;
var SKIN_ON_CLICK_GETBACK_PASSWORD = 9;
var NOTIFY_LOGIN_BY_179NUM = 10;
var NOTIFY_LOGIN_BY_51NUM = 11;
//var SKIN_ON_CLICK_IMAGE_AD = 12;
var SKIN_ON_DIALOG_RESIZE = 13; 
var SKIN_ON_CLICK_LOGIN_AD = 14;
var SKIN_ON_CLICK_BTN_QQ_LOGIN = 15;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysMinimize.AttachEvent("OnClick", OnClickbtnSysMinimize);
btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);


btnGuestLogin.AttachEvent("OnClick",OnClickGuestLogin);
btnRegister.AttachEvent("OnClick",OnClickRegister);
btnLogin.AttachEvent("OnClick",OnClickLogin);

btnGetBackPassword.AttachEvent("OnClick",OnClickGetBackPassword);

//imgLoginDlgAd.AttachEvent("OnClick", OnClickLoginAd);
btnQQLogin.AttachEvent("OnClick", OnClickQQLogin);

function OnClickbtnSysMinimize()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_MINIMIZE, 0);
}

function OnClickbtnSysClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function OnClickGetBackPassword()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_GETBACK_PASSWORD,0);
}

function OnClickGuestLogin(){
    Window.PostSkinMessage(SKIN_ON_CLICK_GUESTLOGIN,0);
}

function OnClickRegister(){
    Window.PostSkinMessage(SKIN_ON_CLICK_REGISTER,0);
}

function OnClickLogin(){
    Window.PostSkinMessage(SKIN_ON_CLICK_LOGIN,0);
	btnLogin.SetFocus();
}

function OnClickLoginAd()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_LOGIN_AD, 0);
}

function OnClickQQLogin()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_QQ_LOGIN, 0);
}

function OnKeyDown(key, flag)
{
	if (key == 0x0D) {	//回车
		itemEditPassword.SetFocus();
		return true;
	}
}

function OnInit()
{
    textTitle.visible = false;
    // textTitle.fontWeight = 500;
	// textTitle.fontSize = 11;
    // textTitle.normalColor = 0xffffff;
    // textTitle.colorTransform = true;
	//imgFrameBackground.skinClass = "loginWindowFrame";
	
	var EditItem = itemEditAccount.CreateChild("Skin_Item_Edit", "EditItem");
	var ButtonItem = itemEditAccount.CreateChild("Skin_Item_Button", "ButtonItem");
	EditItem.useOrigin = true;
	EditItem.hasBorder = false;
	ButtonItem.useOrigin = true;
	
    ButtonItem.normalImage0 = "Login_imgAccountArrow_N.png";
	ButtonItem.normalImage1 = "Login_imgAccountArrow_H.png";
	ButtonItem.normalImage2 = "Login_imgAccountArrow_D.png";

	EditItem.itemID = 5000;
	ButtonItem.itemID = 5001;

	if (EditItem != null) {
		EditItem.AttachEvent("OnKeyDown", OnKeyDown);
		EditItem.bkColorNormal = -1;
	}
	
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    Window.BeginPaint();
      
    Window.PostSkinMessage(SKIN_ON_DIALOG_RESIZE,0);
	
	btnSysClose.top = 5;
	btnSysClose.left = cx - 10 - btnSysClose.width;
	
	btnSysMinimize.top = btnSysClose.top;
	btnSysMinimize.left = btnSysClose.left - btnSysMinimize.width;
	
	imgLoginDlgBk.left = 2;
	imgLoginDlgBk.top = 2;
	imgLoginDlgBk.width = cx - 4;
	imgLoginDlgBk.height = cy - 4;
	
	// imgLoginDlgTitle.left = 12;
	// imgLoginDlgTitle.top = 14;
	
	// imgLoginDlgAd.left = imgLoginDlgTitle.left + imgLoginDlgTitle.width + 20;
	// imgLoginDlgAd.top = 32;
	
	imgHeadPic.left = 20;
	imgHeadPic.top = 140;
	imgHeadPic.width = 85;
	imgHeadPic.height = 85;
	
	imgHeadPicFrame.left = imgHeadPic.left - 5;
	imgHeadPicFrame.top = imgHeadPic.top - 5;
	imgHeadPicFrame.width = 95;
	imgHeadPicFrame.height = 95;
	
	imgItemEditAccountBk.left = imgHeadPicFrame.left + imgHeadPicFrame.width + 10;
	imgItemEditAccountBk.top = imgHeadPicFrame.top - 4;
	imgItemEditAccountBk.width = 234;
	imgItemEditAccountBk.height = 44;
	imgItemEditAccountBkHover.left = imgItemEditAccountBk.left;
	imgItemEditAccountBkHover.top = imgItemEditAccountBk.top;
	imgItemEditAccountBkHover.width = imgItemEditAccountBk.width;
	imgItemEditAccountBkHover.height = imgItemEditAccountBk.height;
	
	itemEditAccount.left = imgItemEditAccountBk.left + 5;
	itemEditAccount.top = imgItemEditAccountBk.top + 12;
	itemEditAccount.width = imgItemEditAccountBk.width - 10;
	itemEditAccount.height = imgItemEditAccountBk.height - 20;
	
	imgItemEditPasswordBk.left = imgItemEditAccountBk.left;
	imgItemEditPasswordBk.top = imgItemEditAccountBk.top + imgItemEditAccountBk.height + 5;
	imgItemEditPasswordBk.width = imgItemEditAccountBk.width;
	imgItemEditPasswordBk.height = imgItemEditAccountBk.height;
	imgItemEditPasswordBkHover.left = imgItemEditPasswordBk.left;
	imgItemEditPasswordBkHover.top = imgItemEditPasswordBk.top;
	imgItemEditPasswordBkHover.width = imgItemEditPasswordBk.width;
	imgItemEditPasswordBkHover.height = imgItemEditPasswordBk.height;
	
	itemEditPassword.left = imgItemEditPasswordBk.left + 6;
	itemEditPassword.top = imgItemEditPasswordBk.top + 5;
	itemEditPassword.width = imgItemEditPasswordBk.width - 11;
	itemEditPassword.height = imgItemEditPasswordBk.height - 10;
	
	btnRegister.left = imgItemEditAccountBk.left + imgItemEditAccountBk.width + 8;
	btnRegister.top = imgItemEditAccountBk.top + 12;
	btnRegister.width = 70;
	btnRegister.height = 20;
	
	btnGuestLogin.left = btnRegister.left;
	btnGuestLogin.top = btnRegister.top + btnRegister.height + 4;
	btnGuestLogin.width = 70;
	btnGuestLogin.height = 20;
	
	btnGetBackPassword.left = btnRegister.left;
	btnGetBackPassword.top = imgItemEditPasswordBk.top + 12;
	btnGetBackPassword.width = 70;
	btnGetBackPassword.height = 20;
	
	itemSavePassword.left = imgItemEditPasswordBk.left + 2;
	itemSavePassword.top = imgItemEditPasswordBk.top + imgItemEditPasswordBk.height + 8;

	itemAutoLogin.left = itemSavePassword.left + itemSavePassword.width + 15;
	itemAutoLogin.top = itemSavePassword.top;
	
	btnQQLogin.width = 209;
	btnQQLogin.height = 56;
	btnQQLogin.left = 10;
	btnQQLogin.top = cy - 10 - btnQQLogin.height;
	
	btnLogin.width = 215;
	btnLogin.height = 57;
	btnLogin.left = cx - 10 - btnLogin.width;
	btnLogin.top = btnQQLogin.top + 1;
	
	Window.EndPaint();
 
}


function OnNotify(code,code1)
{
	switch(code)
	{ 

	default: break;
	}
}



