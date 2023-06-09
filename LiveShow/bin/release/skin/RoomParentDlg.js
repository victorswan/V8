
var SKIN_ON_CLICK_SYS_CLOSE = 1;
var SKIN_ON_CLICK_SYS_MINIMIZE = 2;
var SKIN_ON_CLICK_SYS_MAXIMIZE = 3;
var SKIN_ON_CLICK_BTN_COLLECT_ROOM = 4;

var NOTIFY_SKIN_ROOM_LEFT_DLG = 5;
var NOTIFY_SKIN_ROOM_MID_DLG = 6;
var NOTIFY_SKIN_ROOM_RIGHT_DLG = 7;

var SKIN_ON_CLICK_BTN_STATUS = 8;
var SKIN_ON_CLICK_BTN_AUDIOSET = 9;

var SKIN_ON_CLICK_ICON_MICON = 10;
var SKIN_ON_CLICK_ICON_MICOFF = 11;
var SKIN_ON_CLICK_ICON_SPEAKERON = 12;
var SKIN_ON_CLICK_ICON_SPEAKEROFF = 13;

var SKIN_ON_CLICK_ICON_USERLEVEL = 14;
var SKIN_ON_CLICK_ICON_USERHEAD	= 15;
var SKIN_ON_CLICK_ICON_USERROLE	= 16;

var SKIN_ON_CLICK_SYS_FEEDBACK = 17;
var NOTIFY_SKIN_ROOM_BOTTOM_POS = 18;

var NOTIFY_SKIN_ROOM_BOTTOMLEFT_DLG = 19;

var NOTIFY_SKIN_ROOM_PUBLIC_MIC1_DLG = 20;
var NOTIFY_SKIN_ROOM_PUBLIC_MIC2_DLG = 21;
var NOTIFY_SKIN_ROOM_PUBLIC_MIC3_DLG = 22;

var SKIN_ON_CLICK_PAIMIC = 23;
var NOTIFY_MOVE_PAODAO = 24;
var SKIN_ON_CLICK_BTN_ICON_INTRO = 25;
var SKIN_ON_CLICK_BTN_ROOM_ACTOR_UP = 26;
var SKIN_ON_CLICK_BTN_ROOM_ACTOR_DOWN = 27;
var SKIN_ON_CLICK_BTN_ROOM_ACTOR_TITLE_CLOSE = 28;
var SKIN_ON_CLICK_BIN_ROOM_ACTOR_TOPTITLE_DOWN = 29;
var SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD1 = 30;
var SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD2 = 31;
var SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD3 = 32;
var SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD4 = 33;
var SKIN_ON_CLICK_BTN_SPEAKER = 34;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);
btnSysMinimize.AttachEvent("OnClick", OnClickbtnSysMinimize);
btnSysMaximize.AttachEvent("OnClick", OnClickbtnSysMaximize);
btnIconIntro.AttachEvent("OnClick", OnClickBtnIconIntro);

btnCollectRoom.AttachEvent("OnClick",OnClickBtnCollectRoom);
btnUnCollectRoom.AttachEvent("OnClick", OnClickBtnCollectRoom);

btnPaiMic.AttachEvent("OnClick",OnClickBtnPaiMic);
btnFangMic.AttachEvent("OnClick",OnClickBtnPaiMic);
btnActorHeadUp.AttachEvent("OnClick",OnClickBtnRoomActorUp);
btnActorHeadDown.AttachEvent("OnClick",OnClickBtnRoomActorDown);
btnActorHeadTitleClose.AttachEvent("OnClick",OnClickBtnRoomActorTitleClose);
btnActorHeadTopTitleDown.AttachEvent("OnClick",OnClickBtnRoomActorTopTitleDown);

imgActorHead1.AttachEvent("OnClick",OnClickHead1);
imgActorHead2.AttachEvent("OnClick",OnClickHead2);
imgActorHead3.AttachEvent("OnClick",OnClickHead3);
imgActorHead4.AttachEvent("OnClick",OnClickHead4);

btnSpeaker.AttachEvent("OnClick", OnClickBtnSpeaker);

function OnClickbtnSysClose()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_SYS_CLOSE, 0);
}

