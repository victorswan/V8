
var SKIN_ON_CLICK_BTN_PAODAO = 1;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnPaodao.AttachEvent("OnClick",OnClickBtnPaodao);

function OnClickBtnPaodao()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_PAODAO,0);
}

function OnInit()
{

	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
//	imgScrollBtnDlgBk.visible = true;
//	imgScrollBtnDlgBk.left = 0;
//	imgScrollBtnDlgBk.top = 0;
//	imgScrollBtnDlgBk.width = cx;
//	imgScrollBtnDlgBk.height = cy;
	
	btnPaodao.visible = true;
	btnPaodao.left = 0;
	btnPaodao.top = 0;
	btnPaodao.width = cx;
	btnPaodao.height = cy;
}

function OnNotify(code, code1)
{
	
}
