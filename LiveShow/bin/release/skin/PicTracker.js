var SKIN_ON_CLICK_CLOSE  = 0;
var SKIN_ON_CLICK_ZOOMIN  = 1;
var SKIN_ON_CLICK_ZOOMOUT  = 2;
var SKIN_ON_CLICK_FULLSCREEN  = 3;
var SKIN_ON_CLICK_ORIGINAL  = 4;
var SKIN_ON_CLICK_BROWSER = 5;
var SKIN_ON_CLICK_OK = 6;
var SKIN_ON_CLICK_CANCEL = 7;

Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", NotifyCloseOnClick); 
btnZoomIn.AttachEvent("OnClick",OnClickZoomIn);
btnZoomOut.AttachEvent("OnClick",OnClickZoomOut);
btnFullScreen.AttachEvent("OnClick",OnClickFullScreen);
btnOriginal.AttachEvent("OnClick",OnClickOriginal);
op_img_browser.AttachEvent("OnClick",OnClickBrowser);
btnOk.AttachEvent("OnClick",OnClickOK);
btnCancel.AttachEvent("OnClick",OnClickCancel);

function OnClickCancel()
{ 
	Window.PostSkinMessage(SKIN_ON_CLICK_CANCEL, 0);
}

function OnClickOK()
{ 
	Window.PostSkinMessage(SKIN_ON_CLICK_OK, 0);
}

function OnClickBrowser()
{ 
	Window.PostSkinMessage(SKIN_ON_CLICK_BROWSER, 0);
}
function OnClickZoomIn()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_ZOOMIN, 0);
} 

function OnClickZoomOut()
{ 
	Window.PostSkinMessage(SKIN_ON_CLICK_ZOOMOUT, 0);
}

function OnClickFullScreen()
{ 
	Window.PostSkinMessage(SKIN_ON_CLICK_FULLSCREEN, 0);
}

function OnClickOriginal()
{ 
	Window.PostSkinMessage(SKIN_ON_CLICK_ORIGINAL, 0);
}
function NotifyCloseOnClick()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}


function OnInit()
{
	textTitle.text = "头像剪裁";
	textTitle.visible = false;
    // textTitle.fontWeight = 500;
	// textTitle.fontSize = 11;
    // textTitle.normalColor = 0xffffff;
    // textTitle.colorTransform = true;
	// OnSize(Window.width, Window.height);
}
function OnSize(cx, cy)
{
	Window.BeginPaint();
	
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

	TrackerCtrlBig.left = 11;
	TrackerCtrlBig.top = 64;
	TrackerCtrlBig.width = 373;
    TrackerCtrlBig.height = 247;
	
	btnZoomOut.left = 17;
	btnZoomOut.top = 321;
	
	SliderZoom.left = btnZoomOut.left + btnZoomOut.width;
	SliderZoom.height = 22;
	SliderZoom.width = 260;
	SliderZoom.top = btnZoomOut.top - 4;
	
	btnZoomIn.left = SliderZoom.left + SliderZoom.width;
	btnZoomIn.top = btnZoomOut.top; 
	
	btnFullScreen.left = 334;
	btnFullScreen.top = btnZoomOut.top;
	
	btnOriginal.left = 368;
	btnOriginal.top = btnFullScreen.top;
	
	textLeft.value = "您可以拖动线框，选中部分将为自定义头像。";
	textLeft.left = 12;
	textLeft.top = 32 + 11;
	textLeft.height = 18;
	
	textRight.value = "预览：";
	textRight.left = 412;
	textRight.top = textLeft.top;
	textRight.height = 18; 
	
	TrackerCtrlSmall2.left = 412;
	TrackerCtrlSmall2.top = 62;//op_img_browser.top + op_img_browser.height + 10;
	TrackerCtrlSmall2.width = 93;
	TrackerCtrlSmall2.height = 93;
	
	textSize2.width = textSize2.textWidth;
	textSize2.height = textSize2.textHeight;
	textSize2.left = TrackerCtrlSmall2.left + (TrackerCtrlSmall2.width - textSize2.width)/2;
	textSize2.top = TrackerCtrlSmall2.top + TrackerCtrlSmall2.height + 2;
	
	
	TrackerCtrlSmall.left = 405;
	TrackerCtrlSmall.top = 177;
	TrackerCtrlSmall.width = 108;
    TrackerCtrlSmall.height = 108;
	
	textSize.width = textSize.textWidth;
	textSize.height = textSize.textHeight;
	textSize.left = TrackerCtrlSmall.left + (TrackerCtrlSmall.width - textSize.width)/2;
	textSize.top = TrackerCtrlSmall.top + TrackerCtrlSmall.height + 2;
	
	op_img_browser.width = 134;
	op_img_browser.height = 42;
	op_img_browser.left = TrackerCtrlSmall.left + (TrackerCtrlSmall.width - op_img_browser.width)/2;
	op_img_browser.top = TrackerCtrlSmall.top + TrackerCtrlSmall.height + 25;
	
	
	btnCancel.visible = true;
	//btnCancel.width = 79;
	//btnCancel.height = 35;
	btnCancel.left = cx - 15 - btnCancel.width;
	btnCancel.top = cy - 39;
	
	btnOk.visible = true;
	//btnOk.width = btnCancel.width;
	//btnOk.height = btnCancel.height;
	btnOk.left = btnCancel.left - 15 - btnOk.width;
	btnOk.top = btnCancel.top;
	Window.EndPaint();
}
	
function OnNotify(code, code1)
{
	switch(code)
	{
		default:
		break;
	}
}