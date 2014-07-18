
var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_MINIMIZE = 2;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", btnCloseOnClick);
btnSysMinimize.AttachEvent("OnClick", OnClickbtnSysMinimize);

function btnCloseOnClick()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function OnClickbtnSysMinimize()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_MINIMIZE, 0);
}

function OnInit()
{
    textTitle.visible = false;
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    imgTopBk.visible = true;
	imgTopBk.left = 2;
	imgTopBk.top = 2;
	imgTopBk.width = cx - 4;
	imgTopBk.height = 32;
	
	imgMidBk.left = 2;
	imgMidBk.top = imgTopBk.top + imgTopBk.height;
	imgMidBk.width = cx - 4;
	imgMidBk.height = cy - 2 - imgMidBk.top;

	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	textTheTitle.left = 10;
	textTheTitle.top = 8;
	
	itemHtmlGame.left = imgMidBk.left;
	itemHtmlGame.top = imgMidBk.top;
	itemHtmlGame.width = imgMidBk.width;
	itemHtmlGame.height = imgMidBk.height;
}

function OnNotify(code, code1)
{
	switch(code)
	{

    default:break;
	}
}
