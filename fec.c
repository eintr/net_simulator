#include <stdio.h>
#include <stdlib.h>

#include "fec.h"

extern void global_init(void);
extern void global_destroy(void);

static struct fec_processor_stat_st statics;

struct fec_group_st {
	uint32_t fecg_id;
	int grade;
	int red_level;
	struct internal_fec_frame_st frame[];
};

void global_init(void)
{
}

void global_destroy(void)
{
}

int fec_processor_settimeout(time_t to)
{
	if (to<=0 || to>10000) {
		return -EINVAL;
	}
	statics.timeout = to;
	return 0;
}

int fec_processor_setfalgs(int)
{
}

int fec_frame_decode(struct fec_frame_st*, int size, )
{
}

