// ------------------------------------------------
// File : host.h
// Author: giles
//
// (c) peercast.org
// ------------------------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// ------------------------------------------------

#ifndef _HOST_H
#define _HOST_H

class String;

// ----------------------------------
class Host
{
    inline unsigned int ip3() const
    {
        return (ip>>24);
    }
    inline unsigned int ip2() const
    {
        return (ip>>16)&0xff;
    }
    inline unsigned int ip1() const
    {
        return (ip>>8)&0xff;
    }
    inline unsigned int ip0() const
    {
        return ip&0xff;
    }

public:
    Host() { init(); }
    Host(unsigned int i, unsigned short p)
    {
        ip = i;
        port = p;
    }
    Host(const std::string& hostname, uint16_t port)
    {
        fromStrName(hostname.c_str(), port);
    }


    void    init()
    {
        ip = 0;
        port = 0;
    }

    bool    isMemberOf(const Host &) const;

    bool    isSame(Host &h) const
    {
        return (h.ip == ip) && (h.port == port);
    }

    bool    classType() const { return globalIP(); }

    bool    globalIP() const
    {
        // local host
        if ((ip3() == 127) && (ip2() == 0) && (ip1() == 0) && (ip0() == 1))
            return false;

        // class A
        if (ip3() == 10)
            return false;

        // class B
        if ((ip3() == 172) && (ip2() >= 16) && (ip2() <= 31))
            return false;

        // class C
        if ((ip3() == 192) && (ip2() == 168))
            return false;

        return true;
    }

    bool    localIP() const
    {
        return !globalIP();
    }

    bool    loopbackIP() const
    {
        return ((ip3() == 127) && (ip2() == 0) && (ip1() == 0) && (ip0() == 1));
    }

    bool    isValid() const
    {
        return (ip != 0);
    }

    bool    isSameType(Host &h) const
    {
            return ( (globalIP() && h.globalIP()) ||
                     (!globalIP() && !h.globalIP()) );
    }

    void    IPtoStr(char *str) const
    {
        sprintf(str, "%d.%d.%d.%d", (ip>>24)&0xff, (ip>>16)&0xff, (ip>>8)&0xff, (ip)&0xff);
    }

    ::String IPtoStr();

    void    toStr(char *str) const
    {
        sprintf(str, "%d.%d.%d.%d:%d", (ip>>24)&0xff, (ip>>16)&0xff, (ip>>8)&0xff, (ip)&0xff, port);
    }

    std::string str(bool withPort = true) const
    {
        char buf[22];
        if (withPort)
            toStr(buf);
        else
            IPtoStr(buf);
        return buf;
    }

    operator std::string () const
    {
        return str();
    }

    bool operator < (const Host& other) const
    {
        if (ip == other.ip)
            return port < other.port;
        else
            return ip < other.ip;
    }

    bool operator == (const Host& other) const
    {
        return const_cast<Host*>(this)->isSame(const_cast<Host&>(other));
    }

    void    fromStrIP(const char *, int);
    void    fromStrName(const char *, int);

    bool    isLocalhost();

    unsigned int    ip;
    unsigned short  port;
};

#endif
