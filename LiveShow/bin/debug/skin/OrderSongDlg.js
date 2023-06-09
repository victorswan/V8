var SKIN_ON_CLICK_BTN_CLOSE = 1;
//var SKIN_ON_CLICK_BTN_SONGWISH = 2;
var SKIN_ON_CLICK_TABBTN_ORDERED_SONG = 3;
var SKIN_ON_CLICK_TABBTN_SONGLIST = 4;
var SKIN_ON_CLICK_TABBTN_MARKLIST = 5;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

//btnSongWish.AttachEvent("OnClick", OnClickBtnSongWish);
tabBtnOrderedSong.AttachEvent("OnClick", OnClickTabBtnOrderedSong);
tabBtnSongList.AttachEvent("OnClick", OnClickTabBtnSongList);
tabBtnMarkList.AttachEvent("OnClick", OnClickTabBtnMarkList);
btnClose.AttachEvent("OnClick", OnClickBtnClose);

function OnClickBtnClose()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CLOSE, 0);
}

// function OnClickBtnSongWish()
// {
	// Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SONGWISH, 0);
// }

function OnClickTabBtnOrderedSong()
{
	if(tabBtnOrderedSong.checked == false)
	{
	    tabBtnOrderedSong.checked = true;
		tabBtnSongList.checked = false;
		tabBtnMarkList.checked = false;
		tabBtnOrderedSong.labelNormalColor = "#0";
		tabBtnSongList.labelNormalColor = "#ffffff";
		tabBtnMarkList.labelNormalColor = "#ffffff";
		Window.PostSkinMessage(SKIN_ON_CLICK_TABBTN_ORDERED_SONG, 0);
	}
}		

function OnClickTabBtnSongList()
{
	if(tabBtnSongList.checked == false)
	{
	    tabBtnSongList.checked = true;
		tabBtnOrderedSong.checked = false;
		tabBtnMarkList.checked = false;
		tabBtnSongList.labelNormalColor = "#0";
		tabBtnOrderedSong.labelNormalColor = "#ffffff";
		tabBtnMarkList.labelNormalColor = "#ffffff";
		Window.PostSkinMessage(SKIN_ON_CLICK_TABBTN_SONGLIST, 0);
	}
}	

function OnClickTabBtnMarkList()
{
	if(tabBtnMarkList.checked == false)
	{
	    tabBtnMarkList.checked = true;
		tabBtnOrderedSong.checked = false;
		tabBtnSongList.checked = false;
		tabBtnMarkList.labelNormalColor = "#0";
		tabBtnOrderedSong.labelNormalColor = "#ffffff";
		tabBtnSongList.labelNormalColor = "#ffffff";
		Window.PostSkinMessage(SKIN_ON_CLICK_TABBTN_MARKLIST, 0);
	}
}	

function OnInit()
{
    textTitle.text = "";
    textTitle.visible = false;
	btnSysClose.visible = false;

	imgTitleIcon.visible = false;
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	//////////////////////////////////////
 //取消圆角及圆角外框
	Window.upCornerRadius = "0";
	Window.downCornerRadius = "0";
	imgFrameBackground.visible = false;
		
	//加入直角外框
	imgOrderSongTop.visible = true;
	imgOrderSongTop.left = 0;
	imgOrderSongTop.top = 0;
	imgOrderSongTop.width = cx;
	imgOrderSongTop.height = 1;
		
	imgOrderSongLeft.visible = true;
	imgOrderSongLeft.left = 0;
	imgOrderSongLeft.top = 1;
	imgOrderSongLeft.width = 1;
	imgOrderSongLeft.height = cy - 2;
		
	imgOrderSongRight.visible = true;
	imgOrderSongRight.left = cx - 1;
	imgOrderSongRight.top = imgOrderSongLeft.top;
	imgOrderSongRight.width = imgOrderSongLeft.width;
	imgOrderSongRight.height = imgOrderSongLeft.height;
		
	imgOrderSongBottom.visible = true;
	imgOrderSongBottom.left = imgOrderSongTop.left;
	imgOrderSongBottom.top = imgOrderSongLeft.top + imgOrderSongLeft.height;
	imgOrderSongBottom.width = imgOrderSongTop.width;
	imgOrderSongBottom.height = 1;
		
	imgOrderSongBk.left = 1;
	imgOrderSongBk.top = 1;
	imgOrderSongBk.width = cx - 2;
	imgOrderSongBk.height = 51;	
	
	tabBtnSongList.left = 20;
	tabBtnSongList.top = 2;
	tabBtnSongList.width = 162;
	tabBtnSongList.height = 50;
	
	tabBtnOrderedSong.left = tabBtnSongList.left + tabBtnSongList.width + 5;
	tabBtnOrderedSong.top = tabBtnSongList.top;
	tabBtnOrderedSong.width = 162;
	tabBtnOrderedSong.height = 50;
	
	tabBtnMarkList.left = tabBtnOrderedSong.left + tabBtnOrderedSong.width + 5;
	tabBtnMarkList.top = tabBtnOrderedSong.top;
	tabBtnMarkList.width = 162;
	tabBtnMarkList.height = 50;
	
	itemOrderList.left = 1;
	itemOrderList.top = tabBtnOrderedSong.top + tabBtnOrderedSong.height;
	itemOrderList.width = cx - 2;
	itemOrderList.height = cy - 1 - itemOrderList.top;
	
	itemSongList.left = 1;
	itemSongList.top = tabBtnOrderedSong.top + tabBtnOrderedSong.height;
	itemSongList.width = cx - 2;
	itemSongList.height = cy - 1 - itemSongList.top;
	
	itemMarkList.left = 1;
	itemMarkList.top = tabBtnOrderedSong.top + tabBtnOrderedSong.height;
	itemMarkList.width = cx - 2;
	itemMarkList.height = cy - 1 - itemMarkList.top;
	
	// btnSongWish.left = 20;
	// btnSongWish.top = cy - 4 - btnSongWish.height;
	
	btnClose.left = cx - 2 - btnClose.width;
	btnClose.top = 2;
}

function OnNotify(code, code1)
{
  switch(code)
  {

  default:
    break;
  }
}
