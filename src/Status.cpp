/*
 * Status.cpp
 *
 *  Created on: Jul 12, 2013
 *      Author: dvc
 */


#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "Status.h"

Status::Status() {
	doc = new TiXmlDocument( );
	strcpy (mystatus.System.SystemName,"Lancaster");
	strcpy (mystatus.System.Model,"MDS1440");
	strcpy (mystatus.System.SerialNumber,"3S4413G00000");
	strcpy (mystatus.System.LiveStatus,"ONLINE");
	strcpy (mystatus.System.CurrentTime,"12:05:02 09/10/2013 EST");
	strcpy (mystatus.System.SplicerCnt, "{2-4}");
	strcpy (mystatus.System.Power.p12V,"+12.000 V");
	strcpy (mystatus.System.Power.n12V,"-12.000 V");
	strcpy (mystatus.System.Power.p5V,"+5.000 V");
	strcpy (mystatus.System.Power.p3p3V,"+3.300 V");
	strcpy (mystatus.System.Power.p1p8V,"+1.800 V");
	strcpy (mystatus.System.Power.p1p5V,"+1.500 V");
	strcpy (mystatus.System.Power.p1p3V,"+1.300 V");
	strcpy (mystatus.System.Power.p0p7V,"+0.700 V");
	strcpy (mystatus.System.Temp.SOCA, "+47.0 C");
	strcpy (mystatus.System.Temp.SOCB, "+46.0 C");
	strcpy (mystatus.System.Temp.Ambient, "+33.0 C");
	strcpy (mystatus.System.Fan.Speed, "{0:SLOW/1:FAST)");
	strcpy (mystatus.System.Fan.Mode, "{0:OFF/1:ON/2:AUTO)");
	mystatus.System.Counts.Hours = 1234;
	mystatus.System.Counts.SpotCnt = 1234;				// {00000}
	strcpy (mystatus.System.Counts.BootTime, "12:05:02 09/10/2013 EST");
	mystatus.System.Counts.ErrorCnt = 1234;				// {00000}
	mystatus.System.Counts.AlarmCnt = 1234;				// {00000}
	strcpy (mystatus.System.HW.SystemVersion, "D80-6200-01A0-MDS1440");
	strcpy (mystatus.System.HW.BoardVersion, "D40-6200-01A0-Lancaster");
	strcpy (mystatus.System.HW.SYSVersion, "D21-6201-01A0-SYS_MCU");
	strcpy (mystatus.System.HW.TBCVersion, "D21-6202-01A0-FPGA");
	strcpy (mystatus.System.HW.FPVersion, "D40-6240-01A0-FrontPanel");
	strcpy (mystatus.System.HW.FPCVersion, "D21-6241-01A0-FP_MCU");
	strcpy (mystatus.System.SW.AppVersion, "V 0.080-091313-LanSys4");
	strcpy (mystatus.System.SW.RFSVersion, "V 0.080-091313-RFS");
	strcpy (mystatus.System.SW.KernelVersion, "V 0.080-091313-uImage");
	strcpy (mystatus.System.SW.BootVersion, "V 0.080-091313-uBoot");
	strcpy (mystatus.Channel[0].SwitchVersion, "Switch Version");
	mystatus.Channel[0].Decoder.SpotCount = 3;
}

Status::~Status() {
	delete doc;
	// TODO Auto-generated destructor stub
}

