var SKIN_NOTIFY_VEDIO_CHANGE = 1;
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

function OnInit()
{
		imgVedioSmall.visible = false;
		imgVedioBig.visible = true;
		OnSize(Window.width, Window.height);
}

function OnSize(cx,cy)
{
		imgVedioSmall.left = 0;
		imgVedioSmall.top = 0;
		imgVedioSmall.width = cx;
		imgVedioSmall.height = cy;
		imgVedioBig.left = 0;
		imgVedioBig.top = 0;
		imgVedioBig.width = cx;
		imgVedioBig.height = cy;
}

function OnNotify(code,code1)
{
	switch(code)
	{
		case SKIN_NOTIFY_VEDIO_CHANGE:
			OnVedioChanged();
		break;

		default:
		return;
	}
}


function OnVedioChanged()
{
	var imgVisible;
	imgVisible = imgVedioSmall.visible;
	imgVedioSmall.visible = imgVedioBig.visible;
	imgVedioBig.visible = imgVisible;
}