#include "StdAfx.h"
#include "h264Codec.h"
#include "AvDefine.h"
#include "MyAssert.h"
#include "Global.h"
#include "RelayManger.h"

#define VIDEO_RATE_MIN_LIMIT 7.0f  
#define VIDEO_RATE_MAX_LIMIT 7.5f  //视频流量分界线
#define VIDEO_RATE_COUNT_INTER 5*60*1000  //前5分钟内不计算平均码率

typedef enum
{
	EN_LEVEL_1 = 0x01,
	EN_LEVEL_2 = 0x02,
	EN_LEVEL_3 = 0x03
} enLostType;

typedef struct stQualityInfo
{
	int i_qp_min; //最小量化值
	int i_qp_max; //最大量化值
	int i_qp_constant;  //qp初始值 0~51
	float f_rf_constant; /* In CRF mode, maximum CRF as caused by VBV */
	int	i_bitrate;	//平均码率  -- 有点不准
	int i_vbv_max_bitrate; //平均码率 最大瞬时码率
	float f_ip_factor;  //I帧和P帧之间的量化系数 1.4
	float f_pb_factor;  //P帧和B帧之间的量化系数 1.3
	float f_aq_strength; // 量化强度 ????
} QualityInfo;

#define QUALITYSIZE 5
const static QualityInfo QUALITYLIST[3][QUALITYSIZE] = {
	{
		{3,28,0,6.0f,100,100,1.4f,1.3f,0.1f},
		{4,30,0,7.0f,80	,80	,1.4f,1.3f,0.2f},
		{4,32,0,7.0f,80	,80	,1.4f,1.3f,0.2f},
		{4,34,0,8.0f,70	,70	,1.4f,1.3f,0.3f},
		{5,35,0,8.5f,60	,60	,1.4f,1.3f,0.3f}
	},
	{
		{2 ,30,0 ,8.5f ,70,70,1.4f,1.3f,0.1f},
		{4 ,32,0 ,10.0f,60,60,1.4f,1.3f,0.3f},
		{6 ,34,0 ,12.0f,55,55,1.4f,1.3f,0.6f},
		{8 ,36,0 ,14.0f,55,55,1.4f,1.3f,0.8f},
		{10,38,0 ,25.0f,55,55,1.4f,1.3f,1.3f}
	},
	{
		{5,35,0 ,23.0f,60,60,1.4f,1.3f,0.1f},
		{10,35,0 ,23.0f,60,60,1.4f,1.3f,0.1f},
		{10,35,0 ,23.0f,60,60,1.4f,1.3f,0.1f},
		{15,36,0 ,23.0f,60,60,1.4f,1.3f,0.1f},
		{15,38,0 ,23.0f,60,60,1.4f,1.3f,0.1f}
	//	{20,40,27,27.0f,60,60,1.7f,1.9f}
	}
};

typedef struct stRateInfo
{
	float fRateMinLimit;
	float fRateMaxLimit;
	float fRateAverage;
	DWORD dwRateCountInter; //计算码率时间间隔
} RateInfo;

#define QUALITY_INDEX 1

const static RateInfo RATELIST[3] = {
	{11.0f, 12.0f, 11.5f, 2*60*1000}, //VIDEO_CENT_MIC
	{5.0f , 5.5f , 5.2f , 2*60*1000}, //VIDEO_EDGE_MIC
	{6.0f , 6.5f , 6.0f , 5*60*1000}  //VIDEO_PRIV_MIC
};

h264Codec::h264Codec()
:m_iCurSeqNum(0),
m_iCurKeySeqNum(0),
m_h264_codec_width(224),
m_h264_codec_height(168),
m_eh264_codec_mode(ROOM_VIDEO_CRF_MODE),
m_pBuf(NULL),
m_de_frame(NULL),
m_de_context(NULL),
m_de_codec(NULL),
m_swsContext(NULL),
m_bIsWaittingForKeyFrame(true),
m_encodeType(0),
m_keyFrame_Count(0),
m_last_p(false),
m_is_stop(false),
m_iframe(0),
m_qp_index(QUALITY_INDEX),
dwStart(0),
m_qp_index_old(QUALITY_INDEX),
m_iframeEx(0),
m_iQPIndex(0)
{
	avcodec_register_all();
	memset(m_cframe,0,49+7);

	m_cframe[0] = 1;
	m_cframe[8] = 2;
	m_cframe[16] = 2;
	m_cframe[24] = 2;
	m_cframe[32] = 2;
	m_cframe[40] = 2;

	m_cframe[50] = 2;

	dwStart = 0;
	m_bCacheStart = false;
	m_flastRate = 0.0f;

	memset(m_score,0,SCORE_CALC_LEN*sizeof(int));

	m_dwFirstMapStartTime = 0;
	m_dwSecondMapStartTime = 0;
	m_fAverageRate = 7.0f;

	m_enNewType = enuVIDEO_TYPE::VIDEO_PRIV_MIC;
	m_enUsedType = enuVIDEO_TYPE::VIDEO_PRIV_MIC;
}

h264Codec::~h264Codec(void)
{
	CVideoDataCache* pData = NULL;
	while (m_cache.GetListSize()>0)
	{
		pData=m_cache.GetListData();
		delete pData;
	}

	if (m_bEncode)
	{
		CORelease();
	}
	else
	{
		DeRelease();
	}

	if (m_pBuf)
	{
		delete [] m_pBuf;
		m_pBuf = NULL;
	}

	Trace("h264Codec::~h264Codec(void)\n");
}

bool h264Codec::SetTypeSize(enuVIDEO_TYPE enType)
{
	switch(enType)
	{
	case enuVIDEO_TYPE::VIDEO_CENT_MIC:
		m_h264_codec_width = 288/*-16*/;
		m_h264_codec_height = 216/*-12*/;
		this->m_eh264_codec_mode=ROOM_VIDEO_CQP_BIG;
		break;
	case enuVIDEO_TYPE::VIDEO_EDGE_MIC:
		m_h264_codec_width = 224;
		m_h264_codec_height = 168;
		this->m_eh264_codec_mode=ROOM_VIDEO_CQP_SMAL;
		break;
	case enuVIDEO_TYPE::VIDEO_PRIV_MIC:
		m_h264_codec_width = 224;
		m_h264_codec_height = 168;
		break;
	}

	m_enUsedType = enType;

	return true;
}


bool h264Codec::Init(bool bDecode,int iWidth,int iHeight,int iQP,enuVIDEO_TYPE enType,enuROOM_AV_VIDEO_MODE eMode/* = ROOM_VIDEO_CRF_MODE*/)
{
	m_bEncode	= !bDecode;
	m_nWidth	= iWidth;//encode:输入视频分辨率,decode:输出视频分辨率
	m_nHeight	= iHeight;
	m_en_nQP	= iQP;
	bool bInit = false;
	m_bIsChange = false;

	m_enNewType = enType;
	SetMode(eMode);


	SetTypeSize(m_enNewType);
	m_fAverageRate = RATELIST[m_enUsedType].fRateAverage;

	m_pBuf = new unsigned char[m_nWidth * m_nHeight * 3];
	if (m_bEncode)
	{
		bInit = COConnect();
	}
	else
	{
		bInit = DeConnect();
	}
	return bInit;
}

bool h264Codec::SetMode(enuROOM_AV_VIDEO_MODE eMode/* = ROOM_VIDEO_CRF_MODE*/)
{
	this->m_eh264_codec_mode = eMode;
	switch(this->m_eh264_codec_mode)
	{
	case ROOM_VIDEO_CRF_MODE://恒定码率
		{
			m_h264_codec_width = 224/*320*/;
			m_h264_codec_height = 168/*240*/;
		}
		break;
	case ROOM_VIDEO_CRF_OLD://备份
		{
			m_h264_codec_width = 224;
			m_h264_codec_height = 168;
		}
		break;
	case ROOM_VIDEO_CQP_224: //恒定质量
		{
			m_h264_codec_width = 224;
			m_h264_codec_height = 168;
		}
		break;
	case ROOM_VIDEO_CQP_232:
		{
			m_h264_codec_width = 232;
			m_h264_codec_height = 174;
		}
		break;
	case ROOM_VIDEO_CQP_208:
		{
			m_h264_codec_width = 208;
			m_h264_codec_height = 156;
		}
		break;
	case ROOM_VIDEO_ABR_MODE://平均码率
		{
			m_h264_codec_width = 224;
			m_h264_codec_height = 168;
		}
		break;
	case ROOM_VIDEO_CQP_216:
		{
			m_h264_codec_width = 216;
			m_h264_codec_height = 162;			
		}
		break;
	case ROOM_VIDEO_CRF_MAX://恒定码率 限定最大值
		{
			m_h264_codec_width = 216;
			m_h264_codec_height = 162;
		}
		break;
	case ROOM_VIDEO_CRF_MIN://恒定码率 限定最大值
		{
			m_h264_codec_width = 216;
			m_h264_codec_height = 162;
		}
		break;
	case ROOM_VIDEO_CQP_BIG://大视频
		{
			m_h264_codec_width = 216;
			m_h264_codec_height = 162;
		}
		break;
	case ROOM_VIDEO_CQP_SMAL://小视频
		{
			m_h264_codec_width = 216;
			m_h264_codec_height = 162;
		}
		break;
	default:
		{
			m_h264_codec_width = 224;
			m_h264_codec_height = 168;
		}
	}
	return true;
}

