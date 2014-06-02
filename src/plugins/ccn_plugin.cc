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
		//iniciar temporiazador
		//iniciar ccntraffic
		//computar tempo total

                std::cerr << "ccn client session begin" << std::endl;
                sleep(10);
                std::cerr << "ccn client session end" << std::endl;
            }
        virtual void server_session()
            {

		//iniciar ccndelphi

                std::cerr << "ccn server session begin" << std::endl;
                sleep(10);
                std::cerr << "ccn server session end" << std::endl;
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

