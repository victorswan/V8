
var SKIN_ON_CLICK_BTN_POPUP = 1;
var SKIN_ON_CLICK_BTN_VIDEO = 2;
var SKIN_ON_CLICK_BTN_AUDIO = 3;
var SKIN_ON_CLICK_BTN_TAKEPHOTO = 4;
var SKIN_ON_MOUSE_LEAVE_BKG = 5;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnPopup.AttachEvent("OnClick",OnClickBtnPopup);
btnVideo.AttachEvent("OnClick",OnClickBtnVideo);
btnAudio.AttachEvent("OnClick",OnClickBtnAudio);
btnTakePhoto.AttachEvent("OnClick",OnClickBtnTakePhoto);

Window.AttachEvent("OnMouseLeave", OnMouseLeaveimgBackground);

function OnMouseLeaveimgBackground()
{
    Window.PostSkinMessage(SKIN_ON_MOUSE_LEAVE_BKG,0);
}

function OnClickBtnPopup()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_POPUP,0);
}

function OnClickBtnVideo()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_VIDEO,0);
}

function OnClickBtnAudio()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_AUDIO,0);
}

function OnClickBtnTakePhoto()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_TAKEPHOTO,0);
}

function OnInit()
{
	textTitle.visible = false;
	imgTitleIcon.visible = false;
	btnSysClose.visible = false;
	OnSize(Window.width, Window.height);
}

function OnSize(cx,cy)
{
	imgMicToolBarDlgBk.visible = true;
	imgMicToolBarDlgBk.left = 0;
	imgMicToolBarDlgBk.top = 0;
	imgMicToolBarDlgBk.width = cx;
	imgMicToolBarDlgBk.height = cy;
	///////////////////////////////////////////////////
	btnPopup.visible = true;
	
	btnPopup.width = 20;
	btnPopup.height = 20;
	btnPopup.left = imgMicToolBarDlgBk.left + imgMicToolBarDlgBk.width - 2 - btnPopup.width;
	btnPopup.top = imgMicToolBarDlgBk.top + (imgMicToolBarDlgBk.height - btnPopup.height)/2;
	
	btnVideo.visible = true;
	btnVideo.width = btnPopup.width;
	btnVideo.height = btnPopup.height;
	btnVideo.left = imgMicToolBarDlgBk.left + 2;
	btnVideo.top = btnPopup.top;
	
	
	btnAudio.visible = true;
	btnAudio.left = btnVideo.left + btnVideo.width + 2;
	btnAudio.top = btnVideo.top;
	btnAudio.width = btnVideo.width;
	btnAudio.height = btnVideo.height;
	
	btnTakePhoto.visible = true;
	btnTakePhoto.left = btnAudio.left + btnAudio.width + 2;
	btnTakePhoto.top = btnAudio.top;
	btnTakePhoto.width = btnAudio.width;
	btnTakePhoto.height = btnAudio.height;
	
}

function OnNotify(code,code1)
{
	switch(code)
	{
	  default: break;
	}
}

