/*

  This file is a part of JRTPLIB
  Copyright (c) 1999-2017 Jori Liesenborgs

  Contact: jori.liesenborgs@gmail.com

  This library was developed at the Expertise Centre for Digital Media
  (http://www.edm.uhasselt.be), a research center of the Hasselt University
  (http://www.uhasselt.be). The library is based upon work done for 
  my thesis at the School for Knowledge Technology (Belgium/The Netherlands).

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/

/**
 * \file rtpstructs.h
 */

#ifndef RTPSTRUCTS_H

#define RTPSTRUCTS_H

#include "rtpconfig.h"
#include "rtptypes.h"

namespace jrtplib
{

struct RTPHeader
{
	uint8_t firstbyte;
	uint8_t csrccount() { return (firstbyte) & 0x07; }
	uint8_t extension() { return (firstbyte >> 4) & 0x01; }
	uint8_t padding() { return (firstbyte >> 5) & 0x01; }
	uint8_t version() { return (firstbyte >> 6) & 0x03; }
	
	uint8_t secondbyte;
	uint8_t payloadtype() { return (secondbyte) & 0x7f; }
	uint8_t marker() { return (secondbyte >> 7) & 0x01; }

	void set_version(uint8_t version) { firstbyte = (firstbyte   & 0b00111111) | (version << 6); }
	void set_padding(uint8_t padding) { firstbyte = (firstbyte   & 0b11011111) | (padding << 5); }
	void set_extension(uint8_t extension) { firstbyte = (firstbyte & 0b11101111) | (extension << 4); }
	void set_csrccount(uint8_t csrccount) { firstbyte = (firstbyte & 0b11110000) | (csrccount); }

	void set_marker(uint8_t marker) { secondbyte = (secondbyte & 0b01111111) | (marker << 7); }
	void set_payloadtype(uint8_t payloadtype) { secondbyte = (secondbyte & 0b10000000) | (payloadtype); }
	
	uint16_t sequencenumber;
	uint32_t timestamp;
	uint32_t ssrc;
};

struct RTPExtensionHeader
{
	uint16_t extid;
	uint16_t length;
};

struct RTPSourceIdentifier
{
	uint32_t ssrc;
};

struct RTCPCommonHeader
{
	uint8_t firstbyte;
	uint8_t count() { return (firstbyte) & 0b00011111; }
	uint8_t padding() { return (firstbyte >> 5) & 0x01; }
	uint8_t version() { return (firstbyte >> 6) & 0x03; }

	void set_version(uint8_t version) { firstbyte = (firstbyte & 0b00111111) | (version << 6); }
	void set_padding(uint8_t padding) { firstbyte = (firstbyte & 0b11011111) | (padding << 5); }
	void set_count(uint8_t count) { firstbyte = (firstbyte & 0b11100000) | (count); }

	uint8_t packettype;
	uint16_t length;
};

struct RTCPSenderReport
{
	uint32_t ntptime_msw;
	uint32_t ntptime_lsw;
	uint32_t rtptimestamp;
	uint32_t packetcount;
	uint32_t octetcount;
};

struct RTCPReceiverReport
{
	uint32_t ssrc; // Identifies about which SSRC's data this report is...
	uint8_t fractionlost;
	uint8_t packetslost[3];
	uint32_t exthighseqnr;
	uint32_t jitter;
	uint32_t lsr;
	uint32_t dlsr;
};

struct RTCPSDESHeader
{
	uint8_t sdesid;
	uint8_t length;
};

} // end namespace

#endif // RTPSTRUCTS

