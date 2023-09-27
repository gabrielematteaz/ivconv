#include "mtt\cmd_line.h"
#include "mtt\fmt.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct mtt_opt_t optv[] = {
		{ 'f', OPT_ARG_TYPE_REQUIRED, NULL },
		{ 's', OPT_ARG_TYPE_NONE, NULL },
		{ 't', OPT_ARG_TYPE_REQUIRED, NULL },
		{ 'l', OPT_ARG_TYPE_NONE, NULL }
	};

	char **av = argv + mtt_extr_optv(argc, argv, sizeof(optv) / sizeof(*optv), optv), **argvc = argv + argc, fstr[128];
	struct mtt_ivalfmt_t optfmt = { '+', '-', ' ', 10, FMT_FILLING_LEFT, 0 }, fromfmt = { '+', '-', ' ', 10, FMT_FILLING_LEFT | IVALFMT_LTR_CASE_UNK, 0 }, tofmt = { 0, 0, 0, 16, FMT_FILLING_LEFT | IVALFMT_LTR_CASE_UPPER, 0 };

	if (optv[0].arg)
	{
		fromfmt.base = mtt_fstr_to_ival(optv[0].arg, NULL, optfmt);

		if (fromfmt.base < 2 || fromfmt.base > 36) fromfmt.base = 10;
	}

	if (optv[1].arg) tofmt.minus = '-';

	if (optv[2].arg)
	{
		tofmt.base = mtt_fstr_to_ival(optv[2].arg, NULL, optfmt);

		if (tofmt.base < 2 || tofmt.base > 36) tofmt.base = 16;
	}

	if (optv[3].arg) tofmt.fs |= IVALFMT_LTR_CASE_LOWER;

	while (av < argvc)
	{
		mtt_ival_to_fstr(fstr, mtt_fstr_to_ival(*av, NULL, fromfmt), tofmt);
		av++;
		puts(fstr);
	}

	return 0;
}