void PrintX264Param(x264_param_t *param)
{
#ifdef _DEBUG
	char szTemp[255];
	sprintf(szTemp, "param->i_threads = %d,X264_THREADS_AUTO=%d\n",param->i_threads, X264_THREADS_AUTO);
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->b_deterministic = %d\n",param->b_deterministic);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_sync_lookahead = %d\n",param->i_sync_lookahead);  
	OutputDebugStringA(szTemp);
	//视频属性
	sprintf(szTemp, "param->i_csp = %d\n",param->i_csp); //X264_CSP_I420
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_width = %d\n",param->i_width); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_height = %d\n",param->i_height); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.i_sar_width = %d\n",param->vui.i_sar_width); //VUI:video usability information
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.i_sar_height = %d\n",param->vui.i_sar_height);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.i_overscan = %d\n",param->vui.i_overscan);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.i_vidformat = %d\n",param->vui.i_vidformat);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.b_fullrange = %d\n",param->vui.b_fullrange); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.i_colorprim = %d\n",param->vui.i_colorprim); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.i_transfer = %d\n",param->vui.i_transfer); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.i_colmatrix = %d\n",param->vui.i_colmatrix); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->vui.i_chroma_loc = %d\n",param->vui.i_chroma_loc); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_fps_num = %d\n",param->i_fps_num); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_fps_den = %d\n",param->i_fps_den); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_level_idc = %d\n",param->i_level_idc); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_slice_max_size = %d\n",param->i_slice_max_size);
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_slice_max_size = %d\n",param->i_slice_max_size); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_slice_max_size = %d\n",param->i_slice_max_size); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_slice_max_mbs = %d\n",param->i_slice_max_mbs); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_slice_count = %d\n",param->i_slice_count); 
	OutputDebugStringA(szTemp);

	// 编码参数
	sprintf(szTemp, "param->i_frame_reference = %d\n",param->i_frame_reference); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_keyint_max = %d\n",param->i_keyint_max);
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_keyint_min = %d\n",param->i_keyint_min); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_bframe = %d\n",param->i_bframe); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_scenecut_threshold = %d\n",param->i_scenecut_threshold); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_bframe_adaptive = %d X264_B_ADAPT_FAST=%d\n",param->i_bframe_adaptive,X264_B_ADAPT_FAST);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_bframe_bias = %d\n",param->i_bframe_bias); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->b_deblocking_filter = %d\n",param->b_deblocking_filter);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_deblocking_filter_alphac0 = %d\n",param->i_deblocking_filter_alphac0); //[-6, 6] -6 亮度滤波器, 6 强
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_deblocking_filter_beta = %d\n",param->i_deblocking_filter_beta); //[-6, 6]  同上
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->b_cabac = %d\n",param->b_cabac);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_cabac_init_idc = %d\n",param->i_cabac_init_idc); // -1 ???
	OutputDebugStringA(szTemp);

	//码率控制
	sprintf(szTemp, "param->rc.i_rc_method = %d X264_RC_CRF=%d\n",param->rc.i_rc_method,X264_RC_CRF); //恒定码率  //默认X264_RC_NONE //码率控制，CQP（恒定质量）、//CRF（恒定码率）、ABR（平均码率）
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_bitrate = %d\n",param->rc.i_bitrate);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_rate_tolerance = %f\n",param->rc.f_rate_tolerance); //1.0
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_vbv_max_bitrate = %d\n",param->rc.i_vbv_max_bitrate);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_vbv_buffer_size = %d\n",param->rc.i_vbv_buffer_size);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_vbv_buffer_init = %f\n",param->rc.f_vbv_buffer_init);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_qp_constant = %d\n",param->rc.i_qp_constant);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_rf_constant = %f\n",param->rc.f_rf_constant); //23
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_rf_constant_max = %f\n",param->rc.f_rf_constant_max); //23
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_qp_min = %d\n",param->rc.i_qp_min); //允许的最小量化值
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_qp_max = %d\n",param->rc.i_qp_max); //允许的最大量化值
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_qp_step = %d\n",param->rc.i_qp_step); //帧间最大量化步长
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_ip_factor = %f\n",param->rc.f_ip_factor);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_pb_factor = %f\n",param->rc.f_pb_factor);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_aq_mode = %d X264_AQ_VARIANCE=%d\n",param->rc.i_aq_mode,X264_AQ_VARIANCE);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_aq_strength = %f\n",param->rc.f_aq_strength); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.i_lookahead = %d\n",param->rc.i_lookahead);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.b_stat_write = %d\n",param->rc.b_stat_write);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.psz_stat_out = %s\n",param->rc.psz_stat_out);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.b_stat_read = %d\n",param->rc.b_stat_read);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.psz_stat_in = %s\n",param->rc.psz_stat_in);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_qcompress = %f\n",param->rc.f_qcompress); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_qblur = %f\n",param->rc.f_qblur); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.f_complexity_blur = %f\n",param->rc.f_complexity_blur); 
	OutputDebugStringA(szTemp);

	sprintf(szTemp, "param->rc.i_zones = %d\n",param->rc.i_zones); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->rc.b_mb_tree = %d\n",param->rc.b_mb_tree); 
	OutputDebugStringA(szTemp);

	//日志
	sprintf(szTemp, "param->pf_log = %d\n",param->pf_log);  //X264_LOG_ERROR
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->p_log_private = %s\n",param->p_log_private);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_log_level = %d X264_LOG_INFO=%d\n",param->i_log_level,X264_LOG_INFO);  
	OutputDebugStringA(szTemp);

	//分析
	sprintf(szTemp, "param->analyse.intra = %d X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8=%d\n",param->analyse.intra,X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.inter = %d X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8| X264_ANALYSE_PSUB16x16 | X264_ANALYSE_BSUB16x16=%d\n",
		param->analyse.inter,X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8| X264_ANALYSE_PSUB8x8| X264_ANALYSE_PSUB16x16 | X264_ANALYSE_BSUB16x16); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_direct_mv_pred = %d X264_DIRECT_PRED_SPATIAL=%d\n",param->analyse.i_direct_mv_pred,X264_DIRECT_PRED_SPATIAL);  
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_me_method = %d X264_ME_HEX=%d\n",param->analyse.i_me_method,X264_ME_HEX); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.f_psy_rd = %f\n",param->analyse.f_psy_rd); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_psy = %d\n",param->analyse.b_psy); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.f_psy_trellis = %f\n",param->analyse.f_psy_trellis); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_me_range = %d\n",param->analyse.i_me_range); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_subpel_refine = %d\n",param->analyse.i_subpel_refine); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_mixed_references = %d\n",param->analyse.b_mixed_references); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_chroma_me = %d\n",param->analyse.b_chroma_me); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_mv_range_thread = %d\n",param->analyse.i_mv_range_thread); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_mv_range = %d\n",param->analyse.i_mv_range); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_chroma_qp_offset = %d\n",param->analyse.i_chroma_qp_offset); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_fast_pskip = %d\n",param->analyse.b_fast_pskip); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_weighted_bipred = %d\n",param->analyse.b_weighted_bipred); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_dct_decimate = %d\n",param->analyse.b_dct_decimate); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_transform_8x8 = %d\n",param->analyse.b_transform_8x8); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_trellis = %d\n",param->analyse.i_trellis); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_luma_deadzone[0] = %d\n",param->analyse.i_luma_deadzone[0]); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.i_luma_deadzone[1] = %d\n",param->analyse.i_luma_deadzone[1]); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_psnr = %d\n",param->analyse.b_psnr); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->analyse.b_ssim = %d\n",param->analyse.b_ssim); 
	OutputDebugStringA(szTemp);

	//muxing
	sprintf(szTemp, "param->b_repeat_headers = %d\n",param->b_repeat_headers); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->b_aud = %d\n",param->b_aud); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->b_annexb = %d\n",param->b_annexb); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->b_interlaced = %d\n",param->b_interlaced?1:0); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->b_intra_refresh = %d\n",param->b_intra_refresh?1:0); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_timebase_den = %d\n",param->i_timebase_den?1:0); 
	OutputDebugStringA(szTemp);
	sprintf(szTemp, "param->i_timebase_num = %d\n",param->i_timebase_num?1:0); 
	OutputDebugStringA(szTemp);
#endif
}

#define KEY_DISTANCE  55

