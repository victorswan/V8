#include "stdafx.h"
#include "HtmlOutPutManager.h"
#include "..\..\HTMLEdit\HtmlEditLogic.h"
#include "RoomModule.h"
#include "loudspeaker\SpeakerMsg.h"
#include "personalsetting\PersonalConfig.h"
#include "gift\GiftManager.h"
#include "..\CommonLibrary\include\utility\SystemHelper.h"
#include "..\CommonLibrary\include\utility\StringHelper.h"
#include "..\CommonLibrary\include\utility\URLEncode.h"
#include "Room.h"
#include "HallDefine.h"
#include "RoomParentDlg.h"
#include "sofa\SofaItem.h"

#define MAX_SHOW_179ID 999999

HtmlOutPutManager::HtmlOutPutManager( CRoomParentDlg* pParentDlg )
:m_pParentDlg( pParentDlg ),
m_HtmlBuild( pParentDlg->GetRoomBusiness() )
{

}

HtmlOutPutManager::~HtmlOutPutManager()
{
}

//至尊皇冠
void HtmlOutPutManager::OnEnterRoomGetUserList_VIPLevelTop( IUserItem* pUserIterm ) 
{
	CString strHtml = m_HtmlBuild.GetEnterRoomGetUserList_VIPLevelTop( pUserIterm ) ;
	if ( !strHtml.IsEmpty() )
	{
		m_pParentDlg->InsertPublicText( strHtml ) ;
	}
}

//钻石皇冠
void HtmlOutPutManager::OnEnterRoomGetUserList_VIPLevelDiamond(IUserItem* pUserItem)
{
	CString strHtml = m_HtmlBuild.GetEnterRoomGetUserList_VIPLevelDiamond( pUserItem );
	if ( !strHtml.IsEmpty() )
	{
		m_pParentDlg->InsertPublicText( strHtml ) ;
	}
}

void HtmlOutPutManager::OnEnterRoomGetUserList_GiftStar( IUserItem* pUserItem ) 
{
	OnShowGiftStar( pUserItem );
}

//冠用户
void HtmlOutPutManager::OnEnterRoomGetUserList_Crest( IUserItem* pUserItem ) 
{
	CString strHtml = m_HtmlBuild.GetEnterRoomGetUserList_Crest( pUserItem ) ;
	if ( !strHtml.IsEmpty() )
	{
		m_pParentDlg->InsertPublicText( strHtml ) ;
	}
}

void HtmlOutPutManager::OnEnterRoomGetUserList_Blink( IUserItem* pUserItem ) 
{
	CString strHtml = m_HtmlBuild.GetEnterRoomGetUserList_Blink( pUserItem ) ;
	if ( !strHtml.IsEmpty() )
	{
		m_pParentDlg->InsertPublicText( strHtml ) ;
	}
}

void HtmlOutPutManager::OnEnterRoomGetUserList_LuckyStar( IUserItem* pUserItem ) 
{
	CString strHtml = m_HtmlBuild.GetEnterRoomGetUserList_LuckyStar( pUserItem ) ;
	if ( !strHtml.IsEmpty() )
	{
		m_pParentDlg->InsertPublicText( strHtml ) ;
	}
}

void HtmlOutPutManager::OnEnterRoom( IUserItem * pUserItem ) 
{
	if (pUserItem->IsHideLogin())
	{
		return;
	}

	CString strHtml = m_HtmlBuild.GetEnterRoom( pUserItem ) ;
	if ( !strHtml.IsEmpty() )
	{
		m_pParentDlg->InsertPublicText( strHtml );
	}
}

void HtmlOutPutManager::OnLeaveRoom( uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	if ( pSrcUserItem->IsHideLogin())
	{
		return;
	}
	if ( pSrcUserItem->GetUserVipLevel() < core::VIPLEVEL_SILVER && 
		m_pParentDlg->GetRoomOption()->IsShowUserInOut() && !CPersonalConfig::GetInstance()->GetIsBlockUserInOutMsg()  )
	{
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetLeaveRoom( pSrcUserItem ) ) ;
	}
}

void HtmlOutPutManager::OnSendMsgSuccess( SendMessageEvent& message ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	CString strText = message.message.c_str() ;

	if ( message.enmType == SENDMESSAGETYPE_PUBLIC )
	{
		//公聊
		OnSendPublicMsgRsp( myCurInfo.unUIN , message.dstuin , strText , message.stFont ) ;		
	} 
	else if ( message.enmType == SENDMESSAGETYPE_PRIVATE)
	{
		if (!message.bIsAutoMsg)//自己发给别的人自动回复，自己不显示
		{
			OnPrivateMsg( myCurInfo.unUIN , message.dstuin , strText , message.stFont , false ) ;
		}
	}
	else if ( message.enmType == SENDMESSAGETYPE_TEMP_NOTICE )
	{
		OnTempNoticeMsg( myCurInfo.unUIN , L" "+CString(message.message.c_str()) , message.stFont ) ;
	}
}

void HtmlOutPutManager::OnSendPublicMsgRsp( uint32 srcuin , uint32 dstuin , CString& strText , MessageFont& stFont ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 
	if ( CPersonalConfig::GetInstance()->GetIsBlockPublicMsg() && myCurInfo.unUIN == dstuin )
	{
		//屏蔽公聊信息
		return ;
	}

	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = NULL ;
	if ( dstuin != 0 )
	{
		pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
		if ( pDstUserItem == NULL )
		{
			return ;
		}
	}

	//禁用词不会发出去，所以这里不需要过滤(假设客户端没有被破解)
	ProcessRecvMsgText( strText , false) ;	

	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetChat( pSrcUserItem , pDstUserItem ,strText , stFont , true , false ) ) ;

	if (pDstUserItem != NULL)
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetChat( pSrcUserItem , pDstUserItem ,strText , stFont , true , true , false) ) ;
	}
}

//公屏
void HtmlOutPutManager::OnPublicMsgNotify( uint32 srcuin , uint32 dstuin , CString& strText , MessageFont& stFont  ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 
	if ( CPersonalConfig::GetInstance()->GetIsBlockPublicMsg() && stFont.font_style != FONTSTYLETYPE_COLORTEXT )
	{
		//屏蔽公聊信息
		return ;
	}

	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = NULL ;
	if ( dstuin != 0 )
	{
		pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
		if ( pDstUserItem == NULL )
		{
			return ;
		}
	}
	ProcessRecvMsgText( strText ) ;
	if ( myCurInfo.unUIN == dstuin )
	{
		if ( stFont.font_style == FONTSTYLETYPE_COLORTEXT )
		{
			m_pParentDlg->FlashRoomWindow() ;
		}
		else
		{
			if ( m_pParentDlg->GetRoomBusiness()->IsBlockChat( srcuin ) )
			{
				//本人设置了禁止与他聊天
				return ;
			}
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetChat( pSrcUserItem , pDstUserItem ,strText , stFont , true , true ) ) ;
		}				
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetChat( pSrcUserItem , pDstUserItem , strText , stFont , true , false ) ) ;	

}

//私聊
void HtmlOutPutManager::OnPrivateMsg( uint32 srcuin ,uint32 dstuin , CString& strText , MessageFont& stFont , bool bNotify , bool bAutoMsg) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 
	if ( CPersonalConfig::GetInstance()->GetIsBlockPrivateMsg() && myCurInfo.unUIN == dstuin )
	{
		//屏蔽私聊信息
		return ;
	}

	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	if ( bNotify && m_pParentDlg->GetRoomBusiness()->IsBlockChat( srcuin ) )
	{
		//本人设置了禁止与他聊天
		return ;
	}

	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	
	//禁用词不会发出去，所以这里不需要过滤(假设客户端没有被破解)
	ProcessRecvMsgText( strText, false ) ;

	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetChat( pSrcUserItem , pDstUserItem ,strText , stFont , false , true , bAutoMsg) ) ;
}

//临时公告
void HtmlOutPutManager::OnTempNoticeMsg( uint32 srcuin , CString& strText , MessageFont& stFont ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	CString strTemp = common::utility::stringhelper::XMLEncode( strText.GetBuffer() ).c_str() ;
	ProcessRecvMsgText( strTemp ) ;	

	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetTempNotice( pSrcUserItem->GetUser179ID() , pSrcUserItem->GetDecodeUserName().c_str() , strTemp , stFont ) ) ;
}

void HtmlOutPutManager::OnWelecomeWords( RoomOption* pRoomOption ) 	//欢迎辞
{
	core::CurInfo myCurInfo = GetCurInfo() ;	
	CString strText = pRoomOption->GetWelcomeWords().c_str() ;
	if (myCurInfo.strName != L"")
	{
		strText.Replace(L"%nick" ,CString(myCurInfo.strName.c_str()) ) ;
	}
	else
	{
		CString strTempName = common::utility::stringhelper::IntToString(myCurInfo.un179id).c_str();
		strText.Replace(L"%nick" ,strTempName ) ;
	}
	
	strText.Replace( L"%room" , CString(pRoomOption->GetRoomName().c_str()) ) ;

	ProcessRecvMsgText( strText ) ;
	IUserItem* pOwnerItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserBy179ID( pRoomOption->GetOwner179ID() ) ;
	if ( pOwnerItem != NULL && pRoomOption->GetOwner179ID() != myCurInfo.un179id )
	{
		//房主在线时的欢迎辞
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetWelecomeWords(pOwnerItem , strText , pRoomOption->GetWelcomeFontInfo()) ) ;
	}
}

void HtmlOutPutManager::OnActorAutoSpeak(IUserItem* pUserItem)
{
	if (pUserItem == NULL)
	{
		return;
	}
	m_pParentDlg->InsertPrivateText(m_HtmlBuild.GetActorAutoSpeakWords(pUserItem, WelcomeMgr->GetActorSpeakRandom()));
}

void HtmlOutPutManager::OnAgentAutoSpeak(IUserItem* pUserItem)
{
	if (pUserItem == NULL)
	{
		return;
	}
	m_pParentDlg->InsertPrivateText(m_HtmlBuild.GetActorAutoSpeakWords(pUserItem, WelcomeMgr->GetAgentSpeakRandom()));
}

void HtmlOutPutManager::OnShowGiftStar(IUserItem* pUserItem) //礼物之星
{
	room_user_info* userInfo = pUserItem->GetUserInfo();
	vector<core::GiftStarInfo> vGiftStarInfoList = pUserItem->GetGiftStarInfo() ;
	vector<core::GiftStarInfo>::iterator iter ;
	for ( iter = vGiftStarInfoList.begin() ; iter != vGiftStarInfoList.end() ; ++iter )
	{
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetGiftStar(pUserItem,iter->unGiftID) );
	}
}

