/*
 * Status.h
 *
 *  Created on: Jul 12, 2013
 *      Author: dvc
 */

#ifndef STATUS_H_
#define STATUS_H_

#include <tinyxml.h>


typedef struct {
	char PeakdB[64];			// "Video:714 mV 100 IRE - Audio:L-12.38 dB R -14.45 dB"
	char Stats[64];				// "MPEG-2 pid=-0x01E0 [720x480] pid=0x01E2 [AC3 48000]"
	char Status[64];			// "Played - Matched Audio RC[0x00000000]"
}SpotXMLT;

typedef struct {
	char PeakdB[64];			// "DEC Peak Video:714 mV 100 IRE - Audio:L-12.38 dB R -14.45 dB"
	char ALGaindB[10];			// "-3.00 dB"
	char ARGaindB[10];			// "-3.00 dB"
	int  SpotCount;
	SpotXMLT Spot[8];
}DecoderXMLT;

typedef struct {
	char PeakdB[64];			// "NET Peak Video:714 mV 100 IRE - Audio:L-12.38 dB R -14.45 dB"
	char MatchdB[64];			// "NET Match Audio:L-12.38 dB R -14.45 dB"
	char ALGaindB[10];			// "+3.00 dB"
	char ARGaindB[10];			// "+3.00 dB"
}NetworkXMLT;

typedef struct {
	char SwitchVersion[64];		// "D21-6202-01A0-SW_MCU"
	char GenlockStatus[64];     //Locked, freerun, unlocked, disabled
	NetworkXMLT Network;
	DecoderXMLT Decoder;
}ChannelStatusXMLT;

typedef struct {
	char p12V[10];				// {+12.000 V}
	char n12V[10];				// {-12.000 V}
	char p5V[10];				// {+5.000 V}
	char p3p3V[10];				// {+3.300 V}
	char p1p8V[10];				// {+1.800 V}
	char p1p5V[10];				// {+1.500 V}
	char p1p3V[10];				// {+1.300 V}
	char p0p7V[10];				// {+0.700 V}
}PowerXMLT;

typedef struct {
	char SOCA[10];				// {+47.0 C}
	char SOCB[10];				// {+46.0 C}
	char Ambient[10];			// {+33.0 C}
}TempXMLT;

typedef struct {
	char Speed[64];				// {0:SLOW/1:FAST}
	char Mode[64];				// {0:OFF/1:ON/2:AUTO}
}FanXMLT;

typedef struct {
	int Hours;					// {00000}
	int SpotCnt;				// {00000}
	char BootTime[64];  		// "12:05:02 09/10/2013 EST"
	int ErrorCnt;				// {00000}
	int AlarmCnt;				// {00000}
}CountsXMLT;

typedef struct {
	char SystemVersion[64];		// "D80-6200-01A0-MDS1440"
	char BoardVersion[64];		// "D40-6200-01A0-Lancaster"
	char SYSVersion[64];		// "D21-6201-01A0-SYS_MCU"
	char TBCVersion[64];		// "D21-6202-01A0-FPGA"
	char FPVersion[64];			// "D40-6240-01A0-FrontPanel"
	char FPCVersion[64];		// "D21-6241-01A0-FP_MCU"
}HWVersionXMLT;
typedef struct {
	char AppVersion[64];		// "V 0.080-091313-LanSys4"
	char RFSVersion[64];		// "V 0.080-091313-RFS"
	char KernelVersion[64];		// "V 0.080-091313-uImage"
	char BootVersion[64];		// "V 0.080-091313-uBoot"
}SWVersionXMLT;

typedef struct {
	char SplicerName[64];		// "Lancaster4"
	char ControlIPAddr[64];		// "192.168.2.90:5168"
	char VideoIPAddr[64];		// "192.168.3.90
	int PortBase;				// {0000}
	int NumberPorts;			// {0-8}
	int ChannelCnt;				// {2-4}
}SplicerStatusXMLT;

typedef struct {
	char SystemName[64];		// "Lancaster"
	char Model[64];				// "MDS1440"
	char SerialNumber[64];		// "3S4413G00000"
	char LiveStatus[64];		// "ONLINE"
	char CurrentTime[64];		// "12:05:02 09/10/2013 EST"
	char SplicerCnt[64];		// {2-4}
	PowerXMLT Power;
	TempXMLT Temp;
	FanXMLT Fan;
	CountsXMLT Counts;
	HWVersionXMLT HW;
	SWVersionXMLT SW;
}SystemStatusXMLT;

typedef struct {
	SystemStatusXMLT System;
	SplicerStatusXMLT Splicer;
	ChannelStatusXMLT Channel[4];
}StatusXMLT;



class Status {
public:
	Status();
	virtual ~Status();
	int GenerateXMLDoc();
	void XMLStream(char* XMLStream);
private:
	TiXmlDocument* doc;
	StatusXMLT mystatus;
};

#endif /* STATUS_H_ */