bool h264Codec::COConnect()
{
	if(0 != x264_param_default_preset(&m_en_param, "veryslow", "zerolatency")) //"zerolatency"将延迟降设置成最短
	{
		return false;
	}

	switch(this->m_eh264_codec_mode)
	{
	case ROOM_VIDEO_CRF_MODE://恒定码率  固定不变
		{
			//PrintX264Param(&m_en_param);
			//视频属性相关
			//m_en_param.cpu = X264_CPU_MMXEXT|X264_CPU_SSE|X264_CPU_SSE2;//x264_cpu_detect();
			m_en_param.i_threads = X264_THREADS_AUTO; //根据CPU核数 自动线程数
			m_en_param.i_width = m_h264_codec_width; //进入编码器图像宽度
			m_en_param.i_height = m_h264_codec_height; //进入编码器图像高度
			m_en_param.i_fps_num  = 10;//帧率
			m_en_param.i_fps_den = 1; // 两个整数的比值来表示帧率
			m_en_param.i_timebase_den = m_en_param.i_fps_num; 
			m_en_param.i_timebase_num = m_en_param.i_fps_den;
			m_en_param.i_keyint_min = KEY_DISTANCE;//场景切换少于次值编码位I, 而不是 IDR.
			m_en_param.i_keyint_max = KEY_DISTANCE;//在此间隔设置IDR关键帧
			m_en_param.b_deterministic	= 1; //允许非确定性的线性优化

			m_en_param.i_bframe = 7; //b帧数目
			m_en_param.i_bframe_pyramid=0; //允许B帧做参考帧
			m_en_param.i_frame_reference = 9; //参考帧数量
			m_en_param.i_bframe_bias =100; //B帧被P帧替代的概率
			m_en_param.i_bframe_adaptive = X264_B_ADAPT_NONE;//X264_B_ADAPT_FAST;//X264_B_ADAPT_TRELLIS; 自适应B帧判定
			m_en_param.i_scenecut_threshold = 100; //积极插入额外的I帧

			m_en_param.i_deblocking_filter_alphac0 = 0; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 3; //[-6, 6]  色度滤波
			m_en_param.b_deblocking_filter = 1;  //去块效应 开
			m_en_param.b_intra_refresh=0;    /* Whether or not to use periodic intra refresh instead of IDR frames. */
			m_en_param.b_cabac = 1; //打开cabac
			m_en_param.i_cabac_init_idc = -1;//???
			m_en_param.b_visualize=0;	//显示运动矢量
			m_en_param.b_annexb = 1; 
			m_en_param.i_sync_lookahead = X264_SYNC_LOOKAHEAD_AUTO; //自动选择超前缓冲区

			m_en_param.i_csp			= X264_CSP_I420;
			m_en_param.vui.i_sar_width  = 0;
			m_en_param.vui.i_sar_height = 0;
			m_en_param.vui.i_overscan   = 0;  /* 0=undef, 1=no overscan, 2=overscan */
			m_en_param.vui.i_vidformat  = 5;  /* undef */
			m_en_param.vui.b_fullrange  = 1;  /* on */
			m_en_param.vui.i_colorprim  = 1;  /* undef */ 
			m_en_param.vui.i_transfer   = 2;  /* undef */
			m_en_param.vui.i_colmatrix  = 1;  /* undef */ 
			m_en_param.vui.i_chroma_loc = 5;  // 色度样本指定

			m_en_param.b_interlaced = 1;//纯交错模式
			m_en_param.i_slice_max_size = 0; //每片字节的最大数 包括预计的NAL开销
			m_en_param.i_slice_max_mbs = 0; //宏块数目
			m_en_param.i_slice_count = 0; 
			m_en_param.i_level_idc      = -1;

			//Muxing
			m_en_param.b_repeat_headers = 1; 
			m_en_param.b_aud = 0;

			//量化相关
			m_en_param.i_cqm_preset = X264_CQM_FLAT;//X264_CQM_JVT;  自定义量化矩阵(CQM),初始化量化模式为flat 0
			memset(m_en_param.cqm_4iy,16,16);
			memset(m_en_param.cqm_4ic,16,16);
			memset(m_en_param.cqm_4py,16,16);
			memset(m_en_param.cqm_4pc,16,16);
			memset(m_en_param.cqm_8iy,16,64);
			memset(m_en_param.cqm_8py,16,64);

			//码率控制相关
			m_en_param.rc.i_rc_method = X264_RC_CRF; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率 X264_RC_ABR平均码率 
			m_en_param.rc.i_qp_constant = QUALITYLIST[m_enUsedType][m_qp_index].i_qp_constant;//23;
			m_en_param.rc.f_rf_constant = QUALITYLIST[m_enUsedType][m_qp_index].f_rf_constant;//23.0;
			m_en_param.rc.f_rf_constant_max = 0.0;
			m_en_param.rc.i_qp_min = QUALITYLIST[m_enUsedType][m_qp_index].i_qp_min;//5;//最小量化值
			m_en_param.rc.i_qp_max = QUALITYLIST[m_enUsedType][m_qp_index].i_qp_max;//35;//最大量化值
			m_en_param.rc.i_qp_step = 4;//量化步长 /* max QP step between frames */
			m_en_param.rc.f_qcompress = 0.9; // 0.0 => cbr, 1.0 => constant qp
			m_en_param.rc.f_rate_tolerance = 0.1;//平均码率容限   0.1~100.0
			m_en_param.rc.i_bitrate = QUALITYLIST[m_enUsedType][m_qp_index].i_bitrate;// 60;//平均码率
			m_en_param.rc.i_vbv_max_bitrate = QUALITYLIST[m_enUsedType][m_qp_index].i_vbv_max_bitrate; //60;//平均码率 vbv 最大瞬时码率
			m_en_param.rc.i_vbv_buffer_size = 1024;
			m_en_param.rc.f_vbv_buffer_init = 0.9;
			//m_en_param.rc.b_cbr = 1;//是否使用码率控制
			m_en_param.rc.b_stat_write = 0; //是否允许写状态到文件 影响效率 不允许
			m_en_param.rc.psz_stat_out = "x264.log";
			m_en_param.rc.b_stat_read = 0;//是否允许读状态从文件 影响效率 不允许
			m_en_param.rc.psz_stat_in = "x264.log";
			m_en_param.rc.f_ip_factor = QUALITYLIST[m_enUsedType][m_qp_index].f_ip_factor; //1.4;//I帧和P帧之间的量化系数
			m_en_param.rc.f_pb_factor = QUALITYLIST[m_enUsedType][m_qp_index].f_pb_factor; //1.3;//P帧和B帧之间的量化系数
			m_en_param.rc.i_aq_mode = X264_AQ_VARIANCE;
			m_en_param.rc.f_aq_strength = QUALITYLIST[m_enUsedType][m_qp_index].f_aq_strength;
			m_en_param.rc.f_qblur = 0.5;
			m_en_param.rc.f_complexity_blur = 20;
			m_en_param.rc.i_zones = 0;
			m_en_param.rc.b_mb_tree = 1; 
			m_en_param.rc.i_lookahead = 0;

			//预测相关
			m_en_param.analyse.i_luma_deadzone[0] = 21;
			m_en_param.analyse.i_luma_deadzone[1] = 11;
			m_en_param.analyse.b_psnr = 1; 
			m_en_param.analyse.b_ssim = 1; 
			m_en_param.analyse.b_psy=0;/* Toggle all psy optimizations */
			m_en_param.analyse.f_psy_rd = 0;/* Psy RD strength */
			m_en_param.analyse.f_psy_trellis = 0;/* Psy trellis strength */
			m_en_param.analyse.b_transform_8x8 = 1;
			m_en_param.analyse.i_weighted_pred = X264_WEIGHTP_SMART;
			m_en_param.analyse.b_weighted_bipred = 1;
			m_en_param.analyse.i_noise_reduction = 0;//0~100000噪声去除  
			m_en_param.analyse.b_dct_decimate = 1;
			m_en_param.analyse.b_fast_pskip = 1;
			m_en_param.analyse.b_mixed_references=1;
			m_en_param.analyse.b_chroma_me = 1;
			m_en_param.analyse.i_subpel_refine = 7;
			m_en_param.analyse.i_mv_range_thread = -1;
			m_en_param.analyse.i_mv_range = -1; 
			m_en_param.analyse.i_chroma_qp_offset = -2;  
			m_en_param.analyse.i_trellis = 2; 
			m_en_param.analyse.i_direct_mv_pred = X264_DIRECT_PRED_SPATIAL;
			m_en_param.analyse.i_me_method = X264_ME_UMH;//十字形多边形搜索算法
			//m_en_param.analyse.b_bframe_rdo = 1;//B帧也运动估计 ....???
			m_en_param.analyse.i_me_range = 64; 
			m_en_param.analyse.intra = X264_ANALYSE_I4x4;
			m_en_param.analyse.inter = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8| X264_ANALYSE_PSUB8x8| X264_ANALYSE_PSUB16x16 |X264_ANALYSE_BSUB16x16;

			//日志相关
			m_en_param.pf_log = NULL;//x264_log_default 
			m_en_param.p_log_private = NULL;
			m_en_param.i_log_level = X264_LOG_NONE;
		}
		break;
	case ROOM_VIDEO_CQP_BIG://大视频
		{
			//PrintX264Param(&m_en_param);
			//视频属性相关
			//m_en_param.cpu = X264_CPU_MMXEXT|X264_CPU_SSE|X264_CPU_SSE2;//x264_cpu_detect();
			m_en_param.i_threads = X264_THREADS_AUTO; 
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;//帧率
			m_en_param.i_fps_den = 1;
			m_en_param.i_timebase_den = m_en_param.i_fps_num;
			m_en_param.i_timebase_num = m_en_param.i_fps_den;
			m_en_param.i_keyint_min = KEY_DISTANCE;//场景切换少于次值编码位I, 而不是 IDR.
			m_en_param.i_keyint_max = KEY_DISTANCE;//在此间隔设置IDR关键帧
			m_en_param.b_deterministic	= 1;

			m_en_param.i_bframe = 7;
			m_en_param.i_bframe_pyramid=0;
			m_en_param.i_frame_reference = 9;
			m_en_param.i_bframe_bias =100;
			m_en_param.i_bframe_adaptive = X264_B_ADAPT_NONE;//X264_B_ADAPT_FAST;//X264_B_ADAPT_TRELLIS; 
			m_en_param.i_scenecut_threshold = 100; 

			m_en_param.i_deblocking_filter_alphac0	= 3; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta		= 3; //[-6, 6]  同上
			m_en_param.b_deblocking_filter			= 1; 
			m_en_param.b_intra_refresh				= 0;    
			m_en_param.b_cabac				= 1;
			m_en_param.i_cabac_init_idc		= -1;//???
			m_en_param.b_visualize			= 0;	
			m_en_param.b_annexb				= 1;
			m_en_param.i_sync_lookahead = X264_SYNC_LOOKAHEAD_AUTO;

			m_en_param.i_csp			= X264_CSP_I420;
			m_en_param.vui.i_sar_width  = 0;
			m_en_param.vui.i_sar_height = 0;
			m_en_param.vui.i_overscan   = 0;  /* 0=undef, 1=no overscan, 2=overscan */
			m_en_param.vui.i_vidformat  = 5;  /* undef */
			m_en_param.vui.b_fullrange  = 1;  /* on */
			m_en_param.vui.i_colorprim  = 1;  /* undef */ 
			m_en_param.vui.i_transfer   = 2;  /* undef */
			m_en_param.vui.i_colmatrix  = 1;  /* undef */ 
			m_en_param.vui.i_chroma_loc = 5;  // 色度样本指定

			m_en_param.b_interlaced		= 0;//纯交错模式
			m_en_param.i_slice_max_size = 0;
			m_en_param.i_slice_max_mbs	= 0; 
			m_en_param.i_slice_count	= 0; 
			m_en_param.i_level_idc      = -1;

			//Muxing
			m_en_param.b_repeat_headers = 1; 
			m_en_param.b_aud			= 0;

			//量化相关
			m_en_param.i_cqm_preset = X264_CQM_FLAT;//X264_CQM_JVT;  自定义量化矩阵(CQM),初始化量化模式为flat 0
			memset(m_en_param.cqm_4iy,16,16);
			memset(m_en_param.cqm_4ic,16,16);
			memset(m_en_param.cqm_4py,16,16);
			memset(m_en_param.cqm_4pc,16,16);
			memset(m_en_param.cqm_8iy,16,64);
			memset(m_en_param.cqm_8py,16,64);
			//码率控制相关
			m_en_param.rc.i_rc_method	= X264_RC_CRF; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率 X264_RC_ABR平均码率 
			m_en_param.rc.i_qp_constant = QUALITYLIST[m_enUsedType][m_qp_index].i_qp_constant;//23;
			m_en_param.rc.f_rf_constant = QUALITYLIST[m_enUsedType][m_qp_index].f_rf_constant;//23.0;
			m_en_param.rc.f_rf_constant_max = 0.0;
			m_en_param.rc.i_qp_min	= QUALITYLIST[m_enUsedType][m_qp_index].i_qp_min;//5;//最小量化值
			m_en_param.rc.i_qp_max	= QUALITYLIST[m_enUsedType][m_qp_index].i_qp_max;//35;//最大量化值
			m_en_param.rc.i_qp_step = 4;//量化步长 /* max QP step between frames */
			m_en_param.rc.f_qcompress	= 0.9; // 0.0 => cbr, 1.0 => constant qp
			m_en_param.rc.f_rate_tolerance = 0.1;//平均码率容限   0.1~100.0
			m_en_param.rc.i_bitrate = QUALITYLIST[m_enUsedType][m_qp_index].i_bitrate;// 60;//平均码率
			m_en_param.rc.i_vbv_max_bitrate = QUALITYLIST[m_enUsedType][m_qp_index].i_vbv_max_bitrate; //60;//平均码率 vbv 最大瞬时码率
			m_en_param.rc.i_vbv_buffer_size = 1024;
			m_en_param.rc.f_vbv_buffer_init = 0.9;
			//m_en_param.rc.b_cbr = 1;//是否使用码率控制
			m_en_param.rc.b_stat_write = 0; //是否允许写状态到文件 影响效率 不允许
			m_en_param.rc.psz_stat_out = "x264.log";
			m_en_param.rc.b_stat_read = 0;//是否允许读状态从文件 影响效率 不允许
			m_en_param.rc.psz_stat_in = "x264.log";
			m_en_param.rc.f_ip_factor = QUALITYLIST[m_enUsedType][m_qp_index].f_ip_factor; //1.4;//I帧和P帧之间的量化系数
			m_en_param.rc.f_pb_factor = QUALITYLIST[m_enUsedType][m_qp_index].f_pb_factor; //1.3;//P帧和B帧之间的量化系数
			m_en_param.rc.i_aq_mode = X264_AQ_VARIANCE;
			m_en_param.rc.f_aq_strength = QUALITYLIST[m_enUsedType][m_qp_index].f_aq_strength;
			m_en_param.rc.f_qblur = 0.5;
			m_en_param.rc.f_complexity_blur = 20;
			m_en_param.rc.i_zones = 0;
			m_en_param.rc.b_mb_tree = 1; 
			m_en_param.rc.i_lookahead = 0;

			//预测相关
			m_en_param.analyse.i_luma_deadzone[0] = 21;
			m_en_param.analyse.i_luma_deadzone[1] = 11;
			m_en_param.analyse.b_psnr = 1; 
			m_en_param.analyse.b_ssim = 1; 
			m_en_param.analyse.b_psy=0;/* Toggle all psy optimizations */
			m_en_param.analyse.f_psy_rd = 0;/* Psy RD strength */
			m_en_param.analyse.f_psy_trellis = 0;/* Psy trellis strength */
			m_en_param.analyse.b_transform_8x8 = 1;
			m_en_param.analyse.i_weighted_pred = X264_WEIGHTP_SMART;
			m_en_param.analyse.b_weighted_bipred = 1;
			m_en_param.analyse.i_noise_reduction = 0;//0~100000噪声去除  
			m_en_param.analyse.b_dct_decimate = 1;
			m_en_param.analyse.b_fast_pskip = 1;
			m_en_param.analyse.b_mixed_references=1;
			m_en_param.analyse.b_chroma_me = 1;
			m_en_param.analyse.i_subpel_refine = 5;
			m_en_param.analyse.i_mv_range_thread = -1;
			m_en_param.analyse.i_mv_range = -1; 
			m_en_param.analyse.i_chroma_qp_offset = -2;  
			m_en_param.analyse.i_trellis = 2; 
			m_en_param.analyse.i_direct_mv_pred = X264_DIRECT_PRED_SPATIAL;
			m_en_param.analyse.i_me_method = X264_ME_UMH;//十字形多边形搜索算法
			//m_en_param.analyse.b_bframe_rdo = 1;//B帧也运动估计 ....???
			m_en_param.analyse.i_me_range = 64; 
			m_en_param.analyse.intra = X264_ANALYSE_I4x4 /*| X264_ANALYSE_I8x8*/;
			m_en_param.analyse.inter = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8| X264_ANALYSE_PSUB8x8| X264_ANALYSE_PSUB16x16 |X264_ANALYSE_BSUB16x16;

			//日志相关
			m_en_param.pf_log = NULL;//x264_log_default 
			m_en_param.p_log_private = NULL;
			m_en_param.i_log_level = X264_LOG_NONE;
		}
		break;
	case ROOM_VIDEO_CQP_SMAL://小视频
		{
			//PrintX264Param(&m_en_param);
			//视频属性相关
			//m_en_param.cpu = X264_CPU_MMXEXT|X264_CPU_SSE|X264_CPU_SSE2;//x264_cpu_detect();
			m_en_param.i_threads = X264_THREADS_AUTO; 
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;//帧率
			m_en_param.i_fps_den = 1;
			m_en_param.i_timebase_den = m_en_param.i_fps_num;
			m_en_param.i_timebase_num = m_en_param.i_fps_den;
			m_en_param.i_keyint_min = KEY_DISTANCE;//场景切换少于次值编码位I, 而不是 IDR.
			m_en_param.i_keyint_max = KEY_DISTANCE;//在此间隔设置IDR关键帧
			m_en_param.b_deterministic	= 1;

			m_en_param.i_bframe = 7;
			m_en_param.i_bframe_pyramid=0;
			m_en_param.i_frame_reference = 9;
			m_en_param.i_bframe_bias =100;
			m_en_param.i_bframe_adaptive = X264_B_ADAPT_NONE;//X264_B_ADAPT_FAST;//X264_B_ADAPT_TRELLIS; 
			m_en_param.i_scenecut_threshold = 100; 

			m_en_param.i_deblocking_filter_alphac0 = 3; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 3; //[-6, 6]  同上
			m_en_param.b_deblocking_filter = 1; 
			m_en_param.b_intra_refresh=0;    
			m_en_param.b_cabac = 1;
			m_en_param.i_cabac_init_idc = -1;//???
			m_en_param.b_visualize=0;	
			m_en_param.b_annexb = 1;
			m_en_param.i_sync_lookahead = X264_SYNC_LOOKAHEAD_AUTO;

			m_en_param.i_csp			= X264_CSP_I420;
			m_en_param.vui.i_sar_width  = 0;
			m_en_param.vui.i_sar_height = 0;
			m_en_param.vui.i_overscan   = 0;  /* 0=undef, 1=no overscan, 2=overscan */
			m_en_param.vui.i_vidformat  = 5;  /* undef */
			m_en_param.vui.b_fullrange  = 1;  /* on */
			m_en_param.vui.i_colorprim  = 1;  /* undef */ 
			m_en_param.vui.i_transfer   = 2;  /* undef */
			m_en_param.vui.i_colmatrix  = 1;  /* undef */ 
			m_en_param.vui.i_chroma_loc = 5;  // 色度样本指定

			m_en_param.b_interlaced = 0;//纯交错模式
			m_en_param.i_slice_max_size = 0;
			m_en_param.i_slice_max_mbs = 0; 
			m_en_param.i_slice_count = 0; 
			m_en_param.i_level_idc      = -1;

			//Muxing
			m_en_param.b_repeat_headers = 1; 
			m_en_param.b_aud = 0;

			//量化相关
			m_en_param.i_cqm_preset = X264_CQM_FLAT;//X264_CQM_JVT;  自定义量化矩阵(CQM),初始化量化模式为flat 0
			memset(m_en_param.cqm_4iy,16,16);
			memset(m_en_param.cqm_4ic,16,16);
			memset(m_en_param.cqm_4py,16,16);
			memset(m_en_param.cqm_4pc,16,16);
			memset(m_en_param.cqm_8iy,16,64);
			memset(m_en_param.cqm_8py,16,64);

			//码率控制相关
			m_en_param.rc.i_rc_method = X264_RC_CRF; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率 X264_RC_ABR平均码率 
			m_en_param.rc.i_qp_constant = QUALITYLIST[m_enUsedType][m_qp_index].i_qp_constant;//23;
			m_en_param.rc.f_rf_constant = QUALITYLIST[m_enUsedType][m_qp_index].f_rf_constant;//23.0;
			m_en_param.rc.f_rf_constant_max = 0.0;
			m_en_param.rc.i_qp_min = QUALITYLIST[m_enUsedType][m_qp_index].i_qp_min;//5;//最小量化值
			m_en_param.rc.i_qp_max = QUALITYLIST[m_enUsedType][m_qp_index].i_qp_max;//35;//最大量化值
			m_en_param.rc.i_qp_step = 4;//量化步长 /* max QP step between frames */
			m_en_param.rc.f_qcompress = 0.9; // 0.0 => cbr, 1.0 => constant qp
			m_en_param.rc.f_rate_tolerance = 0.1;//平均码率容限   0.1~100.0
			m_en_param.rc.i_bitrate = QUALITYLIST[m_enUsedType][m_qp_index].i_bitrate;// 60;//平均码率
			m_en_param.rc.i_vbv_max_bitrate = QUALITYLIST[m_enUsedType][m_qp_index].i_vbv_max_bitrate; //60;//平均码率 vbv 最大瞬时码率
			m_en_param.rc.i_vbv_buffer_size = 1024;
			m_en_param.rc.f_vbv_buffer_init = 0.9;
			//m_en_param.rc.b_cbr = 1;//是否使用码率控制
			m_en_param.rc.b_stat_write = 0; //是否允许写状态到文件 影响效率 不允许
			m_en_param.rc.psz_stat_out = "x264.log";
			m_en_param.rc.b_stat_read = 0;//是否允许读状态从文件 影响效率 不允许
			m_en_param.rc.psz_stat_in = "x264.log";
			m_en_param.rc.f_ip_factor = QUALITYLIST[m_enUsedType][m_qp_index].f_ip_factor; //1.4;//I帧和P帧之间的量化系数
			m_en_param.rc.f_pb_factor = QUALITYLIST[m_enUsedType][m_qp_index].f_pb_factor; //1.3;//P帧和B帧之间的量化系数
			m_en_param.rc.i_aq_mode = X264_AQ_VARIANCE;
			m_en_param.rc.f_aq_strength = QUALITYLIST[m_enUsedType][m_qp_index].f_aq_strength;
			m_en_param.rc.f_qblur = 0.5;
			m_en_param.rc.f_complexity_blur = 20;
			m_en_param.rc.i_zones = 0;
			m_en_param.rc.b_mb_tree = 1; 
			m_en_param.rc.i_lookahead = 0;

			//预测相关
			m_en_param.analyse.i_luma_deadzone[0] = 21;
			m_en_param.analyse.i_luma_deadzone[1] = 11;
			m_en_param.analyse.b_psnr = 1; 
			m_en_param.analyse.b_ssim = 1; 
			m_en_param.analyse.b_psy=0;/* Toggle all psy optimizations */
			m_en_param.analyse.f_psy_rd = 0;/* Psy RD strength */
			m_en_param.analyse.f_psy_trellis = 0;/* Psy trellis strength */
			m_en_param.analyse.b_transform_8x8 = 1;
			m_en_param.analyse.i_weighted_pred = X264_WEIGHTP_SMART;
			m_en_param.analyse.b_weighted_bipred = 1;
			m_en_param.analyse.i_noise_reduction = 0;//0~100000噪声去除  
			m_en_param.analyse.b_dct_decimate = 1;
			m_en_param.analyse.b_fast_pskip = 0;
			m_en_param.analyse.b_mixed_references=1;
			m_en_param.analyse.b_chroma_me = 1;
			m_en_param.analyse.i_subpel_refine = 7;
			m_en_param.analyse.i_mv_range_thread = -1;
			m_en_param.analyse.i_mv_range = -1; 
			m_en_param.analyse.i_chroma_qp_offset = -2;  
			m_en_param.analyse.i_trellis = 2; 
			m_en_param.analyse.i_direct_mv_pred = X264_DIRECT_PRED_SPATIAL;
			m_en_param.analyse.i_me_method = X264_ME_UMH;//十字形多边形搜索算法
			//m_en_param.analyse.b_bframe_rdo = 1;//B帧也运动估计 ....???
			m_en_param.analyse.i_me_range = 64; 
			m_en_param.analyse.intra = X264_ANALYSE_I4x4;
			m_en_param.analyse.inter = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8| X264_ANALYSE_PSUB8x8| X264_ANALYSE_PSUB16x16 |X264_ANALYSE_BSUB16x16;

			//日志相关
			m_en_param.pf_log = NULL;//x264_log_default 
			m_en_param.p_log_private = NULL;
			m_en_param.i_log_level = X264_LOG_NONE;
		}
		break;
	case ROOM_VIDEO_CRF_OLD:
		{
			//m_en_param.cpu = X264_CPU_MMXEXT|X264_CPU_SSE|X264_CPU_SSE2;//x264_cpu_detect();
			m_en_param.i_threads = X264_THREADS_AUTO; 
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.b_deterministic	= 1; 
			m_en_param.i_fps_num  = 10;//帧率
			m_en_param.i_fps_den = 1; 
			m_en_param.i_keyint_min = 25;//场景切换少于次值编码位I, 而不是 IDR.
			m_en_param.i_keyint_max = 40;//在此间隔设置IDR关键帧

			m_en_param.i_bframe = 5;//最大共出现B帧
			m_en_param.i_bframe_pyramid=0;//2;//允许B帧作为新的参考帧
			m_en_param.i_frame_reference = 12;//参考帧最大帧数 
			m_en_param.i_bframe_bias =100;//B帧被P代替的概率
			m_en_param.i_bframe_adaptive = X264_B_ADAPT_NONE;//X264_B_ADAPT_FAST;//X264_B_ADAPT_TRELLIS; //自适应B帧判定1
			m_en_param.i_scenecut_threshold = 100; //如何积极地插入额外的I帧	
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.b_intra_refresh=0;    
			//m_en_param.b_interlaced = 0;//纯交错模式

			m_en_param.b_cabac = 1;//打开cabac
			m_en_param.i_cabac_init_idc = 2;//???
			m_en_param.analyse.i_trellis = 2; 
			m_en_param.rc.i_qp_constant = 20;//m_en_nQP;	 //qp的初始值，最大最小的qp值，默认26  0~51
			m_en_param.rc.f_rf_constant = 1;//m_en_nQP;
			m_en_param.rc.i_qp_min = 20;//最小量化值
			m_en_param.rc.i_qp_max = 32;//最大量化值
			m_en_param.rc.i_qp_step = 4;//量化步长
			m_en_param.rc.i_rc_method = X264_RC_CRF; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率 X264_RC_ABR平均码率 

			// 			m_en_param.rc.i_rc_method = X264_RC_ABR;   
			// 			m_en_param.rc.i_bitrate = 0;
			// 			m_en_param.rc.f_rate_tolerance = 1.0;
			// 			m_en_param.rc.i_vbv_max_bitrate = 0;
			// 			m_en_param.rc.i_vbv_buffer_size = 0;
			// 			m_en_param.rc.f_vbv_buffer_init = 0.9;

			m_en_param.rc.i_bitrate = 73;
			m_en_param.rc.i_vbv_max_bitrate = 73;//平均码率 vbv
			m_en_param.rc.i_vbv_buffer_size = 200;
			m_en_param.rc.f_vbv_buffer_init = 0.9;
			m_en_param.rc.f_rate_tolerance = 0.8;//码率容限   0.1~100.0

			m_en_param.i_csp			= X264_CSP_I420;
			m_en_param.vui.i_sar_width  = 0;
			m_en_param.vui.i_sar_height = 0;
			m_en_param.vui.i_overscan   = 0;  /* 0=undef, 1=no overscan, 2=overscan */
			m_en_param.vui.i_vidformat  = 5;  /* undef */
			m_en_param.vui.b_fullrange  = 1;  /* on */
			m_en_param.vui.i_colorprim  = 2;  /* undef */
			m_en_param.vui.i_transfer   = 2;  /* undef */
			m_en_param.vui.i_colmatrix  = 2;  /* undef */
			m_en_param.vui.i_chroma_loc = 3;  //调整颜射对比度  0-5  
			m_en_param.i_level_idc      = 30;

			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;
			m_en_param.i_sync_lookahead = 0;//自动选择超前缓冲大小
			PrintX264Param(&m_en_param);

			m_en_param.rc.b_stat_write = 0;
			//m_en_param.rc.psz_stat_out = "x264.log";
			m_en_param.rc.b_stat_read = 0;
			//m_en_param.rc.psz_stat_in = "x264.log";
			m_en_param.rc.f_ip_factor = 1.4;
			m_en_param.rc.f_pb_factor = 1.3;
			m_en_param.rc.i_aq_mode = X264_AQ_VARIANCE;//通过减少色度量化偏移量的方法来提高亮度的总体质量
			m_en_param.rc.f_aq_strength = 1.3;
			m_en_param.rc.f_qcompress = 1.0; // 0.0 => cbr, 1.0 => constant qp
			m_en_param.rc.f_qblur = 0.5;
			m_en_param.rc.f_complexity_blur = 20;
			m_en_param.rc.i_zones = 0;
			m_en_param.rc.b_mb_tree = 1;
			m_en_param.rc.i_lookahead = 0;

			m_en_param.i_cqm_preset = X264_CQM_FLAT;//X264_CQM_JVT;
			m_en_param.analyse.i_chroma_qp_offset = 0;  //-12~12   
			m_en_param.analyse.b_fast_pskip = 1;//p帧跳过检测
			m_en_param.analyse.b_dct_decimate = 1;//p帧联合编码
			m_en_param.analyse.i_noise_reduction = 0;//0~100000噪声去除

			m_en_param.analyse.i_luma_deadzone[0] = 21;
			m_en_param.analyse.i_luma_deadzone[1] = 11;

			m_en_param.analyse.b_psnr = 1;
			m_en_param.analyse.b_ssim = 1;
			m_en_param.analyse.b_chroma_me = 1;
			m_en_param.analyse.i_mv_range_thread = -1;
			m_en_param.analyse.i_mv_range = -1; // set from level_idc
			m_en_param.analyse.i_subpel_refine = 7; 

			m_en_param.analyse.i_direct_mv_pred = X264_DIRECT_PRED_SPATIAL;
			m_en_param.analyse.f_psy_rd = 1.0;
			m_en_param.analyse.f_psy_trellis = 1; 
			m_en_param.analyse.i_me_range = 32;  
			//m_en_param.analyse.b_transform_8x8 = 0;
			m_en_param.analyse.i_weighted_pred = X264_WEIGHTP_SMART;//智能判断
			m_en_param.analyse.b_weighted_bipred = 1;

			m_en_param.pf_log = NULL;//x264_log_default 
			m_en_param.p_log_private = NULL;
			m_en_param.i_log_level = X264_LOG_NONE;

			m_en_param.analyse.i_me_method = X264_ME_UMH; 
			m_en_param.analyse.inter = X264_ANALYSE_I4x4; 
			m_en_param.analyse.intra = X264_ANALYSE_I4x4; 
		}
		break;
	case ROOM_VIDEO_CRF_MAX: //7 ~ 17k 浮动码率  
		{
			m_en_param.i_threads = X264_THREADS_AUTO; 
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;
			m_en_param.i_fps_den = 1;
			m_en_param.i_keyint_min = 30;
			m_en_param.i_keyint_max = 60;
			m_en_param.i_log_level = X264_LOG_NONE;
			m_en_param.rc.i_qp_constant = m_en_nQP;	
			m_en_param.rc.i_rc_method = X264_RC_CRF; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率 X264_RC_ABR平均码率 

			m_en_param.rc.i_bitrate = 120;
			m_en_param.rc.i_vbv_max_bitrate = 120;

			m_en_param.rc.f_rate_tolerance = 1.0;//码率容限
			m_en_param.rc.i_vbv_buffer_size = 240;//缓冲区大小
			m_en_param.rc.f_vbv_buffer_init = 0.9;//<=1: fraction of buffer_size. >1: kbit码率控制缓冲区数据保留的最大数据量与缓冲区大小之比，范围0~1.0，默认0.9

			m_en_param.rc.b_mb_tree = 1;
			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;

			PrintX264Param(&m_en_param);

			m_en_param.i_frame_reference = 8;//参考帧最大帧数
			m_en_param.vui.b_fullrange = 1;
			m_en_param.i_sync_lookahead = 0;//自动选择超前缓冲大小
			m_en_param.vui.i_colorprim = 2; //undef原始色度格式
			m_en_param.vui.i_transfer  = 2; //undef 转换方式
			m_en_param.vui.i_colmatrix = 2; //undef 色度矩阵设置
			//m_en_param.vui.i_chroma_loc= 2; //调整颜射对比度  0-5  
			m_en_param.i_cabac_init_idc = 2;
			m_en_param.rc.i_aq_mode = X264_AQ_VARIANCE;//通过减少色度量化偏移量的方法来提高亮度的总体质量
			m_en_param.rc.f_aq_strength = 1.3;
			m_en_param.rc.f_qcompress = 0.8; // 0.0 => cbr, 1.0 => constant qp
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.analyse.i_me_method = X264_ME_DIA;//使用砖石形搜索算法 最优
			m_en_param.analyse.inter = X264_ANALYSE_I8x8|X264_ANALYSE_I4x4;
			//m_en_param.rc.f_qblur = 0.0;   //时间上模糊量化
			//m_en_param.rc.f_complexity_blur = 20; //时间上模糊复杂性
			// 			m_en_param.i_bframe = 5;//最大共出现B帧
			// 			m_en_param.i_scenecut_threshold = 40; //如何积极地插入额外的I帧
			// 			m_en_param.i_bframe_adaptive=X264_B_ADAPT_TRELLIS;
			// 			m_en_param.i_bframe_bias = -100;//B帧被P帧代替的概率
			// 			m_en_param.i_bframe_pyramid=1;//允许B帧作为新的参考帧
			// 			m_en_param.b_cabac=1;//开启上下文自适应二进制编码
			// 			m_en_param.i_frame_reference = 6;//参考帧最大帧数
			// 			m_en_param.i_deblocking_filter_alphac0 = 1; //[-6, 6] -6 锐化
			// 			m_en_param.i_deblocking_filter_beta = 2; //[-6, 6]  模糊

			// 			m_en_param.rc.i_qp_min=25;
			// 			m_en_param.rc.i_qp_max=30;
			// 			m_en_param.rc.i_qp_step=4;//量化质量变化步长
			//			m_en_param.vui.i_chroma_loc= 2;//亮度

		}
		break;
	case ROOM_VIDEO_CRF_MIN://4 ~ 11K 浮动码率
		{
			m_en_param.i_threads = X264_THREADS_AUTO; 
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;
			m_en_param.i_fps_den = 1;
			m_en_param.i_keyint_min = 30;
			m_en_param.i_keyint_max = 60;
			m_en_param.i_log_level = X264_LOG_NONE;
			m_en_param.rc.i_qp_constant = m_en_nQP;	
			m_en_param.rc.i_rc_method = X264_RC_CRF; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率 X264_RC_ABR平均码率 

			m_en_param.rc.i_bitrate = 78;
			m_en_param.rc.i_vbv_max_bitrate = 80;
			m_en_param.rc.f_rate_tolerance = 1.0;//码率容限
			m_en_param.rc.i_vbv_buffer_size = 160;//缓冲区大小
			m_en_param.rc.f_vbv_buffer_init = 0.9;//<=1: fraction of buffer_size. >1: kbit码率控制缓冲区数据保留的最大数据量与缓冲区大小之比，范围0~1.0，默认0.9

			m_en_param.rc.b_mb_tree = 1;
			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;

			PrintX264Param(&m_en_param);

			m_en_param.i_frame_reference = 8;//参考帧最大帧数
			m_en_param.vui.b_fullrange = 1;
			m_en_param.i_sync_lookahead = 0;//自动选择超前缓冲大小
			m_en_param.vui.i_colorprim = 2; //undef原始色度格式
			m_en_param.vui.i_transfer  = 2; //undef 转换方式
			m_en_param.vui.i_colmatrix = 2; //undef 色度矩阵设置
			//m_en_param.vui.i_chroma_loc= 2; //调整颜射对比度  0-5  
			m_en_param.i_cabac_init_idc = 2;
			m_en_param.rc.i_aq_mode = X264_AQ_VARIANCE;//通过减少色度量化偏移量的方法来提高亮度的总体质量
			m_en_param.rc.f_aq_strength = 1.3;
			m_en_param.rc.f_qcompress = 0.9; // 0.0 => cbr, 1.0 => constant qp
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.analyse.i_me_method = X264_ME_DIA;//使用砖石形搜索算法 最优
			m_en_param.analyse.inter = X264_ANALYSE_I8x8|X264_ANALYSE_I4x4;
		}
		break;
	case ROOM_VIDEO_CQP_224: //恒定质量
		{
			m_en_param.i_threads = X264_THREADS_AUTO; //1
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;
			m_en_param.i_fps_den = 1;
			m_en_param.i_keyint_min = 30;
			m_en_param.i_keyint_max = 60;
			m_en_param.i_log_level = X264_LOG_NONE;
			m_en_param.rc.i_qp_constant = m_en_nQP;	
			m_en_param.rc.i_rc_method = X264_RC_CQP; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率

			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;

			PrintX264Param(&m_en_param);

			m_en_param.i_frame_reference = 8;//参考帧最大帧数
			m_en_param.i_sync_lookahead = 0;
			m_en_param.vui.b_fullrange = 1;
			m_en_param.vui.i_colorprim = 2; //undef原始色度格式
			m_en_param.vui.i_transfer  = 2; //undef 转换方式
			m_en_param.vui.i_colmatrix = 2; //undef 色度矩阵设置
			// 			m_en_param.vui.i_chroma_loc= 2;
			m_en_param.rc.i_aq_mode = X264_AQ_VARIANCE;//通过减少色度量化偏移量的方法来提高亮度的总体质量
			m_en_param.rc.f_aq_strength = 1.3;
			m_en_param.rc.f_qcompress = 0.9; // 0.0 => cbr, 1.0 => constant qp
			// 			m_en_param.rc.f_qblur = 1.0;   //时间上模糊量化
			// 			m_en_param.rc.f_complexity_blur = 20; //时间上模糊复杂性
			// 			m_en_param.rc.i_zones = 0; //number of zone_t's
			// 			m_en_param.rc.b_mb_tree = 1; // Macroblock-tree ratecontrol

			m_en_param.i_cabac_init_idc = 2;
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.analyse.i_me_method = X264_ME_DIA;//使用砖石形搜索算法 最优
			m_en_param.analyse.intra = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8; //analyse 帧内分析
			m_en_param.analyse.inter = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8| X264_ANALYSE_PSUB16x16 | X264_ANALYSE_BSUB16x16; //桢间分析
		}
		break;
	case ROOM_VIDEO_CQP_216:
		{
			m_en_param.i_threads = X264_THREADS_AUTO; //1
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;
			m_en_param.i_fps_den = 1;
			m_en_param.i_keyint_min = 30;
			m_en_param.i_keyint_max = 60;
			m_en_param.i_log_level = X264_LOG_NONE;
			m_en_param.rc.i_qp_constant = m_en_nQP;	
			m_en_param.rc.i_rc_method = X264_RC_CQP; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率

			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;

			PrintX264Param(&m_en_param);

			m_en_param.i_frame_reference = 8;//参考帧最大帧数
			m_en_param.i_sync_lookahead = 0;
			m_en_param.vui.b_fullrange = 1;
			m_en_param.vui.i_colorprim = 2; //undef原始色度格式
			m_en_param.vui.i_transfer  = 2; //undef 转换方式
			m_en_param.vui.i_colmatrix = 2; //undef 色度矩阵设置
			m_en_param.i_cabac_init_idc = 2;
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.analyse.i_me_method = X264_ME_DIA;//使用砖石形搜索算法 最优
			m_en_param.analyse.intra = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8; //analyse 帧内分析
			m_en_param.analyse.inter = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8| X264_ANALYSE_PSUB16x16 | X264_ANALYSE_BSUB16x16; //桢间分析
		}
		break;
	case ROOM_VIDEO_CQP_232:
		{
			m_en_param.i_threads = X264_THREADS_AUTO; 
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;
			m_en_param.i_fps_den = 1;
			m_en_param.i_keyint_min = 30;
			m_en_param.i_keyint_max = 60;
			m_en_param.i_log_level = X264_LOG_NONE;
			m_en_param.rc.i_qp_constant = m_en_nQP;	
			m_en_param.rc.i_rc_method = X264_RC_CQP; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率

			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;

			PrintX264Param(&m_en_param);

			m_en_param.i_frame_reference = 8;//参考帧最大帧数
			//	m_en_param.i_bframe = 0;//两个参考帧中的B帧数目
			//	m_en_param.i_bframe_adaptive = X264_B_ADAPT_FAST;//自适应B帧判定
			m_en_param.i_sync_lookahead = 0;
			m_en_param.vui.b_fullrange = 1;
			m_en_param.vui.i_colorprim = 2; //undef原始色度格式
			m_en_param.vui.i_transfer  = 2; //undef 转换方式
			m_en_param.vui.i_colmatrix = 2; //undef 色度矩阵设置
			m_en_param.i_cabac_init_idc = 2;
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			// m_en_param.rc.i_qp_min = 10; //允许的最小量化值
			// m_en_param.rc.i_qp_max = 60; //允许的最大量化值
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.analyse.i_me_method = X264_ME_DIA;//使用砖石形搜索算法 最优
		}
		break;
	case ROOM_VIDEO_CQP_208:
		{
			m_en_param.i_threads = X264_THREADS_AUTO; 
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;
			m_en_param.i_fps_den = 1;
			m_en_param.i_keyint_min = 30;
			m_en_param.i_keyint_max = 60;
			m_en_param.i_log_level = X264_LOG_NONE;
			m_en_param.rc.i_qp_constant = m_en_nQP;	
			m_en_param.rc.i_rc_method = X264_RC_CQP; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率

			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;

			PrintX264Param(&m_en_param);

			m_en_param.i_frame_reference = 8;//参考帧最大帧数
			//	m_en_param.i_bframe = 0;//两个参考帧中的B帧数目
			//	m_en_param.i_bframe_adaptive = X264_B_ADAPT_FAST;//自适应B帧判定
			m_en_param.i_sync_lookahead = 0;
			m_en_param.vui.b_fullrange = 1;
			m_en_param.vui.i_colorprim = 2; //undef原始色度格式
			m_en_param.vui.i_transfer  = 2; //undef 转换方式
			m_en_param.vui.i_colmatrix = 2; //undef 色度矩阵设置
			m_en_param.i_cabac_init_idc = 2;
			// 	m_en_param.rc.i_qp_min = 10; //允许的最小量化值
			// 	m_en_param.rc.i_qp_max = 60; //允许的最大量化值
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.analyse.i_me_method = X264_ME_DIA;//使用砖石形搜索算法 最优
		}
		break;
	case ROOM_VIDEO_ABR_MODE://平均码率
		{
			m_en_param.i_threads = X264_THREADS_AUTO; //1
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;
			m_en_param.i_fps_den = 1;
			m_en_param.i_keyint_min = 30;
			m_en_param.i_keyint_max = 60;
			m_en_param.i_log_level = X264_LOG_NONE;
			m_en_param.rc.i_qp_constant = m_en_nQP;	
			m_en_param.rc.i_rc_method = X264_RC_ABR; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率

			m_en_param.rc.i_bitrate = 80;
			m_en_param.rc.i_vbv_max_bitrate = 120;
			m_en_param.rc.f_rate_tolerance = 1.0;
			m_en_param.rc.i_vbv_buffer_size = 1200;
			m_en_param.rc.f_vbv_buffer_init = 1.0;

			m_en_param.rc.b_mb_tree = 1;
			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;

			PrintX264Param(&m_en_param);

			m_en_param.i_frame_reference = 8;//参考帧最大帧数
			//	m_en_param.i_bframe = 0;//两个参考帧中的B帧数目
			//	m_en_param.i_bframe_adaptive = X264_B_ADAPT_FAST;//自适应B帧判定
			m_en_param.i_sync_lookahead = 0;
			m_en_param.vui.b_fullrange = 1;
			m_en_param.vui.i_colorprim = 2; //undef原始色度格式
			m_en_param.vui.i_transfer  = 2; //undef 转换方式
			m_en_param.vui.i_colmatrix = 2; //undef 色度矩阵设置
			m_en_param.i_cabac_init_idc = 2;
			// 	m_en_param.rc.i_qp_min = 10; //允许的最小量化值
			// 	m_en_param.rc.i_qp_max = 60; //允许的最大量化值
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.analyse.i_me_method = X264_ME_DIA;//使用砖石形搜索算法 最优
			m_en_param.analyse.intra = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8; //analyse 帧内分析
			m_en_param.analyse.inter = X264_ANALYSE_I4x4 | X264_ANALYSE_I8x8| X264_ANALYSE_PSUB16x16 | X264_ANALYSE_BSUB16x16; //桢间分析
		}
		break;
	default://默认恒定码率
		{
			m_en_param.i_threads = X264_THREADS_AUTO; 
			m_en_param.i_width = m_h264_codec_width;
			m_en_param.i_height = m_h264_codec_height;
			m_en_param.i_fps_num  = 10;
			m_en_param.i_fps_den = 1;
			m_en_param.i_keyint_min = 30;
			m_en_param.i_keyint_max = 60;
			m_en_param.i_log_level = X264_LOG_NONE;
			m_en_param.rc.i_qp_constant = m_en_nQP;	
			m_en_param.rc.i_rc_method = X264_RC_CRF; //X264_RC_CQP恒定质量  X264_RC_CRF恒定码率 X264_RC_ABR平均码率 

			m_en_param.rc.i_bitrate = 78;
			m_en_param.rc.i_vbv_max_bitrate = 80;
			m_en_param.rc.f_rate_tolerance = 0.5;
			m_en_param.rc.i_vbv_buffer_size = 800;
			m_en_param.rc.f_vbv_buffer_init = 1.0;

			m_en_param.rc.b_mb_tree = 1;
			m_en_param.b_repeat_headers = 1;
			m_en_param.b_annexb = 1;

			PrintX264Param(&m_en_param);

			m_en_param.i_frame_reference = 8;//参考帧最大帧数
			m_en_param.vui.b_fullrange = 1;
			m_en_param.i_sync_lookahead = 0;//自动选择超前缓冲大小

			m_en_param.vui.i_colorprim = 2; //undef原始色度格式
			m_en_param.vui.i_transfer  = 2; //undef 转换方式
			m_en_param.vui.i_colmatrix = 2; //undef 色度矩阵设置
			m_en_param.i_cabac_init_idc = 2;
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.i_deblocking_filter_alphac0 = 6; //[-6, 6] -6 亮度滤波器, 6 强
			m_en_param.i_deblocking_filter_beta = 6; //[-6, 6]  同上
			m_en_param.analyse.i_me_method = X264_ME_DIA;//使用砖石形搜索算法 最优
			m_en_param.b_deblocking_filter = 1; //去块效应相关
			m_en_param.analyse.inter = X264_ANALYSE_I8x8|X264_ANALYSE_I4x4;
		}
	}
	//x264_param_apply_fastfirstpass(&m_en_param);//rc.b_stat_read == 0, rc.b_stat_write == 1
	if(0 != x264_param_apply_profile(&m_en_param, "high"))
	{
		return false;
	}

	if ((m_en_h = x264_encoder_open(&m_en_param)) == NULL)
	{
		return false;
	}

	if(x264_picture_alloc(&m_en_picture,X264_CSP_I420,m_h264_codec_width,m_h264_codec_height) != 0)
	{
		return false;
	}

	m_swsContext = sws_getContext(m_nWidth, m_nHeight,
		PIX_FMT_RGB24,
		m_h264_codec_width, m_h264_codec_height,   // 编码器 输入大小320*240     变换成 208 * 156
		PIX_FMT_YUV420P, SWS_LANCZOS, NULL, NULL, NULL);

	return true;
}

