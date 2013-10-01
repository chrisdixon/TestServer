
typedef struct {	char Systemname[64];	// "Lancaster"	char Logfile[64];		// "/home/root/logfile"	char Location[64];		// "DVC Woburn"	bool  InvalidTones;	// {0:OFF/1:ON}	bool  Attach; 		// {0:BYPASS/1:ATTACH}	bool  AlarmBuzzer;	// {0:OFF/1:ON}	bool  TrigBuzzer;	// {0:OFF/1:ON}	int  Fan;			// {0:OFF/1:ON/2:AUTO}	int  FanSpeed;		// {0:SLOW/1:FAST}	char   DebugLevel[64];		// {0x0000 - 0xFFFF}	int  Console;		// {0:SOCA/1:SOCB}}SystemXMLT;

typedef struct {	char SplicerName[64];	// "Lancaster4"	char ControlIPAddr[64];	// "192.168.2.90:5168"	char VideoIPAddr[64];	// "192.168.3.90"	int  PortBase;			// {5000}}SplicerXMLT;
typedef struct {	char channelname[64];	// "CNN"	char zonename[64];		// "LAN4"	char NameZone[64];		// "CNN_LAN4"	int  trigger;  		    // {0:OFF/1:DTMF/2:CC/3:BOTH}	int  cutoff;			// {0-240}	char entrydelim;		// "*"	char exitdelim;			// "#"	int  exitflag;     	    // {0:IGNORE/1:ON}	int  genlock;		    // {0:OFF/1:FAST/2:AUTO]	int  agcdec;            // {0:OFF/1:FIXED/2:MATCH]	int  preroll; 			// {0-900}	int  postblack;			// {0-900}	char toneone[4];		// "000"	char tonetwo[4];		// "000"	char tonethree[4];		// "000"	char tonefour[4];		// "000"	int  swbacktime;		// {0}	int  pal;    			// {0:NTSC/1:PAL}	int  frm_sec;			// {30}	int  bypass;		    // {0:OFF/1:ON}	int  latestart;			// {0}	int  earlystop;			// {0}	int  vnet_agc;		    // {0:OFF/1:ON}	int  vdec_agc;		    // {0:OFF/1:ON}	int  adecl_gain;		// {0-255}	int  adecr_gain;    	// {0-255}	int  anetl_gain;		// {0-255}	int  anetr_gain;		// {0-255}	bool AudioMute;	bool LevelMatchingEnable;	bool NetworkGainEnable;
}ChannelXMLT;

typedef struct {	SystemXMLT System;	SplicerXMLT Splicer;	ChannelXMLT Channel[4];}ConfigXMLT;

