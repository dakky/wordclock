// ESP8266 Wordclock
// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  See nteFunctions.cpp for description.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef _NTPFUNCTIONS_H_
#define _NTPFUNCTIONS_H_

#include <ezTime.h>

class NtpFunctionsClass {
    public:
        NtpFunctionsClass();
        ~NtpFunctionsClass();
        void begin();
        uint8_t getHours();
        uint8_t getMinutes();

    private:
        Timezone clockTimezoned;
};

extern NtpFunctionsClass NTP;

#endif