Window.AttachEvent("OnFrameSize", OnFrameSize);

function OnFrameSize(cx, cy)
{
  /* *************************窗口风格相关************************* */
  /*背景*/
  imgFrameBackground.width = cx;
  imgFrameBackground.height = cy;
  imgFrameBackground.left = 0;
  imgFrameBackground.top = 0;

  imgBackgroundMid.visible = false;
  imgBackgroundMid.left = 2;
  imgBackgroundMid.top = 2;
  imgBackgroundMid.width = cx - 4;
  imgBackgroundMid.height = cy - imgBackgroundMid.top - 2;

  imgTopLeftBackground.left = 2;
  imgTopLeftBackground.top = 2;

  /*拖动标识*/
  imgDrag.visible = Window.resizable;
  imgDrag.left = cx - imgDrag.width - 4;
  imgDrag.top = cy - imgDrag.height - 4;

  /*系统按钮*/
  var sysBtnLeft = cx;
  var sysBtnTop = 2;
  var visibleNum = 0;
  var sysBtnShadowLeft = cx;
  var sysBtnShadowRight = 0;

  /* 只有关闭按钮时选择btnSysClose2 */
  // if ((!Window.maximizable) && (!Window.minimizable)) {
    // btnSysClose.skinClass = "btnSysClose2";
  // }

  if (btnSysClose.visible) {
    sysBtnLeft = sysBtnLeft - btnSysClose.width - 2;
    btnSysClose.left = sysBtnLeft;
    btnSysClose.top = sysBtnTop;
    visibleNum += 1;
    
    if (btnSysClose.left < sysBtnShadowLeft)
      sysBtnShadowLeft = btnSysClose.left;
    if ((btnSysClose.left + btnSysClose.width) > sysBtnShadowRight)
      sysBtnShadowRight = btnSysClose.left + btnSysClose.width;
  }

  btnSysMaximize.visible = Window.maximizable;
  if (btnSysMaximize.visible) {
    sysBtnLeft = sysBtnLeft - btnSysMaximize.width;
    btnSysMaximize.left = sysBtnLeft;
    btnSysMaximize.top = sysBtnTop;
    if (Window.IsZoomed()) {
      btnSysMaximize.skinClass = "btnSysRestore";
    } else {
      btnSysMaximize.skinClass = "btnSysMaximize";
    }
    visibleNum += 1;
    
    if (btnSysMaximize.left < sysBtnShadowLeft)
      sysBtnShadowLeft = btnSysMaximize.left;
    if ((btnSysMaximize.left + btnSysMaximize.width) > sysBtnShadowRight)
      sysBtnShadowRight = btnSysMaximize.left + btnSysMaximize.width;
  }

  btnSysMinimize.visible = Window.minimizable;
  if (btnSysMinimize.visible) {
    sysBtnLeft = sysBtnLeft - btnSysMinimize.width;
    btnSysMinimize.left = sysBtnLeft;
    btnSysMinimize.top = sysBtnTop;
    visibleNum += 1;
    
    if (btnSysMinimize.left < sysBtnShadowLeft)
      sysBtnShadowLeft = btnSysMinimize.left;
    if ((btnSysMinimize.left + btnSysMinimize.width) > sysBtnShadowRight)
      sysBtnShadowRight = btnSysMinimize.left + btnSysMinimize.width;
  }
  
  if(btnSysFeedback.visible)
  {
	sysBtnLeft = sysBtnLeft - btnSysFeedback.width;
    btnSysFeedback.left = sysBtnLeft;
    btnSysFeedback.top = sysBtnTop;
    visibleNum += 1;
    
    if (btnSysFeedback.left < sysBtnShadowLeft)
      sysBtnShadowLeft = btnSysFeedback.left;
    if ((btnSysFeedback.left + btnSysFeedback.width) > sysBtnShadowRight)
      sysBtnShadowRight = btnSysFeedback.left + btnSysFeedback.width;
  }

  imgSysBtnShadow.left = sysBtnShadowLeft + 6;
  imgSysBtnShadow.width = sysBtnShadowRight - sysBtnShadowLeft - 12;
  imgSysBtnShadow.top = sysBtnTop + btnSysClose.height;

  /*标题图标、文字*/
  
  imgTitleIcon.left = 6;
  imgTitleIcon.top = 4;


  textTitle.left = imgTitleIcon.left + imgTitleIcon.width + 1;
  textTitle.top = 9;
  textTitle.height = 18;
  textTitle.width = sysBtnLeft - textTitle.left - 3;
  /* *************************结束 窗口风格相关************************* */
}
