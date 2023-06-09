var cx;
var cy;

var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_CHANGEUSER = 2;
var SKIN_ON_CLICK_EXIT = 3;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);

btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);

btnChangeUser.AttachEvent("OnClick",OnClickChangeUser);
btnExit.AttachEvent("OnClick",OnClickExit);

function OnClickbtnSysClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function OnClickChangeUser()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_CHANGEUSER,0);
}

function OnClickExit()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_EXIT,0);
}

function OnInit()
{
    textTitle.visible = false;
	imgTitleIcon.visible = false;
	
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
	
	textTheTitle.left = 10;
	textTheTitle.top = 8;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	btnChangeUser.visible = true;
	btnChangeUser.left = 25;
	btnChangeUser.top = imgMidBk.top + 10;
	btnChangeUser.width = 105;
	btnChangeUser.height = 105;
	
	btnExit.visible = true;
	btnExit.left = btnChangeUser.left + btnChangeUser.width + 40;
	btnExit.top = btnChangeUser.top;
	btnExit.width = btnChangeUser.width;
	btnExit.height = btnChangeUser.height;
    
	Window.EndPaint();
 
}




