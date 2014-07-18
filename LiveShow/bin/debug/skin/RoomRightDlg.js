
var SKIN_NOTIFY_SEARCH_DLG_HWND = 1;
var SKIN_ON_CLICK_TABBTN_MGR = 2;
var SKIN_ON_CLICK_TABBTN_USER = 3;
var SKIN_ON_CLICK_TABBTN_MIC = 4;
var SKIN_ON_CLICK_BTN_SEARCH = 5;
var SKIN_ON_CLICK_ICON_INSTRUCTION = 6;
var SKIN_ON_CLICK_BTN_WHEREIAM = 7;
var SKIN_ON_CLICK_BTN_GIFTLIST_DOWN = 8;
var SKIN_NOTIFY_GIFTLIST_DOWN = 9;
var SKIN_ON_CLICK_BTN_GIFTLIST_UP = 10;
var SKIN_ON_CLICK_TAB_GIFT = 11;
var SKIN_ON_CLICK_PRESENT_DETAIL = 12;
var SKIN_ON_CLICK_SPEAKER = 13;
var SKIN_NOTIFY_SEARCH_LIST = 14;
var SKIN_NOTIFY_SHOW_USERITEM = 16;
var SKIN_ON_CLICK_BTN_PAY_VIP = 17;
var SKIN_NOTIFY_MARK_DLG = 18;
var SKIN_ON_CLICK_BTN_MY_GOODS = 15;
var SKIN_ON_CLICK_BTN_GIFT = 19;
var SKIN_ON_CLICK_BTN_GAME = 20;
var SKIN_ON_CLICK_BTN_BAITU_SERVICE = 21;
var SKIN_ON_CLICK_TEXT_PAY = 22;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnGiftHot.AttachEvent("OnClick", OnClickBtnGiftHot);
btnGiftLove.AttachEvent("OnClick", OnClickBtnGiftLove);
btnGiftFriend.AttachEvent("OnClick", OnClickBtnGiftFriend);
btnGiftLuxury.AttachEvent("OnClick", OnClickBtnGiftLuxury);
btnGiftProps.AttachEvent("OnClick", OnClickBtnGiftProps);

//btnGiftListUp.AttachEvent("OnClick",OnClickBtnGiftListUp);

btnPresentDetail.AttachEvent("OnClick",OnClickBtnPresentDetail);

// btnGift.AttachEvent("OnClick",OnClickBtnGift);
// btnMyGoods.AttachEvent("OnClick",OnClickBtnMyGoods);
// btnGame.AttachEvent("OnClick",OnClickBtnGame);

btnBaiTuService.AttachEvent("OnClick", OnClickBtnBaiTuService);
textPay.AttachEvent("OnClick", OnClickTextPay);
btnPayVIP.AttachEvent("OnClick", OnClickTextPay);

function OnClickBtnBaiTuService()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_BAITU_SERVICE, 0);
}

function OnClickTextPay()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_TEXT_PAY, 0);
}

function OnClickBtnGiftHot()
{
	btnGiftHot.checked = true;
    btnGiftLove.checked = false;
    btnGiftFriend.checked = false;
    btnGiftLuxury.checked = false;
    btnGiftProps.checked = false;
	
	btnGiftHot.labelNormalColor = "#ffffff";
    btnGiftLove.labelNormalColor = "#ffffff";
    btnGiftFriend.labelNormalColor = "#ffffff";
    btnGiftLuxury.labelNormalColor = "#ffffff";
    btnGiftProps.labelNormalColor = "#ffffff";
	
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_GIFT,0);
}
function OnClickBtnGiftLove()
{
	btnGiftHot.checked = false;
    btnGiftLove.checked = true;
    btnGiftFriend.checked = false;
    btnGiftLuxury.checked = false;
    btnGiftProps.checked = false;
	
	btnGiftHot.labelNormalColor = "#ffffff";
    btnGiftLove.labelNormalColor = "#ffffff";
    btnGiftFriend.labelNormalColor = "#ffffff";
    btnGiftLuxury.labelNormalColor = "#ffffff";
    btnGiftProps.labelNormalColor = "#ffffff";
	
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_GIFT,1);
}
function OnClickBtnGiftFriend()
{
	btnGiftHot.checked = false;
    btnGiftLove.checked = false;
    btnGiftFriend.checked = true;
    btnGiftLuxury.checked = false;
    btnGiftProps.checked = false;
	
	btnGiftHot.labelNormalColor = "#ffffff";
    btnGiftLove.labelNormalColor = "#ffffff";
    btnGiftFriend.labelNormalColor = "#ffffff";
    btnGiftLuxury.labelNormalColor = "#ffffff";
    btnGiftProps.labelNormalColor = "#ffffff";
	
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_GIFT,2);
}
function OnClickBtnGiftLuxury()
{
	btnGiftHot.checked = false;
    btnGiftLove.checked = false;
    btnGiftFriend.checked = false;
    btnGiftLuxury.checked = true;
    btnGiftProps.checked = false;
	
	btnGiftHot.labelNormalColor = "#ffffff";
    btnGiftLove.labelNormalColor = "#ffffff";
    btnGiftFriend.labelNormalColor = "#ffffff";
    btnGiftLuxury.labelNormalColor = "#ffffff";
    btnGiftProps.labelNormalColor = "#ffffff";
	
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_GIFT,3);
}

