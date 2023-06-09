var SKIN_ON_CLICK_BTN_TEST = 1;
var SKIN_ON_CLICK_BTN_STOP = 2;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnTest.AttachEvent("OnClick", OnClickBtnTest);
btnStop.AttachEvent("OnClick", OnClickBtnStop);

function OnClickBtnTest()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_TEST,0);
	btnTest.visible = false;
	btnStop.visible = true;
}

function OnClickBtnStop()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_STOP,0);
	btnTest.visible = true;
	btnStop.visible = false;
}

function OnInit()
{
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	Step1DlgBk.visible = true;
	Step1DlgBk.left = 0;
	Step1DlgBk.top = 0;
	Step1DlgBk.width = cx;
    Step1DlgBk.height = cy;
///////////////////////////////////////
    textTestSound.visible = true;
	textTestSound.left = Step1DlgBk.left + 60;
	textTestSound.top = Step1DlgBk.top + 1;
	textTestSound.width = Step1DlgBk.width - 120;
	textTestSound.height = 40;
		
	imgLoudSpeaker.visible = true;
	imgLoudSpeaker.left = textTestSound.left;
	imgLoudSpeaker.top = textTestSound.top + textTestSound.height + 35;
	imgLoudSpeaker.width = 94;
	imgLoudSpeaker.height = 72;
	
	textLoudSpeaker.visible = true;
	textLoudSpeaker.left = imgLoudSpeaker.left + imgLoudSpeaker.width + 8;
	textLoudSpeaker.top = imgLoudSpeaker.top + 3;
	textLoudSpeaker.width = textLoudSpeaker.textWidth;
	textLoudSpeaker.height = textLoudSpeaker.textHeight;
	
	itemComboLoudSpeaker.visible = true;
	itemComboLoudSpeaker.left = textLoudSpeaker.left;
	itemComboLoudSpeaker.top = textLoudSpeaker.top + textLoudSpeaker.height + 8;
	itemComboLoudSpeaker.width = 158;
	itemComboLoudSpeaker.height = 20;
	
	SliderLoudSpeaker.visible = true;
	SliderLoudSpeaker.left = itemComboLoudSpeaker.left;
	SliderLoudSpeaker.top = itemComboLoudSpeaker.top + itemComboLoudSpeaker.height + 25;
	SliderLoudSpeaker.width = 125;
	SliderLoudSpeaker.height = 20;
	
	btnTest.visible = true;
	btnTest.left = SliderLoudSpeaker.left + SliderLoudSpeaker.width + 5;
	btnTest.top = SliderLoudSpeaker.top - 8;
	btnTest.width = 134;
	btnTest.height = 42;
	
	btnStop.visible = false;
	btnStop.left = SliderLoudSpeaker.left + SliderLoudSpeaker.width + 5;
	btnStop.top = SliderLoudSpeaker.top - 8;
	btnStop.width = btnTest.width;
	btnStop.height = btnTest.height;
	
	imgSeperatorLine.visible = true;
	imgSeperatorLine.left = 5;
	imgSeperatorLine.top = SliderLoudSpeaker.top + SliderLoudSpeaker.height + 45
	imgSeperatorLine.width = cx - 10;
	imgSeperatorLine.height = 1;
	
	textPrompt.visible = true;
	textPrompt.left = textTestSound.left;
	textPrompt.top = imgSeperatorLine.top + imgSeperatorLine.height + 15;
	textPrompt.width = textPrompt.textWidth;
	textPrompt.height = textPrompt.textHeight;
	
	textContent.left = textPrompt.left;
	textContent.top = textPrompt.top + textPrompt.height + 5;
	textContent.width = textTestSound.width;
    textContent.height = 40;	
	
    	
}

function OnNotify(code, code1)
{
  switch(code)
  {
  default:
    break;
  }
}