//房间公告,strText内含字体信息
void HtmlOutPutManager::OnNoticeMsg( CString& strText ) 
{
	ProcessRecvNoticeText( strText ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetNotice( strText ) );
}

//房间公告
void HtmlOutPutManager::OnNoticeMsg( CString& strText , MessageFont& stFont ) 
{
	ProcessRecvNoticeText( strText ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetNotice( strText , stFont ) ) ;
}

//官方公告
void HtmlOutPutManager::OnOfficialNocice( CString& strText ) 
{
	ProcessRecvNoticeText( strText ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetOfficialNocice(strText) ) ;
}

//不能公聊
void HtmlOutPutManager::OnSendMsg_NoPublic() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"管理员关闭了房间公聊！" , COLOR_OPERATE ) ) ;
}

//不能发送彩字
void HtmlOutPutManager::OnSendMsg_NoCaiZi() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"管理员关闭了房间彩字功能" , COLOR_OPERATE ) ) ;
}

//管理员称号变更
void HtmlOutPutManager::OnUserTitleChange( uint32 srcuin ,uint32 dstuin ,uint16 unTitle ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	if ( (pDstUserItem->GetUserTitleLevel() != core::TITLELEVEL_NONE && pDstUserItem->GetUserTitleLevel() != unTitle) 
		|| unTitle == core::TITLELEVEL_NONE )
	{
		//取消先前的管理称号
		CString strTemp ;		
		strTemp.Format( L"%s被 %s取消%s", GetNameAndID(pDstUserItem), GetNameAndID(pSrcUserItem) ,
			m_HtmlBuild.GetTitleName( pDstUserItem->GetUserTitleLevel()) ) ;

		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips(_T("【提示】： ") , strTemp , COLOR_OPERATE ) ) ;
	}
	if ( unTitle != core::TITLELEVEL_NONE )
	{
		//添加称号
		CString strTemp ;
		strTemp.Format( _T("%s添加 %s 成为%s") , GetNameAndID(pSrcUserItem) ,
			GetNameAndID(pDstUserItem) , m_HtmlBuild.GetTitleName( unTitle ) ) ;

		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips(_T("【提示】： ") , strTemp , COLOR_OPERATE ) ) ;
	}
}

//禁言
void HtmlOutPutManager::OnShutUpNotifyEvent( uint32 srcuin , uint32 dstuin , uint32 unLeftTime ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;
	if ( pDstUserItem->GetUserUIN() == myCurInfo.unUIN )
	{
		//自己被禁言
		if ( unLeftTime >= 60 )
		{
			strTemp.Format( L"您已被管理员禁言%d分钟" , unLeftTime/60 ) ;
		}
		else
		{
			strTemp.Format( L"您已被管理员禁言%d秒" , unLeftTime ) ;
		}
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips(_T("【提示】： ") , strTemp , COLOR_OPERATE ) ) ;
	}			
	strTemp.Format( _T("%s已禁止%s在本房间内发言") ,GetNameAndID(pSrcUserItem) ,GetNameAndID(pDstUserItem) ) ;
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips(_T("【提示】： ") ,strTemp , COLOR_OPERATE ) );
}

//发送消息太快
void HtmlOutPutManager::OnSendMsgRsp_Fast() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips(_T("【警告】： ") , _T("您的发言过于频繁,请稍作休息") , COLOR_OPERATE ) ) ;
}

//公聊被禁止
void HtmlOutPutManager::OnSendMsgRsp_PublicForbid() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips(_T("【提示】： ") , _T("管理员禁止房间公聊") , COLOR_OPERATE ) ) ;
}

//彩条被禁止
void HtmlOutPutManager::OnSendMsgRsp_CaiZiForbid() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , _T("彩字被禁止") , COLOR_OPERATE ) ) ;
}

//用户被禁言
void HtmlOutPutManager::OnSendMsgRsp_UsrForbid( uint32 unLeftTime ) 
{
	CString strTemp ;
	if ( unLeftTime >= 60 )
	{
		strTemp.Format( L"您已被禁言，还有%d分钟才能发言" , unLeftTime/60 ) ;
	}
	else
	{
		strTemp.Format( L"您已被禁言，还有%d秒才能发言" , unLeftTime ) ;
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , strTemp , COLOR_OPERATE ) ) ;
}

//无权限
void HtmlOutPutManager::OnSendMsgRsp_NoPermission() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , _T("您没有权限") , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnSendMsgRsp_PublicVip() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"本房间只有VIP以上用户才能公聊" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnSendMsgRsp_PublicReg() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"本房间注册用户才能公聊" , COLOR_OPERATE ) ) ;
}

//金币不足
void HtmlOutPutManager::OnNotEnoughGold() 
{	 
	CString strTemp;
	strTemp.Format( L"您的余额不足 <a href=\"%s\" target=\"_blank\">请充值</a>" , m_pParentDlg->GetRoomBusiness()->GetRoomPayUrl() ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp ,COLOR_OPERATE) );
}

//禁止重复发言
void HtmlOutPutManager::OnNotRepeat() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , _T("重复发言不能超过3次！") , COLOR_OPERATE ) ) ;
}

//聊天信息为空
void HtmlOutPutManager::OnMsgEmpty() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"请输入聊天内容" , COLOR_OPERATE ) ) ;
}

//复制房间地址
void HtmlOutPutManager::OnCopyRoomUrl()
{
	CString strCopyData;
	strCopyData.Format(L"我觉得这个视频聊天室还不错，快去看看吧!   %s", m_pParentDlg->GetRoomBusiness()->GetCopyRoomUrl()); 
	common::utility::systemhelper::CopyDataToClipbord(strCopyData.GetBuffer());
	m_pParentDlg->InsertPrivateText(m_HtmlBuild.GetPrivateTips(_T("【提示】： "), _T("您已复制该房间地址，快快发送给好友吧！") , COLOR_OPERATE ));
}

//彩字发送间隔未满10秒
void HtmlOutPutManager::OnNotCaiZiTime( core::ENM_VipLevel nVipLevel ,uint32 nLeftTime ) 
{
	if ( nVipLevel == core::VIPLEVEL_NONE || nVipLevel == core::VIPLEVEL_TOP )
	{
		return ;
	}
	else if ( nVipLevel == core::VIPLEVEL_REGISTER )
	{
		CString strTemp ;
		strTemp.Format( L"刷彩条的时间间隔为%d秒,现在还有%d秒,升级VIP大幅缩减间隔时间 <a href=\"%s\" target=\"_blank\">立即升级</a>" ,
			m_pParentDlg->GetRoomBusiness()->GetCaiZiIntervalTime( nVipLevel ) ,nLeftTime ,m_pParentDlg->GetRoomBusiness()->GetUpdateVipUrl() ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , strTemp , COLOR_OPERATE) ) ;
	}
	else 
	{
		CString strTemp ;
		strTemp.Format( L"刷彩条时间间隔为%d秒，现在还有%d秒" ,m_pParentDlg->GetRoomBusiness()->GetCaiZiIntervalTime( nVipLevel ) , nLeftTime ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , strTemp , COLOR_OPERATE ) ) ;
	}
}

void HtmlOutPutManager::OnPublicChatChange( ENM_RoomPublicChat enmType , uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ;
	CString strTemp ;
	if ( enmType == PUBLICCHAT_ABOVE_REGISTER )
	{
		strTemp.Format( L"%s允许所有注册用户在本房间公聊" , GetNameAndID(pSrcUserItem) ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) );		 
		if ( myCurInfo.unUIN == srcuin )
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPublicTips( L"【提示】： " , L"您已允许所有注册用户在本房间公聊" , COLOR_OPERATE ) );
		}		
	}
	else if ( enmType == PUBLICCHAT_ABOVE_VIP )
	{
		strTemp.Format( L"%s允许VIP以上用户在本房间公聊" , GetNameAndID(pSrcUserItem) ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) );
		if ( myCurInfo.unUIN == srcuin )
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPublicTips( L"【提示】： " , L"您已允许VIP以上用户在房间公聊" , COLOR_OPERATE ) );
		}
	}	
}

void HtmlOutPutManager::OnColorTextChange( bool bColorText , uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;
	if ( bColorText )
	{				
		strTemp.Format( L"%s开启房间彩字功能" , GetNameAndID(pSrcUserItem) ) ;

	}
	else
	{
		strTemp.Format( L"%s关闭房间彩字功能" , GetNameAndID(pSrcUserItem) ) ;
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) );
}

//自由排麦
void HtmlOutPutManager::OnFreeShowChange( bool bFreeShow , uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;
	if ( bFreeShow )
	{				
		strTemp.Format( L"%s开启了房间自由排麦功能" , GetNameAndID(pSrcUserItem) ) ;
	}
	else
	{
		strTemp.Format( L"%s关闭了房间自由排麦功能" , GetNameAndID(pSrcUserItem) ) ;
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) );
}

//房间主题
void HtmlOutPutManager::OnSignatureChange( std::wstring& strSignature ) 
{
	CString strSignatureTemp = strSignature.c_str() ;
	ProcessRecvMsgText( strSignatureTemp ) ;
}

void HtmlOutPutManager::SetPublicSheChiGift( uint32 srcuin ,uint32 dstuin ,uint16 unGiftID ,uint32 unCount  ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 

	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicSheChiGift( pSrcUserItem , pDstUserItem , unGiftID ,unCount) ) ;
}

//收到礼物时，输出到公屏区
void HtmlOutPutManager::SetPublicNormalGift( GiftInfo& giftinfo, bool reallyOutput) 
{
	//礼物计数，不能少
	uint32 unGiftCount = m_pParentDlg->GetGiftBaseListCount( giftinfo.dstuin , giftinfo.unGiftid ) ;

	if(!reallyOutput)
	{
		return;
	}
	
	//"加速"模式时，过滤跟自己无关的刷礼物
	if(g_RoomModule->IsSpeedUpMode())
	{
		core::CurInfo info = GetCurInfo();
		if(giftinfo.dstuin != info.unUIN && giftinfo.srcuin != info.unUIN)
		{
			return;
		}
	}

	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicNormalGift( giftinfo , unGiftCount ) ) ;
}