function OnClickbtnSysMinimize()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_SYS_MINIMIZE, 0);
}

function OnClickbtnSysMaximize()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_SYS_MAXIMIZE, 0);
}

function OnClickBtnIconIntro()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_ICON_INTRO , 0);
}

function OnClickBtnCollectRoom()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_COLLECT_ROOM,0);
}

function OnClickBtnRoomActorUp()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_ROOM_ACTOR_UP,0);
}

function OnClickBtnRoomActorDown()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_ROOM_ACTOR_DOWN,0);
}

function OnClickBtnRoomActorTitleClose()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_ROOM_ACTOR_TITLE_CLOSE,0);
}
function OnClickBtnRoomActorTopTitleDown()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BIN_ROOM_ACTOR_TOPTITLE_DOWN,0);
}
function OnClickHead1()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD1,0);
}
function OnClickHead2()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD2,0);
}
function OnClickHead3()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD3,0);
}
function OnClickHead4()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BIN_ROOM_ACTOR_HEAD4,0);
}

function OnClickBtnPaiMic()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_PAIMIC,0);
}

function OnClickBtnSpeaker()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SPEAKER,0);
}


///////////////////////////////////////

function OnInit()
{
	textTitle.visible = false;
	imgTitleIcon.visible = false;
	btnSysFeedback.visible = false;
	
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    Window.BeginPaint();
    textTitle.visible = false;
	imgTitleIcon.visible = false;
	
	imgRoomDlgBk.visible = true;
	imgRoomDlgBk.left = 1;
	imgRoomDlgBk.top = 1;
	imgRoomDlgBk.width = cx - 2;
	imgRoomDlgBk.height = 600;
	
	imgRoomLogo.visible = true;
	imgRoomLogo.left = 1;
	imgRoomLogo.top = 1;
	
	imgRoomBottomLeftBk.left = 1;
	imgRoomBottomLeftBk.height = 57;
	imgRoomBottomLeftBk.width = 3;
	imgRoomBottomLeftBk.top = cy - 2 - imgRoomBottomLeftBk.height;
	
	imgRoomBottomRightBk.width = 3;
	imgRoomBottomRightBk.height = 57;
	imgRoomBottomRightBk.left = cx - 1 - imgRoomBottomRightBk.width;
	imgRoomBottomRightBk.top = imgRoomBottomLeftBk.top;
	
	btnSpeaker.width = 61;
	btnSpeaker.height = 66;
	btnSpeaker.left = cx - 1 - btnSpeaker.width;
	btnSpeaker.top = 1;

	btnSysClose.left = btnSpeaker.left - 2 - btnSysClose.width;
	btnSysClose.top = 3;
	
	btnSysMaximize.left = btnSysClose.left - 2 - btnSysMaximize.width;
	btnSysMaximize.top = btnSysClose.top;
	
	btnSysMinimize.left = btnSysMaximize.left - 2 - btnSysMinimize.width;
	btnSysMinimize.top = btnSysMaximize.top;

	btnIconIntro.visilbe = true;
	btnIconIntro.width = btnSysMinimize.width;
	btnIconIntro.height = btnSysMinimize.height;
	btnIconIntro.left = btnSysMinimize.left - btnIconIntro.width;
	btnIconIntro.top = btnSysMinimize.top;
	
    /////////////////////////////
	itemHtmlPaoDao.visible = false;
	itemHtmlPaoDao.width = btnIconIntro.left - 100 - itemHtmlPaoDao.left;
	itemHtmlPaoDao.height = 60;
	itemHtmlPaoDao.left =  imgRoomDlgBk.left + (imgRoomDlgBk.width - itemHtmlPaoDao.width)/2;
	itemHtmlPaoDao.top = 0;
	Window.PostSkinMessage(NOTIFY_MOVE_PAODAO, 0);
	
	imgPaoDaoLeft.left = itemHtmlPaoDao.left - 19 + 10;
	imgPaoDaoLeft.top = 0;
	imgPaoDaoLeft.width = 19;
	imgPaoDaoLeft.height = 65;
	
	imgPaoDaoRight.left = itemHtmlPaoDao.left + itemHtmlPaoDao.width - 10;
	imgPaoDaoRight.top = 0;
	imgPaoDaoRight.width = 19;
	imgPaoDaoRight.height = 65;
	
	imgPaoDaoDown.left = itemHtmlPaoDao.left + 10;
	imgPaoDaoDown.top = itemHtmlPaoDao.top + itemHtmlPaoDao.height;
	imgPaoDaoDown.width = itemHtmlPaoDao.width - 20;
	imgPaoDaoDown.height = 5;
	
	textRoomInfo.visible = true;
	textRoomInfo.height = textRoomInfo.textHeight;
	textRoomInfo.width = 110;
	textRoomInfo.height = 18;
	textRoomInfo.left = imgRoomLogo.left + 4;
	textRoomInfo.top = imgRoomLogo.top + imgRoomLogo.height - 18 - textRoomInfo.height;
	
	imgRoomAnnounce.left = textRoomInfo.left + 60;
	imgRoomAnnounce.top = textRoomInfo.top + textRoomInfo.height + 10;
	imgRoomAnnounce.width = 234;
	imgRoomAnnounce.height = 50;
	
	textRoomAnnounce.left = imgRoomAnnounce.left + 1;
	textRoomAnnounce.top = imgRoomAnnounce.top + 20;
	textRoomAnnounce.width = imgRoomAnnounce.width - 2;
	textRoomAnnounce.height = 18;
	
	// btnCollectRoom.width = 27;
	// btnCollectRoom.height = 27;
	// btnCollectRoom.top = 3;
	// btnCollectRoom.left = imgRoomLogo.left + imgRoomLogo.width + 15;
	
	// btnUnCollectRoom.left = btnCollectRoom.left;
	// btnUnCollectRoom.top = btnCollectRoom.top;
	// btnUnCollectRoom.width = btnCollectRoom.width;
	// btnUnCollectRoom.height = btnCollectRoom.height;
	
	btnCollectRoom.width = 27;
	btnCollectRoom.height = 27;
	btnCollectRoom.top = 3;
	btnCollectRoom.left = btnIconIntro.left - btnCollectRoom.width;
	
	btnUnCollectRoom.left = btnCollectRoom.left;
	btnUnCollectRoom.top = btnCollectRoom.top;
	btnUnCollectRoom.width = btnCollectRoom.width;
	btnUnCollectRoom.height = btnCollectRoom.height;
	
	imgNetSignal.visible = false;
	imgNetSignal.width = 24;
	imgNetSignal.height = 13;
	imgNetSignal.left = btnIconIntro.left - imgNetSignal.width - 5;
	imgNetSignal.top = btnIconIntro.top + btnIconIntro.height - imgNetSignal.height - 8;
	
	//公麦窗口
	imgPublicMic1Bk.left = imgRoomDlgBk.left + (imgRoomDlgBk.width - imgPublicMic1Bk.width)/2;
	imgPublicMic1Bk.top = imgRoomDlgBk.top + 70;
	
	itemPublicMic1.width = 360;
	itemPublicMic1.height = 294;
	itemPublicMic1.left = imgPublicMic1Bk.left + (imgPublicMic1Bk.width - itemPublicMic1.width)/2;
	itemPublicMic1.top = imgPublicMic1Bk.top + 14;
	
	imgPublicMic2Bk.left = imgPublicMic1Bk.left - 25 - imgPublicMic2Bk.width;
	imgPublicMic2Bk.top = imgPublicMic1Bk.top + imgPublicMic1Bk.height - imgPublicMic2Bk.height - 22;
	//imgPublicMic1Bottom.width = 160;
	//imgPublicMic1Bottom.left = imgPublicMic1Bk.left + (imgPublicMic1Bk.width - imgPublicMic1Bottom.width)/2;
	imgPublicMic2Bottom.left = imgPublicMic2Bk.left - 11;
	imgPublicMic2Bottom.top = imgPublicMic2Bk.top + imgPublicMic2Bk.height + 5;
	itemPublicMic2.width = 190;
	itemPublicMic2.height = 168;
	itemPublicMic2.left = imgPublicMic2Bk.left + (imgPublicMic2Bk.width - itemPublicMic2.width)/2;
	itemPublicMic2.top = imgPublicMic2Bk.top + 10;
	
	imgPublicMic3Bk.left = imgPublicMic1Bk.left + imgPublicMic1Bk.width + 25;
	imgPublicMic3Bk.top = imgPublicMic2Bk.top;
	//imgPublicMic3Bottom.width = 160;
	//imgPublicMic3Bottom.left = imgPublicMic3Bk.left + (imgPublicMic3Bk.width - imgPublicMic3Bottom.width)/2;
	imgPublicMic3Bottom.left = imgPublicMic3Bk.left - 11;
	imgPublicMic3Bottom.top = imgPublicMic3Bk.top + imgPublicMic3Bk.height + 5;
	itemPublicMic3.width = itemPublicMic2.width;
	itemPublicMic3.height = itemPublicMic2.height;
	itemPublicMic3.left = imgPublicMic3Bk.left + (imgPublicMic3Bk.width - itemPublicMic3.width)/2;
	itemPublicMic3.top = imgPublicMic3Bk.top + 10;
	
	btnPaiMic.visible = true;
	btnPaiMic.width = 122;
	btnPaiMic.height = 68;
	btnPaiMic.left = 10;
	btnPaiMic.top = imgPublicMic2Bk.top + imgPublicMic2Bk.height - 10;
	
	btnFangMic.left = btnPaiMic.left;
	btnFangMic.top = btnPaiMic.top;
	// btnFangMic.width = btnPaiMic.width;
	// btnFangMic.height = btnPaiMic.height;
	//////////////
	//喇叭
	imgRoomSpeakerBK.width = 260;
	imgRoomSpeakerBK.height = 156;
	imgRoomSpeakerBK.left = cx - imgRoomSpeakerBK.width - 10;
	imgRoomSpeakerBK.top = 40;
	
	itemHtmlSpeaker.width = 238;
	itemHtmlSpeaker.height = 126;
	itemHtmlSpeaker.left = imgRoomSpeakerBK.left + 12;
	itemHtmlSpeaker.top = imgRoomSpeakerBK.top + 19;
	
	imgRoomRightRound.top = 420;
	imgRoomRightRound.width = 255 + 8;
	imgRoomRightRound.height = cy - 2 - imgRoomRightRound.top;
	imgRoomRightRound.left = imgRoomDlgBk.left + imgRoomDlgBk.width - imgRoomRightRound.width;
	
	itemRoomRightDlg.left = imgRoomRightRound.left + 3;
	itemRoomRightDlg.top = imgRoomRightRound.top + 3;
	itemRoomRightDlg.width = imgRoomRightRound.width - 6;
	itemRoomRightDlg.height = imgRoomRightRound.height - 3;
	
	imgRoomMall.left =  imgRoomRightRound.left + (imgRoomRightRound.width - imgRoomMall.width)/2;
	imgRoomMall.top = imgRoomRightRound.top - imgRoomMall.height + 17;
	
	imgRoomBottomLeftRound.left = 1;
	imgRoomBottomLeftRound.top = 420;
	imgRoomBottomLeftRound.width = 261;
	imgRoomBottomLeftRound.height = cy - 2 - imgRoomBottomLeftRound.top;
	
	itemRoomBottomLeftDlg.visible = true;
	itemRoomBottomLeftDlg.left = imgRoomBottomLeftRound.left + 3;
	itemRoomBottomLeftDlg.top = imgRoomBottomLeftRound.top + 4;
	itemRoomBottomLeftDlg.width = imgRoomBottomLeftRound.width - 6;
	itemRoomBottomLeftDlg.height = imgRoomBottomLeftRound.height - 4;
	
	imgRoomMidRound.left = imgRoomBottomLeftRound.left + imgRoomBottomLeftRound.width - 6;
	imgRoomMidRound.top = imgRoomBottomLeftRound.top - 25;
	imgRoomMidRound.width = imgRoomRightRound.left + 6 - imgRoomMidRound.left;
	imgRoomMidRound.height = cy - 2 - imgRoomMidRound.top;
	
	itemRoomMidDlg.visible = true;
	itemRoomMidDlg.left = imgRoomMidRound.left + 20;
	itemRoomMidDlg.top = imgRoomMidRound.top + 20;
	itemRoomMidDlg.width = imgRoomMidRound.width - 40;
	itemRoomMidDlg.height = imgRoomMidRound.height - 20;
	
	imgRoomBottomMidLeftBk.left = itemRoomMidDlg.left - imgRoomBottomMidLeftBk.width;
	imgRoomBottomMidLeftBk.top = cy - 2 - imgRoomBottomMidLeftBk.height;
	
	imgRoomBottomMidRightBk.left = itemRoomMidDlg.left + itemRoomMidDlg.width;
	imgRoomBottomMidRightBk.top = imgRoomBottomMidLeftBk.top;
	
	imgRoomBottomSubBorder2.left = imgRoomBottomLeftRound.left + imgRoomBottomLeftRound.width - imgRoomBottomSubBorder2.width;
	imgRoomBottomSubBorder2.top = cy - 2 - imgRoomBottomSubBorder2.height;
	
	imgRoomBottomSubBorder3.left = imgRoomBottomSubBorder2.left + imgRoomBottomSubBorder2.width;
	imgRoomBottomSubBorder3.top = imgRoomBottomSubBorder2.top;
	
	imgRoomBottomSubBorder4.left = imgRoomMidRound.left + imgRoomMidRound.width - imgRoomBottomSubBorder4.width - 6;
	imgRoomBottomSubBorder4.top = imgRoomBottomSubBorder3.top;
	
	imgRoomBottomSubBorder5.left = imgRoomBottomSubBorder4.left + imgRoomBottomSubBorder4.width;
	imgRoomBottomSubBorder5.top = imgRoomBottomSubBorder4.top;
	
	//房间主播列表
	imgActorHeadTopTitle.visible = true;    
	imgActorHeadTopTitle.left = 2;
	imgActorHeadTopTitle.top = 70;
	imgActorHeadTopTitle.width = 63;
	imgActorHeadTopTitle.height = 48;
	
	btnActorHeadTopTitleDown.visible = true;    
	btnActorHeadTopTitleDown.left = imgActorHeadTopTitle.left+20;
	btnActorHeadTopTitleDown.top = imgActorHeadTopTitle.top + 25;
	btnActorHeadTopTitleDown.width = 21;
	btnActorHeadTopTitleDown.height = 15;	
	
	imgActorHeadTop.visible = false;    
	imgActorHeadTop.left = imgActorHeadTopTitle.left;
	imgActorHeadTop.top = imgActorHeadTopTitle.top;
	imgActorHeadTop.width = 67;
	imgActorHeadTop.height = 50;	
	
	imgActorHeadBk.visible = false;
	imgActorHeadBk.left = imgActorHeadTop.left;
	imgActorHeadBk.top = imgActorHeadTop.top + imgActorHeadTop.height;
	imgActorHeadBk.width = 67;
	imgActorHeadBk.height = 80;		
	
	btnActorHeadUp.visible = false;
	btnActorHeadUp.left = imgActorHeadTop.left + 15;
	btnActorHeadUp.top = imgActorHeadTop.top + 25;
	btnActorHeadUp.width = 27;
	btnActorHeadUp.height = 14;	
	
	imgActorHead1bk.visible = false;  
	imgActorHead1bk.left = imgActorHeadTop.left+6;
	imgActorHead1bk.top = btnActorHeadUp.top + btnActorHeadUp.height +1;
	imgActorHead1bk.width = 48;
	imgActorHead1bk.height = 49;
	
	imgActorHead2bk.visible = false;  
	imgActorHead2bk.left = imgActorHead1bk.left;
	imgActorHead2bk.top = imgActorHead1bk.top + imgActorHead1bk.height+1;
	imgActorHead2bk.width = 48;
	imgActorHead2bk.height = 49;
	
	imgActorHead3bk.visible = false;  
	imgActorHead3bk.left = imgActorHead2bk.left;
	imgActorHead3bk.top = imgActorHead2bk.top + imgActorHead2bk.height+1 ;
	imgActorHead3bk.width = 48;
	imgActorHead3bk.height = 49;
	
	imgActorHead4bk.visible = false;  
	imgActorHead4bk.left = imgActorHead3bk.left;
	imgActorHead4bk.top = imgActorHead3bk.top + imgActorHead3bk.height+1;
	imgActorHead4bk.width = 48;
	imgActorHead4bk.height = 49;	
	
	imgActorHead1.visible = false;  
	imgActorHead1.left = imgActorHead1bk.left + 5;
	imgActorHead1.top = imgActorHead1bk.top+ 5;
	imgActorHead1.width = 38;
	imgActorHead1.height = 39;
	
	imgActorHead2.visible = false;
	imgActorHead2.left = imgActorHead1.left;
	imgActorHead2.top = imgActorHead2bk.top+5;
	imgActorHead2.width = 38;
	imgActorHead2.height = 39;
	
	imgActorHead3.visible = false;
	imgActorHead3.left = imgActorHead1.left;
	imgActorHead3.top = imgActorHead3bk.top+5;
	imgActorHead3.width = 38;
	imgActorHead3.height = 39;
	
	imgActorHead4.visible = false;
	imgActorHead4.left = imgActorHead1.left;
	imgActorHead4.top = imgActorHead4bk.top+5;
	imgActorHead4.width = 38;
	imgActorHead4.height = 39;	
	
	btnActorHeadDown.visible = false;
	btnActorHeadDown.left = btnActorHeadUp.left ;
	btnActorHeadDown.top = imgActorHead4.top + imgActorHead4.height + 6;
	btnActorHeadDown.width = 27;
	btnActorHeadDown.height = 14;
	
	imgActorHeadTitle.visible = true;
	imgActorHeadTitle.left = imgActorHeadTop.left;
	imgActorHeadTitle.top = btnActorHeadDown.top + btnActorHeadDown.height;
	imgActorHeadTitle.width = 67;
	imgActorHeadTitle.height = 39;	

	btnActorHeadTitleClose.visible = true;
	btnActorHeadTitleClose.left = imgActorHeadTitle.left+20;
	btnActorHeadTitleClose.top = imgActorHeadTitle.top + 20;
	btnActorHeadTitleClose.width = 12;
	btnActorHeadTitleClose.height = 13;		
	
	imgActorHeadCtrlBack_H.visible = false;
	imgActorHeadCtrlBack_H.left = imgActorHead1.left-1;
	imgActorHeadCtrlBack_H.top = imgActorHead1.top-1;
	imgActorHeadCtrlBack_H.width = 50;
	imgActorHeadCtrlBack_H.height = 51;	
	Window.EndPaint();
 
}