function OnClickBtnGiftProps()
{
	btnGiftHot.checked = false;
    btnGiftLove.checked = false;
    btnGiftFriend.checked = false;
    btnGiftLuxury.checked = false;
    btnGiftProps.checked = true;
	
	btnGiftHot.labelNormalColor = "#ffffff";
    btnGiftLove.labelNormalColor = "#ffffff";
    btnGiftFriend.labelNormalColor = "#ffffff";
    btnGiftLuxury.labelNormalColor = "#ffffff";
    btnGiftProps.labelNormalColor = "#ffffff";
	
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_GIFT,4);
}

// function OnClickBtnGiftListUp()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_GIFTLIST_UP,0);
// }

function OnClickBtnPresentDetail()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_PRESENT_DETAIL,0);
}

// function OnClickBtnGift()
// {
    // btnGift.checked = true;
    // btnMyGoods.checked = false;
	
	// btnGift.labelNormalColor = "#0";
    // btnMyGoods.labelNormalColor = "#ffffff";
	
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_GIFT, 0);
// }

// function OnClickBtnGame()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_GAME, 0);
// }

// function OnClickBtnMyGoods()
// {
    // btnGift.checked = false;
    // btnMyGoods.checked = true;
	
	// btnGift.labelNormalColor = "#ffffff";
    // btnMyGoods.labelNormalColor = "#0";
	
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_MY_GOODS, 0);
// }