int Status::GenerateXMLDoc()
{

	const char* StatusString =
			"<Status>\n"
			"</Status>";
	char Temp[64];
	TiXmlNode* pStatus = NULL;
	while (pStatus = doc->FirstChild())
		doc->Clear();
	doc->Parse(StatusString);
	TiXmlHandle TiXMLH = doc->FirstChild("Status");

	TiXmlElement* TiXMLE_Status = TiXMLH.ToElement();

	TiXmlElement TiXMLE_System("System");
	//char SystemName[64];		// "Lancaster"
	TiXMLE_System.SetAttribute("SystemName", mystatus.System.SystemName);
	//char Model[64];				// "MDS1440"
	TiXMLE_System.SetAttribute("Model", mystatus.System.Model);
	//char SerialNumber[64];		// "3S4413G00000"
	TiXMLE_System.SetAttribute("SerialNumber", mystatus.System.SerialNumber);
	//char LiveStatus[64];		// "ONLINE"
	TiXMLE_System.SetAttribute("LiveStatus", mystatus.System.LiveStatus);
	//char CurrentTime[64];		// "12:05:02 09/10/2013 EST"
	TiXMLE_System.SetAttribute("CurrentTime", mystatus.System.CurrentTime);
	//char SplicerCnt[64];		// {2-4}
	TiXMLE_System.SetAttribute("SplicerCnt", mystatus.System.SplicerCnt);

	TiXmlElement TiXMLE_Power("Power");
	//char p12V[10];				// {+12.000 V}
	TiXMLE_Power.SetAttribute("p12V", mystatus.System.Power.p12V);
	//char n12V[10];				// {-12.000 V}
	TiXMLE_Power.SetAttribute("n12V", mystatus.System.Power.n12V);
	//char p5V[10];					// {+5.000 V}
	TiXMLE_Power.SetAttribute("p5V", mystatus.System.Power.p5V);
	//char p3p3V[10];				// {+3.300 V}
	TiXMLE_Power.SetAttribute("p3p3V", mystatus.System.Power.p3p3V);
	//char p1p8V[10];				// {+1.800 V}
	TiXMLE_Power.SetAttribute("p1p8V", mystatus.System.Power.p1p8V);
	//char p1p5V[10];				// {+1.500 V}
	TiXMLE_Power.SetAttribute("p1p5V", mystatus.System.Power.p1p5V);
	//char p1p3V[10];				// {+1.300 V}
	TiXMLE_Power.SetAttribute("p1p3V", mystatus.System.Power.p1p3V);
	//char p0p7V[10];				// {+0.700 V}
	TiXMLE_Power.SetAttribute("p0p7V", mystatus.System.Power.p0p7V);
	TiXMLE_System.InsertEndChild(TiXMLE_Power);

	TiXmlElement TiXMLE_Temp("Temp");
	//char SOCA[10];				// {+47.0 C}
	TiXMLE_Temp.SetAttribute("SOCA", mystatus.System.Temp.SOCA);
	//char SOCB[10];				// {+46.0 C}
	TiXMLE_Temp.SetAttribute("SOCB", mystatus.System.Temp.SOCB);
	//char Ambient[10];			// {+33.0 C}
	TiXMLE_Temp.SetAttribute("Ambient", mystatus.System.Temp.Ambient);
	TiXMLE_System.InsertEndChild(TiXMLE_Temp);

	TiXmlElement TiXMLE_Fan("Fan");
	//char Speed[64];				// {0:SLOW/1:FAST}
	TiXMLE_Fan.SetAttribute("Speed", mystatus.System.Fan.Speed);
	//char Mode[64];				// {0:OFF/1:ON/2:AUTO}
	TiXMLE_Fan.SetAttribute("Mode", mystatus.System.Fan.Mode);
	TiXMLE_System.InsertEndChild(TiXMLE_Fan);

	TiXmlElement TiXMLE_Counts("Counts");
	//int Hours;					// {00000}
	TiXMLE_Counts.SetAttribute("Hours", mystatus.System.Counts.Hours);
	//int SpotCnt;				// {00000}
	TiXMLE_Counts.SetAttribute("SpotCnt", mystatus.System.Counts.SpotCnt);
	//char BootTime[64];  		// "12:05:02 09/10/2013 EST"
	TiXMLE_Counts.SetAttribute("BootTime", mystatus.System.Counts.BootTime);
	//int ErrorCnt;				// {00000}
	TiXMLE_Counts.SetAttribute("ErrorCnt", mystatus.System.Counts.ErrorCnt);
	//int AlarmCnt;				// {00000}
	TiXMLE_Counts.SetAttribute("AlarmCnt", mystatus.System.Counts.AlarmCnt);
	TiXMLE_System.InsertEndChild(TiXMLE_Counts);

	TiXmlElement TiXMLE_HWVersion("HWVersion");
	//char SystemVersion[64];		// "D80-6200-01A0-MDS1440"
	TiXMLE_HWVersion.SetAttribute("SystemVersion", mystatus.System.HW.SystemVersion);
	//char BoardVersion[64];		// "D40-6200-01A0-Lancaster"
	TiXMLE_HWVersion.SetAttribute("BoardVersion", mystatus.System.HW.BoardVersion);
	//char SYSVersion[64];		// "D21-6201-01A0-SYS_MCU"
	TiXMLE_HWVersion.SetAttribute("SYSVersion", mystatus.System.HW.SYSVersion);
	//char TBCVersion[64];		// "D21-6202-01A0-FPGA"
	TiXMLE_HWVersion.SetAttribute("TBCVersion", mystatus.System.HW.TBCVersion);
	//char FPVersion[64];			// "D40-6240-01A0-FrontPanel"
	TiXMLE_HWVersion.SetAttribute("FPVersion", mystatus.System.HW.FPVersion);
	//char FPCVersion[64];		// "D21-6241-01A0-FP_MCU"
	TiXMLE_HWVersion.SetAttribute("FPCVersion", mystatus.System.HW.FPCVersion);
	TiXMLE_System.InsertEndChild(TiXMLE_HWVersion);

	TiXmlElement TiXMLE_SWVersion("SWVersion");
	//char AppVersion[64];		// "V 0.080-091313-LanSys4"
	TiXMLE_SWVersion.SetAttribute("AppVersion", mystatus.System.SW.AppVersion);
	//char RFSVersion[64];		// "V 0.080-091313-RFS"
	TiXMLE_SWVersion.SetAttribute("RFSVersion", mystatus.System.SW.RFSVersion);
	//char KernelVersion[64];		// "V 0.080-091313-uImage"
	TiXMLE_SWVersion.SetAttribute("KernelVersion", mystatus.System.SW.KernelVersion);
	//char BootVersion[64];		// "V 0.080-091313-uBoot"
	TiXMLE_SWVersion.SetAttribute("BootVersion", mystatus.System.SW.BootVersion);
	TiXMLE_System.InsertEndChild(TiXMLE_SWVersion);

	TiXMLE_Status->InsertEndChild(TiXMLE_System);

	TiXmlElement TiXMLE_Splicer("Splicer");
	//char SplicerName[64];		// "Lancaster4"
	TiXMLE_Splicer.SetAttribute("SplicerName",mystatus.Splicer.SplicerName);
	//char ControlIPAddr[64];		// "192.168.2.90:5168"
	TiXMLE_Splicer.SetAttribute("ControlIPAddr",mystatus.Splicer.ControlIPAddr);
	//char VideoIPAddr[64];		// "192.168.3.90
	TiXMLE_Splicer.SetAttribute("VideoIPAddr",mystatus.Splicer.VideoIPAddr);
	//int PortBase;				// {0000}
	TiXMLE_Splicer.SetAttribute("PortBase",mystatus.Splicer.PortBase);
	//int NumberPorts;			// {0-8}
	TiXMLE_Splicer.SetAttribute("NumberPorts",mystatus.Splicer.NumberPorts);
	//int ChannelCnt;				// {2-4}
	TiXMLE_Splicer.SetAttribute("ChannelCnt",mystatus.Splicer.ChannelCnt);

	TiXMLE_Status->InsertEndChild(TiXMLE_Splicer);

	for(int iChannel=0;iChannel<4;iChannel++)
	{
		TiXmlElement TiXMLE_Channel("Channel");

		TiXMLE_Channel.SetAttribute("GenlockStatus", mystatus.Channel[iChannel].GenlockStatus);
		TiXMLE_Channel.SetAttribute("SwitchVersion", mystatus.Channel[iChannel].SwitchVersion);

		TiXmlElement TiXMLE_Network("Network");
		//char PeakdB[64];			// "NET Peak Video:714 mV 100 IRE - Audio:L-12.38 dB R -14.45 dB"
		TiXMLE_Network.SetAttribute("PeakdB",mystatus.Channel[iChannel].Network.PeakdB);
		//char MatchdB[64];			// "NET Match Audio:L-12.38 dB R -14.45 dB"
		TiXMLE_Network.SetAttribute("MatchdB",mystatus.Channel[iChannel].Network.MatchdB);
		//char ALGaindB[10];			// "+3.00 dB"
		TiXMLE_Network.SetAttribute("ALGaindB",mystatus.Channel[iChannel].Network.ALGaindB);
		//char ARGaindB[10];			// "+3.00 dB"
		TiXMLE_Network.SetAttribute("ARGaindB",mystatus.Channel[iChannel].Network.ARGaindB);
		TiXMLE_Channel.InsertEndChild(TiXMLE_Network);

		TiXmlElement TiXMLE_Decoder("Decoder");
		//char PeakdB[64];			// "DEC Peak Video:714 mV 100 IRE - Audio:L-12.38 dB R -14.45 dB"
		TiXMLE_Decoder.SetAttribute("PeakdB",mystatus.Channel[iChannel].Decoder.PeakdB);
		//char ARGaindB[10];			// "-3.00 dB"
		TiXMLE_Decoder.SetAttribute("ARGaindB",mystatus.Channel[iChannel].Decoder.ARGaindB);
		//char ARGaindB[10];			// "-3.00 dB"
		TiXMLE_Decoder.SetAttribute("ALGaindB",mystatus.Channel[iChannel].Decoder.ALGaindB);
		//int SpotCount;			//0-8
		TiXMLE_Decoder.SetAttribute("SpotCount",mystatus.Channel[iChannel].Decoder.SpotCount);
		int iSpotCount = mystatus.Channel[iChannel].Decoder.SpotCount;
		if (iSpotCount > 8) iSpotCount = 8;
		for(int iSpot=0;iSpot<iSpotCount;iSpot++)
		{
			TiXmlElement TiXMLE_Spot("Spot");
			//char PeakdB[64];			// "Video:714 mV 100 IRE - Audio:L-12.38 dB R -14.45 dB"
			TiXMLE_Spot.SetAttribute("PeakdB",mystatus.Channel[iChannel].Decoder.Spot[iSpot].PeakdB);
			//char Stats[64];				// "MPEG-2 pid=-0x01E0 [720x480] pid=0x01E2 [AC3 48000]"
			TiXMLE_Spot.SetAttribute("Stats",mystatus.Channel[iChannel].Decoder.Spot[iSpot].Stats);
			//char Status[64];			// "Played - Matched Audio RC[0x00000000]"
			TiXMLE_Spot.SetAttribute("Status",mystatus.Channel[iChannel].Decoder.Spot[iSpot].Status);

			TiXMLE_Decoder.InsertEndChild(TiXMLE_Spot);
		}
		for(int iSpot=iSpotCount;iSpot<8;iSpot++)
		{
			TiXmlElement TiXMLE_Spot("Spot");
			//char PeakdB[64];			// "Video:714 mV 100 IRE - Audio:L-12.38 dB R -14.45 dB"
			TiXMLE_Spot.SetAttribute("PeakdB","");
			//char Stats[64];				// "MPEG-2 pid=-0x01E0 [720x480] pid=0x01E2 [AC3 48000]"
			TiXMLE_Spot.SetAttribute("Stats","");
			//char Status[64];			// "Played - Matched Audio RC[0x00000000]"
			TiXMLE_Spot.SetAttribute("Status","");

			TiXMLE_Decoder.InsertEndChild(TiXMLE_Spot);
		}
		TiXMLE_Channel.InsertEndChild(TiXMLE_Decoder);

		TiXMLE_Status->InsertEndChild(TiXMLE_Channel);
	}
	doc->Print( );
	return true;
}
void Status::XMLStream(char* XMLStream)
{
	TiXmlPrinter printer;
	int Retval = 1;
	Retval = GenerateXMLDoc();
	if (Retval)
	{
		printer.SetIndent( "\t");
		doc->Accept(&printer);
	}
	strcpy(XMLStream, printer.CStr());
}
