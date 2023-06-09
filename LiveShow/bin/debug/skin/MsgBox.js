var cx;
var cy;

var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_OK = 2;
// var MSGBOX_STYLE_OK = 3;
// var MSGBOX_STYLE_OK_CANCEL = 4;
// var MSGBOX_STYLE_OK_WITH_LINK = 5;
// var MSGBOX_STYLE_OK_CANCEL_WITH_LINK = 6;
var SKIN_ON_CLICK_CANCEL = 7;
var NOTIFY_SKIN_REFRESH = 8;
// var MSGBOX_STYLE_OK_CANCEL_WITH_2_LINK = 8;
// var MSGBOX_STYLE_OK_WITH_TAIL_LINK = 12;
// var MSGBOX_STYLE_OK_WITH_CHECKBOX = 13;
// var MSGBOX_STYLE_OK_CANCEL_WITH_CHECKBOX = 14;

// var SKIN_ON_CLICK_BTN_LINK = 9;
// var SKIN_ON_CLICK_BTN_LINK_MID = 10;
// var SKIN_ON_CLICK_BTN_LINK_TAIL = 11;

///////////////////////新提示框样式//////////////////////////
//无图标的几个类型 
var MSGBOX_OK_ONE_STRING                    = 50;  //一行文字，确定
var MSGBOX_OK_TWO_STRING                    = 51;  //两行文字，确定
var MSGBOX_OK_ONE_STRING_WITH_LINK          = 52;  //一行文字，一个链接，确定
var MSGBOX_OK_TWO_STRING_WITH_LINK			= 53;  //两行文字，一个链接，确定
//带图标的几个类型
var MSGBOX_ICO_OK_ONE_STRING				= 54;  //图标，一行文字，确定
var MSGBOX_ICO_OK_TWO_STRING				= 55;  //图标，两行文字，确定
var MSGBOX_ICO_OK_CANCEL_ONE_STRING			= 56;  //图标，一行文字，确定，取消
var MSGBOX_ICO_OK_CANCEL_TWO_STRING			= 57;  //图标，两行文字，确定，取消
//游客操作提示类型
var MSGBOX_GUEST_OPERATE					= 58;	  //游客操作提示的普遍样式
var MSGBOX_OK_THREE_STRING                  = 59;
var MSGBOX_OK_THREE_STRING_WITH_LINK        = 60;
//带CheckBox提示类型
var	MSGBOX_OK_CANCEL_ONE_STRING_WITH_CHECKBOX = 61;	  //一行文字，确定，取消，CheckBox
var	MSGBOX_OK_CANCEL_TWO_STRING_WITH_CHECKBOX = 62;	  //两行文字，确定，取消，CheckBox
var	MSGBOX_OK_CANCEL_THREE_STRING_WITH_CHECKBOX = 63;  //三行文字，确定，取消，CheckBox
var MSGBOX_ICO_OK_ONE_STRING_NONDOMODAL = 64;         //非模态，图标，一行文字
//为点歌系统所用的类型
var MSGBOX_ORDERSONG_OK_TWO_STRING = 65;
var MSGBOX_ORDERSONG_OK_CANCEL_TWO_STRING = 66;
var MSGBOX_ORDERSONG_OK_CANCEL_ONE_STRING = 67;
//图标类型
var ICONTYPE_WARNING                        = 80;      
var ICONTYPE_BINGO                          = 81;
var ICONTYPE_ERROR                          = 82;
//////////////////////////////////////////////////////////////

var SKIN_ON_CLICK_BTN_NEW_LINK = 100;

var STYLE = 0;
var ICONTYPE = 0;
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);//在模态对话框下无效果

btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);
btnOK.AttachEvent("OnClick",OnClickbtnOK);
btnCancel.AttachEvent("OnClick",OnClickbtnCancel);

// btnLink.AttachEvent("OnClick", OnClickBtnLink);
// btnLinkMid.AttachEvent("OnClick", OnClickBtnLinkMid);
// btnLinkTail.AttachEvent("OnClick", OnClickBtnLinkTail);

///////////////
btnNewLink.AttachEvent("OnClick", OnClickBtnNewLink);
function OnClickBtnNewLink()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_NEW_LINK, 0);
}
/////////////////
// function OnClickBtnLink()
// {
    // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_LINK, 0);
// }

// function OnClickBtnLinkMid()
// {
    // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_LINK_MID, 0);
// }

// function OnClickBtnLinkTail()
// {
    // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_LINK_TAIL, 0);
// }

function OnClickbtnSysClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}
function OnClickbtnOK()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_OK,0);
}
function OnClickbtnCancel()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_CANCEL,0);
}