//自己收到礼物时，输出到私聊区
void HtmlOutPutManager::SetPrivateNormalGift( uint32 srcuin , uint32 dstuin ,uint16 unGiftID , uint16 unCount ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 
	if ( myCurInfo.unUIN != dstuin || myCurInfo.unUIN == srcuin )
	{
		return ;
	}
	if(myCurInfo.enmVIPLevel == VIPLEVEL_NONE )
	{
		return ;
	}
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateNormalGift( pSrcUserItem , unGiftID ,unCount) ) ;
}

void HtmlOutPutManager::SetPrivateFireWork( uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateFireWork( pSrcUserItem ) ) ;
}

void HtmlOutPutManager::SetPrivateSlavo( uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateSlavo(pSrcUserItem) ) ;
}

void HtmlOutPutManager::OnSendGift_NotExist() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"道具不存在" , COLOR_OPERATE ) );
}

void HtmlOutPutManager::OnSendGift_CanNotSend( uint16 unGiftID ) 
{
	if ( GiftManager::GetInstance()->IsFirework(unGiftID) )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"赠送失败，当前房间无管理员" , COLOR_OPERATE ) );
	}	
	else
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"赠送失败，当前房间无赠送对象" , COLOR_OPERATE ) );
	}
}

void HtmlOutPutManager::OnSendGift_CanNotSendToVisitor( core::ENM_GiftType enmType ) 
{
	switch( enmType )
	{
	case core::GIFTTYPE_NORMAL:
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"不能给游客赠送礼物" , COLOR_OPERATE ) );
		}
		break;
	case core::GIFTTYPE_STAMP:
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"不能对游客使用道具" , COLOR_OPERATE ) );
		}
		break;
	case  core::GIFTTYPE_SHECHI:
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"不能给游客赠送礼物" , COLOR_OPERATE ) );
		}
		break;
	case core::GIFTTYPE_CHANGEVOICE:
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"不能对游客使用道具" , COLOR_OPERATE ) );
		}
		break;
	default: break;
	}
}

void HtmlOutPutManager::OnSendGift_CanNotSendToManage( ) 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"不能对官方人员使用此道具" , COLOR_OPERATE ) );
}

void HtmlOutPutManager::OnPublicGiftTip( uint32 srcuin , uint16 unGiftID , core::ENM_GiftDstType enmDstType ) 
{
	if ( CPersonalConfig::GetInstance()->GetIsBlockGiftMsg() )
	{
		return ;
	}
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unGiftID ) ;
	if ( pGiftItem == NULL )
	{
		return ;
	}
	CString strTemp ;
	if ( GiftManager::GetInstance()->IsFirework( unGiftID ) )
	{
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicFireWork( pSrcUserItem ) ) ;
		m_pParentDlg->FlashRoomWindow() ;
	}
	else if ( GiftManager::GetInstance()->IsSalute(unGiftID) )
	{
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicSlavo( pSrcUserItem ) ) ;
		m_pParentDlg->FlashRoomWindow() ;
	}
	else
	{
		if ( enmDstType == core::GIFTDSTTYPE_MANAGER )
		{
			strTemp.Format( L"%s赠予房间所有管理员每人一%s%s" , GetNameAndID(pSrcUserItem) ,pGiftItem->GetUnitName().c_str() , pGiftItem->GetName().c_str() ) ;
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp ,COLOR_GIFT) ) ;
		}
		else if ( enmDstType == core::GIFTDSTTYPE_ALL )
		{
			strTemp.Format( L"%s赠予房间内每人一%s%s" , GetNameAndID(pSrcUserItem) , pGiftItem->GetUnitName().c_str() , pGiftItem->GetName().c_str() ) ;
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp ,COLOR_GIFT) ) ;
		}
	}
}

//购买闪亮登场道具成功
void HtmlOutPutManager::OnLinkEnterGift(uint16 unGiftID) 
{
	IGiftItem * pGiftItem = GiftManager::GetInstance()->SearchBlinkEnterByID(unGiftID);
	if (pGiftItem != NULL)
	{
		CString strTemp;
		strTemp.Format(L"购买成功，下次进入房间即可享有%s效果", pGiftItem->GetName().c_str());
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE) ) ;
	}
}

//奢侈道具礼物(notify)
void HtmlOutPutManager::OnPaodaoSheChiGift(core::SendGiftNotifyEvent* pInfo) 
{
	m_pParentDlg->InsertPaoDaoText( pInfo->strSrcName.c_str() , pInfo->strDstName.c_str() , pInfo->strAttachMessage.c_str() ,pInfo->unSrc179ID , 
		pInfo->unDst179ID , pInfo->unGiftID , pInfo->unSentCount ,m_HtmlBuild.GetGiftDateString(pInfo->unTime) ) ;

	if (pInfo->bAttachFlyEffect)
	{
		m_pParentDlg->GetEffectManager()->ProcessFlyLuxury(pInfo->strSrcName.c_str(), pInfo->strDstName.c_str(), pInfo->unSrc179ID, pInfo->unDst179ID, pInfo->unGiftID, pInfo->unSentCount);
	}	
}

//奢侈道具礼物(rsp)
void HtmlOutPutManager::OnPaodaoSheChiGift( uint32 srcuin , uint32 dstuin ,std::wstring strGiftWord ,uint16 unGiftID , uint16 unCount , uint32 unTime ) 
{	
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}

	m_pParentDlg->InsertPaoDaoText( 
		pSrcUserItem->GetUserName().c_str(),pDstUserItem->GetUserName().c_str(),strGiftWord.c_str(), pSrcUserItem->GetUser179ID() ,
		pDstUserItem->GetUser179ID() ,unGiftID , unCount , m_HtmlBuild.GetGiftDateString( unTime ) ) ;;

	m_pParentDlg->GetEffectManager()->ProcessFlyLuxury(pSrcUserItem->GetUserName().c_str(), pDstUserItem->GetUserName().c_str(), pSrcUserItem->GetUser179ID(), pDstUserItem->GetUser179ID(), unGiftID, unCount);
}

//财神到
void HtmlOutPutManager::OnNotifyPlutusAward( uint32 srcuin , uint32 un179ID , std::wstring& strName ,
											std::wstring strRoomName ,std::vector<uint16>& vecMoneys  , uint16 unGiftID ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 
	IUserItem* pSelfUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
	if ( pSelfUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.OnNotifyPlutusAward( srcuin,un179ID ,strName , 
		strRoomName ,pSelfUserItem->GetUserTitleLevel() , vecMoneys.size() , unGiftID ) ) ;
}


void HtmlOutPutManager::OnUserStampChangeRsp( uint32 unDstUIN, uint16 unStampID) 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicStamp( pSrcUserItem , pDstUserItem , unStampID ) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateStampRsp( pDstUserItem, unStampID ) ) ;
}

//盖章
void HtmlOutPutManager::OnUserStampChangeNotify( uint32 unSrcUIN , uint32 unDstUIN, uint16 unStampID ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.unUIN == unDstUIN )
	{
		//别人给我盖了章
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateStamp( pSrcUserItem ,unStampID) ) ;
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicStamp( pSrcUserItem , pDstUserItem , unStampID ) ) ;
}

void HtmlOutPutManager::OnRequestShow_WaitingList( bool freeshow_opened ) 
{
	RoomOption *pRoomOption = m_pParentDlg->GetRoomOption() ;
	if ( pRoomOption != NULL )
	{
		if ( pRoomOption->GetPublicMicStatus(1) == PUBLIC_MIC_STATUS_CLOSE && 
			pRoomOption->GetPublicMicStatus(2) == PUBLIC_MIC_STATUS_CLOSE && 
			pRoomOption->GetPublicMicStatus(3) == PUBLIC_MIC_STATUS_CLOSE )
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"抱歉，当前房间视频窗口已被室主关闭" , COLOR_OPERATE ) ) ;
			return ;
		}
		else
		{
			OnRequestShow_Success() ;
			return ;
		}
	}	

	if ( !freeshow_opened )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"该房间关闭了自由排麦功能" , COLOR_OPERATE ) ) ;
	}
}

//请求排麦失败
void HtmlOutPutManager::OnRequestShow_Failed( core::ENM_RequestShowResult nResult ) 
{
	switch( nResult )
	{
	case REQUESTSHOWRESULT_FULL:		//麦已满
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , _T("排麦人数已满，请稍后再试") , COLOR_OPERATE ) ) ;
		}
		break;
	case REQUESTSHOWRESULT_PRIVATE_CLOSED: //房间私麦已关闭
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , _T("房间私麦已关闭，请向室主要求开放此功能") , COLOR_OPERATE ) ) ;
		}
		break;
	case REQUESTSHOWRESULT_FAIL:		//排麦失败
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , _T("排麦失败") , COLOR_OPERATE ) ) ;
		}
		break;
	default:break ;
	}
}

void HtmlOutPutManager::OnRequestShow_Already_OnShow() 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	IUserItem* pSelfUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem() ;
	if ( pSelfUserItem != NULL )
	{
		if ( pSelfUserItem->GetUserStatus()&core::USERSTATUSTYPE_P2P )
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"抱歉，您正在一对一视频中" , COLOR_OPERATE ) ) ;
		}
	}
}


//自己排上公麦
void HtmlOutPutManager::OnRequestShow_Public( uint8 unIndex  ) 
{
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	if ( unIndex>=1 && unIndex<=3 )
	{
		//core::CurInfo myCurInfo = GetCurInfo() ;		
		CString strTemp ;
		CString strNameAndID;
		if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
		{
			strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
		}
		else
		{
			strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str() , pMyUserItem->GetUser179ID());
		}
		strTemp.Format( L"%s成为主持人" , strNameAndID ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp, COLOR_OPERATE ) ) ;		
	}
}

void HtmlOutPutManager::OnRequestShow_PublicNotify( uint32 unSrcUIN ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}	
	CString strTemp ;
	strTemp.Format( L"%s成为主持人" ,GetNameAndID(pSrcUserItem) ) ;
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) );
}


//排上私麦
void HtmlOutPutManager::OnRequestShow_Private( ) 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"您已上私麦，荣耀VIP以上用户可观看" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnRequestShow_PrivateNotify( uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateMicNotify( pSrcUserItem ) );
}

