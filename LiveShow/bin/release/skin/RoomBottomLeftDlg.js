
var SKIN_NOTIFY_MARK_DLG = 1;
var SKIN_NOTIFY_SEARCH_DLG_HWND = 2;
var SKIN_ON_CLICK_TABBTN_MGR = 3;
var SKIN_ON_CLICK_TABBTN_USER = 4;
var SKIN_ON_CLICK_TABBTN_MIC = 5;
var SKIN_ON_CLICK_BTN_SEARCH = 6;
var SKIN_ON_CLICK_ICON_INSTRUCTION = 7;
var SKIN_ON_CLICK_BTN_WHEREIAM = 8;
var SKIN_NOTIFY_SEARCH_LIST	= 9;
var SKIN_NOTIFY_SHOW_USERITEM = 10;
var SKIN_NOTIFY_SELFINFOANDSET_DLG = 11;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

tabBtnMgr.AttachEvent("OnClick",OnClickTabBtnMgr);
tabBtnUser.AttachEvent("OnClick",OnClickTabBtnUser);
tabBtnMicList.AttachEvent("OnClick",OnClickTabBtnMicList);

btnSearch.AttachEvent("OnClick",OnClickBtnSearch);
btnIconInstruction.AttachEvent("OnClick",OnClickBtnIconInstruction);
btnWhereIAm.AttachEvent("OnClick", OnClickBtnWhereIAm);

function OnClickTabBtnMgr()
{
   tabBtnMgr.checked = true;
   tabBtnUser.checked = false;
   tabBtnMicList.checked = false;
   btnIconInstruction.checked = false;
   tabBtnMgr.labelNormalColor = "#ffffff";
   tabBtnUser.labelNormalColor = "#ffffff";
   tabBtnMicList.labelNormalColor = "#ffffff";
   Window.PostSkinMessage(SKIN_ON_CLICK_TABBTN_MGR,0);
}

function OnClickTabBtnUser()
{
   tabBtnMgr.checked = false;
   tabBtnUser.checked = true;
   tabBtnMicList.checked = false;
   btnIconInstruction.checked = false;
   tabBtnUser.labelNormalColor = "#ffffff";
   tabBtnMgr.labelNormalColor = "#ffffff";
   tabBtnMicList.labelNormalColor = "#ffffff";
   Window.PostSkinMessage(SKIN_ON_CLICK_TABBTN_USER,0);
}

function OnClickTabBtnMicList()
{
   tabBtnMgr.checked = false;
   tabBtnUser.checked = false;
   tabBtnMicList.checked = true;
   btnIconInstruction.checked = false;
   tabBtnMicList.labelNormalColor = "#ffffff";
   tabBtnMgr.labelNormalColor = "#ffffff";
   tabBtnUser.labelNormalColor = "#ffffff";   
   Window.PostSkinMessage(SKIN_ON_CLICK_TABBTN_MIC,0);
}

function OnClickBtnSearch()
{
   if(true == btnSearch.checked)
   {
      btnSearch.checked = false;
	  Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SEARCH,0);
   }
   else
   {
      btnSearch.checked = true;
	  Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SEARCH,1);
   }
   OnSize(Window.width,Window.height);
}

function OnClickBtnIconInstruction()
{
   tabBtnMgr.checked = false;
   tabBtnUser.checked = false;
   tabBtnMicList.checked = false;
   btnIconInstruction.checked = true;
  // if(false == btnIconInstruction.checked)
  // {
   //   btnIconInstruction.checked = true;
   //   Window.PostSkinMessage(SKIN_ON_CLICK_ICON_INSTRUCTION,1);
   //}
  // else
   //{
   //  btnIconInstruction.checked = false;
      Window.PostSkinMessage(SKIN_ON_CLICK_ICON_INSTRUCTION,0);
   //}
}

function OnClickBtnWhereIAm()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_WHEREIAM, 0);
}


