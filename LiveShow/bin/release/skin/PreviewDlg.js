
var SKIN_ON_CLICK_CLOSE = 1;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", btnCloseOnClick);



function btnCloseOnClick()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}


function OnInit()
{
	textTitle.text = "效果";
    textTitle.visible = false;
    // textTitle.fontWeight = 500;
	// textTitle.fontSize = 11;
    // textTitle.normalColor = 0xffffff;
    // textTitle.colorTransform = true;
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    // textTitle.width = textTitle.textWidth;
	// textTitle.height = textTitle.textHeight;
	// textTitle.left = imgTitleIcon.left + imgTitleIcon.width + 10;
	// textTitle.top = 0 + (32 - textTitle.height)/2 ;	
	
	imgTopBk.left = 2;
	imgTopBk.top = 2;
	imgTopBk.width = cx - 4;
	imgTopBk.height = 32;

	imgMidBk.left = 2;
	imgMidBk.top = imgTopBk.top + imgTopBk.height;
	imgMidBk.width = cx - 4;
	imgMidBk.height = cy - 2 - imgMidBk.top;
	
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	textTheTitle.left = 10;
	textTheTitle.top = 8;
	
	itemHtmlPreview.visible = true;
	itemHtmlPreview.left = imgMidBk.left;
	itemHtmlPreview.top = imgMidBk.top;
	itemHtmlPreview.width = imgMidBk.width;
	itemHtmlPreview.height = imgMidBk.height;

}

function OnNotify(code, code1)
{
	
}
