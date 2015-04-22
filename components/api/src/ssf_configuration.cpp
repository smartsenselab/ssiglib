#include "api/ssf_configuration.hpp"

namespace ssf{

	SSFConfiguration::SSFConfiguration(){
		//Constructor
	}

	SSFConfiguration::~SSFConfiguration(){
		//Destructor
	}

	SSFConfiguration::SSFConfiguration(const SSFConfiguration& rhs){
		//Constructor Copy
	}

	SSFConfiguration& SSFConfiguration::operator=(const SSFConfiguration& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}
    
    std::map< std::string, std::vector< std::string > > SSFConfiguration::modules;
    void SSFConfiguration::addModule(const std::string& moduleName, const std::string& moduleType){
        std::map<std::string, std::vector<std::string> >::iterator it;
        it = SSFConfiguration::modules.find(moduleName);
        if(it == SSFConfiguration::modules.end()){
            std::vector<std::string> temp;
            temp.push_back(moduleType);
            std::pair<std::string, std::vector<std::string> > temp2(moduleName, temp);
            SSFConfiguration::modules.insert(temp2);
        }else{
            SSFConfiguration::modules[moduleName].push_back(moduleType);
        }
    }
    
    std::map< std::string, std::vector< std::pair< std::string, ParamTemp<class T> > > > SSFConfiguration::parameters;
    template <class type>
    void setParam(const std::string& moduleName, type param){
        
    }
    
    
    std::map< std::string, std::map< std::string, std::vector< std::pair< std::string, std::string > > > > SSFConfiguration::streams;
    void SSFConfiguration::setStream(const std::string& moduleGiver, const std::string& giverOut, const std::string& moduleReceiver, const std::string& receiverIn){
        std::map< std::string, std::map< std::string, std::vector< std::pair< std::string, std::string > > > >::iterator it1;
        it1 = SSFConfiguration::streams.find(moduleGiver);
        if(it1 == SSFConfiguration::streams.end()){
            //create relation with output and input
            std::pair< std::string, std::string > temp_pair(giverOut, receiverIn);
            std::vector<std::pair<std::string, std::string> > temp_vec;
            temp_vec.push_back(temp_pair);
            
            //create map of receiver
            std::pair<std::string, std::vector<std::pair<std::string, std::string> > > temp_pair2(moduleReceiver, temp_vec);
            std::map<std::string, std::vector< std::pair<std::string, std::string > > > temp_map;
            temp_map.insert(temp_pair2);
            
            //create final map
            std::pair<std::string, std::map< std::string, std::vector< std::pair< std::string, std::string > > > > temp_pair3(moduleGiver, temp_map);
            SSFConfiguration::streams.insert(temp_pair3);
        }else{
            std::map< std::string, std::vector< std::pair< std::string, std::string > > >::iterator it2;
            it2 = it1->second.find(moduleReceiver);
            if(it2 == it1->second.end()){
                
                //create relation with output and input
                std::pair< std::string, std::string > temp_pair(giverOut, receiverIn);
                std::vector<std::pair<std::string, std::string> > temp_vec;
                temp_vec.push_back(temp_pair);
                
                //creating new receiver
                std::pair<std::string, std::vector<std::pair<std::string, std::string> > > temp_pair2(moduleReceiver, temp_vec);
                
                //adding receiver
                SSFConfiguration::streams[moduleGiver].insert(temp_pair2);
                
            }else{
                
                //create relation with output and input
                std::pair< std::string, std::string > temp_pair(giverOut, receiverIn);
                SSFConfiguration::streams[moduleGiver][moduleReceiver].push_back(temp_pair);
                
            }
        }
    }

}