void h264Codec::CORelease()
{
	x264_picture_clean(&m_en_picture);
	x264_encoder_close(m_en_h);
	sws_freeContext(m_swsContext);
}

bool h264Codec::RestEncodeSWS()
{
	try
	{
		if (m_swsContext)
			sws_freeContext(m_swsContext);
		m_swsContext = NULL;
		m_swsContext = sws_getContext(m_nWidth, m_nHeight,
			PIX_FMT_RGB24,
			m_h264_codec_width, m_h264_codec_height,   // 编码器 输入大小320*240     变换成 208 * 156
			PIX_FMT_YUV420P, SWS_LANCZOS, NULL, NULL, NULL);
	}
	catch (...)
	{
		Assert(0);
		Trace("h264Codec::RestEncodeSWS() .....操作异常...\n");
	}
	return true;
}

bool h264Codec::RestDecodeSWS()
{
	m_bIsChange = true;
	try
	{

		if (m_swsContext )
			sws_freeContext(m_swsContext);
		m_swsContext = NULL;
		m_swsContext = sws_getContext(m_h264_codec_width,m_h264_codec_height,
			PIX_FMT_YUV420P,
			m_nWidth, m_nHeight,						//修改 从208*156 变换到 m_nWidth*m_nHeight  大小
			PIX_FMT_RGB24, SWS_SINC, NULL, NULL, NULL);
	}
	catch (...)
	{
		Assert(0);
		Trace("h264Codec::RestDecodeSWS() .....操作异常...\n");
	}
	m_bIsChange = false;
	return true;
}

