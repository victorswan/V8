
var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_BTN_CONFIRM = 2;

var NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE = 3;

var SKIN_ON_CLICK_BTN_DELETE = 4;
var SKIN_ON_CLICK_BTN_SAVE_TO_REASON = 5;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", btnCloseOnClick);
btnConfirm.AttachEvent("OnClick",OnClickBtnConfirm);
btnCancel.AttachEvent("OnClick",btnCloseOnClick);
btnDelete.AttachEvent("OnClick",OnClickBtnDelete);
btnSaveToReason.AttachEvent("OnClick",OnClickBtnSaveToReason);

function OnClickBtnDelete()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_DELETE, 0);
}

function OnClickBtnSaveToReason()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SAVE_TO_REASON, 0);
}

function btnCloseOnClick()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function OnClickBtnConfirm()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CONFIRM,0);
}

function OnInit()
{
	textTitle.text = "踢出房间";
	textTitle.visible = false;
	
	itemEditKickReason.visible = false;
	btnSaveToReason.visible = false;
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
	////////////////////////////////////////
	textPrompt1.visible = true;
	textPrompt1.left = 25;
	textPrompt1.top = 50;
	textPrompt1.width = 75;
	textPrompt1.height = textPrompt1.textHeight;
	
	textUser.visible = true;
	textUser.left = textPrompt1.left + textPrompt1.width;
	textUser.top = textPrompt1.top;
	textUser.width = 150;
	textUser.height = textUser.textHeight;
	
	textPrompt2.visible = true;
	textPrompt2.left = textUser.left + textUser.width;
	textPrompt2.top = textPrompt1.top;
	textPrompt2.width = cx - textPrompt2.left;
	textPrompt2.height = textPrompt1.height;
	
	textKickReason.visible = true;
	textKickReason.left = textPrompt1.left + 25;
	textKickReason.top = textPrompt1.top + textPrompt1.height + 25;
	textKickReason.width = textKickReason.textWidth;
	textKickReason.height = textKickReason.textHeight;
	
	itemComboKickReason.visible = true;
	itemComboKickReason.left = textKickReason.left + textKickReason.width + 8;
	itemComboKickReason.top = textKickReason.top - 2;
	itemComboKickReason.width = 120;
	itemComboKickReason.height = 20;
	
	btnDelete.visible = true;
	btnDelete.left = itemComboKickReason.left + itemComboKickReason.width + 15;
	btnDelete.top = itemComboKickReason.top - 10;
	btnDelete.width = 134;
	btnDelete.height = 42;
	
//	textNotDelete.visible = true;
	textNotDelete.left = itemComboKickReason.left;
	textNotDelete.top = itemComboKickReason.top + itemComboKickReason.height + 8;
	textNotDelete.width = textNotDelete.textWidth;
	textNotDelete.height = textNotDelete.textHeight;
	
//	itemEditKickReason.visible = false;
	itemEditKickReason.left = textNotDelete.left;
	itemEditKickReason.top = textNotDelete.top;
	itemEditKickReason.width = 120;
	itemEditKickReason.height = 35;
	
//	btnSaveToReason.visible = false;
	btnSaveToReason.left = btnDelete.left;
	btnSaveToReason.top = itemEditKickReason.top;
	btnSaveToReason.width = 134;
	btnSaveToReason.height = 42;
	
	textKickTime.visible = true;
	textKickTime.left = textKickReason.left;
	textKickTime.top = itemEditKickReason.top + itemEditKickReason.height + 10;
	textKickTime.width = textKickTime.textWidth;
	textKickTime.height = textKickTime.textHeight;
	
	itemComboKickTime.visible = true;
	itemComboKickTime.left = textKickTime.left + textKickTime.width + 8;
	itemComboKickTime.top = textKickTime.top - 2;
	itemComboKickTime.width = 120;
	itemComboKickTime.height = 20;
	
	btnConfirm.visible = true;
	//btnConfirm.width = 79;
	//btnConfirm.height = 35;
	btnConfirm.left = (cx - btnConfirm.width * 2 - 30)/2;
	btnConfirm.top = cy - 12 - btnConfirm.height;
	
	btnCancel.visible = true;
	//btnCancel.width = btnConfirm.width;
	//btnCancel.height = btnConfirm.height;
	btnCancel.left = btnConfirm.left + btnConfirm.width + 30;
	btnCancel.top = btnConfirm.top;
	
}

function OnNotify(code, code1)
{
	switch(code)
	{
	 case NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE:
	     {	    
		    if(0 == code1)//选择的是自定义理由
			{
			   textNotDelete.visible = false;
			   itemEditKickReason.visible = true;
			   btnSaveToReason.visible = true;
			   btnDelete.disabled = true;
			   OnSize(Window.width,Window.height);
			}
			else if(1 == code1)//选择的是已经定义好的自定义理由
			{
			   textNotDelete.visible = false;
			   itemEditKickReason.visible = false;
			   btnSaveToReason.visible = false;
			   btnDelete.disabled = false;
			   OnSize(Window.width,Window.height);
			}
			else//选择的是默认理由
			{
			   textNotDelete.visible = true;
			   itemEditKickReason.visible = false;
			   btnSaveToReason.visible = false;
			   btnDelete.disabled = true;
			   OnSize(Window.width,Window.height);
			}
			
		 }
		 break;
     default:break;
	}
}
