
var  NOFITY_SKIN_SHOW_MARK = 2;
var  SKIN_ON_CLICK_BTN_GETTICKET = 3;
var  SKIN_ON_CLICK_BTN_OK_IN_12 = 4;
var  SKIN_ON_CLICK_BTN_OK_IN_13 = 5;
var  SKIN_ON_CLICK_BTN_ORDERSONG = 6;
//var  SKIN_ON_CLICK_BTN_PAIMIC = 7;
var  SKIN_ON_CLICK_BTN_OK_IN_20 = 8;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnGetTicket.AttachEvent("OnClick", OnClickBtnGetTicket);
btnOKIn12.AttachEvent("OnClick", OnClickBtnOKIn12);
btnOKIn13.AttachEvent("OnClick", OnClickBtnOKIn13);
btnOrderSong.AttachEvent("OnClick", OnClickBtnOrderSong);
btnOKIn20.AttachEvent("OnClick", OnClickBtnOKIn20);

function OnClickBtnGetTicket()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_GETTICKET, 0);
}

function OnClickBtnOKIn12()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_OK_IN_12, 0);
}

function OnClickBtnOKIn13()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_OK_IN_13, 0);
}

function OnClickBtnOrderSong()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_ORDERSONG, 0);
}


function OnClickBtnOKIn20()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_OK_IN_20, 0);
}

function OnInit()
{
	checkUseOne.visible = false;
    radioGoodMark.visible = false;
	radioBadMark.visible = false;
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{
	imgSongMarkBorderLeft.left = 0;
	imgSongMarkBorderLeft.top = 0;
	imgSongMarkBorderLeft.width = 1;
	imgSongMarkBorderLeft.height = cy;
	
	imgSongMarkBorderBottom.left = 0;
	imgSongMarkBorderBottom.top = cy - 1;
	imgSongMarkBorderBottom.width = cx;
	imgSongMarkBorderBottom.height = 1;
	
	imgSongMarkBorderRight.left = cx - 1;
	imgSongMarkBorderRight.top = 0;
	imgSongMarkBorderRight.width = 1;
	imgSongMarkBorderRight.height = cy;
	
	imgSongMarkBorderTop.left = 0;
	imgSongMarkBorderTop.top = 0;
	imgSongMarkBorderTop.width = cx;
	imgSongMarkBorderTop.height = 1;

	imgSongMarkTitleBk.left = 1;
	imgSongMarkTitleBk.top = 1;
	imgSongMarkTitleBk.width = cx - 2;
	
	imgSongMarkTitle.left = imgSongMarkTitleBk.left + 2;
	imgSongMarkTitle.top = imgSongMarkTitleBk.top + 6;
	
	imgSongNameBk.left = imgSongMarkTitle.left + imgSongMarkTitle.width;
	imgSongNameBk.top = imgSongMarkTitleBk.top + 3;
	imgSongNameBk.width = cx - 2 - imgSongNameBk.left;
	imgSongNameBk.height = 24;
	
	imgSongMarkContentBk.left = 1;
	imgSongMarkContentBk.top = imgSongMarkTitleBk.top + imgSongMarkTitleBk.height - 1;
	imgSongMarkContentBk.width = cx - 2;
	imgSongMarkContentBk.height = 90;
	
	textSongName.left = imgSongNameBk.left + 5;
	textSongName.top = imgSongNameBk.top + 1;
	textSongName.width = 120;
	textSongName.height = imgSongNameBk.height - 2;
	
	textActorName.left = textSongName.left + textSongName.width;
	textActorName.top = textSongName.top;
	textActorName.width = imgSongNameBk.left + imgSongNameBk.width - 5 - textActorName.left;
	textActorName.height = textSongName.height;
}

function SetUnVisible()
{
	textUpCon1.visible = false;
	textUpCon1.horizAlign="center";
	textUpCon2.visible = false;
	textUpCon2.horizAlign="center";
	textUpCon3.visible = false;
	textUpCon3.horizAlign="center";
	textSuperTicket.visible = false;
	textSuperTicket.horizAlign="center";
	textCountDownPrompt.visible = false;
	textCountDownPrompt.horizAlign="center";
	textCountDownTime.visible = false;
	textCountDownTime.horizAlign="center";
	textLeaveTicketPrompt.visible = false;
	textLeaveTicketPrompt.horizAlign="center";
	textLeaveTicket.visible = false;
	textLeaveTicket.horizAlign="center";
	textDownConPrompt.visible = false;
	textDownConPrompt.horizAlign="center";
	imgBaiTuOrTip.visible = false;
	textMark1.visible = false;
	textMark1.horizAlign="center";
	textMark2.visible = false;
	textMark2.horizAlign="center";
	textMark3.visible = false;
	textMark3.horizAlign="center";
	imgGoodMark.visible = false;
	textGoodMark.visible = false;
	textGoodMark.horizAlign="center";
	textVS.visible = false;
	textVS.horizAlign="center";
	imgBadMark.visible = false;
	textBadMark.visible = false;
	textBadMark.horizAlign="center";
	imgGiveupMark.visible = false;
	textGiveupMark.visible = false;
	textGiveupMark.horizAlign="center";
	checkUseOne.visible = false;
	radioGoodMark.visible = false;
	radioBadMark.visible = false;
	btnGetTicket.visible = false;
	btnOKIn12.visible = false;
	btnOKIn13.visible = false;
	btnOrderSong.visible = false;
	btnOKIn20.visible = false;
}

function Show1()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textCountDownPrompt.visible = true;
	textCountDownTime.visible = true;
	textLeaveTicketPrompt.visible = true;
	textLeaveTicket.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 9;
	textUpCon1.fontWeight = 800;
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 1;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 9;
	textUpCon2.fontWeight = 500;
	textUpCon2.left =  textUpCon1.left;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 12;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.text = "抢票倒计时：";
	textCountDownPrompt.left = 10;
	textCountDownPrompt.top = Window.height - 40;
	textCountDownPrompt.width = 96;
	textCountDownPrompt.height = 30;
	
	textCountDownTime.color = "#0";
	textCountDownTime.fontSize = 12;
	textCountDownTime.fontWeight = 800;
	textCountDownTime.fontFamily = "微软雅黑";
	textCountDownTime.left = textCountDownPrompt.left + textCountDownPrompt.width;
	textCountDownTime.top = textCountDownPrompt.top;
	textCountDownTime.width = 48;
	textCountDownTime.height = textCountDownPrompt.height;
	
	textLeaveTicketPrompt.color = "#0";
	textLeaveTicketPrompt.fontSize = 12;
	textLeaveTicketPrompt.fontWeight = 800;
	textLeaveTicketPrompt.fontFamily = "微软雅黑";
	textLeaveTicketPrompt.text = "余票：";
	textLeaveTicketPrompt.left = textCountDownTime.left + textCountDownTime.width + 5;
	textLeaveTicketPrompt.top = textCountDownTime.top;
	textLeaveTicketPrompt.width = 48;
	textLeaveTicketPrompt.height = textCountDownTime.height;
	
	textLeaveTicket.color = "#0";
	textLeaveTicket.fontSize = 12;
	textLeaveTicket.fontWeight = 800;
	textLeaveTicket.fontFamily = "微软雅黑";
	textLeaveTicket.left = textLeaveTicketPrompt.left + textLeaveTicketPrompt.width;
	textLeaveTicket.top = textLeaveTicketPrompt.top;
	textLeaveTicket.width = 48;
	textLeaveTicket.height = textLeaveTicketPrompt.height;
}

