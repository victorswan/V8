
var SKIN_ON_CLICK_BTN_CLOSE = 1;
var NOTIFY_SKIN_IF_AUDIO = 2;
var NOTIFY_SKIN_VIDEO_DLG_HWND = 3;

var bHasAudio = false;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnClose.AttachEvent("OnClick",OnClickBtnClose);


function OnClickBtnClose()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CLOSE,0);  
}

function OnInit()
{
    btnSysClose.visible = false;
	Window.titleHeight = 20;
	OnSize(Window.width, Window.height);
}

function OnSize(cx,cy)
{
	imgTopBk.left = 2;
	imgTopBk.top = 2;
	imgTopBk.width = cx - 4;
	imgTopBk.height = 21;

	imgMidBk.left = 2;
	imgMidBk.top = imgTopBk.top + imgTopBk.height;
	imgMidBk.width = cx - 4;
	imgMidBk.height = cy - 2 - imgMidBk.top;
	
	textUser.visible = true;
	textUser.top = 2;
	textUser.left = 2;
	textUser.width = cx - 4;
	textUser.height = 18;
	
	btnClose.visible = true;
	btnClose.width = 17;
	btnClose.height = 18;
	btnClose.top = 3;
	btnClose.left = imgTopBk.left + imgTopBk.width - 5 - btnClose.width;
	
	itemVideoDlg.visible = true;
	itemVideoDlg.left = imgMidBk.left;
	itemVideoDlg.top = imgMidBk.top + 19;
	itemVideoDlg.width = 216;
	itemVideoDlg.height = 165;//宽高与C++代码里一致
	
}

function OnNotify(code,code1)
{
	switch(code)
	{
	  case NOTIFY_SKIN_IF_AUDIO:
	  {
	     if(0 == code1)
		 {
		    bHasAudio = false;
		 }
		 else
		 {
		    bHasAudio = true;
		 }
		 OnSize(Window.width,Window.height);
	  }
	     break;
	  case NOTIFY_SKIN_VIDEO_DLG_HWND:
	     {
		    itemVideoDlg.SetClient(code1);
		 }
		 break;
	  default: break;
	}
}

