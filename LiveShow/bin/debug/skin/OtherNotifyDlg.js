

var NOTIFY_STYLE_NO_ICON_LINK = 1;
var NOTIFY_STYLE_ICON_LINK = 2;

var SKIN_ON_CLICK_CLOSE = 3;
var SKIN_ON_CLICK_OK = 4;

var SKIN_NOTIFY_SHOW = 5;
var SKIN_NOTIFY_COLSE = 6;

var SKIN_ON_CLICK_BTN_LINK = 7;

var STYLE = 0;
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);//在模态对话框下无效果

btnSysClose.AttachEvent("OnClick", OnClickbtnSysClose);
// btnOK.AttachEvent("OnClick",OnClickbtnOK);
btnLink.AttachEvent("OnClick",OnClickBtnLink);

function OnClickbtnSysClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}
function OnClickbtnOK()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_OK,0);
}
function OnClickBtnLink()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_LINK,0);
}

function OnInit()
{
    textTitle.visible = false;
	imgTitleIcon.visible = false;

	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
    Window.BeginPaint();

	STYLE = textNotifyDlgStyle.text;//类型标记
	
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
	textTheTitle.width = 150;
	textTheTitle.height = 20;
	
	if(STYLE == NOTIFY_STYLE_NO_ICON_LINK)
	{
	    textContent1.visible = true;
		textContent1.width = cx - 30;
		textContent1.height = 40;
		textContent1.left =  (cx - textContent1.width)/2;
		textContent1.top = 50;
		
	}else if(STYLE == NOTIFY_STYLE_ICON_LINK)
	{
	    textBegin.visible = true;
		textBegin.left = 25;
		textBegin.top =  42;
		textBegin.width = textBegin.textWidth;
		textBegin.height = textBegin.textHeight;
		
		imgLevelOrTitle.visible = true;
		imgLevelOrTitle.left = textBegin.left + textBegin.width + 1;
		imgLevelOrTitle.top = textBegin.top - 2;
		imgLevelOrTitle.width = 16;
		imgLevelOrTitle.height = 16;
		
		textName.visible = true;
		textName.left = imgLevelOrTitle.left + imgLevelOrTitle.width + 1;
		textName.top = textBegin.top;
		textName.width = textName.textWidth;
		textName.height = textName.textHeight;
		
		textContent2.visible = true;
		textContent2.width = cx - 40;
		textContent2.height = 60;
		textContent2.left = textBegin.left;
		textContent2.top = textBegin.top + textBegin.height + 5;
		
		
		btnLink.visible = true;
		btnLink.width = textContent2.width;
		btnLink.height = 15;
		btnLink.left = (cx - btnLink.width)/2;
		btnLink.top = textContent2.top + textContent2.height + 2;
		
	}
    	
	Window.EndPaint();
 
}

function OnNotify(code, code1)
{
  switch(code)
  {
  case SKIN_NOTIFY_SHOW:
       {
	     imgLevelOrTitle.Play();
	     OnSize(Window.width,Window.height);
	   }
	   break;
  case SKIN_NOTIFY_COLSE:
      {
	   imgLevelOrTitle.Stop();
	  }
	  break;
  default:
    break;
  }
}