function Show2()
{
	//Show1();
}

function Show3()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textCountDownPrompt.visible = true;
	textCountDownTime.visible = true;
	textLeaveTicketPrompt.visible = true;
	textLeaveTicket.visible = true;
	textDownConPrompt.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 8;
	textUpCon1.fontWeight = 500;
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 1;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 8;
	textUpCon2.fontWeight = 500;
	textUpCon2.left =  textUpCon1.left;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;
	
	textDownConPrompt.color = "#006DFF";
	textDownConPrompt.fontSize = 11;
	textDownConPrompt.fontWeight = 800;
	textDownConPrompt.fontFamily = "微软雅黑";
	textDownConPrompt.left = 1;
	textDownConPrompt.top = textUpCon2.top + textUpCon2.height + 5;
	textDownConPrompt.width = Window.width - 2;
	textDownConPrompt.height = 22;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 10;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.text = "抢票倒计时：";
	textCountDownPrompt.left = 20;
	textCountDownPrompt.top = textDownConPrompt.top + textDownConPrompt.height;
	textCountDownPrompt.width = 86;
	textCountDownPrompt.height = 22;
	
	textCountDownTime.color = "#0";
	textCountDownTime.fontSize = 10;
	textCountDownTime.fontWeight = 800;
	textCountDownTime.fontFamily = "微软雅黑";
	textCountDownTime.left = textCountDownPrompt.left + textCountDownPrompt.width;
	textCountDownTime.top = textCountDownPrompt.top;
	textCountDownTime.width = 38;
	textCountDownTime.height = textCountDownPrompt.height;
	
	textLeaveTicketPrompt.color = "#0";
	textLeaveTicketPrompt.fontSize = 10;
	textLeaveTicketPrompt.fontWeight = 800;
	textLeaveTicketPrompt.fontFamily = "微软雅黑";
	textLeaveTicketPrompt.text = "余票：";
	textLeaveTicketPrompt.left = textCountDownTime.left + textCountDownTime.width + 5;
	textLeaveTicketPrompt.top = textCountDownTime.top;
	textLeaveTicketPrompt.width = 45;
	textLeaveTicketPrompt.height = textCountDownTime.height;
	
	textLeaveTicket.color = "#0";
	textLeaveTicket.fontSize = 10;
	textLeaveTicket.fontWeight = 800;
	textLeaveTicket.fontFamily = "微软雅黑";
	textLeaveTicket.left = textLeaveTicketPrompt.left + textLeaveTicketPrompt.width;
	textLeaveTicket.top = textLeaveTicketPrompt.top;
	textLeaveTicket.width = 38;
	textLeaveTicket.height = textLeaveTicketPrompt.height;
}

function Show4()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textCountDownPrompt.visible = true;
	textCountDownTime.visible = true;
	textLeaveTicketPrompt.visible = true;
	textLeaveTicket.visible = true;
	btnGetTicket.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 11;
	textUpCon1.fontWeight = 800;
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 12;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 10;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.horizAlign = "right";
	textCountDownPrompt.text = "抢票倒计时：";
	textCountDownPrompt.left = 1;
	textCountDownPrompt.top = textUpCon1.top + textUpCon1.height + 10;
	textCountDownPrompt.width = 85;
	textCountDownPrompt.height = 21;
	
	textCountDownTime.color = "#0";
	textCountDownTime.fontSize = 10;
	textCountDownTime.fontWeight = 800;
	textCountDownTime.fontFamily = "微软雅黑";
	textCountDownTime.left = textCountDownPrompt.left + textCountDownPrompt.width;
	textCountDownTime.top = textCountDownPrompt.top;
	textCountDownTime.width = 38;
	textCountDownTime.height = textCountDownPrompt.height;
	
	textLeaveTicketPrompt.color = "#0";
	textLeaveTicketPrompt.fontSize = 10;
	textLeaveTicketPrompt.fontWeight = 800;
	textLeaveTicketPrompt.fontFamily = "微软雅黑";
	textLeaveTicketPrompt.horizAlign = "right";
	textLeaveTicketPrompt.text = "余票：";
	textLeaveTicketPrompt.left = textCountDownPrompt.left;
	textLeaveTicketPrompt.top = textCountDownPrompt.top + textCountDownPrompt.height;
	textLeaveTicketPrompt.width = 85;
	textLeaveTicketPrompt.height = textCountDownPrompt.height;
	
	textLeaveTicket.color = "#0";
	textLeaveTicket.fontSize = 10;
	textLeaveTicket.fontWeight = 800;
	textLeaveTicket.fontFamily = "微软雅黑";
	textLeaveTicket.left = textLeaveTicketPrompt.left + textLeaveTicketPrompt.width;
	textLeaveTicket.top = textLeaveTicketPrompt.top;
	textLeaveTicket.width = 38;
	textLeaveTicket.height = textLeaveTicketPrompt.height;
	
	btnGetTicket.width = 120;
	btnGetTicket.height = 44;
	btnGetTicket.left = Window.width - 2 - btnGetTicket.width;
	btnGetTicket.top = Window.height - 2 - btnGetTicket.height;
}

