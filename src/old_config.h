typedef struct
{
	double GainNetworkLeft;
	double GainNetworkRight;
	double GainDecoderLeft;
	double GainDecoderRight;
	bool AudioMute;
	bool LevelMatchingEnable;
	bool NetworkGainEnable;
}GainT;
typedef struct
{
	char channelname[64];
	char zonename[64];
	char trigger[64];
	int cutoff;
	char entrydelim[64];
	char exitdelim[64];
	char exitflag[64];
	char genlock[64];
	char agcdec[64];
	int preroll;
	int postblack;
	char toneone[64];
	char tonetwo[64];
	char tonethree[64];
	char tonefour[64];
	int ccabort;
	int swbacktime;
	int pal;
	int frm_sec;
	char bypass[64];
	GainT gains;
}channelconfigT;
typedef struct
{
	char systemname[64];
	char ControlIPAddr[64];
	bool InvalidTones;
	bool Attach;
	bool Buzzer;
	bool ToneBuzzer;
}SystemConfigT;
typedef struct
{
	char splicername[64];
	char StreamingIPAddr[64];
	channelconfigT channel[2];
}SplicerConfigT;
typedef struct
{
	SystemConfigT system;
	SplicerConfigT splicer[2];
	bool updated;
}configT;

