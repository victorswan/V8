

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);


function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	Step2DlgBk.visible = true;
	Step2DlgBk.left = 0;
	Step2DlgBk.top = 0;
	Step2DlgBk.width = cx;
    Step2DlgBk.height = cy;
///////////////////////////////////////
    textMicPrompt.visible = true;
	textMicPrompt.left = 60;
	textMicPrompt.top = 1;
	textMicPrompt.width = cx - 120;
	textMicPrompt.height = 40;
	
	imgMic.visible = true;
	imgMic.left = textMicPrompt.left;
	imgMic.top = textMicPrompt.top + textMicPrompt.height + 35;
	imgMic.width = 40;
	imgMic.height = 74;
	
	textMic.visible = true;
	textMic.left = imgMic.left + imgMic.width + 16;
	textMic.top = imgMic.top + 3;
	textMic.width = textMic.textWidth;
	textMic.height = textMic.textHeight;
	
	itemComboMic.visible = true;
	itemComboMic.left = textMic.left;
	itemComboMic.top = textMic.top + textMic.height + 13;
	itemComboMic.width = 158;
	itemComboMic.height = 20;
	
	SliderMic.visible = true;
	SliderMic.left = itemComboMic.left;
	SliderMic.top = itemComboMic.top + itemComboMic.height + 31;
	SliderMic.width = 125;
	SliderMic.height = 20;
	
	progBack.left = SliderMic.left + SliderMic.width + 6;
	progBack.top = SliderMic.top - 2;
	progBack.width = 119;
	progBack.height = 17;
	
	progFull.left = progBack.left;
	progFull.top = progBack.top;
	progFull.height = progBack.height;
	
	progWhite.left = progBack.left;
	progWhite.top = progBack.top;
	progWhite.height = progBack.height;
	
	imgSeperatorLine.visible = true;
	imgSeperatorLine.left = 5;
	imgSeperatorLine.top = SliderMic.top + SliderMic.height + 65;
	imgSeperatorLine.width = cx - 10;
	imgSeperatorLine.height = 1;
	
	textPrompt.visible = true;
	textPrompt.left = textMicPrompt.left;
	textPrompt.top = imgSeperatorLine.top + imgSeperatorLine.height + 5;
	textPrompt.width = textMicPrompt.width;
	textPrompt.height = 40;
    	
}

function OnNotify(code, code1)
{
  switch(code)
  {
  default:
    break;
  }
}
