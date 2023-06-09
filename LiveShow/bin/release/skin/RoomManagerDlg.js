
var SKIN_ON_CLICK_CLOSE = 1;
var NOTIFY_SKIN_ANNOUNCEMENT_DLG = 2;
var NOTIFY_SKIN_ROOMSETTING_DLG = 3;
var SKIN_ON_CLICK_TAB_TEMP_ANNOUNCE = 4;
var SKIN_ON_CLICK_TAB_ROOMSETTING = 5;
var SKIN_ON_CLICK_TAB_MICSETTING = 6;
var SKIN_ON_CLICK_TAB_USERMGR = 7;
var NOTIFY_SKIN_MICSETTING_DLG = 8;
var NOTIFY_SKIN_USERMGR_DLG = 9;
var SKIN_ON_CLICK_BTN_GET_CONTRIBUTE = 10;
var SKIN_ON_CLICK_TAB_ROOM_ANNOUNCE = 11;
var  NOTIFY_SKIN_TEMP_ANNOUNCEMENT_DLG = 12;
var  NOTIFY_SKIN_ROOM_ANNOUNCEMENT_DLG = 13;
var SKIN_ON_CLICK_BTN_ROOMER_SYS = 14;
var SKIN_ON_CLICK_BTN_CONFIRM = 15;
var SKIN_ON_CLICK_BTN_APPLY = 16;

Window.AttachEvent("OnInit", OnInit);
//Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", btnCloseOnClick);


btnGetContribution.AttachEvent("OnClick",OnClickBtnGetContribute);
btnRoomerSys.AttachEvent("OnClick", OnClickBtnRoomerSys);

btnBottomCancel.AttachEvent("OnClick",btnCloseOnClick);
btnBottomConfirm.AttachEvent("OnClick",OnClickBtnConfirm);
btnBottomApply.AttachEvent("OnClick", OnClickBtnApply);

iconTempAnnounce.AttachEvent("OnClick", OnClickTempAnnounce);
textItemTempAnnounce.AttachEvent("OnClick", OnClickTempAnnounce);
iconRoomAnnounce.AttachEvent("OnClick", OnClickRoomAnnounce);
textItemRoomAnnounce.AttachEvent("OnClick", OnClickRoomAnnounce);
iconRoomSetting.AttachEvent("OnClick", OnClickRoomSetting);
textItemRoomSetting.AttachEvent("OnClick", OnClickRoomSetting);
iconMicSetting.AttachEvent("OnClick", OnClickMicSetting);
textItemMicSetting.AttachEvent("OnClick", OnClickMicSetting);
iconWelcomeSetting.AttachEvent("OnClick", OnClickWelcomeSetting);
textItemWelcomeSetting.AttachEvent("OnClick", OnClickWelcomeSetting);

function OnClickBtnRoomerSys()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_ROOMER_SYS, 0);
}

function OnClickBtnConfirm()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CONFIRM, 0);
}

function OnClickBtnApply()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_APPLY, 0);
}

function OnClickTempAnnounce() 
{
	 Window.PostSkinMessage(SKIN_ON_CLICK_TAB_TEMP_ANNOUNCE ,0);
}
function OnClickRoomAnnounce()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_ROOM_ANNOUNCE ,0);
}
function OnClickRoomSetting()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_ROOMSETTING ,0);
}
function OnClickMicSetting()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_MICSETTING ,0);
}
function OnClickWelcomeSetting()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_USERMGR ,0);
}


function OnClickBtnGetContribute()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_GET_CONTRIBUTE,0);
}

function btnCloseOnClick()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}


