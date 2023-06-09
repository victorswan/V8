var SKIN_ON_CLICK_SEND = 1;
var SKIN_ON_CLICK_RECHARGE = 2;
var SKIN_NOTIFY_CHANGE_GIFT = 3;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);//在模态对话框下无效果

btnSend.AttachEvent("OnClick",OnClickBtnSend);
btnRecharge.AttachEvent("OnClick",OnClickBtnRecharge);

function OnClickBtnSend()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_SEND,0);
}

function OnClickBtnRecharge()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_RECHARGE,0);
}

function OnInit()
{
	OnSize(Window.width, Window.height);
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

function OnSize(cx, cy)
{	
    Window.BeginPaint();
	
	imgFramgQQLoginDlg.visible = true;
	imgFramgQQLoginDlg.left = 0;
	imgFramgQQLoginDlg.top = 0;
	imgFramgQQLoginDlg.width = cx;
	imgFramgQQLoginDlg.height = cy;
	
	
	imgGiftItem.visible = true;
	//imgGiftItem.left = 5 + (cx - 134 - imgGiftItem.originWidth)/2;
	//imgGiftItem.top = 5 + (cy - 30 - imgGiftItem.originHeight)/2;
	//imgGiftItem.width = imgGiftItem.originWidth;
	//imgGiftItem.height = imgGiftItem.originHeight;
	
	textName.left = cx - 127;
	textName.top = 10;
	textName.width = 120;
	textName.height = 15;
	
	btnSend.visible = false;
	btnSend.left = cx - 130;
	btnSend.top = 10;
	btnSend.width = 120;
	btnSend.height = 15;
	
	btnRecharge.visible = false;
	btnRecharge.left = cx - 50;
	btnRecharge.top = 10;
	btnRecharge.width = 45;
	btnRecharge.height = 15;
	
	textPriceTitle1.visible = true;
	//textPriceTitle1.left = imgGiftItem.left + imgGiftItem.width + 20;
	textPriceTitle1.left = cx - 127;
	textPriceTitle1.top = btnSend.top + 25;
	textPriceTitle1.width = textPriceTitle1.textWidth;
	textPriceTitle1.height = textPriceTitle1.textHeight;
	
	textPriceTitle2.visible = true;
	textPriceTitle2.left = textPriceTitle1.left;
	textPriceTitle2.top = textPriceTitle1.top + textPriceTitle1.textHeight + 6;
	textPriceTitle2.width = textPriceTitle2.textWidth;
	textPriceTitle2.height = textPriceTitle2.textHeight;
	
	textPriceUnit1.visible = true;
	textPriceUnit1.left = cx - textPriceUnit1.textWidth - 5;
	textPriceUnit1.top = textPriceTitle1.top;
	textPriceUnit1.width = textPriceUnit1.textWidth;
	textPriceUnit1.height = textPriceUnit1.textHeight;
	
	textPriceUnit2.visible = true;
	textPriceUnit2.left = cx - textPriceUnit2.textWidth - 5;
	textPriceUnit2.top = textPriceTitle2.top;
	textPriceUnit2.width = textPriceUnit2.textWidth;
	textPriceUnit2.height = textPriceUnit2.textHeight;
	
	textPrice1.visible = true;
	textPrice1.left = textPriceTitle1.left + textPriceTitle1.textWidth + 7;
	textPrice1.top = textPriceTitle1.top;
	textPrice1.width = textPrice1.textWidth;
	textPrice1.height = textPrice1.textHeight;
	
	textPrice2.visible = false;
	textPrice2.left = textPriceTitle2.left + textPriceTitle2.textWidth + 7;
	textPrice2.top = textPriceTitle2.top;
	textPrice2.width = textPrice2.textWidth;
	textPrice2.height = textPrice2.textHeight;
	
	textPrescriptionTitle.visible = false;
	textPrescriptionTitle.left = textPriceTitle1.left;
	textPrescriptionTitle.top = textPriceTitle1.top + textPriceTitle1.textHeight + 7;
	textPrescriptionTitle.width = textPrescriptionTitle.textWidth;
	textPrescriptionTitle.height = textPrescriptionTitle.textHeight;
	
	textPrescription.visible = false;
	textPrescription.left = textPrescriptionTitle.left + textPrescriptionTitle.textWidth + 7;
	textPrescription.top = textPrescriptionTitle.top;
	textPrescription.width = 100;
	textPrescription.height = textPrescription.textHeight;
	
	textCountTitle.visible = false;
	textCountTitle.left = textPriceTitle1.left;
	textCountTitle.top = btnSend.top;
	textCountTitle.width = textCountTitle.textWidth;
	textCountTitle.height = textCountTitle.textHeight;
	
	textCount.visible = false;
	textCount.left = textCountTitle.left + textCountTitle.textWidth + 7;
	textCount.top = textCountTitle.top;
	textCount.width = 100;
	textCount.height = textCount.textHeight;
	
	textDesc.visible = true;
	textDesc.left = 20;
	textDesc.top = cy - 20;
	textDesc.width = cx - 20;
	textDesc.height = textDesc.textHeight;
	
	Window.EndPaint();
 
}

function OnNotify(code, code1)
{
  switch(code)
  {
  case SKIN_NOTIFY_CHANGE_GIFT:
	{
		OnSize(Window.width,Window.height);
	}
  default:
    break;
  }
}