//////////////////////////////////////////////////////////////////////////////////////////////
function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	imgRoomRightDlgBk.left = 0;
	imgRoomRightDlgBk.top = 0;
	imgRoomRightDlgBk.width = cx;
	imgRoomRightDlgBk.height = cy;
	
	//先画上，再画下，最后画喇叭，因为喇叭区要可伸缩
	//上部分
	imgBtnGiftBk.left = 0;
	imgBtnGiftBk.top = 0;
	imgBtnGiftBk.width = cx - imgBtnGiftBk.left;
	imgBtnGiftBk.height = 31;
	
	// btnGift.left = imgBtnGiftBk.left + 15;
	// btnGift.top = 6;
	// btnGift.width = 44;
	// btnGift.height = 27;
	
	// btnMyGoods.left = btnGift.left + btnGift.width + 20;
	// btnMyGoods.top = btnGift.top;
	// btnMyGoods.width = btnGift.width;
	// btnMyGoods.height = btnGift.height;
	
	// btnGame.left = btnMyGoods.left + btnMyGoods.width + 20;
	// btnGame.top = btnMyGoods.top;
	// btnGame.width = btnMyGoods.width;
	// btnGame.height = btnMyGoods.height;
	
	btnGiftHot.left = imgBtnGiftBk.left + 15;
	btnGiftHot.top = imgBtnGiftBk.top + 2;
	btnGiftHot.width = 44;
	btnGiftHot.height = 31;
	
	imgSeperator1.left = btnGiftHot.left + btnGiftHot.width;
	imgSeperator1.top = btnGiftHot.top - 2;
	imgSeperator1.width = 2;
	imgSeperator1.height = btnGiftHot.height;
	
	btnGiftLove.left = btnGiftHot.left + btnGiftHot.width + 2;
	btnGiftLove.top = btnGiftHot.top;
	btnGiftLove.width = btnGiftHot.width;
	btnGiftLove.height = btnGiftHot.height;
	
	imgSeperator2.left = btnGiftLove.left + btnGiftLove.width;
	imgSeperator2.top = imgSeperator1.top;
	imgSeperator2.width = imgSeperator1.width;
	imgSeperator2.height = imgSeperator1.height;
	
	btnGiftFriend.left = btnGiftLove.left + btnGiftLove.width + 2;
	btnGiftFriend.top = btnGiftLove.top;
	btnGiftFriend.width = btnGiftLove.width;
	btnGiftFriend.height = btnGiftLove.height;
	
	imgSeperator3.left = btnGiftFriend.left + btnGiftFriend.width;
	imgSeperator3.top = imgSeperator2.top;
	imgSeperator3.width = imgSeperator2.width;
	imgSeperator3.height = imgSeperator2.height;
	
	btnGiftLuxury.left = btnGiftFriend.left + btnGiftFriend.width + 2;
	btnGiftLuxury.top = btnGiftFriend.top;
	btnGiftLuxury.width = btnGiftFriend.width;
	btnGiftLuxury.height = btnGiftFriend.height;
	
	imgSeperator4.left = btnGiftLuxury.left + btnGiftLuxury.width;
	imgSeperator4.top = imgSeperator3.top;
	imgSeperator4.width = imgSeperator3.width;
	imgSeperator4.height = imgSeperator3.height;
	
	btnGiftProps.left = btnGiftLuxury.left + btnGiftLuxury.width + 2;
	btnGiftProps.top = btnGiftLuxury.top;
	btnGiftProps.width = btnGiftLuxury.width;
	btnGiftProps.height = btnGiftLuxury.height;
	
	imgSendToAndMountBk.left = imgBtnGiftBk.left;
	imgSendToAndMountBk.top = imgBtnGiftBk.top + imgBtnGiftBk.height;
	imgSendToAndMountBk.width = imgBtnGiftBk.width;
	imgSendToAndMountBk.height = 31;
	
	textSendTo.left = imgSendToAndMountBk.left + 15;
	textSendTo.top = imgSendToAndMountBk.top + 8;
	textSendTo.width = textSendTo.textWidth;
	textSendTo.height = textSendTo.textHeight;
	
	itemComboSendTo.left = textSendTo.left + textSendTo.width + 3;
	itemComboSendTo.top = textSendTo.top - 2;
	itemComboSendTo.width = 90;
	itemComboSendTo.height = 20;
	
	textAmount.left = itemComboSendTo.left + itemComboSendTo.width + 10;
	textAmount.top = textSendTo.top;
	textAmount.width = textAmount.textWidth;
	textAmount.height = textAmount.textHeight;
	
	itemComboAmount.left = textAmount.left + textAmount.width + 3;
	itemComboAmount.top = itemComboSendTo.top
	itemComboAmount.width = 52;
	itemComboAmount.height = itemComboSendTo.height;
	
	HotGiftList.width = imgSendToAndMountBk.width - 20;
	HotGiftList.height = 170;
	HotGiftList.left = imgSendToAndMountBk.left + imgSendToAndMountBk.width - HotGiftList.width;
	HotGiftList.top = imgSendToAndMountBk.top + imgSendToAndMountBk.height;
	
	LoveGiftList.width = HotGiftList.width;
	LoveGiftList.height = HotGiftList.height;
	LoveGiftList.left = HotGiftList.left;
	LoveGiftList.top = HotGiftList.top;
	FriendGiftList.width = HotGiftList.width;
	FriendGiftList.height = HotGiftList.height;
	FriendGiftList.left = HotGiftList.left;
	FriendGiftList.top = HotGiftList.top;
	LuxuryGiftList.width = HotGiftList.width;
	LuxuryGiftList.height = HotGiftList.height;
	LuxuryGiftList.left = HotGiftList.left;
	LuxuryGiftList.top = HotGiftList.top;
	ToolGiftList.width = HotGiftList.width;
	ToolGiftList.height = HotGiftList.height;
	ToolGiftList.left = HotGiftList.left;
	ToolGiftList.top = HotGiftList.top;
	
	MyGoodsList.visible = false;
	MyGoodsList.width = HotGiftList.width;
	MyGoodsList.height = HotGiftList.height;
	MyGoodsList.left = HotGiftList.left;
	MyGoodsList.top = HotGiftList.top;
	
	imgMoneyBk.left = imgSendToAndMountBk.left;
	imgMoneyBk.top = HotGiftList.top + HotGiftList.height;
	imgMoneyBk.width = imgSendToAndMountBk.width;
	imgMoneyBk.height = imgSendToAndMountBk.height;
	
	imgCoin.left = imgMoneyBk.left + 25;
	imgCoin.top = imgMoneyBk.top + 6;
	imgCoin.width = 14;
	imgCoin.height = 14;
	
	textCoin.left = imgCoin.left + imgCoin.width + 1;
	textCoin.top = imgCoin.top;
	textCoin.width = textCoin.textWidth;
	textCoin.height = textCoin.textHeight;
	
	textHowMuch.left = textCoin.left + textCoin.width + 1;
	textHowMuch.top = textCoin.top - 2;
	textHowMuch.width = 80;
	textHowMuch.height = 15;
	
	btnPresentDetail.left = textHowMuch.left + textHowMuch.width;
	btnPresentDetail.top = textHowMuch.top + 1;
	btnPresentDetail.width = 23;
	btnPresentDetail.height = 22;
	
	btnPayVIP.left = btnPresentDetail.left + btnPresentDetail.width + 10;
	btnPayVIP.top = btnPresentDetail.top - 1;
	btnPayVIP.width = 70;
	btnPayVIP.height = 20;
	//下部分
	imgMutipleBk.width = cx;
	imgMutipleBk.height = 57;
	imgMutipleBk.left = 0;
	imgMutipleBk.top = cy - imgMutipleBk.height;
	
	btnBaiTuService.left = imgMutipleBk.left + 113;
	btnBaiTuService.top = imgMutipleBk.top + 21;
	btnBaiTuService.width = 52;
	btnBaiTuService.height = 23;
	
	textPay.left = btnBaiTuService.left + btnBaiTuService.width + 15;
	textPay.top = btnBaiTuService.top;
	textPay.width = 59;
	textPay.height = 22;
	//中部分
	if( (imgMutipleBk.top - itemHtmlSpeaker.top) > 0)
	{
		itemHtmlSpeaker.visible = true;
		itemHtmlSpeaker.left = imgMoneyBk.left;
		itemHtmlSpeaker.top = imgMoneyBk.top + imgMoneyBk.height;
		itemHtmlSpeaker.width = imgMoneyBk.width;
		itemHtmlSpeaker.height = imgMutipleBk.top - itemHtmlSpeaker.top;
	}else
	{
		itemHtmlSpeaker.visible = false;
	}
	
	
	
	
}