function Show5()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textCountDownPrompt.visible = true;
	textCountDownTime.visible = true;
	textLeaveTicketPrompt.visible = true;
	textLeaveTicket.visible = true;
	imgBaiTuOrTip.visible = true;
	
	textUpCon1.color = "#2A2AFF";
	textUpCon1.fontSize = 12;
	textUpCon1.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 8;
	textUpCon2.fontWeight = 500;
	textUpCon2.left =  textUpCon1.left;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 10;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.horizAlign = "right";
	textCountDownPrompt.text = "余票倒计时：";
	textCountDownPrompt.left = 1;
	textCountDownPrompt.top = textUpCon1.top + textUpCon1.height + 20;
	textCountDownPrompt.width = 85;
	textCountDownPrompt.height = 21;
	
	textCountDownTime.color = "#0";
	textCountDownTime.fontSize = 10;
	textCountDownTime.fontWeight = 800;
	textCountDownTime.fontFamily = "微软雅黑";
	textCountDownTime.left = textCountDownPrompt.left + textCountDownPrompt.width;
	textCountDownTime.top = textCountDownPrompt.top;
	textCountDownTime.width = 38;
	textCountDownTime.height = textCountDownPrompt.height;
	
	textLeaveTicketPrompt.color = "#0";
	textLeaveTicketPrompt.fontSize = 10;
	textLeaveTicketPrompt.fontWeight = 800;
	textLeaveTicketPrompt.fontFamily = "微软雅黑";
	textLeaveTicketPrompt.horizAlign = "right";
	textLeaveTicketPrompt.text = "余票：";
	textLeaveTicketPrompt.left = textCountDownPrompt.left;
	textLeaveTicketPrompt.top = textCountDownPrompt.top + textCountDownPrompt.height;
	textLeaveTicketPrompt.width = 85;
	textLeaveTicketPrompt.height = textCountDownPrompt.height;
	
	textLeaveTicket.color = "#0";
	textLeaveTicket.fontSize = 10;
	textLeaveTicket.fontWeight = 800;
	textLeaveTicket.fontFamily = "微软雅黑";
	textLeaveTicket.left = textLeaveTicketPrompt.left + textLeaveTicketPrompt.width;
	textLeaveTicket.top = textLeaveTicketPrompt.top;
	textLeaveTicket.width = 38;
	textLeaveTicket.height = textLeaveTicketPrompt.height;
	
	imgBaiTuOrTip.image = "Room_imgMarkGetTicket.png";
	imgBaiTuOrTip.width = 86;
	imgBaiTuOrTip.height = 63;
	imgBaiTuOrTip.left = Window.width - 2 - imgBaiTuOrTip.width;
	imgBaiTuOrTip.top = Window.height - 2 - imgBaiTuOrTip.height;
}

function Show6()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textCountDownPrompt.visible = true;
	textLeaveTicketPrompt.visible = true;
	imgBaiTuOrTip.visible = true;
	
	textUpCon1.color = "#2A2AFF";
	textUpCon1.fontSize = 14;
	textUpCon1.fontWeight = 800;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 10;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 10;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.horizAlign = "left";
	textCountDownPrompt.left = 5;
	textCountDownPrompt.top = textUpCon1.top + textUpCon1.height + 10;
	textCountDownPrompt.width = 180;
	textCountDownPrompt.height = 21;
	
	textLeaveTicketPrompt.color = "#0";
	textLeaveTicketPrompt.fontSize = 10;
	textLeaveTicketPrompt.fontWeight = 800;
	textLeaveTicketPrompt.fontFamily = "微软雅黑";
	textLeaveTicketPrompt.horizAlign = "left";
	textLeaveTicketPrompt.left = textCountDownPrompt.left;
	textLeaveTicketPrompt.top = textCountDownPrompt.top + textCountDownPrompt.height;
	textLeaveTicketPrompt.width = textCountDownPrompt.width;
	textLeaveTicketPrompt.height = textCountDownPrompt.height;
	
	imgBaiTuOrTip.image = "Room_imgMarkNoTicket.png";
	imgBaiTuOrTip.width = 66;
	imgBaiTuOrTip.height = 70;
	imgBaiTuOrTip.left = Window.width - 2 - imgBaiTuOrTip.width;
	imgBaiTuOrTip.top = Window.height - 2 - imgBaiTuOrTip.height;
}

function Show7()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textCountDownPrompt.visible = true;
	imgBaiTuOrTip.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 11;
	textUpCon1.fontWeight = 800;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 10;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 10;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.left = 5;
	textCountDownPrompt.top = textUpCon1.top + textUpCon1.height + 23;
	textCountDownPrompt.width = 180;
	textCountDownPrompt.height = 21;
	
	imgBaiTuOrTip.image = "Room_imgMarkOnShow.png";
	imgBaiTuOrTip.width = 69;
	imgBaiTuOrTip.height = 74;
	imgBaiTuOrTip.left = Window.width - 2 - imgBaiTuOrTip.width;
	imgBaiTuOrTip.top = Window.height - 2 - imgBaiTuOrTip.height;
}