function OnNotify(code,code1){
    switch(code){
	  case NOTIFY_SKIN_ROOM_LEFT_DLG:
	       { 
	           //itemRoomLeftDlg.SetClient(code1);
	       }
	       break;
	   case NOTIFY_SKIN_ROOM_MID_DLG:
	       {
		       itemRoomMidDlg.SetClient(code1);
		   }
		   break;
	   case NOTIFY_SKIN_ROOM_RIGHT_DLG:
	       {
		       itemRoomRightDlg.SetClient(code1);
		   }
		   break;
	   case NOTIFY_SKIN_ROOM_BOTTOMLEFT_DLG:
	       {
				itemRoomBottomLeftDlg.SetClient(code1);
		   }
		   break;
	   case NOTIFY_SKIN_ROOM_BOTTOM_POS:
	       {
			    
		   }
		   break;
	   case NOTIFY_SKIN_ROOM_PUBLIC_MIC1_DLG:
	       {
				itemPublicMic1.SetClient(code1);
		   }
		   break;
	   case NOTIFY_SKIN_ROOM_PUBLIC_MIC2_DLG:
	       {
				itemPublicMic2.SetClient(code1);
		   }
		   break;
	   case NOTIFY_SKIN_ROOM_PUBLIC_MIC3_DLG:
	       {
				itemPublicMic3.SetClient(code1);
		   }
		   break;
	  default: break;
	}
}








