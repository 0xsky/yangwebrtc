﻿/*
 * YangPlayFactory.h
 *
 *  Created on: 2020年9月4日
 *      Author: yang
 */

#ifndef YANGPLAYER_INCLUDE_YANGPLAYFACTORY_H_
#define YANGPLAYER_INCLUDE_YANGPLAYFACTORY_H_
#include <yangaudiodev/YangAudioPlay.h>
enum YangAudioPlayType{
	Yang_AP_SDL,
	Yang_AP_ALSA,
};

class YangPlayFactory {
public:
	YangPlayFactory();
	virtual ~YangPlayFactory();
	YangAudioPlay* createAudioPlay(YangAudioInfo *pcontext);
	YangAudioPlay *createAudioPlay(YangAudioPlayType paet,YangAudioInfo *pcontext);
};

#endif /* YANGPLAYER_INCLUDE_YANGPLAYFACTORY_H_ */