bool h264Codec::SetType(enuVIDEO_TYPE enType)
{
	m_enNewType = enType;
	return true;
}

bool h264Codec::ResetSize()
{
	if (m_enNewType == m_enUsedType)
		return false;

	SetTypeSize(m_enNewType);

	if (m_bEncode)
	{
		ResetQP(m_iQPIndex);
		RestEncodeSWS();
	}
	else
	{
		RestDecodeSWS();
	}
	return true;
}

void h264Codec::ResetQP(int iQPIndex)
{
	m_iframe = 0;
	m_iQPIndex = iQPIndex;
	x264_encoder_delayed_frames(m_en_h);
	x264_encoder_close(m_en_h);
	m_en_h = NULL;
	m_en_param.rc.i_qp_constant = QUALITYLIST[m_enUsedType][iQPIndex].i_qp_constant;
	m_en_param.rc.f_rf_constant = QUALITYLIST[m_enUsedType][iQPIndex].f_rf_constant;
	m_en_param.rc.i_qp_min		= QUALITYLIST[m_enUsedType][iQPIndex].i_qp_min;
	m_en_param.rc.i_qp_max		= QUALITYLIST[m_enUsedType][iQPIndex].i_qp_max;
	m_en_param.rc.i_bitrate		= QUALITYLIST[m_enUsedType][iQPIndex].i_bitrate;
	m_en_param.rc.i_vbv_max_bitrate = QUALITYLIST[m_enUsedType][iQPIndex].i_vbv_max_bitrate;
	m_en_param.rc.f_ip_factor		= QUALITYLIST[m_enUsedType][iQPIndex].f_ip_factor;
	m_en_param.rc.f_pb_factor		= QUALITYLIST[m_enUsedType][iQPIndex].f_pb_factor;

	if(0 != x264_param_apply_profile(&m_en_param, "high"))
		ErrTrace("h264Codec::ResetQP x264_param_apply_profile Error!\n");

	m_en_h = x264_encoder_open(&m_en_param);

	Assert(m_en_h==NULL);
}