void HtmlOutPutManager::OnRequestShow_InOtherRoom() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", L"请求失败，您已在其他房间麦上" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnRequestShow_WaitButOnMic( uint32 srcuin ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.unUIN == srcuin )
	{
		IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
		if ( pSrcUserItem == NULL )
		{
			return ;
		}
		if ( pSrcUserItem->GetUserStatus()&USERSTATUSTYPE_P2P )
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", L"您正在进行一对一视频，系统已为您跳过麦序", COLOR_OPERATE ) ) ;
		}
		else
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", L"抱歉，您已在其他房间公麦上", COLOR_OPERATE ) ) ;
		}
	}	
}

void HtmlOutPutManager::OnRequestShow_WaitingOnMic() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", L"请求失败，您已在其他房间麦上" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnRequestShow_Success() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", L"排麦成功" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnExitShowSelf( IUserItem *pUserItem  ) //自己下麦
{
	if ( IsPublicMic( pUserItem->GetUserStatus() ) )
	{
		CString strTemp ;		
		strTemp.Format(_T("%s停止主持节目") , GetNameAndID(pUserItem) );
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips(_T("【提示】： ") ,strTemp , COLOR_OPERATE ) );
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"您已下麦" , COLOR_OPERATE ) ) ;
	}
}

void HtmlOutPutManager::OnExitShowNotify( uint32 unSrcUIN , int nType ) 
{
	if ( nType == EXIT_SHOW_OTHER )
	{
		IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
		if ( pSrcUserItem == NULL )
		{
			return ;
		}
		if ( IsPublicMic( pSrcUserItem->GetUserStatus() ) )
		{
			CString strTemp ;
			strTemp.Format( L"%s停止主持节目" ,GetNameAndID(pSrcUserItem) ) ;
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) );
		}
	}
}

void HtmlOutPutManager::OnExitP2P( uint32 unUIN ) 
{
	IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unUIN ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ;	
	if ( myCurInfo.unUIN == unUIN )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"您结束了此次一对一视频" , COLOR_OPERATE ) ) ;
	}
	else
	{
		CString strTemp ;		
		strTemp.Format( L"%s结束了此次一对一视频" , GetNameAndID(pUserItem) ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}	
}

void HtmlOutPutManager::OnKickOutRsp( uint32 unDstUIN ) 
{
	IUserItem* pDecUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDecUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	//core::CurInfo myCurInfo = GetCurInfo() ;
	CString strTemp ;
	CString strNameAndID;
	if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str() , pMyUserItem->GetUser179ID());
	}
	strTemp.Format( L"%s被%s踢出房间", GetNameAndID(pDecUserItem) , strNameAndID );
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnKickOutNotify( uint32 srcuin , uint32 unDstUIN ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDecUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDecUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;		
	strTemp.Format( L"%s被%s踢出房间", GetNameAndID(pDecUserItem) ,GetNameAndID(pSrcUserItem) );
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnAddBlackNotify( uint32 unSrcUIN , uint32 unDstUIN ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDecUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDecUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;		
	strTemp.Format( L"%s已将%s加入黑名单"  ,GetNameAndID(pSrcUserItem) , GetNameAndID(pDecUserItem) );
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnLockIpNotify( uint32 unSrcUIN , uint32 unDstUIN ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDecUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDecUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;		
	strTemp.Format( L"%s已将%s踢出本房间" , GetNameAndID(pSrcUserItem) , GetNameAndID(pDecUserItem) );
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
}

//对方没有私麦打开
void HtmlOutPutManager::OnOpenPrivateRsp_NotOpen() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,_T("该用户未上私麦，无法观看") , COLOR_OPERATE ) );
}

//无权限
void HtmlOutPutManager::OnOpenPrivateRsp_NotPermission() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetOpenPrivateRspNoPermission() ) ;
}


//当前打开的私麦已达上限
void HtmlOutPutManager::OnOpenPrivateRsp_ISFull() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetOpenPrivateRspIsFull() ) ;
}

//已经打开过了
void HtmlOutPutManager::OnOpenPrivateRsp_AlreadyOpened() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") ,_T("您已经打开了此用户的私麦") , COLOR_OPERATE ) );
}

//是自己
void HtmlOutPutManager::OnOpenPrivateRsp_IsSelf()
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") ,_T("您已在私麦上") , COLOR_OPERATE ) );
}

//邀请上麦成功
void HtmlOutPutManager::OnPushOnShowRsp_Success( uint32 dstuin ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	CString strTemp ;
	//core::CurInfo myCurInfo = GetCurInfo() ;
	CString strNameAndID;
	if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str() ,pMyUserItem->GetUser179ID());
	}
	if ( pMyUserItem->GetUserUIN() == dstuin )
	{
		strTemp.Format( L"%s成为主持人" , strNameAndID ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) );
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"您已成功上麦" , COLOR_OPERATE ) );
	}
	else
	{
		strTemp.Format( L"您已成功邀请%s上麦" , GetNameAndID(pDstUserItem) ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;

		strTemp.Format( L"%s被%s邀请上麦" , GetNameAndID(pDstUserItem)  , strNameAndID );
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) );
	}
}

