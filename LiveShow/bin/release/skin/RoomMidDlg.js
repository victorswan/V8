
var SKIN_ON_SPLITTER_MOVE = 1;
var SKIN_ON_CLICK_BTN_EMOTION = 2;
var SKIN_ON_CLICK_BTN_COLORWORD = 3;
var SKIN_ON_CLICK_BTN_CLEANSCREEN = 4;
var SKIN_ON_CLICK_BTN_STAMP = 5;
var SKIN_ON_CLICK_BTN_SHORTCUT = 6;
var SKIN_ON_CLICK_BTN_COMPLAINT = 7;
var SKIN_ON_CLICK_JIACU = 9;
var SKIN_ON_CLICK_XIETI = 10;
var SKIN_ON_CLICK_UNDERLINE = 11;
var SKIN_ON_CLICK_FONT_COLOR = 12;
var SKIN_ON_CLICK_BTN_SENDMSG = 13;
var SKIN_ON_CLICK_BTN_AUTOREPLY = 14;
var SKIN_ON_CLICK_BTN_COPYURL = 15;
var SKIN_ON_CLICK_BTN_FLYTEXT = 16;
var SKIN_ON_CLICK_BTN_SENDFLYTEXT = 17;
var SKIN_ON_CLICK_BTN_FLYTEXTEFFECT = 18;
var SKIN_ON_CLICK_BTN_FONT = 21;
var SKIN_NOTIFY_SHOW_FONT = 22;
var SKIN_ON_CLICK_BTN_MORE = 23;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

// btnFont.AttachEvent("OnClick",OnClickBtnFont);
// btnEmotion.AttachEvent("OnClick",OnClickBtnEmotion);
// btnColorWord.AttachEvent("OnClick",OnClickBtnColorWord);
// btnCleanScreen.AttachEvent("OnClick",OnClickBtnCleanScreen);
// btnStamp.AttachEvent("OnClick",OnClickBtnStamp);
// btnComplaint.AttachEvent("OnClick",OnClickBtnComplaint);
// btnCopyUrl.AttachEvent("OnClick",OnClickBtnCopyUrl);

// btnJiaCu.AttachEvent("OnClick",OnClickBtnJiaCu);
// btnXieTi.AttachEvent("OnClick",OnClickBtnXieTi);
// btnUnderLine.AttachEvent("OnClick",OnClickBtnUnderLine);
// btnColor.AttachEvent("OnClick",OnClickBtnColor);

btnSendMsg.AttachEvent("OnClick",OnClickBtnSendMsg);
// btnFlyText.AttachEvent("OnClick", OnClickBtnFlyText);
// btnSendFlyText.AttachEvent("OnClick", OnClickBtnSendFlyText);
// btnFlyTextEffect.AttachEvent("OnClick", OnClickBtnFlyTextEffect);

btnEmotionAndFont.AttachEvent("OnClick",OnClickBtnEmotionAndFont);
btnMore.AttachEvent("OnClick", OnClickBtnMore);

// function OnClickBtnFont()
// {
   // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_FONT, 0);
// }

// function OnClickBtnEmotion()
// {
   // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EMOTION ,0);
// }

// function OnClickBtnColorWord()
// {
   // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_COLORWORD ,0);
// }

// function OnClickBtnCleanScreen()
// {
   // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CLEANSCREEN ,0);
// }

// function OnClickBtnStamp()
// {
   // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_STAMP ,0);
// }

// function OnClickBtnComplaint()
// {
   // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_COMPLAINT ,0);
// }

// function OnClickBtnCopyUrl()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_COPYURL, 0);
// }

// function OnClickBtnJiaCu()
// {
   // if(false == btnJiaCu.checked)
   // {
      // btnJiaCu.checked = true;
	  // Window.PostSkinMessage(SKIN_ON_CLICK_JIACU,1);
   // }else
   // {
      // btnJiaCu.checked = false;
	  // Window.PostSkinMessage(SKIN_ON_CLICK_JIACU,0);
   // }
// }

// function OnClickBtnXieTi()
// {
   // if(false == btnXieTi.checked)
   // {
      // btnXieTi.checked = true;
	  // Window.PostSkinMessage(SKIN_ON_CLICK_XIETI,1);
   // }else
   // {
      // btnXieTi.checked = false;
	  // Window.PostSkinMessage(SKIN_ON_CLICK_XIETI,0);
   // }
// }

// function OnClickBtnUnderLine()
// {
   // if(false == btnUnderLine.checked)
   // {
      // btnUnderLine.checked = true;
	  // Window.PostSkinMessage(SKIN_ON_CLICK_UNDERLINE,1);
   // }else
   // {
      // btnUnderLine.checked = false;
	  // Window.PostSkinMessage(SKIN_ON_CLICK_UNDERLINE,0);
   // }
// }

// function OnClickBtnColor()
// {
   // Window.PostSkinMessage(SKIN_ON_CLICK_FONT_COLOR,0);
// }

function OnClickBtnEmotionAndFont()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EMOTION ,0);
}

function OnClickBtnSendMsg()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SENDMSG,0);
}

function OnClickBtnMore()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_MORE, 0);
}

// function OnClickBtnFlyText()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_FLYTEXT,0);
// }

// function OnClickBtnSendFlyText()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SENDFLYTEXT,0);
// }

// function OnClickBtnFlyTextEffect()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_FLYTEXTEFFECT,0);
// }

