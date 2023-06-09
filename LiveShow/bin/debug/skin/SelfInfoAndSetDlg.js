
var SKIN_ON_CLICK_HEAD = 1;
var SKIN_ON_CLICK_USERLEVEL = 2;
var SKIN_ON_CLICK_USERROLE = 3;
var SKIN_ON_CLICK_SYSSETTING = 4;
var SKIN_ON_CLICK_ROOMMANAGER = 5;
var SKIN_ON_CLICK_ON_OFF_LINE = 6;
var SKIN_ON_CLICK_ICON_MICON = 7;
var SKIN_ON_CLICK_ICON_MICOFF = 8;
var SKIN_ON_CLICK_ICON_SPEAKERON = 9;
var SKIN_ON_CLICK_ICON_SPEAKEROFF = 10;
var SKIN_ON_CLICK_BTN_AUDIOSET = 11;

var NOTIFY_SKIN_TO_ONSIZE = 20;
var SKIN_NOTIFY_MICSLIDER_DLG = 21;
var SKIN_NOTIFY_SPEAKERSLIDER_DLG = 22;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

imgMyHeadCtrlBack_N.AttachEvent("OnClick",OnClickHead);
imgMyHeadCtrlBack_H.AttachEvent("OnClick",OnClickHead);
imgUserLevel.AttachEvent("OnClick", OnClickUserLevel);
imgUserRole.AttachEvent("OnClick", OnClickIconUserRole);
btnSysSetting.AttachEvent("OnClick", OnClickSysSetting);
btnRoomManager.AttachEvent("OnClick", OnClickRoomManager);
btnStatus.AttachEvent("OnClick", OnClickBtnStatus);

btnAudioSet.AttachEvent("OnClick", OnClickBtnAudioSet);
imgMicOn.AttachEvent("OnClick",OnClickIconMicOn);
imgMicOff.AttachEvent("OnClick",OnClickIconMicOff);
imgSpeakerOn.AttachEvent("OnClick",OnClickIconSpeakerOn);
imgSpeakerOff.AttachEvent("OnClick",OnClickIconSpeakerOff);

function OnClickHead()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_HEAD, 0);
}
function OnClickUserLevel()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_USERLEVEL, 0);
}

function OnClickIconUserRole()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_USERROLE, 0);
}

function OnClickSysSetting()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_SYSSETTING, 0);
}

function OnClickRoomManager()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_ROOMMANAGER, 0);
}

function OnClickBtnStatus()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_ON_OFF_LINE, 0);
}

function OnClickBtnAudioSet()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_AUDIOSET,0);
}

function OnClickIconMicOn()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_ICON_MICON,0);
}

function OnClickIconMicOff()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_ICON_MICOFF,0);
}

function OnClickIconSpeakerOn()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_ICON_SPEAKERON,0);
}

function OnClickIconSpeakerOff()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_ICON_SPEAKEROFF,0);
}

function OnInit()
{
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{
	imgSelfInfoAndSetDlgBk.left = 0;
	imgSelfInfoAndSetDlgBk.top = 0;
	imgSelfInfoAndSetDlgBk.width = cx;
	imgSelfInfoAndSetDlgBk.height = cy;
	
	imgMyHead.left = 10;
	imgMyHead.top = 13;
	imgMyHead.width = 40;
	imgMyHead.height = 40;

	imgMyHeadCtrlBack_N.left = imgMyHead.left - 1;
	imgMyHeadCtrlBack_N.top = imgMyHead.top - 1;
	imgMyHeadCtrlBack_N.width = 42;
	imgMyHeadCtrlBack_N.height = 42;
	
	imgMyHeadCtrlBack_H.left = imgMyHeadCtrlBack_N.left;
	imgMyHeadCtrlBack_H.top = imgMyHeadCtrlBack_N.top;
	imgMyHeadCtrlBack_H.width = imgMyHeadCtrlBack_N.width;
	imgMyHeadCtrlBack_H.height = imgMyHeadCtrlBack_N.height;
	
	textUserName.height = 18;
	textUserName.left = imgMyHeadCtrlBack_N.left + imgMyHeadCtrlBack_N.width + 6;
	textUserName.top = 8;
	textUserName.width = cx - textUserName.left;
	
	btnStatus.left = imgMyHeadCtrlBack_N.left + imgMyHeadCtrlBack_N.width - 18;
	btnStatus.top = imgMyHeadCtrlBack_N.top + imgMyHeadCtrlBack_N.height - btnStatus.height;
	
	imgUserLevel.left = imgMyHeadCtrlBack_N.left + imgMyHeadCtrlBack_N.width + 6;
	imgUserLevel.top = textUserName.top + textUserName.height + 3;
	imgUserLevel.width = 18;
	imgUserLevel.height = 19;
	
	imgRichLevel.left = imgUserLevel.left + imgUserLevel.width + 6;
	imgRichLevel.top = imgUserLevel.top + 3;
	
	imgUserRole.left = imgRichLevel.left + imgRichLevel.width + 6;
	imgUserRole.top = imgUserLevel.top;
	imgUserRole.width = imgUserLevel.width;
	imgUserRole.height = imgUserLevel.height;
	
	btnSysSetting.left = imgUserRole.left + imgUserRole.width + 6;
	btnSysSetting.top = imgUserRole.top;
	
	btnRoomManager.left = btnSysSetting.left + btnSysSetting.width + 6;
	btnRoomManager.top = btnSysSetting.top;
	
	btnAudioSet.left = cx - 8 - imgMicOn.width;
	btnAudioSet.top = btnSysSetting.top;
	
	imgMicOn.left = btnAudioSet.left - 2 - btnAudioSet.width;
	imgMicOn.top = btnAudioSet.top;
	
	imgMicOff.left = imgMicOn.left;
	imgMicOff.top = imgMicOn.top;
	
	imgSpeakerOn.left = imgMicOn.left - 2 - imgSpeakerOn.width;
	imgSpeakerOn.top = imgMicOn.top;
	
	imgSpeakerOff.left = imgSpeakerOn.left;
	imgSpeakerOff.top = imgSpeakerOn.top;
	
	
	
	// itemMicSliderDlg.width = 38;
	// itemMicSliderDlg.height = 140;
	// itemMicSliderDlg.left = imgMicOn.left - 10;
	// itemMicSliderDlg.top = imgMicOn.top - itemMicSliderDlg.height;
	
	// itemSpeakerSliderDlg.width = itemMicSliderDlg.width;
	// itemSpeakerSliderDlg.height = itemMicSliderDlg.height;
	// itemSpeakerSliderDlg.left = imgSpeakerOn.left - 10;
	// itemSpeakerSliderDlg.top = itemMicSliderDlg.top;
}

function OnNotify(code, code1)
{
  switch(code)
  {
  case NOTIFY_SKIN_TO_ONSIZE:
	   {
			OnSize(Window.width, Window.height);
	   }
	   break;
   case SKIN_NOTIFY_MICSLIDER_DLG:
       {
			//itemMicSliderDlg.SetClient(code1);
	   }
	   break;
    case SKIN_NOTIFY_SPEAKERSLIDER_DLG:
	   {
			//itemSpeakerSliderDlg.SetClient(code1);
	   }
	   break;
  default:
    break;
  }
}
