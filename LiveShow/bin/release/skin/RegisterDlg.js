
var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_NOTIFY_DLG_TYPE = 2;

var dlgType = 0;//0为注册框，1为完善资料框，默认为0

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
	textTitle.text = "账号注册";
    textTitle.visible = false;
    // textTitle.fontWeight = 500;
	// textTitle.fontSize = 11;
    // textTitle.normalColor = 0xffffff;
    // textTitle.colorTransform = true;
	if(0 == dlgType)
	{
	  Window.width = 491;
	  Window.height = 448;
	  cx = Window.width;
	  cy = Window.height;
	  textTheTitle.text = "账号注册";
	 // imgRegisterEffect1.visible = true;
	  btnSysClose.visible = true;
	}else if(1 == dlgType)
	{
	  Window.width = 491; 
	  Window.height = 398;
	  cx = Window.width;
	  cy = Window.height;
	  textTheTitle.text = "白兔KTV";
	  //imgRegisterEffect1.visible = true;
	  btnSysClose.visible = false;
	}
	
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	// textTitle.width = textTitle.textWidth;
	// textTitle.height = textTitle.textHeight;
	// textTitle.left = imgTitleIcon.left + imgTitleIcon.width + 10;
	// textTitle.top = 0 + (32 - textTitle.height)/2 ;
	
    imgRegisterBk.visible = true;
	imgRegisterBk.left = 2;
	imgRegisterBk.top = 2;
	imgRegisterBk.width = cx - 4;
	imgRegisterBk.height = 90;
	
	// imgRegisterEffect1.left = 2;
	// imgRegisterEffect1.top = 2;
	
	// imgRegisterEffect2.left = 2;
	// imgRegisterEffect2.top = 2;
	
	
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	textTheTitle.left = 35;
	textTheTitle.top = 16;
	
	// imgRegisterTitle.left = 10;
	// imgRegisterTitle.top = 8;
	
	itemHtmlRegister.visible = true;
	itemHtmlRegister.left = imgRegisterBk.left;
	itemHtmlRegister.top = imgRegisterBk.top + imgRegisterBk.height;
	itemHtmlRegister.width = imgRegisterBk.width;
	itemHtmlRegister.height = cy - 2- itemHtmlRegister.top;
}

function OnNotify(code, code1)
{
	switch(code)
	{
	case SKIN_NOTIFY_DLG_TYPE:
	    {
		    dlgType = code1;
		}
		break;
    default:break;
	}
}
