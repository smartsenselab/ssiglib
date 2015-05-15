//          Copyright Jeremy Coulon 2012-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//[MyPlugin_h_file
//==============
//==  Plugin  ==
//==============
#include "core/plugin.hpp"
#include "core/plugin_defs.hpp"

namespace Example
{
    // Your class must inherits from an interface.
    // Here we inherits from Plugin::IPlugin but you can write your own interface that may (or may not) inherits from Plugin::IPlugin as well.
    class MyPlugin : public ssf::Plugin
    {
    public:
        // Constructor
        MyPlugin();
        // Destructor
        virtual ~MyPlugin();

        // IPlugin interface implementation
        //@{
        virtual const std::string& getName() const;
        virtual const ssf::VersionInfo& getVersion() const;
        //@}

    protected:
        std::string name_;
        ssf::VersionInfo version_;
    };
}

// One important thing to don't forget here is to call the macro PLUGIN_FACTORY_DECLARATION(T).
// It creates factory methods that can be called from outside of your dynamic library.
// This factory implements a Singleton design pattern. There will be only one instance of MyPlugin during execution of the program.
// Declare plugin factory. Must be in the global namespace.
PLUGIN_FACTORY_DECLARATION( Example::MyPlugin )
//]