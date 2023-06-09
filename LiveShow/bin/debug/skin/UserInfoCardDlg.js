
var SKIN_ON_CLICK_DETAIL = 1 ; 
var SKIN_ON_CLICK_PHOTO = 2 ;
var SKIN_ON_CLICK_SELFVERIFY = 3;
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnDetailInfo.AttachEvent("OnClick" , OnClickbtnDetail);
btnPhoto.AttachEvent("OnClick" ,OnClickbtnPhoto ) ;
btnSelfVerify.AttachEvent("OnClick", OnClickSelfVerify);


function OnClickbtnDetail()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_DETAIL,0);
}

function OnClickbtnPhoto()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_PHOTO,0);
}

function OnClickSelfVerify()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_SELFVERIFY, 0);
}

Window.AttachEvent("OnShowWindow", OnShowWindowWindow)
function OnShowWindowWindow(bShow)
{
  if (bShow) {
    imgRichLevel.Play();
	//imgVip.Play();
  } else {
    imgRichLevel.Stop();
	//imgVip.Stop();
  }
}

function OnInit()
{
	textTitle.text = "";
    textTitle.fontSize="10";
	textTitle.visible = false;
	btnSysClose.visible = false;
	btnSysMinimize.visible = false;
	btnSysMaximize.visible = false;
	
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	

	ImgIconIntroduceBk.visible = true;
	ImgIconIntroduceBk.left = 1;
	ImgIconIntroduceBk.top = 1;
	ImgIconIntroduceBk.width = cx - 2;
	ImgIconIntroduceBk.height = cy - 2;
	
	imgFramgQQUserInfoCardDlg.left = 0;
	imgFramgQQUserInfoCardDlg.top = 0;
	imgFramgQQUserInfoCardDlg.width = cx;
	imgFramgQQUserInfoCardDlg.height = cy;
	
	imgHeadBorder.visible = true;
	imgHeadBorder.left = ImgIconIntroduceBk.left + 8;
	imgHeadBorder.top = ImgIconIntroduceBk.top + 8;
	imgHeadBorder.width = 100;
	imgHeadBorder.height = 100;
	
	imgUserHead.visible = true;
	imgUserHead.left = imgHeadBorder.left + 1 ;
	imgUserHead.top = imgHeadBorder.top + 1;
	imgUserHead.width = imgHeadBorder.width - 2;
	imgUserHead.height = imgHeadBorder.height - 2;
	
	textNameAndCount.visible = true;
	textNameAndCount.left = imgHeadBorder.left + imgHeadBorder.width + 11 ;
	textNameAndCount.top = imgHeadBorder.top+ 2 ;
	textNameAndCount.width = 140 ;
	textNameAndCount.height = textNameAndCount.textHeight ;
		
	imgVip.visible = true;
	imgVip.left = textNameAndCount.left;
	imgVip.top = textNameAndCount.top + textNameAndCount.height + 5;
	imgVip.width = 16;	
	imgVip.height = 16;
	//imgVip.Play();
	
	imgRichLevel.visible = true;
	imgRichLevel.left = imgVip.left + imgVip.width + 5;
	imgRichLevel.top = imgVip.top + 2;
	// imgRichLevelTip.visible = true;
	// imgRichLevelTip.left = imgRichLevel.left;
	// imgRichLevelTip.top = imgRichLevel.top;
	// imgRichLevelTip.width = imgRichLevel.width;
	// imgRichLevelTip.height = imgRichLevel.height;
	//imgRichLevel.Play();
	
	imgGift.visible = true;
	imgGift.left = imgVip.left;
	imgGift.top = imgVip.top + imgVip.height + 5;
	imgGift.width = imgVip.width;
	imgGift.height = imgVip.height;
	
	textGiftRank.visible = true ;
	textGiftRank.left =imgGift.left + imgGift.width ;
	textGiftRank.top = imgGift.top ;
	textGiftRank.width = textGiftRank.txtWidth ;
	textGiftRank.height = imgGift.height ;
	
	imgBaiTuVerify.left = imgGift.left - 6;
	imgBaiTuVerify.top = imgVip.top + imgVip.height + 4;
	
	btnDetailInfo.visible = true ;
	btnDetailInfo.width = 70 ;
	btnDetailInfo.height = 20 ;
	btnDetailInfo.left = cx -77  ;
	btnDetailInfo.top = cy- 30 ;
	
	btnPhoto.left = btnDetailInfo.left - 25 ;
    btnPhoto.width = 20 ;
	btnPhoto.height = 19 ;
	btnPhoto.top = btnDetailInfo.top ;
	
	btnSelfVerify.left = btnDetailInfo.left - btnSelfVerify.width;
	btnSelfVerify.top = btnDetailInfo.top + 3;
}

function OnNotify(code, code1)
{
	
}
