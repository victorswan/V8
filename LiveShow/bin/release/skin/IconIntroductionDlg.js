
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
	textTitle.text = "图标说明";

	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	ImgIconIntroduceTopBk.left = 2;
	ImgIconIntroduceTopBk.top = 2;
	ImgIconIntroduceTopBk.width = cx - 4;
	ImgIconIntroduceTopBk.height = 32;
	
	ImgIconIntroduceMidBk.left = 2;
	ImgIconIntroduceMidBk.top = ImgIconIntroduceTopBk.top + ImgIconIntroduceTopBk.height;
	ImgIconIntroduceMidBk.width = cx - 4;
	ImgIconIntroduceMidBk.height = cy - 2 - ImgIconIntroduceMidBk.top;

	textTheTitle.left = 10;
	textTheTitle.top = 8;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	itemHtmlIconIntroduce.visible = true;
	itemHtmlIconIntroduce.left = ImgIconIntroduceMidBk.left ;
	itemHtmlIconIntroduce.top = ImgIconIntroduceMidBk.top;
	itemHtmlIconIntroduce.width = ImgIconIntroduceMidBk.width ;
	itemHtmlIconIntroduce.height = cy - 2 - itemHtmlIconIntroduce.top;

}

function OnNotify(code, code1)
{
	
}
