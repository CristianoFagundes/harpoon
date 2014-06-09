/* 
 * $Id: ccn_plugin.cc,v 1.5 2005-11-07 03:40:15 jsommers Exp $
 */

/*
 * Copyright 2004, 2005  Joel Sommers.  All rights reserved.
 * 
 * This file is part of Harpoon, a flow-level traffic generator.
 * 
 * Harpoon is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Harpoon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Harpoon; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */



#include <iostream>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include "configurator.hh"
#include "harpoon_plugin.hh"
#include "xmlrpc_util.hh"


namespace Harpoon
{
    class ccnPlugin : public HarpoonPlugin
    {
    public:
        ccnPlugin() : HarpoonPlugin() {}
        virtual ~ccnPlugin() {}

        virtual bool init(HarpoonPluginConfig *hpc, HarpoonLog *hlog)
            {
                HarpoonPlugin::init(hpc, hlog);
                return true;
            }

        virtual void client_session()
            {
		//./ccntraffic [-h] [-n flying] [-s starting URI index] -f <URI file path>
		//  -f - specify the location of the URI file
		//  -n - specify the number of concurrent interests, i.e., the number of queried URIs, default value = 100
		//  -s - specify the starting point of the requested interest. Default value = 0. With the support of this option,
		//       multiple machines can share the same URI file but query different portion of the URIs
		//  -h - print help message and exit
		//	-n 10 -f <URI file path>

		char comando[256];
		char nameApplication[256] = "ccntraffic";

		int  numeroInterestsConcurrent = 0;
		char locationURI[256] = "arquivoDelinkCcnx";

		sprintf(comando,"%s -n %d -f %s", nameApplication, numeroInterestsConcurrent, locationURI);
		system(comando);
            }

        virtual void server_session()
            {
		//./ccndelphi [-hv] [-x freshness_seconds] [-s reply_size_in_bytes] <URI prefix>
		//	 -h - print this message and exit
		//	 -v - verbose
		//	 -x seconds - set FreshnessSeconds
		//	 -s bytes - set size of replies (default 1024)

		FILE *filePipe;
		char arquivoPathServer[256] = "serverNamePath";

		char comando[256];
		char nameApplication[256] = "ccndelphi";

		int  sizeReply = 0;
		char prefixURI[256];


		if(!(filePipe = (FILE*) popen(arquivoPathServer, "r"))){
		    perror("Problems with pipe");  	
		    exit(1);
		}

		fscanf(filePipe,"%s",&prefixURI);

		sprintf(comando,"%s -s %d %s", nameApplication, sizeReply, prefixURI);
		system(comando);
            }
        virtual void shutdown()
            {
                std::cerr << "ccn shutdown" << std::endl;
                return;
            }
        virtual void stats(std::ostream &os)
            {
                XmlRpcUtil::encode_struct_value(os, "dummystats", "no stats!");
            }

    private:

    };
}


/*
 * factory function.  "factory_generator" is the symbol we look for
 * when loading harpoon plugins.
 */
extern "C"
{
#if STATIC_PLUGINS
    Harpoon::HarpoonPlugin *ccn_plugin_generator(void)
    {
        return dynamic_cast<Harpoon::HarpoonPlugin*>(new Harpoon::ccnPlugin()); 
    }
#else
    Harpoon::ccnPlugin *factory_generator(void)
    {
        return (new Harpoon::ccnPlugin()); 
    }
#endif
}

