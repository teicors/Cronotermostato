#pragma once

#include <SmingCore.h>
#include <Libraries/Timezone/include/Timezone.h>

class NtpClientDemo
{
public:
	NtpClientDemo() : ntpcp("10.10.20.1", 60, NtpTimeResultDelegate(&NtpClientDemo::ntpResult, this))
	{
	}

	void ntpResult(NtpClient& client, time_t ntpTime);

	time_t getNextSunriseSet(bool isSunrise);

private:
	NtpClient ntpcp;
	/*
	 * For handling local/UTC time conversions
	 * This is for the UK, amend as required
	 */
	static const TimeChangeRule dstStart;
	static const TimeChangeRule stdStart;
	static Timezone tz;
};

