#include <bcrypt/BCrypt.hpp>
#include "json.hpp"
#include <iostream>
using namespace std;
using json = nlohmann::json;

int main()
{
	string password = "test";
	string hash = BCrypt::generateHash(password);
	cout << hash;
	cout << BCrypt::validatePassword(password, hash) << endl;
	cout << BCrypt::validatePassword("test1", hash) << endl;
	json j{{"name", "nooshin"},
		   {"family", "mishmast"}};
	cout << j["name"] << endl;
	cout << j["family"];

	return 0;
}
