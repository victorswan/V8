
var SKIN_ON_CLICK_BTN_CONFIRM_MODIFY = 1;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

//btnConfirmModify.AttachEvent("OnClick",OnClickBtnConfirmModify);

// function OnClickBtnConfirmModify()
// {
    // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CONFIRM_MODIFY,0);
// }

function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{   
    imgMicSettingDlgBk.visible = true;
	imgMicSettingDlgBk.left = 0;
	imgMicSettingDlgBk.top = 0;
	imgMicSettingDlgBk.width = cx;
	imgMicSettingDlgBk.height = cy;

	// MicSettingDlgTitleEffect.visible = false;
	// MicSettingDlgTitleEffect.left = 0; 
	// MicSettingDlgTitleEffect.top = 0;
	
	imgTitleIcon.visible = true;
	imgTitleIcon.left = 10;
	imgTitleIcon.top = 1;

	textTheTitle.visible = true;
	textTheTitle.left = imgTitleIcon.left + imgTitleIcon.width + 5;
	textTheTitle.top = 4;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	imgTitleLine.visible = true;
	imgTitleLine.left = textTheTitle.left + textTheTitle.width + 2;
	imgTitleLine.top = textTheTitle.top +(textTheTitle.height - imgTitleLine.height)/2;
	////////////////////////
	
	
	textFreeMic.visible = true;
	textFreeMic.left = textTheTitle.left + 105;
	textFreeMic.top = textTheTitle.top + textTheTitle.height + 100;
	textFreeMic.width = textFreeMic.textWidth;
	textFreeMic.height = textFreeMic.textHeight;
	
	radioFreeMicClose.visible = true;
	radioFreeMicClose.left = textFreeMic.left + textFreeMic.width + 5;
	radioFreeMicClose.top = textFreeMic.top;
	
	radioFreeMicOpen.visible = true;
	radioFreeMicOpen.left = radioFreeMicClose.left + radioFreeMicClose.width + 10;
	radioFreeMicOpen.top = radioFreeMicClose.top;
	
	textMicTime.visible = true;
	textMicTime.left = textFreeMic.left;
	textMicTime.top =  textFreeMic.top + textFreeMic.height + 20;
	textMicTime.width = textMicTime.textWidth;
	textMicTime.height = textMicTime.textHeight;
	
	itemComboMicTime.visible = true;
	itemComboMicTime.left = textMicTime.left + textMicTime.width + 5;
	itemComboMicTime.top = textMicTime.top - 2;
	itemComboMicTime.width = 72;
	itemComboMicTime.height = 20;
	
	textMicTimePrompt.visible = true;
	textMicTimePrompt.left = itemComboMicTime.left + itemComboMicTime.width + 3;
	textMicTimePrompt.top = textMicTime.top;
	textMicTimePrompt.width = textMicTimePrompt.textWidth;
	textMicTimePrompt.height = textMicTimePrompt.textHeight;
	
	itemCheckLimitMicTime.visible = true;
	itemCheckLimitMicTime.left = itemComboMicTime.left;
	itemCheckLimitMicTime.top = itemComboMicTime.top + itemComboMicTime.height + 20;
	
	itemCheckModifyMicTime.visible = true;
	itemCheckModifyMicTime.left = itemCheckLimitMicTime.left + itemCheckLimitMicTime.width + 8;
	itemCheckModifyMicTime.top = itemCheckLimitMicTime.top;
	
	// itemCheckClosePrivateMic.visible = true;
	// itemCheckClosePrivateMic.left = itemCheckLimitMicTime.left;
	// itemCheckClosePrivateMic.top = itemCheckLimitMicTime.top + itemCheckLimitMicTime.height + 20;
	
	textPrivateMicState.visible = true;
	textPrivateMicState.left = textFreeMic.left;
	textPrivateMicState.top = itemCheckModifyMicTime.top + itemCheckModifyMicTime.height + 20;
	textPrivateMicState.width = textPrivateMicState.textWidth;
	textPrivateMicState.height = textPrivateMicState.textHeight;
	
	textState.visible = true;
	textState.left = textPrivateMicState.left + textPrivateMicState.width + 10;
	textState.top = textPrivateMicState.top;
	textState.width = textState.textWidth;
	textState.height = textState.textHeight;
	
	textRoomPrivateMic.visible = true;
	textRoomPrivateMic.left = textPrivateMicState.left;
	textRoomPrivateMic.top = textPrivateMicState.top + textPrivateMicState.height + 10;
	textRoomPrivateMic.width = textRoomPrivateMic.textWidth;
	textRoomPrivateMic.height = textRoomPrivateMic.textHeight;
	
	radioPrivateMicClose.visible = true;
	radioPrivateMicClose.left = textState.left;
	radioPrivateMicClose.top = textRoomPrivateMic.top;
	
	radioPrivateMicOpen.visible = true;
	radioPrivateMicOpen.left = radioPrivateMicClose.left + radioPrivateMicClose.width + 20;
	radioPrivateMicOpen.top = radioPrivateMicClose.top;
	
	// btnConfirmModify.visible = true;
	// btnConfirmModify.left = textState.left + 70;
	// btnConfirmModify.top = textState.top + textState.height + 50;
	// btnConfirmModify.width = 77;
	// btnConfirmModify.height = 30;
	
	imgApplyEffect.left = 0;
	imgApplyEffect.top = 0;
	imgApplyEffect.width = cx;
	imgApplyEffect.height = cy;
	
}

function OnNotify(code, code1)
{
  switch(code)
  {
 
  default:
    break;
  }
}