function Show8()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textCountDownPrompt.visible = true;
	imgBaiTuOrTip.visible = true;
	
	textUpCon1.color = "#2A2AFF";
	textUpCon1.fontSize = 11;
	textUpCon1.fontWeight = 800;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 9;
	textUpCon2.fontWeight = 500;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.left =  textUpCon1.left;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 10;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.left = 5;
	textCountDownPrompt.top = textUpCon2.top + textUpCon2.height + 13;
	textCountDownPrompt.width = 180;
	textCountDownPrompt.height = 21;
	
	imgBaiTuOrTip.image = "Room_imgMarkGetTicket.png";
	imgBaiTuOrTip.width = 86;
	imgBaiTuOrTip.height = 63;
	imgBaiTuOrTip.left = Window.width - 2 - imgBaiTuOrTip.width;
	imgBaiTuOrTip.top = Window.height - 2 - imgBaiTuOrTip.height;
}

function Show9()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textCountDownPrompt.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 11;
	textUpCon1.fontWeight = 800;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 10;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 10;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.left = 5;
	textCountDownPrompt.top = textUpCon1.top + textUpCon1.height + 23;
	textCountDownPrompt.width = Window.width - 10;
	textCountDownPrompt.height = 21;
}

function Show10()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	imgBaiTuOrTip.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 9;
	textUpCon1.fontWeight = 800;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 9;
	textUpCon2.fontWeight = 800;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.left =  textUpCon1.left;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;

	imgBaiTuOrTip.image = "Room_imgMarkImgTip2.png";
	imgBaiTuOrTip.width = 112;
	imgBaiTuOrTip.height = 26;
	imgBaiTuOrTip.left = (Window.width - imgBaiTuOrTip.width)/2;
	imgBaiTuOrTip.top = Window.height - 10 - imgBaiTuOrTip.height;
}

function Show11()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	imgBaiTuOrTip.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 9;
	textUpCon1.fontWeight = 800;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 9;
	textUpCon2.fontWeight = 800;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.left =  textUpCon1.left;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;

	imgBaiTuOrTip.image = "Room_imgMarkImgTip1.png";
	imgBaiTuOrTip.width = 240;
	imgBaiTuOrTip.height = 41;
	imgBaiTuOrTip.left = (Window.width - imgBaiTuOrTip.width)/2;
	imgBaiTuOrTip.top = Window.height - 8 - imgBaiTuOrTip.height;
}

function Show12()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textUpCon3.visible = true;
	textSuperTicket.visible = true;
	checkUseOne.visible = true;
	textMark1.visible = true;
	textMark2.visible = true;
	radioGoodMark.visible = true;
	radioBadMark.visible = true;
	imgGoodMark.visible = true;
	textGoodMark.visible = true;
	textVS.visible = true;
	imgBadMark.visible = true;
	textBadMark.visible = true;
	btnOKIn12.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 10;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.fontWeight = 800;
	textUpCon1.horizAlign = "right";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = ( imgSongMarkContentBk.width - 2 )/2;
	textUpCon1.height = 21;
	
	textSuperTicket.labelHorizAlign = "left";
	textSuperTicket.left = textUpCon1.left + textUpCon1.width;
	textSuperTicket.top = textUpCon1.top;
	textSuperTicket.width = textUpCon1.width;
	textSuperTicket.height = textUpCon1.height;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 10;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.fontWeight = 800;
	textUpCon2.horizAlign = "right";
	textUpCon2.text = "使用一张";
	textUpCon2.left =  imgSongMarkContentBk.left + 1;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = ( imgSongMarkContentBk.width - 2 )/2 - 25;
	textUpCon2.height = 21;
	
	checkUseOne.left = textUpCon2.left + textUpCon2.width;
	checkUseOne.top = textUpCon2.top;
	
	textUpCon3.color = "#66686A";
	textUpCon3.fontSize = 9;
	textUpCon3.fontFamily = "微软雅黑";
	textUpCon3.fontWeight = 500;
	textUpCon3.horizAlign = "left";
	textUpCon3.left = checkUseOne.left + checkUseOne.width;
	textUpCon3.top = checkUseOne.top;
	textUpCon3.width =  ( imgSongMarkContentBk.width - 2 )/2 - 25;
	textUpCon3.height = 21;
	
	textMark1.color = "#0";
	textMark1.fontSize = 10;
	textMark1.fontWeight = 800;
	textMark1.fontFamily = "微软雅黑";
	textMark1.text = "我的评价：";
	textMark1.left = 2;
	textMark1.top = textUpCon2.top + textUpCon2.height + 2;
	textMark1.width = 72;
	textMark1.height = 21;
	
	radioGoodMark.left = textMark1.left + textMark1.width;
	radioGoodMark.top = textMark1.top + 1;
	radioGoodMark.width = 50;
	
	radioBadMark.left = radioGoodMark.left + radioGoodMark.width;
	radioBadMark.top = radioGoodMark.top;
	radioBadMark.width = radioGoodMark.width;
	
	textMark2.color = "#0";
	textMark2.fontSize = 10;
	textMark2.fontWeight = 800;
	textMark2.fontFamily = "微软雅黑";
	textMark2.text = "大众评委：";
	textMark2.left = textMark1.left;
	textMark2.top = textMark1.top + textMark1.height;
	textMark2.width = textMark1.width;
	textMark2.height = textMark1.height;
	
	imgGoodMark.left = textMark2.left + textMark2.width;
	imgGoodMark.top = textMark2.top + 2;
	imgGoodMark.width = 38;
	imgGoodMark.height = 17;
	
	textGoodMark.color = "#ffffff";
	textGoodMark.fontSize = 11;
	textGoodMark.fontWeight = 800;
	textGoodMark.fontFamily = "微软雅黑";
	textGoodMark.left = imgGoodMark.left + 1;
	textGoodMark.top = imgGoodMark.top + 1;
	textGoodMark.width = imgGoodMark.width - 2;
	textGoodMark.height = imgGoodMark.height - 2;
	
	textVS.color = "#696868";
	textVS.fontSize = 11;
	textVS.fontWeight = 800;
	textVS.fontFamily = "微软雅黑";
	textVS.left = imgGoodMark.left + imgGoodMark.width + 1;
	textVS.top = textGoodMark.top - 2;
	textVS.width = textVS.textWidth;
	textVS.height = textVS.textHeight;
	
	imgBadMark.left = textVS.left + textVS.width + 1;
	imgBadMark.top = imgGoodMark.top;
	imgBadMark.width = 38;
	imgBadMark.height = 17;
	
	textBadMark.color = "#ffffff";
	textBadMark.fontSize = 11;
	textBadMark.fontWeight = 800;
	textBadMark.fontFamily = "微软雅黑";
	textBadMark.left = imgBadMark.left + 1;
	textBadMark.top = imgBadMark.top + 1;
	textBadMark.width = imgBadMark.width - 2;
	textBadMark.height = imgBadMark.height - 2;
		
	btnOKIn12.width = 71;
	btnOKIn12.height = 40;
	btnOKIn12.left = Window.width - 2 - btnOKIn12.width;
	btnOKIn12.top = Window.height - 2 - btnOKIn12.height;
}

