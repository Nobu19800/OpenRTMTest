// -*-C++-*-
/*!
 * @file  UDPData.h
 * @brief 
 *
 */

#ifndef UDPData_H
#define UDPData_H

#pragma pack(push, 1)
struct UDPDataHeader
{
	uint32_t address_length;
	uint32_t comp_length;
	uint32_t port;
};

#pragma pack(pop)



#endif // UDPData_H