void h264Codec::SetKeyFrame(x264_picture_t* p_en_picture)
{
	switch(m_cframe[m_iframe++%49])
	{
	case 0: p_en_picture->i_type = X264_TYPE_B;   break;
	case 1: p_en_picture->i_type = X264_TYPE_IDR; break;
	case 2: p_en_picture->i_type = X264_TYPE_P;   break;
	default:
		p_en_picture->i_type = X264_TYPE_AUTO; break;
	}
}

void h264Codec::SetKeyFrame(x264_picture_t* p_en_picture,int index)
{
	switch(m_cframe[index])
	{
	case 0: p_en_picture->i_type = X264_TYPE_B;   break;
	case 1: p_en_picture->i_type = X264_TYPE_IDR; break;
	case 2: p_en_picture->i_type = X264_TYPE_P;   break;
	default:
		p_en_picture->i_type = X264_TYPE_AUTO; break;
	}
}

enLostType g_entype = enLostType::EN_LEVEL_3;

bool h264Codec::EncodeVideoData(unsigned char *pInData, int iLen, unsigned char *pOutBuf, int *iOutLen, unsigned char *cKeyFrame,bool& bStop)
{
	if(iLen < m_en_param.i_width * m_en_param.i_height * 3)
	{
		return false;
	}

	ResetSize()?(m_iframe = 0):0;

	m_en_param.i_frame_total++;

	int srcStride = m_nWidth*3;//320采样

	int rets = sws_scale(m_swsContext, &pInData, &srcStride, 0, m_nHeight, //变换从 320*240 变换到 sws_getContext 设置的208*156
		m_en_picture.img.plane, m_en_picture.img.i_stride);

	m_en_picture.i_pts = (int64_t)m_en_param.i_frame_total*m_en_param.i_fps_den;

	SetKeyFrame(&m_en_picture);

	static x264_picture_t pic_out;
	x264_nal_t *nal = NULL;
	int i_nal;

	int ret = x264_encoder_encode(m_en_h,&nal,&i_nal,&m_en_picture,&pic_out);
	if (ret <= 0 && !m_bCacheStart)
	{
		//开始7帧相同  不缓存
		int iStartCount = 0;
		while (iStartCount++<7)
		{
			nal = NULL;
			SetKeyFrame(&m_en_picture);
			ret = x264_encoder_encode(m_en_h,&nal,&i_nal,&m_en_picture,&pic_out);
			if (ret>0)  break;
			SwitchToThread();
		}

		m_vecFirst.clear();
		m_vecSecond.clear();
		m_dwFirstMapStartTime = 0;
		m_dwSecondMapStartTime = 0;
	}
	if(ret <= 0) //补帧
	{
		OutputDebugStringA("补帧111111111111111111111\n");
		CVideoDataCache* pData = NULL;
		if (m_bCacheStart && (pData=m_cache.GetListData())!=NULL)
		{
			ErrTrace("从缓存中取帧--------------------------------------------------------------------------m_cache.size()=%d,datalen=%d\n",m_cache.GetListSize(),pData->GetLength());
			memcpy(pOutBuf, pData->GetDataPtr(), pData->GetLength());
			*iOutLen = pData->GetLength();
			m_iframeEx = m_iframe-8;
			if (m_iframeEx<0) m_iframeEx=0;
			m_score[m_iframeEx %SCORE_CALC_LEN] = pData->GetLength();

			switch(pData->GetType())
			{
			case X264_TYPE_AUTO:
				ErrTrace("X264_TYPE_AUTO ----------------\n");
				break;
			case X264_TYPE_IDR:
				ErrTrace("X264_TYPE_IDR ----------------\n");
				break;
			case X264_TYPE_I:
				ErrTrace("X264_TYPE_I ----------------\n");
				break;
			case X264_TYPE_P:
				ErrTrace("X264_TYPE_P ----------------\n");
				break;
			case X264_TYPE_BREF:
				ErrTrace("X264_TYPE_BREF ----------------\n");
				break;
			case X264_TYPE_B:
				ErrTrace("X264_TYPE_B ----------------\n");
				break;
			case X264_TYPE_KEYFRAME:
				ErrTrace("X264_TYPE_KEYFRAME ----------------\n");
				break;
			default:
				ErrTrace("default ----------------\n");
			}

			ErrTrace("从缓存中取帧--------------------------------------------------------------------------m_cache.size()=%d,datalen=%d\n",m_cache.GetListSize(),pData->GetLength());
			delete pData;
			return true;
		}
		return false;
	}
	m_bCacheStart = false;
	*iOutLen = ret;
	BAD_MEM_READ_RETURN(nal[0].p_payload,ret,"x264_encoder_encode 内存读错误",0)
		memcpy(pOutBuf, nal[0].p_payload, ret);

	static unsigned int i_auto_count = 0;
	static unsigned int i_idr_count = 0;
	static unsigned int i_i_count = 0;
	static unsigned int i_P_count = 0;
	static unsigned int i_Bref_count = 0;
	static unsigned int i_B_count = 0;
	static unsigned int i_key_count = 0;
	static unsigned int i_Other_count=0;
	static  int64 i_last_time = 0;
	static unsigned char c_p_distance = 0;

	//static unsigned int 
	*cKeyFrame = pic_out.i_type == X264_TYPE_IDR?KEY_VALUE:0;
	{
		switch(pic_out.i_type)
		{
		case X264_TYPE_AUTO:
			i_auto_count++;
			break;
		case X264_TYPE_IDR:
			i_idr_count++;
			c_p_distance = 0;
			Trace("GetTickCount()-i_last_time=%I64d  time=%I64d\n",GetTickCount()-i_last_time,GetTickCount());
			i_last_time = GetTickCount();
			m_keyFrame_Count = 0;
			break;
		case X264_TYPE_I:
			i_i_count++;
			break;
		case X264_TYPE_P:
			i_P_count++;
			c_p_distance=0;
			*cKeyFrame = c_p_distance;
			break;
		case X264_TYPE_BREF:
			i_Bref_count++;
			break;
		case X264_TYPE_B:
			i_B_count++;
			c_p_distance++;
			*cKeyFrame = c_p_distance;
			break;
		case X264_TYPE_KEYFRAME:
			i_key_count++;
			break;
		default:
			i_Other_count++;
		}
		static int maxFrameSize = 0;
		maxFrameSize = ((ret>maxFrameSize && pic_out.i_type!=X264_TYPE_IDR)?ret:maxFrameSize);

		//ErrTrace("enLostType=%s,m_qp_index_old=%d,KeyNum=%d,SIZE=%d,MAXSIZE=%d,m_lastRate=%d,cKeyFrame=%d,X264_TYPE_AUTO=%d,X264_TYPE_IDR=%d,X264_TYPE_I=%d,X264_TYPE_P=%d,
		//X264_TYPE_BREF=%d,X264_TYPE_B=%d,X264_TYPE_KEYFRAME=%d,Other=%d time = %I64d\n",g_entype==enLostType::EN_LEVEL_1?"EN_LEVEL_1":(g_entype==enLostType::EN_LEVEL_2?"EN_LEVEL_2":"EN_LEVEL_3"),m_qp_index,m_keyFrame_Count,ret,maxFrameSize,m_lastRate,*cKeyFrame,i_auto_count,i_idr_count,i_i_count,i_P_count,i_Bref_count,i_B_count,i_key_count,i_Other_count,GetTickCount());
		m_encodeType = pic_out.i_type;
	}
	unsigned char cType = (unsigned char)m_enUsedType;
	*cKeyFrame = *cKeyFrame | (cType<<4);
	m_keyFrame_Count++;
	//KEY_DISTANCE

	//带宽50s计算一次
	m_iframeEx = m_iframe-8;
	if (m_iframeEx<0) m_iframeEx=0;
	m_score[m_iframeEx %SCORE_CALC_LEN] = ret;
	dwStart = (dwStart==0)?GetTickCount():dwStart;
	dwStart = (m_iframeEx %SCORE_CALC_LEN == 0)?GetTickCount():dwStart;
	if (m_iframeEx %SCORE_CALC_LEN == (SCORE_CALC_LEN-1))
	{
		float total = 0;
		for (int i=0;i<SCORE_CALC_LEN;i++)
		{
			total += m_score[i];
		}

		total /= 1024;
		total *= 1000;
		total /= (GetTickCount()-dwStart);
		m_flastRate = total;


		ErrTrace("视频码流 m_lastRate=%f ========================================\n",m_flastRate);

		m_vecFirst.push_back(m_flastRate);
		m_vecSecond.push_back(m_flastRate);

		if (m_dwFirstMapStartTime == 0) m_dwFirstMapStartTime = GetTickCount();
		if (m_dwSecondMapStartTime == 0) m_dwSecondMapStartTime = GetTickCount();

		ErrTrace("m_qp_index_old=%d m_lastRate=%f m_mapFirt.size()=%d  m_mapSecond.size()=%d m_fAverageRate=%f dwRateCountInter=%d ------------\n",m_qp_index_old,m_flastRate,m_vecFirst.size(),m_vecSecond.size(),m_fAverageRate,RATELIST[m_enUsedType].dwRateCountInter);

		//计算平均码流
		DWORD dwFirt = GetTickCount() - m_dwFirstMapStartTime;
		DWORD dwSecond = GetTickCount() - m_dwSecondMapStartTime;
		std::vector<float> &vecCurrent = (dwFirt > dwSecond)?m_vecFirst:m_vecSecond;
		if (dwFirt>RATELIST[m_enUsedType].dwRateCountInter/*VIDEO_RATE_COUNT_INTER*/ && dwSecond>RATELIST[m_enUsedType].dwRateCountInter/*VIDEO_RATE_COUNT_INTER*/)
		{
			m_fAverageRate = 0.0f;
			for (std::vector<float>::iterator iter=vecCurrent.begin();iter!=vecCurrent.end();iter++)
			{
				m_fAverageRate += *iter;
				ErrTrace("视频码流 iter=%f ***dwRateCountInter=%d****************\n",*iter,RATELIST[m_enUsedType].dwRateCountInter);
			}

			m_fAverageRate /= vecCurrent.size();

			ErrTrace("计算得到的平均码流*******************************************************************m_fAverageRate=%f GetTickCount=%ld\n",m_fAverageRate,GetTickCount());

			//重置统计数据
			if (dwFirt>RATELIST[m_enUsedType].dwRateCountInter/*VIDEO_RATE_COUNT_INTER*/ && dwSecond>RATELIST[m_enUsedType].dwRateCountInter/*VIDEO_RATE_COUNT_INTER*/)
			{
				if (dwFirt > dwSecond)
				{
					m_vecFirst.clear();
					m_dwFirstMapStartTime = GetTickCount();
				}
				else
				{	
					m_vecSecond.clear();
					m_dwSecondMapStartTime = GetTickCount();
				}
			}

			//if ((m_iframeEx/SCORE_CALC_LEN)%2 == 1)  //不限制
			{
				/////////////////////////////////////////////////瞬时平均码率 判断
				enLostType entype = enLostType::EN_LEVEL_3/*EN_LEVEL_1*//*EN_LEVEL_3*/;

				RelayManger* pRelayMgr = RelayManger::Instance();
				if (pRelayMgr)
				{
					float fLostRate = pRelayMgr->GetLostRate();
					if (fLostRate <= 0.05f) //丢包率 < 5%
					{
						entype = enLostType::EN_LEVEL_1;
					} 
					else if(fLostRate<=0.1f && fLostRate>0.05f) //丢包率 5%>  <10%
					{
						entype = enLostType::EN_LEVEL_2;
					}
				}

				g_entype = entype;

				//按照丢包率调整级别
				switch (entype)
				{
				case enLostType::EN_LEVEL_1: //网络状态很好
					{
						if (m_fAverageRate>RATELIST[m_enUsedType].fRateMaxLimit/*VIDEO_RATE_MAX_LIMIT*/) m_qp_index++;
						if (m_fAverageRate-RATELIST[m_enUsedType].fRateMaxLimit>7) m_qp_index++;
						if (m_fAverageRate<RATELIST[m_enUsedType].fRateMinLimit/*VIDEO_RATE_MIN_LIMIT*/) m_qp_index--;
						if (m_qp_index<0) m_qp_index = 0;
						if (m_qp_index>QUALITYSIZE-1) m_qp_index = QUALITYSIZE-1;
					}
					break;
				case enLostType::EN_LEVEL_2: //网咯状态良好
					{
						if (m_fAverageRate>RATELIST[m_enUsedType].fRateMaxLimit/*VIDEO_RATE_MAX_LIMIT*/) m_qp_index++;
						if (m_fAverageRate-RATELIST[m_enUsedType].fRateMaxLimit>7) m_qp_index++;
						if (m_fAverageRate<RATELIST[m_enUsedType].fRateMinLimit/*VIDEO_RATE_MIN_LIMIT*/) m_qp_index--;
						if (m_qp_index<1) m_qp_index = 1;
						if (m_qp_index>QUALITYSIZE-1) m_qp_index = QUALITYSIZE-1;
					}
					break;
				case enLostType::EN_LEVEL_3: //网络状态差  不用判断
					{
						m_qp_index = QUALITYSIZE-1;
					}
					break;
				default:
					m_qp_index = 0;
				}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//量化级别变化 动态调整
				if (m_qp_index_old!=m_qp_index)
				{
					//////////////////////////////////////////////
					//开始缓存7帧
					ErrTrace("缓存帧开始----m_fAverageRate=%f fRateMaxLimit=%f fRateMinLimit=%f----------------------------------------------------------------------\n",m_fAverageRate,RATELIST[m_enUsedType].fRateMaxLimit,RATELIST[m_enUsedType].fRateMinLimit);
					m_cache.ClearList();
					int iFrameCount = 0;
					while(iFrameCount++<7)
					{
						SetKeyFrame(&m_en_picture,48+iFrameCount);

						switch(m_en_picture.i_type)
						{
						case X264_TYPE_AUTO:
							ErrTrace("X264_TYPE_AUTO \n");
							break;
						case X264_TYPE_IDR:
							ErrTrace("X264_TYPE_IDR \n");
							break;
						case X264_TYPE_I:
							ErrTrace("X264_TYPE_I \n");
							break;
						case X264_TYPE_P:
							ErrTrace("X264_TYPE_P \n");
							break;
						case X264_TYPE_BREF:
							ErrTrace("X264_TYPE_BREF \n");
							break;
						case X264_TYPE_B:
							ErrTrace("X264_TYPE_B \n");
							break;
						case X264_TYPE_KEYFRAME:
							ErrTrace("X264_TYPE_KEYFRAME \n");
							break;
						default:
							ErrTrace("default \n");
						}

						static x264_picture_t pic_out;
						x264_nal_t *nal = NULL;
						int i_nal;

						int ret = x264_encoder_encode(m_en_h,&nal,&i_nal,&m_en_picture,&pic_out);
						if(ret <= 0) //补帧
						{
							OutputDebugStringA("补帧22222222222222222222222222\n");
							return false;
						}
						BAD_MEM_READ_RETURN(nal[0].p_payload,ret,"x264_encoder_encode 内存读错误",0)

							CVideoDataCache* p = new CVideoDataCache();
						p->SetData((char*)nal[0].p_payload, ret);
						p->SetType(m_en_picture.i_type);
						m_cache.SetListData(p);
						m_bCacheStart = true;
						SwitchToThread();
					}
					ErrTrace("缓存帧结束--------------------------------------------------------------------------\n");

					//重置编码器参数
					//////////////////////////////////////////////
					m_qp_index_old = m_qp_index;
					ResetQP(m_qp_index_old);

					//清理码率统计 重新计算
					m_fAverageRate = RATELIST[m_enUsedType].fRateAverage/*7.0f*/;
					m_vecFirst.clear();
					m_vecSecond.clear();
					m_dwFirstMapStartTime = 0;
					m_dwSecondMapStartTime = 0;

					///////////////////////////////////////////////
					char buf[512];
					sprintf(buf,"haosl total=%fk,enLostType=%s,m_qp_index_old=%d\n",total,entype==enLostType::EN_LEVEL_1?"EN_LEVEL_1":(entype==enLostType::EN_LEVEL_2?"EN_LEVEL_2":"EN_LEVEL_3"),m_qp_index_old);
					OutputDebugStringA(buf);
				}
			}
		}
	}

	if (pic_out.i_type==X264_TYPE_P && m_last_p)
	{
		if (!m_is_stop && ret>PER_PACKET_P_FRAME_LIMIT)
		{
			m_is_stop = true;
		}
	}

	if (pic_out.i_type==X264_TYPE_IDR)
	{
		m_is_stop = false;
	}

	m_last_p = (pic_out.i_type==X264_TYPE_P)?TRUE:FALSE;

	if (m_is_stop)
	{
		bStop = true;
	}

	//去掉丢B帧判断
	// 	if (pic_out.i_type==X264_TYPE_B && ret>PER_PACKET_B_FRAME_LIMIT)
	// 	{
	// 		bStop = true;
	// 	}

	return true;
}

