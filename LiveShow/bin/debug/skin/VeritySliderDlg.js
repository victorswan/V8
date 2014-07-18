
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);


function OnInit()
{
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{
	imgVeritySliderDlgBorderLeft.left = 0;
	imgVeritySliderDlgBorderLeft.top = 0;
	imgVeritySliderDlgBorderLeft.width = 1;
	imgVeritySliderDlgBorderLeft.height = cy;
	
	imgVeritySliderDlgBorderBottom.left = 0;
	imgVeritySliderDlgBorderBottom.top = cy - 1;
	imgVeritySliderDlgBorderBottom.width = cx;
	imgVeritySliderDlgBorderBottom.height = 1;
	
	imgVeritySliderDlgBorderRight.left = cx - 1;
	imgVeritySliderDlgBorderRight.top = 0;
	imgVeritySliderDlgBorderRight.width = 1;
	imgVeritySliderDlgBorderRight.height = cy;
	
	imgVeritySliderDlgBorderTop.left = 0;
	imgVeritySliderDlgBorderTop.top = 0;
	imgVeritySliderDlgBorderTop.width = cx;
	imgVeritySliderDlgBorderTop.height = 1;

	imgVeritySliderDlgBk.left = 1;
	imgVeritySliderDlgBk.top = 1;
	imgVeritySliderDlgBk.width = cx - 2;
	imgVeritySliderDlgBk.height = cy - 2;
	
	itemVeritySlider.width = 22;
	itemVeritySlider.height = 80;
	itemVeritySlider.left = imgVeritySliderDlgBk.left + (imgVeritySliderDlgBk.width - itemVeritySlider.width)/2;
	itemVeritySlider.top = imgVeritySliderDlgBk.top + (imgVeritySliderDlgBk.height - itemVeritySlider.height)/2;
	
}

function OnNotify(code, code1)
{
	switch(code)
	{
       default:break;
	}
}
