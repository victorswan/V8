var cx;
var cy;

var SKIN_ON_CLICK_BTN_SENDWORDS = 1;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSendWords.AttachEvent("OnClick", OnClickBtnSendWords);

function OnClickBtnSendWords()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SENDWORDS, 0);
}

Window.AttachEvent("OnShowWindow", OnShowWindowWindow)
function OnShowWindowWindow(bShow)
{
  if (bShow) {
    imgGiftItem.Play();
  } else {
    imgGiftItem.Stop();
  }
}

function OnInit()
{
	textTitle.text = "游客注册";
    textTitle.visible = false;
	btnSysClose.visible = false;
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

	textReceiveName.width = 100;
	textReceiveName.height = 16;
	textReceiveName.left = cx - 4 - textReceiveName.width;
	textReceiveName.top = 50;
	
	textReceiveID.width = textReceiveName.width;
	textReceiveID.height = textReceiveName.height;
	textReceiveID.left = textReceiveName.left;
	textReceiveID.top = textReceiveName.top + textReceiveName.height;
	
	textSendTo.width = textSendTo.textWidth;
	textSendTo.height = textSendTo.textHeight;
	textSendTo.left = textReceiveName.left - textSendTo.width;
	textSendTo.top = textReceiveName.top + 2;
	
	textGiftCount.width = textReceiveName.width;
	textGiftCount.height = textReceiveName.height;
	textGiftCount.left = textReceiveName.left;
	textGiftCount.top = textReceiveID.top + textReceiveID.height + 5;
	
	textQuantity.width = textQuantity.textWidth;
	textQuantity.height = textQuantity.textHeight;
	textQuantity.left = textSendTo.left;
	textQuantity.top = textGiftCount.top + 2;
	
	//Window.DebugMessage(textSendTo.left - 2);
	imgGiftItem.visible = true;
	// imgGiftItem.width = 140;
	// imgGiftItem.height = 58;
	// imgGiftItem.left = (textSendTo.left - 2 - imgGiftItem.width)/2;
	// imgGiftItem.top = 50;
	
	textToSay.left = 24;
	textToSay.top = 125;
	textToSay.width = textToSay.textWidth;
	textToSay.height = textToSay.textHeight;
	
	imgItemEditGiftWordsBk.visible = true;
	imgItemEditGiftWordsBk.width = 330;
	imgItemEditGiftWordsBk.height = 25;
	imgItemEditGiftWordsBk.left = textToSay.left - 2;
	imgItemEditGiftWordsBk.top = textToSay.top + textToSay.height + 5;
	
	itemEditGiftWords.visible = true;
	itemEditGiftWords.left = imgItemEditGiftWordsBk.left + 2;
	itemEditGiftWords.top = imgItemEditGiftWordsBk.top + 6;
	itemEditGiftWords.width = imgItemEditGiftWordsBk.width - 4;
	itemEditGiftWords.height = imgItemEditGiftWordsBk.height - 8;
	
	textToInput.left = textToSay.left;
	textToInput.top = imgItemEditGiftWordsBk.top + imgItemEditGiftWordsBk.height + 5;
	textToInput.width = imgItemEditGiftWordsBk.width;
	textToInput.height = 16;
	
	btnSendWords.width = 134;
	btnSendWords.height = 42;
	btnSendWords.left = cx - 2 - 10 - btnSendWords.width;
	btnSendWords.top = cy - 2 - btnSendWords.height;
	
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