void h264Codec::DeRelease()
{
	avcodec_close(m_de_context);
	av_free(m_de_context);
	av_free(m_de_frame);
	sws_freeContext(m_swsContext);
}

bool h264Codec::DeChangeInit(int iWidth, int iHeight)
{
	if (iWidth == m_nWidth && iHeight == m_nHeight)
	{
		return true;
	}

	m_bIsChange = true;
	try
	{
		Trace("h264Codec::DeChangeInit...1\n");
		if (m_swsContext )
			sws_freeContext(m_swsContext);
		m_swsContext = NULL;
		Trace("h264Codec::DeChangeInit...2\n");
		SAFE_DELETEA(m_pBuf)
			Trace("h264Codec::DeChangeInit...3\n");
		m_nWidth	= iWidth;//encode:输入视频分辨率,decode:输出视频分辨率
		m_nHeight	= iHeight;
		Trace("h264Codec::DeChangeInit...4\n");
		m_pBuf = new unsigned char[m_nWidth * m_nHeight * 3];
		m_swsContext = sws_getContext(m_h264_codec_width,m_h264_codec_height,
			PIX_FMT_YUV420P,
			m_nWidth, m_nHeight,										//修改 从208*156 变换到 m_nWidth*m_nHeight  大小
			PIX_FMT_RGB24, SWS_SINC, NULL, NULL, NULL);
		Trace("h264Codec::DeChangeInit...5\n");
	}
	catch (...)
	{
		Assert(0);
		Trace("h264Codec::DeChangeInit .....操作异常...\n");
	}
	m_bIsChange = false;
	return true;
}

