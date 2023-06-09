
var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_TAB_STAMP = 2;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", btnCloseOnClick);
//tabStamp.AttachEvent("OnClick",tabEmotionOnClick);

btnStampRole.AttachEvent("OnClick", OnClickBtnStampRole);
btnStampPraise.AttachEvent("OnClick", OnClickBtnStampPraise);
btnStampSpoof.AttachEvent("OnClick", OnClickBtnStampSpoof);
btnStampImagination.AttachEvent("OnClick", OnClickBtnStampImagination);
btnStampNobility.AttachEvent("OnClick", OnClickBtnStampNobility);

function btnCloseOnClick()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

// function tabEmotionOnClick(iTab)
// {
    // Window.PostSkinMessage(SKIN_ON_CLICK_TAB_STAMP,iTab);
// }

function OnClickBtnStampRole()
{
	btnStampRole.checked = true;
	btnStampPraise.checked = false;
	btnStampSpoof.checked = false;
	btnStampImagination.checked = false;
	btnStampNobility.checked = false;
	
	btnStampRole.labelNormalColor = "#0";
	btnStampPraise.labelNormalColor = "#ffffff";
	btnStampSpoof.labelNormalColor = "#ffffff";
	btnStampImagination.labelNormalColor = "#ffffff";
	btnStampNobility.labelNormalColor = "#ffffff";

	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_STAMP,0);
}

function OnClickBtnStampPraise()
{
	btnStampRole.checked = false;
	btnStampPraise.checked = true;
	btnStampSpoof.checked = false;
	btnStampImagination.checked = false;
	btnStampNobility.checked = false;
	
	btnStampRole.labelNormalColor = "#ffffff";
	btnStampPraise.labelNormalColor = "#0";
	btnStampSpoof.labelNormalColor = "#ffffff";
	btnStampImagination.labelNormalColor = "#ffffff";
	btnStampNobility.labelNormalColor = "#ffffff";
	
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_STAMP,1);
}

function OnClickBtnStampSpoof()
{
	btnStampRole.checked = false;
	btnStampPraise.checked = false;
	btnStampSpoof.checked = true;
	btnStampImagination.checked = false;
	btnStampNobility.checked = false;
	
	btnStampRole.labelNormalColor = "#ffffff";
	btnStampPraise.labelNormalColor = "#ffffff";
	btnStampSpoof.labelNormalColor = "#0";
	btnStampImagination.labelNormalColor = "#ffffff";
	btnStampNobility.labelNormalColor = "#ffffff";

	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_STAMP,2);
}

function OnClickBtnStampImagination()
{
	btnStampRole.checked = false;
	btnStampPraise.checked = false;
	btnStampSpoof.checked = false;
	btnStampImagination.checked = true;
	btnStampNobility.checked = false;
	
	btnStampRole.labelNormalColor = "#ffffff";
	btnStampPraise.labelNormalColor = "#ffffff";
	btnStampSpoof.labelNormalColor = "#ffffff";
	btnStampImagination.labelNormalColor = "#0";
	btnStampNobility.labelNormalColor = "#ffffff";

	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_STAMP,3);
}

function OnClickBtnStampNobility()
{
	btnStampRole.checked = false;
	btnStampPraise.checked = false;
	btnStampSpoof.checked = false;
	btnStampImagination.checked = false;
	btnStampNobility.checked = true;
	
	btnStampRole.labelNormalColor = "#ffffff";
	btnStampPraise.labelNormalColor = "#ffffff";
	btnStampSpoof.labelNormalColor = "#ffffff";
	btnStampImagination.labelNormalColor = "#ffffff";
	btnStampNobility.labelNormalColor = "#0";
	
	Window.PostSkinMessage(SKIN_ON_CLICK_TAB_STAMP,4);
}

function OnInit()
{
	textTitle.text = "盖章";
    textTitle.visible = false;
	
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	imgTopBk.left = 2;
	imgTopBk.top = 2;
	imgTopBk.width = cx - 4;
	imgTopBk.height = 32;

	imgMidBk.left = 2;
	imgMidBk.top = imgTopBk.top + imgTopBk.height;
	imgMidBk.width = cx - 4;
	imgMidBk.height = cy - 2 - imgMidBk.top;

	textTheTitle.left = 10;
	textTheTitle.top = 8;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	btnStampRole.left = 2;
	btnStampRole.top = 34;
	btnStampRole.width = 56;
	btnStampRole.height = 24;
	
	btnStampPraise.left = btnStampRole.left + btnStampRole.width + 5;
	btnStampPraise.top = btnStampRole.top;
	btnStampPraise.width = btnStampRole.width;
	btnStampPraise.height = btnStampRole.height;
	
	btnStampSpoof.left = btnStampPraise.left + btnStampPraise.width + 5;
	btnStampSpoof.top = btnStampPraise.top;
	btnStampSpoof.width = btnStampPraise.width;
	btnStampSpoof.height = btnStampPraise.height;
	
	btnStampImagination.left = btnStampSpoof.left + btnStampSpoof.width + 5;
	btnStampImagination.top = btnStampSpoof.top;
	btnStampImagination.width = btnStampSpoof.width;
	btnStampImagination.height = btnStampSpoof.height;
	
	btnStampNobility.left = btnStampImagination.left + btnStampImagination.width + 5;
	btnStampNobility.top = btnStampImagination.top;
	btnStampNobility.width = btnStampImagination.width;
	btnStampNobility.height = btnStampImagination.height;
	
	itemListStamp.visible = true;
	itemListStamp.left =  2;
	itemListStamp.top = btnStampRole.top + btnStampRole.height;
	itemListStamp.width = cx - 4;
	itemListStamp.height = cy - 4 - itemListStamp.top;
	
	
}

function OnNotify(code, code1)
{
	switch(code)
	{
	 
     default:break;
	}
}