function Show13()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textMark1.visible = true;
	textMark2.visible = true;
	textMark3.visible = true;
	radioGoodMark.visible = true;
	radioBadMark.visible = true;
	btnOKIn13.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 10;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.fontWeight = 800;
	//textUpCon1.horizAlign = "right";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2 ;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 9;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.fontWeight = 500;
	textUpCon2.left =  textUpCon1.left ;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;
	
	textMark1.color = "#0";
	textMark1.fontSize = 10;
	textMark1.fontWeight = 800;
	textMark1.fontFamily = "微软雅黑";
	textMark1.text = "点歌者：";
	textMark1.horizAlign = "right";
	textMark1.left = 1;
	textMark1.top = textUpCon2.top + textUpCon2.height + 2;
	textMark1.width = 68;
	textMark1.height = 21;
	
	textMark2.color = "#0";
	textMark2.fontSize = 10;
	textMark2.fontWeight = 800;
	textMark2.fontFamily = "微软雅黑";
	textMark2.horizAlign = "left";
	textMark2.left = textMark1.left + textMark1.width;
	textMark2.top = textMark1.top;
	textMark2.width = 120;
	textMark2.height = textMark1.height;
	
	textMark3.color = "#0";
	textMark3.fontSize = 10;
	textMark3.fontWeight = 800;
	textMark3.fontFamily = "微软雅黑";
	textMark3.text = "我的评价：";
	textMark3.horizAlign = "right";
	textMark3.left = textMark1.left;
	textMark3.top = textMark1.top + textMark1.height;
	textMark3.width = textMark1.width;
	textMark3.height = textMark1.height;
	
	radioGoodMark.left = textMark3.left + textMark3.width;
	radioGoodMark.top = textMark3.top + 1;
	radioGoodMark.width = 50;
	
	radioBadMark.left = radioGoodMark.left + radioGoodMark.width;
	radioBadMark.top = radioGoodMark.top;
	radioBadMark.width = radioGoodMark.width;
		
	btnOKIn13.width = 71;
	btnOKIn13.height = 40;
	btnOKIn13.left = Window.width - 2 - btnOKIn13.width;
	btnOKIn13.top = Window.height - 2 - btnOKIn13.height;
}

function Show14()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textMark1.visible = true;
	textMark2.visible = true;
	textMark3.visible = true;
	imgGoodMark.visible = true;
	textGoodMark.visible = true;
	textVS.visible = true;
	imgBadMark.visible = true;
	textBadMark.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 11;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.fontWeight = 800;
	//textUpCon1.horizAlign = "right";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2 ;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 11;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.fontWeight = 800;
	textUpCon2.left =  textUpCon1.left ;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;
	
	textMark1.color = "#0";
	textMark1.fontSize = 10;
	textMark1.fontWeight = 800;
	textMark1.fontFamily = "微软雅黑";
	textMark1.text = "点歌者：";
	textMark1.horizAlign = "right";
	textMark1.left = 1;
	textMark1.top = textUpCon2.top + textUpCon2.height + 2;
	textMark1.width = 68;
	textMark1.height = 21;
	
	textMark2.color = "#0";
	textMark2.fontSize = 10;
	textMark2.fontWeight = 800;
	textMark2.fontFamily = "微软雅黑";
	textMark2.horizAlign = "left";
	textMark2.left = textMark1.left + textMark1.width;
	textMark2.top = textMark1.top;
	textMark2.width = 120;
	textMark2.height = textMark1.height;
	
	textMark3.color = "#0";
	textMark3.fontSize = 10;
	textMark3.fontWeight = 800;
	textMark3.fontFamily = "微软雅黑";
	textMark3.text = "大众评委：";
	textMark3.horizAlign = "right";
	textMark3.left = textMark1.left;
	textMark3.top = textMark1.top + textMark1.height;
	textMark3.width = textMark1.width;
	textMark3.height = textMark1.height;
	
	imgGoodMark.left = textMark3.left + textMark3.width;
	imgGoodMark.top = textMark3.top + 2;
	imgGoodMark.width = 38;
	imgGoodMark.height = 17;
	
	textGoodMark.color = "#ffffff";
	textGoodMark.fontSize = 11;
	textGoodMark.fontWeight = 800;
	textGoodMark.fontFamily = "微软雅黑";
	textGoodMark.left = imgGoodMark.left + 1;
	textGoodMark.top = imgGoodMark.top + 1;
	textGoodMark.width = imgGoodMark.width - 2;
	textGoodMark.height = imgGoodMark.height - 2;
	
	textVS.color = "#696868";
	textVS.fontSize = 11;
	textVS.fontWeight = 800;
	textVS.fontFamily = "微软雅黑";
	textVS.left = imgGoodMark.left + imgGoodMark.width + 1;
	textVS.top = textGoodMark.top - 2;
	textVS.width = textVS.textWidth;
	textVS.height = textVS.textHeight;
	
	imgBadMark.left = textVS.left + textVS.width + 1;
	imgBadMark.top = imgGoodMark.top;
	imgBadMark.width = 38;
	imgBadMark.height = 17;
	
	textBadMark.color = "#ffffff";
	textBadMark.fontSize = 11;
	textBadMark.fontWeight = 800;
	textBadMark.fontFamily = "微软雅黑";
	textBadMark.left = imgBadMark.left + 1;
	textBadMark.top = imgBadMark.top + 1;
	textBadMark.width = imgBadMark.width - 2;
	textBadMark.height = imgBadMark.height - 2;
}

