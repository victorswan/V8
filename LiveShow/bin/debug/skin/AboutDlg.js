var cx;
var cy;

var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_BTN_LINK = 2;
var SKIN_ON_CLICK_BTN_USER_AGREEMENT = 3;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);//在模态对话框下无效果

btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);
btnOK.AttachEvent("OnClick",OnClickbtnSysClose);
//btnLink.AttachEvent("OnClick", OnClickBtnLink);
btnLinkToUserAgreement.AttachEvent("OnClick", OnClickBtnUserAgreement);

function OnClickbtnSysClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

// function OnClickBtnLink()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_LINK, 0);
// }

function OnClickBtnUserAgreement()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_USER_AGREEMENT, 0);
}

function OnInit()
{
	textTitle.text = "关于";
    textTitle.visible = false;
	// imgFrameBackground.visible = false;
	// imgFrameBackground.left = 1;
	// imgFrameBackground.top = 1;
	// imgFrameBackground.width = 1;
	// imgFrameBackground.height = 1;

	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    Window.BeginPaint();

	imgAboutDlgBk.left = 2;
	imgAboutDlgBk.top = 2;
	imgAboutDlgBk.width = cx - 4;
	imgAboutDlgBk.height = cy - 4;
	
	textTheTitle.visible = false;   //
	textTheTitle.left = 10;
	textTheTitle.top = 8;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	textName.left = 140;
	textName.top = 30;
	textName.width = textName.textWidth;
	textName.height = textName.textHeight;
	
	textVersion.left = textName.left + textName.width;
	textVersion.top = textName.top;
	textVersion.width = 120;
	textVersion.height = textName.height;
	
	textCompany.left = textName.left;
	textCompany.top = textName.top + textName.height + 5;
	textCompany.width = textCompany.textWidth;
	textCompany.height = textCompany.textHeight;
	
	textRight.left = textCompany.left;
	textRight.top = textCompany.top + textCompany.height + 5;
	textRight.width = textRight.textWidth;
	textRight.height = textRight.textHeight;
	
	textRight2.left = textRight.left;
	textRight2.top = textRight.top + textRight.height + 5;
	textRight2.width = textRight2.textWidth;
	textRight2.height = textRight2.textHeight;
	
	// btnLink.left = textRight.left;
	// btnLink.top = textRight.top + textRight.height + 15;
	// btnLink.width = 110;
	// btnLink.height = 16;
	
	btnLinkToUserAgreement.width = 80;
	btnLinkToUserAgreement.height = 16;
	btnLinkToUserAgreement.top = textRight2.top + textRight2.height + 30;
	btnLinkToUserAgreement.left = textRight2.left;

	btnOK.left = imgAboutDlgBk.left + imgAboutDlgBk.width - btnOK.width - 15;
	btnOK.top = imgAboutDlgBk.top + imgAboutDlgBk.height - btnOK.height - 4;
	
	Window.EndPaint();
 
}

function OnNotify(code, code1)
{
  switch(code)
  {

  default:
    break;
  }
}


