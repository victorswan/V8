
var SKIN_ON_CLICK_ClOSE = 1 ; 
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

// btnClose.AttachEvent("OnClick" ,OnClickbtnClose ) ;
btnSysClose.AttachEvent("OnClick" ,OnClickbtnClose ) ;

function OnInit()
{
	// btnSysClose.visible = false;
	OnSize(Window.width, Window.height);
}

function OnClickbtnClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_ClOSE, 0);
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
	
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	textTheTitle.left = 10;
	textTheTitle.top = 8;
	
	ToolGiftList.visible = true ;
	ToolGiftList.left = 2 ;
	ToolGiftList.top = 42 ;
	ToolGiftList.width = cx - 4;
	ToolGiftList.height = cy - 40 - ToolGiftList.top;
	
	textSendTo.visible = true ;
	textSendTo.left = 5 ;
	textSendTo.top = ToolGiftList.top + ToolGiftList.height + 12 ;
	textSendTo.width = textSendTo.textWidth;
	textSendTo.height = textSendTo.textHeight;
	
	itemComboSendTo.visible = true ;
	itemComboSendTo.left = textSendTo.left + textSendTo.width + 1 ;
	itemComboSendTo.top = textSendTo.top - 3;
	itemComboSendTo.width = 80 ;
	itemComboSendTo.height = 25 ;
	
	textAmount.visible = true ;
	textAmount.left = itemComboSendTo.left + itemComboSendTo.width + 10 ;
	textAmount.top = textSendTo.top ;
	textAmount.width = textAmount.textWidth ;
	textAmount.height = textAmount.textHeight ;
	
	itemComboAmount.visible = true ;
	itemComboAmount.left = textAmount.left + textAmount.width + 1 ;
	itemComboAmount.top = itemComboSendTo.top ;
	itemComboAmount.width = 62 ;
	itemComboAmount.height = 25 ;
	
}

function OnNotify(code, code1)
{
	
}
