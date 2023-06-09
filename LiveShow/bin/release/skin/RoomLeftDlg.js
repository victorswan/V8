
var NOTIFY_SKIN_ROOM_PUBLIC_MIC1_DLG = 1;
var NOTIFY_SKIN_ROOM_PUBLIC_MIC2_DLG = 2;
var NOTIFY_SKIN_ROOM_PUBLIC_MIC3_DLG = 3;
var SKIN_NOTIFY_PUBLICMIC_DIS = 4;

var SKIN_ON_CLICK_PAIMIC = 5;
var SKIN_ON_CLICK_ICON_MIC0 = 6;
var SKIN_ON_CLICK_ICON_MIC1 = 7;
var SKIN_ON_CLICK_ICON_SPEAKER0 = 8;
var SKIN_ON_CLICK_ICON_SPEAKER1 = 9;

var SKIN_ON_CLICK_BTN_USERSETTING = 10;
var SKIN_ON_CLICK_BTN_ROOMMGR = 11;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnPaiMic.AttachEvent("OnClick",OnClickBtnPaiMic);
btnFangMic.AttachEvent("OnClick",OnClickBtnPaiMic);

// btnUserSetting.AttachEvent("OnClick",OnClickBtnUserSetting);
// btnRoomMgr.AttachEvent("OnClick",OnClickBtnRoomMgr);

function OnClickBtnPaiMic()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_PAIMIC,0);
}

// function OnClickBtnUserSetting()
// {
    // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_USERSETTING,0);
// }

// function OnClickBtnRoomMgr()
// {
    // Window.PostSkinMessage(SKIN_ON_CLICK_BTN_ROOMMGR,0);
// }

/////////////////////////////////////////////////

var m_publicMicDis = 0;

function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	imgRoomLeftDlgBk.left = 0;
	imgRoomLeftDlgBk.top = 0;
	imgRoomLeftDlgBk.width = cx;
	imgRoomLeftDlgBk.height = cy;
	/////////////////////////////////
	imgPublicOnMic2Bk.width = 200;
	imgPublicOnMic2Bk.height = 198;
	imgPublicOnMic2Bk.left = imgRoomLeftDlgBk.left + (imgRoomLeftDlgBk.width - imgPublicOnMic2Bk.width)/2;
	imgPublicOnMic2Bk.top = cy - 8 - imgPublicOnMic2Bk.height;
	
	imgPublicOutMic2Bk.left = imgPublicOnMic2Bk.left;
	imgPublicOutMic2Bk.top = imgPublicOnMic2Bk.top;
	imgPublicOutMic2Bk.width = imgPublicOnMic2Bk.width;
	imgPublicOutMic2Bk.height = imgPublicOnMic2Bk.height;
	itemPublicMic2.visible = true;
	itemPublicMic2.width = 364;
	itemPublicMic2.height = 295;
	itemPublicMic2.left = imgRoomLeftDlgBk.left + (imgRoomLeftDlgBk.width - itemPublicMic2.width)/2;
	itemPublicMic2.top = imgPublicOnMic2Bk.top + imgPublicOnMic2Bk.height - 20 - itemPublicMic2.height;
	
	imgPublicOnMic1Bk.width = 200;
	imgPublicOnMic1Bk.height = 198;
	imgPublicOnMic1Bk.left = itemPublicMic2.left - 15 - imgPublicOnMic1Bk.width;
	imgPublicOnMic1Bk.top = imgPublicOnMic2Bk.top + imgPublicOnMic2Bk.height - imgPublicOnMic1Bk.height;
	
	imgPublicOutMic1Bk.left = imgPublicOnMic1Bk.left;
	imgPublicOutMic1Bk.top = imgPublicOnMic1Bk.top;
	imgPublicOutMic1Bk.width = imgPublicOnMic1Bk.width;
	imgPublicOutMic1Bk.height = imgPublicOnMic1Bk.height;
	itemPublicMic1.visible = true;
	itemPublicMic1.left = imgPublicOnMic1Bk.left;
	itemPublicMic1.top = imgPublicOnMic1Bk.top + 1;
	itemPublicMic1.width = 196;
	itemPublicMic1.height = 169;
	
	imgPublicOnMic3Bk.width = imgPublicOnMic1Bk.width;
	imgPublicOnMic3Bk.height = imgPublicOnMic1Bk.height;
	imgPublicOnMic3Bk.left = itemPublicMic2.left + itemPublicMic2.width + 15;
	imgPublicOnMic3Bk.top = imgPublicOnMic1Bk.top;
	
	imgPublicOutMic3Bk.left = imgPublicOnMic3Bk.left;
	imgPublicOutMic3Bk.top = imgPublicOnMic3Bk.top;
	imgPublicOutMic3Bk.width = imgPublicOnMic3Bk.width;
	imgPublicOutMic3Bk.height = imgPublicOnMic3Bk.height;
	itemPublicMic3.visible = true;
	itemPublicMic3.left = imgPublicOnMic3Bk.left;
	itemPublicMic3.top = imgPublicOnMic3Bk.top + 1;
	itemPublicMic3.width = itemPublicMic1.width;
	itemPublicMic3.height = itemPublicMic1.height;
	////////////////////////////////////////////////
	
	btnPaiMic.visible = true;
	btnPaiMic.width = 108;
	btnPaiMic.height = 47;
	btnPaiMic.left = imgRoomLeftDlgBk.left + imgRoomLeftDlgBk.width - 15 - btnPaiMic.width;
	btnPaiMic.top = imgRoomLeftDlgBk.top + imgRoomLeftDlgBk.height - 2 - btnPaiMic.height;
	
	btnFangMic.left = btnPaiMic.left;
	btnFangMic.top = btnPaiMic.top;
	btnFangMic.width = btnPaiMic.width;
	btnFangMic.height = btnPaiMic.height;
	
	// btnUserSetting.visible = true;
	// btnUserSetting.width = 84;
	// btnUserSetting.height = 24;
	// btnUserSetting.left = btnPaiMic.left;
	// btnUserSetting.top = btnPaiMic.top - 8 - btnUserSetting.height;
	
	// btnRoomMgr.visible = true;
	// btnRoomMgr.width = btnUserSetting.width;
	// btnRoomMgr.height = btnUserSetting.height;
	// btnRoomMgr.left = btnUserSetting.left;
	// btnRoomMgr.top = btnUserSetting.top - 5 - btnRoomMgr.height;
	
	
}

function OnNotify(code, code1)
{
  switch(code)
  {
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
   case SKIN_NOTIFY_PUBLICMIC_DIS:
       {
	       m_publicMicDis = code1;
		   if(m_publicMicDis < 50)
		      m_publicMicDis = 0;
		   OnSize(Window.width,Window.height);
	   }
  default:
    break;
  }
}
