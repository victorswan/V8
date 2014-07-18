
var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_SEND = 2;
var SKIN_ON_CLICK_BTN_EFFECT1 = 3;
var SKIN_ON_CLICK_BTN_EFFECT2 = 4;
var SKIN_ON_CLICK_BTN_EFFECT3 = 5;
var SKIN_ON_CLICK_BTN_EFFECT4 = 6;
var SKIN_ON_CLICK_BTN_RANDOM = 7;
var SKIN_NOTIFY_EFFECT_CHANGE = 8;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnEffect1.AttachEvent("OnClick",OnClickBtnEffect1);
btnEffect2.AttachEvent("OnClick",OnClickBtnEffect2);
btnEffect3.AttachEvent("OnClick",OnClickBtnEffect3);
btnEffect4.AttachEvent("OnClick",OnClickBtnEffect4);
btnRandom.AttachEvent("OnClick",OnClickBtnRandom);

btnSysClose.AttachEvent("OnClick", OnClickbtnClose);

op_send.AttachEvent("OnClick", OnClickSend);
op_cancel.AttachEvent("OnClick", OnClickbtnClose);

function OnClickBtnEffect1()
{
   if(false == btnEffect1.checked)
   {
		btnEffect1.checked = true;
		btnEffect2.checked = false;
		btnEffect3.checked = false;
		btnEffect4.checked = false;
		btnRandom.checked = false;
		Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT1 ,1);
		
		imgFlyingTextCheck.visible = true;
		imgFlyingTextCheck.left = btnEffect1.left;
		imgFlyingTextCheck.top = btnEffect1.top;
		OnSize(Window.width, Window.height);
   }
   // else
   // {
		// btnEffect1.checked = false;
		// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT1 ,0);
		
		// imgFlyingTextCheck.visible = false;
		// OnSize(Window.width, Window.height);
   // }
}

function OnClickBtnEffect2()
{
  if(false == btnEffect2.checked)
  {
		btnEffect2.checked = true;
		btnEffect1.checked = false;
		btnEffect3.checked = false;
		btnEffect4.checked = false;
		btnRandom.checked = false;
		Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT2 ,1);
		
		imgFlyingTextCheck.visible = true;
		imgFlyingTextCheck.left = btnEffect2.left;
		imgFlyingTextCheck.top = btnEffect2.top;
		OnSize(Window.width, Window.height);
  }
  // else
  // {
		// btnEffect2.checked = false;
		// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT2 ,0);
		
		// imgFlyingTextCheck.visible = false;
		// OnSize(Window.width, Window.height);
  // }
}

function OnClickBtnEffect3()
{
  if(false == btnEffect3.checked)
  {
		btnEffect3.checked = true;
		btnEffect1.checked = false;
		btnEffect2.checked = false;
		btnEffect4.checked = false;
		btnRandom.checked = false;
		Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT3 ,1);
		
		imgFlyingTextCheck.visible = true;
		imgFlyingTextCheck.left = btnEffect3.left;
		imgFlyingTextCheck.top = btnEffect3.top;
		OnSize(Window.width, Window.height);
  }
  // else
  // {
		// btnEffect3.checked = false;
		// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT3 ,0);
		
		// imgFlyingTextCheck.visible = false;
		// OnSize(Window.width, Window.height);
  // }
}

function OnClickBtnEffect4()
{
  if(false == btnEffect4.checked)
  {
		btnEffect4.checked = true;
		btnEffect1.checked = false;
		btnEffect2.checked = false;
		btnEffect3.checked = false;
		btnRandom.checked = false;
		Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT4 ,1);
		
		imgFlyingTextCheck.visible = true;
		imgFlyingTextCheck.left = btnEffect4.left;
		imgFlyingTextCheck.top = btnEffect4.top;
		OnSize(Window.width, Window.height);
  }
  // else
  // {
		// btnEffect4.checked = false;
		// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT4 ,0);
		
		// imgFlyingTextCheck.visible = false;
		// OnSize(Window.width, Window.height);
  // }
}

function OnClickBtnRandom()
{
  if(false == btnRandom.checked)
  {
		btnEffect4.checked = false;
		btnEffect1.checked = false;
		btnEffect2.checked = false;
		btnEffect3.checked = false;
		btnRandom.checked = true;
		Window.PostSkinMessage(SKIN_ON_CLICK_BTN_RANDOM,1);
		
		imgFlyingTextCheck.visible = true;
		imgFlyingTextCheck.left = btnRandom.left;
		imgFlyingTextCheck.top = btnRandom.top;
		OnSize(Window.width, Window.height);
  }
  // else
  // {
		// btnRandom.checked = false;
		// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_EFFECT4 ,0);
		
		// imgFlyingTextCheck.visible = false;
		// OnSize(Window.width, Window.height);
  // }
}


function OnClickbtnClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function OnClickSend()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_SEND, 0);
}

