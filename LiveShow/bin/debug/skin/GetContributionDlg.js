var cx;
var cy;

var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_GETIT = 2;
var SKIN_ON_CLICK_LINK_TO_INTRO = 3;


Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);//在模态对话框下无效果

btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);

function OnClickbtnSysClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}



function OnInit()
{
    textTitle.visible = false;

	OnSize(Window.width, Window.height);
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
	
	itemHtmlGetContribute.visible = true;
	itemHtmlGetContribute.left = imgMidBk.left;
	itemHtmlGetContribute.top = imgMidBk.top;
	itemHtmlGetContribute.width = imgMidBk.width;
	itemHtmlGetContribute.height = imgMidBk.height;

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


