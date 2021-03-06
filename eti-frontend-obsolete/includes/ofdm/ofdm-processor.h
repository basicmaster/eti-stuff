#
/*
 *    Copyright (C) 2016 .. 2017
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Programming
 *
 *    This file is part of the eti-frontend 
 *    eti-frontend is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    eti-frontend is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with eti-frontend; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#
#ifndef	__OFDM_PROCESSOR__
#define	__OFDM_PROCESSOR__
/*
 *
 */
#include	"dab-constants.h"
#include	<QThread>
#include	<QObject>
#include	"stdint.h"
#include	<sndfile.h>
#include	"freq-interleaver.h"
#include        "phasetable.h"
#include	"phasereference.h"
#include	"virtual-input.h"
#include	"ringbuffer.h"
#include	"dab-params.h"
#include	"freq-interleaver.h"

//	Note:
//	It was found that enlarging the buffersize to e.g. 8192
//	cannot be handled properly by the underlying system.
#define	DUMPSIZE		4096
class	RadioInterface;
class	common_fft;
class	etiGenerator;
class	dabParams;

class ofdmProcessor: public QThread {
Q_OBJECT
public:
		ofdmProcessor  	(virtualInput *,
	                         uint8_t,
	                         RadioInterface *,
	                         etiGenerator *,
	                         int16_t,
	                         uint8_t);
		~ofdmProcessor	(void);
	void	reset			(void);
	void	stop		(void);
	void	setOffset	(int32_t);
	void	coarseCorrectorOn	(void);
	void	coarseCorrectorOff	(void);
	void	set_scanMode		(bool, QString);
	void	startDumping	(SNDFILE *);
	void	stopDumping	(void);
private:
	bool		running;
	int16_t		gain;
	bool		dumping;
	int16_t		dumpIndex;
	int16_t		dumpScale;
	int16_t		dumpBuffer [DUMPSIZE];
	SNDFILE		*dumpFile;
	virtualInput	*theRig;
	dabParams	params;
	int32_t		T_null;
	int32_t		T_u;
	int32_t		T_s;
	int32_t		T_g;
	int32_t		T_F;
	int32_t		nrBlocks;
	int32_t		carriers;
	int32_t		carrierDiff;
	float		sLevel;
	RadioInterface	*myRadioInterface;
	DSPCOMPLEX	*dataBuffer;
	int32_t		FreqOffset;
	DSPCOMPLEX	*oscillatorTable;
	int32_t		localPhase;
	int16_t		fineCorrector;
	int32_t		coarseCorrector;

	uint8_t		freqSyncMethod;
	bool		f2Correction;
	int32_t		tokenCount;
	DSPCOMPLEX	*ofdmBuffer;
	uint32_t	ofdmBufferIndex;
	uint32_t	ofdmSymbolCount;
	int16_t		*dabFrame;
	DSPCOMPLEX	*referenceFase;
	phaseReference	phaseSynchronizer;
	interLeaver	myMapper;
	DSPFLOAT	avgCorr;
	etiGenerator	*my_etiGenerator;
private:
	float		*correlationVector;
	float		*refArg;
	int32_t		sampleCnt;
	int32_t		inputSize;
	int32_t		inputPointer;
	DSPCOMPLEX	getSample	(int32_t);
	void		getSamples	(DSPCOMPLEX *, int16_t, int32_t);
virtual	void		run		(void);
	int32_t		bufferContent;
	bool		isReset;
	void    	processBlock	(DSPCOMPLEX *inv, int16_t *ibits);
	int16_t		processBlock_0	(DSPCOMPLEX *, bool);
	int16_t		get_snr		(DSPCOMPLEX *v);

	int16_t		getMiddle	(DSPCOMPLEX *);
	common_fft	*fft_handler;
	DSPCOMPLEX	*fft_buffer;
	int16_t		snrCount;
	int16_t		snr;
signals:
	void		show_fineCorrector	(int);
	void		show_coarseCorrector	(int);
	void		setSynced		(char);
	void		show_snr		(int);
};
#endif