void HtmlOutPutManager::OnPushOnShowRsp_Failed( uint32 dstuin ) 			   //邀请上麦
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	if ( pMyUserItem->GetUserUIN() == dstuin )
	{
		if ( pMyUserItem->GetUserStatus()&core::USERSTATUSTYPE_P2P )
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"上麦失败，您正在进行一对一视频" , COLOR_OPERATE ) ) ;
		}
		else if ( pMyUserItem->GetUserStatus()&core::USERSTATUSTYPE_PRIVATE)
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"上麦失败，您正在私麦上" , COLOR_OPERATE ) ) ;
		}
		else if( IsPublicMic(pMyUserItem->GetUserStatus()))
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"上麦失败，您正在公麦上" , COLOR_OPERATE ) ) ;
		}
	}
	else
	{
		if ( pDstUserItem->GetUserStatus()&core::USERSTATUSTYPE_P2P )
		{
			CString strTemp ;		
			strTemp.Format( L"邀请失败，%s正在进行一对一视频" , GetNameAndID(pDstUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		else if ( pDstUserItem->GetUserStatus()&core::USERSTATUSTYPE_PRIVATE)
		{
			CString strTemp ;		
			strTemp.Format( L"邀请失败，%s正在私麦上" , GetNameAndID(pDstUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		else if( IsPublicMic(pDstUserItem->GetUserStatus()))
		{
			CString strTemp ;		
			strTemp.Format( L"邀请失败，%s正在公麦上" , GetNameAndID(pDstUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
	}
}

void HtmlOutPutManager::OnPushOnShowRsp_MicLocked() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"此麦序已被限制使用，请向室主请求取消限制" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnPullOffShowRsp_Success( uint32 unDstUIN ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}	
	CString strTemp ;
	strTemp.Format( L"您已取消了%s主持的节目"  , GetNameAndID(pDstUserItem) ) ;
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnPullOffShowRsp_Failed() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"抱歉，该用户不在麦上" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnPushOnShowNotify( uint32 srcuin , uint32 dstuin , uint8 unIndex ) 
{
	//邀请者，可能不在房间
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	//if ( pSrcUserItem == NULL )
	//{
	//	return ;
	//}
	//被邀请者
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( srcuin == dstuin )
	{		
		strTemp.Format( L"%s成为主持人" , GetNameAndID(pDstUserItem) ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
	}
	else
	{
		if ( myCurInfo.unUIN == dstuin )                                                                                    
		{
			if (pSrcUserItem != NULL)
			{
				strTemp.Format( L"您已被%s邀请上麦" , GetNameAndID(pSrcUserItem) ) ;
				m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
			}
			else
			{
				m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"您已成功上麦" , COLOR_OPERATE ) ) ;
			}

		}
		else if ( myCurInfo.unUIN == srcuin)
		{
			strTemp.Format( L"您已成功邀请%s上麦" , GetNameAndID(pDstUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
		}

		if (pSrcUserItem != NULL)
		{
			strTemp.Format( L"%s被%s邀请上麦" , GetNameAndID(pDstUserItem) , GetNameAndID(pSrcUserItem) );
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		else
		{
			strTemp.Format( L"%s成为主持人" , GetNameAndID(pDstUserItem) ) ;
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
		}
	}
}

void HtmlOutPutManager::OnPuffOffShowNotify( uint32 unSrcUIN ,uint32 unDstUIN )
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.unUIN == unDstUIN )
	{
		CString strTemp ;		
		strTemp.Format( L"您被%s取消了主持的节目" , GetNameAndID(pSrcUserItem) ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
	else
	{
		CString strTemp ;		
		strTemp.Format( L"%s取消了%s主持的节目" , GetNameAndID(pSrcUserItem) ,GetNameAndID(pDstUserItem) );
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
}

void HtmlOutPutManager::OnSetMicStatusRsp( int nIndex , int nStatus  ) 
{
	if ( nIndex >= 1 && nIndex <= 3 )
	{
		CString strTemp ;
		if ( nStatus == PUBLIC_MIC_STATUS_OPEN )
		{
			strTemp.Format( L"您开启了%s麦窗口" , MicChineseIndex( nIndex) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) );
		}
		else
		{
			strTemp.Format( L"您关闭了%s麦窗口" , MicChineseIndex( nIndex) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) );

			uint32 unDstUIN = m_pParentDlg->GetPulicMicUINByIndex( nIndex ) ;
			IUserItem* pDstUserItem = NULL ;
			if ( unDstUIN != 0 )
			{
				pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ; 
			}			
			//core::CurInfo myCurInfo = GetCurInfo() ;
			IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();

			CString strNameAndID;
			if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
			{
				strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
			}
			else
			{
				strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str() , pMyUserItem->GetUser179ID());
			}

			if ( unDstUIN != 0 && pDstUserItem != NULL )
			{								
				strTemp.Format( L"%s取消了%s主持的节目" , strNameAndID , GetNameAndID(pDstUserItem) );
				m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
			}

			strTemp.Format( L"%s关闭了%s麦窗口" ,strNameAndID ,MicChineseIndex( nIndex) ) ;
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;

		}
	}
}

void HtmlOutPutManager::OnSetMicStatusNotify( int nIndex , int nStatus , uint32 srcuin ) 
{
	if ( nIndex >= 1 && nIndex <= 3 )
	{
		CString strTemp ;
		if (nStatus == PUBLIC_MIC_STATUS_CLOSE )
		{
			uint32 unDstUIN = m_pParentDlg->GetPulicMicUINByIndex( nIndex ) ;
			IUserItem* pDstUserItem = NULL ;
			if ( unDstUIN != 0 )
			{
				pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ; 
			}
			IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
			if ( unDstUIN != 0 && pDstUserItem != NULL && pSrcUserItem != NULL )
			{							
				strTemp.Format( L"%s取消了%s主持的节目" , GetNameAndID(pSrcUserItem), GetNameAndID(pDstUserItem) );
				m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
				core::CurInfo myCurInfo = GetCurInfo() ;
				if ( myCurInfo.unUIN == unDstUIN )
				{
					m_pParentDlg->FlashRoomWindow() ;
				}
			}
			if ( pSrcUserItem != NULL )
			{				
				strTemp.Format( L"%s关闭了%s麦窗口" , GetNameAndID(pSrcUserItem) , MicChineseIndex(nIndex) ) ;
				m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
			}
		}
	}
}

void HtmlOutPutManager::OnRequestP2PRspOK( uint32 dstuin ) 
{
	IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}	
	CString strTemp ;
	strTemp.Format( L"您邀请%s进行一对一视频" , GetNameAndID(pUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnRequestP2PNotify(  uint32 unSrcUIN ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetRequestP2PNotify( pSrcUserItem ) ) ;
}

void HtmlOutPutManager::OnRequestP2PRspFailed( uint32 nResult , uint32 dstuin  ) 
{
	IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	switch( nResult )
	{
	case core::CONNECTP2PRESULT_SELF_ON_PUBLIC://自己已经在公麦上
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"邀请失败，您已在公麦上" , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_SELF_ON_PRIVATE://自己已经在私麦上
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"邀请失败，您已在私麦上" , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_SELF_ON_P2P://自己已经在1v1中
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"邀请失败，您正在进行一对一视频" , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_ON_PUBLIC://对方已经在公麦上
		{
			CString strTemp ;			
			strTemp.Format( L"邀请失败，%s正在公麦上" , GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_ON_PRIVATE://对方已经在私麦上
		{
			CString strTemp ;			
			strTemp.Format( L"邀请失败，%s正在私麦上" , GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_ON_P2P://对方已经在1v1中
		{
			CString strTemp ;			
			strTemp.Format( L"邀请失败，%s正在进行一对一视频" ,GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_NEED_VIP://对方只接受vip以上的
		{
			CString strTemp ;			
			strTemp.Format( L"抱歉！%s只接受VIP以上用户的私聊请求" , GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_NEED_KING://对方只接受皇冠以上的
		{
			CString strTemp ;			
			strTemp.Format( L"抱歉！%s只接受皇冠以上用户的私聊请求" , GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_CLOSE://对方设置了拒绝1v1
		{
			CString strTemp ;			
			strTemp.Format( L"抱歉！%s拒绝所有用户的私聊请求" , GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	default:break;
	}
}

void HtmlOutPutManager::OnResponseP2PRspFailed( uint32 nResult , uint32 dstuin  , ENM_ResponseP2PType enmType ) 
{
	IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	switch( nResult )
	{
	case core::CONNECTP2PRESULT_SELF_ON_PUBLIC://自己已经在公麦中
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"邀请失败，您已在公麦上" , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_SELF_ON_PRIVATE://自己已经在私麦上
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"邀请失败，您已在私麦上" , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_SELF_ON_P2P://自己已经在1v1中
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"邀请失败，您正在进行一对一视频" , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_ON_PUBLIC://对方已经在公麦中
		{
			CString strTemp ;	
			if ( enmType == core::RESPONSEP2PTYPE_ACCEPT )
			{
				strTemp.Format( L"连接失败，%s正在公麦上" , GetNameAndID(pUserItem) ) ;
			}
			else
			{
				strTemp.Format( L"邀请失败，%s正在公麦上" , GetNameAndID(pUserItem) ) ;
			}
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_ON_PRIVATE://对方已经在私麦上
		{
			CString strTemp ;
			if ( enmType == core::RESPONSEP2PTYPE_ACCEPT )
			{
				strTemp.Format( L"连接失败，%s正在私麦上" , GetNameAndID(pUserItem) ) ;
			}
			else
			{
				strTemp.Format( L"邀请失败，%s正在私麦上" , GetNameAndID(pUserItem) ) ;
			}
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_ON_P2P://对方已经在1v1中
		{
			CString strTemp ;		
			if ( enmType == core::RESPONSEP2PTYPE_ACCEPT )
			{
				strTemp.Format( L"连接失败，%s正在进行一对一视频" ,GetNameAndID(pUserItem) ) ;
			}
			else
			{
				strTemp.Format( L"邀请失败，%s正在进行一对一视频" ,GetNameAndID(pUserItem) ) ;
			}
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_NEED_VIP://对方只接受vip以上的
		{
			CString strTemp ;			
			strTemp.Format( L"抱歉！%s只接受VIP以上用户的私聊请求" , GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_NEED_KING://对方只接受皇冠以上的
		{
			CString strTemp ;			
			strTemp.Format( L"抱歉！%s只接受皇冠以上用户的私聊请求" , GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	case core::CONNECTP2PRESULT_OTHER_CLOSE://对方设置了拒绝1v1
		{
			CString strTemp ;			
			strTemp.Format( L"抱歉！%s拒绝所有用户的私聊请求" , GetNameAndID(pUserItem) ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		break;
	default:break;
	}
}

void HtmlOutPutManager::OnResponseP2PRspAccept( uint32 dstuin ) //自己接受
{
	IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;	
	strTemp.Format( L"您接受与%s一对一视频" , GetNameAndID(pUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) );
}

void HtmlOutPutManager::OnResponseP2PRspRefuse( uint32 dstuin ) //自己拒绝
{
	IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;	
	strTemp.Format( L"您拒绝与%s一对一视频" , GetNameAndID(pUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) );
}

void HtmlOutPutManager::OnResponseP2PNotifyAccept( uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;	
	strTemp.Format( L"%s已接受与您一对一视频" , GetNameAndID(pSrcUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnResponseP2PNotifyRefuse( uint32 srcuin ) 
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( srcuin ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;	
	strTemp.Format( L"%s拒绝与您一对一视频" , GetNameAndID(pSrcUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
}

//请求一对一私聊时，无权限
void HtmlOutPutManager::OnRequestP2PFailed_NotPermission() 
{
	CString strHref ;
	strHref.Format( L"VIP以上用户才能发起一对一视频 <a href=\"%s\" target=\"_blank\">立即升级VIP</a>" ,m_pParentDlg->GetRoomBusiness()->GetUpdateVipUrl() ) ;

	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strHref , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnKickUserNotPermission( uint32 unDstUIN ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;
	strTemp.Format( L"抱歉！对方为%s用户" , m_HtmlBuild.GetVipName( pDstUserItem->GetUserVipLevel() ) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnKickUserRsp_Success( uint32 dstuin , bool bKickAllVisitor ) 
{
	if ( bKickAllVisitor )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"您已将所有游客踢出房间" , COLOR_OPERATE ) ) ;
	}
	else
	{
		IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
		if ( pDstUserItem == NULL )
		{
			return ;
		}
		IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
		if (pMyUserItem == NULL)
		{
			return;
		}
		CString strTemp ;
		strTemp.Format( L"您已将%s踢出房间" ,  GetNameAndID(pDstUserItem)  ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
		//core::CurInfo myCurInfo = GetCurInfo() ;
		CString strNameAndID;
		if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
		{
			strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
		}
		else
		{
			strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str(), pMyUserItem->GetUser179ID());
		}
		strTemp.Format(L"%s被%s踢出房间"  , GetNameAndID(pDstUserItem) ,strNameAndID );
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
}

void HtmlOutPutManager::OnAddBlackRsp_Success( uint32 dstuin ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	CString strTemp ;	
	strTemp.Format( L"您已将%s加入黑名单" , GetNameAndID(pDstUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
	//core::CurInfo myCurInfo = GetCurInfo() ;	
	CString strNameAndID;
	if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str(), pMyUserItem->GetUser179ID());
	}
	strTemp.Format(L"%s已将%s加入黑名单"  , strNameAndID, GetNameAndID(pDstUserItem) );
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnLockIpRsp_Success( uint32 dstuin ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	CString strTemp ;	
	strTemp.Format( L"您已封停%s的IP地址" , GetNameAndID(pDstUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;

	//core::CurInfo myCurInfo = GetCurInfo() ;
	CString strNameAndID;
	if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str(), pMyUserItem->GetUser179ID());
	}
	strTemp.Format( L"%s已将%s踢出本房间" , strNameAndID , GetNameAndID(pDstUserItem) );
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnShutUpRsp_Success( uint32 dstuin ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	CString strTemp ;	
	strTemp.Format( L"您已禁止%s在本房间发言" , GetNameAndID(pDstUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;

	//core::CurInfo myCurInfo = GetCurInfo() ;
	CString strNameAndID;
	if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str(), pMyUserItem->GetUser179ID());
	}
	strTemp.Format( L"%s已禁止%s在本房间内发言" ,strNameAndID , GetNameAndID(pDstUserItem) );
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips(_T("【提示】： ") ,strTemp , COLOR_OPERATE ) );
}

void HtmlOutPutManager::OnUnLockShutUpRsp_Success( uint32 dstuin ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	CString strTemp ;	
	strTemp.Format( L"您已恢复%s在本房间发言" , GetNameAndID(pDstUserItem) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
	//core::CurInfo myCurInfo = GetCurInfo() ;
	CString strNameAndID;
	if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str(), pMyUserItem->GetUser179ID());
	}
	strTemp.Format( L"%s恢复了%s的发言权" , strNameAndID , GetNameAndID(pDstUserItem) );
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips(_T("【提示】： ") ,strTemp , COLOR_OPERATE ) );
}


void HtmlOutPutManager::OnAddTitleRsp_Success( core::ENM_TitleLevel nTitleLevel , uint32 dstuin ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	//core::CurInfo myCurInfo = GetCurInfo() ; 
	CString strNameAndID;
	if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str(), pMyUserItem->GetUser179ID());
	}
	CString strTemp ;
	if ( nTitleLevel == core::TITLELEVEL_SECOND_OWNER )
	{
		strTemp.Format( L"您已任命%s为房间副室主" , GetNameAndID(pDstUserItem) ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;

		strTemp.Format( L"%s被%s任命为房间副室主" ,GetNameAndID(pDstUserItem) , strNameAndID ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " ,strTemp , COLOR_OPERATE ) ) ;
	}	
	else if ( nTitleLevel == core::TITLELEVEL_MANAGER )
	{
		strTemp.Format( L"您已任命%s为房间管理员" , GetNameAndID(pDstUserItem) ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;

		strTemp.Format( L"%s被%s任命为房间管理员" ,GetNameAndID(pDstUserItem) , strNameAndID ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
	else if ( nTitleLevel == core::TITLELEVEL_TEMP_MANAGER )
	{
		strTemp.Format( L"您已任命%s为房间临时管理员" , GetNameAndID(pDstUserItem) ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;		

		strTemp.Format( L"%s被%s任命为房间临时管理员" ,GetNameAndID(pDstUserItem) ,strNameAndID ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}

}

void HtmlOutPutManager::OnAddTitleRsp_IsFull( core::ENM_TitleLevel nTitleLevel , uint32 dstuin ) 
{
	if ( nTitleLevel == core::TITLELEVEL_SECOND_OWNER )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"添加失败，本房间副室主数量已满" , COLOR_OPERATE ) ) ;
	}
	else if ( nTitleLevel == core::TITLELEVEL_MANAGER )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"添加失败，本房间管理员数量已满" , COLOR_OPERATE ) ) ;
	}	
	else if ( nTitleLevel == core::TITLELEVEL_TEMP_MANAGER )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"添加失败，本房间临时管理员数量已满" , COLOR_OPERATE ) ) ;
	}
}

void HtmlOutPutManager::OnAddTitleRsp_IsAdmin_InOther( core::ENM_TitleLevel nTitleLevel ,uint32 dstuin ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	if ( nTitleLevel == core::TITLELEVEL_SECOND_OWNER )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"添加失败，该用户的任职数量已达上限" , COLOR_OPERATE ) ) ;
	}
	else if( nTitleLevel == core::TITLELEVEL_MANAGER )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"添加失败，该用户的任职数量已达上限" , COLOR_OPERATE ) ) ;
	}
	else if ( nTitleLevel == core::TITLELEVEL_TEMP_MANAGER )
	{
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"添加失败，该用户的任职数量已达上限" , COLOR_OPERATE ) ) ;
	}
}

void HtmlOutPutManager::OnRemoveTitleRsp_Success( core::ENM_TitleLevel nTitleLevel , uint32 dstuin ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( dstuin ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
	if (pMyUserItem == NULL)
	{
		return;
	}
	if ( nTitleLevel == core::TITLELEVEL_TEMP_MANAGER )
	{
		//core::CurInfo myCurInfo = GetCurInfo() ; 
		CString strNameAndID;
		if (pMyUserItem->GetUser179ID() > MAX_SHOW_179ID)
		{
			strNameAndID = common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str();
		}
		else
		{
			strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pMyUserItem->GetUserName()).c_str(), pMyUserItem->GetUser179ID());
		}
		CString strTemp ;		
		strTemp.Format( L"您已取消%s的临时管理员身份" , GetNameAndID(pDstUserItem) ) ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;

		strTemp.Format( L"%s被%s取消了房间临时管理员" ,GetNameAndID(pDstUserItem) , strNameAndID ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
}

void HtmlOutPutManager::OnAddTitleNotify( uint32 unSrcUIN ,uint32 unDstUIN ,core::ENM_TitleLevel nTitleLevel , uint32 unRoomID ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ; 
	CString strTemp ;
	if ( unSrcUIN == unDstUIN )
	{
		if ( nTitleLevel == core::TITLELEVEL_SECOND_OWNER )
		{						
			if ( myCurInfo.unUIN == unDstUIN )
			{
				m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"您已被设置为副室主" , COLOR_OPERATE ) ) ;
			}
			strTemp.Format( L"%s成为副室主" ,GetNameAndID(pDstUserItem) ) ;
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) );
		}
		else if ( nTitleLevel == core::TITLELEVEL_MANAGER )
		{
			if ( myCurInfo.unUIN == unDstUIN )
			{
				m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"您已被设置为管理员" ,COLOR_OPERATE ) ) ;
			}
			strTemp.Format( L"%s成为管理员" , GetNameAndID(pDstUserItem) ) ;
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) );
		}
		return ;
	}

	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	if ( nTitleLevel == core::TITLELEVEL_SECOND_OWNER )
	{
		if ( myCurInfo.unUIN == unDstUIN )
		{			 			
			strTemp.Format( L"您已被%s任命为%d房间副室主" , GetNameAndID(pSrcUserItem) , unRoomID ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		strTemp.Format( L"%s被%s任命为房间副室主" , GetNameAndID(pDstUserItem) , GetNameAndID(pSrcUserItem) ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
	else if ( nTitleLevel == core::TITLELEVEL_MANAGER )
	{
		if ( myCurInfo.unUIN == unDstUIN )
		{
			strTemp.Format( L"您已被%s任命为%d房间管理员" , GetNameAndID(pSrcUserItem) ,unRoomID ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}		
		strTemp.Format( L"%s被%s任命为房间管理员" ,  GetNameAndID(pDstUserItem) , GetNameAndID(pSrcUserItem) ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
	else if ( nTitleLevel == core::TITLELEVEL_TEMP_MANAGER )
	{
		if ( myCurInfo.unUIN == unDstUIN )
		{			
			strTemp.Format( L"您已被%s任命为%d房间临时管理员" , GetNameAndID(pSrcUserItem) , unRoomID ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}				
		strTemp.Format( L"%s被%s任命为房间临时管理员" , GetNameAndID(pDstUserItem) , GetNameAndID(pSrcUserItem) ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}

}

void HtmlOutPutManager::OnRemoveTitleNotify( uint32 unSrcUIN ,uint32 unDstUIN , core::ENM_TitleLevel nTitleLevel ,  uint32 unRoomID ) 
{
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ; 
	CString strTemp ;
	if ( unSrcUIN == unDstUIN )
	{
		if ( nTitleLevel == core::TITLELEVEL_SECOND_OWNER )
		{
			if ( myCurInfo.unUIN == unDstUIN )
			{
				m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"您已被撤销副室主" , COLOR_OPERATE ) ) ;
			}			
			strTemp.Format( L"%s被撤销副室主" , GetNameAndID(pDstUserItem) ) ;
			m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}
		else if ( nTitleLevel == core::TITLELEVEL_MANAGER )
		{
			if ( unDstUIN == myCurInfo.unUIN  )
			{
				strTemp =  L"操作成功，您已退出对本房间的管理" ;
				m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
			}					
		}
		return ;
	}
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	if ( nTitleLevel == core::TITLELEVEL_TEMP_MANAGER )
	{
		if ( myCurInfo.unUIN == unDstUIN )
		{			
			strTemp.Format( L"您已被%s取消了%d房间的临时管理员身份" , GetNameAndID(pSrcUserItem) , unRoomID ) ;
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
		}		
		strTemp.Format( L"%s被%s取消了房间临时管理员" , GetNameAndID(pDstUserItem)  ,GetNameAndID(pSrcUserItem) );
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
}

//踢人、拉黑、禁言、邀麦等无权限
void HtmlOutPutManager::OnOperateNotPermission() 
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"抱歉！您的权限不够" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::InsertPrivateTips(const CString& strTitle , const CString& strValue , const CString& strColor ) 
{
	m_pParentDlg->InsertPrivateText(  m_HtmlBuild.GetPrivateTips(strTitle , strValue , strColor ) ) ;
}

bool HtmlOutPutManager::IsPublicMic( uint16 unStatus ) 
{
	if ( (unStatus&USERSTATUSTYPE_PUBLIC_1) || 
		(unStatus&USERSTATUSTYPE_PUBLIC_2) ||
		(unStatus&USERSTATUSTYPE_PUBLIC_3) )
	{
		return true ;
	}
	else
	{
		return false ;
	}
}

CString HtmlOutPutManager::MicChineseIndex( int nIndex ) 
{
	CString strTemp ;
	switch( nIndex )
	{
	case 1:
		{
			strTemp = L"一" ;
		}
		break;
	case 2:
		{
			strTemp = L"二" ;
		}
		break;
	case 3:
		{
			strTemp = L"三" ;
		}
		break;
	default:
		break;
	}
	return strTemp ;
}

bool HtmlOutPutManager::ProcessSendMsgText( CString& strText , bool bFilter ) 
{
	bool bForbidden = false;

	//将表情图片的链接 替换成 表情Code	
	if ( bFilter )
	{
		std::wstring strTextTemp = strText.GetBuffer() ;
		common::utility::systemhelper::FilterWords( strTextTemp ) ;		
		bForbidden = strTextTemp.compare(strText.GetBuffer()) != 0;
	}
	int nStartPos = 0 ;
	while ( true )
	{
		nStartPos = strText.Find( L"<IMG" , nStartPos ) ;
		if ( nStartPos < 0 )
		{
			break;
		}
		int nEndPos = strText.Find( L">" , nStartPos ) ;
		if ( nEndPos < 0 )
		{
			break;
		}
		CString strTemp = strText.Mid( nStartPos , nEndPos - nStartPos+1 ) ;
		EmotionItem* pEmotionItem = EmotionMgr->SearchEmotionByBigFilePath( strTemp.GetBuffer(0) ) ;
		if ( pEmotionItem != NULL )
		{
			strText.Replace( strTemp , pEmotionItem->GetCode().c_str() ) ;
		}
		nStartPos = nStartPos+1 ;
	}

	return bForbidden;
}

void HtmlOutPutManager::EmotionCodeToPath( CString& strText ) 
{
	int nStartPos = 0 ;
	while( true )
	{
		nStartPos = strText.Find( L"/" , nStartPos ) ;
		if ( nStartPos < 0 )
		{
			break;
		}
		int nEndPos = strText.Find( L"/" , nStartPos+1 ) ;
		if ( nEndPos < 0 )
		{
			break; 
		}
		CString strCode = strText.Mid( nStartPos , nEndPos - nStartPos+1 ) ;
		EmotionItem* pEmotionItem = EmotionMgr->SearchEmotionByCode( strCode.GetBuffer(0) ) ;
		if ( pEmotionItem != NULL )
		{
			//将表情Code 替换成 表情图片的链接
			CString strTemp ;
			strTemp.Format(_T("%s%s%s"), _T("<img class=\"image_normal\" id=\"c_i\" src=\"file:///"), pEmotionItem->GetBigEmotionPath().c_str(), _T("\">"));
			strText.Replace( strCode , strTemp ) ;
		}
		nStartPos = nStartPos +1 ;
	}
}

void HtmlOutPutManager::ProcessRecvMsgText( CString& strText  , bool bFilter ) 
{
	if ( bFilter )
	{
		std::wstring strTextTemp = strText.GetBuffer() ;
		common::utility::systemhelper::FilterWords( strTextTemp ) ;
		strText = strTextTemp.c_str() ;
	}
	EmotionCodeToPath( strText ) ;
}

void HtmlOutPutManager::ProcessRecvNoticeText( CString& strText , bool bFilter ) 
{
	if ( bFilter )
	{
		std::wstring strTextTemp = strText.GetBuffer() ;
		common::utility::systemhelper:: FilterNoticeWords( strTextTemp ) ;
		strText = strTextTemp.c_str() ;
	}
	EmotionCodeToPath( strText ) ;
}

bool HtmlOutPutManager::OutPutGift( GiftInfo& giftinfo, bool canCheat ) 
{
	bool canOutputMoreone = false;

	switch ( giftinfo.unType )
	{
	case core::GIFTTYPE_NORMAL:
		{
			if(canCheat)
			{
				bool reallyOutput = ((giftinfo.unCount+giftinfo.srcuin)%2)==0;
				canOutputMoreone = !reallyOutput;
				SetPublicNormalGift( giftinfo, reallyOutput ) ;				
			}
			else
			{
				SetPublicNormalGift( giftinfo, true ) ;
			}			
		}
		break;
	case core::GIFTTYPE_SHECHI:
		{
			//奢侈品
			SetPublicSheChiGift( giftinfo.srcuin , giftinfo.dstuin , giftinfo.unGiftid , giftinfo.unCount ) ;				
		}
		break;
	}

	return canOutputMoreone;
}

void HtmlOutPutManager::OutPutLucky( LuckyInfo& luckyinfo ) 
{
	if ( luckyinfo.unLuckyTimes > 500 )
	{
		m_pParentDlg->InsertSystemSpeaker( m_HtmlBuild.GetSpeakerLucky( CString(luckyinfo.strSrcName.c_str()) ,luckyinfo.strSrcLuckyHead , 
			luckyinfo.src179ID ,luckyinfo.unLuckyTimes ,luckyinfo.unLuckyMoney ,luckyinfo.unGiftid) );
		core::CurInfo myCurInfo = GetCurInfo() ;
		if ( luckyinfo.unLuckyTimes == 5000 && myCurInfo.unUIN == luckyinfo.srcuin )
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetLuckyStarBirth() ) ;
		}
	}
	core::CurInfo myCurInfo = GetCurInfo() ; 
	if (myCurInfo.unUIN == luckyinfo.srcuin)
	{
		m_pParentDlg->InsertPrivateText(  m_HtmlBuild.GetGiftLucky( luckyinfo.srcuin ,luckyinfo.src179ID  ,luckyinfo.strSrcHead ,
			luckyinfo.strSrcName ,luckyinfo.unGiftid , luckyinfo.unLuckyTimes , luckyinfo.unLuckyMoney) ) ;	
	}
	else if (luckyinfo.unLuckyTimes > 10) //其他人中10倍的信息不显示
	{
		m_pParentDlg->InsertPrivateText(  m_HtmlBuild.GetGiftLucky( luckyinfo.srcuin ,luckyinfo.src179ID  ,luckyinfo.strSrcHead ,
			luckyinfo.strSrcName ,luckyinfo.unGiftid , luckyinfo.unLuckyTimes , luckyinfo.unLuckyMoney) ) ;	
		core::CurInfo myCurInfo = GetCurInfo() ; 
	}

	if ( myCurInfo.unUIN == luckyinfo.srcuin )
	{
		//自己中奖，更新钱币
		g_RoomModule->UpdatePlutusAwardOrLuckMoney( luckyinfo.unLuckyMoney ) ;
	}	
}

void HtmlOutPutManager::PlutusAward( int nPlutesIndex , int nPlutusMoney )
{
	CString strTemp ;
	strTemp.Format( L"第%d次赏赐开始！" , nPlutesIndex ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strTemp , COLOR_GIFT ) ) ;

	std::wstring strModulePath = common::utility::systemhelper::Get179AppPath();
	common::CURLEncode urlEncode;
	strModulePath = urlEncode.URLEncodeLocalPath(strModulePath);

	std::wstring strIconPngPath = strModulePath + IMG_COIN_PNG_PATH;	

	strTemp.Format( L"恭喜您，财神赐给您%d币<IMG src=\"%s\"><BR>" , nPlutusMoney ,strIconPngPath.c_str() ) ;
	m_pParentDlg->InsertPrivateText(  m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_GIFT ) ) ;
}

void HtmlOutPutManager::OnSpeakerMsg( core::ENM_LoudSpeakerType enmType , CString& strText , MessageFont& stFont , SpeakerInfo& stInfo )
{
	ProcessRecvMsgText( strText ) ;
	m_pParentDlg->InsertSpeakerText( CSpeakerMsg::GetSpeakerShortCut(enmType, stInfo) + m_HtmlBuild.GetSpeaker( strText , stFont , stInfo ) ) ;
}

void HtmlOutPutManager::OnTopVipClickBlink()
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"尊敬的至尊皇冠用户，您当前已享有最高级别的入场效果。" , COLOR_GIFT) ) ;
}

//解除禁言
void HtmlOutPutManager::OnUnLockShutUpNotify( uint32 unDstUIN ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 
	if ( myCurInfo.unUIN == unDstUIN )
	{
		m_pParentDlg->InsertPrivateText(  m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"您已被解除禁言" , COLOR_OPERATE ) ) ;
	}	
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ;
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	CString strTemp ;			
	strTemp.Format( L"用户%s的发言权已经恢复!" , GetNameAndID(pDstUserItem) ) ;
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicTips( L"【提示】： " , strTemp , COLOR_OPERATE ) );
}


void HtmlOutPutManager::OnSpeakerLuckyMsg( CString& strText, SpeakerInfo& stInfo, uint16 unGiftID )
{
	//ProcessRecvMsgText( strText ) ;
	if (GiftManager::GetInstance()->IsFirework(unGiftID))
	{
		m_pParentDlg->InsertSystemSpeaker(m_HtmlBuild.GetSpeakerFirework(strText, stInfo));
		return;
	}
	else if (GiftManager::GetInstance()->IsSalute(unGiftID))
	{
		m_pParentDlg->InsertSystemSpeaker(m_HtmlBuild.GetSpeakerSalute(strText, stInfo));
		return;
	}
	else
	{
		m_pParentDlg->InsertSystemSpeaker( m_HtmlBuild.GetSpeakerLucky(strText, stInfo, unGiftID));
		return;
	}
}

//财神
void HtmlOutPutManager::OnSpeakerPlutusAward(CString& strText, SpeakerInfo& stInfo, uint16 unGiftID)
{
	m_pParentDlg->InsertSystemSpeaker( m_HtmlBuild.GetSpeakerPlutusAward( strText , stInfo ,unGiftID ) ) ;
}

void HtmlOutPutManager::OnSpeakerSystemMsg( CString& strText )
{
	ProcessRecvMsgText( strText ) ;
	m_pParentDlg->InsertSystemSpeaker( m_HtmlBuild.GetSpeakerSystem(strText));
}

//该用户已经下私麦
void HtmlOutPutManager::OnPrivateShowOff( IUserItem* pUserItem ) 
{
	CString strTemp ;	
	strTemp.Format( L"观看失败，%s已下私麦" , GetNameAndID(pUserItem) ) ;
	m_pParentDlg->InsertPrivateText(  m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnModifyRoomName()
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"修改房间名称后需重新审核，请耐心等待" , COLOR_OPERATE ) ) ;
}

CString HtmlOutPutManager::GetUserHead( IUserItem* pUserItem )
{
	return m_HtmlBuild.GetUserHead( pUserItem ) ;
}

CString HtmlOutPutManager::GetUserItemHeadImg( IUserItem* pUsrItem ) //获得用户名前的章和冠图片
{
	return m_HtmlBuild.GetUserItemHeadImg( pUsrItem ) ;
}
void HtmlOutPutManager::OnBlockChatToMe( std::wstring strName , uint32 un179ID )
{
	CString strTemp;
	CString strNameAndID;
	if (un179ID > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(strName).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(strName).c_str(), un179ID);
	}
	strTemp.Format(L"您已禁止%s与您聊天", strNameAndID );
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnUnBlockChatToMe( std::wstring strName , uint32 un179ID )
{
	CString strTemp;
	CString strNameAndID;
	if (un179ID > MAX_SHOW_179ID)
	{
		strNameAndID = common::utility::stringhelper::XMLEncode(strName).c_str();
	}
	else
	{
		strNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(strName).c_str(), un179ID);
	}
	strTemp.Format(L"您已允许%s与您聊天", strNameAndID );
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", strTemp , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::AutoWelcome( IUserItem* pUserItem) 
{
	if ( pUserItem == NULL )
	{
		return ;
	}
	CString strTemp;
	if(GetCurInfo().bFirstLogin)
	{
		strTemp = WelcomeMgr->GetFirstLoginUserWelcomeRandom();
	}else
	{
		strTemp = WelcomeMgr->GetWelcomeRandom() ;
	}
	 
	if ( !strTemp.IsEmpty() )
	{
		core::CurInfo myCurInfo = GetCurInfo() ;
		if (myCurInfo.strName != L"")
		{
			strTemp.Replace( L"name" , common::utility::stringhelper::XMLEncode(myCurInfo.strName).c_str() ) ;
		}
		else
		{
			CString strTempName = common::utility::stringhelper::IntToString(myCurInfo.un179id).c_str();
			strTemp.Replace( L"name" , strTempName ) ;
		}
		
		ProcessRecvMsgText( strTemp , true ) ;
		m_pParentDlg->InsertPublicText( m_HtmlBuild.GetAutoWelcome( pUserItem , strTemp ) ) ;
	}
}

void HtmlOutPutManager::VisitorRegister( IUserItem* pUserItem ) 
{
	if ( pUserItem == NULL )
	{
		return ;
	}
	CString strTemp = VisitorMgr->GetVisitorRandom() ;
	if ( !strTemp.IsEmpty() )
	{
		core::CurInfo myCurInfo = GetCurInfo() ;
		CString strHref ;		
		strHref.Format( L"<a href=\"%s\" name=\"%s\" type=\"%d\" uuid=\"%u\" >去注册吧</a>", L"" ,L"Register" ,CLICK_TYPE_REGISTER ,  myCurInfo.unUIN) ;
		strTemp += strHref ;
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetVisistorRegistor( pUserItem , strTemp ) ) ;
	}
}

void HtmlOutPutManager::OnUserChangeVoiceRsp( uint32 unDstUIN, uint16 unChangeVoiceID )
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicChangeVoice( pSrcUserItem , pDstUserItem , unChangeVoiceID ) ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateChangeVoiceRsp( pDstUserItem, unChangeVoiceID ) ) ;
}

void HtmlOutPutManager::OnUserChangeVoiceNotify( uint32 unSrcUIN , uint32 unDstUIN, uint16 unChangeVoiceID )
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	IUserItem* pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unDstUIN ) ; 
	if ( pDstUserItem == NULL )
	{
		return ;
	}
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( myCurInfo.unUIN == unDstUIN )
	{
		//别人让我变声
		m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateChangeVoice( pSrcUserItem ,unChangeVoiceID) ) ;
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicChangeVoice( pSrcUserItem , pDstUserItem , unChangeVoiceID ) ) ;
}

void HtmlOutPutManager::OnFlyTextNotify( uint32 unSrcUIN, std::wstring strText )
{
	IUserItem * pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN(unSrcUIN);
	if (pSrcUserItem == NULL)
	{
		return;
	}
	m_pParentDlg->InsertPublicText( m_HtmlBuild.GetPublicFlyText( pSrcUserItem, strText.c_str()));
}

void HtmlOutPutManager::OnSendMsgLimitedTime( uint32 unLeftTime )
{
	CString strTemp ;
	strTemp.Format( L"%d秒后才能发言哦，VIP以上用户自由发言无限制， <a href=\"%s\" target=\"_blank\">马上升级VIP</a>" ,
		unLeftTime ,m_pParentDlg->GetRoomBusiness()->GetUpdateVipUrl() ) ;
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( _T("【提示】： ") , strTemp , COLOR_OPERATE) ) ;
}

void HtmlOutPutManager::OnRequestPushOnShowNotify( uint32 unSrcUIN, uint8 unIndex )
{
	IUserItem* pSrcUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pSrcUserItem == NULL )
	{
		return ;
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetRequestPublicMicNotify( pSrcUserItem, unIndex ) ) ;
}

void HtmlOutPutManager::OnPushOnShowRsp_OnMic()
{
	IUserItem* pSelfUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem() ;
	if ( pSelfUserItem != NULL )
	{
		if ( pSelfUserItem->GetUserStatus()&core::USERSTATUSTYPE_P2P )
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"抱歉，您正在一对一视频中" , COLOR_OPERATE ) ) ;
		}
		else if ( pSelfUserItem->GetUserStatus()&core::USERSTATUSTYPE_PRIVATE)
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"抱歉，您正在私麦上" , COLOR_OPERATE ) ) ;
		}
		else
		{
			m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"抱歉，您正在公麦上" , COLOR_OPERATE ) ) ;
		}
	}
}

