
var SKIN_ON_CLICK_CLOSE = 1;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", btnCloseOnClick);

function btnCloseOnClick()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
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
	imgTopBk.height = 30;

	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	textTheTitle.left = 10;
	textTheTitle.top = 8;
	
	itemHtmlPay.visible = true;
	itemHtmlPay.left = 2;
	itemHtmlPay.top = imgTopBk.top + imgTopBk.height;
	itemHtmlPay.width = imgTopBk.width;
	itemHtmlPay.height = cy - 2 - itemHtmlPay.top;
}

function OnNotify(code, code1)
{
	switch(code)
	{

    default:break;
	}
}
