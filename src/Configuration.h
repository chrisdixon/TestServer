/*
 * Configuration.h
 *
 *  Created on: Jun 27, 2013
 *      Author: dvc
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "config.h"
#include <tinyxml.h>

class Configuration {
public:
	Configuration();
	virtual ~Configuration();
	int ReadFile(void);
	int SaveFile(void);
	int ProcessXMLStream(const char* XMLStream);
	void XMLStream(char* XMLStream);

private:
	ConfigXMLT myconfig;
	TiXmlDocument* doc;
	int GenerateXMLDoc(void);
	int ProcessXMLDoc(void);
	double MakeGainFloat(int a_gain);
	int MakeGainByte(double f_gain);
};

#endif /* CONFIGURATION_H_ */
