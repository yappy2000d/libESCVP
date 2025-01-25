/**
 * @file ESCVP.h
 * @brief ESC/VP.net protocol packet definition
 * @author LSweetSour
 */

#pragma once

#ifdef _WIN32
    #ifdef LIBESCVP_EXPORTS
        #define LIBESCVP_API __declspec(dllexport)
    #else
        #define LIBESCVP_API __declspec(dllimport)
    #endif
#else
    #define LIBESCVP_API __attribute__((visibility("default")))
#endif

#include <cstdint>
#include <vector>

namespace ESCVP
{
    using BYTE = uint8_t;
    using UCHAR = uint8_t;
    using STR = char[16];
    using USHORT = uint16_t;

    struct LIBESCVP_API Header
    {
        enum class Identifier : UCHAR
        {
            Null,                   ///< Reserved
            Password,
            New_Password,
            Projector_Name,
            IM_Type,
            Projector_Cmd_Type
        };
        Identifier identifier;      ///< Header identifier
        UCHAR attribute;
        STR infomation;
    };

    /**
     * @brief Password header
     * @details
     * - attribute = 0: No password
     * - attribute = 1: Plain (no encoding)
     * - infomation: Password (16 bytes)
     */
    struct LIBESCVP_API PasswordHeader : Header
    {
        PasswordHeader();                               ///< No password
        PasswordHeader(const STR password);	            ///< Plain (no encoding)
    };

    /**
     * @brief New-Password header
     */
    struct LIBESCVP_API NewPasswordHeader : Header
    {
        NewPasswordHeader();
        NewPasswordHeader(const STR projector_name);    ///< Plain (no encoding)
    };

    /**
     * @brief Projector-Name header
     * @details
     * - attribute = 0: No projector name
     * - attribute = 1: US-ASCII
     * - attribute = 2: Shift_JIS (Reserved)
     * - attribute = 3: EUC-JP (Reserved)
     * - infomation: Projector name (16 bytes)
     */
    struct LIBESCVP_API ProjectorNameHeader : Header
    {
        enum class Encoding : UCHAR
        {
            Plain,
            US_ASCII,
            Shift_JIS,
            EUC_JP,
        };
        ProjectorNameHeader();  ///< No projector name
        ProjectorNameHeader(const Encoding enc, const STR projector_name);
    };

    /**
     * @brief IM-Type header
     * @details
     * - attribute = 16~19: Type A
     * - attribute = 0C: Type D
     * - attribute = 20: Initial model of EMP/PL-735
     * - attribute = 21: Type C, Type E
     * - attribute = 22: Type F
     * - attribute = 23: Type G
     * - attribute = 40: Type H
     * - attribute = 41: Type I
     * - attribute = 42: Type J
     * - attribute = 50: Type K
     * - attribute = others: Reserved
     * - infomation: all bytes are 0x00
     */
    struct LIBESCVP_API IMTypeHeader : Header
    {
        IMTypeHeader(const UCHAR im_type = 0x00);
    };

    /**
     * @brief Projector-Cmd-Type header
     * @details
     * - attribute = 0x16: ESC/VP Level 6
     * - attribute = 0x21: ESC/VP21
     * - infomation: all bytes are 0x00
     */
    struct LIBESCVP_API ProjectorCmdTypeHeader : Header
    {
        enum class CmdType : UCHAR
        {
            ESCVPLevel6 = 0x16,
            ESCVP21 = 0x21,
        };
        ProjectorCmdTypeHeader(const UCHAR cmd_type = 0x00);
    };

    /**
     * @brief Common part of the request and response
     * @details
     * An ESC/VP.net packet consists of a common part and number of "headers".
     */
    struct LIBESCVP_API CommonPart
    {
        enum class Type : UCHAR
        {
            Null,               ///< Reserved
            HELLO,
            PASSWORD,
            CONNECT,
        };

        enum class Status : BYTE
        {
            Null = 0x00,                   ///< Always 0 for request
            OK = 0x20,                     ///< Success
            BadRequest = 0x40,             ///< Request is invalid
            Unauthorized = 0x41,           ///< Unauthorized
            Forbidden = 0x45,              ///< Password is incorrect
            Unavailable = 0x53,            ///< The projector is busy, etc.
            VersionNotSupported = 0x55,    ///< Unsupported version
        };

        char protocol[10] = { 0x45,0x53,0x43,0x2F,0x56,0x50,0x2E,0x6E,0x65,0x74 };  ///< "ESC/VP.net"
        BYTE version = 0x10;
        Type type = Type::Null;
        USHORT Reserved = 0;
        Status status = Status::Null;
        UCHAR length = 0;                  ///< number of the following headers
    };

    using Packet = std::pair<CommonPart, std::vector<Header>>;
}