function OnInit()
{
    textTitle.visible = false;
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	////////////////////////////
	imgRoomMgrTopBk.left = 2;
	imgRoomMgrTopBk.top = 2;
	imgRoomMgrTopBk.width = cx - 4;
	
	imgRoomMgrLeftBk.left = imgRoomMgrTopBk.left;
	imgRoomMgrLeftBk.top = imgRoomMgrTopBk.top + imgRoomMgrTopBk.height;
	
	imgRoomMgrBottomBK.left = imgRoomMgrLeftBk.left + imgRoomMgrLeftBk.width;
	imgRoomMgrBottomBK.top = cy - 2 - imgRoomMgrBottomBK.height;
	
	textTheTitle.left = 35;
	textTheTitle.top = 16;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	/////////////////////////////////
	
	//公告信息
	imgItemAnnounceInfoBk.left = imgRoomMgrLeftBk.left;
	imgItemAnnounceInfoBk.top = imgRoomMgrLeftBk.top + 10;
	imgItemAnnounceInfoBk.width = 145;
	imgItemAnnounceInfoBk.height = 39;
	textAnnounceMessage.width = textAnnounceMessage.textWidth;
	textAnnounceMessage.height = textAnnounceMessage.textHeight;
	textAnnounceMessage.left = imgItemAnnounceInfoBk.left + (imgItemAnnounceInfoBk.width - textAnnounceMessage.width)/2;
	textAnnounceMessage.top = imgItemAnnounceInfoBk.top + (imgItemAnnounceInfoBk.height - textAnnounceMessage.height)/2 - 3;
	
	imgTempAnnounceBk.left = imgItemAnnounceInfoBk.left;
	imgTempAnnounceBk.top = imgItemAnnounceInfoBk.top + imgItemAnnounceInfoBk.height + 2;
	imgTempAnnounceBk.width = imgItemAnnounceInfoBk.width;
	imgTempAnnounceBk.height = 20;
	iconTempAnnounce.left = textAnnounceMessage.left - 4;
	iconTempAnnounce.top = imgTempAnnounceBk.top + 2;
	textItemTempAnnounce.width = textItemTempAnnounce.textWidth;
	textItemTempAnnounce.height = textItemTempAnnounce.textHeight;
	textItemTempAnnounce.left = iconTempAnnounce.left + iconTempAnnounce.width + 1;
	textItemTempAnnounce.top = imgTempAnnounceBk.top + (imgTempAnnounceBk.height - textItemTempAnnounce.height)/2;
	
	imgRoomAnnounceBk.left = imgTempAnnounceBk.left;
	imgRoomAnnounceBk.top = imgTempAnnounceBk.top + imgTempAnnounceBk.height + 2;
	imgRoomAnnounceBk.width = imgTempAnnounceBk.width;
	imgRoomAnnounceBk.height = imgTempAnnounceBk.height;
	iconRoomAnnounce.left = iconTempAnnounce.left;
	iconRoomAnnounce.top = imgRoomAnnounceBk.top + 2;
	textItemRoomAnnounce.width = textItemRoomAnnounce.textWidth;
	textItemRoomAnnounce.height = textItemRoomAnnounce.textHeight;
	textItemRoomAnnounce.left = iconRoomAnnounce.left + iconRoomAnnounce.width;
	textItemRoomAnnounce.top = imgRoomAnnounceBk.top + (imgRoomAnnounceBk.height - textItemRoomAnnounce.height)/2;
	
	//基本信息
	imgItemBasicInfoBk.left = imgItemAnnounceInfoBk.left;
	imgItemBasicInfoBk.top = imgRoomAnnounceBk.top + imgRoomAnnounceBk.height + 2 ;
	imgItemBasicInfoBk.width = imgItemAnnounceInfoBk.width;
	imgItemBasicInfoBk.height = imgItemAnnounceInfoBk.height;
	textBasicInfo.width = textBasicInfo.textWidth;
	textBasicInfo.height = textBasicInfo.textHeight;
	textBasicInfo.left = imgItemBasicInfoBk.left + (imgItemBasicInfoBk.width - textBasicInfo.width)/2;
	textBasicInfo.top = imgItemBasicInfoBk.top + (imgItemBasicInfoBk.height - textBasicInfo.height)/2 - 3;
	
	imgRoomSettingBk.left = imgRoomAnnounceBk.left;
	imgRoomSettingBk.top = imgItemBasicInfoBk.top + imgItemBasicInfoBk.height + 2;
	imgRoomSettingBk.width = imgRoomAnnounceBk.width;
	imgRoomSettingBk.height = imgRoomAnnounceBk.height;
	iconRoomSetting.left = iconRoomAnnounce.left;
	iconRoomSetting.top = imgRoomSettingBk.top + 2;
	textItemRoomSetting.width = textItemRoomSetting.textWidth;
	textItemRoomSetting.height = textItemRoomSetting.textHeight;
	textItemRoomSetting.left = iconRoomSetting.left + iconRoomSetting.width;
	textItemRoomSetting.top = imgRoomSettingBk.top + (imgRoomSettingBk.height - textItemRoomSetting.height)/2;
	
	imgMicSettingBk.left = imgRoomSettingBk.left;
	imgMicSettingBk.top = imgRoomSettingBk.top + imgRoomSettingBk.height + 2;
	imgMicSettingBk.width = imgRoomSettingBk.width;
	imgMicSettingBk.height = imgRoomSettingBk.height;
	iconMicSetting.left = iconRoomSetting.left;
	iconMicSetting.top = imgMicSettingBk.top + 2;
	textItemMicSetting.width = textItemMicSetting.textWidth;
	textItemMicSetting.height = textItemMicSetting.textHeight;
	textItemMicSetting.left = iconMicSetting.left + iconMicSetting.width;
	textItemMicSetting.top = imgMicSettingBk.top + (imgMicSettingBk.height - textItemMicSetting.height)/2;
	
	//迎宾信息
	imgItemWelcomeInfoBk.left = imgItemBasicInfoBk.left;
	imgItemWelcomeInfoBk.top = imgMicSettingBk.top + imgMicSettingBk.height + 2;
	imgItemWelcomeInfoBk.width = imgItemBasicInfoBk.width;
	imgItemWelcomeInfoBk.height = imgItemBasicInfoBk.height;
	textWelcomeInfo.width = textWelcomeInfo.textWidth;
	textWelcomeInfo.height = textWelcomeInfo.textHeight;
	textWelcomeInfo.left = imgItemWelcomeInfoBk.left + (imgItemWelcomeInfoBk.width - textWelcomeInfo.width)/2;
	textWelcomeInfo.top = imgItemWelcomeInfoBk.top + (imgItemWelcomeInfoBk.height - textWelcomeInfo.height)/2 - 3;
	
	imgWelcomeSettingBk.left = imgMicSettingBk.left;
	imgWelcomeSettingBk.top = imgItemWelcomeInfoBk.top + imgItemWelcomeInfoBk.height + 2;
	imgWelcomeSettingBk.width = imgMicSettingBk.width;
	imgWelcomeSettingBk.height = imgMicSettingBk.height;
	iconWelcomeSetting.left = iconMicSetting.left;
	iconWelcomeSetting.top = imgWelcomeSettingBk.top + 2;
	textItemWelcomeSetting.width = textItemWelcomeSetting.textWidth;
	textItemWelcomeSetting.height = textItemWelcomeSetting.textHeight;
	textItemWelcomeSetting.left = iconWelcomeSetting.left + iconWelcomeSetting.width;
	textItemWelcomeSetting.top = imgWelcomeSettingBk.top + (imgWelcomeSettingBk.height - textItemWelcomeSetting.height)/2;
	
	
	///////////////////////////////////////
	//右边子窗口
	
	itemTempAnnouncementDlg.visible = true;
	itemTempAnnouncementDlg.left = imgRoomMgrLeftBk.left + imgRoomMgrLeftBk.width;
	itemTempAnnouncementDlg.top = imgRoomMgrTopBk.top + imgRoomMgrTopBk.height;
	itemTempAnnouncementDlg.width = cx - itemTempAnnouncementDlg.left;
	itemTempAnnouncementDlg.height = imgRoomMgrBottomBK.top - itemTempAnnouncementDlg.top;//底部36，顶部40
	
	itemRoomAnnouncementDlg.visible = false;
	itemRoomAnnouncementDlg.left = itemTempAnnouncementDlg.left;
	itemRoomAnnouncementDlg.top = itemTempAnnouncementDlg.top;
	itemRoomAnnouncementDlg.width = itemTempAnnouncementDlg.width;
	itemRoomAnnouncementDlg.height = itemTempAnnouncementDlg.height;
	
	itemRoomSettingDlg.visible = false;
	itemRoomSettingDlg.left = itemRoomAnnouncementDlg.left;
	itemRoomSettingDlg.top = itemRoomAnnouncementDlg.top;
	itemRoomSettingDlg.width = itemRoomAnnouncementDlg.width;
	itemRoomSettingDlg.height = itemRoomAnnouncementDlg.height;
	
	itemMicSettingDlg.visible = false;
	itemMicSettingDlg.left = itemRoomSettingDlg.left;
	itemMicSettingDlg.top = itemRoomSettingDlg.top;
	itemMicSettingDlg.width = itemRoomSettingDlg.width;
	itemMicSettingDlg.height = itemRoomSettingDlg.height;
	
	itemUserMgrDlg.visible = false;
	itemUserMgrDlg.left = itemMicSettingDlg.left;
	itemUserMgrDlg.top = itemMicSettingDlg.top;
	itemUserMgrDlg.width = itemMicSettingDlg.width;
	itemUserMgrDlg.height = itemMicSettingDlg.height;

	///////////////////////////////////////////
	//底部按钮
	btnBottomApply.width = 111;
	btnBottomApply.height = 45;
	btnBottomApply.left = imgRoomMgrBottomBK.left + imgRoomMgrBottomBK.width - 8 - btnBottomApply.width;
	btnBottomApply.top = imgRoomMgrBottomBK.top + imgRoomMgrBottomBK.height - 8 - btnBottomApply.height;
	
	btnBottomCancel.width = btnBottomApply.width;
	btnBottomCancel.height = btnBottomApply.height;
	btnBottomCancel.left = btnBottomApply.left - 2 - btnBottomCancel.width;
	btnBottomCancel.top = btnBottomApply.top;
	
	btnBottomConfirm.width = btnBottomCancel.width;
	btnBottomConfirm.height = btnBottomCancel.height;
	btnBottomConfirm.left = btnBottomCancel.left - 2 - btnBottomConfirm.width;
	btnBottomConfirm.top = btnBottomCancel.top;
	
	btnRoomerSys.width = 75;
	btnRoomerSys.height = 23;
	btnRoomerSys.left = imgRoomMgrLeftBk.left + imgRoomMgrLeftBk.width + 8;
	btnRoomerSys.top = imgRoomMgrBottomBK.top + imgRoomMgrBottomBK.height - 15 - btnRoomerSys.height;
	
	btnGetContribution.width = btnRoomerSys.width;
	btnGetContribution.height = btnRoomerSys.height;
	btnGetContribution.left = btnRoomerSys.left + btnRoomerSys.width + 10;
	btnGetContribution.top = btnRoomerSys.top;
	
}

function OnNotify(code, code1)
{
	switch(code)
	{ 
	  case NOTIFY_SKIN_TEMP_ANNOUNCEMENT_DLG:
	       {
		     itemTempAnnouncementDlg.SetClient(code1);
		   }
		   break;
	  case NOTIFY_SKIN_ROOM_ANNOUNCEMENT_DLG:
	       {
		     itemRoomAnnouncementDlg.SetClient(code1);
		   }
		   break;
	  case NOTIFY_SKIN_ROOMSETTING_DLG:
	      {
		     itemRoomSettingDlg.SetClient(code1);
		  }
		  break;
	  case NOTIFY_SKIN_MICSETTING_DLG:
	      {
		     itemMicSettingDlg.SetClient(code1);
		  }
		  break;
	  case NOTIFY_SKIN_USERMGR_DLG:
	      {
		     itemUserMgrDlg.SetClient(code1);
		  }
		  break;
		default:
			break;
	}
}