function Show15()
{
 //与Show14()样式一样
	Show14();
}

function Show16()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textMark1.visible = true;
	textMark2.visible = true;
	textMark3.visible = true;
	imgGoodMark.visible = true;
	textGoodMark.visible = true;
	textVS.visible = true;
	imgBadMark.visible = true;
	textBadMark.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 11;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.fontWeight = 800;
	//textUpCon1.horizAlign = "right";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 13;
	textUpCon1.width = imgSongMarkContentBk.width - 2 ;
	textUpCon1.height = 21;
	
	textMark1.color = "#0";
	textMark1.fontSize = 10;
	textMark1.fontWeight = 800;
	textMark1.fontFamily = "微软雅黑";
	textMark1.text = "点歌者：";
	textMark1.horizAlign = "right";
	textMark1.left = 1;
	textMark1.top = textUpCon1.top + textUpCon1.height + 11;
	textMark1.width = 68;
	textMark1.height = 21;
	
	textMark2.color = "#0";
	textMark2.fontSize = 10;
	textMark2.fontWeight = 800;
	textMark2.fontFamily = "微软雅黑";
	textMark2.horizAlign = "left";
	textMark2.left = textMark1.left + textMark1.width;
	textMark2.top = textMark1.top;
	textMark2.width = 120;
	textMark2.height = textMark1.height;
	
	textMark3.color = "#0";
	textMark3.fontSize = 10;
	textMark3.fontWeight = 800;
	textMark3.fontFamily = "微软雅黑";
	textMark3.text = "大众评委：";
	textMark3.horizAlign = "right";
	textMark3.left = textMark1.left;
	textMark3.top = textMark1.top + textMark1.height;
	textMark3.width = textMark1.width;
	textMark3.height = textMark1.height;
	
	imgGoodMark.left = textMark3.left + textMark3.width;
	imgGoodMark.top = textMark3.top + 2;
	imgGoodMark.width = 38;
	imgGoodMark.height = 17;
	
	textGoodMark.color = "#ffffff";
	textGoodMark.fontSize = 11;
	textGoodMark.fontWeight = 800;
	textGoodMark.fontFamily = "微软雅黑";
	textGoodMark.left = imgGoodMark.left + 1;
	textGoodMark.top = imgGoodMark.top + 1;
	textGoodMark.width = imgGoodMark.width - 2;
	textGoodMark.height = imgGoodMark.height - 2;
	
	textVS.color = "#696868";
	textVS.fontSize = 11;
	textVS.fontWeight = 800;
	textVS.fontFamily = "微软雅黑";
	textVS.left = imgGoodMark.left + imgGoodMark.width + 1;
	textVS.top = textGoodMark.top - 2;
	textVS.width = textVS.textWidth;
	textVS.height = textVS.textHeight;
	
	imgBadMark.left = textVS.left + textVS.width + 1;
	imgBadMark.top = imgGoodMark.top;
	imgBadMark.width = 38;
	imgBadMark.height = 17;
	
	textBadMark.color = "#ffffff";
	textBadMark.fontSize = 11;
	textBadMark.fontWeight = 800;
	textBadMark.fontFamily = "微软雅黑";
	textBadMark.left = imgBadMark.left + 1;
	textBadMark.top = imgBadMark.top + 1;
	textBadMark.width = imgBadMark.width - 2;
	textBadMark.height = imgBadMark.height - 2;
}