void HtmlOutPutManager::OnPushOnShowRsp_Mic_HasPlayer()
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"抱歉，当前视频窗口被占用" , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnPushOnShowRsp_Refuse()
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,L"您拒绝了上麦邀请" , COLOR_OPERATE ) );
}

void HtmlOutPutManager::OnPushOnShowRsp_Refuse( uint32 unDstUIN )
{
	IUserItem * pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN(unDstUIN);
	if (pDstUserItem != NULL)
	{
		CString strTemp ;	
		strTemp.Format( L"%s拒绝您的上麦邀请" , GetNameAndID(pDstUserItem) ) ;
		m_pParentDlg->InsertPrivateText(  m_HtmlBuild.GetPrivateTips( L"【提示】： " , strTemp , COLOR_OPERATE ) ) ;
	}
}

void HtmlOutPutManager::OnPushOnShowRsp_NeedAnswer()
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " , L"视频邀请已发送，等待对方确认..." , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::OnSofaBeKicked( IUserItem * pUserItem )
{
	CString strTemp;
	CString strName = m_HtmlBuild.ChatUserItem(pUserItem);
	strTemp = L"很抱歉，您被" + strName + L"踢下沙发，心有不甘？还不快把沙发抢回来！";
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", strTemp, COLOR_OPERATE ));
}