bool h264Codec::DeConnect()
{
	m_de_codec = avcodec_find_decoder(CODEC_ID_H264);
	m_de_context = avcodec_alloc_context();
	m_de_context->error_concealment = 1;
	m_de_frame = avcodec_alloc_frame();

	m_swsContext = sws_getContext(m_h264_codec_width,m_h264_codec_height,
		PIX_FMT_YUV420P,
		m_nWidth, m_nHeight,										//修改 从208*156 变换到 m_nWidth*m_nHeight  大小
		PIX_FMT_RGB24, SWS_SINC, NULL, NULL, NULL);

	if(avcodec_open(m_de_context,m_de_codec) != 0)
	{
		return false;
	}

	/* plushu remove 
	m_de_context->width = m_nWidth;
	m_de_context->height = m_nHeight;
	H264Context *h = (H264Context*)m_de_context->priv_data;
	MpegEncContext *s = &h->s;
	s->dsp.idct_permutation_type = 1;
	dsputil_init(&s->dsp,m_de_context);*/

	return true;
}

bool h264Codec::DecodeVideoData(unsigned char *pInData, int iLen, unsigned char *pOutBuf, int &iOutLen,int& err,bool bForceKey)
{	
	static Mutex s_local_mutex;
	MutexLocker locker(&s_local_mutex); //

	BAD_MEM_READ_RETURN(pInData,iLen,"h264Codec::DecodeVideoData in error",0)
		BAD_MEM_WRITE_RETURN(pOutBuf,100,"h264Codec::DecodeVideoData out error",0)

	BAD_MEM_WRITE_RETURN(m_de_frame,sizeof(AVFrame),"h264Codec::DecodeVideoData ...m_de_frame",0)
		memset(m_de_frame, 0, sizeof(AVFrame));

	av_init_packet(&m_avpkt);
	m_avpkt.data = pInData;
	m_avpkt.size = iLen;

	if(bForceKey)
	{
		//avpkt.flags |= AV_PKT_FLAG_CORRUPT;
		//avpkt.flags |= AV_PKT_FLAG_KEY;
	}


	try
	{
		int got_picture = 0;
		iOutLen = avcodec_decode_video2(m_de_context,m_de_frame,&got_picture,&m_avpkt);
		if(iOutLen < 0)
		{
			return false;
		}
	}
	catch (...)
	{
		LostTrace("m_avpkt.convergence_duration=%ld,m_avpkt.dts=%ld,m_avpkt.duration=%d,m_avpkt.flags=%d,m_avpkt.pos=%d,m_avpkt.pts=%ld,m_avpkt.stream_index=%d\n",
			m_avpkt.convergence_duration,m_avpkt.dts,m_avpkt.duration,m_avpkt.flags,m_avpkt.pos,m_avpkt.pts,m_avpkt.stream_index);
		LostTrace("视频解码失败 ....11111.\n");
		Assert(0);
#ifndef IGNOR_INT_3
		_asm int 3;
#endif
		err = 1;
		return false;
	}


	avpicture_fill(&m_outpic, pOutBuf, PIX_FMT_RGB24, m_nWidth, m_nHeight);

	/*图像倒立
	m_de_frame->data[0] = m_de_frame->data[0]+m_de_frame->linesize[0]*(m_de_context->height-1);
	m_de_frame->data[1] = m_de_frame->data[1]+m_de_frame->linesize[0]*m_de_context->height/4-1;
	m_de_frame->data[2] = m_de_frame->data[2]+m_de_frame->linesize[0]*m_de_context->height/4-1;
	m_de_frame->linesize[0] *= -1;
	m_de_frame->linesize[1] *= -1;
	m_de_frame->linesize[2] *= -1;*/
	int rets = 0;
	if (!m_bIsChange && m_swsContext)
	{
		try
		{
			for (int i=0; i<4;i++)
			{
				BAD_MEM_READ_RETURN((m_de_frame->data[i]),m_de_frame->linesize[i],"h264Codec::DecodeVideoData sws_scale 0",0)
					BAD_MEM_READ_RETURN((m_outpic.data[i]),m_outpic.linesize[i],"h264Codec::DecodeVideoData sws_scale 1",0)
			}


			rets= sws_scale(m_swsContext, m_de_frame->data, m_de_frame->linesize, 0, m_de_context->height,m_outpic.data, m_outpic.linesize);

		}
		catch (...)
		{
			LostTrace("视频解码失败 .....22222\n");
			Assert(0);
#ifndef IGNOR_INT_3
			_asm int 3;
#endif
			err = 1;
			return false;
		}
	}
	else
	{
		Sleep(10);
	}

	return rets > 0;
}