function Show17()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textMark1.visible = true;
	textMark2.visible = true;
	textMark3.visible = true;
	imgGoodMark.visible = true;
	textGoodMark.visible = true;
	textVS.visible = true;
	imgBadMark.visible = true;
	textBadMark.visible = true;
	imgGiveupMark.visible = true;
	textGiveupMark.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 12;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.fontWeight = 800;
	//textUpCon1.horizAlign = "right";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2 ;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 9;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.fontWeight = 500;
	textUpCon2.left =  textUpCon1.left ;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;
	
	textMark1.color = "#0";
	textMark1.fontSize = 10;
	textMark1.fontWeight = 800;
	textMark1.fontFamily = "微软雅黑";
	textMark1.text = "点歌者：";
	textMark1.horizAlign = "right";
	textMark1.left = 1;
	textMark1.top = textUpCon2.top + textUpCon2.height + 2;
	textMark1.width = 68;
	textMark1.height = 21;
	
	textMark2.color = "#0";
	textMark2.fontSize = 10;
	textMark2.fontWeight = 800;
	textMark2.fontFamily = "微软雅黑";
	textMark2.horizAlign = "left";
	textMark2.left = textMark1.left + textMark1.width;
	textMark2.top = textMark1.top;
	textMark2.width = 120;
	textMark2.height = textMark1.height;
	
	textMark3.color = "#0";
	textMark3.fontSize = 10;
	textMark3.fontWeight = 800;
	textMark3.fontFamily = "微软雅黑";
	textMark3.text = "大众评委：";
	textMark3.horizAlign = "right";
	textMark3.left = textMark1.left;
	textMark3.top = textMark1.top + textMark1.height;
	textMark3.width = textMark1.width;
	textMark3.height = textMark1.height;
	
	imgGoodMark.left = textMark3.left + textMark3.width;
	imgGoodMark.top = textMark3.top + 2;
	imgGoodMark.width = 38;
	imgGoodMark.height = 17;
	
	textGoodMark.color = "#ffffff";
	textGoodMark.fontSize = 11;
	textGoodMark.fontWeight = 800;
	textGoodMark.fontFamily = "微软雅黑";
	textGoodMark.left = imgGoodMark.left + 1;
	textGoodMark.top = imgGoodMark.top + 1;
	textGoodMark.width = imgGoodMark.width - 2;
	textGoodMark.height = imgGoodMark.height - 2;
	
	textVS.color = "#696868";
	textVS.fontSize = 11;
	textVS.fontWeight = 800;
	textVS.fontFamily = "微软雅黑";
	textVS.left = imgGoodMark.left + imgGoodMark.width + 1;
	textVS.top = textGoodMark.top - 2;
	textVS.width = textVS.textWidth;
	textVS.height = textVS.textHeight;
	
	imgBadMark.left = textVS.left + textVS.width + 1;
	imgBadMark.top = imgGoodMark.top;
	imgBadMark.width = 38;
	imgBadMark.height = 17;
	
	textBadMark.color = "#ffffff";
	textBadMark.fontSize = 11;
	textBadMark.fontWeight = 800;
	textBadMark.fontFamily = "微软雅黑";
	textBadMark.left = imgBadMark.left + 1;
	textBadMark.top = imgBadMark.top + 1;
	textBadMark.width = imgBadMark.width - 2;
	textBadMark.height = imgBadMark.height - 2;
	
	imgGiveupMark.left = imgBadMark.left + imgBadMark.width + 10;
	imgGiveupMark.top = imgBadMark.top;
	imgGiveupMark.width = 52;
	imgGiveupMark.height = 17;
	
	textGiveupMark.color = "#ffffff";
	textGiveupMark.fontSize = 11;
	textGiveupMark.fontWeight = 800;
	textGiveupMark.fontFamily = "微软雅黑";
	textGiveupMark.left = imgGiveupMark.left + 1;
	textGiveupMark.top = imgGiveupMark.top + 1;
	textGiveupMark.width = imgGiveupMark.width - 2;
	textGiveupMark.height = imgGiveupMark.height - 2;
}

function Show18()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	imgBaiTuOrTip.visible = true;
	btnOrderSong.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 12;
	textUpCon1.fontWeight = 800;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 12;
	textUpCon2.fontWeight = 800;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.left =  textUpCon1.left;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;

	imgBaiTuOrTip.image = "Room_imgMarkNoOrderSong.png";
	imgBaiTuOrTip.width = 71;
	imgBaiTuOrTip.height = 82;
	imgBaiTuOrTip.left = 20;
	imgBaiTuOrTip.top = Window.height - 1 - imgBaiTuOrTip.height;
	
	btnOrderSong.left = Window.width - 30 - btnOrderSong.width;
	btnOrderSong.top = Window.height - 10 - btnOrderSong.height;
}

function Show19()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textCountDownPrompt.visible = true;
	imgBaiTuOrTip.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 12;
	textUpCon1.fontWeight = 800;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = imgSongMarkContentBk.width - 2;
	textUpCon1.height = 21;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 12;
	textUpCon2.fontWeight = 800;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.left =  textUpCon1.left;
	textUpCon2.top = textUpCon1.top + textUpCon1.height;
	textUpCon2.width = textUpCon1.width;
	textUpCon2.height = textUpCon1.height;
	
	imgBaiTuOrTip.image = "Room_imgMarkNoActor.png";
	imgBaiTuOrTip.width = 52;
	imgBaiTuOrTip.height = 87;
	imgBaiTuOrTip.left = 8;
	imgBaiTuOrTip.top = Window.height - 1 - imgBaiTuOrTip.height;
	
	textCountDownPrompt.color = "#0";
	textCountDownPrompt.fontSize = 10;
	textCountDownPrompt.fontWeight = 800;
	textCountDownPrompt.fontFamily = "微软雅黑";
	textCountDownPrompt.left = imgBaiTuOrTip.left + imgBaiTuOrTip.width;
	textCountDownPrompt.top = textUpCon2.top + textUpCon2.height + 13;
	textCountDownPrompt.width = Window.width - 1 - textCountDownPrompt.left;
	textCountDownPrompt.height = 21;
}

