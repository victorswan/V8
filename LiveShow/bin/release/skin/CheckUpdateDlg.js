
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);


function OnInit()
{
	textTitle.text = "";
    textTitle.visible=false;
	btnSysClose.visible = false;
	imgTitleIcon.visible = false;
	
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	imgCheckUpdateDlgBk.visible = true;
	imgCheckUpdateDlgBk.left = 0;
	imgCheckUpdateDlgBk.top = 0;
	imgCheckUpdateDlgBk.width = cx;
	imgCheckUpdateDlgBk.height = cy;
	
	// textPrompt.visible = true;
	// textPrompt.width = textPrompt.textWidth;
	// textPrompt.height = textPrompt.textHeight;
	// textPrompt.left = imgCheckUpdateDlgBk.left + 4;
	// textPrompt.top = imgCheckUpdateDlgBk.top + imgCheckUpdateDlgBk.height - 4 - textPrompt.height;

}

function OnNotify(code, code1)
{
	
}
