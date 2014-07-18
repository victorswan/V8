var cx;
var cy;

var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_OK = 2;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);//在模态对话框下无效果

btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);
btnOK.AttachEvent("OnClick",OnClickbtnOK);

function OnClickbtnSysClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function OnClickbtnOK()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_OK, 0);
}

function OnInit()
{
	textTitle.text = "提示";
    textTitle.visible = false;

	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    Window.BeginPaint();

	imgTopBk.left = 2;
	imgTopBk.top = 2;
	imgTopBk.width = cx - 4;
	imgTopBk.height = 32;

	imgMidBk.left = 2;
	imgMidBk.top = imgTopBk.top + imgTopBk.height;
	imgMidBk.width = cx - 4;
	imgMidBk.height = cy - 2 - imgMidBk.top;
	
	imgEnterRoomPwdTitle.left = 10;
	imgEnterRoomPwdTitle.top = 8;
	imgEnterRoomPwdTitle.width = imgEnterRoomPwdTitle.textWidth;
	imgEnterRoomPwdTitle.height = imgEnterRoomPwdTitle.textHeight;
	
	textRoomPwd.visible = true;
	textRoomPwd.left = 17;
	textRoomPwd.top = 72;
	textRoomPwd.width = textRoomPwd.textWidth;
	textRoomPwd.height = textRoomPwd.textHeight;
	
	editEnterRoomPwd.visible = true;
	editEnterRoomPwd.left = textRoomPwd.left + textRoomPwd.width + 3;
	editEnterRoomPwd.top = textRoomPwd.top - 3;
	editEnterRoomPwd.width = 120;
	editEnterRoomPwd.height = 20;
	
	textPwdError.width = textPwdError.textWidth;
	textPwdError.height = textPwdError.textHeight;
	textPwdError.left = (cx - textPwdError.width)/2;
	textPwdError.top = editEnterRoomPwd.top + editEnterRoomPwd.height + 5;
	
	btnOK.visible = true;
	btnOK.width = 79;
	btnOK.height = 35;
	btnOK.left = (cx - btnOK.width)/2;
	btnOK.top = cy - 2 - btnOK.height;
	
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


