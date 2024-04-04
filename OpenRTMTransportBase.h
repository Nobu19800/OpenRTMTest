// -*-C++-*-
/*!
 * @file  CORBATransportBase.h
 * @brief
 *
 */

#ifndef CORBATRANSPORTBASE_H
#define CORBATRANSPORTBASE_H

#pragma pack(push, 1)
struct InDataHdr
{
	uint32_t id;
	uint64_t pub_sec_count;
	uint64_t pub_nsec_count;
};

struct DataHdr
{
	struct InDataHdr out;
	uint64_t sub_sec_count;
	uint64_t sub_nsec_count;
};
#pragma pack(pop)

#endif // MYSERVICESVC_IMPL_H
