
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
	textTitle.text = "变声卡";
    textTitle.visible = false;
	
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
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
	//////////////////////////////////////
	
	itemListChangeVoice.visible = true;
	itemListChangeVoice.left =  2;
	itemListChangeVoice.top = 55;
	itemListChangeVoice.width = cx - 4;
	itemListChangeVoice.height = cy - 32 - itemListChangeVoice.top;
	
	textTip.visible = true;
	textTip.left = itemListChangeVoice.left + 5;
	textTip.top = cy - 25;
	textTip.width = textTip.textWidth;
	textTip.height = 20;
	
	
}

function OnNotify(code, code1)
{
	switch(code)
	{
	 
     default:break;
	}
}
