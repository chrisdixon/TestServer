/*
 * Configuration.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: dvc
 */

#include "Configuration.h"

const char* OnOffString []
{
	   "Off",
	   "On"
};
const char* FanString []
{
   "Off",
   "On",
   "Auto"
};
const char* FanSpeedString []
{
   "Slow",
   "Fast"
};
const char* ConsoleString []
{
   "SOCA",
   "SOCB"
};
const char* triggerstring [] //pointer to one of these literals, which must match the webpage
{
	"off",
	"dtmf",
	"contact",
	"both"
};
const char* exitflagstring[] //pointer to one of these literals, which must match the webpage
{
	"ignore",
	"enable"
};
const char* genlockstring[] //pointer to one of these literals, which must match the webpage
{
	"genlock_off",
	"genlock_fast",
	"genlock_auto"
};
const char* agcstring[] //pointer to one of these literals, which must match the webpage
{
	"agc_dec_on",
	"agc_dec_off",
	"agc_dec_match"

};
const char* palstring[] //pointer to one of these literals, which must match the webpage
{
	"ntsc",
	"pal"
};
const char* bypassstring[] //pointer to one of these literals, which must match the webpage
{
   "channel_enable",
   "channel_bypass"
};

Configuration::Configuration() {
	doc = new TiXmlDocument( "configuration.xml" );
}

