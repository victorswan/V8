var SKIN_ON_CLICK_SEARCH = 1;
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize); 
// btnMagnifier.AttachEvent("OnClick",OnSearch);

// function OnSearch()
// { 
	// Window.PostSkinMessage(SKIN_ON_CLICK_SEARCH, 0);
// }

function OnInit()
{
	itemSearch.tabStop = false;
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{
    imgSearchBarBk.left = 0;
	imgSearchBarBk.top = 0;
	imgSearchBarBk.width = cx;
	imgSearchBarBk.height = cy;
	
	// btnMagnifier.width = 40;
	// btnMagnifier.height = 30; 
    // btnMagnifier.left = imgSearchBarBk.left + imgSearchBarBk.width - btnMagnifier.width - 5;
	// btnMagnifier.top = imgSearchBarBk.top + 9;
	
	// imgRoundBackground.left = imgSearchBarBk.left + 4;
	// imgRoundBackground.top = imgSearchBarBk.top + 4;
	// imgRoundBackground.width = imgSearchBarBk.width - 8;
	// imgRoundBackground.height = imgSearchBarBk.height - 8;
	
	imgSearchBarEditBk.left = 2;
	imgSearchBarEditBk.top = 3;
	imgSearchBarEditBk.width = cx - 4;
	imgSearchBarEditBk.height = 26;
	
	// itemSearch.left = 12;
	// itemSearch.top = 3;
	// itemSearch.height = cy - itemSearch.top - 2;
	// itemSearch.width = btnMagnifier.left - itemSearch.left - 6;
	
	itemSearch.height = 16;
	itemSearch.left = imgSearchBarEditBk.left + 4;
	itemSearch.top = imgSearchBarEditBk.top + 6;
	itemSearch.width = imgSearchBarEditBk.width - 8;
	
}

