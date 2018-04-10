#ifndef FABRICK_NETWORK_INTERFACE_H
#define FABRICK_NETWORK_INTERFACE_H

class FabrickNetIF {
	public:
	virtual ~FabrickNetIF() {};
	virtual bool send(String deviceId, int frameCounter, int channel, int dataType, String data, int dataLengthInHex) = 0;
};

#endif