
var SKIN_ON_CLICK_CLOSE = 1;
var SKIN_ON_CLICK_MINIMIZE = 2;

var SKIN_NOTIFY_IF_DOWNLOADING = 3;

var m_bDownloading = 1;


Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", btnCloseOnClick);
btnSysMinimize.AttachEvent("OnClick",btnMinimizeOnClick);

function btnCloseOnClick()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_CLOSE, 0);
}

function btnMinimizeOnClick()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_MINIMIZE, 0);
}

function OnInit()
{
	textTitle.text = "白兔KTV更新向导";
     textTitle.visible = false;
	 imgTitleIcon.visible = false;
	 btnSysClose.disabled = true;  
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
   
	ImgUpdateGuideDlgBk.visible = true;
	ImgUpdateGuideDlgBk.left = 1;
	ImgUpdateGuideDlgBk.top = 1;
	ImgUpdateGuideDlgBk.width = cx-2;
	ImgUpdateGuideDlgBk.height = cy-2;	
	
	textTheTitle.left = 12;
	textTheTitle.top = 12;
	textTheTitle.width = textTheTitle.textWidth;
	textTheTitle.height = textTheTitle.textHeight;
	
	textTopPrompt.visible = true;
	textTopPrompt.width = textTopPrompt.textWidth;
	textTopPrompt.height = textTopPrompt.textHeight;
	textTopPrompt.left = ImgUpdateGuideDlgBk.left + (ImgUpdateGuideDlgBk.width - textTopPrompt.width)/2;
	textTopPrompt.top = ImgUpdateGuideDlgBk.top + 45;
	
	itemHtmlUpdateGuide.visible = true;
	itemHtmlUpdateGuide.left = ImgUpdateGuideDlgBk.left;
	itemHtmlUpdateGuide.top = 62;
	itemHtmlUpdateGuide.width = ImgUpdateGuideDlgBk.width;
	itemHtmlUpdateGuide.height = ImgUpdateGuideDlgBk.top + ImgUpdateGuideDlgBk.height - 100 - itemHtmlUpdateGuide.top;
		   
	   
	   progBack.visible = true;
	   progBack.height = 17;
	   progBack.width = 418;
	   progBack.left = ImgUpdateGuideDlgBk.left + (ImgUpdateGuideDlgBk.width - progBack.width)/2;
	   progBack.top = itemHtmlUpdateGuide.top + itemHtmlUpdateGuide.height + 12;
	   
	   progFull.visible = true;
	   progFull.height = progBack.height - 2;
	   progFull.left = progBack.left;
	   progFull.top = progBack.top + 1;
	   
	   progWhite.visible = true;
	   progWhite.height = progBack.height;
	   progWhite.left = progBack.left;
	   progWhite.top = progBack.top;
	   
	   textProg.visible = true;
	   textProg.width = 50;
	   textProg.height = 18;
	   textProg.left = progBack.left + (progBack.width - textProg.width)/2 ;
	   textProg.top = progBack.top + (progBack.height - textProg.height)/2;
	   
	   textUpdateFail.width = 200;
	   textUpdateFail.height = 18;
	   textUpdateFail.left = progBack.left + (progBack.width - textUpdateFail.width)/2;
	   textUpdateFail.top = progBack.top + progBack.height + 5;  
	   

}

function OnNotify(code, code1)
{
	switch(code)
	{ 
	  case SKIN_NOTIFY_IF_DOWNLOADING:
	  {
	      // m_bDownloading = code1;
		  m_bDownloading = true;
		  OnSize(Window.width,Window.height);
	  }
	  break;
	  default:break;
	}
}
