#ifndef _AUDIO_H
#define _AUDIO_H
#include "stdafx.h"
#include "Mutex.h"
#include "ClientUser.h"
#include "boost/timer.hpp"
#include "packetdatastream.h"
#include "RC.h" 

#define SAMPLE_RATE 48000//44100				//采样率
#define SAMPLE_DIV  50
#define BIT_RATE 40960  //5K
#define AUDIO_CHANNEL 2

typedef std::pair<wstring,QByteArray> audioDevice;

//celt编解码库
class CELTCodec:public RCObject {

protected:

	CELTCodec();

	static CELTCodec* m_static_celtCodec;
	static RCPtr<CELTCodec> m_static_celtptr;

	const CELTMode *cmMode;

	CELTMode *(*mode_create)(celt_int32 Fs, int frame_size, int *error);
	void (*mode_destroy)(CELTMode *mode);
	int (__cdecl *mode_info)(const CELTMode *mode, int request, celt_int32 *value);

public:

	static CELTCodec* instance();
	static void deleteInstance();

	void (__cdecl *encoder_destroy)(CELTEncoder *st);
	int (__cdecl *encode)(CELTEncoder *st, const celt_int16 *pcm, int frame_size, unsigned char *compressed, int maxCompressedBytes);
	int (__cdecl *encode_float)(CELTEncoder *st, const float *pcm, int frame_size, unsigned char *compressed, int maxCompressedBytes);
	int (__cdecl *encoder_ctl)(CELTEncoder * st, int request, ...);

	void (__cdecl *decoder_destroy)(CELTDecoder *st);
	int (__cdecl *decode)(CELTDecoder *st, const unsigned char *data, int len, celt_int16 *pcm, int frame_size);
	int (__cdecl *decode_float)(CELTDecoder *st, const unsigned char *data, int len, float *pcm, int frame_size);
	int (__cdecl *decoder_ctl)(CELTDecoder * st, int request, ...);

	const char *(__cdecl *strerror)(int error);

	virtual ~CELTCodec();
	int bitstreamVersion() const;

	virtual CELTEncoder *encoderCreate();
	virtual CELTDecoder *decoderCreate();
};

//回环测试
class LoopUser: public ClientUser {

protected:
	Mutex qmLock;
	boost::timer  qtTicker;
	boost::timer  qtLastFetch;
	std::multimap<float, QByteArray> qmPackets;
	LoopUser();
public:
	static LoopUser lpLoopy;
	void addFrame(const QByteArray &packet);
	void fetchFrames();
};
#endif
