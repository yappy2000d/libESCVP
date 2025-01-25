/**
 * @file ESCVP.cpp
 * @brief ESC/VP.net protocol packet definition
 * @author LSweetSour
 */

#include <cstring>

#include "ESCVP.h"

#ifndef _WIN32
    #define strcpy_s(dest, size, src) strncpy(dest, src, size)  
#endif

namespace ESCVP
{
    PasswordHeader::PasswordHeader() {
        identifier = Identifier::Password;
        attribute = static_cast<UCHAR>(0);
    }
    PasswordHeader::PasswordHeader(const STR password) {
        identifier = Identifier::Password;
        attribute = static_cast<UCHAR>(1);
        strcpy_s(reinterpret_cast<char*>(infomation), 16, reinterpret_cast<const char*>(password));
    }

    NewPasswordHeader::NewPasswordHeader() {
        identifier = Identifier::New_Password;
        attribute = static_cast<UCHAR>(0);
    }
    NewPasswordHeader::NewPasswordHeader(const STR projector_name) {
        identifier = Identifier::New_Password;
        attribute = static_cast<UCHAR>(1);
		strcpy_s(reinterpret_cast<char*>(infomation), 16, reinterpret_cast<const char*>(projector_name));
    }

    ProjectorNameHeader::ProjectorNameHeader() {
        identifier = Identifier::Projector_Name;
        attribute = static_cast<UCHAR>(0);
    }
    ProjectorNameHeader::ProjectorNameHeader(const Encoding enc, const STR projector_name) {
        identifier = Identifier::Projector_Name;
        attribute = static_cast<UCHAR>(enc);
		strcpy_s(reinterpret_cast<char*>(infomation), 16, reinterpret_cast<const char*>(projector_name));
    }

    IMTypeHeader::IMTypeHeader(const UCHAR im_type) {
        identifier = Identifier::IM_Type;
        attribute = im_type;
    }

    ProjectorCmdTypeHeader::ProjectorCmdTypeHeader(const UCHAR cmd_type) {
        identifier = Identifier::Projector_Cmd_Type;
        attribute = cmd_type;
    }
}
