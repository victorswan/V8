
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);


function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	ShowPersonalDlgBk.visible = true;
	ShowPersonalDlgBk.left = 0;
	ShowPersonalDlgBk.top = 0;
	ShowPersonalDlgBk.width = cx;
	ShowPersonalDlgBk.height = cy;
	
	imgTitleIcon.visible = true;
	imgTitleIcon.left = 10;
	imgTitleIcon.top = 2;

	textTitle.visible = true;
	textTitle.left = imgTitleIcon.left + imgTitleIcon.width + 5;
	textTitle.top = 4;
	textTitle.width = textTitle.textWidth;
	textTitle.height = textTitle.textHeight;
	
	imgLine.left = textTitle.left + textTitle.width + 6;
	imgLine.top = textTitle.top + 5;
	
	////////////////////////////////////////////
	itemCheckAutoLogin.visible = true;
	itemCheckAutoLogin.left = 264;
	itemCheckAutoLogin.top = imgTitleIcon.top + imgTitleIcon.height + 130;

	itemCheckAutoRun.visible = true;
	itemCheckAutoRun.left = itemCheckAutoLogin.left;
	itemCheckAutoRun.top = itemCheckAutoLogin.top + itemCheckAutoLogin.height + 10;

	itemCheckOpenSound.visible = true;
	itemCheckOpenSound.left = itemCheckAutoRun.left;
	itemCheckOpenSound.top = itemCheckAutoRun.top + itemCheckAutoRun.height + 10;

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