void HtmlOutPutManager::OnSofaNewUser( IUserItem * pNewUserItem, IUserItem * pOldUserItem, bool bEmpty/* = false*/ )
{
	CString strTemp;
	if (bEmpty)
	{
		if (pNewUserItem->GetUserUIN() == GetCurInfo().unUIN)
		{
			strTemp = L"恭喜，您已成功抢到沙发";
		}
		else
		{
			CString strNewUserName = m_HtmlBuild.ChatUserItem(pNewUserItem);
			strTemp = L"恭喜，" + strNewUserName + L"成功抢到沙发";
		}
	}
	else
	{
		if (pNewUserItem->GetUserUIN() == GetCurInfo().unUIN)
		{
			strTemp = L"恭喜，您已成功抢到沙发";
		}
		else if (pNewUserItem->GetUserUIN() == pOldUserItem->GetUserUIN())
		{
			CString strNewUserName = m_HtmlBuild.ChatUserItem(pNewUserItem);
			strTemp = L"恭喜，" + strNewUserName + L"成功升级沙发";
		}
		else
		{
			CString strNewUserName = m_HtmlBuild.ChatUserItem(pNewUserItem);
			CString strOldUserName = m_HtmlBuild.ChatUserItem(pOldUserItem);

			strTemp = L"沙发大战开始啦！" + strNewUserName + L"使出无影脚，将" + strOldUserName + L"一脚踢飞。沙发争霸，你还不快来一试高下？";
		}
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", strTemp, COLOR_OPERATE ));
}

void HtmlOutPutManager::OnSofaNewUser( IUserItem * pNewUserItem, CSofaItem * pSofaItem )
{
	CString strTemp;
	if (pNewUserItem->GetUserUIN() == GetCurInfo().unUIN)
	{
		strTemp = L"恭喜，您已成功抢到沙发";
	}
	else
	{
		CString strNewUserName = m_HtmlBuild.ChatUserItem(pNewUserItem);
		CString strOldUserName = m_HtmlBuild.ChatSofaUserItem(pSofaItem);

		strTemp = L"沙发大战开始啦！" + strNewUserName + L"使出无影脚，将" + strOldUserName + L"一脚踢飞。沙发争霸，你还不快来一试高下？";
	}
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", strTemp, COLOR_OPERATE ));
}
void HtmlOutPutManager::OnSofaPublicNotify( IUserItem * pUserItem, bool bSameUser/* = false*/ )
{
	CString strName = m_HtmlBuild.ChatUserItem(pUserItem);

	CString strAct;
	if (bSameUser)
	{
		strAct = L"升级";
	}
	else
	{
		strAct = L"抢到";
	}
	CString strTemp;
	strTemp = L"恭喜，" + strName + L"成功" + strAct + L"沙发";
	m_pParentDlg->InsertPublicText(m_HtmlBuild.GetPrivateTips( L"【提示】： ", strTemp, COLOR_OPERATE ));
}

void HtmlOutPutManager::OnSofaMyUpdate( IUserItem * pUserItem )
{
	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： ", L"恭喜，您已成功升级沙发", COLOR_OPERATE ));
}

CString HtmlOutPutManager::GetSofaUserHead( CSofaItem * pSofaItem )
{
	return m_HtmlBuild.GetSofaUserHead(pSofaItem);
}

void HtmlOutPutManager::OnEnterRoomGetUserList_Event( IUserItem * pUserItem, uint8 unIndex )
{
	CString strHtml = m_HtmlBuild.GetEnterRoomGetUserList_Event( pUserItem, unIndex ) ;
	if ( !strHtml.IsEmpty() )
	{
		m_pParentDlg->InsertPublicText( strHtml ) ;
	}
}

CString HtmlOutPutManager::GetNameAndID( IUserItem * pUserItem )
{
	return m_HtmlBuild.GetNameAndID(pUserItem);
}

void HtmlOutPutManager::OnEnterRoomGetUserList_VIPLevelBlackDiamond( IUserItem* pUserIterm )
{
	//黑钻皇冠
	CString strHtml = m_HtmlBuild.GetEnterRoomGetUserList_VIPLevelBlackDiamond( pUserIterm ) ;
	if ( !strHtml.IsEmpty() )
	{
		m_pParentDlg->InsertPublicText( strHtml ) ;
	}
}

void HtmlOutPutManager::OnSpeakerGameMsg( CString& strText )
{
	m_pParentDlg->InsertSystemSpeaker( m_HtmlBuild.GetSpeakerGame(strText));
}

void HtmlOutPutManager::OnModifyFont()
{
	CString strHref ;
	strHref.Format( L"抱歉，只有荣耀VIP以上用户可修改字体 <a href=\"%s\" target=\"_blank\">立即升级</a>" ,m_pParentDlg->GetRoomBusiness()->GetUpdateVipUrl() ) ;

	m_pParentDlg->InsertPrivateText( m_HtmlBuild.GetPrivateTips( L"【提示】： " ,strHref , COLOR_OPERATE ) ) ;
}

void HtmlOutPutManager::InsertRoomMidInputDefaultText(CString& strText)
{
	m_pParentDlg->InsertRoomMidInputDefaultText( m_HtmlBuild.GetRoomMidInputDefaultText(strText) );
}

void HtmlOutPutManager::OnMarkNotify( CString& strSongerName )
{
	m_pParentDlg->InsertPrivateText(m_HtmlBuild.GetMarkInvite(strSongerName));
}

void HtmlOutPutManager::OnMarkSongNotify( CString& strOrderName, CString& strSongName, CString& strMark )
{
	CString strTip;
	strTip.Format(L"%s给了你演唱的%s一个%s", strOrderName, strSongName, strMark);

	m_pParentDlg->InsertPrivateText(m_HtmlBuild.GetMarkTips(L"【点歌评价】 ", strTip, L"#EF427B"));
}

void HtmlOutPutManager::OnSpeakerLuxuryMsg( SpeakerInfo& stSrcInfo, SpeakerInfo& stDstInfo, CString& strRoomName, uint16 unGiftID, uint16 unCount )
{
	m_pParentDlg->InsertSystemSpeaker( m_HtmlBuild.GetSpeakerLuxury(stSrcInfo, stDstInfo, strRoomName, unGiftID, unCount));
}