
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

function OnInit()
{
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	ImgIconPaodaoDlgBK.visible = true ;
	ImgIconPaodaoDlgBK.left = 0;
	ImgIconPaodaoDlgBK.top = 0;
	ImgIconPaodaoDlgBK.width = cx ;
	ImgIconPaodaoDlgBK.height = cy;
	
	MyGoodsList.visible = true ;
	MyGoodsList.left = 5 ;
	MyGoodsList.top = 30 ;
	MyGoodsList.width = cx - 10;
	MyGoodsList.height = cy - 35 ;	
}

function OnNotify(code, code1)
{
	
}
