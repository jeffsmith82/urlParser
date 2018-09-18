#include <iostream>
#include <string>
#include <string_view>

void* operator new(std::size_t count){
    std::cout << "   " << count << " bytes" << std::endl;
    return malloc(count);
}

//general scheme is 
// [scheme:][//[userinfo@]host][/]path[?query][#fragment]

struct URL {
	std::string	rawString;
	std::string_view scheme;
	std::string_view username;
	std::string_view password;
	bool passwordSet = false;
	std::string_view host;
	std::string_view path;
	std::string_view rawPath;
	std::string_view rawQuery;
	std::string_view fragment;
};

//Parse

URL parse(const std::string rawurl){
	URL url;
	//Split # off the url if present
	std::string_view s = rawurl.substr(rawurl.find('#')+1);
	url.fragment = s;
	std::cout << url.fragment << std::endl;
	//Move this last
	url.rawString = std::move(rawurl);
	return url;
}
	
int main(){

	std::string st = "https://example.com/foo%2fbar#tester";
	auto url = parse(st);
	std::cout << "rawstring: " << url.rawString << std::endl;
	std::cout << "fragment: " << url.fragment << std::endl;
	return 0;
}