function Show20()
{
	SetUnVisible();
	textUpCon1.visible = true;
	textUpCon2.visible = true;
	textUpCon3.visible = true;
	textSuperTicket.visible = true;
	textMark1.visible = true;
	textMark2.visible = true;
	radioGoodMark.visible = true;
	radioBadMark.visible = true;
	imgGoodMark.visible = true;
	textGoodMark.visible = true;
	textVS.visible = true;
	imgBadMark.visible = true;
	textBadMark.visible = true;
	btnOKIn20.visible = true;
	
	textUpCon1.color = "#66686A";
	textUpCon1.fontSize = 10;
	textUpCon1.fontFamily = "微软雅黑";
	textUpCon1.fontWeight = 800;
	textUpCon1.horizAlign = "right";
	textUpCon1.text = "您今天的"
	textUpCon1.left =  imgSongMarkContentBk.left + 1;
	textUpCon1.top = imgSongMarkContentBk.top + 2;
	textUpCon1.width = ( imgSongMarkContentBk.width - 2 )/3;
	textUpCon1.height = 21;
	
	textSuperTicket.labelHorizAlign = "left";
	textSuperTicket.left = textUpCon1.left + textUpCon1.width;
	textSuperTicket.top = textUpCon1.top;
	textSuperTicket.width = 70;
	textSuperTicket.height = textUpCon1.height;
	
	textUpCon2.color = "#66686A";
	textUpCon2.fontSize = 10;
	textUpCon2.fontFamily = "微软雅黑";
	textUpCon2.fontWeight = 800;
	textUpCon2.horizAlign = "left";
	textUpCon2.text = "用光啦";
	textUpCon2.left =  textSuperTicket.left + textSuperTicket.width;
	textUpCon2.top = textSuperTicket.top;
	textUpCon2.width = textSuperTicket.width;
	textUpCon2.height = 21;
	
	textUpCon3.color = "#66686A";
	textUpCon3.fontSize = 9;
	textUpCon3.fontFamily = "微软雅黑";
	textUpCon3.fontWeight = 500;
	//textUpCon3.horizAlign = "left";
	textUpCon3.left = 2;
	textUpCon3.top = textUpCon1.top + textUpCon1.height;
	textUpCon3.width =  Window.width - 4;
	textUpCon3.height = 21;
	
	textMark1.color = "#0";
	textMark1.fontSize = 10;
	textMark1.fontWeight = 800;
	textMark1.fontFamily = "微软雅黑";
	textMark1.text = "我的评价：";
	textMark1.left = 2;
	textMark1.top = textUpCon3.top + textUpCon3.height + 2;
	textMark1.width = 72;
	textMark1.height = 21;
	
	radioGoodMark.left = textMark1.left + textMark1.width;
	radioGoodMark.top = textMark1.top + 1;
	radioGoodMark.width = 50;
	
	radioBadMark.left = radioGoodMark.left + radioGoodMark.width;
	radioBadMark.top = radioGoodMark.top;
	radioBadMark.width = radioGoodMark.width;
	
	textMark2.color = "#0";
	textMark2.fontSize = 10;
	textMark2.fontWeight = 800;
	textMark2.fontFamily = "微软雅黑";
	textMark2.text = "大众评委：";
	textMark2.left = textMark1.left;
	textMark2.top = textMark1.top + textMark1.height;
	textMark2.width = textMark1.width;
	textMark2.height = textMark1.height;
	
	imgGoodMark.left = textMark2.left + textMark2.width;
	imgGoodMark.top = textMark2.top + 2;
	imgGoodMark.width = 38;
	imgGoodMark.height = 17;
	
	textGoodMark.color = "#ffffff";
	textGoodMark.fontSize = 11;
	textGoodMark.fontWeight = 800;
	textGoodMark.fontFamily = "微软雅黑";
	textGoodMark.left = imgGoodMark.left + 1;
	textGoodMark.top = imgGoodMark.top + 1;
	textGoodMark.width = imgGoodMark.width - 2;
	textGoodMark.height = imgGoodMark.height - 2;
	
	textVS.color = "#696868";
	textVS.fontSize = 11;
	textVS.fontWeight = 800;
	textVS.fontFamily = "微软雅黑";
	textVS.left = imgGoodMark.left + imgGoodMark.width + 1;
	textVS.top = textGoodMark.top - 2;
	textVS.width = textVS.textWidth;
	textVS.height = textVS.textHeight;
	
	imgBadMark.left = textVS.left + textVS.width + 1;
	imgBadMark.top = imgGoodMark.top;
	imgBadMark.width = 38;
	imgBadMark.height = 17;
	
	textBadMark.color = "#ffffff";
	textBadMark.fontSize = 11;
	textBadMark.fontWeight = 800;
	textBadMark.fontFamily = "微软雅黑";
	textBadMark.left = imgBadMark.left + 1;
	textBadMark.top = imgBadMark.top + 1;
	textBadMark.width = imgBadMark.width - 2;
	textBadMark.height = imgBadMark.height - 2;
		
	btnOKIn20.width = 71;
	btnOKIn20.height = 40;
	btnOKIn20.left = Window.width - 2 - btnOKIn20.width;
	btnOKIn20.top = Window.height - 2 - btnOKIn20.height;
}

function OnNotify(code, code1)
{
  if(code == NOFITY_SKIN_SHOW_MARK)
  {
	 switch(code1)
	 {
		case 1:	Show1(); OnSize(Window.width, Window.height);
        break;
		case 2:	Show2(); OnSize(Window.width, Window.height);
        break;
		case 3: Show3(); OnSize(Window.width, Window.height);
        break;
		case 4:	Show4(); OnSize(Window.width, Window.height);
        break;
		case 5:	Show5(); OnSize(Window.width, Window.height);
        break;
		case 6:	Show6(); OnSize(Window.width, Window.height);
        break;
		case 7:	Show7(); OnSize(Window.width, Window.height);
        break;
		case 8:	Show8(); OnSize(Window.width, Window.height);
        break;
		case 9:	Show9(); OnSize(Window.width, Window.height);
        break;
		case 10:Show10(); OnSize(Window.width, Window.height);
        break;
		case 11:Show11(); OnSize(Window.width, Window.height);
        break;
		case 12:Show12(); OnSize(Window.width, Window.height);
        break;
		case 13:Show13(); OnSize(Window.width, Window.height);
        break;
		case 14:Show14(); OnSize(Window.width, Window.height);
        break;
		case 15:Show15(); OnSize(Window.width, Window.height);
        break;
		case 16:Show16(); OnSize(Window.width, Window.height);
        break;
		case 17:Show17(); OnSize(Window.width, Window.height);
        break;
		case 18:Show18(); OnSize(Window.width, Window.height);
        break;
		case 19:Show19(); OnSize(Window.width, Window.height);
		break;
		case 20:Show20(); OnSize(Window.width, Window.height);
		break;
        default:break;
	 }
  }
}
