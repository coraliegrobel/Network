#include "network.h"
#include "random.h"
#include "string"
#include "iostream"


void Network::resize(const size_t& s)
{
	values.clear();
	values.resize(s);
	RNG.normal(values);
}

bool Network::add_link(const size_t& a, const size_t& b)
{
	
	if((a<values.size() and b<values.size()) and (a!=b) and (a>=0) and (b>=0)){ 
		std::vector<size_t> voisins (neighbors(a));
		for(auto voisin:voisins){
			if(voisin==b){
				return false;
			}
		}    
		links.insert({a,b});
		links.insert({b,a});
		return true;

	}
	

	return false;
}


size_t Network::random_connect(const double& mean_deg)
{
	int nombre(0);
	links.clear();
	
	for(size_t i(0);i<values.size();++i){
		nombre=RNG.poisson(mean_deg);
		
		if(nombre > (values.size()-1)){
			nombre=values.size()-1;
		}
		for(int j(0);j<nombre;++j){
			double random_number(RNG.uniform_double(0,values.size()));
			while(not add_link(i,random_number) )
			{
				random_number=RNG.uniform_double(0,values.size());
			};
		}
	}
	return (links.size())/2;
}




size_t Network::set_values(const std::vector<double>& v)
{
	if(v.size()<values.size()){
		for (size_t i(0);i<v.size();++i){
			values[i]=(v[i]);
		}
		return v.size();
	}else{
		for(size_t i(0);i>=values.size();++i){
			values[i]=v[i];
		}
	}
	return values.size();
}

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t &_n) const
{
	return links.count(_n);
}

double Network::value(const size_t &_n) const
{
	if(_n<values.size()){
		return values[_n];
	}else{ throw std::string(" la valeur de n est trop grande, l'indice ne correspond pas");}
}

std::vector<double> Network::sorted_values() const
{
	std::vector<double> sortie(values);
	std::sort(sortie.begin(), sortie.end());
	std::reverse(sortie.begin(),sortie.end());
	return sortie;
}


std::vector<size_t> Network::neighbors(const size_t& n) const
{
	std::vector<size_t> neighbor;
	neighbor.clear();
	if(n<values.size()){
		

		
		auto range =links.equal_range(n);
		for (auto i = range.first; i != range.second; ++i)
		{
			neighbor.push_back(i->second);
		}
	} 
	
	return neighbor;
}