Configuration::~Configuration() {
	delete doc;
}
int Configuration::ReadFile()
{
	TiXmlNode* pConfig = NULL;
	while (pConfig = doc->FirstChild())
		doc->Clear();
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load configuration file. Error='%s'. Exiting.\n", doc->ErrorDesc() );
		return false;
	}
	return ProcessXMLDoc();
}
int Configuration::SaveFile()
{
	int Retval = 0;
	Retval = GenerateXMLDoc();
	if (Retval)
		Retval = doc->SaveFile();
	return Retval;
}
int Configuration::ProcessXMLStream(const char* XMLStream)
{
	TiXmlNode* pConfig = NULL;
	while (pConfig = doc->FirstChild())
		doc->Clear();
	doc->Parse(XMLStream);
	return ProcessXMLDoc();
}
void Configuration::XMLStream(char* XMLStream)
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
int Configuration::ProcessXMLDoc()
{

	int iValue = 0;
	int iChannel = 0;
	const char * psz = NULL;
	TiXmlHandle TiXMLH = doc->FirstChild("Configuration");
	TiXmlElement* TiXMLE_System = TiXMLH.FirstChild("System").ToElement();
	if (TiXMLE_System)
	{
		if (psz = TiXMLE_System->Attribute("systemname"))
			strcpy(myconfig.System.Systemname, psz);
		// char Logfile[64];		// "/home/root/logfile"
		if (psz = TiXMLE_System->Attribute("Logfile"))
					strcpy(myconfig.System.Logfile, psz);
		//	char Location[64];		// "DVC Woburn"
		if (psz = TiXMLE_System->Attribute("Location"))
					strcpy(myconfig.System.Location, psz);
		if (psz = TiXMLE_System->Attribute("InvalidTones"))
			if(0 == strcmp(psz,"On"))
				myconfig.System.InvalidTones = true;
			else
				myconfig.System.InvalidTones = false;
		if (psz = TiXMLE_System->Attribute("Attach"))
			if(0 == strcmp(psz,"On"))
				myconfig.System.Attach = true;
			else
				myconfig.System.Attach = false;
		if (psz = TiXMLE_System->Attribute("Buzzer"))
			if(0 == strcmp(psz,"On"))
				myconfig.System.AlarmBuzzer = true;
			else
				myconfig.System.AlarmBuzzer = false;
		if (psz = TiXMLE_System->Attribute("ToneBuzzer"))
			if(0 == strcmp(psz,"On"))
				myconfig.System.TrigBuzzer = true;
			else
				myconfig.System.TrigBuzzer = false;
		//char  Fan[64];			// {0:OFF/1:ON/2:AUTO}
		if(psz = TiXMLE_System->Attribute("Fan"))
		{
			int i = 0;
			while ((i<3) && strcmp(psz,FanString[i]))i++;
			myconfig.System.Fan = i;
		}
		//char  FanSpeed[64];		// {0:SLOW/1:FAST}
		if(psz = TiXMLE_System->Attribute("FanSpeed"))
		{
			int i = 0;
			while ((i<2) && strcmp(psz,FanSpeedString[i]))i++;
			myconfig.System.FanSpeed = i;
		}
		//int   DebugLevel;		// {0x0000 - 0xFFFF}
		if (psz = TiXMLE_System->Attribute("DebugLevel"))
			strcpy(myconfig.System.DebugLevel, psz);
		//char  Console[64];		// {0:SOCA/1:SOCB}
		if(psz = TiXMLE_System->Attribute("Console"))
		{
			int i = 0;
			while ((i<2) && strcmp(psz,ConsoleString[i]))i++;
			myconfig.System.Console = i;
		}
	}
	TiXmlElement* TiXMLE_Splicer = TiXMLH.FirstChild("Splicer").ToElement();
	if(TiXMLE_Splicer)
	{
		if (psz = TiXMLE_Splicer->Attribute("splicername"))
			strcpy(myconfig.Splicer.SplicerName, psz);
		if (psz = TiXMLE_Splicer->Attribute("StreamingIPAddr"))
			strcpy(myconfig.Splicer.VideoIPAddr, psz);
		if (psz = TiXMLE_Splicer->Attribute("ControlIPAddr"))
			strcpy(myconfig.Splicer.ControlIPAddr, psz);
		if (TIXML_SUCCESS == TiXMLE_Splicer->QueryIntAttribute("PortBase",&iValue))
			myconfig.Splicer.PortBase = iValue;
	}
	iChannel = 0;
	while (iChannel < 4)
	{
		TiXmlElement* TiXMLE_Channel = TiXMLH.Child("Channel", iChannel).ToElement();
		if(TiXMLE_Channel)
		{
			//These two lines allow us to parse a single channel's worth of data from the web page
			if (TIXML_SUCCESS == TiXMLE_Channel->QueryIntAttribute("channel",&iValue))
				iChannel = iValue;
			if(psz = TiXMLE_Channel->Attribute("channelname"))
				strcpy(myconfig.Channel[iChannel].channelname, psz);
			if(psz = TiXMLE_Channel->Attribute("zonename"))
				strcpy(myconfig.Channel[iChannel].zonename, psz);
			if(psz = TiXMLE_Channel->Attribute("trigger"))
			{
				int i = 0;
				while (strcmp(psz,triggerstring[i]) && (i<4))i++;
				myconfig.Channel[iChannel].trigger = i;
			}
			if (TIXML_SUCCESS == TiXMLE_Channel->QueryIntAttribute("cutoff",&iValue))
				myconfig.Channel[iChannel].cutoff = iValue;
			if(psz = TiXMLE_Channel->Attribute("entrydelim"))
				myconfig.Channel[iChannel].entrydelim = psz[0];
			if(psz = TiXMLE_Channel->Attribute("exitdelim"))
				myconfig.Channel[iChannel].exitdelim = psz[0];
			if(psz = TiXMLE_Channel->Attribute("exitflag"))
			{
				int i = 0;
				while (strcmp(psz,exitflagstring[i]) && (i<2))i++;
				myconfig.Channel[iChannel].exitflag = i;
			}
			if(psz = TiXMLE_Channel->Attribute("genlock"))
			{
				int i = 0;
				while (strcmp(psz,genlockstring[i]) && (i<3))i++;
				myconfig.Channel[iChannel].genlock = i;
			}
			if(psz = TiXMLE_Channel->Attribute("agcdec"))
			{
				int i = 0;
				while (strcmp(psz,agcstring[i]) && (i<3))i++;
				myconfig.Channel[iChannel].agcdec = i;
			}
			if (TIXML_SUCCESS == TiXMLE_Channel->QueryIntAttribute("preroll",&iValue))
				myconfig.Channel[iChannel].preroll = iValue;
			if (TIXML_SUCCESS == TiXMLE_Channel->QueryIntAttribute("postblack",&iValue))
				myconfig.Channel[iChannel].postblack = iValue;
			if(psz = TiXMLE_Channel->Attribute("toneone"))
				strncpy(myconfig.Channel[iChannel].toneone, psz, 4);
			if(psz = TiXMLE_Channel->Attribute("tonetwo"))
				strncpy(myconfig.Channel[iChannel].tonetwo, psz, 4);
			if(psz = TiXMLE_Channel->Attribute("tonethree"))
				strncpy(myconfig.Channel[iChannel].tonethree, psz, 4);
			if(psz = TiXMLE_Channel->Attribute("tonefour"))
				strncpy(myconfig.Channel[iChannel].tonefour, psz, 4);
			if (TIXML_SUCCESS == TiXMLE_Channel->QueryIntAttribute("pal",&iValue))
				myconfig.Channel[iChannel].pal = iValue;
			if (TIXML_SUCCESS == TiXMLE_Channel->QueryIntAttribute("frm_sec",&iValue))
				myconfig.Channel[iChannel].frm_sec = iValue;
			if(psz = TiXMLE_Channel->Attribute("bypass"))
			{
				int i = 0;
				while (strcmp(psz,bypassstring[i]) && (i<2))i++;
				myconfig.Channel[iChannel].bypass = i;
			}
			if(psz = TiXMLE_Channel->Attribute("GainNetworkLeft"))
				myconfig.Channel[iChannel].anetl_gain = MakeGainByte(strtod(psz,NULL));
			if(psz = TiXMLE_Channel->Attribute("GainNetworkRight"))
				myconfig.Channel[iChannel].anetr_gain = MakeGainByte(strtod(psz,NULL));
			if(psz = TiXMLE_Channel->Attribute("GainDecoderLeft"))
				myconfig.Channel[iChannel].adecl_gain = MakeGainByte(strtod(psz,NULL));
			if(psz = TiXMLE_Channel->Attribute("GainDecoderRight"))
				myconfig.Channel[iChannel].adecr_gain = MakeGainByte(strtod(psz,NULL));

			if (psz = TiXMLE_Channel->Attribute("AudioMute"))
				if(0 == strcmp(psz,"On"))
					myconfig.Channel[iChannel].AudioMute = true;
				else
					myconfig.Channel[iChannel].AudioMute = false;
			if (psz = TiXMLE_Channel->Attribute("LevelMatchingEnable"))
				if(0 == strcmp(psz,"On"))
					myconfig.Channel[iChannel].LevelMatchingEnable = true;
				else
					myconfig.Channel[iChannel].LevelMatchingEnable = false;
			if (psz = TiXMLE_Channel->Attribute("NetworkGainEnable"))
				if(0 == strcmp(psz,"On"))
					myconfig.Channel[iChannel].NetworkGainEnable = true;
				else
					myconfig.Channel[iChannel].NetworkGainEnable = false;
		}
		iChannel++;
	}
	return true;
}
int Configuration::GenerateXMLDoc()
{
	const char* ConfigString =
			"<Configuration>\n"
			"</Configuration>";
	int iChannel;
	TiXmlNode* pConfig = NULL;
	char Temp[64];
	while (pConfig = doc->FirstChild())
		doc->Clear();
	doc->Parse(ConfigString);
	TiXmlHandle TiXMLH = doc->FirstChild("Configuration");

	TiXmlElement* TiXMLE_Configuration = TiXMLH.ToElement();

	TiXmlElement TiXMLE_System("System");
	TiXMLE_System.SetAttribute("systemname", myconfig.System.Systemname);
	TiXMLE_System.SetAttribute("Logfile", myconfig.System.Logfile);
	TiXMLE_System.SetAttribute("Location", myconfig.System.Location);
	if(myconfig.System.InvalidTones)
		TiXMLE_System.SetAttribute("InvalidTones", "On");
	else
		TiXMLE_System.SetAttribute("InvalidTones", "Off");
	if(myconfig.System.Attach)
			TiXMLE_System.SetAttribute("Attach", "On");
		else
			TiXMLE_System.SetAttribute("Attach", "Off");
	if(myconfig.System.AlarmBuzzer)
		TiXMLE_System.SetAttribute("Buzzer", "On");
	else
		TiXMLE_System.SetAttribute("Buzzer", "Off");
	if(myconfig.System.TrigBuzzer)
		TiXMLE_System.SetAttribute("ToneBuzzer", "On");
	else
		TiXMLE_System.SetAttribute("ToneBuzzer", "Off");
	TiXMLE_System.SetAttribute("Fan",FanString[myconfig.System.Fan]);
	TiXMLE_System.SetAttribute("FanSpeed",FanSpeedString[myconfig.System.FanSpeed]);
	TiXMLE_System.SetAttribute("Console",ConsoleString[myconfig.System.Console]);
	TiXMLE_System.SetAttribute("DebugLevel", myconfig.System.DebugLevel);

	TiXMLE_Configuration->InsertEndChild(TiXMLE_System);

	TiXmlElement TiXMLE_Splicer("Splicer");
	TiXMLE_Splicer.SetAttribute("splicername",myconfig.Splicer.SplicerName);
	TiXMLE_Splicer.SetAttribute("StreamingIPAddr",myconfig.Splicer.VideoIPAddr);
	TiXMLE_Splicer.SetAttribute("ControlIPAddr",myconfig.Splicer.ControlIPAddr);
	TiXMLE_Splicer.SetAttribute("PortBase",myconfig.Splicer.PortBase);
	TiXMLE_Configuration->InsertEndChild(TiXMLE_Splicer);

	TiXmlElement TiXMLE_Channel("Channel");

	for(iChannel=0;iChannel<4;iChannel++)
	{
		TiXMLE_Channel.SetAttribute("channelname", myconfig.Channel[iChannel].channelname);
		TiXMLE_Channel.SetAttribute("zonename", myconfig.Channel[iChannel].zonename);
		TiXMLE_Channel.SetAttribute("trigger", triggerstring[myconfig.Channel[iChannel].trigger]);
		TiXMLE_Channel.SetAttribute("cutoff", myconfig.Channel[iChannel].cutoff);
		TiXMLE_Channel.SetAttribute("entrydelim", myconfig.Channel[iChannel].entrydelim);
		TiXMLE_Channel.SetAttribute("exitdelim", myconfig.Channel[iChannel].exitdelim);
		TiXMLE_Channel.SetAttribute("exitflag", exitflagstring[myconfig.Channel[iChannel].exitflag]);
		TiXMLE_Channel.SetAttribute("genlock", genlockstring[myconfig.Channel[iChannel].genlock]);
		TiXMLE_Channel.SetAttribute("agcdec", agcstring[myconfig.Channel[iChannel].agcdec]);
		TiXMLE_Channel.SetAttribute("preroll", myconfig.Channel[iChannel].preroll);
		TiXMLE_Channel.SetAttribute("postblack", myconfig.Channel[iChannel].postblack);
		TiXMLE_Channel.SetAttribute("toneone", myconfig.Channel[iChannel].toneone);
		TiXMLE_Channel.SetAttribute("tonetwo", myconfig.Channel[iChannel].tonetwo);
		TiXMLE_Channel.SetAttribute("tonethree", myconfig.Channel[iChannel].tonethree);
		TiXMLE_Channel.SetAttribute("tonefour", myconfig.Channel[iChannel].tonefour);
		TiXMLE_Channel.SetAttribute("swbacktime", myconfig.Channel[iChannel].swbacktime);
		TiXMLE_Channel.SetAttribute("latestart", myconfig.Channel[iChannel].latestart);
		TiXMLE_Channel.SetAttribute("earlystop", myconfig.Channel[iChannel].earlystop);
		TiXMLE_Channel.SetAttribute("pal", palstring[myconfig.Channel[iChannel].pal]);
		TiXMLE_Channel.SetAttribute("frm_sec", myconfig.Channel[iChannel].frm_sec);

		TiXMLE_Channel.SetAttribute("bypass", bypassstring[myconfig.Channel[iChannel].bypass]);
		if(myconfig.Channel[iChannel].vnet_agc)
			TiXMLE_Channel.SetAttribute("vnet_agc", "On");
		else
			TiXMLE_Channel.SetAttribute("vnet_agc", "Off");
		if(myconfig.Channel[iChannel].vdec_agc)
			TiXMLE_Channel.SetAttribute("vdec_agc", "On");
		else
			TiXMLE_Channel.SetAttribute("vdec_agc", "Off");
		sprintf(Temp, "%.2f", MakeGainFloat(myconfig.Channel[iChannel].adecl_gain));
		TiXMLE_Channel.SetAttribute("GainDecoderLeft", Temp);
		sprintf(Temp, "%.2f", MakeGainFloat(myconfig.Channel[iChannel].adecr_gain));
		TiXMLE_Channel.SetAttribute("GainDecoderRight", Temp);
		sprintf(Temp, "%.2f", MakeGainFloat(myconfig.Channel[iChannel].anetl_gain));
		TiXMLE_Channel.SetAttribute("GainNetworkLeft", Temp);
		sprintf(Temp, "%.2f", MakeGainFloat(myconfig.Channel[iChannel].anetr_gain));
		TiXMLE_Channel.SetAttribute("GainNetworkRight", Temp);
		if(myconfig.Channel[iChannel].AudioMute)
			TiXMLE_Channel.SetAttribute("AudioMute", "On");
		else
			TiXMLE_Channel.SetAttribute("AudioMute", "Off");
		if(myconfig.Channel[iChannel].LevelMatchingEnable)
			TiXMLE_Channel.SetAttribute("LevelMatchingEnable", "On");
		else
			TiXMLE_Channel.SetAttribute("LevelMatchingEnable", "Off");
		if(myconfig.Channel[iChannel].NetworkGainEnable)
			TiXMLE_Channel.SetAttribute("NetworkGainEnable", "On");
		else
			TiXMLE_Channel.SetAttribute("NetworkGainEnable", "Off");
		TiXMLE_Configuration->InsertEndChild(TiXMLE_Channel);
	}
	doc->Print( stdout );
	return true;
}
double Configuration::MakeGainFloat(int a_gain)
{
	double f_gain = ((double)a_gain/2 - 85);
	return f_gain;
}
int Configuration::MakeGainByte(double f_gain)
{
	int a_gain = (f_gain + 85)*2;
	return a_gain;
}
