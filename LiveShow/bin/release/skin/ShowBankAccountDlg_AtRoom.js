
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);


function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	ShowBankAccountDlgBk.visible = true;
	ShowBankAccountDlgBk.left = 0;
	ShowBankAccountDlgBk.top = 0;
	ShowBankAccountDlgBk.width = cx;
	ShowBankAccountDlgBk.height = cy;
	
	itemHtmlBankAccount.visible = true;
	itemHtmlBankAccount.left = 0;
	itemHtmlBankAccount.top = 0;
	itemHtmlBankAccount.width = cx;
	itemHtmlBankAccount.height = cy;
	
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