function OnNotify(code, code1)
{
  switch(code)
  {
  case SKIN_NOTIFY_SEARCH_DLG_HWND:
       {
	       itemSearchDlg.SetClient(code1);
	   }
	   break;
  case SKIN_NOTIFY_GIFTLIST_DOWN:
       {
	       //OnSize(Window.width,Window.height);
	   }
	   break;
  case SKIN_NOTIFY_SEARCH_LIST:
	   {
			if(0 == code1)
			{
				searchlist.visible = false;
				if(tabBtnUser.checked)
				{
					userList.visible = true;
				}
				if(tabBtnMgr.checked)
				{
					managerList.visible = true;
				}
				if(tabBtnMicList.checked)
				{
					micList.visible = true;
				}
				OnSize(Window.width,Window.height);
			}
			else
			{
			}
		}
		break;
  case SKIN_NOTIFY_SHOW_USERITEM:
	   {
			if(0 == code1)
			{
				userList.visible = true;
				managerList.visible = false;
				micList.visible = false;
				searchlist.visible = false;
				tabBtnUser.labelNormalColor = "#0";
				tabBtnMgr.labelNormalColor = "#ffffff";
				tabBtnMicList.labelNormalColor = "#ffffff";
				tabBtnMgr.checked = false;
				tabBtnUser.checked = true;
				tabBtnMicList.checked = false;
				btnSearch.checked = false;
				OnSize(Window.width,Window.height);
			}
	   }
	   break;
  case SKIN_NOTIFY_MARK_DLG:
	  {
		  
	  }
	  break;
  default:
    break;
  }
}
