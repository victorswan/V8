var SKIN_ON_CLICK_BTN_GETFLASH = 1;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnGetFlash.AttachEvent("OnClick", OnClickBtnGetFlash)

function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	imgSofaDlgBk.visible = true;
	imgSofaDlgBk.left = 0;
	imgSofaDlgBk.top = 0;
	imgSofaDlgBk.width = cx;
	imgSofaDlgBk.height = cy;
	
	//btnGetFlash.visible = false;
	btnGetFlash.width = 350;
	btnGetFlash.height = 30;
	btnGetFlash.left = imgSofaDlgBk.left + (imgSofaDlgBk.width - btnGetFlash.width)/2;
	btnGetFlash.top = imgSofaDlgBk.top + (imgSofaDlgBk.height - btnGetFlash.height)/2;
	
}

function OnNotify(code, code1)
{
  switch(code)
  {
  default:
    break;
  }
}

function OnClickBtnGetFlash()
{
   Window.PostSkinMessage(SKIN_ON_CLICK_BTN_GETFLASH ,0);
}
