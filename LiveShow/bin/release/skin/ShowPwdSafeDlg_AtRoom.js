
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);


function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	ShowPwdSafeDlgBk.visible = true;
	ShowPwdSafeDlgBk.left = 0;
	ShowPwdSafeDlgBk.top = 0;
	ShowPwdSafeDlgBk.width = cx;
	ShowPwdSafeDlgBk.height = cy;
	
	itemHtmlPwdSafe.visible = true;
	itemHtmlPwdSafe.left = 0;
	itemHtmlPwdSafe.top = 0;
	itemHtmlPwdSafe.width = cx;
	itemHtmlPwdSafe.height = cy;
	
	imgApplyEffect.left = 0;
	imgApplyEffect.top = 0;
	imgApplyEffect.width = cx;
	imgApplyEffect.height = cy;
	
	
}

function OnNotify(code, code1)
{
  switch(code)
  {
  default:
    break;
  }
}