function OnInit()
{
	textTitle.text = "飞屏";
    textTitle.visible = false;
    // textTitle.fontWeight = 500;
	// textTitle.fontSize = 11;
    // textTitle.normalColor = 0xffffff;
    // textTitle.colorTransform = true;
	
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	// textTitle.width = textTitle.textWidth;
	// textTitle.height = textTitle.textHeight;
	// textTitle.left = imgTitleIcon.left + imgTitleIcon.width + 10;
	// textTitle.top = 0 + (32 - textTitle.height)/2 ;
	
	imgFlyingTextDlgBk.left = 2;
	imgFlyingTextDlgBk.top = 2;
	imgFlyingTextDlgBk.width = cx - 4;
	imgFlyingTextDlgBk.height = cy - 4;
	
	imgFlyingTextDlgEffect.left = 2;
	imgFlyingTextDlgEffect.top = 2;
	
	// imgFlyingTextDlgTitle.left = 10;
	// imgFlyingTextDlgTitle.top = 8;
	textTheTitle.left = 10;
	textTheTitle.top = 8;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	textTip.visible = true;
	textTip.left = 13;
	textTip.top = 36;
	textTip.width = textTip.textWidth;
	textTip.height = textTip.textHeight;
	
	btnRandom.visible = true;
	btnRandom.left = 13;
	//btnRandom.top = textTip.top + textTip.height + 5;
	btnRandom.top = 56;
	btnRandom.width = 46;
	btnRandom.height = 34;

	btnEffect1.visible = true;
	btnEffect1.left = btnRandom.left + btnRandom.width + 18;
	btnEffect1.top = btnRandom.top;
	btnEffect1.width = 46;
	btnEffect1.height = 34;
	
	//imgFlyingTextCheck.visible = false;
	//imgFlyingTextCheck.left = btnEffect1.left;
	//imgFlyingTextCheck.top = btnEffect1.top;
	
	btnEffect2.visible = true;
	btnEffect2.left = btnEffect1.left + btnEffect1.width + 18;
	btnEffect2.top = btnRandom.top;
	btnEffect2.width = 46;
	btnEffect2.height = 34;
	
	btnEffect3.visible = true;
	btnEffect3.left = btnEffect2.left + btnEffect2.width + 18;
	btnEffect3.top = btnRandom.top;
	btnEffect3.width = 46;
	btnEffect3.height = 34;
	
	btnEffect4.visible = true;
	btnEffect4.left = btnEffect3.left + btnEffect3.width + 18;
	btnEffect4.top = btnRandom.top;
	btnEffect4.width = 46;
	btnEffect4.height = 34;
	
	imgInputRound.visible = true;
	imgInputRound.left = 10;
	imgInputRound.top = 97;
	imgInputRound.width = cx - 20;
	imgInputRound.height = 55;
	
	itemFlyingTextInput.visible = true;
	itemFlyingTextInput.left = imgInputRound.left + 1;
	itemFlyingTextInput.top = imgInputRound.top + 1;
	itemFlyingTextInput.width = imgInputRound.width - 2;
	itemFlyingTextInput.height = imgInputRound.height - 4;
	
	textPrompt.visible = true;
	textPrompt.left = itemFlyingTextInput.left;
	textPrompt.top = itemFlyingTextInput.top + itemFlyingTextInput.height + 5;
	textPrompt.width = itemFlyingTextInput.width;
	textPrompt.height = textPrompt.textHeight;
	
	op_cancel.visible = true;
	op_cancel.width = 79;
	op_cancel.height = 35;
	op_cancel.left = cx - 10 - op_cancel.width;
	op_cancel.top = cy - 36;
	
	op_send.visible = true;
	op_send.width = op_cancel.width;
	op_send.height = op_cancel.height;
	op_send.left = op_cancel.left - 10 - op_send.width;
	op_send.top = op_cancel.top;
	/////////////////////////////////////////////////
	
}

function OnNotify(code, code1)
{
	switch(code)
	{
		case SKIN_NOTIFY_EFFECT_CHANGE:
			{
				switch(code1)
				{
					case 0:
						{
							btnEffect1.checked = false;
							btnEffect2.checked = false;
							btnEffect3.checked = false;
							btnEffect4.checked = false;
							btnRandom.checked = true;
							
							imgFlyingTextCheck.visible = true;
							imgFlyingTextCheck.left = btnRandom.left;
							imgFlyingTextCheck.top = btnRandom.top;
							OnSize(Window.width, Window.height);
						}
						break;
					case 1:
						{
							btnEffect1.checked = true;
							btnEffect2.checked = false;
							btnEffect3.checked = false;
							btnEffect4.checked = false;
							btnRandom.checked = false;
							
							imgFlyingTextCheck.visible = true;
							imgFlyingTextCheck.left = btnEffect1.left;
							imgFlyingTextCheck.top = btnEffect1.top;
							OnSize(Window.width, Window.height);
						}
						break;
					case 2:
						{
							btnEffect1.checked = false;
							btnEffect2.checked = true;
							btnEffect3.checked = false;
							btnEffect4.checked = false;
							btnRandom.checked = false;
							
							imgFlyingTextCheck.visible = true;
							imgFlyingTextCheck.left = btnEffect2.left;
							imgFlyingTextCheck.top = btnEffect2.top;
							OnSize(Window.width, Window.height);
						}
						break;
					case 3:
						{
							btnEffect1.checked = false;
							btnEffect2.checked = false;
							btnEffect3.checked = true;
							btnEffect4.checked = false;
							btnRandom.checked = false;
							
							imgFlyingTextCheck.visible = true;
							imgFlyingTextCheck.left = btnEffect3.left;
							imgFlyingTextCheck.top = btnEffect3.top;
							OnSize(Window.width, Window.height);
						}
						break;
					case 4:
						{
							btnEffect1.checked = false;
							btnEffect2.checked = false;
							btnEffect3.checked = false;
							btnEffect4.checked = true;
							btnRandom.checked = false;
							
							imgFlyingTextCheck.visible = true;
							imgFlyingTextCheck.left = btnEffect4.left;
							imgFlyingTextCheck.top = btnEffect4.top;
							OnSize(Window.width, Window.height);
						}
						break;
					default:
						break;
				}
			}
			break;
		default:
			break;
	}
}