function OnInit()
{
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{
	imgRoomBottomLeftDlgBk.left = 0;
	imgRoomBottomLeftDlgBk.top = 0;
	imgRoomBottomLeftDlgBk.width = cx;
	imgRoomBottomLeftDlgBk.height = cy;
	//评价区
	itemSongMarkDlg.visible = false;
	itemSongMarkDlg.left = imgRoomBottomLeftDlgBk.left;
	itemSongMarkDlg.top = imgRoomBottomLeftDlgBk.top;
	itemSongMarkDlg.width = imgRoomBottomLeftDlgBk.width;
	itemSongMarkDlg.height = 122;
	//个人信息区
	itemSelfInfoAndSetDlg.width = itemSongMarkDlg.width;
	itemSelfInfoAndSetDlg.height = 57;
	itemSelfInfoAndSetDlg.left = itemSongMarkDlg.left;
	itemSelfInfoAndSetDlg.top = cy - itemSelfInfoAndSetDlg.height;
	//用户列表
	imgTabBtnBk.left = imgRoomBottomLeftDlgBk.left - 1;
	//imgTabBtnBk.top = itemSongMarkDlg.top + itemSongMarkDlg.height;
	imgTabBtnBk.top = imgRoomBottomLeftDlgBk.top;
	imgTabBtnBk.width = cx - imgTabBtnBk.left;
	imgTabBtnBk.height = 31;
	
	tabBtnMgr.visible = true;
	tabBtnMgr.left = imgTabBtnBk.left + 3 ;
	tabBtnMgr.top = imgTabBtnBk.top + 2;
	tabBtnMgr.width = 68;
	tabBtnMgr.height = 31;
	
	imgSeperator1.left = tabBtnMgr.left + tabBtnMgr.width;
	imgSeperator1.top = tabBtnMgr.top - 2;
	imgSeperator1.width = 2;
	imgSeperator1.height = tabBtnMgr.height;
	
	tabBtnUser.visible = true;
	tabBtnUser.left = tabBtnMgr.left + tabBtnMgr.width + 2;
	tabBtnUser.top = tabBtnMgr.top;
	tabBtnUser.width = tabBtnMgr.width;
	tabBtnUser.height = tabBtnMgr.height;
	
	imgSeperator2.left = tabBtnUser.left + tabBtnUser.width;
	imgSeperator2.top = imgSeperator1.top;
	imgSeperator2.width = imgSeperator1.width;
	imgSeperator2.height = imgSeperator1.height;
	
	tabBtnMicList.visible = true;
	tabBtnMicList.left = tabBtnUser.left + tabBtnUser.width + 2;
	tabBtnMicList.top = tabBtnUser.top;
	tabBtnMicList.width = 50;
	tabBtnMicList.height = tabBtnUser.height;
	
	imgSeperator3.left = tabBtnMicList.left + tabBtnMicList.width;
	imgSeperator3.top = imgSeperator2.top;
	imgSeperator3.width = imgSeperator2.width;
	imgSeperator3.height = imgSeperator2.height;
	
	btnIconInstruction.visible = true;
	btnIconInstruction.left = tabBtnMicList.left + tabBtnMicList.width + 2;
	btnIconInstruction.top = tabBtnMicList.top;
	btnIconInstruction.width = 30;
	btnIconInstruction.height = 31;
	
	btnSearch.visible = true;
	btnSearch.left = btnIconInstruction.left + btnIconInstruction.width + 8;
	btnSearch.top = tabBtnMicList.top  + 2;
	btnSearch.width = 16;
	btnSearch.height = 30;
	
	imgSearchDlgBk.visible = btnSearch.checked;
    imgSearchDlgBk.left = imgRoomBottomLeftDlgBk.left;
    imgSearchDlgBk.top = tabBtnMgr.top + tabBtnMgr.height - 2;
    imgSearchDlgBk.width = imgRoomBottomLeftDlgBk.width;
    imgSearchDlgBk.height = 37;
	btnWhereIAm.visible = btnSearch.checked;
	btnWhereIAm.width = 73;
	btnWhereIAm.height = 34;
	btnWhereIAm.left = imgSearchDlgBk.left + imgSearchDlgBk.width - 2 - btnWhereIAm.width;
	btnWhereIAm.top = imgSearchDlgBk.top + 2;	  
	itemSearchDlg.visible = btnSearch.checked;
	itemSearchDlg.left = imgSearchDlgBk.left + 1;
	itemSearchDlg.width = btnWhereIAm.left - itemSearchDlg.left;
	itemSearchDlg.height = 30;
	itemSearchDlg.top = imgSearchDlgBk.top + (imgSearchDlgBk.height - itemSearchDlg.height)/2;
	
  	userList.left = imgRoomBottomLeftDlgBk.left;
	userList.width = imgRoomBottomLeftDlgBk.width;
	if(btnSearch.checked)//打开查找
	{ 
	    userList.top = imgSearchDlgBk.top + imgSearchDlgBk.height;
		userList.height = itemSelfInfoAndSetDlg.top - userList.top;
	}
	else
	{
		searchList.visible = false;
		if(tabBtnMgr.checked)
		{
			managerList.visible = true;
		}
		if(tabBtnUser.checked)
		{
			userList.visible = true;
		}
		if(tabBtnMicList.checked)
		{
			micList.visible = true;
		}
		if(btnIconInstruction.checked)
		{
			agentList.visible = true;
		}
		userList.top = imgSearchDlgBk.top;
		userList.height = itemSelfInfoAndSetDlg.top - userList.top;
	}
	
	managerList.left = userList.left;
	managerList.top = userList.top;
	managerList.width = userList.width;
	managerList.height = userList.height;
	micList.left = userList.left;
	micList.top = userList.top;
	micList.width = userList.width;
	micList.height = userList.height;
	searchList.left = userList.left;
	searchList.top = userList.top;
	searchList.width = userList.width;
	searchList.height = userList.height;
	agentList.left = userList.left;
	agentList.top = userList.top;
	agentList.width = userList.width;
	agentList.height = userList.height;
}

function OnNotify(code, code1)
{
  switch(code)
  {
  case SKIN_NOTIFY_MARK_DLG:
        {
			itemSongMarkDlg.SetClient(code1);
        }
        break;
  case SKIN_NOTIFY_SELFINFOANDSET_DLG:
		{	
			itemSelfInfoAndSetDlg.SetClient(code1);
		}
		break;
    case SKIN_NOTIFY_SEARCH_DLG_HWND:
		{
		   itemSearchDlg.SetClient(code1);
		}
		break;
    case SKIN_NOTIFY_SEARCH_LIST:
		{
			if(0 == code1)
			{
				searchList.visible = false;
				if(tabBtnUser.checked)
				{
					userList.visible = true;
				}
				if(tabBtnMgr.checked)
				{
					managerList.visible = true;
				}
				if(tabBtnMicList.checked)
				{
					micList.visible = true;
				}
				if(btnIconInstruction.checked)
				{
					agentList.visible = true;
				}
				OnSize(Window.width,Window.height);
			}
			else
			{
			}
		}
		break;
    case SKIN_NOTIFY_SHOW_USERITEM:
		{
			if(0 == code1)
			{
				userList.visible = true;
				managerList.visible = false;
				micList.visible = false;
				searchList.visible = false;
				agentList.visible = false;
				tabBtnUser.labelNormalColor = "#0";
				tabBtnMgr.labelNormalColor = "#ffffff";
				tabBtnMicList.labelNormalColor = "#ffffff";
				tabBtnMgr.checked = false;
				tabBtnUser.checked = true;
				tabBtnMicList.checked = false;
				btnSearch.checked = false;
				OnSize(Window.width,Window.height);
			}
		}
		break;
  default:
		break;
  }
}