function OnInit()
{
    textTitle.visible = false;
    
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    Window.BeginPaint();
	
	btnSysClose.top = 2;
	
	STYLE = textMsgBoxStyle.text;//类型标记

	imgMsgBoxBk.visible = true;
	imgMsgBoxBk.left = 2;
	imgMsgBoxBk.top = 2;
	imgMsgBoxBk.width = cx - 4;
    imgMsgBoxBk.height = cy - 4;
	
	textTheTitle.left = 10;
	textTheTitle.top = 8;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	 
///////////////////////新提示框样式//////////////////////////
    ICONTYPE = textIconType.text;
	if(ICONTYPE_WARNING == ICONTYPE)
	{
		imgShowWarning.visible = true;
		imgShowWarning.left = 10;
		imgShowWarning.top = 45;
	}else if(ICONTYPE_BINGO == ICONTYPE)
	{
		imgShowBingo.visible = true;
		imgShowBingo.left = 10;
		imgShowBingo.top = 45;
	}else if(ICONTYPE_ERROR == ICONTYPE)
	{
		imgShowError.visible = true;
		imgShowError.left = 10;
		imgShowError.top = 45;
	}

	if(STYLE == MSGBOX_OK_ONE_STRING)	
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 65;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		btnOK.visible = true;
		//btnOK.width = 77;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_OK_TWO_STRING)	
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 55;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_OK_ONE_STRING_WITH_LINK)	
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 65;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		btnNewLink.visible = true;
		btnNewLink.left = textNewPrompt1.left;
		btnNewLink.top = textNewPrompt1.top + textNewPrompt1.height + 10;
		btnNewLink.width = textNewPrompt1.width;
		btnNewLink.height = textNewPrompt1.height;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_OK_TWO_STRING_WITH_LINK)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 55;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		btnNewLink.visible = true;
		btnNewLink.left = textNewPrompt2.left;
		btnNewLink.top = textNewPrompt2.top + textNewPrompt2.height + 5;
		btnNewLink.width = textNewPrompt2.width;
		btnNewLink.height = textNewPrompt2.height;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_ICO_OK_ONE_STRING)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 55;
		textNewPrompt1.top = 60;
		textNewPrompt1.width = cx - 10 - textNewPrompt1.left;
		textNewPrompt1.height = 18;

		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_ICO_OK_TWO_STRING)
	{
		textNewPrompt1.visible = true;
		//textNewPrompt1.horizAlign = "left";
		textNewPrompt1.left = 55;
		textNewPrompt1.top = 50;
		textNewPrompt1.width = cx - 20 - textNewPrompt1.left;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		//textNewPrompt2.horizAlign = "left";
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_ICO_OK_CANCEL_ONE_STRING)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 55;
		textNewPrompt1.top = 60;
		textNewPrompt1.width = cx - 20 - textNewPrompt1.left;
		textNewPrompt1.height = 18;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = 30;
		btnOK.top = cy - btnOK.height - 3;
		
		btnCancel.visible = true;
		btnCancel.width = btnOK.width;
		btnCancel.height = btnOK.height;
		btnCancel.left = cx - 30 - btnCancel.width;
		btnCancel.top = btnOK.top;
	}else if(STYLE == MSGBOX_ICO_OK_CANCEL_TWO_STRING)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 55;
		textNewPrompt1.top = 50;
		textNewPrompt1.width = cx - 10 - textNewPrompt1.left;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = 30;
		btnOK.top = cy - btnOK.height - 3;
		
		btnCancel.visible = true;
		btnCancel.width = btnOK.width;
		btnCancel.height = btnOK.height;
		btnCancel.left = cx - 30 - btnCancel.width;
		btnCancel.top = btnOK.top;
	}else if(STYLE == MSGBOX_GUEST_OPERATE)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 55;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.horizAlign="right";
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width/2 + 15;
		textNewPrompt2.height = textNewPrompt1.height;
		
		btnNewLink.visible = true;
		btnNewLink.labelHorizAlign = "left";
		btnNewLink.left = textNewPrompt2.left + textNewPrompt2.width;
		btnNewLink.top = textNewPrompt2.top + 2;
		btnNewLink.width = textNewPrompt2.width - 15;
		btnNewLink.height = textNewPrompt2.height;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_OK_THREE_STRING)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 45;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		textNewPrompt3.visible = true;
		textNewPrompt3.left = textNewPrompt2.left;
		textNewPrompt3.top = textNewPrompt2.top + textNewPrompt2.height;
		textNewPrompt3.width = textNewPrompt2.width;
		textNewPrompt3.height = textNewPrompt2.height;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_OK_THREE_STRING_WITH_LINK)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 35;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		textNewPrompt3.visible = true;
		textNewPrompt3.left = textNewPrompt2.left;
		textNewPrompt3.top = textNewPrompt2.top + textNewPrompt2.height;
		textNewPrompt3.width = textNewPrompt2.width;
		textNewPrompt3.height = textNewPrompt2.height;
		
		btnNewLink.visible = true;
		btnNewLink.left = textNewPrompt3.left;
		btnNewLink.top = textNewPrompt3.top + textNewPrompt3.height + 5;
		btnNewLink.width = textNewPrompt3.width;
		btnNewLink.height = textNewPrompt3.height;
		
		btnOK.visible = true;
		//btnOK.width = 79;
		//btnOK.height = 35;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 3;
	}else if(STYLE == MSGBOX_OK_CANCEL_ONE_STRING_WITH_CHECKBOX)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 65;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		btnCancel.visible = true;
		//btnCancel.width = 79;
		//btnCancel.height = 35;
		btnCancel.left = cx - btnCancel.width - 5;
		btnCancel.top = cy - btnCancel.height - 3;
		
		btnOK.visible = true;
		//btnOK.width = btnCancel.width;
		//btnOK.height = btnOK.height;
		btnOK.left = btnCancel.left - btnOK.width;
		btnOK.top =  cy - btnOK.height - 3;
		
		itemCheckNoPrompt.visible = true;
		itemCheckNoPrompt.top = btnOK.top + 12;
		itemCheckNoPrompt.left = 10;
	}else if(STYLE == MSGBOX_OK_CANCEL_TWO_STRING_WITH_CHECKBOX)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 55;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		btnCancel.visible = true;
		//btnCancel.width = 79;
		//btnCancel.height = 35;
		btnCancel.left = cx - btnCancel.width - 5;
		btnCancel.top = cy - btnCancel.height - 3;
		
		btnOK.visible = true;
		//btnOK.width = btnCancel.width;
		//btnOK.height = btnOK.height;
		btnOK.left = btnCancel.left - btnOK.width;
		btnOK.top =  cy - btnOK.height - 3;
		
		itemCheckNoPrompt.visible = true;
		itemCheckNoPrompt.top = btnOK.top + 12;
		itemCheckNoPrompt.left = 10;
	}else if(STYLE == MSGBOX_OK_CANCEL_THREE_STRING_WITH_CHECKBOX)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 2;
		textNewPrompt1.top = 45;
		textNewPrompt1.width = cx - 4;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		textNewPrompt3.visible = true;
		textNewPrompt3.left = textNewPrompt2.left;
		textNewPrompt3.top = textNewPrompt2.top + textNewPrompt2.height;
		textNewPrompt3.width = textNewPrompt2.width;
		textNewPrompt3.height = textNewPrompt2.height;
		
		btnCancel.visible = true;
		//btnCancel.width = 79;
		//btnCancel.height = 35;
		btnCancel.left = cx - btnCancel.width - 5;
		btnCancel.top = cy - btnCancel.height - 3;
		
		btnOK.visible = true;
		//btnOK.width = btnCancel.width;
		//btnOK.height = btnOK.height;
		btnOK.left = btnCancel.left - btnOK.width;
		btnOK.top =  cy - btnOK.height - 3;
		
		itemCheckNoPrompt.visible = true;
		itemCheckNoPrompt.top = btnOK.top + 12;
		itemCheckNoPrompt.left = 10;
	}else if(STYLE == MSGBOX_ICO_OK_ONE_STRING_NONDOMODAL)
	{
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 55;
		textNewPrompt1.top = 60;
		textNewPrompt1.width = cx - 20 - textNewPrompt1.left;
		textNewPrompt1.height = 18;
	}else if(STYLE == MSGBOX_ORDERSONG_OK_TWO_STRING)
	{
		 //取消圆角及圆角外框
		Window.upCornerRadius = "0";
		Window.downCornerRadius = "0";
		imgFrameBackground.visible = false;
		textTheTitle.color = "#0";
		
		//加入直角外框，背景变白，关闭按钮，确定取消按钮
		imgOrderSongTop.visible = true;
		imgOrderSongTop.left = 0;
		imgOrderSongTop.top = 0;
		imgOrderSongTop.width = cx;
		imgOrderSongTop.height = 2;
		
		imgOrderSongLeft.visible = true;
		imgOrderSongLeft.left = 0;
		imgOrderSongLeft.top = 2;
		imgOrderSongLeft.width = 1;
		imgOrderSongLeft.height = cy - 2;
		
		imgOrderSongRight.visible = true;
		imgOrderSongRight.left = cx - 1;
		imgOrderSongRight.top = imgOrderSongLeft.top;
		imgOrderSongRight.width = imgOrderSongLeft.width;
		imgOrderSongRight.height = imgOrderSongLeft.height;
		
		imgOrderSongBottom.visible = true;
		imgOrderSongBottom.left = imgOrderSongTop.left;
		imgOrderSongBottom.top = imgOrderSongLeft.top + imgOrderSongLeft.height - 1;
		imgOrderSongBottom.width = imgOrderSongTop.width;
		imgOrderSongBottom.height = 1;
		
		imgMsgBoxBk.image = "Global_imgWhiteBackground.png";//背景变白
		imgMsgBoxBk.left = 1;
		imgMsgBoxBk.top = 2;
		imgMsgBoxBk.width = cx - 2;
		imgMsgBoxBk.height = cy - 3;
		
		btnSysClose.normalImage = "Room_OrderSongMsgBox_btnClose_N.png";
		btnSysClose.hoverImage="Room_OrderSongMsgBox_btnClose_H.png";
		btnSysClose.downImage="Room_OrderSongMsgBox_btnClose_H.png";
		btnSysClose.top = 8;
		btnSysClose.left = cx - 8 - btnSysClose.width;
		
		btnOK.normalImage = "Room_OrderSongMsgBox_btnOK_N.png";
		btnOK.hoverImage="Room_OrderSongMsgBox_btnOK_H.png";
		btnOK.downImage="Room_OrderSongMsgBox_btnOK_H.png";
		
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 10;
		textNewPrompt1.top = 45;
		textNewPrompt1.width = cx - 20;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height + 5;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		btnOK.visible = true;
		btnOK.width = 70;
		btnOK.height = 25;
		btnOK.left = (cx - btnOK.width)/2;
		btnOK.top = cy - btnOK.height - 12;

	}else if(STYLE == MSGBOX_ORDERSONG_OK_CANCEL_TWO_STRING)	
	{
	    //取消圆角及圆角外框
		Window.upCornerRadius = "0";
		Window.downCornerRadius = "0";
		imgFrameBackground.visible = false;
		textTheTitle.color = "#0";
		
		//加入直角外框，背景变白，关闭按钮，确定取消按钮
		imgOrderSongTop.visible = true;
		imgOrderSongTop.left = 0;
		imgOrderSongTop.top = 0;
		imgOrderSongTop.width = cx;
		imgOrderSongTop.height = 2;
		
		imgOrderSongLeft.visible = true;
		imgOrderSongLeft.left = 0;
		imgOrderSongLeft.top = 2;
		imgOrderSongLeft.width = 1;
		imgOrderSongLeft.height = cy - 2;
		
		imgOrderSongRight.visible = true;
		imgOrderSongRight.left = cx - 1;
		imgOrderSongRight.top = imgOrderSongLeft.top;
		imgOrderSongRight.width = imgOrderSongLeft.width;
		imgOrderSongRight.height = imgOrderSongLeft.height;
		
		imgOrderSongBottom.visible = true;
		imgOrderSongBottom.left = imgOrderSongTop.left;
		imgOrderSongBottom.top = imgOrderSongLeft.top + imgOrderSongLeft.height - 1;
		imgOrderSongBottom.width = imgOrderSongTop.width;
		imgOrderSongBottom.height = 1;
		
		imgMsgBoxBk.image = "Global_imgWhiteBackground.png";//背景变白
		imgMsgBoxBk.left = 1;
		imgMsgBoxBk.top = 2;
		imgMsgBoxBk.width = cx - 2;
		imgMsgBoxBk.height = cy - 3;
		
		btnSysClose.normalImage = "Room_OrderSongMsgBox_btnClose_N.png";
		btnSysClose.hoverImage="Room_OrderSongMsgBox_btnClose_H.png";
		btnSysClose.downImage="Room_OrderSongMsgBox_btnClose_H.png";
		btnSysClose.top = 8;
		btnSysClose.left = cx - 8 - btnSysClose.width;
		
		btnOK.normalImage = "Room_OrderSongMsgBox_btnOK_N.png";
		btnOK.hoverImage="Room_OrderSongMsgBox_btnOK_H.png";
		btnOK.downImage="Room_OrderSongMsgBox_btnOK_H.png";
		
		btnCancel.normalImage = "Room_OrderSongMsgBox_btnCancel_N.png";
		btnCancel.hoverImage="Room_OrderSongMsgBox_btnCancel_H.png";
		btnCancel.downImage="Room_OrderSongMsgBox_btnCancel_H.png";
		
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 10;
		textNewPrompt1.top = 45;
		textNewPrompt1.width = cx - 20;
		textNewPrompt1.height = 18;
		
		textNewPrompt2.visible = true;
		textNewPrompt2.left = textNewPrompt1.left;
		textNewPrompt2.top = textNewPrompt1.top + textNewPrompt1.height + 5;
		textNewPrompt2.width = textNewPrompt1.width;
		textNewPrompt2.height = textNewPrompt1.height;
		
		btnOK.visible = true;
		btnOK.width = 70;
		btnOK.height = 25;
		btnOK.left = 30;
		btnOK.top = cy - btnOK.height - 12;
		
		btnCancel.visible = true;
		btnCancel.width = btnOK.width;
		btnCancel.height = btnOK.height;
		btnCancel.left = cx - 30 - btnCancel.width;
		btnCancel.top = btnOK.top;
	}else if(STYLE == MSGBOX_ORDERSONG_OK_CANCEL_ONE_STRING)
	{
		//取消圆角及圆角外框
		Window.upCornerRadius = "0";
		Window.downCornerRadius = "0";
		imgFrameBackground.visible = false;
		textTheTitle.color = "#0";
		
		//加入直角外框，背景变白，关闭按钮，确定取消按钮
		imgOrderSongTop.visible = true;
		imgOrderSongTop.left = 0;
		imgOrderSongTop.top = 0;
		imgOrderSongTop.width = cx;
		imgOrderSongTop.height = 2;
		
		imgOrderSongLeft.visible = true;
		imgOrderSongLeft.left = 0;
		imgOrderSongLeft.top = 2;
		imgOrderSongLeft.width = 1;
		imgOrderSongLeft.height = cy - 2;
		
		imgOrderSongRight.visible = true;
		imgOrderSongRight.left = cx - 1;
		imgOrderSongRight.top = imgOrderSongLeft.top;
		imgOrderSongRight.width = imgOrderSongLeft.width;
		imgOrderSongRight.height = imgOrderSongLeft.height;
		
		imgOrderSongBottom.visible = true;
		imgOrderSongBottom.left = imgOrderSongTop.left;
		imgOrderSongBottom.top = imgOrderSongLeft.top + imgOrderSongLeft.height - 1;
		imgOrderSongBottom.width = imgOrderSongTop.width;
		imgOrderSongBottom.height = 1;
		
		imgMsgBoxBk.image = "Global_imgWhiteBackground.png";//背景变白
		imgMsgBoxBk.left = 1;
		imgMsgBoxBk.top = 2;
		imgMsgBoxBk.width = cx - 2;
		imgMsgBoxBk.height = cy - 3;
		
		btnSysClose.normalImage = "Room_OrderSongMsgBox_btnClose_N.png";
		btnSysClose.hoverImage="Room_OrderSongMsgBox_btnClose_H.png";
		btnSysClose.downImage="Room_OrderSongMsgBox_btnClose_H.png";
		btnSysClose.top = 8;
		btnSysClose.left = cx - 8 - btnSysClose.width;
		
		btnOK.normalImage = "Room_OrderSongMsgBox_btnOK_N.png";
		btnOK.hoverImage="Room_OrderSongMsgBox_btnOK_H.png";
		btnOK.downImage="Room_OrderSongMsgBox_btnOK_H.png";
		
		btnCancel.normalImage = "Room_OrderSongMsgBox_btnCancel_N.png";
		btnCancel.hoverImage="Room_OrderSongMsgBox_btnCancel_H.png";
		btnCancel.downImage="Room_OrderSongMsgBox_btnCancel_H.png";
		
		textNewPrompt1.visible = true;
		textNewPrompt1.left = 10;
		textNewPrompt1.top = 54;
		textNewPrompt1.width = cx - 20;
		textNewPrompt1.height = 18;
		
		btnOK.visible = true;
		btnOK.width = 70;
		btnOK.height = 25;
		btnOK.left = 45;
		btnOK.top = cy - btnOK.height - 12;
		
		btnCancel.visible = true;
		btnCancel.width = btnOK.width;
		btnCancel.height = btnOK.height;
		btnCancel.left = cx - 45 - btnCancel.width;
		btnCancel.top = btnOK.top;
	}
	Window.EndPaint();
 
}

function OnNotify(code, code1)
{
  switch(code)
  {
  case NOTIFY_SKIN_REFRESH:
       {
	       OnSize(Window.width, Window.height);
	   }
	   break;
  default:
    break;
  }
}


