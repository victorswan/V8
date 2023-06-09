
var SKIN_ON_CLICK_CLOSE = 0;
var SKIN_ON_CLICK_BTN_UPLOAD_LOCAL = 1;
var SKIN_ON_CLICK_BTN_CONFIRM = 2;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", OnClickSysBtnClose);
btnUploadLocal.AttachEvent("OnClick", OnClickBtnUploadLocal);
btnConfirm.AttachEvent("OnClick", OnClickBtnConfirm);
btnCancel.AttachEvent("OnClick", OnClickSysBtnClose);

function OnClickSysBtnClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function OnClickBtnUploadLocal()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_UPLOAD_LOCAL, 0);
}

function OnClickBtnConfirm()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CONFIRM, 0);
}

///////////////////////////////////////////////////////
function OnInit()
{
	textTitle.text = "头像设置";
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

    imgHeadBk.width = 108;
	imgHeadBk.height = 108;
	imgHeadBk.left = (cx - imgHeadBk.width)/2;
	imgHeadBk.top = 60;
	
	imgHead.width = 100;
	imgHead.height = 100;
	imgHead.left = imgHeadBk.left + (imgHeadBk.width - imgHead.width)/2;
	imgHead.top = imgHeadBk.top + (imgHeadBk.height - imgHead.height)/2;
	
	textPrompt.width = textPrompt.textWidth;
	textPrompt.height = textPrompt.textHeight;
	textPrompt.left = imgHeadBk.left;
	textPrompt.top = imgHeadBk.top + imgHeadBk.height + 10;
	
	btnUploadLocal.width = 134;
	btnUploadLocal.height = 42;
	btnUploadLocal.left = imgHeadBk.left + (imgHeadBk.width - btnUploadLocal.width)/2;
	btnUploadLocal.top = textPrompt.top + textPrompt.height + 5;
	
	
	btnCancel.visible = true;
	//btnCancel.width = 79;
	//btnCancel.height = 35;
	btnCancel.left = cx - 15 - btnCancel.width;
	btnCancel.top = cy - 45;
	
	btnConfirm.visible = true;
	//btnConfirm.width = btnCancel.width;
	//btnConfirm.height = btnCancel.height;
	btnConfirm.left = btnCancel.left - 15 - btnConfirm.width;
	btnConfirm.top = btnCancel.top;
	
}

function OnNotify(code, code1)
{
   switch(code)
    {
    }
}



