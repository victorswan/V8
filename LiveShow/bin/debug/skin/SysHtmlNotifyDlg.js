
//var SKIN_ON_CLICK_BTN_CLOSE = 1;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

//btnSysClose.AttachEvent("OnClick", btnCloseOnClick);

//function btnCloseOnClick()
//{
//    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CLOSE,0);
//}

function OnInit()
{
    textTitle.text = "系统消息";
    textTitle.visible = false;

	imgTitleIcon.visible = false;
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	//SysNotifyDlgBk.visible = true;
	//SysNotifyDlgBk.left = 2;
	//SysNotifyDlgBk.top = 2;
	//SysNotifyDlgBk.width = cx - 4;
	//SysNotifyDlgBk.height = cy - 4;
	
	//textTheTitle.left = 10;
	//textTheTitle.top = 8;
	//textTheTitle.width = 150;
	//textTheTitle.height = 20;
	
	//////////////////////////////////////
	itemHtmlSysNotify.left = 1;
	itemHtmlSysNotify.top = 1;
	itemHtmlSysNotify.width = cx-2;
	itemHtmlSysNotify.height = cy-2;
	
}

function OnNotify(code, code1)
{
  switch(code)
  {

  default:
    break;
  }
}