////////////////////////////////////////////////
function OnInit()
{
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{
    //信息输入
	imgInputmsgBk.width = cx;
	imgInputmsgBk.height = 57;
	imgInputmsgBk.left = 0;
	imgInputmsgBk.top = cy - imgInputmsgBk.height;
	
	itemTalkTo.left = imgInputmsgBk.left + 1;
	itemTalkTo.top = imgInputmsgBk.top + 10;
	itemTalkTo.width = 100;
	itemTalkTo.height = 24;
	
	itemFlyText.left = itemTalkTo.left;
	itemFlyText.top = itemTalkTo.top + itemTalkTo.height + 2;
	itemFlyText.width = 50;
	itemFlyText.height = 22;
	
	itemPillowTalk.width = 50;
	itemPillowTalk.height = 22;
	itemPillowTalk.left = itemTalkTo.left + itemTalkTo.width - itemPillowTalk.width ;
	itemPillowTalk.top = itemFlyText.top;
	
	imgMsgEditBk.left = itemTalkTo.left + itemTalkTo.width + 5;
	imgMsgEditBk.top = imgInputmsgBk.top + 10;
	imgMsgEditBk.width = imgInputmsgBk.left + imgInputmsgBk.width - 50 - imgMsgEditBk.left;
	imgMsgEditBk.height = 39;
	
	btnEmotionAndFont.left = imgMsgEditBk.left + 4;
	btnEmotionAndFont.top = imgMsgEditBk.top + (imgMsgEditBk.height - btnEmotionAndFont.height)/2;
	
	itemHtmlInputMsg.left = btnEmotionAndFont.left + btnEmotionAndFont.width;
	itemHtmlInputMsg.top = imgMsgEditBk.top + 3;
	itemHtmlInputMsg.width = imgMsgEditBk.left + imgMsgEditBk.width - 84 - itemHtmlInputMsg.left;
	itemHtmlInputMsg.height = imgMsgEditBk.height - 6;

	btnSendMsg.left = imgMsgEditBk.left + imgMsgEditBk.width - 1 - btnSendMsg.width;
	btnSendMsg.top = imgMsgEditBk.top + (imgMsgEditBk.height - btnSendMsg.height)/2 + 1;
	
	btnMore.left = imgMsgEditBk.left + imgMsgEditBk.width + 2;
	btnMore.top = imgInputmsgBk.top + (imgInputmsgBk.height - btnMore.height)/2;
	
	
	//////////////////////////////////
	itemHtmlPublicChat.visible = true;
	itemHtmlPublicChat.left = 0;
	itemHtmlPublicChat.top = 0;
	itemHtmlPublicChat.width = cx;
	//itemHtmlPublicChat.height = imgInputmsgBk.top - 80 - itemHtmlPublicChat.top;
	itemHtmlPublicChat.height = cy * 3 / 5 - 10;
	
	Splitter.visible = true;
	Splitter.left = itemHtmlPublicChat.left;
	Splitter.top = itemHtmlPublicChat.top + itemHtmlPublicChat.height;
	Splitter.width = itemHtmlPublicChat.width;
	Splitter.height = 10;
	imgSplitter.visible = true;
	imgSplitter.left = Splitter.left;
	imgSplitter.top = Splitter.top;
	imgSplitter.width = Splitter.width;
	imgSplitter.height = Splitter.height;
	
	itemHtmlPrivateChat.visible = true;
	itemHtmlPrivateChat.left = imgSplitter.left;
	itemHtmlPrivateChat.top = imgSplitter.top + imgSplitter.height;
	itemHtmlPrivateChat.width = imgSplitter.width;
	itemHtmlPrivateChat.height = imgInputmsgBk.top - (imgSplitter.top + imgSplitter.height );
	
	ModifySplitter();
	
}

// function ShowFontToolBar(bShow)
// {
    // imgFontToolBar.visible = bShow;
    // btnJiaCu.visible = bShow;
    // btnXieTi.visible = bShow;
    // btnUnderLine.visible = bShow;
    // btnColor.visible = bShow;
    // itemComboFontSize.visible = bShow;
    // itemComboFont.visible = bShow;

    // imgFontToolBar.left = imgEditToolBar.left;
	// imgFontToolBar.width = imgEditToolBar.width;
	// imgFontToolBar.height = 28;
	// imgFontToolBar.top = imgEditToolBar.top - imgFontToolBar.height;
	
	// btnJiaCu.left = imgFontToolBar.left + 2;
	// btnJiaCu.top = imgFontToolBar.top + 2;
	
	// btnXieTi.left = btnJiaCu.left + btnJiaCu.width + 3;
	// btnXieTi.top = btnJiaCu.top;
	
	// btnUnderLine.left = btnXieTi.left + btnXieTi.width + 3;
	// btnUnderLine.top = btnXieTi.top;

    // btnColor.left = btnUnderLine.left + btnUnderLine.width + 3;
    // btnColor.top = btnUnderLine.top ;
	// btnColor.width = 24;
	// btnColor.height = 24;
	
	// itemComboFontSize.left = btnColor.left + btnColor.width + 5;
	// itemComboFontSize.top = btnColor.top + 2;
	// itemComboFontSize.width = 50;
	// itemComboFontSize.height = btnColor.height;
	
	// itemComboFont.left = itemComboFontSize.left + itemComboFontSize.width + 5;
	// itemComboFont.top = itemComboFontSize.top;
	// itemComboFont.width = 120;
	// itemComboFont.height = itemComboFontSize.height;
// }

function ModifySplitter(){
   Window.PostSkinMessage(SKIN_ON_SPLITTER_MOVE, 0);
}

function OnNotify(code, code1)
{
  switch(code)
  {
  case SKIN_NOTIFY_SHOW_FONT:
      {
		  // if(false == btnFont.checked)
		  // {
			 // btnFont.checked = true;
		  // }else
		  // {
			 // btnFont.checked = false;
		  // }
		  // OnSize(Window.width,Window.height);
	  }
	  break;
  default:
    break;
  }
}
