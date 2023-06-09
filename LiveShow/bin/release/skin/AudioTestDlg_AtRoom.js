
var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_NOTIFY_STEP1_HWND = 2;
var SKIN_NOTIFY_STEP2_HWND = 3;
var SKIN_ON_CLICK_BTN_CANCEL = 4;
var SKIN_ON_CLICK_BTN_PRESTEP = 5;
var SKIN_ON_CLICK_BTN_NEXTSTEP = 6;
var SKIN_ON_CLICK_BTN_DONE = 7;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", OnClickBtnClose);

btnFront.AttachEvent("OnClick", OnClickBtnFront);
btnBack.AttachEvent("OnClick",OnClickBtnBack);

function OnClickBtnClose()
{
   Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE,0);
}

function OnClickBtnFront()
{
   if(itemAudioSetStep1Dlg.visible)
   {
      Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CANCEL,0);
   }
   
   if(itemAudioSetStep2Dlg.visible)
   {
      Window.PostSkinMessage(SKIN_ON_CLICK_BTN_PRESTEP,0);
   }
   
}

function OnClickBtnBack()
{
   if(itemAudioSetStep1Dlg.visible)
   {
      Window.PostSkinMessage(SKIN_ON_CLICK_BTN_NEXTSTEP,0);
   }
   
   if(itemAudioSetStep2Dlg.visible)
   {
      Window.PostSkinMessage(SKIN_ON_CLICK_BTN_DONE,0);
   }
}

function OnInit()
{
    textTitle.visible = false;
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    imgAudioTestBk.visible = true;
	imgAudioTestBk.left = 2;
	imgAudioTestBk.top = 2;
	imgAudioTestBk.width = cx - 4;
	imgAudioTestBk.height = cy - 4;
	
	textTheTitle.left = 35;
	textTheTitle.top = 10;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	btnBack.visible = true;
	btnBack.width = 111;
	btnBack.height = 45;
	btnBack.left = cx - 40 - btnBack.width;
	btnBack.top = cy - btnBack.height + 3;
	
	btnFront.visible = true;
	btnFront.width = btnBack.width;
	btnFront.height = btnBack.height;
	btnFront.left = btnBack.left - 20 - btnFront.width;
	btnFront.top = btnBack.top;
	
	///////////////////////////
	itemAudioSetStep1Dlg.visible = true;
	itemAudioSetStep1Dlg.left = imgAudioTestBk.left;
	itemAudioSetStep1Dlg.top = 34;
	itemAudioSetStep1Dlg.width = imgAudioTestBk.width;
	itemAudioSetStep1Dlg.height = cy - 36 - itemAudioSetStep1Dlg.top;
	
	itemAudioSetStep2Dlg.visible = false;
	itemAudioSetStep2Dlg.left = itemAudioSetStep1Dlg.left;
	itemAudioSetStep2Dlg.top = itemAudioSetStep1Dlg.top;
	itemAudioSetStep2Dlg.width = itemAudioSetStep1Dlg.width;
	itemAudioSetStep2Dlg.height = itemAudioSetStep1Dlg.height;
	
	

}

function OnNotify(code, code1)
{
	switch(code)
	{
	  case SKIN_NOTIFY_STEP1_HWND:
	       {
		      itemAudioSetStep1Dlg.SetClient(code1);
		   }
	       break;
	  case SKIN_NOTIFY_STEP2_HWND:
	       {
		      itemAudioSetStep2Dlg.SetClient(code1);
		   }
		   break;
	  default:break;
	}
}
