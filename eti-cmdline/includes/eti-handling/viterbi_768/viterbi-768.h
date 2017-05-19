#
#ifndef	__VITERBI_768__
#define	__VITERBI_768__
/*
 * 	Viterbi.h according to the SPIRAL project
 */
#include	"dab-constants.h"

//	For our particular viterbi decoder, we have
#define	RATE	4
#define NUMSTATES 64
#define DECISIONTYPE uint8_t
#define DECISIONTYPE_BITSIZE 8
#define COMPUTETYPE uint32_t

//decision_t is a BIT vector
typedef union {
	DECISIONTYPE t[NUMSTATES/DECISIONTYPE_BITSIZE];
	uint32_t w[NUMSTATES/32];
	uint16_t s[NUMSTATES/16];
	uint8_t c[NUMSTATES/8];
} decision_t __attribute__ ((aligned (16)));

typedef union {
	COMPUTETYPE t[NUMSTATES];
} metric_t __attribute__ ((aligned (16)));

/* State info for instance of Viterbi decoder
 */

struct v {
/* path metric buffer 1 */
	__attribute__ ((aligned (16))) metric_t metrics1;
/* path metric buffer 2 */
	__attribute__ ((aligned (16))) metric_t metrics2;
/* Pointers to path metrics, swapped on every bit */
	metric_t *old_metrics,*new_metrics;
	decision_t *decisions;   /* decisions */
};

class	viterbi_768 {
public:
		viterbi_768	(int16_t, bool spiral = false);
		~viterbi_768	(void);
	void	deconvolve	(int16_t *, uint8_t *);
private:

	bool		spiral;
	struct v	vp;
	COMPUTETYPE Branchtab	[NUMSTATES / 2 * RATE] __attribute__ ((aligned (16)));
	int	parity		(int);
	void	partab_init	(void);
	void	init_viterbi	(struct v *, int16_t);
	void	update_viterbi_blk_GENERIC	(struct v *, COMPUTETYPE *,
	                                         int16_t);
	void	update_viterbi_blk_SPIRAL	(struct v *, COMPUTETYPE *,
	                                         int16_t);
	void	chainback_viterbi (struct v *, uint8_t *, int16_t, uint16_t);
	struct v *viterbi_alloc (int32_t);
	void	BFLY		(int32_t, int, COMPUTETYPE *,
	                         struct v *, decision_t *);
//	uint8_t *bits;
	uint8_t *data;
	COMPUTETYPE *symbols;
	int16_t	frameBits;
};

#endif
